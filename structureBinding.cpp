#include <map>
#include <iostream>
#include <format>
#include <iomanip>

/* What is a Structure Binding ?
   ----------------------------
   Introduced in C++17, 
   structured bindings allow you to "unpack" or "destructure" an object—like a tuple, 
   pair, struct, or array—into multiple individual variables in a single statement. 
   It makes code cleaner by replacing manual access (like .first, .second, or std::get<0>) 
   with meaningful variable names.
   
*/

int main()
{
   std::map<int, std::string>  studentRollNoName = {{1,"Henry"}, {2,"Atlas"}, {3, "Benjamin"}};
   std::cout <<  std::format("|{:^20}|\n", "Student Details" );
   std::cout << std::format("|{:-^20}|\n", "---");

   for( const auto &[rollNo, Name] : studentRollNoName)
        std::cout << "rollNo = " << std::setw(3) << std::setfill('0')  
                  << rollNo << "|" << "Name = " << Name << std::endl;
   std::setfill(' ');
   return 0;
}


