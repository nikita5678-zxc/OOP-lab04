#pragma once

#include "figure.h"
#include <array>
#include <cmath>
#include <numbers>
#include <iostream>

template <Scalar T>
class Hexagon : public Figure<T> {
public:
    Hexagon() {
        for (auto& point : points)
            point = std::make_unique<Point<T>>();
    }

    Hexagon(const Point<T>& center, const Point<T>& vertex) {
        calculatePoints(center, vertex);
    }

    Hexagon(const Hexagon& other) {
        for (size_t i = 0; i < 6; ++i)
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }

    Hexagon& operator=(const Hexagon& other) {
        if (this == &other) return *this;
        for (size_t i = 0; i < 6; ++i)
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
        return *this;
    }

    Hexagon(Hexagon&& other) noexcept {
        for (size_t i = 0; i < 6; ++i)
            points[i] = std::move(other.points[i]);
    }

    Hexagon& operator=(Hexagon&& other) noexcept {
        if (this == &other) return *this;
        for (size_t i = 0; i < 6; ++i)
            points[i] = std::move(other.points[i]);
        return *this;
    }

    Point<T> Center() const override {
        T sumX{0}, sumY{0};
        for (const auto& p : points) {
            sumX += p->x();
            sumY += p->y();
        }
        return Point<T>(sumX / 6, sumY / 6);
    }

    operator double() const override {
        T dx = points[0]->x() - Center().x();
        T dy = points[0]->y() - Center().y();
        T R = std::hypot(dx, dy);
        return static_cast<double>(1.5 * std::sqrt(3.0) * R * R);
    }

    bool operator==(const Figure<T>& other) const override {
        const Hexagon<T>* otherHex = dynamic_cast<const Hexagon<T>*>(&other);
        if (!otherHex) return false;
        for (size_t i = 0; i < 6; ++i)
            if (*(points[i]) != *(otherHex->points[i]))
                return false;
        return true;
    }

    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Hexagon>(*this);
    }

protected:
    void print(std::ostream& os) const override {
        os << "Hexagon: ";
        for (const auto& p : points)
            os << *p << " ";
    }

    void read(std::istream& is) override {
        Point<T> center, vertex;
        std::cout << "Enter center: ";
        is >> center >> vertex;
        calculatePoints(center, vertex);
    }

private:
    std::array<std::unique_ptr<Point<T>>, 6> points;

    void calculatePoints(const Point<T>& center, const Point<T>& vertex) {
        T dx = vertex.x() - center.x();
        T dy = vertex.y() - center.y();
        T radius = std::hypot(dx, dy);

        if (radius == T{0}) {
            calculatePoints(Point<T>(T{0}, T{0}), Point<T>(T{1}, T{0}));
            return;
        }

        constexpr long double PI_LD = 3.141592653589793238462643383279502884L;
        const T PI = static_cast<T>(PI_LD);
        T baseAngle = std::atan2(dy, dx);
        for (size_t i = 0; i < 6; ++i) {
            T angle = baseAngle + i * (T{2} * PI / T{6});
            T x = center.x() + radius * std::cos(angle);
            T y = center.y() + radius * std::sin(angle);
            points[i] = std::make_unique<Point<T>>(x, y);
        }
    }
};