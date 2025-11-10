#pragma once

#include <type_traits>
#include <concepts>
#include <iostream>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
class Point {
public:
    T x_{}, y_{};

    Point() = default;
    Point(T x, T y) : x_(x), y_(y) {}

    Point(const Point& other) = default;
    Point(Point&& other) noexcept = default;

    Point& operator=(const Point& other) = default;
    Point& operator=(Point&& other) noexcept = default;

    bool operator==(const Point& other) const = default;

    T x() const { return x_; }
    T y() const { return y_; }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x_ << ", " << p.y_ << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x_ >> p.y_;
        return is;
    }
};








