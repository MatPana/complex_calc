#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <vector>
#include <string>
#include "CalculatorOperation.h"
#include "ComplexNumber.h"

class HistoryEntry {
public:
    std::unique_ptr<CalculatorOperation> operation;
    ComplexNumber result;
    ComplexNumber operand1;
    ComplexNumber operand2;

    HistoryEntry(std::unique_ptr<CalculatorOperation> op, ComplexNumber res, ComplexNumber op1, ComplexNumber op2)
        : operation(std::move(op)), result(res), operand1(op1), operand2(op2) {}
};

class HistoryManager {
public:
    void addOperation(std::unique_ptr<CalculatorOperation> operation, const ComplexNumber& result, const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr);
    std::string serializeHistory() const;
    void deserializeHistory(const std::string& serializedHistory);
    std::unique_ptr<CalculatorOperation> createOperation(const std::string& operationName) const;
    const HistoryEntry& getHistoryEntry(int index) const { return history.at(index); }
    int getHistorySize() const { return static_cast<int>(history.size()); }

private:
    std::vector<HistoryEntry> history;
};

#endif // HISTORYMANAGER_H
