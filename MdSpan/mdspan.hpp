#ifndef MD_SPAN_HPP
#define MD_SPAN_HPP

#include <cstddef>
#include <span>
#include <stdexcept>
#include <iterator>

namespace myspan {

template <typename T, std::size_t Extent = std::dynamic_extent>
class span {
public:
    using element_type = T;
    using value_type = std::remove_cv_t<T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    constexpr span() noexcept : data_(nullptr), size_(0) {}

    constexpr span(T* ptr, size_type size) : data_(ptr), size_(size) {}

    template <size_type N>
    constexpr span(T (&arr)[N]) noexcept : data_(arr), size_(N) {}

    constexpr T* data() const noexcept {
        return data_;
    }

    constexpr size_type size() const noexcept {
        return size_;
    }

    constexpr T& operator[](size_type index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds in span");
        }
        return data_[index];
    }

    constexpr T* begin() const noexcept {
        return data_;
    }

    constexpr T* end() const noexcept {
        return data_ + size_;
    }

    constexpr const T* cbegin() const noexcept {
        return data_;
    }

    constexpr const T* cend() const noexcept {
        return data_ + size_;
    }

    constexpr T& front() const {
        if (size_ == 0) {
            throw std::out_of_range("Calling front() on an empty span");
        }
        return *data_;
    }

    constexpr T& back() const {
        if (size_ == 0) {
            throw std::out_of_range("Calling back() on an empty span");
        }
        return *(data_ + size_ - 1);
    }

    constexpr T& at(size_type index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds in span");
        }
        return data_[index];
    }

    constexpr std::reverse_iterator<T*> rbegin() const noexcept {
        return std::reverse_iterator<T*>(end());
    }

    constexpr std::reverse_iterator<T*> rend() const noexcept {
        return std::reverse_iterator<T*>(begin());
    }

    constexpr std::reverse_iterator<const T*> crbegin() const noexcept {
        return std::reverse_iterator<const T*>(cend());
    }

    constexpr std::reverse_iterator<const T*> crend() const noexcept {
        return std::reverse_iterator<const T*>(cbegin());
    }

    constexpr bool empty() const noexcept {
        return size_ == 0;
    }

private:
    T* data_;
    size_type size_;
};

template <typename T, std::size_t Rows, std::size_t Cols>
class md_span {
public:
    using element_type = T;
    using value_type = std::remove_cv_t<T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    constexpr md_span(T* ptr) : data_(ptr), size_(Rows * Cols) {}

    constexpr span<T> operator[](size_type index) const {
        if (index >= Rows) {
            throw std::out_of_range("Index out of bounds in md_span");
        }
        return span<T>(data_ + index * Cols, Cols);
    }

    constexpr T* data() const noexcept {
        return data_;
    }

    constexpr size_type size() const noexcept {
        return size_;
    }

private:
    T* data_;
    size_type size_;
};

} // namespace myspan

#endif // MD_SPAN_HPP
