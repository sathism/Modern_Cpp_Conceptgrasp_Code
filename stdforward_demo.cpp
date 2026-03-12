#include <utility>
#include <iostream>

void process(const std::string &s)
{
   std::cout << "Inside LValue process \n";
   std::cout << s << "\n";
}

void process(std::string&& s)
{
   std::cout << "Inside RValue process \n";
   std::cout << s << "\n";
}

template <typename T>
void log(T && arg)
{
   process(std::forward<T>(arg));
}

int main()
{
     std::string s("Henry");
     log(s);
     log(std::string("Mark"));   
}
