

#include <iostream>
#include <vector>
#include <ranges>

/*Defintion - 
  In modern C++, range adaptors are helper objects used to create Views—lightweight, 
  non-owning wrappers that transform or filter data lazily. 
  They are typically found in the std::views namespace
*/

/* 
            C++ 20 Range Adaptors
            ---------------------
   all: Returns a view including all elements of a range.
   filter: Keeps only elements matching a predicate.
   transform: Applies a function to each element.
   take / take_while: Takes the first elements or until a condition is false.
   drop / drop_while: Skips the first elements or until a condition is false.
   join: Flattens a range of ranges into a single range.
   split / lazy_split: Splits a range into subranges based on a delimiter.
   reverse: Iterates over a bidirectional range in reverse.  
   elements<N>: Extracts the -th element from a range of tuple-like values.
   keys: Alias for elements<0> (first element of pairs/tuples).
   values: Alias for elements<1> (second element of pairs/tuples).
   common: Converts a view into a common_range where iterator and sentinel types match.
   counted: Creates a subrange from an iterator and a count. 

           C++23 Range Adaptors 
           --------------------
    C++23 introduced more advanced data-shaping and utility adaptors. 

    zip: Combines multiple ranges element-wise into tuples.
    zip_transform: Zips ranges and immediately applies a transformation function.
    enumerate: Yields tuples of (index, value) for each element.
    adjacent<N>: Provides a sliding window of adjacent elements as tuples.
    adjacent_transform<N>: Applies a function to each -element window.
    join_with: Flattens a range of ranges using a delimiter between elements.
    chunk: Splits a range into fixed-size chunks.
    chunk_by: Splits a range into chunks where adjacent elements satisfy a predicate.
    slide: Provides a sliding window of size as subranges.
    stride: Samples every -th element from a range.
    cartesian_product: Produces all possible combinations from multiple ranges.
    as_rvalue: Casts each element to an rvalue (useful for moving data).
    as_const: Provides a read-only (const) view of the underlying range. 

          C++26 Range Adaptors (Upcoming)
          ------------------------------
    concat: Concatenates multiple views of the same value type into one continuous range. 

          Range Factories
          ---------------
    While not "adaptors" (they don't take a range as input), these factories are often used at the start of pipelines: 

    empty: Creates a view with no elements.
    single: Creates a view containing exactly one element.
    iota: Generates a sequence of increasing values.
    repeat: (C++23) Generates an infinite sequence by repeatedly producing the same value.
    istream: Creates a view over elements obtained from an input stream. 
*/

int main()
{
   std::vector<int> vec;
   /* Interesting vector reserver and size  */
    
   vec.reserve(10);

   for (auto i : std::views::iota(0,10))
   {
       vec.emplace_back( i%2 == 0 ? i * 20 : i * 11);
   }

   //1. std::views::all
   auto res = vec | std::views::all;
   for(const auto &r : res)
      std::cout << r << " ";
   std::cout << std::endl;
 
   //2. std::views::filter
   auto fil_res = vec | std::views::filter( [](int n) {
                                               return n%2 == 0;
                          });
   for(const auto &r :fil_res)
      std::cout << r << " ";
   std::cout << std::endl;

  //Practise other range adaptor usage on your own.
    
}
