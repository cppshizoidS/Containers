#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <utility>

namespace cppshizoid::tools {
template <typename First, typename Second> struct pair {
  First first;
  Second second;
};

template <typename First, typename Second>
[[nodiscard]] constexpr bool operator==(const pair<First, Second> &lhs,
                                        const pair<First, Second> &rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename First, typename Second>
[[nodiscard]] constexpr bool operator==(const ::std::pair<First, Second> &lhs,
                                        const pair<First, Second> &rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename First, typename Second>
pair(First f, Second s) -> pair<First, Second>;

} // namespace cppshizoid::tools

#endif // !UTILITY_HPP
