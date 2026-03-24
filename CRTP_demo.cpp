#include <iostream>
#include <string>

/* 
     CRTP
     ----
    The Curiously Recurring Template Pattern (CRTP) is a C++ idiom used to achieve 
    static polymorphism at compile time, avoiding the runtime overhead of virtual functions. 
    In this pattern, a class derives from a base class template that is instantiated with 
    itself as a template argument.

  Key Benefits:
  --------------
   1. Performance: Eliminates the need for a virtual table (vtable) and pointer dereferencing, enabling compiler optimizations like inlining.
   2. Code Reuse: Allows the base class to provide common functionality that depends on specific implementations in derived classes.
   3. Static Type Safety: Since relationships are resolved at compile time, the compiler can catch type mismatches early.
   
  Common Use Cases:
  -----------------
  1. Static Polymorphism: Providing a common interface for different types without the cost of virtual calls.
  2. Mixins: Adding specific behaviors to a class by inheriting from multiple CRTP base classes.
  3. Object Counter: Tracking the number of instances for specific types using a static member in the CRTP base.
  4. Method Chaining: Enabling fluent interfaces where methods in the base class can return a reference to the derived type. 
  5. Introspection/Static Reflection(The "Logic" Pattern) : Introspection is a technique where the base class "looks into" 
     the derived class to see what it is capable of. It doesn't add data; it changes behavior based on what it finds.
  
  History
  -------
   C++ 11 Introduced a standard library utility that explicitly uses the CRTP idiom -> std::enable_shared_from_this
   C++ 20: Concepts can now be used to express the requirements of a CRTP base class more clearly, providing better compile-time error messages.
   C++23: Introduced "deducing this" (explicit object parameters), which provides a cleaner, modern syntax that can replace many traditional CRTP use cases.

*/

/* 
  As we are expecting C++ 26 release anytime this year, Lets focus on how to use CRTP based on 
  the last released C++ version(23).
*/

//Use case-1 Static Polymorphism (Interface Pattern)
class Base {

  public:
   inline void implementation()   {    
       std::cout << "Base Implementation" << std::endl;
   }

   template <typename Self>
   inline void do_work(this Self&& self)   {
       self.implementation();
   }
};

class Derived : public Base {
   public :
   inline void implementation()   {
      std::cout << "Derived Implementation" << std::endl;
   }
};

//Use Case-2 Method Chaining (Fluent Interface)
/* The base class methods can return a reference to the Derived type directly, 
 * allowing you to chain methods from both the classes
*/
class PrinterBase {
   public :
    template <typename Self>
    auto& print(this Self&& self, const char* msg) {
        std::cout << msg << "\n";
        return self; // 'self' is the Derived type!
    }
};

class ColorPrinter : public PrinterBase {
   public :
    ColorPrinter& set_color(int c) { return *this; }
};

// Use Case-3  Mixins (Adding Reusable Logic)
/*   You can inject common logic into any class just by inheriting from a base.
     For example, an "Equality" mixin that uses a member value

  When to Choose Mixins
  ----------------------
  Cross-Cutting Concerns: Use mixins for shared behaviors like logging, serialization, comparison operators, 
                          or caching that apply to many different types of objects.
  Avoiding Deep Hierarchies: Instead of a single, deep inheritance tree where a class must inherit everything 
                             from its parents, mixins allow you to compose a class "horizontally" from small, independent blocks of functionality.
  Code Reuse Across Unrelated Types: If both a User class and a Product class need a Timestamp or ID, a mixin provides this implementation once, 
                                     and you simply "mix it in" to both.
  Real World Examples :
  ---------------------
    std::enable_shared_from_this: A standard library mixin that adds the ability for an object to safely generate a shared_ptr to itself.
    std::nested_exception: A mixin that allows any exception class to store and rethrow another "nested" exception.
*/

class EqualityMixin {
  public:
    // C++23 "Deducing this" allows the base to compare two Derived objects
    template <typename Self>
    bool operator==(this const Self& lhs, const Self& rhs) {
        return lhs.value == rhs.value;
    }
};

