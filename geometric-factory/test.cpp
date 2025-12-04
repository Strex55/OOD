#include "gtest/gtest.h"
#include "pch.h"
#include "CPoint.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "ShapeFactory.h"
#include "Functions.h"
#include "FileShapeParser.h"
#include <memory>
#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>

// Тесты для новой фабрики с SFML точками
TEST(ShapeFactoryTest, CreateTriangleFromPoints) {
    ShapeFactory factory;
    std::vector<sf::Vector2f> points = {
        sf::Vector2f(0, 0),
        sf::Vector2f(3, 0),
        sf::Vector2f(0, 4)
    };
    auto shape = factory.CreateShape("TRIANGLE", points);
    ASSERT_NE(shape, nullptr);
    EXPECT_DOUBLE_EQ(shape->GetArea(), 6.0);
    EXPECT_DOUBLE_EQ(shape->GetPerimeter(), 12.0);
}

TEST(ShapeFactoryTest, CreateRectangleFromPoints) {
    ShapeFactory factory;
    std::vector<sf::Vector2f> points = {
        sf::Vector2f(0, 0),
        sf::Vector2f(5, 3)
    };
    auto shape = factory.CreateShape("RECTANGLE", points);
    ASSERT_NE(shape, nullptr);
    EXPECT_DOUBLE_EQ(shape->GetArea(), 15.0);
    EXPECT_DOUBLE_EQ(shape->GetPerimeter(), 16.0);
}

TEST(ShapeFactoryTest, CreateCircleFromPoints) {
    ShapeFactory factory;
    std::vector<sf::Vector2f> points = { sf::Vector2f(0, 0) };
    auto shape = factory.CreateShape("CIRCLE", points, 5.0);
    ASSERT_NE(shape, nullptr);
    EXPECT_NEAR(shape->GetArea(), 78.54, 0.01);
    EXPECT_NEAR(shape->GetPerimeter(), 31.42, 0.01);
}

TEST(ShapeFactoryTest, InvalidShapeType) {
    ShapeFactory factory;
    std::vector<sf::Vector2f> points = { sf::Vector2f(0, 0) };
    auto shape = factory.CreateShape("INVALID", points);
    EXPECT_EQ(shape, nullptr);
}

TEST(ShapeFactoryTest, CaseInsensitiveTypes) {
    ShapeFactory factory;
    std::vector<sf::Vector2f> points = {
        sf::Vector2f(0, 0),
        sf::Vector2f(3, 0),
        sf::Vector2f(0, 4)
    };

    auto shape1 = factory.CreateShape("triangle", points);
    auto shape2 = factory.CreateShape("TRIANGLE", points);
    auto shape3 = factory.CreateShape("Triangle", points);

    ASSERT_NE(shape1, nullptr);
    ASSERT_NE(shape2, nullptr);
    ASSERT_NE(shape3, nullptr);

    EXPECT_DOUBLE_EQ(shape1->GetArea(), 6.0);
    EXPECT_DOUBLE_EQ(shape2->GetArea(), 6.0);
    EXPECT_DOUBLE_EQ(shape3->GetArea(), 6.0);
}

// Тесты для парсера файлов
TEST(FileParserTest, ParseTriangleLine) {
    std::string line = "TRIANGLE: P1=100,100; P2=200,200; P3=150,150";
    auto shapeData = FileShapeParser::ParseLine(line);

    EXPECT_EQ(shapeData.type, "TRIANGLE");
    EXPECT_EQ(shapeData.points.size(), 3);
    EXPECT_FLOAT_EQ(shapeData.points[0].x, 100);
    EXPECT_FLOAT_EQ(shapeData.points[0].y, 100);
    EXPECT_FLOAT_EQ(shapeData.points[1].x, 200);
    EXPECT_FLOAT_EQ(shapeData.points[1].y, 200);
    EXPECT_FLOAT_EQ(shapeData.points[2].x, 150);
    EXPECT_FLOAT_EQ(shapeData.points[2].y, 150);
}

TEST(FileParserTest, ParseRectangleLine) {
    std::string line = "RECTANGLE: P1=200,200; P2=300,300";
    auto shapeData = FileShapeParser::ParseLine(line);

    EXPECT_EQ(shapeData.type, "RECTANGLE");
    EXPECT_EQ(shapeData.points.size(), 2);
    EXPECT_FLOAT_EQ(shapeData.points[0].x, 200);
    EXPECT_FLOAT_EQ(shapeData.points[0].y, 200);
    EXPECT_FLOAT_EQ(shapeData.points[1].x, 300);
    EXPECT_FLOAT_EQ(shapeData.points[1].y, 300);
}

TEST(FileParserTest, ParseCircleLine) {
    std::string line = "CIRCLE: C=100,100; R=50";
    auto shapeData = FileShapeParser::ParseLine(line);

    EXPECT_EQ(shapeData.type, "CIRCLE");
    EXPECT_EQ(shapeData.points.size(), 1);
    EXPECT_FLOAT_EQ(shapeData.points[0].x, 100);
    EXPECT_FLOAT_EQ(shapeData.points[0].y, 100);
    EXPECT_FLOAT_EQ(shapeData.radius, 50);
}

