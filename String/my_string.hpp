// Created by cppshizoid on 1/9/24.

#ifndef MY_STRING_HPP
#define MY_STRING_HPP

#include <algorithm>
#include <cctype>
#include <cstring>
#include <istream>
#include <stdexcept>
#include <utility>

namespace my_string {

template <typename T>
concept CharacterType = std::same_as<T, char> || std::same_as<T, wchar_t> ||
                        std::same_as<T, char16_t> || std::same_as<T, char32_t>;

template <typename CharT> class my_string_reverse_iterator {
public:
  using pointer = CharT *;
  using reference = CharT &;

  constexpr explicit my_string_reverse_iterator(pointer ptr) noexcept
      : current(ptr) {}

  // dereference operator
  constexpr reference operator*() const noexcept { return *current; }

  // increment operator
  constexpr my_string_reverse_iterator &operator++() noexcept {
    --current;
    return *this;
  }
  // decrement operator
  constexpr my_string_reverse_iterator &operator--() noexcept {
    ++current;
    return *this;
  }
  // equality comparison
  constexpr bool
  operator==(const my_string_reverse_iterator &other) const noexcept {
    return current == other.current;
  }
  // inequality comparison
  constexpr bool
  operator!=(const my_string_reverse_iterator &other) const noexcept {
    return current != other.current;
  }

private:
  pointer current;
};

template <CharacterType CharT> class my_string {
public:
  using size_type = std::size_t;
  using iterator = CharT *;

  using reverse_iterator = my_string_reverse_iterator<CharT>;

  // reverse iterator pointing to the last character
  [[nodiscard]] constexpr reverse_iterator rbegin() const noexcept {
    return reverse_iterator(m_data + m_length - 1);
  }

  // reverse iterator pointing to position before the first character
  [[nodiscard]] constexpr reverse_iterator rend() const noexcept {
    return reverse_iterator(m_data - 1);
  }

  constexpr my_string() noexcept : m_data(nullptr), m_length(0) {}

  constexpr explicit my_string(const CharT *str) noexcept
      : m_data(new CharT[std::char_traits<CharT>::length(str) + 1]),
        m_length(std::char_traits<CharT>::length(str)) {
    std::copy(str, str + m_length, m_data);
    m_data[m_length] = '\0';
  }

  constexpr my_string(const CharT *str, size_type len) noexcept
      : m_data(new CharT[len + 1]), m_length(len) {
    std::copy(str, str + len, m_data);
    m_data[len] = '\0';
  }

  template <std::convertible_to<const CharT *> S>
  constexpr explicit my_string(const S &str) noexcept
      : m_data(new CharT[str.size() + 1]), m_length(str.size()) {
    std::copy(str.data(), str.data() + m_length, m_data);
    m_data[m_length] = '\0';
  }

  [[nodiscard]] constexpr const CharT *c_str() const noexcept { return m_data; }

  [[nodiscard]] constexpr size_type size() const noexcept { return m_length; }

  [[nodiscard]] constexpr bool empty() const noexcept { return m_length == 0; }

  constexpr my_string operator+(const CharT &ch) const noexcept {
    my_string result(*this);
    result = result + ch;
    return result;
  }

  constexpr CharT operator[](size_type pos) const { return m_data[pos]; }

  [[nodiscard]] constexpr my_string substr(size_type pos,
                                           size_type len = npos) const {
    if (pos > m_length)
      throw std::out_of_range("Out of range");
    return my_string(m_data + pos, std::min(len, m_length - pos));
  }

  [[nodiscard]] constexpr size_type find(const my_string &str,
                                         size_type pos = 0) const noexcept {
    if (pos > m_length || str.size() > m_length - pos)
      return npos;
    auto it = std::search(m_data + pos, m_data + m_length, str.m_data,
                          str.m_data + str.m_length);
    return it == m_data + m_length ? npos : it - m_data;
  }

  [[nodiscard]] constexpr size_type find(CharT ch,
                                         size_type pos = 0) const noexcept {
    if (pos > m_length)
      return npos;
    auto it = std::find(m_data + pos, m_data + m_length, ch);
    return it == m_data + m_length ? npos : it - m_data;
  }

  [[nodiscard]] constexpr size_type rfind(const my_string &str,
                                          size_type pos = npos) const noexcept {
    if (m_length < str.m_length)
      return npos;
    if (str.empty())
      return std::min(pos, m_length);
    auto r_it =
        std::find_end(m_data, m_data + std::min(pos, m_length - str.m_length),
                      str.m_data, str.m_data + str.m_length);
    return r_it == m_data + (std::min(pos, m_length - str.m_length))
               ? npos
               : r_it - m_data;
  }

  [[nodiscard]] constexpr size_type rfind(CharT ch,
                                          size_type pos = npos) const noexcept {
    if (m_length == 0)
      return npos;
    for (size_type i = std::min(pos, m_length - 1); i != npos; --i) {
      if (m_data[i] == ch)
        return i;
    }
    return npos;
  }

  int compare(const my_string &other) const {
    return std::strcmp(m_data, other.m_data);
  }

  constexpr bool operator==(const my_string &str) const noexcept {
    return (m_length == str.m_length) &&
           (std::char_traits<CharT>::compare(m_data, str.m_data, m_length) ==
            0);
  }

  constexpr bool operator!=(const my_string &str) const noexcept {
    return !(*this == str);
  }

  constexpr bool operator<(const my_string &str) const noexcept {
    return std::lexicographical_compare(m_data, m_data + m_length, str.m_data,
                                        str.m_data + str.m_length);
  }

  constexpr bool operator>(const my_string &str) const noexcept {
    return str < *this;
  }

  [[nodiscard]] constexpr iterator begin() const noexcept { return m_data; }

  [[nodiscard]] constexpr iterator end() const noexcept {
    return m_data + m_length;
  }

  constexpr void swap(my_string &other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_length, other.m_length);
  }

