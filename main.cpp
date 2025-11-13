#include "include/array.h"
#include "include/triangle.h"
#include "include/hexagon.h"
#include "include/octagon.h"

#include <iostream>
#include <memory>

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;

    auto tri = std::make_shared<Triangle<double>>(
        Point<double>(0, 0), Point<double>(1, 0)
    );
    figures.add(std::move(tri));

    auto hex = std::make_shared<Hexagon<double>>(
        Point<double>(3, 0), Point<double>(4, 0)
    );
    figures.add(std::move(hex));

    auto oct = std::make_shared<Octagon<double>>(
        Point<double>(0, 3), Point<double>(1, 3)
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
        Point<int>(0, 0), Point<int>(2, 0)
    ));
    octagons.add(std::make_shared<Octagon<int>>(
        Point<int>(5, 5), Point<int>(7, 5)
    ));

    std::cout << "Integer octagons:\n";
    for (size_t i = 0; i < octagons.getSize(); ++i) {
        std::cout << *octagons[i] << "\n";
        std::cout << "Area: " << static_cast<double>(*octagons[i]) << "\n";
    }

    return 0;
}