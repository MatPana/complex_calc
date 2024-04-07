#include <cmath>
#include <stdexcept>
#include "complexnumber.h"

/**
 * @brief Default constructor.
 */
ComplexNumber::ComplexNumber(double a, double b) : real(a), imaginary(b) {}
ComplexNumber::ComplexNumber() : real(0), imaginary(0) {}

/**
 * @brief Default destructor.
 */
ComplexNumber::~ComplexNumber() {}

// Template for operations
template <typename Operation>
ComplexNumber performOperation(const ComplexNumber& a, const ComplexNumber& b) {
    Operation op;
    return (a.*op)(b);
}

void ComplexNumber::setReal(double value) {
    this->real = value;
};

void ComplexNumber::setImaginary(double value) {
    this->imaginary = value;
};

/**
 * @brief Addition.
 *
 * @param other the complex number to be added.
 * @return sum of the two complex numbers (ComplexNumber).
 */
ComplexNumber ComplexNumber::add(const ComplexNumber& other) const {
    return ComplexNumber(real + other.real, imaginary + other.imaginary);
}

/**
 * @brief Subtraction.
 *
 * @param other the complex number to be subtracted.
 * @return subtraction of the two complex numbers (ComplexNumber).
 */
ComplexNumber ComplexNumber::subtract(const ComplexNumber& other) const {
    return ComplexNumber(real - other.real, imaginary - other.imaginary);
}

/**
 * @brief Multiplication.
 *
 * @param other the complex number to be multiplied.
 * @return mltiplication of the two complex numbers (ComplexNumber).
 */
ComplexNumber ComplexNumber::multiply(const ComplexNumber& other) const {
    return ComplexNumber(real * other.real - imaginary * other.imaginary,
                         real * other.imaginary + imaginary * other.real);
}

/**
 * @brief Division.
 *
 * @param other the complex number - divisor.
 * @return division of the two complex numbers (ComplexNumber).
 * @throws std::invalid_argument If the divisor is zero.
 */
ComplexNumber ComplexNumber::divide(const ComplexNumber& other) const {
    if (other.real == 0 && other.imaginary == 0) {
        throw std::invalid_argument("Division by zero!");
    }

    const double denominator = other.real * other.real + other.imaginary * other.imaginary;
    return ComplexNumber((real * other.real + imaginary * other.imaginary) / denominator,
                         (imaginary * other.real - real * other.imaginary) / denominator);
}



/**
 * @brief Aabsolute value of a complex number.
 *
 * @return absolute value of the complex number (double).
 */
double ComplexNumber::absoluteValue() const {
    double absValue = std::sqrt(real * real + imaginary * imaginary);
    return absValue;
}

/**
 * @brief Square a complex number.
 *
 * @return square of the complex number (ComplexNumber).
 */
ComplexNumber ComplexNumber::square() const {
    return this->add(*this);
}

/**
 * @brief Root of a complex number.
 *
 * @return root value of the complex number (ComplexNumber).
 */
ComplexNumber ComplexNumber::root() const {
    double absValue = absoluteValue();
    double newReal = std::sqrt((absValue + real) / 2);

    double norm = (imaginary >= 0) ? 1 : ((imaginary < 0) ? -1 : 1);
    double newImaginary = norm * std::sqrt((absValue - real) / 2);

    return ComplexNumber(newReal, newImaginary);
}

/**
 * @brief Inverse of a complex number.
 *
 * @return root value of the complex number (ComplexNumber).
 * @throws std::invalid_argument If the divisor is zero.
 */
ComplexNumber ComplexNumber::inverse() const {
    double denominator = real * real + imaginary * imaginary;
    if (denominator == 0) {
        throw std::invalid_argument("Division by zero!");
    }
    double invReal = real / denominator;
    double invImag = -imaginary / denominator;
    return ComplexNumber(invReal, invImag);
}

/**
 * @brief Conjugate of a complex number.
 *
 * @return conjugate value of the complex number (ComplexNumber).
 */
ComplexNumber ComplexNumber::conjugate() const {
    return ComplexNumber(real, -imaginary);
}
