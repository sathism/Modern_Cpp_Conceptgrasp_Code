#include <iostream>

class Test {
    public :
       Test() { std::cout << "Test Constructor " <<"\n";}
       Test(Test &&ref) { std::cout << "Test Move Constructor" << "\n";}
};

auto fn() {
      Test obj;
      //Compile does Named return value optimizatiton
      return obj;
}

int main() {
    //calls default consturctor
    Test ref = fn();
}
