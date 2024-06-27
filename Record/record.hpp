#ifndef RECORD_HPP
#define RECORD_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <format>
#include <print>

struct Record {
    int id;
    std::string name;
    double value;

    constexpr Record() {};

    constexpr Record(int id, std::string name, double value)
        : id(id), name(std::move(name)), value(value) {}

    constexpr bool operator==(const Record& other) const {
        return std::tie(id, name, value) == std::tie(other.id, other.name, other.value);
    }
};

template<typename T>
class RecordContainer {
public:
    using value_type = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    constexpr RecordContainer() = default;

    constexpr void add(const T& record) {
        records_.push_back(record);
    }

    constexpr void remove(const T& record) {
        records_.erase(std::remove(records_.begin(), records_.end(), record), records_.end());
    }

    constexpr iterator begin() {
        return records_.begin();
    }

    constexpr const_iterator begin() const {
        return records_.cbegin();
    }

    constexpr iterator end() {
        return records_.end();
    }

    constexpr const_iterator end() const {
        return records_.cend();
    }

    constexpr size_t size() const {
        return records_.size();
    }

    constexpr bool empty() const {
        return records_.empty();
    }

    constexpr void clear() {
        records_.clear();
    }

    constexpr T& operator[](size_t index) {
        return records_[index];
    }

    constexpr const T& operator[](size_t index) const {
        return records_[index];
    }

private:
    std::vector<T> records_;
};


#if __cplusplus >= 202300L
template<typename Container>
constexpr void print_container(const Container& container) {
    for (const auto& record : container) {
        std::print("Record{{id={}, name={}, value={}}}\n", record.id, record.name, record.value);
    }
}
#elif __cplusplus >= 202000L 
#include <format>
template<typename Container>
constexpr void print_container(const Container& container) {
    for (const auto& record : container) {
        std::cout << std::format("Record{{id={}, name={}, value={}}}\n", record.id, record.name, record.value);
    }
}
#else 
template<typename Container>
void print_container(const Container& container) {
    for (const auto& record : container) {
        std::cout << "Record{id=" << record.id << ", name=" << record.name << ", value=" << record.value << "}\n";
    }
}
#endif

#endif // !RECORD_HPP
