#ifdef SharedPtr
#define SharedPtr

template <typename T> class SharedPtr {
private:
  T *m_data = nullptr;
  int *m_count = nullptr;

  void clean_up();

public:
  // disable default constructor
  SharedPtr() = delete;

  // constructor
  SharedPtr(T data) {
    m_data = new T(data);
    m_count = new int(1);
  }

  // copy constructor
  SharedPtr(const SharedPtr<T> &another_ptr);

  // destructor
  ~SharedPtr() { clean_up(); }

  // move constructor
  SharedPtr(SharedPtr<T> &&another_ptr);

  T &operator*() const { return *m_data; }

  T *operator->() const { return m_data; }

  // copy Assignment
  SharedPtr<T> &operator=(const SharedPtr<T> &another_ptr);

  // move Assignment
  SharedPtr<T> &operator=(SharedPtr<T> &&another_ptr);
};

template <typename T> void SharedPtr<T>::clean_up() {
  if (nullptr != m_count) {
    (*m_count)--;

    if (*m_count == 0) {
      delete m_data;
      delete m_count;
    }
  }
}

template <typename T> SharedPtr<T>::SharedPtr(const SharedPtr<T> &another_ptr) {
  m_data = another_ptr.m_data;
  m_count = another_ptr.m_count;

  if (nullptr != another_ptr.m_data) {
    (*m_count)++;
  }
}

template <typename T> SharedPtr<T>::SharedPtr(SharedPtr<T> &&another_ptr) {
  m_data = another_ptr.m_data;
  m_count = another_ptr.m_count;
  // clean up another pointer
  another_ptr.m_data = nullptr;
  another_ptr.m_count = nullptr;
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &another_ptr) {
  clean_up();
  m_count = another_ptr.m_count;
  m_data = another_ptr.m_data;

  if (nullptr != another_ptr.m_data) {
    (*m_count)++;
  }
  return *this;
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr<T> &&another_ptr) {
  clean_up();
  m_count = another_ptr.m_count;
  m_data = another_ptr.m_data;
  // clean up another pointer
  another_ptr.m_data = nullptr;
  another_ptr.m_count = nullptr;
  return *this;
}

#endif // DEBUG