  my_string &operator=(const my_string &other) {
    if (this != &other) {
      delete[] m_data;
      m_data = new CharT[other.m_length + 1];
      std::copy(other.m_data, other.m_data + other.m_length, m_data);
      m_data[other.m_length] = '\0';
      m_length = other.m_length;
    }
    return *this;
  }

  my_string &insert(size_type pos, const my_string &str) {
    if (pos > m_length) {
      throw std::out_of_range("Out of range");
    }

    size_type new_length = m_length + str.size();
    CharT *new_data = new CharT[new_length + 1];

    std::copy(m_data, m_data + pos, new_data);

    std::copy(str.m_data, str.m_data + str.m_length, new_data + pos);

    std::copy(m_data + pos, m_data + m_length, new_data + pos + str.m_length);

    new_data[new_length] = '\0';

    delete[] m_data;
    m_data = new_data;
    m_length = new_length;

    return *this;
  }

  my_string &erase(size_type pos, size_type len = npos) {
    if (pos >= m_length) {
      throw std::out_of_range("Out of range");
    }

    len = std::min(len, m_length - pos);

    std::copy(m_data, m_data + pos, m_data + pos + len);

    std::copy(m_data + pos + len, m_data + m_length, m_data + pos);

    m_length -= len;
    m_data[m_length] = '\0';

    return *this;
  }

  my_string &replace(size_type pos, size_type len, const my_string &str) {
    erase(pos, len);
    insert(pos, str);
    return *this;
  }

  static constexpr size_type npos = static_cast<size_type>(-1);
  CharT *m_data;

  constexpr size_type find_first_of(const CharT *s, size_type pos = 0) const {
    for (size_type i = pos; i < m_length; ++i) {
      if (std::strchr(s, m_data[i]) != nullptr) {
        return i;
      }
    }
    return npos;
  }

  constexpr size_type find_last_of(const CharT *s, size_type pos = npos) const {
    if (pos == npos) {
      pos = m_length - 1;
    }
    for (size_type i = pos; i < m_length; --i) {
      if (std::strchr(s, m_data[i]) != nullptr) {
        return i;
      }
    }
    return npos;
  }

  constexpr bool contains(CharT ch) const noexcept {
    for (size_t i = 0; i < size(); ++i) {
      if (c_str()[i] == ch) {
        return true;
      }
    }
    return false;
  }

  constexpr my_string strip() const noexcept {
    size_type start = 0;
    size_type end = m_length;

    while (start < m_length && std::isspace(m_data[start])) {
      ++start;
    }
    while (end > start && std::isspace(m_data[end - 1])) {
      --end;
    }
    return substr(start, end - start);
  }

  ~my_string() { delete[] m_data; }

private:
  size_type m_length;
};

template <CharacterType CharT>
std::istream &getline(std::istream &is, my_string<CharT> &str, CharT delim) {
  str = my_string<CharT>(); // Clear the existing content

  typename my_string<CharT>::size_type count = 0;
  CharT ch;
  while (is.get(ch)) {
    if (ch == delim) {
      break; // Stop reading at the delimiter
    }
    str = str + ch;
    ++count;
  }

  if (count > 0) {
    is.clear(); // Clear any potential error flags
  }

  return is;
}

// Specialization for char type to support getline with std::string
template <>
inline std::istream &getline(std::istream &is, my_string<char> &str, char delim) {
  str = my_string<char>(); // Clear the existing content

  typename my_string<char>::size_type count = 0;
  char ch;
  while (is.get(ch)) {
    if (ch == delim) {
      break; // Stop reading at the delimiter
    }
    str = str + ch;
    ++count;
  }

  if (count > 0) {
    is.clear(); // Clear any potential error flags
  }

  return is;
}

using string = my_string<char>;

} // namespace my_string

#endif // MY_STRING_HPP
