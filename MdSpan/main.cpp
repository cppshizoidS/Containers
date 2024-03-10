#include "mdspan.hpp"
#include <iostream>

int main() {
    // Example usage of md_span
    constexpr std::size_t rows = 3;
    constexpr std::size_t cols = 4;

    int matrixData[rows][cols] = {{1, 2, 3, 4},
                                  {5, 6, 7, 8},
                                  {9, 10, 11, 12}};

    myspan::md_span<int, rows, cols> matrix(matrixData[0]);

    // Accessing elements using md_span
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
