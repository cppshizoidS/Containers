#ifndef SIMPLE_STACK_FLAT_MAP
#define SIMPLE_STACK_FLAT_MAP

#include "flat_map_adapter.hpp"
#include "stack_vector.hpp"
#include "utitlity.hpp"
#include <cstddef>

namespace cppshizoid::tools {
template <typename Key, typename Value, std::size_t Size>
using stack_flat_map =
    flat_map_adapter<Key, Value, simple_stack_vector<pair<Key, Value>, Size>>;
}

#endif
