#include <utility>
#include <iostream>

enum class A : unsigned
{
  HIGH = 20,
  LOW = 40,
  MID = 40
};


int main()
{
    using enum A;
    std::cout << std::to_underlying(HIGH);
    std::cout << "\n" << "\n";

}
