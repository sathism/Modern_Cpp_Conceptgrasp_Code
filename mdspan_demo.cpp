#include <iostream>
#include <mdspan>

int main()
{
   std::vector data = {1,2,3,4,5,6};
   std::mdspan arr1(data, 3, 2 );
   std::mdspan<int, std::extents<std::size_t 3,3>>  arr2(data);
   std::coutt << "Element at [0,1] " << arr1[0,1] << std::endl;
   return 0;
}
