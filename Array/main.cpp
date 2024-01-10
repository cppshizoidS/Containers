#include <iostream>
#include "my_array.hpp"

int main() {
    // Example Creating an array of integers
    my_array_namespace::my_array<int, 5> arr1 = {1, 2, 3, 4, 5};
    std::cout << "arr1: ";
    for (const auto& element : arr1) {
        std::cout << element << " ";
    }
    std::cout << "Size of arr1: " << arr1.size();
    std::cout << std::endl;

    // Example  Creating an array of doubles
    my_array_namespace::my_array<double, 5> arrd = {1.45, 2.34, 3.234, 4.234, 5.21};
    std::cout << "arrd: ";
    for (const auto& element : arrd) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Example Using comparison operators
    my_array_namespace::my_array<int, 5> arr2 = {1, 2, 3, 4, 5};
     // Print arr2
    std::cout << "arr2: ";
    for (const auto& element : arr2) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    my_array_namespace::my_array<int, 5> arr3 = {1, 2, 3, 4, 6};
    std::cout << "arr3: ";
    for (const auto& element : arr3) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    if (arr1 == arr2) {
        std::cout << "arr1 is equal to arr2" << std::endl;
    } else {
        std::cout << "arr1 is not equal to arr2" << std::endl;
    }

    if (arr1 < arr3) {
        std::cout << "arr1 is less than arr3" << std::endl;
    } else {
        std::cout << "arr1 is not less than arr3" << std::endl;
    }

    // Example Modifying elements and using other member functions
    my_array_namespace::my_array<std::string, 3> strArray = {"apple", "orange", "banana"};
    std::cout << "Original strArray: ";
    for (const auto& element : strArray) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Fill the array with a new value
    strArray.fill("grape");
    std::cout << "After fill: ";
    for (const auto& element : strArray) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Swap the arrays using the constexpr swap function
    my_array_namespace::my_array<int, 3> arr4 = {1, 3 ,4};
    my_array_namespace::my_array<int, 3> arr5 = {3, 2, 6};
    arr4.swap(arr5);

    std::cout << "\nArrays after swapping:" << std::endl;
    std::cout << "Array 1: ";
    for (const auto& element : arr4) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;

    std::cout << "Array 2: ";
    for (const auto& element : arr5) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;


    return 0;
}
