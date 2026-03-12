#include <map>
#include <iostream>
#include <format>
#include <iomanip>

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


