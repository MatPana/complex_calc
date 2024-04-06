#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <vector>
#include <string>
#include "CalculatorOperation.h"
#include "ComplexNumber.h"

class HistoryEntry {
public:
    std::unique_ptr<CalculatorOperation> operation;
    ComplexNumber operand1;
    ComplexNumber operand2;

    HistoryEntry(std::unique_ptr<CalculatorOperation> op, ComplexNumber op1, ComplexNumber op2)
        : operation(std::move(op)), operand1(op1), operand2(op2) {}
};

class HistoryManager {
public:
    void addOperation(std::unique_ptr<CalculatorOperation> operation, const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr);
    std::string serializeHistory() const;
    void deserializeHistory(const std::string& serializedHistory);
    std::unique_ptr<CalculatorOperation> createOperation(const std::string& operationName) const;

private:
    std::vector<HistoryEntry> history;
};

#endif // HISTORYMANAGER_H
