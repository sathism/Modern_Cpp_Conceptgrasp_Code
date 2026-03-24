#include <iostream>
#include <memory>

/* This code snippet demonstrates c++ weak_ptr
   A weak_ptr is a non-owning observer. It points to an object managed by a shared_ptr
   but does not increment the reference count. This is primarily used to break circular 
   dependencies or safely cache objects that might be deleted.
 */

int main() {

    auto shared = std::make_shared<int>(42);
    std::weak_ptr<int> weak = shared;

    // To use it, you must "lock" it
    if (auto tempShared = weak.lock()) {
        std::cout << "Value is: " << *tempShared << "\n";
    } else {
        std::cout << "Object is gone!\n";
    }

    shared.reset(); // Destroy the object

    if (weak.expired()) {
        std::cout << "Confirmed: Object expired.\n";
    }
  return 0;
}
