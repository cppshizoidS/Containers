#ifndef FLAT_MAP_HPP
#define FLAT_MAP_HPP

#include "flat_map_adapter.hpp"
#include "utitlity.hpp"
#include <vector>

namespace cppshizoid::tools {
template <typename Key, typename Value>
using flat_map =
    flat_map_adapter<Key, Value, std::vector<pair<const Key, Value>>>;
}

#endif // DEBUG
