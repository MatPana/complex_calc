#include "historymanager.h"
#include <sstream>

void HistoryManager::addOperation(std::unique_ptr<CalculatorOperation> operation, const ComplexNumber& operand1, const ComplexNumber* operand2) {
    if (operand2) {
        history.emplace_back(std::move(operation), operand1, *operand2);
    } else {
        // ComplexNumber(0, 0) won't be used for unary.
        history.emplace_back(std::move(operation), operand1, ComplexNumber(0, 0));
    }
}

std::string HistoryManager::serializeHistory() const {
    std::ostringstream oss;
    for (const auto& entry : history) {
        oss << entry.operation->serialize() << ":";
        oss << entry.operand1.getReal() << "+" << entry.operand1.getImaginary() << "i";
        if (!entry.operation->isUnary()) {
            oss << "," << entry.operand2.getReal() << "+" << entry.operand2.getImaginary() << "i";
        }
        oss << ";"; // End of this operation entry
    }
    std::string result = oss.str();
    if (!result.empty()) {
        result.pop_back(); // Remove the trailing semicolon
    }
    return result;
}

void HistoryManager::deserializeHistory(const std::string& serializedHistory) {
    std::istringstream stream(serializedHistory);
    std::string entry;

    history.clear(); // Clear existing history

    while (std::getline(stream, entry, ';')) {
        std::istringstream entryStream(entry);
        std::string operationName, operandStr;
        std::getline(entryStream, operationName, ':');
        std::getline(entryStream, operandStr);

        ComplexNumber operand1, operand2;
        std::istringstream operandStream(operandStr);

        double real1, imag1, real2, imag2;
        char delimiter;
        operandStream >> real1 >> delimiter >> imag1;
        operand1.setReal(real1);
        operand1.setImaginary(imag1);

        if (operandStream >> delimiter && delimiter == ',') {
            operandStream >> real2 >> delimiter >> imag2;
            operand2.setReal(real2);
            operand2.setImaginary(imag2);
        }

        std::unique_ptr<CalculatorOperation> operation = createOperation(operationName);
        if (operation) {
            bool isOperand2Set = operand2.getReal() != 0 || operand2.getImaginary() != 0;
            addOperation(std::move(operation), operand1, isOperand2Set ? &operand2 : nullptr);
        }
    }
}

std::unique_ptr<CalculatorOperation> HistoryManager::createOperation(const std::string& operationName) const {
    if (operationName == "AdditionOperation") {
        return std::make_unique<AdditionOperation>();
    } else if (operationName == "SubtractionOperation") {
        return std::make_unique<SubtractionOperation>();
    } else if (operationName == "MultiplicationOperation") {
        return std::make_unique<MultiplicationOperation>();
    } else if (operationName == "DivisionOperation") {
        return std::make_unique<DivisionOperation>();
    } else if (operationName == "ConjugateOperation") {
        return std::make_unique<ConjugateOperation>();
    } else if (operationName == "AbsoluteValueOperation") {
        return std::make_unique<AbsoluteValueOperation>();
    } else if (operationName == "RootOperation") {
        return std::make_unique<RootOperation>();
    } else if (operationName == "InverseOperation") {
        return std::make_unique<InverseOperation>();
    }

    return nullptr;
}
