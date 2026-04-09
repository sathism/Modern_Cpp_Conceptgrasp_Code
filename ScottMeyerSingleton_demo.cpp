#include <iostream>

class Singleton {
   public :
       static Singleton& getInstance() {
             static Singleton obj;
             return obj;
       }
       Singleton(const Singleton &ref) = delete ;
       Singleton& operator=(const Singleton &ref) = delete;
       Singleton(Singleton &&ref) = delete;
       Singleton& operator=(Singleton &&ref) = delete;
       Singleton() { std::cout << "Inside Singleton Constructor " << "\n";}
};

int main() {
   Singleton ins;
   return 0;
}
