#include <iostream>
#include <vector>
#include <cstddef> // Required for std::byte
#include <utility> // Required for std::to_underlying (C++23)

int main() {

    std::vector v = {std::byte{0b0001}, std::byte{0b0001}, std::byte{0b0001}};
    std::vector b = {1, 0, 1};
    
    
    std::byte mask{0b0001};

    for (auto &&ref : v) {
        ref &= mask; 
        std::cout << "Result: " << std::to_underlying(ref) << "\n";
    }
    for (auto &ref : v) {
        ref &= mask; 
        std::cout << "Result: " << std::to_underlying(ref) << "\n";
    }

    for (auto &&ref : b) {
        std::cout << "Result: " << (ref) << "\n";
    }
    for (auto &ref : b) {
        std::cout << "Result: " << (ref) << "\n";
    }
}
