#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <memory>
class Base
{
   public:
      virtual void print() = 0;
      virtual ~Base() = default ;
};

class IntDerived : public Base
{
   private:
     int data = 0;
   public:
      IntDerived(int input) : data(input) { }
      void print() override { std:: cout << "Printing Integer Value " << data <<"\n"; }
      ~IntDerived() { std:: cout << "IntDerived - Destructor \n";} 
};

class StringDerived : public Base {

   private :
      std::string data;
  public :
      StringDerived(std::string input)  : data(input)  {
      }
      void print() override { std::cout<< "Printing String Value " << data <<"\n"; }

      ~StringDerived() { 
	  std:: cout << "StringDerived - Destrutor \n" ;
      }     
};

int main() {

    std::vector<std::unique_ptr<Base>> obj(2);
    
    obj[0] = std::make_unique<IntDerived>(10);
    obj[1] = std::make_unique<StringDerived>("Sathish");

    for(const auto & i : obj)
    {
        i->print();
    }
}

