#include <cmath>
#include <stdexcept>
#include "ComplexNumber.h"


ComplexNumber::ComplexNumber(double a, double b) : real(a), imaginary(b) {}

ComplexNumber::~ComplexNumber() {}

template <typename Operation>
ComplexNumber performOperation(const ComplexNumber& a, const ComplexNumber& b) {
    Operation op;
    return (a.*op)(b);
}

ComplexNumber ComplexNumber::add(const ComplexNumber& other) const {
    return ComplexNumber(real + other.real, imaginary + other.imaginary);
}

ComplexNumber ComplexNumber::subtract(const ComplexNumber& other) const {
    return ComplexNumber(real - other.real, imaginary - other.imaginary);
}

ComplexNumber ComplexNumber::multiply(const ComplexNumber& other) const {
    return ComplexNumber(real * other.real - imaginary * other.imaginary,
                         real * other.imaginary + imaginary * other.real);
}

ComplexNumber ComplexNumber::divide(const ComplexNumber& other) const {
    if (other.real == 0 && other.imaginary == 0) {
        throw std::invalid_argument("Division by zero!");
    }

    const double denominator = other.real * other.real + other.imaginary * other.imaginary;
    return ComplexNumber((real * other.real + imaginary * other.imaginary) / denominator,
                         (imaginary * other.real - real * other.imaginary) / denominator);
}

double ComplexNumber::absoluteValue() const {
    double absValue = std::sqrt(real * real + imaginary * imaginary);
    return absValue;
}

ComplexNumber ComplexNumber::root() const {
    double absValue = absoluteValue();
    double newReal = std::sqrt((absValue + real) / 2);

    double norm = (imaginary >= 0) ? 1 : ((imaginary < 0) ? -1 : 1);
    double newImaginary = norm * std::sqrt((absValue - real) / 2);

    return ComplexNumber(newReal, newImaginary);
}

ComplexNumber ComplexNumber::inverse() const {
    double denominator = real * real + imaginary * imaginary;
    if (denominator == 0) {
        throw std::invalid_argument("Division by zero!");
    }
    double invReal = real / denominator;
    double invImag = -imaginary / denominator;
    return ComplexNumber(invReal, invImag);
}

ComplexNumber ComplexNumber::conjugate() const {
    return ComplexNumber(real, -imaginary);
}

