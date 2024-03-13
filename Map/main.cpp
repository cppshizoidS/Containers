#include <iostream>
#include "map.hpp" // Include your custom map header

int main() {
    cppshizoid::tools::map::Map<std::string, int> myMap;

    myMap.insert({"apple", 5});
    myMap.insert({"banana", 7});
    myMap.insert({"orange", 3});

    std::cout << "Size of the map: " << myMap.size() << std::endl;

    std::cout << "Contents of the map:" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << pair.first << " => " << pair.second << std::endl;
    }

    std::cout << "Value associated with 'banana': " << myMap.at("banana") << std::endl;

    myMap.erase("banana");

    std::cout << "Size of the map after erasing: " << myMap.size() << std::endl;

    std::cout << "Is the map empty? " << (myMap.empty() ? "Yes" : "No") << std::endl;

    return 0;
}
