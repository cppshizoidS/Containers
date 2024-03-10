#include <algorithm>
#include <vector>

namespace cppshizoid::tools {

namespace fsimpl {
struct less {
  template <typename T, typename U>
  auto operator()(const T &t, const U &u) const -> decltype(t < u) {
    return t < u;
  }
};
} // namespace fsimpl

template <typename Key, typename Compare = fsimpl::less,
          typename Container = std::vector<Key>>
class flat_set : private /*EBO*/ Compare {
  Container m_container;
  Compare &cmp() { return *this; }
  const Compare &cmp() const { return *this; }

public:
  using key_type = Key;
  using value_type = Key;
  using container_type = Container;
  using key_compare = Compare;
  using reference = value_type &;
  using const_reference = const value_type &;
  using allocator_type = typename container_type::allocator_type;
  using pointer = typename std::allocator_traits<allocator_type>::pointer;
  using const_pointer = typename std::allocator_traits<allocator_type>::pointer;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator =
      typename container_type::const_reverse_iterator;
  using difference_type = typename container_type::difference_type;
  using size_type = typename container_type::size_type;

  flat_set() {}

  explicit flat_set(const key_compare &comp,
                    const allocator_type &alloc = allocator_type())
      : Compare(comp), m_container(alloc) {}

  explicit flat_set(container_type container,
                    const key_compare &comp = key_compare())
      : Compare(comp), m_container(std::move(container)) {
    std::sort(m_container.begin(), m_container.end(), cmp());
    auto new_end =
        std::unique(m_container.begin(), m_container.end(),
                    [this](const value_type &a, const value_type &b) -> bool {
                      return !cmp()(a, b) && !cmp()(b, a);
                    });
    m_container.erase(new_end, m_container.end());
  }

  flat_set(std::initializer_list<value_type> init,
           const key_compare &comp = key_compare(),
           const allocator_type &alloc = allocator_type())
      : flat_set(container_type(std::move(init), alloc), comp) {}

  flat_set(std::initializer_list<value_type> init, const allocator_type &alloc)
      : flat_set(std::move(init), key_compare(), alloc) {}

  template <class InputIterator,
            typename = decltype(*std::declval<InputIterator>())>
  flat_set(InputIterator begin, InputIterator end, const key_compare &comp,
           const allocator_type &alloc = allocator_type())
      : flat_set(container_type(begin, end, alloc), comp) {}

  template <class InputIterator,
            typename = decltype(*std::declval<InputIterator>())>
  flat_set(InputIterator begin, InputIterator end,
           const allocator_type &alloc = allocator_type())
      : flat_set(begin, end, key_compare(), alloc) {}

  flat_set(const flat_set &x) = default;
  flat_set &operator=(const flat_set &x) = default;

  flat_set(flat_set &&x) noexcept = default;
  flat_set &operator=(flat_set &&x) noexcept = default;

  key_compare key_comp() const { return *this; }

  iterator begin() noexcept { return m_container.begin(); }
  const_iterator begin() const noexcept { return m_container.begin(); }
  iterator end() noexcept { return m_container.end(); }
  const_iterator end() const noexcept { return m_container.end(); }
  reverse_iterator rbegin() noexcept { return m_container.rbegin(); }
  const_reverse_iterator rbegin() const noexcept {
    return m_container.rbegin();
  }
  reverse_iterator rend() noexcept { return m_container.rend(); }
  const_reverse_iterator rend() const noexcept { return m_container.rend(); }
  const_iterator cbegin() const noexcept { return m_container.cbegin(); }
  const_iterator cend() const noexcept { return m_container.cend(); }

  bool empty() const noexcept { return m_container.empty(); }
  size_type size() const noexcept { return m_container.size(); }
  size_type max_size() const noexcept { return m_container.max_size(); }

  void reserve(size_type count) { return m_container.reserve(count); }
  size_type capacity() const noexcept { return m_container.capacity(); }

  void clear() noexcept { m_container.clear(); }

  template <typename F> iterator lower_bound(const F &k) {
    return std::lower_bound(m_container.begin(), m_container.end(), k, cmp());
  }

  template <typename F> const_iterator lower_bound(const F &k) const {
    return std::lower_bound(m_container.begin(), m_container.end(), k, cmp());
  }

  template <typename K> iterator upper_bound(const K &k) {
    return std::upper_bound(m_container.begin(), m_container.end(), k, cmp());
  }

  template <typename K> const_iterator upper_bound(const K &k) const {
    return std::upper_bound(m_container.begin(), m_container.end(), k, cmp());
  }

  template <typename K> std::pair<iterator, iterator> equal_range(const K &k) {
    return std::equal_range(m_container.begin(), m_container.end(), k, cmp());
  }

  template <typename K>
  std::pair<const_iterator, const_iterator> equal_range(const K &k) const {
    return std::equal_range(m_container.begin(), m_container.end(), k, cmp());
  }

  template <typename F> iterator find(const F &k) {
    auto i = lower_bound(k);
    if (i != end() && !cmp()(k, *i))
      return i;

    return end();
  }

  template <typename F> const_iterator find(const F &k) const {
    auto i = lower_bound(k);
    if (i != end() && !cmp()(k, *i))
      return i;

    return end();
  }

  template <typename F> size_t count(const F &k) const {
    return find(k) == end() ? 0 : 1;
  }

  template <typename P> std::pair<iterator, bool> insert(P &&val) {
    auto i = lower_bound(val);
    if (i != end() && !cmp()(val, *i)) {
      return {i, false};
    }

    return {m_container.emplace(i, std::forward<P>(val)), true};
  }

  std::pair<iterator, bool> insert(const value_type &val) {
    auto i = lower_bound(val);
    if (i != end() && !cmp()(val, *i)) {
      return {i, false};
    }

    return {m_container.emplace(i, val), true};
  }

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args) {
    value_type val(std::forward<Args>(args)...);
    return insert(std::move(val));
  }

  iterator erase(const_iterator pos) { return m_container.erase(pos); }

  iterator erase(iterator pos) { return erase(const_iterator(pos)); }

  template <typename F> size_type erase(const F &k) {
    auto i = find(k);
    if (i == end()) {
      return 0;
    }

    erase(i);
    return 1;
  }

  void swap(flat_set &x) {
    std::swap(cmp(), x.cmp());
    m_container.swap(x.m_container);
  }

  const container_type &container() const noexcept { return m_container; }

  container_type &modify_container() noexcept { return m_container; }
};

template <typename Key, typename Compare, typename Container>
bool operator==(const flat_set<Key, Compare, Container> &a,
                const flat_set<Key, Compare, Container> &b) {
  return a.container() == b.container();
}

template <typename Key, typename Compare, typename Container>
bool operator!=(const flat_set<Key, Compare, Container> &a,
                const flat_set<Key, Compare, Container> &b) {
  return a.container() != b.container();
}
} // namespace cppshizoid::tools
