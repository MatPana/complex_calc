#ifndef CALCULATOR_OPERATIONS_H
#define CALCULATOR_OPERATIONS_H

#include "complexnumber.h"
#include <memory>
#include <string>
#include <stdexcept>


/**
 * \brief Base class for calculator operations.
 */
class CalculatorOperation {
public:
    /**
     * \brief Virtual destructor.
     */
    virtual ~CalculatorOperation() = default;

    /**
     * \brief Performs operation (later like addition, multiplication).
     *
     * \param operand1  first operand.
     * \param operand2  second operand (optional)
     *
     * \return result
     */
    virtual ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const = 0;

    /**
     * \brief Serializes the operation into a string.
     *
     * \return string
     */
    virtual std::string serialize() const = 0;

    /**
     * \brief Checks if the operation is unary.
     *
     * \return bool - true if unary, false if binary
     */
    virtual bool isUnary() const = 0;

    /**
     * \brief Deserializes a string of an operation.
     */
    static std::unique_ptr<CalculatorOperation> deserialize(const std::string& serializedOperation);
};

/**
 * \brief Addition operation in a calculator.
 *
 * This class defines the addition operation, which requires two operands.
 */
class AdditionOperation : public CalculatorOperation {
public:
    /**
     * \brief Adds two complex numbers.
     *
     * \param operand1 - first operand (ComplexNumber)
     * \param operand2 - second operand (ComplexNumber)
     * \return result
     * \throws std::invalid_argument if second operand is not provided
     */
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 == nullptr) {
            throw std::invalid_argument("AdditionOperation requires two operands.");
        }
        return operand1.add(*operand2);
    }

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override {
        return "AdditionOperation";
    }

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return false
     */
    bool isUnary() const override { return false; }
};

/**
 * \brief Subtraction operation in a calculator.
 *
 * This class defines the subtraction operation, which requires two operands.
 */
class SubtractionOperation : public CalculatorOperation {
public:
    /**
     * \brief Subtract two complex numbers.
     *
     * \param operand1 - first operand (ComplexNumber)
     * \param operand2 - second operand (ComplexNumber)
     * \return result
     * \throws std::invalid_argument if second operand is not provided
     */
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 == nullptr) {
            throw std::invalid_argument("SubtractionOperation requires two operands.");
        }
        return operand1.subtract(*operand2);
    }

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override {
        return "SubtractionOperation";
    }

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return false
     */
    bool isUnary() const override { return false; }
};

/**
 * \brief Multiplication operation in a calculator.
 *
 * This class defines the multiplication operation, which requires two operands.
 */
class MultiplicationOperation : public CalculatorOperation {
public:
    /**
     * \brief Multiplies two complex numbers.
     *
     * \param operand1 - first operand (ComplexNumber)
     * \param operand2 - second operand (ComplexNumber)
     * \return result
     * \throws std::invalid_argument if second operand is not provided
     */
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 == nullptr) {
            throw std::invalid_argument("MultiplicationOperation requires two operands.");
        }
        return operand1.multiply(*operand2);
    }

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override {
        return "MultiplicationOperation";
    }

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return false
     */
    bool isUnary() const override { return false; }
};

/**
 * \brief Division operation in a calculator.
 *
 * This class defines the division operation, which requires two operands.
 */
class DivisionOperation : public CalculatorOperation {
public:
    /**
     * \brief Divided first operand by the second one.
     *
     * Doesn't check for zero as the second operand as ComplexNumber already checks it.
     *
     * \param operand1 - first operand (ComplexNumber)
     * \param operand2 - second operand (ComplexNumber)
     * \return result
     * \throws std::invalid_argument if second operand is not provided
     */
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 == nullptr) {
            throw std::invalid_argument("DivisionOperation requires two operands.");
        }
        // Division by zero throws error higher.
        return operand1.divide(*operand2);
    }

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override {
        return "DivisionOperation";
    }

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return false
     */
    bool isUnary() const override { return false; }
};

/**
 * \brief Conjugate operation in a calculator.
 *
 * This class defines the conjugate operation.
 */
class ConjugateOperation : public CalculatorOperation {
public:
    /**
     * \brief Calculates the conjugate of a ComplexNumber.
     *
     *
     * \param operand1 - complex number to calculate absolute value
     * \param operand2 - not used, defaults to nullptr.
     * \return result
     */
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        return operand1.conjugate();
    }

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override {
        return "ConjugateOperation";
    }

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return true
     */
    bool isUnary() const override { return true; }
};

/**
 * \brief Absolute value operation in a calculator.
 *
 * This class defines the absolute value operation.
 */
class AbsoluteValueOperation : public CalculatorOperation {
public:

    /**
     * \brief Calculates the absolute value of a ComplexNumber.
     *
     * \param operand1 - complex number to calculate absolute value
     * \param operand2 - not used, defaults to nullptr.
     * \return result
     */
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        double absValue = operand1.absoluteValue();
        return ComplexNumber(absValue, 0);
    }

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override {
        return "AbsoluteValueOperation";
    }

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return true
     */
    bool isUnary() const override { return true; }
};

/**
 * \brief Square value operation in a calculator.
 *
 * This class defines the square value operation.
 */
class SquareOperation : public CalculatorOperation {
public:
    /**
     * \brief Calculates the square value of a ComplexNumber.
     *
     * \param operand1 - complex number to calculate square value
     * \param operand2 - not used, defaults to nullptr.
     * \return result
     */
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        return operand1.square();
    }

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override {
        return "SquareOperation";
    }

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return true
     */
    bool isUnary() const override { return true; }
};

/**
 * \brief Root value operation in a calculator.
 *
 * This class defines the root value operation.
 */
class RootOperation : public CalculatorOperation {
public:
    /**
     * \brief Calculates the root value of a ComplexNumber.
     *
     *
     * \param operand1 - complex number to calculate root value
     * \param operand2 - not used, defaults to nullptr.
     * \return result
     */
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        return operand1.root();
    }

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override {
        return "RootOperation";
    }

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return true
     */
    bool isUnary() const override { return true; }
};

/**
 * \brief Inverse value operation in a calculator.
 *
 * This class defines the inverse value operation.
 */
class InverseOperation : public CalculatorOperation {
public:
    /**
     * \brief Calculates the inverse value of a ComplexNumber.
     *
     *
     * \param operand1 - complex number to calculate inverse value
     * \param operand2 - not used, defaults to nullptr.
     * \return result
     */
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override {
        if (operand2 != nullptr) {
            throw std::invalid_argument("InverseOperation does not require a second operand.");
        }
        return operand1.inverse();
    }

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override {
        return "InverseOperation";
    }

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return true
     */
    bool isUnary() const override { return true; }
};

/**
 * \brief Deserializes a string operation into a unique pointer to a CalculatorOperation.
 *
 * \param serializedOperation - string representing operation
 * \return std::unique_ptr to a CalculatorOperation, nullptr if no operation found
 */
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
