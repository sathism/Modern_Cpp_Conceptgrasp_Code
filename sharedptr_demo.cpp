#include <memory>
#include <iostream>

/* This code snippet demonstrates all about shared_ptr
   In  C++, std::shared_ptr is a smart pointer that provides shared ownership of a dynamically allocated object.

   The core mechanism is reference counting: 
   ========================================
   Control Block: Internally, a shared_ptr holds two pointers: one to the managed object and one to a "control block".
   Counting: This control block stores a "use count" (the number of shared_ptr instances currently owning the object) 
             and a "weak count".
   Creation & Copying: When you create a new shared_ptr or copy an existing one, the use count increments.
   Destruction: When a shared_ptr goes out of scope or is reset, the count decrements.
   Cleanup: The managed object is automatically deleted only when the last shared_ptr owning it is destroyed (i.e., 
            when the use count hits zero). 

   Key Benefits
   ============
   Automatic Memory Management: Eliminates the need for manual delete calls, drastically reducing the risk of 
                                memory leaks and double-free errors.
   Shared Lifetimes: Ideal for complex data structures where the "last user" of a resource is non-deterministic 
                     (e.g., asynchronous operations or shared caches).
   Thread Safety: The internal reference counter is incremented and decremented atomically, making it safe 
                  to copy or destroy shared pointers across different threads without causing race conditions on 
                  the counter itself.
   Flexibility: Supports custom deleters (useful for non-memory cleanup tasks) and casting via functions like 
                std::static_pointer_cast.

   Important Trade-offs
   =====================
   Overhead: It is slightly heavier and slower than unique_ptr due to the need for a control block and atomic 
             counter updates.
   Circular Dependencies: If two objects hold a shared_ptr to each other, they will never be deleted. i
                           You must use std::weak_ptr to break these cycles. 
*/
struct Base {
    virtual ~Base() = default;
    virtual void say() { std::cout << "Base\n"; }
};

struct Derived : public Base {
    int id = 20 ;
    Derived(int i) : id(i) {}
    Derived() {}
    
    void say() override { std::cout << "Derived " << id << "\n"; }
};

class Test {
  public :
     inline Test() {
        std::cout<<"Inside Test Constructor"<<std::endl;
     }
     ~Test() {
        std::cout<<"Insider ~Test Destructor"<<std::endl;
     }
     inline void print() {
       std::cout << "Inside Test::Print()" << std::endl;
     }
};

int main() {
   std::shared_ptr<Test> sp = std::make_shared<Test>();

   //Copying Increases reference count
   std::shared_ptr<Test> sp1(sp);
   std::cout << "Use Count " << sp1.use_count() << std::endl;
   
   //ways to access the shared ptr using * and -> operator
   sp->print();
   (*sp).print();
   

   //get the raw pointer
   auto ptr = sp1.get();
   ptr->print();
   
   //Release ownership
   sp.reset();
   std::cout << "Use Count " << sp1.use_count() << std::endl;
   
   std::shared_ptr<Test> sp2(sp1);
   std::cout << "Use Count " << sp1.use_count() << std::endl;
   
   //Release ownership of sp1 and adds new ownership
   sp1.reset(new Test());
   std::cout << "Use Count " << sp1.use_count() << std::endl;

   //Swapping pointers
   auto sp3 = std::make_shared<Test>();
   sp1.swap(sp3);
   
   //owner before check
   if(sp1.owner_before(sp3))
      std::cout << "owner_before" << std::endl;

   //comparison with nullptr
   if (sp2 == nullptr) 
       std::cout << "sp2 is empty\n";

   //Pointer Casting (static, dynamic, const)
   std::shared_ptr<Base> basePtr = std::make_shared<Base>(); // Implicit upcast
   auto derivedPtr = std::dynamic_pointer_cast<Derived>(basePtr); // Safe downcast
   if (derivedPtr) 
          std::cout << "Cast successful!\n";

    auto derived = std::make_shared<Derived>();

    // Static cast: Derived to Base (Upcast)
    std::shared_ptr<Base> base = std::static_pointer_cast<Base>(derived);
    
    // Const cast: Add/Remove const
    auto constPtr = std::make_shared<const int>(42);
    auto modifiablePtr = std::const_pointer_cast<int>(constPtr); 
    *modifiablePtr = 100; // Now allowed

   return 0;
}

