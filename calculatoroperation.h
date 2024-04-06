#ifndef CALCULATOROPERATION_H
#define CALCULATOROPERATION_H

#include <string>
#include <memory>
#include "ComplexNumber.h"

class CalculatorOperation {
public:
    virtual ~CalculatorOperation() = default;
    virtual ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2) const = 0;
    virtual std::string serialize() const = 0;

    static std::unique_ptr<CalculatorOperation> deserialize(const std::string& serializedOperation);
};

class AdditionOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;
    std::string serialize() const override;
};

class SubtractionOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;
    std::string serialize() const override;
};

class MultiplicationOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;
    std::string serialize() const override;
};

class DivisionOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;
    std::string serialize() const override;
};

class ConjugateOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;
    std::string serialize() const override;
};

class AbsoluteValueOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;
    std::string serialize() const override;
};

class SquareOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;
    std::string serialize() const override;
};


class RootOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;
    std::string serialize() const override;
};

class InverseOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;
    std::string serialize() const override;
};

#endif // CALCULATOROPERATION_H
