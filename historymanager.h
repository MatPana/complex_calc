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
    /**
     * @brief Adds a new operation to the history.
     *
     * @param operation
     * @param result
     * @param operand1 - first operand
     * @param operand2 - second operand (optional)
     */
    void addOperation(std::unique_ptr<CalculatorOperation> operation, const ComplexNumber& result, const ComplexNumber& operand1, const ComplexNumber* operand2 = nullptr);

    /**
     * @brief Serializes the operation history into a string.
     *
     * @return std::string - serialized history.
     */
    std::string serializeHistory() const;

    /**
     * @brief Turns string into parsed history.
     *
     * @param serializedHistory - serialized history (string)
     */
    void deserializeHistory(const std::string& serializedHistory);

    /**
     * @brief Creates operationt based on its name.
     *
     * @param operationName - name of the operation
     * @return operation object
     */
    std::unique_ptr<CalculatorOperation> createOperation(const std::string& operationName) const;

    /**
     * @brief Retrieves a history entry by its index.
     *
     * @param index - index of the history entry to retrieve
     * @return reference to the HistoryEntry
     */
    const HistoryEntry& getHistoryEntry(int index) const { return history.at(index); }

    /**
     * @brief Gets the number of operations stored in history.
     *
     * @return number of operations in history (int)
     */
    int getHistorySize() const { return static_cast<int>(history.size()); }

    /**
     * @brief Saves history to a file.
     *
     * @param filePath - path to the file
     */
    void saveHistoryToFile(const std::string& filePath) const;

    /**
     * @brief Reads history from a file.
     *
     * @param filePath - path to the file
     */
    void loadHistoryFromFile(const std::string& filePath);

    /**
     * @brief Clears operation history.
     */
    void clearHistory();

private:
    std::vector<HistoryEntry> history;
};

#endif // HISTORYMANAGER_H