class ID : public EqualityMixin {
  public:
    int value;
    // Constructor for easy initialization
    ID(int v) : value(v) {}
};

//Use Case-4 Recursive Visitor/Custom Logic
/* 
   You can use the type of self to perform different logic based on the actual object type at the call site.
   Why this is powerful:
   ---------------------
   Zero Overhead: The decision of which branch to take is made by the compiler. There is no if statement running while your program is executing.
   Flexible Interfaces: You don't have to force every derived class to implement name(). The base class gracefully handles classes that choose not to provide it.
   Static Safety: If you make a typo in name(), the compiler simply falls into the else block (or you can make it a compiler error using static_assert).
*/
class Logger {
    public:
    template <typename Self>
    void log(this Self&& self) {
        // Compile-time check: does the derived type have a name() method?
        if constexpr (requires { self.name(); }) {
            std::cout << "[IDENTIFIED] Logging: " << self.name() << "\n";
        } else {
            std::cout << "[ANONYMOUS] Logging unknown type\n";
        }
    }
};

// Case A: A class that provides the required method
class User : public Logger {
   public:
      std::string name() const { return "Admin_User_01"; }
};

// Case B: A class that does NOT provide the method
class Device : public Logger {
  public:
    int id = 404;
    // No name() method here
};

// Use Case-5 Object Counter
/* In the context of CRTP, an Object Counter is a reusable template base class that tracks how many active 
 *  instances of a specific derived class exist in memory at any given time.
 *  The Definition
 *  It relies on two core C++ mechanics:
 *  Template Instantiation: Because the base is Counter<Derived>, the compiler creates a unique static variable for every different derived class.
 *  RAII (Resource Acquisition Is Initialization): It uses the Constructor to increment and the Destructor to decrement the count automatically.
*/

template <typename T>
class Counter {
   public :
    static inline int alive_count = 0;

    // Increment when an object is created
    Counter() { ++alive_count; }
    
    // Decrement when an object is destroyed
    ~Counter() { --alive_count; }

    /* Not required to pass this Self&& self as its static function aslo
     *  no template is required
     */
    static int count() {
        return T::alive_count;
    }
};

class Users : public Counter<Users> {};
class Tasks : public Counter<Tasks> {};

//Driver code to demonstrate CRTP
int main() {
     Base b{};
     Derived d{};
     PrinterBase pb{};
     ColorPrinter cd{};

     //Use case 1 - Static Polymorphism
     b.do_work();
     d.do_work();

     //Use case 2 - Method Chaining (Fluent Interface)
     cd.print("hello").set_color(1);

     //Use case 3 - Mixins (Adding Reusable Logic)
     // 1. Create two identical IDs
     ID id1{101};
     ID id2{101};

     // 2. Create a different ID
     ID id3{202};

    // 3. Demonstrate the Mixin logic
    std::cout << std::boolalpha; // Prints true/false instead of 1/0
    
    std::cout << "Is id1 == id2? " << (id1 == id2) << "\n"; // true
    std::cout << "Is id1 == id3? " << (id1 == id3) << "\n"; // false

     //Use case 4 - Recursive Visitor
     User u;
     Device dev;

    // The same 'log' method behaves differently based on the calling type
    u.log(); // Output: [IDENTIFIED] Logging: Admin_User_01
    dev.log(); // Output: [ANONYMOUS] Logging unknown type
    
    //Use Case 5 - Object Counter

    // 1. Initial State
    std::cout << "Initial Users: " << Users::count() << "\n"; // 0
    // 2. Create objects
    Users u1, u2;
    {
        Users u3;
        Tasks t1;
        std::cout << "Users (inside block): " << Users::count() << "\n"; // 3
        std::cout << "Tasks (inside block): " << Tasks::count() << "\n"; // 1
    } // u3 and t1 go out of scope here

    // 3. Final State
    std::cout << "Final Users: " << Users::count() << "\n"; // 2
    std::cout << "Final Tasks: " << Tasks::count() << "\n"; // 0

     return 0;
}

