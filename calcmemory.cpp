#include "calcmemory.h"


/**
 * @brief Default constructor.
 */
CalcMemory::CalcMemory() {
    sumInMemory = ComplexNumber(0, 0);
}

/**
 * @brief Destructor.
 */
CalcMemory::~CalcMemory() {}

/**
 * @brief Reads the current value stored in memory.
 *
 * @return sum of all values stored in memory (ComplexNumber).
 */
ComplexNumber CalcMemory::readMemory() {
    return sumInMemory;
}

/**
 * @brief Gets the last value that was added to memory.
 *
 * @return last value added to memory (ComplexNumber).
 */
ComplexNumber CalcMemory::getLast() {
    return lastValue;
};

/**
 * @brief Resets the memory to zero.
 */
void CalcMemory::clearMemory() {
    sumInMemory = ComplexNumber(0, 0);
};

/**
 * @brief Updates the last value stored in memory.
 *
 * @param read new value to be stored (ComplexNumber).
 */
void CalcMemory::updateValue(ComplexNumber read) {
    lastValue = read;
};

/**
 * @brief Sets the value stored in memory.
 *
 * @param read to be stored in memory (ComplexNumber).
 */
void CalcMemory::setMemory(ComplexNumber read) {
    sumInMemory = read;
};

/**
 * @brief Adds a value to the memory.
 *
 * @param read added to the memory (ComplexNumber).
 */
void CalcMemory::addToMemory(ComplexNumber read) {
    sumInMemory = sumInMemory.add(read);
};
