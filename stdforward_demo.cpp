#include <utility>
#include <iostream>

/* 
   Perfect Forwarding Concept :
   -----------------------------
   In C++, perfect forwarding is a technique that allows a function template to receive arguments and 
pass them to another function while preserving their original value category (lvalue vs. rvalue) and cv-qualifiers (const/volatile). 
Without perfect forwarding, an argument passed as an rvalue (temporary) into a wrapper function
becomes an lvalue inside that function because it has a name, which could inadvertently trigger a copy instead of an efficient move. 

How to Achieve Perfect Forwarding
---------------------------------
Perfect forwarding is implemented using two key C++ features: 
Forwarding References (Universal References &&): A template parameter declared as 
 where is deduced. It can bind to both lvalues and rvalues.
std::forward: A conditional cast that restores the original value category of the argument before passing it to the next function. 
Core Mechanism
The mechanism relies on Reference Collapsing rules, which dictate how "references to references" are resolved during template instantiation: 
*/

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
   //Perfect forwarding forward the passed argument as such without stripping anything
   process(std::forward<T>(arg));
}
   
int main()
{
     std::string s("Henry");
     log(s);  //Passes rvalue
     log(std::string("Mark"));   //Generates Pure rvalue 
}
