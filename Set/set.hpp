#ifndef SET_HPP
#define SET_HPP

#include <cstddef>
#include <initializer_list>
using node_t = struct node*;

struct node {
  int elem;
  node_t left, right;

  node(int elem) : elem(elem), left(nullptr), right(nullptr) {}
};

inline node_t remove_node(node_t root) {
  node_t current;
  if (!root->left) {
    current = root->right;
  } else {
    node_t previous = root;
    current = root->left;
    while (current->right) {
      previous = current;
      current = current->right;
    }
    if (previous != root) {
      previous->right = current->left;
      current->left = root->left;
    }
    current->right = root->right;
  }
  delete root;
  return current;
}

inline void delete_node(node_t root) {
  if (root->left) delete_node(root->left);
  if (root->right) delete_node(root->right);

  delete root;
}

class set {
  node_t root;
  size_t size_;

 public:
  set() : root(nullptr), size_(0) {}
  set(const std::initializer_list<int>& il) : set() {
    for (const int elem : il) insert(elem);
  }
  ~set() {
    if (root) delete_node(root);
  }

  bool empty() { return !root; }
  std::size_t size() { return size_; }

  void insert(int elem);
  void remove(int elem);
  bool member(int elem);
};

inline void set::insert(int elem) {
  node_t* current = &root;
  while (*current) {
    if (elem == (*current)->elem) return;
    if (elem < (*current)->elem)
      current = &(*current)->left;
    else
      current = &(*current)->right;
  }
  *current = new node(elem);
  ++size_;
}

inline void set::remove(int elem) {
  node_t* current = &root;
  while (*current) {
    if (elem == (*current)->elem) {
      *current = remove_node(*current);
      --size_;
      return;
    }
    if (elem < (*current)->elem)
      current = &(*current)->left;
    else
      current = &(*current)->right;
  }
}

inline bool set::member(int elem) {
  node_t* current = &root;
  while (*current) {
    if (elem == (*current)->elem) return true;
    if (elem < (*current)->elem)
      current = &(*current)->left;
    else
      current = &(*current)->right;
  }
  return false;
}

#endif  // SET_HPP
