#ifndef MY_LIST_HPP
#define MY_LIST_HPP

#include <cstddef>
#include <utility>

template <typename T>
void swap(T &a, T &b) {
  T temp = std::move(a);
  a = std::move(b);
  b = std::move(temp);
}
namespace my_list {

template <typename T>
class ListNode {
 public:
  T data;
  ListNode *prev;
  ListNode *next;

  ListNode(const T &value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class MyList {
 public:
  ListNode<T> *head;
  ListNode<T> *tail;
  size_t size;

  void sort(ListNode<T> *left, ListNode<T> *right) {
    if (left != nullptr && right != nullptr && left != right &&
        left->prev != right) {
      ListNode<T> *pivot = partition(left, right);
      sort(left, pivot);
      sort(pivot->next, right);
    }
  }

  ListNode<T> *partition(ListNode<T> *left, ListNode<T> *right) {
    T pivotValue = right->data;
    ListNode<T> *i = left->prev;

    for (ListNode<T> *j = left; j != right; j = j->next) {
      if (j->data <= pivotValue) {
        i = (i == nullptr) ? left : i->next;
        swap(i->data, j->data);
      }
    }

    i = (i == nullptr) ? left : i->next;
    swap(i->data, right->data);

    return i;
  }

  MyList() : head(nullptr), tail(nullptr), size(0) {}

  ~MyList() { clear(); }

  void push_back(const T &value) {
    ListNode<T> *newNode = new ListNode<T>(value);
    if (size == 0) {
      head = tail = newNode;
    } else {
      newNode->prev = tail;
      tail->next = newNode;
      tail = newNode;
    }
    size++;
  }

  void pop_back() {
    if (size == 0) {
      return;
    }
    if (size == 1) {
      delete head;
      head = tail = nullptr;
    } else {
      ListNode<T> *temp = tail;
      tail = tail->prev;
      tail->next = nullptr;
      delete temp;
    }
    size--;
  }

  void push_front(const T &value) {
    ListNode<T> *newNode = new ListNode<T>(value);
    if (size == 0) {
      head = tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
    size++;
  }

  void pop_front() {
    if (size == 0) {
      return;  // empty list
    }
    if (size == 1) {
      delete head;
      head = tail = nullptr;
    } else {
      ListNode<T> *temp = head;
      head = head->next;
      head->prev = nullptr;
      delete temp;
    }
    size--;
  }

  size_t getSize() const { return size; }

  void clear() {
    while (size > 0) {
      pop_back();
    }
  }

  class Iterator {
   private:
    ListNode<T> *current;

   public:
    Iterator(ListNode<T> *node) : current(node) {}

    T &operator*() const { return current->data; }

    Iterator &operator++() {
      current = current->next;
      return *this;
    }

    bool operator!=(const Iterator &other) const {
      return current != other.current;
    }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }
  };

  Iterator begin() const { return Iterator(head); }

  Iterator end() const { return Iterator(nullptr); }

  void insert(Iterator position, const T &value) {
    if (position == end()) {
      push_back(value);
    } else if (position == begin()) {
      push_front(value);
    } else {
      ListNode<T> *newNode = new ListNode<T>(value);
      newNode->prev = position.current->prev;
      newNode->next = position.current;
      position.current->prev->next = newNode;
      position.current->prev = newNode;
      size++;
    }
  }
  void erase(Iterator position) {
    if (position != end()) {
      if (position.current == head) {
        pop_front();
      } else if (position.current == tail) {
        pop_back();
      } else {
        position.current->prev->next = position.current->next;
        position.current->next->prev = position.current->prev;
        delete position.current;
        size--;
      }
    }
  }

  template <typename Predicate>
  void erase_if(Predicate pred) {
    for (auto it = begin(); it != end();) {
      if (pred(*it)) {
        it = erase(it);
      } else {
        ++it;
      }
    }
  }
};
}  // namespace my_list
#endif  // MY_LIST_HPP
