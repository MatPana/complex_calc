#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H


class ComplexNumber {
public:
    ComplexNumber(double a, double b);
    ~ComplexNumber();

    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    double absoluteValue() const;

    ComplexNumber add(const ComplexNumber& other) const;

    ComplexNumber subtract(const ComplexNumber& other) const;

    ComplexNumber multiply(const ComplexNumber& other) const;

    ComplexNumber divide(const ComplexNumber& other) const;

    ComplexNumber root() const;

    ComplexNumber inverse();

    ComplexNumber conjugate() const;

private:
    double real;
    double imaginary;
};

#endif // COMPLEXNUMBER_H

