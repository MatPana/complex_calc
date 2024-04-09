#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <vector>
#include <string>
#include "CalculatorOperation.h"
#include "ComplexNumber.h"


/**
 * @brief Single calculation operation and its result.
 */
class HistoryEntry {
public:
    std::unique_ptr<CalculatorOperation> operation;
    ComplexNumber result;
    ComplexNumber operand1;
    ComplexNumber operand2;

    /**
     * @brief Constructs a new History Entry object.
     *
     * @param op - operation
     * @param res - result
     * @param op1 - first operand
     * @param op2 - second operand
     */
    HistoryEntry(std::unique_ptr<CalculatorOperation> op, ComplexNumber res, ComplexNumber op1, ComplexNumber op2)
        : operation(std::move(op)), result(res), operand1(op1), operand2(op2) {}
};


/**
 * @brief Remembers history of the calculator and navigates it.
 */
class HistoryManager {
public:
    void addOperation(std::unique_ptr<CalculatorOperation> operation, const ComplexNumber& result, const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr);

    std::string serializeHistory() const;
    void deserializeHistory(const std::string& serializedHistory);
    std::unique_ptr<CalculatorOperation> createOperation(const std::string& operationName) const;

    const HistoryEntry& getHistoryEntry(int index) const { return history.at(index); }
    int getHistorySize() const { return static_cast<int>(history.size()); }

    void saveHistoryToFile(const std::string& filePath) const;
    void loadHistoryFromFile(const std::string& filePath);

    void clearHistory();

private:
    std::vector<HistoryEntry> history;
};

#endif // HISTORYMANAGER_H
