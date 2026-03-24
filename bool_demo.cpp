#include <iostream>
#include <vector>

int main() {

    std::vector<bool> v = {1, 1, 1};
    /*  compiler allowes this declaration : int &&ref = 5 but it wont allow
     *  int &ref = 5
     *  Hence w.r.t bool the below for loop is totally fine
     *  
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
       the below throws compilations error
     */
    for (auto  &ref : v) {
        ref = 0; 
        std::cout << "Result: " << ref << "\n";
    }

    for (auto  &ref : v) {
        ref = 0; 
        std::cout << "Result: " << ref << "\n";
}
