#ifndef MY_MIN_HPP
#define MY_MIN_HPP

template <typename T>
const T& my_min(const T& a, const T& b) {
    return (b < a) ? b : a;
}
#endif