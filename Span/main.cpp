#include <iostream>
#include "span.hpp"

int main() {
    // Example 1: Using span with a dynamic array
    int dynamicArray[] = {1, 2, 3, 4, 5};
    myspan::span<int> dynamicSpan(dynamicArray, 5);

    int atSpan = dynamicSpan.at(4);
    std::cout << "4 index of span contains: " << atSpan << "\n";

    std::cout << "Forward Iteration (Dynamic Array): ";
    for (const auto& value : dynamicSpan) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "Reverse Iteration (Dynamic Array): ";
    for (auto it = dynamicSpan.rbegin(); it != dynamicSpan.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Example 2: Using span with a static array
    int staticArray[3] = {6, 7, 8};
    myspan::span<int, 3> staticSpan(staticArray);

    std::cout << "Forward Iteration (Static Array): ";
    for (const auto& value : staticSpan) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "Front element: " << staticSpan.front() << "\n";
    std::cout << "Back element: " << staticSpan.back() << "\n";

    std::cout << "Reverse Iteration (Static Array): ";
    for (auto it = staticSpan.rbegin(); it != staticSpan.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Example 3: Using span with an empty array
    myspan::span<int> emptySpan;

    std::cout << "Is Empty Array Empty? " << (emptySpan.empty() ? "Yes" : "No") << "\n";

    try {
        // Accessing an out-of-bounds index
        std::cout << "Accessing out-of-bounds index: " << emptySpan[5] << "\n";
    } catch (const std::out_of_range& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }

    //  Using span with char data
    char charArray[] = {'H', 'e', 'l', 'l', 'o'};
    myspan::span<char> charSpan(charArray, 5);

    std::cout << "Front element: " << charSpan.front() << "\n";
    std::cout << "Back element: " << charSpan.back() << "\n";

    std::cout << "Forward Iteration: ";
    for (const auto& value : charSpan) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "Reverse Iteration: ";
    for (auto it = charSpan.rbegin(); it != charSpan.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    //  Using span with const char data
    const char constCharArray[] = {'W', 'o', 'r', 'l', 'd'};
    myspan::span<const char> constCharSpan(constCharArray, 5);

    std::cout << "Front element: " << constCharSpan.front() << "\n";
    std::cout << "Back element: " << constCharSpan.back() << "\n";

    std::cout << "Forward Iteration: ";
    for (const auto& value : constCharSpan) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    //  Using span with an empty char array
    myspan::span<char> emptyCharSpan;

    std::cout << "Is Empty Char Array Empty? " << (emptyCharSpan.empty() ? "Yes" : "No") << "\n";

    try {
        // Accessing an out-of-bounds index
        std::cout << "Accessing out-of-bounds index: " << emptyCharSpan[5] << "\n";
    } catch (const std::out_of_range& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }


    return 0;
}
