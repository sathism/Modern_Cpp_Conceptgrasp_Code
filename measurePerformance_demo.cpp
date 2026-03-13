#include <iostream>
#include <chrono>
#include <numeric>
#include <vector>

#define SIZE 10
void calculate(int value)
{
   std::vector<int> vec(SIZE);
   std::iota(vec.rbegin(), vec.rend(), value);
   for (const auto &ref : vec)
   {
      for(auto &ref1 : vec)
          ref1 *= 20;
   }
  
}
int main()
{
   using namespace std::chrono_literals;
   auto start = std::chrono::high_resolution_clock::now();
   //call function
   calculate(1000);

   //difference in nano seconds
   auto diff = std::chrono::high_resolution_clock::now() - start;

   //convert nano seconds to whichever format we want 
   std::cout << "Function Execution time in ms = " 
             << std::chrono::duration<double, std::milli>(diff).count()
             << "ms"<< std::endl; 
   std::cout << "Function Execution time in ms = " 
             << std::chrono::duration<double, std::nano>(diff).count()
             << "ns"<< std::endl; 
   return 0;
}
