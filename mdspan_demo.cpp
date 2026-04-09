#include <iostream>
#include <mdspan>

<<<<<<< HEAD
/*  In C++23, std::mdspan is a multidimensional array view that allows you to interact with a flat, 
    contiguous block of memory (like a std::vector or a raw pointer) as if it were a multi-dimensional array. 

    Think of it as a more powerful, multi-dimensional version of std::span. It is non-owning, meaning it
    doesn't manage the memory itself; it just provides a structured "window" into existing data. 

    Key Features
    ============
     Decoupled Layout: You can switch between row-major (C-style), column-major (Fortran-style), or custom strides just by changing a template parameter.
     Flexible Dimensions: It supports both static extents (dimensions known at compile-time for better optimization) and dynamic extents (dimensions determined at runtime).
     Zero Overhead: It is designed to be a "zero-overhead abstraction," meaning the compiler can optimize it as effectively as manual index calculations (e.g., data[i * cols + j]).
     New Syntax: It takes advantage of the C++23 multidimensional subscript operator, allowing you to access elements using the intuitive matrix[i, j] syntax. 

*/
#include <memory>
#include <mdspan>
#include <vector>
#include <array>

int main() {
   
   std::vector data = {1,2,3,4,5,6};
   
   //Storage of 100 elements reserved and initilaized it with zero
   std::vector data1(100,0);
   
   //Declaration - Usage-1 - static extents - Assume ROW -2, COL -3 but memory is still contigous
   std::mdspan arr1(data.data(), 3, 2 );
   
   //Declaration - Usage-2, static extents - Assume ROW -2, COL -3 but memory is still contigous
   std::mdspan<int, std::extents<std::size_t 3,3>>  arr2(data);

   /*   Declaration - Usage-3 ROW is Fixed, but COLUMN Is dynamic { Mixed Stuff}, 
        std::dynamic_extent is a place holder to receive that particular extent at run time
   */
   using ext_type = std::extents<std::size_t 3, std::dynamic_extent> ;
   std::mdspan mat(data, ext_type{3});

   //Custom Layouts and inter-operability
   /*   Layout policies determine how an index (i, j) maps to the 1D index in memory. 
        This is crucial for performance (cache locality) and working with other languages. 
        std::layout_right (Default): Row-major (C/C++ style). Last index is contiguous.
        std::layout_left: Column-major (Fortran/MATLAB style). First index is contiguous.
        std::layout_stride: Custom steps between elements. Perfect for viewing a "sub-window" or "slice" of a larger matrix. 
        std::dextents<size_t, 2> tells the rank - Here rank is 2 meaning 3D array
   */
   
   /*    std::dextents<std::size_t, 2> - it's a 2D array and offset it based on std::layout_left
         with std::layout_left policy from the vector data the 
         Formed Matrix would be [ 1 3 5]
                                [ 2 4 6]
    */
   std::mdspan<int, std::dextents<size_t, 2>, std::layout_left> mat1_left_layout (data.data(), 2, 3);
   
    /*    std::dextents<size_t, 2> - It's a 2D array and offset it based on std::layout_left
          with std::layout_right policy from the vector data the 
          Formed Matrix would be [ 1 2 3]
                                 [ 4 5 6]
    */   
    std::mdspan<int, std::dextents<size_t, 2>, std::layout_right> mat1_right_layout (data.data(), 2, 3);

    /* Use Case: Slicing a Matrix
          The most common use for layout_stride is creating a view of a sub-section of a larger matrix.
          For example, if you have a matrix and want to view just the corner, your "steps" between rows will
          still be 10 (the width of the original matrix), even though your view is only 3 wide.
    */
    
    // We want a 3x3 view, but rows are 10 elements apart in memory
    std::dextents<size_t,2> shape{3, 3};
    
    std::array<size_t, 2> strides{10, 1}; // Jump 10 for new row, 1 for new col
    
    // Create the mapping
    std::layout_stride::mapping mapping{shape, strides};
    
    // Create the mdspan using the mapping
    auto sub_view = std::mdspan(data.data(), mapping);

    // data_handle(): Get the raw pointer back
    int* raw_ptr = sub_view.data_handle();

    sub_view[0, 2] = 42; 
    std::cout << "Value at [0, 2]: " << sub_view[0, 2] << "\n";
    
    std::cout << "Rank (Dimensions): " << sub_view.rank() << "\n";      
    std::cout << "Total Size: " << sub_view.size() << "\n";            
    
    // Check specific dimensions
    std::cout << "Depth (Extent 0): " << sub_view.extent(0) << "\n";    
    std::cout << "Rows  (Extent 1): " << sub_view.extent(1) << "\n";    
   
    // --- LAYOUT/STRIDE METHODS ---
    std::cout << "Stride for Rows: " << sub_vivew.mapping().stride(1) << "\n"; 
  
=======
/* What is mdspan
    Introduced in C++23, std::mdspan is a lightweight, non-owning "view" that allows you to treat a flat, 
    contiguous piece of memory (like a std::vector or raw array) as a multidimensional array. It solves the 
    long-standing problem of managing matrices and tensors without the performance overhead or fragmentation 
    of traditional "pointer-to-pointer" (int**) approaches.
*/
int main()
{
   std::vector data = {1,2,3,4,5,6};
   /* Usage 1 */
   std::mdspan arr1(data, 3, 2 );

   /* Usage 2 - Static Extents */
   std::mdspan<int, std::extents<std::size_t 3,3>>  arr2(data);

   std::cout << "Element at [0,1] " << arr1[0,1] << std::endl;
>>>>>>> b887430 (Modified Files)
   return 0;
}
