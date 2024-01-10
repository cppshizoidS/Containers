#ifndef MY_ARRAY_HPP
#define MY_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <algorithm>

namespace my_array_namespace {

template <typename T, std::size_t N>
class my_array {
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    constexpr my_array() noexcept = default;

    // Template constructor for variadic initialization
    template <typename... Args>
    constexpr my_array(Args&&... args) : data{std::forward<Args>(args)...} {
        static_assert(sizeof...(Args) == N, "Incorrect number of arguments");
    }

    constexpr reference operator[](size_type index) {
        return data[index];
    }

    constexpr const_reference operator[](size_type index) const {
        return data[index];
    }

    constexpr iterator begin() noexcept {
        return data;
    }

    constexpr const_iterator begin() const noexcept {
        return data;
    }

    constexpr iterator end() noexcept {
        return data + N;
    }

    constexpr const_iterator end() const noexcept {
        return data + N;
    }

    constexpr size_type size() const noexcept {
        return N;
    }

    constexpr bool empty() const noexcept {
        return N == 0;
    }

    constexpr void fill(const T& value) noexcept {
        std::fill(data, data + N, value);
    }
    
    constexpr void swap(my_array& other) noexcept {
        std::swap_ranges(data, data + N, other.data);
    }

private:
    value_type data[N] = {};  // Default-initialize elements
};

// Comparison operators
template <typename T, std::size_t N>
constexpr bool operator==(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, std::size_t N>
constexpr bool operator!=(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
    return !(lhs == rhs);
}

template <typename T, std::size_t N>
constexpr bool operator<(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, std::size_t N>
constexpr bool operator>(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
    return rhs < lhs;
}

template <typename T, std::size_t N>
constexpr bool operator<=(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
    return !(rhs < lhs);
}

template <typename T, std::size_t N>
constexpr bool operator>=(const my_array<T, N>& lhs, const my_array<T, N>& rhs) {
    return !(lhs < rhs);
}

}  // namespace my_array_namespace

#endif // MY_ARRAY_HPP
