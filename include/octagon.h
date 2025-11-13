#pragma once

#include "figure.h"
#include <array>
#include <cmath>
#include <iostream>

template <Scalar T>
class Octagon : public Figure<T> {
public:
    Octagon() {
        for (auto& point : points)
            point = std::make_unique<Point<T>>();
    }

    Octagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3,
            const Point<T>& p4, const Point<T>& p5, const Point<T>& p6,
            const Point<T>& p7, const Point<T>& p8) {
        points[0] = std::make_unique<Point<T>>(p1);
        points[1] = std::make_unique<Point<T>>(p2);
        points[2] = std::make_unique<Point<T>>(p3);
        points[3] = std::make_unique<Point<T>>(p4);
        points[4] = std::make_unique<Point<T>>(p5);
        points[5] = std::make_unique<Point<T>>(p6);
        points[6] = std::make_unique<Point<T>>(p7);
        points[7] = std::make_unique<Point<T>>(p8);
    }

    Octagon(const Octagon& other) {
        for (size_t i = 0; i < 8; ++i)
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }

    Octagon& operator=(const Octagon& other) {
        if (this == &other) return *this;
        for (size_t i = 0; i < 8; ++i)
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
        return *this;
    }

    Octagon(Octagon&& other) noexcept {
        for (size_t i = 0; i < 8; ++i)
            points[i] = std::move(other.points[i]);
    }

    Octagon& operator=(Octagon&& other) noexcept {
        if (this == &other) return *this;
        for (size_t i = 0; i < 8; ++i)
            points[i] = std::move(other.points[i]);
        return *this;
    }

    Point<T> Center() const override {
        T sumX{0}, sumY{0};
        for (const auto& p : points) {
            sumX += p->x();
            sumY += p->y();
        }
        return Point<T>(sumX / 8, sumY / 8);
    }

    operator double() const override {
        double area = 0.0;
        for (size_t i = 0; i < 8; ++i) {
            size_t j = (i + 1) % 8;
            area += static_cast<double>(points[i]->x() * points[j]->y());
            area -= static_cast<double>(points[j]->x() * points[i]->y());
        }
        return std::abs(area) / 2.0;
    }

    bool operator==(const Figure<T>& other) const override {
        const Octagon<T>* oct = dynamic_cast<const Octagon<T>*>(&other);
        if (!oct) return false;
        for (size_t i = 0; i < 8; ++i)
            if (*(points[i]) != *(oct->points[i]))
                return false;
        return true;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Octagon>(*this);
    }

protected:
    void print(std::ostream& os) const override {
        os << "Octagon:";
        for (const auto& p : points) os << " " << *p;
    }

    void read(std::istream& is) override {
        std::cout << "Enter 8 vertices (x1 y1 x2 y2 ... x8 y8): ";
        for (size_t i = 0; i < 8; ++i) {
            Point<T> p;
            is >> p;
            *points[i] = p;
        }
    }

private:
    std::array<std::unique_ptr<Point<T>>, 8> points;
};