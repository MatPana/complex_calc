#ifndef SHAPE_H
#define SHAPE_H

#include <stdexcept>

/**
 * @brief Base class representing a geometric shape.
 *
 * This abstract base class defines the interface for shapes.
 */
class Shape {
public:
    /**
   * @brief Constructor for the Shape class with input validation.
   *
   * @param value value representing the shape (double).
   */
    Shape(double value) {
        if (value <= 0.0) {
            throw std::invalid_argument("Value cannot be zero or negative!");
        }
    }
    virtual ~Shape() = default;

    /**
   * @brief Calculates the area of the shape - virtual function to be overwritten.
   *
   * @return The calculated area of the shape as a double.
   */
    virtual double calculateArea() const = 0;

    /**
   * @brief Calculates the area of the shape - virtual function to be overwritten.
   *
   * @return The calculated area of the shape as a double.
   */
    virtual double calculateCircumference() const = 0;

};


/**
 * @brief Class representing a circle.
 *
 *Additionally shows polymorphism.
 */
class Circle : public Shape {
public:
    Circle(double radius) : Shape(radius), _radius(radius) {}

    /**
   * @brief Calculates the area of circle.
   *
   * @return area of the shape as a double.
   */
    double calculateArea() const override final {
        return 3.14 * _radius * _radius;
    }

    /**
   * @brief Calculates the circumference of circle.
   *
   * @return circumference of the shape as a double.
   */
    double calculateCircumference() const override final {
        return 2 * 3.14 * _radius;
    }

private:
    double _radius;
};

/**
 * @brief Class representing a triangle.
 *
 *Additionally shows polymorphism.
 */
class Triangle : public Shape {
public:
    Triangle(double side) : Shape(side), _side(side) {}

    /**
   * @brief Calculates the area of triangle.
   *
   * @return area of the shape as a double.
   */
    double calculateArea() const override final {
        // Formula for area of equilateral triangle
        const double sqrt3 = 1.732;  // Approximate value of square root of 3
        return sqrt3 * _side * _side / 4.0;
    }

    /**
   * @brief Calculates the circumference of triangle.
   *
   * @return circumference of the shape as a double.
   */
    double calculateCircumference() const override final {
        return 3 * _side;
    }

private:
    double _side;
};

#endif  // SHAPE_H
