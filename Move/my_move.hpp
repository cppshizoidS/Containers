#ifndef MY_MOVE_HPP
#define MY_MOVE_HPP
#include "remove_reference.hpp"

template <typename T> remove_reference_t<T> &&my_move(T &&arg) noexcept {
  return static_cast<remove_reference_t<T> &&>(arg);
}
#endif