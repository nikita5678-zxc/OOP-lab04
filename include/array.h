#pragma once

#include <memory>
#include <iostream>
#include <stdexcept>
#include <cstddef>

template <typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t capacity;
    size_t size;

    void grow() {
        size_t new_capacity = (capacity == 0) ? 2 : capacity * 2;
        auto new_data = std::make_shared<T[]>(new_capacity);
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]); 
        }
        data = std::move(new_data);
        capacity = new_capacity;
    }

public:
    Array() : data(std::make_shared<T[]>(2)), capacity(2), size(0) {}

    Array(const Array& other)
        : capacity(other.capacity)
        , size(other.size)
        , data(std::make_shared<T[]>(capacity))
    {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            auto new_data = std::make_shared<T[]>(other.capacity);
            for (size_t i = 0; i < other.size; ++i) {
                new_data[i] = other.data[i];
            }
            data = std::move(new_data);
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }

    Array(Array&& other) noexcept
        : data(std::move(other.data))
        , capacity(other.capacity)
        , size(other.size)
    {
        other.capacity = 0;
        other.size = 0;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            capacity = other.capacity;
            size = other.size;
            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }

    void add(T&& item) {
        if (size >= capacity) {
            grow();
        }
        data[size++] = std::move(item);
    }

    void remove(size_t idx) {
        if (idx >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = idx; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }

    T& operator[](size_t idx) {
        if (idx >= size) throw std::out_of_range("Index out of range");
        return data[idx];
    }

    const T& operator[](size_t idx) const {
        if (idx >= size) throw std::out_of_range("Index out of range");
        return data[idx];
    }

    size_t getSize() const { return size; }

    void printFigures() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << *data[i] << "\n";
        }
    }

    void printCenters() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << "Center: " << data[i]->Center() << "\n";
        }
    }

    double totalArea() const {
        double sum = 0.0;
        for (size_t i = 0; i < size; ++i) {
            sum += static_cast<double>(*data[i]);
        }
        return sum;
    }
};