#pragma once

#include "point.h"
#include <memory>
#include <iosfwd>

template <Scalar T>
class Figure {
public:
    virtual ~Figure() noexcept = default;
    virtual operator double() const = 0;
    virtual Point<T> Center() const = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;

    virtual std::unique_ptr<Figure<T>> clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.read(is);
        return is;
    }

protected:
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
};
