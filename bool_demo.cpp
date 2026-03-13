#include <iostream>
#include <vector>

int main() {

    std::vector<bool> v = {1, 1, 1};
    /* this is posisble w.r.t to bool because
     *  int &&ref = 5 is allowed by compiler
    */
    for (auto &&ref : v) {
        ref  = 0 ; 
        std::cout << "Result: " << ref << "\n";
    }

    /* when iterating the vector v.begin returns a temporatory proxy object 
       std::vector<bool>::reference which is an rvalue ref  - non-const lvalue	 
       The Rule: A non-const lvalue reference (&) refuses to bind to an rvalue (temporary).
       The Reason: The compiler thinks, "If I let you make a reference to this temporary, 
       and you change it, the temporary will vanish in a millisecond and your change might be lost or 
       you'll be left holding a 'broken' reference."
       example int &ref = 5 // is not possible
     */
    for (auto  &ref : v) {
        ref = 0; 
        std::cout << "Result: " << ref << "\n";
    }

    for (auto  &ref : v) {
        ref = 0; 
        std::cout << "Result: " << ref << "\n";
}
