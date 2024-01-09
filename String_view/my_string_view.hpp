#ifndef MY_STRING_VIEW_HPP
#define MY_STRING_VIEW_HPP

#include <algorithm>
#include <concepts>
#include <cstring>
#include <iostream>
#include <string>
namespace my_string_view_namespace {
template <typename T>
concept CharacterType = std::same_as<T, char> || std::same_as<T, wchar_t> ||
                        std::same_as<T, char16_t> || std::same_as<T, char32_t>;

template <CharacterType CharT>
class my_string_view {
 public:
  using size_type = std::size_t;
  using const_iterator = const CharT*;

  constexpr my_string_view() noexcept : m_data(nullptr), m_length(0) {}

  constexpr explicit my_string_view(const CharT* str) noexcept
      : m_data(str), m_length(std::char_traits<CharT>::length(str)) {}

  constexpr my_string_view(const CharT* str, size_type len) noexcept
      : m_data(str), m_length(len) {}

  template <std::convertible_to<const CharT*> S>
  constexpr explicit my_string_view(const S& str) noexcept
      : m_data(str.data()), m_length(str.size()) {}

  [[nodiscard]] constexpr const CharT* data() const noexcept { return m_data; }

  [[nodiscard]] constexpr size_type size() const noexcept { return m_length; }

  [[nodiscard]] constexpr bool empty() const noexcept { return m_length == 0; }

  constexpr CharT operator[](size_type pos) const { return m_data[pos]; }

  [[nodiscard]] constexpr my_string_view substr(size_type pos, size_type len = npos) const {
    if (pos > m_length) throw std::out_of_range("Out of range");
    return my_string_view(m_data + pos, std::min(len, m_length - pos));
  }

  [[nodiscard]] constexpr size_type find(my_string_view sv,
                           size_type pos = 0) const noexcept {
    if (pos > m_length || sv.size() > m_length - pos) return npos;
    auto it = std::search(m_data + pos, m_data + m_length, sv.m_data,
                          sv.m_data + sv.m_length);
    return it == m_data + m_length ? npos : it - m_data;
  }

  [[nodiscard]] constexpr size_type find(CharT ch, size_type pos = 0) const noexcept {
    if (pos > m_length) return npos;
    auto it = std::find(m_data + pos, m_data + m_length, ch);
    return it == m_data + m_length ? npos : it - m_data;
  }

  [[nodiscard]] constexpr size_type rfind(my_string_view sv,
                            size_type pos = npos) const noexcept {
    if (m_length < sv.m_length) return npos;
    if (sv.empty()) return std::min(pos, m_length);
    auto r_it =
        std::find_end(m_data, m_data + std::min(pos, m_length - sv.m_length),
                      sv.m_data, sv.m_data + sv.m_length);
    return r_it == m_data + (std::min(pos, m_length - sv.m_length))
               ? npos
               : r_it - m_data;
  }

  [[nodiscard]] constexpr size_type rfind(CharT ch, size_type pos = npos) const noexcept {
    if (m_length == 0) return npos;
    for (size_type i = std::min(pos, m_length - 1); i != npos; --i) {
      if (m_data[i] == ch) return i;
    }
    return npos;
  }

  constexpr bool operator==(my_string_view sv) const noexcept {
    return (m_length == sv.m_length) &&
           (std::char_traits<CharT>::compare(m_data, sv.m_data, m_length) == 0);
  }

  constexpr bool operator!=(my_string_view sv) const noexcept {
    return *this != sv;
  }

  constexpr bool operator<(my_string_view sv) const noexcept {
    return std::lexicographical_compare(m_data, m_data + m_length, sv.m_data,
                                        sv.m_data + sv.m_length);
  }

  constexpr bool operator>(my_string_view sv) const noexcept {
    return sv < *this;
  }

  [[nodiscard]] constexpr const_iterator begin() const noexcept { return m_data; }

  [[nodiscard]] constexpr const_iterator end() const noexcept { return m_data + m_length; }

  constexpr void swap(my_string_view& other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_length, other.m_length);
  }
  my_string_view& operator=(const my_string_view& other) {
    if (this != &other) {
      m_data = other.m_data;
      m_length = other.m_length;
    }
    return *this;
  }

  static constexpr size_type npos = static_cast<size_type>(-1);
  const CharT* m_data;
  size_type m_length;

  constexpr size_type find_first_of(const CharT* s, size_type pos = 0) const {
    for (size_type i = pos; i < m_length; ++i) {
      if (std::strchr(s, m_data[i]) != nullptr) {
        return i;
      }
    }
    return npos;
  }

  constexpr size_type find_last_of(const CharT* s, size_type pos = npos) const {
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
      if (data()[i] == ch) {
        return true;
      }
    }
    return false;
  }
};

using string_view = my_string_view<char>;
}
#endif //STRING_VIEW_MY_STRING_VIEW_HPP