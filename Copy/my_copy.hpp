#ifndef MY_COPY_HPP
#define MY_COPY_HPP

template <typename InputIterator, typename OutputIterator>
OutputIterator my_copy(InputIterator first, InputIterator last, OutputIterator result) {
    while (first != last) {
        *result = *first;
        ++result;
        ++first;
    }
    return result;
}
#endif