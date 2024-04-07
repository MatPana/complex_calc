#ifndef CALCULATOR_OPERATIONS_H
#define CALCULATOR_OPERATIONS_H

#include "complexnumber.h"
#include <memory>
#include <string>
#include <stdexcept>



class CalculatorOperation {
public:
    virtual ~CalculatorOperation() = default;
    virtual ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const = 0;
    virtual std::string serialize() const = 0;
    virtual bool isUnary() const = 0;

    static std::unique_ptr<CalculatorOperation> deserialize(const std::string& serializedOperation);
};


class AdditionOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 == nullptr) {
            throw std::invalid_argument("AdditionOperation requires two operands.");
        }
        return operand1.add(*operand2);
    }

    std::string serialize() const override {
        return "AdditionOperation";
    }

    bool isUnary() const override { return false; }
};


class SubtractionOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 == nullptr) {
            throw std::invalid_argument("SubtractionOperation requires two operands.");
        }
        return operand1.subtract(*operand2);
    }

    std::string serialize() const override {
        return "SubtractionOperation";
    }

    bool isUnary() const override { return false; }
};

class MultiplicationOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 == nullptr) {
            throw std::invalid_argument("MultiplicationOperation requires two operands.");
        }
        return operand1.multiply(*operand2);
    }

    std::string serialize() const override {
        return "MultiplicationOperation";
    }

    bool isUnary() const override { return false; }
};


class DivisionOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 == nullptr) {
            throw std::invalid_argument("DivisionOperation requires two operands.");
        }
        // Division by zero throws error higher.
        return operand1.divide(*operand2);
    }

    std::string serialize() const override {
        return "DivisionOperation";
    }

    bool isUnary() const override { return false; }
};


class ConjugateOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        return operand1.conjugate();
    }
    std::string serialize() const override {
        return "ConjugateOperation";
    }

    bool isUnary() const override { return true; }
};


class AbsoluteValueOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        double absValue = operand1.absoluteValue();
        return ComplexNumber(absValue, 0);
    }

    std::string serialize() const override {
        return "AbsoluteValueOperation";
    }

    bool isUnary() const override { return true; }
};

class SquareOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        return operand1.square();
    }

    std::string serialize() const override {
        return "SquareOperation";
    }

    bool isUnary() const override { return true; }
};

class RootOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        return operand1.root();
    }

    std::string serialize() const override {
        return "RootOperation";
    }

    bool isUnary() const override { return true; }
};

class InverseOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 != nullptr) {
            throw std::invalid_argument("InverseOperation does not require a second operand.");
        }
        return operand1.inverse();
    }

    std::string serialize() const override {
        return "InverseOperation";
    }

    bool isUnary() const override { return true; }
};

std::unique_ptr<CalculatorOperation> CalculatorOperation::deserialize(const std::string& serializedOperation) {
    if (serializedOperation == "AdditionOperation") {
        return std::make_unique<AdditionOperation>();
    } else if (serializedOperation == "SubtractionOperation") {
        return std::make_unique<SubtractionOperation>();
    } else if (serializedOperation == "MultiplicationOperation") {
        return std::make_unique<MultiplicationOperation>();
    } else if (serializedOperation == "DivisionOperation") {
        return std::make_unique<DivisionOperation>();
    } else if (serializedOperation == "ConjugateOperation") {
        return std::make_unique<ConjugateOperation>();
    } else if (serializedOperation == "AbsoluteValueOperation") {
        return std::make_unique<AbsoluteValueOperation>();
    } else if (serializedOperation == "RootOperation") {
        return std::make_unique<RootOperation>();
    } else if (serializedOperation == "InverseOperation") {
        return std::make_unique<InverseOperation>();
    } else if (serializedOperation == "SquareOperation") {
        return std::make_unique<SquareOperation>();
    }


    return nullptr;
}


#endif // CALCULATOR_OPERATIONS_H
