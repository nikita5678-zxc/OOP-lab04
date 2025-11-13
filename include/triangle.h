#pragma once

#include "figure.h"
#include <array>
#include <cmath>
#include <iostream>

template <Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() {
        for (auto& point : points)
            point = std::make_unique<Point<T>>();
    }

    Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        points[0] = std::make_unique<Point<T>>(p1);
        points[1] = std::make_unique<Point<T>>(p2);
        points[2] = std::make_unique<Point<T>>(p3);
    }

    Triangle(const Triangle& other) {
        for (size_t i = 0; i < 3; ++i)
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }

    Triangle& operator=(const Triangle& other) {
        if (this == &other) return *this;
        for (size_t i = 0; i < 3; ++i)
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
        return *this;
    }

    Triangle(Triangle&& other) noexcept {
        for (size_t i = 0; i < 3; ++i)
            points[i] = std::move(other.points[i]);
    }

    Triangle& operator=(Triangle&& other) noexcept {
        if (this == &other) return *this;
        for (size_t i = 0; i < 3; ++i)
            points[i] = std::move(other.points[i]);
        return *this;
    }

    Point<T> Center() const override {
        T sumX{0}, sumY{0};
        for (const auto& p : points) {
            sumX += p->x();
            sumY += p->y();
        }
        return Point<T>(sumX / 3, sumY / 3);
    }

    operator double() const override {
        T x1 = points[0]->x(), y1 = points[0]->y();
        T x2 = points[1]->x(), y2 = points[1]->y();
        T x3 = points[2]->x(), y3 = points[2]->y();
        T area = std::abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2;
        return static_cast<double>(area);
    }

    bool operator==(const Figure<T>& other) const override {
        const Triangle<T>* tri = dynamic_cast<const Triangle<T>*>(&other);
        if (!tri) return false;
        for (size_t i = 0; i < 3; ++i)
            if (*(points[i]) != *(tri->points[i]))
                return false;
        return true;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Triangle>(*this);
    }

protected:
    void print(std::ostream& os) const override {
        os << "Triangle: " << *points[0] << " " << *points[1] << " " << *points[2];
    }

    void read(std::istream& is) override {
        Point<T> p1, p2, p3;
        std::cout << "Enter three vertices (x1 y1 x2 y2 x3 y3): ";
        is >> p1 >> p2 >> p3;
        *points[0] = p1;
        *points[1] = p2;
        *points[2] = p3;
    }

private:
    std::array<std::unique_ptr<Point<T>>, 3> points;
};