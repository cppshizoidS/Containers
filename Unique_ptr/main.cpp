#include <utility>

template <typename Contained> class unique_ptr {
public:
  constexpr void reset() {
    delete data;
    data = nullptr;
  }
  constexpr unique_ptr() = default;
  constexpr ~unique_ptr() { reset(); }
  constexpr unique_ptr(Contained *data_) : data(data_) {}

  // move
  constexpr unique_ptr(unique_ptr &&other)
      : data(std::exchange(other.data, nullptr)) {}
  constexpr unique_ptr &operator=(unique_ptr &&other) {
    reset();
    data = std::exchange(other.data, nullptr);
  }

  unique_ptr(const unique_ptr &) = delete;
  unique_ptr &operator=(const unique_ptr &) = delete;

private:
  Contained *data = nullptr;
};

constexpr void myfunc() { unique_ptr<int> data(new int()); }

auto main() -> int {}
