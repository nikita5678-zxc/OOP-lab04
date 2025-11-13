#include "include/array.h"
#include "include/triangle.h"
#include "include/hexagon.h"
#include "include/octagon.h"

#include <iostream>
#include <memory>

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;

    auto tri = std::make_shared<Triangle<double>>(
        Point<double>(0, 0),
        Point<double>(1, 0),
        Point<double>(0, 1)
    );
    figures.add(std::move(tri));

    auto hex = std::make_shared<Hexagon<double>>(
        Point<double>(2, 0),
        Point<double>(3, 0),
        Point<double>(4, 1),
        Point<double>(3, 2),
        Point<double>(2, 2),
        Point<double>(1, 1)
    );
    figures.add(std::move(hex));

    auto oct = std::make_shared<Octagon<double>>(
        Point<double>(0, 3),
        Point<double>(1, 3),
        Point<double>(2, 4),
        Point<double>(2, 5),
        Point<double>(1, 6),
        Point<double>(0, 6),
        Point<double>(-1, 5),
        Point<double>(-1, 4)
    );
    figures.add(std::move(oct));

    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << "Figure " << i << ":\n";
        std::cout << *figures[i] << "\n";
        std::cout << "Center: " << figures[i]->Center() << "\n";
        std::cout << "Area: " << static_cast<double>(*figures[i]) << "\n\n";
    }

    std::cout << "Total area: " << figures.totalArea() << "\n\n";

    figures.remove(1);

    std::cout << "After removing index 1:\n";
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << "Figure " << i << ":\n";
        std::cout << *figures[i] << "\n";
        std::cout << "Area: " << static_cast<double>(*figures[i]) << "\n\n";
    }

    Array<std::shared_ptr<Octagon<int>>> octagons;
    octagons.add(std::make_shared<Octagon<int>>(
        Point<int>(0, 0),
        Point<int>(2, 0),
        Point<int>(3, 1),
        Point<int>(2, 2),
        Point<int>(0, 2),
        Point<int>(-1, 2),
        Point<int>(-2, 1),
        Point<int>(-1, 0)
    ));

    std::cout << "Integer octagon:\n";
    for (size_t i = 0; i < octagons.getSize(); ++i) {
        std::cout << *octagons[i] << "\n";
        std::cout << "Area: " << static_cast<double>(*octagons[i]) << "\n";
    }

    return 0;
}