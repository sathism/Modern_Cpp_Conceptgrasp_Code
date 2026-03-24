#include <iostream>
#include <memory>

/* This code snipped demonstrates about std::unique_ptr: Its a smart pointer introduced 
   in C++11 that manages a dynamically allocated object through exclusive ownership. 
   This means only one unique_ptr can own a specific resource at any given time.
   When the unique_ptr goes out of scope, it automatically deletes the object it points to.
   Key Benefits
   ============
   Automatic Memory Management (No Leaks)
   Zero Overhead (Performance)
   Prevention of "Dangling Pointers"
   Clear Intent in Code
*/
   
class Test {
  public :
    inline Test() {
      std::cout<<"Inside Test Constructor"<<std::endl;
    }
    ~Test() {
       std::cout<<"Inside ~Test Destructor"<<std::endl;
    }
    inline void print() {
       std::cout << "Inside Test::Print"<<std::endl;
    }
};

class CustomDeleter {
  public :
     void operator()(Test *ptr) const {
       std::cout << "Custom Delete Functor Ccalled" << std::endl;
       delete ptr;
     }
};

// 1. BY VALUE: The function takes OWNERSHIP. 
// The original pointer becomes null.
void takeOwnership(std::unique_ptr<Test> p) {
    if (p) p->print();
} // 'p' is deleted here automatically


// 2. BY REFERENCE: The function can MODIFY the pointer (e.g., reset it).
// The original pointer stays valid unless the function changes it.
void modifyPointer(std::unique_ptr<Test>& p) {
    if (p) p->print();
    // p.reset(); // If we did this, the caller's pointer would become null
}
int main() {

  //Usage - 1
  std::unique_ptr<Test> up(new Test());
  std::unique_ptr<Test> up1(new Test());
  std::unique_ptr<Test> up2(new Test());
 
  //Usage - 2
  std::unique_ptr<Test> up_1 = std::make_unique<Test>();

  //Usage - 3 with cusomt deleter
  std::unique_ptr<Test, CustomDeleter> up_2(new Test(), CustomDeleter());

  //custom lambda delete
  auto res = [](Test *ref) {
     std::cout << "Inside Custom Delete Lambda " << std::endl;
     delete ref;
  };
  std::unique_ptr<Test, decltype(res)> up_3(new Test(), res);
  
  //Derefencing
  up->print();
  (*up).print();

  /* Copying of unique_Ptr is not allowlwed but transfer ofe
   * ownership is possible throught move
   */
  auto new_owner = std::move(up);
  new_owner->print();


  //Fetch the raw pointer
  auto ptr = up.get();
  ptr->print();


  //Reset the unique ptr
  up.reset();

  //Manual Control
  auto raw = up_1.release();
  //take care  raw pointer deletion manually
  delete raw;
  
  //Passing by value
  takeOwnership(std::move(up1));

  //Passing by reference 
  modifyPointer(up2);

  return 0;
}
