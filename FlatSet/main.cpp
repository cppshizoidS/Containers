#include <deque>
#include <iostream>
#include "flat_set.hpp"

int main() {
    // Example 1: Using the default constructor
    cppshizoid::tools::flat_set<int> set1;
    set1.insert(3);
    set1.insert(1);
    set1.insert(4);
    set1.insert(1);  // Won't be inserted, as it's a set (no duplicates)

    // using a custom comparator
    cppshizoid::tools::flat_set<std::string, std::greater<>> set2{"apple", "banana", "orange"};

    // using initializer list
    cppshizoid::tools::flat_set<double> set3{3.14, 1.1, 2.2, 3.14};  // Duplicates are not allowed

    // using iterators
    std::vector<char> charVector{'z', 'a', 'd', 'f', 'z', 'a'};
    cppshizoid::tools::flat_set<char> set4(charVector.begin(), charVector.end());

    // using custom container type (e.g., std::deque)
    cppshizoid::tools::flat_set<int, std::less<>, std::deque<int>> set5{5, 2, 8, 2, 1};

    // iterating through the set
    std::cout << "Set 5 elements: ";
    for (const auto& element : set5) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
