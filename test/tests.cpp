#include <gtest/gtest.h>
#include "../include/point.h"
#include "../include/triangle.h"
#include "../include/hexagon.h"
#include "../include/octagon.h"
#include "../include/array.h"
#include <memory>
#include <cmath>

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

Point<double> t1(0.0, 0.0);
Point<double> t2(1.0, 0.0);
Point<double> t3(0.0, 1.0);

Point<double> h1(0, 0);
Point<double> h2(1, 0);
Point<double> h3(1.5, 0.866);
Point<double> h4(1, 1.732);
Point<double> h5(0, 1.732);
Point<double> h6(-0.5, 0.866);

Point<double> o1(0, 0);
Point<double> o2(1, 0);
Point<double> o3(1.707, 0.707);
Point<double> o4(2.414, 1.414);
Point<double> o5(1.707, 2.414);
Point<double> o6(1, 3.414);
Point<double> o7(0, 3.414);
Point<double> o8(-0.707, 2.414);

// Тесты для Triangle
TEST(TriangleTest, AreaAndCenter) {
    Triangle<double> tri(t1, t2, t3);

    Point<double> center = tri.Center();
    EXPECT_NEAR(center.x(), (0.0 + 1.0 + 0.0) / 3.0, 1e-6);
    EXPECT_NEAR(center.y(), (0.0 + 0.0 + 1.0) / 3.0, 1e-6);

    double area = static_cast<double>(tri);
    EXPECT_NEAR(area, 0.5, 1e-6); // площадь треугольника (0,0)-(1,0)-(0,1)
}

TEST(TriangleTest, Equality) {
    Triangle<double> t1_obj(t1, t2, t3);
    Triangle<double> t2_obj(t1, t2, t3);
    Triangle<double> t3_obj(t1, t3, t2); // другой порядок → не равны

    EXPECT_TRUE(t1_obj == t2_obj);
    EXPECT_FALSE(t1_obj == t3_obj);
}

// Тесты для Hexagon
TEST(HexagonTest, Area) {
    Hexagon<double> hex(h1, h2, h3, h4, h5, h6);
    double area = static_cast<double>(hex);
    // Приблизительная площадь этого шестиугольника
    EXPECT_GT(area, 2.5);
    EXPECT_LT(area, 3.0);
}

// Тесты для Array
TEST(ArrayTest, AddAndTotalArea) {
    Array<std::shared_ptr<Figure<double>>> arr;

    auto tri = std::make_shared<Triangle<double>>(t1, t2, t3);
    auto hex = std::make_shared<Hexagon<double>>(h1, h2, h3, h4, h5, h6);

    arr.add(std::move(tri));
    arr.add(std::move(hex));

    EXPECT_EQ(arr.getSize(), 2);
    double total = arr.totalArea();
    EXPECT_NEAR(total, 0.5 + static_cast<double>(*hex), 1e-3);
}

TEST(ArrayTest, Remove) {
    Array<std::shared_ptr<Figure<double>>> arr;

    auto t1_ptr = std::make_shared<Triangle<double>>(t1, t2, t3);
    auto t2_ptr = std::make_shared<Triangle<double>>(t1, t2, Point<double>(0, 2));

    arr.add(std::move(t1_ptr));
    arr.add(std::move(t2_ptr));

    EXPECT_EQ(arr.getSize(), 2);
    arr.remove(0);
    EXPECT_EQ(arr.getSize(), 1);

    double area = arr.totalArea();
    EXPECT_NEAR(area, 1.0, 1e-6); // второй треугольник: (0,0)-(1,0)-(0,2) → площадь = 1
}

// Тест клонирования
TEST(FigureTest, Clone) {
    Triangle<double> orig(t1, t2, t3);
    auto clone_ptr = orig.clone();
    Triangle<double>* cloned = dynamic_cast<Triangle<double>*>(clone_ptr.get());
    ASSERT_NE(cloned, nullptr);
    EXPECT_TRUE(orig == *cloned);
}