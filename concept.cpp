#include <concepts>
#include <ranges>
#include <iterator>
#include <deque>
#include <vector>
#include <list>
#include <iostream>

/* SFINAE stands for Substitution Failure Is Not An Error. 
It is a core principle in C++ template logic that dictates how the compiler handles errors during the template specialization process. 
The Core Definition
When a compiler encounters a function template call, it tries to "substitute" the actual types (like int or std::string) 
for the template parameters (like T). If this substitution results in an invalid type or expression in the template's signature, 
the compiler does not stop with a compilation error. 
Instead, it simply:
Discard that particular template specialization from the set of potential candidates (the "overload set").
Continues searching for other valid overloads that might fit the call. 
*/

/* C++ 17 refined SFINAE with enable_if, decltype but C++ 20 has come up interesting 
 * thing called concept to refine SFINAE
*/

template <typename T>
/*
  1. Named conept
  concept is the rule name
  requires is the actual rule to be applied
  at compile time to check the template deductions is proper or not
*/
concept INTEGRAL = requires(T) { 
                     requires std::integral<T> || std::signed_integral<T>;
                  };
template<INTEGRAL T>

void process(T ref)
{
   std::cout << ref << std::endl;
}

/* Usage 2. Ad-hoc concept
 * directly use the rule on a function
 */
template <typename T>
void process1( T ref) requires (std::integral<T>)
{
  std::cout << ref << std::endl;
}

/* Usage 3. Double requires
 * first requires says a constraint is coming
 * second requires check whether the code is valid
 */
template <typename T>
void process3(T &ref) requires requires{  ref.move(); }
{
    std::cout << ref << std::endl;
}

/* Usage4. Nested Concept
 * it does deep validation
 */
template <typename T>
concept CHECK = requires (T){
    requires std::copyable<T>;
   
};
template <CHECK T>
void process4(T &ref)
{
   std::cout << ref << std::endl;
}

/*
           Listing all possible concept rules 
           ----------------------------------

    // 1. Lifecycle Rules 
    std::default_initializable<T> && 
    std::regular<T> &&         
    std::semiregular<T> &&         
    std::destructible<T> &&          
    std::constructible_from<T, U> &&          
    std::move_constructible<T> &&          
    std::copy_constructible<T> &&          
    std::swappable<T> &&
    std::copyable<T> &&

    // 2. Comparison Rules 
    std::totally_ordered<T> &&
    std::threeway_comparable<T> ||
    std::equality_comparable<T> ||

    // 3. Core Language Rules
     std::integral<T> || 
     std::signed_integral<T> || 
     std::unsigned_integral<T> || 
     std::floating_point<T>  ||
     std::same_as<T,U> ||
     std::derived_from<T,U> ||
     std::convertible_to<T,U> ||
     std::common_with<T,U> ||
     std::assignable_from<T,U>

    // 4. Memory/Hardware Rules
    (sizeof(T) <= 64)  ||

    //5.Iterator & Range concepts
    std::std::input_iterator<T> ||
    std::output_iterator<T> ||
    std::forward_iterator<T> ||
    std::bidirectional_iterator<T> ||
    std::random_access_iterator<T> ||
    std::contiguous_iterator<T> ||
    std::range<T> ||

    //6. Callable Concepts
    std::invocable<T, Args...>
    std::predicate<T, Args...>
    std::relation<T, F, U> ;
*/

/* Custom concept */
template <typename T>
concept SortableContainer = std::ranges::random_access_range<T> && 
                            std::totally_ordered<std::ranges::range_value_t<T>>;

void my_sort(SortableContainer auto& container) {
    // This is only allowed for random access ranges like std::vector
}

/* subsumption rules to pick overlaod */
// General version
template <std::random_access_iterator I>
void advanced_algo(I it) { /* Logic for random access (e.g., deque) */ }

// More specific version
template <std::contiguous_iterator I>
void advanced_algo(I it) { /* Optimized logic for back-to-back memory (e.g., vector) */ }

int main()
{
    process(1);
    process(-1);

    std::vector<int> v = {3, 1, 2};
    my_sort(v); // OK: vector is random_access and int is totally_ordered
    std::list<int> l = {3, 1, 2};
    my_sort(l); // COMPILE ERROR: list is NOT random_access

    std::deque<int> d = {1, 2, 3};
    advanced_algo(d.begin()); // Picks the random_access version

    std::vector<int> v1 = {1, 2, 3};
    advanced_algo(v.begin()); // Picks the contiguous version (more specific)
}

