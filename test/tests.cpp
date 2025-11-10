#include <gtest/gtest.h>
#include "../include/point.h"
#include "../include/triangle.h"
#include "../include/hexagon.h"
#include "../include/octagon.h"
#include "../include/array.h"
#include <memory>

// Тесты для Point
TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_EQ(p.x(), 0.0);
    EXPECT_EQ(p.y(), 0.0);
}

TEST(PointTest, ParamConstructor) {
    Point<int> p(3, -4);
    EXPECT_EQ(p.x(), 3);
    EXPECT_EQ(p.y(), -4);
}

TEST(PointTest, Equality) {
    Point<float> p1(1.0f, 2.0f);
    Point<float> p2(1.0f, 2.0f);
    Point<float> p3(0.0f, 0.0f);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

// Тесты для Triangle
TEST(TriangleTest, AreaAndCenter) {
    Point<double> center(0.0, 0.0);
    Point<double> vertex(1.0, 0.0);
    Triangle<double> tri(center, vertex);

    auto center_calc = tri.Center();
    EXPECT_NEAR(center_calc.x(), 0.0, 1e-6);
    EXPECT_NEAR(center_calc.y(), 0.0, 1e-6);

    double area = static_cast<double>(tri);
    double expected = 0.75 * std::sqrt(3.0); // R = 1
    EXPECT_NEAR(area, expected, 1e-6);
}

TEST(TriangleTest, Equality) {
    Triangle<double> t1(Point<double>(0,0), Point<double>(1,0));
    Triangle<double> t2(Point<double>(0,0), Point<double>(1,0));
    Triangle<double> t3(Point<double>(0,0), Point<double>(2,0));

    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

// Тесты для Hexagon
TEST(HexagonTest, Area) {
    Hexagon<double> hex(Point<double>(0,0), Point<double>(1,0));
    double area = static_cast<double>(hex);
    double expected = 1.5 * std::sqrt(3.0); // R = 1
    EXPECT_NEAR(area, expected, 1e-6);
}

// Тесты для Octagon
TEST(OctagonTest, Area) {
    Octagon<double> oct(Point<double>(0,0), Point<double>(1,0));
    double area = static_cast<double>(oct);
    double expected = 2.0 * (1.0 + std::sqrt(2.0)); // R = 1
    EXPECT_NEAR(area, expected, 1e-6);
}

// Тесты для Array
TEST(ArrayTest, AddAndTotalArea) {
    Array<std::shared_ptr<Figure<double>>> arr;

    auto tri = std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(1,0));
    auto hex = std::make_shared<Hexagon<double>>(Point<double>(0,0), Point<double>(1,0));

    arr.add(std::move(tri));
    arr.add(std::move(hex));

    EXPECT_EQ(arr.getSize(), 2);
    double total = arr.totalArea();
    double expected = 0.75 * std::sqrt(3.0) + 1.5 * std::sqrt(3.0);
    EXPECT_NEAR(total, expected, 1e-6);
}

TEST(ArrayTest, Remove) {
    Array<std::shared_ptr<Figure<double>>> arr;

    auto t1 = std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(1,0));
    auto t2 = std::make_shared<Triangle<double>>(Point<double>(0,0), Point<double>(2,0));

    arr.add(std::move(t1));
    arr.add(std::move(t2));

    EXPECT_EQ(arr.getSize(), 2);
    arr.remove(0);
    EXPECT_EQ(arr.getSize(), 1);

    // Оставшаяся фигура — t2 (площадь в 4 раза больше, т.к. R=2 → S ~ R²)
    double area = arr.totalArea();
    double expected = 0.75 * std::sqrt(3.0) * 4.0;
    EXPECT_NEAR(area, expected, 1e-6);
}

// Тест клонирования (если нужно)
TEST(FigureTest, Clone) {
    Triangle<double> orig(Point<double>(1,1), Point<double>(2,1));
    auto clone_ptr = orig.clone();
    Triangle<double>* cloned = dynamic_cast<Triangle<double>*>(clone_ptr.get());
    ASSERT_NE(cloned, nullptr);
    EXPECT_TRUE(orig == *cloned);
}