TEST(FileParserTest, ParseInvalidLine) {
    EXPECT_THROW(FileShapeParser::ParseLine("INVALID: format"), std::runtime_error);
    EXPECT_THROW(FileShapeParser::ParseLine("TRIANGLE: invalid"), std::runtime_error);
}

// Существующие тесты для классов фигур (остаются без изменений)
TEST(CPointTest, ConstructorAndGetters) {
    CPoint point(3.5, 4.2);
    EXPECT_DOUBLE_EQ(point.GetX(), 3.5);
    EXPECT_DOUBLE_EQ(point.GetY(), 4.2);
}

TEST(CPointTest, DifferentValues) {
    CPoint point(-2.1, 0.0);
    EXPECT_DOUBLE_EQ(point.GetX(), -2.1);
    EXPECT_DOUBLE_EQ(point.GetY(), 0.0);
}

TEST(CLineSegmentTest, Properties) {
    CLineSegment line(CPoint(0, 0), CPoint(3, 4), 0xFF0000);
    EXPECT_DOUBLE_EQ(line.GetPerimeter(), 5.0);
    EXPECT_DOUBLE_EQ(line.GetArea(), 0.0);
    EXPECT_EQ(line.GetOutlineColor(), 0xFF0000);

    CPoint start = line.GetStartPoint();
    CPoint end = line.GetEndPoint();
    EXPECT_DOUBLE_EQ(start.GetX(), 0.0);
    EXPECT_DOUBLE_EQ(start.GetY(), 0.0);
    EXPECT_DOUBLE_EQ(end.GetX(), 3.0);
    EXPECT_DOUBLE_EQ(end.GetY(), 4.0);
}

TEST(CTriangleTest, AreaAndPerimeter) {
    CTriangle triangle(CPoint(0, 0), CPoint(3, 0), CPoint(0, 4), 0xFF0000, 0x00FF00);
    EXPECT_DOUBLE_EQ(triangle.GetArea(), 6.0);
    EXPECT_DOUBLE_EQ(triangle.GetPerimeter(), 12.0);
    EXPECT_EQ(triangle.GetOutlineColor(), 0xFF0000);
    EXPECT_EQ(triangle.GetFillColor(), 0x00FF00);
}

TEST(CRectangleTest, Properties) {
    CRectangle rect(CPoint(10, 20), 30, 40, 0xAABBCC, 0xDDEEFF);
    EXPECT_DOUBLE_EQ(rect.GetArea(), 1200.0);
    EXPECT_DOUBLE_EQ(rect.GetPerimeter(), 140.0);
    EXPECT_EQ(rect.GetOutlineColor(), 0xAABBCC);
    EXPECT_EQ(rect.GetFillColor(), 0xDDEEFF);
}

TEST(CCircleTest, Calculations) {
    CCircle circle(CPoint(0, 0), 10, 0x112233, 0x445566);
    EXPECT_NEAR(circle.GetArea(), 314.16, 0.01);
    EXPECT_NEAR(circle.GetPerimeter(), 62.83, 0.01);
    EXPECT_EQ(circle.GetOutlineColor(), 0x112233);
    EXPECT_EQ(circle.GetFillColor(), 0x445566);
}

// Тесты для функций поиска (остаются без изменений)
TEST(FindShapeTest, FindShapeWithMaxArea) {
    std::vector<std::unique_ptr<IShape>> shapes;
    shapes.push_back(std::make_unique<CCircle>(CPoint(0, 0), 1, 0xFF0000, 0x00FF00));
    shapes.push_back(std::make_unique<CCircle>(CPoint(0, 0), 5, 0xFF0000, 0x00FF00));

    auto maxAreaShape = MaxArea(shapes);
    ASSERT_NE(maxAreaShape, nullptr);
    EXPECT_NEAR(maxAreaShape->GetArea(), 78.54, 0.01);
}

TEST(FindShapeTest, FindShapeWithMinPerimeter) {
    std::vector<std::unique_ptr<IShape>> shapes;
    shapes.push_back(std::make_unique<CLineSegment>(CPoint(0, 0), CPoint(10, 0), 0xFF0000));
    shapes.push_back(std::make_unique<CLineSegment>(CPoint(0, 0), CPoint(2, 0), 0xFF0000));

    auto minPerimeterShape = MinPerimeter(shapes);
    ASSERT_NE(minPerimeterShape, nullptr);
    EXPECT_DOUBLE_EQ(minPerimeterShape->GetPerimeter(), 2.0);
}

TEST(FindShapeTest, EmptyVector) {
    std::vector<std::unique_ptr<IShape>> shapes;

    auto maxAreaShape = MaxArea(shapes);
    EXPECT_EQ(maxAreaShape, nullptr);

    auto minPerimeterShape = MinPerimeter(shapes);
    EXPECT_EQ(minPerimeterShape, nullptr);
}