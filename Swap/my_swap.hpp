#ifndef MY_SWAP_HPP
#define MY_SWAP_HPP
#include "my_move.hpp"

template<typename T>
void my_swap(T& a, T& b) {
    T temp = my_move(a);
    a = my_move(b);
    b = my_move(temp);
}
#endif