#ifndef CALCULATOR_OPERATIONS_H
#define CALCULATOR_OPERATIONS_H

#include "ComplexNumber.h"
#include <memory>
#include <string>
#include <stdexcept>



class CalculatorOperation {
public:
    virtual ~CalculatorOperation() = default;
    virtual ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const = 0;
    virtual std::string serialize() const = 0;
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
};


class ConjugateOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        return operand1.conjugate();
    }
    std::string serialize() const override {
        return "ConjugateOperation";
    }
};


class AbsoluteValueOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 != nullptr) {
            throw std::invalid_argument("AbsoluteValueOperation does not require a second operand.");
        }
        double absValue = operand1.absoluteValue();
        return ComplexNumber(absValue, 0);
    }

    std::string serialize() const override {
        return "AbsoluteValueOperation";
    }
};

class SquareOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        return operand1.square();
    }

    std::string serialize() const override {
        return "SquareOperation";
    }
};

class RootOperation : public CalculatorOperation {
public:
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 != nullptr) {
            throw std::invalid_argument("RootOperation does not require a second operand.");
        }
        return operand1.root();
    }

    std::string serialize() const override {
        return "RootOperation";
    }
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
    }

    return nullptr;
}


#endif // CALCULATOR_OPERATIONS_H
