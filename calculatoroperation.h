#ifndef CALCULATOROPERATION_H
#define CALCULATOROPERATION_H

#include <string>
#include <memory>
#include "ComplexNumber.h"


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
    virtual ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2) const = 0;

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
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override;

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return false
     */
    bool isUnary() const override;
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
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override;

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return false
     */
    bool isUnary() const override;
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
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override;

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return false
     */
    bool isUnary() const override;
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
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override;

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return false
     */
    bool isUnary() const override;
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
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override;

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return true
     */
    bool isUnary() const override;
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
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override;

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return true
     */
    bool isUnary() const override;
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
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override;

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return true
     */
    bool isUnary() const override;
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
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override;

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return true
     */
    bool isUnary() const override;
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
    ComplexNumber performOperation(const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr) const override;

    /**
     * \brief Serializes the operation into a string.
     *
     * \return serialised string
     */
    std::string serialize() const override;

    /**
     * \brief Shows that addition needs two operands.
     *
     * \return true
     */
    bool isUnary() const override;
};

#endif // CALCULATOROPERATION_H
