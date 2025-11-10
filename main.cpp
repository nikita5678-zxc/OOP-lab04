#include "include/array.h"
#include "include/triangle.h"
#include "include/hexagon.h"
#include "include/octagon.h"

#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    string command;

    cout << "Программа для работы с фигурами\n";
    cout << "Доступные команды:\n";
    cout << "  add <тип>   — добавить фигуру (triangle, hexagon, octagon)\n";
    cout << "  list        — показать все фигуры\n";
    cout << "  area        — посчитать общую площадь\n";
    cout << "  remove <n>  — удалить фигуру под номером n\n";
    cout << "  quit        — выйти\n\n";

    while (cin >> command) {
        if (command == "quit") {
            break;
        }

        else if (command == "add") {
            string type;
            cin >> type;

            if (type != "triangle" && type != "hexagon" && type != "octagon") {
                cout << "Неизвестный тип фигуры\n";
                continue;
            }

            double cx, cy, vx, vy;
            cout << "Введите координаты центра (x y): ";
            cin >> cx >> cy;
            cout << "Введите координаты одной вершины (x y): ";
            cin >> vx >> vy;

            if (type == "triangle") {
                figures.add(std::make_shared<Triangle<double>>(
                    Point<double>(cx, cy), Point<double>(vx, vy)
                ));
            } else if (type == "hexagon") {
                figures.add(std::make_shared<Hexagon<double>>(
                    Point<double>(cx, cy), Point<double>(vx, vy)
                ));
            } else if (type == "octagon") {
                figures.add(std::make_shared<Octagon<double>>(
                    Point<double>(cx, cy), Point<double>(vx, vy)
                ));
            }

            cout << "Фигура добавлена\n";
        }

        else if (command == "list") {
            if (figures.getSize() == 0) {
                cout << "Нет фигур\n";
                continue;
            }

            for (size_t i = 0; i < figures.getSize(); ++i) {
                cout << "Фигура " << i << ":\n";
                cout << *figures[i] << "\n";
                cout << "Центр: " << figures[i]->Center() << "\n";
                cout << "Площадь: " << static_cast<double>(*figures[i]) << "\n\n";
            }
        }

        else if (command == "area") {
            cout << "Общая площадь: " << figures.totalArea() << "\n";
        }

        else if (command == "remove") {
            size_t index;
            cin >> index;
            if (index >= figures.getSize()) {
                cout << "Неверный номер фигуры\n";
            } else {
                figures.remove(index);
                cout << "Фигура удалена\n";
            }
        }

        else {
            cout << "Неизвестная команда\n";
        }
    }

    cout << "программа завершена\n";
    return 0;
}