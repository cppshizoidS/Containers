#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <algorithm>

namespace my_vector {

template <typename T>
class my_vector_reverse_iterator {
public:
  using pointer = T *;
  using reference = T &;

  constexpr explicit my_vector_reverse_iterator(pointer ptr) noexcept
      : current(ptr) {}

  // dereference operator
  constexpr reference operator*() const noexcept { return *current; }

  // increment operator
  constexpr my_vector_reverse_iterator &operator++() noexcept {
    --current;
    return *this;
  }

  // decrement operator
  constexpr my_vector_reverse_iterator &operator--() noexcept {
    ++current;
    return *this;
  }

  // equality comparison
  constexpr bool operator==(const my_vector_reverse_iterator &other) const noexcept {
    return current == other.current;
  }

  // inequality comparison
  constexpr bool operator!=(const my_vector_reverse_iterator &other) const noexcept {
    return current != other.current;
  }

private:
  pointer current;
};

template <typename T>
class my_vector {
public:
  using size_type = std::size_t;
  using iterator = T *;

  using reverse_iterator = my_vector_reverse_iterator<T>;

  // reverse iterator pointing to the last element
  [[nodiscard]] constexpr reverse_iterator rbegin() const noexcept {
    return reverse_iterator(m_data + m_size - 1);
  }

  // reverse iterator pointing to position before the first element
  [[nodiscard]] constexpr reverse_iterator rend() const noexcept {
    return reverse_iterator(m_data - 1); // Correction: subtract 1
  }

  constexpr my_vector() noexcept : m_data(nullptr), m_size(0), m_capacity(0) {}

  constexpr explicit my_vector(size_type count, const T &value = T()) noexcept
      : m_data(new T[count]), m_size(count), m_capacity(count) {
    std::fill(m_data, m_data + count, value);
  }

  constexpr my_vector(const my_vector &other) noexcept
      : m_data(new T[other.m_capacity]), m_size(other.m_size),
        m_capacity(other.m_capacity) {
    std::copy(other.m_data, other.m_data + other.m_size, m_data);
  }

  constexpr my_vector &operator=(const my_vector &other) noexcept {
    if (this != &other) {
      delete[] m_data;
      m_data = new T[other.m_capacity];
      std::copy(other.m_data, other.m_data + other.m_size, m_data);
      m_size = other.m_size;
      m_capacity = other.m_capacity;
    }
    return *this;
  }

  [[nodiscard]] constexpr size_type size() const noexcept { return m_size; }

  [[nodiscard]] constexpr size_type capacity() const noexcept {
    return m_capacity;
  }

  [[nodiscard]] constexpr bool empty() const noexcept { return m_size == 0; }

  constexpr void push_back(const T &value) {
    if (m_size == m_capacity) {
      reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    m_data[m_size++] = value;
  }

  constexpr void pop_back() {
    if (m_size > 0) {
      --m_size;
    }
  }

 constexpr iterator begin() noexcept {
    return m_data;
  }

  constexpr const iterator cbegin() const noexcept {
    return m_data;
  }

  constexpr iterator end() noexcept {
    return m_data + m_size;
  }

  constexpr const iterator cend() const noexcept {
    return m_data + m_size;
  }

  [[nodiscard]] constexpr T &operator[](size_type pos) noexcept {
    return m_data[pos];
  }

  [[nodiscard]] constexpr const T &operator[](size_type pos) const noexcept {
    return m_data[pos];
  }

  [[nodiscard]] constexpr T &front() noexcept { return m_data[0]; }

  [[nodiscard]] constexpr const T &front() const noexcept { return m_data[0]; }

  [[nodiscard]] constexpr T &back() noexcept { return m_data[m_size - 1]; }

  [[nodiscard]] constexpr const T &back() const noexcept {
    return m_data[m_size - 1];
  }
//
  constexpr void clear() noexcept { m_size = 0; }

  constexpr void resize(size_type count, const T &value = T()) {
    if (count < m_size) {
      m_size = count;
    } else if (count > m_size) {
      reserve(count);
      std::fill(m_data + m_size, m_data + count, value);
      m_size = count;
    }
  }

  constexpr void reserve(size_type new_capacity) {
    if (new_capacity > m_capacity) {
      T *new_data = new T[new_capacity];
      std::copy(m_data, m_data + m_size, new_data);
      delete[] m_data;
      m_data = new_data;
      m_capacity = new_capacity;
    }
  }

  ~my_vector() { delete[] m_data; }

private:
  T *m_data;
  size_type m_size;
  size_type m_capacity;
};

} // namespace my_vector

#endif // MY_VECTOR_HPP
