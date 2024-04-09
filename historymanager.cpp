#include "historymanager.h"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <limits>

/**
 * @brief Adds a new operation to the history.
 *
 * @param operation
 * @param result
 * @param operand1 - first operand
 * @param operand2 - second operand (optional)
 */
void HistoryManager::addOperation(std::unique_ptr<CalculatorOperation> operation, const ComplexNumber& result, const ComplexNumber& operand1, const ComplexNumber* operand2) {
    // Need to use move, as unique_ptr can't be copied.
    if (operand2) {
        history.emplace_back(std::move(operation), result, operand1, *operand2);
    } else {
        history.emplace_back(std::move(operation), result, operand1, ComplexNumber(0, 0));
    }
}

/**
 * @brief Serializes the operation history into a string.
 *
 * @return std::string - serialized history.
 */
std::string HistoryManager::serializeHistory() const {
    std::ostringstream oss;
    // For each element in history.
    for (const auto& entry : history) {
        // "operation:ra+rbi,a1+b1i;" if unary, "operation:ra+rbi,a1+b1i,a2+b2i;" if binary.
        oss << entry.operation->serialize() << ":";
        oss << entry.result.getReal() << "+" << entry.result.getImaginary() << "i,";
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

/**
 * @brief Turns string into parsed history.
 *
 * @param serializedHistory - serialized history (string)
 */
void HistoryManager::deserializeHistory(const std::string& serializedHistory) {
    std::istringstream stream(serializedHistory);
    std::string entry;

    history.clear();

    while (std::getline(stream, entry, ';')) {
        std::istringstream entryStream(entry);
        std::string operationName;
        double real1, imag1, real2 = 0, imag2 = 0, resultReal, resultImag;
        char delimiter;

        std::getline(entryStream, operationName, ':');
        entryStream >> resultReal >> delimiter >> resultImag;
        // Have to eliminate "i" from imaginary part.
        entryStream.ignore(std::numeric_limits<std::streamsize>::max(), 'i');

        // Eliminate ",".
        entryStream >> delimiter;

        ComplexNumber result(resultReal, resultImag);

        // First operand.
        entryStream >> real1 >> delimiter >> imag1;
        entryStream.ignore(std::numeric_limits<std::streamsize>::max(), 'i');
        ComplexNumber operand1(real1, imag1);
        ComplexNumber operand2;

        std::unique_ptr<CalculatorOperation> operation = createOperation(operationName);

        if (operation && !operation->isUnary()) {
            if (entryStream >> delimiter && delimiter == ',') {
                entryStream >> real2 >> delimiter >> imag2;
                // Remove "i" just as abovr.
                entryStream.ignore(std::numeric_limits<std::streamsize>::max(), 'i');
                operand2.setReal(real2);
                operand2.setImaginary(imag2);
            }
        }

        if (operation) {
            addOperation(std::move(operation), result, operand1, (operation->isUnary() ? nullptr : &operand2));
        }
    }
}


/**
 * @brief Creates operationt based on its name.
 *
 * @param operationName - name of the operation
 * @return operation object
 */
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
    }else if (operationName == "SquareOperation") {
        return std::make_unique<SquareOperation>();
    }
    return nullptr;
}

/**
 * @brief Saves history to a file.
 *
 * @param filePath - path to the file
 */
void HistoryManager::saveHistoryToFile(const std::string& filePath) const {
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("Can't access file: " + filePath);
    }

    std::string serializedHistory = serializeHistory();
    outFile << serializedHistory;
    if (!outFile.good()) {
        throw std::runtime_error("Error saving to file: " + filePath);
    }
}

/**
 * @brief Reads history from a file.
 *
 * @param filePath - path to the file
 */
void HistoryManager::loadHistoryFromFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) {
        throw std::runtime_error("Can't read file: " + filePath);
    }

    std::string serializedHistory((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    deserializeHistory(serializedHistory);
    if (!inFile.good()) {
        throw std::runtime_error("Error reading from file: " + filePath);
    }
}

/**
 * @brief Clears operation history.
 */
void HistoryManager::clearHistory() {
    history.clear();
}

