#include "historymanager.h"
#include <sstream>

void HistoryManager::addOperation(std::unique_ptr<CalculatorOperation> operation, const ComplexNumber& result, const ComplexNumber& operand1, const ComplexNumber* operand2) {
    // Need to use move, as unique_ptr can't be copied.
    if (operand2) {
        history.emplace_back(std::move(operation), result, operand1, *operand2);
    } else {
        history.emplace_back(std::move(operation), result, operand1, ComplexNumber(0, 0));
    }
}

std::string HistoryManager::serializeHistory() const {
    std::ostringstream oss;
    // For each element in history.
    for (const auto& entry : history) {
        // "operation:a+bi;" if unary, "operation:a+bi,c+di;" if binary.
        oss << entry.operation->serialize() << ":";
        oss << entry.result.getReal() << "+" << entry.result.getImaginary() << "i";
        oss << entry.operand1.getReal() << "+" << entry.operand1.getImaginary() << "i";
        if (!entry.operation->isUnary()) {
            oss << "," << entry.operand2.getReal() << "+" << entry.operand2.getImaginary() << "i";
        }
        oss << ";";
    }
    std::string result = oss.str();
    // We don't need last semicolon.
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}

void HistoryManager::deserializeHistory(const std::string& serializedHistory) {
    // Stream for easier parsing.
    std::istringstream stream(serializedHistory);
    // Single entry.
    std::string entry;

    history.clear();

    // Parse knowing that entries are separeted by semicolon.
    while (std::getline(stream, entry, ';')) {
        std::istringstream entryStream(entry);
        std::string operationName;
        double real1, imag1, real2, imag2, resultReal, resultImag;

        // Will be used to store not needed part of string.
        char delimiter;

        // Parse operation name, everything up to colon.
        std::getline(entryStream, operationName, ':');

        // a+bi
        entryStream >> resultReal >> delimiter >> resultImag;

        ComplexNumber result(resultReal, resultImag);

        // Moving on to read the first operand
        entryStream >> delimiter >> real1 >> delimiter >> imag1;
        ComplexNumber operand1(real1, imag1);
        ComplexNumber operand2;

        std::unique_ptr<CalculatorOperation> operation = createOperation(operationName);

        // Check if we have second operand.
        if (!operation->isUnary()) {
            entryStream >> delimiter;

            if (delimiter == ',') {
                entryStream >> real2 >> delimiter >> imag2;
                operand2.setReal(real2);
                operand2.setImaginary(imag2);
            }
        }

        addOperation(std::move(operation), result, operand1, &operand2);
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
