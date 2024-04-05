#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

/**
 * @brief Class representing a complex number.
 *
 * This class provides functionalities for creating, manipulating, and performing
 * various operations on complex numbers.
 */
class ComplexNumber {
public:
    ComplexNumber(double a, double b);
    ~ComplexNumber();

    /** @brief The imaginary part of the complex number. */
    double getReal() const { return real; }

    /** @brief The imaginary part of the complex number. */
    double getImaginary() const { return imaginary; }

    /**
     * @brief Calculates the absolute value of the complex number.
     *
     * @return result (double).
    */
    double absoluteValue() const;

    /**
     * @brief Addition of complex numbers.
     *
     * @param other number to be added (const ComplexNumber&).
     * @return result (ComplexNumber).
    */
    ComplexNumber add(const ComplexNumber& other) const;

    /**
     * @brief Subtraction of complex numbers.
     *
     * @param other number to be subtracted (const ComplexNumber&).
     * @return result (ComplexNumber).
    */
    ComplexNumber subtract(const ComplexNumber& other) const;

    /**
     * @brief Multiplication of complex numbers.
     *
     * @param other number to be multiplied (const ComplexNumber&).
     * @return result (ComplexNumber).
    */
    ComplexNumber multiply(const ComplexNumber& other) const;

    /**
     * @brief Divides two complex numbers.
     *
     * @param other complex number to be divided by (const ComplexNumber&).
     * @throws std::invalid_argument If the divisor is zero.
     * @return result (ComplexNumber).
    */
    ComplexNumber divide(const ComplexNumber& other) const;

    /**
     * @brief Square root of the complex number.
     *
     * @return result (ComplexNumber).
     */
    ComplexNumber root() const;

    /**
     * @brief Inverse of a complex number.
     *
     * @return root value of the complex number (ComplexNumber).
     * @throws std::invalid_argument If the divisor is zero.
    */
    ComplexNumber inverse() const;

    /**
     * @brief Conjugate of a complex number.
     *
     * @return result (ComplexNumber).
     * @throws std::invalid_argument If the divisor is zero.
    */
    ComplexNumber conjugate() const;

private:
    // Real part.
    double real;
    // Imaginary part.
    double imaginary;
};

#endif // COMPLEXNUMBER_H

