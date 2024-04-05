#ifndef CALCMEMORY_H
#define CALCMEMORY_H

#include "complexnumber.h"


/**
 * @brief Class for managing memory operations in a calculator application.
 *
 * This class provides functionalities for storing, retrieving, and manipulating complex numbers in memory.
 */
class CalcMemory {
public:
    /**
   * @brief Default constructor.
   */
    CalcMemory();

    /**
   * @brief Default destructor.
   */
    ~CalcMemory();

    /**
   * @brief Reads the currently displayed value.
   */
    ComplexNumber readMemory();

    /**
   * @brief Gets last used value.
   */
    ComplexNumber getLast();

    /**
     * @brief Updates the last value stored in memory.
     *
     * @param read new value to be stored as the last value (ComplexNumber).
    */
    void updateValue(ComplexNumber read);

    /**
     * @brief Sets memory to given value.
     *
     * @param read new value to set memory to (ComplexNumber).
    */
    void setMemory(ComplexNumber read);

    /**
     * @brief Adds number to number contained in the memory.
     *
     * @param read to be added (ComplexNumber).
    */
    void addToMemory(ComplexNumber read);

    /**
     * @brief Clears the memory content.
    */
    void clearMemory();

private:
    /**
   * @brief Sum of all values stored in memory.
   */
    ComplexNumber sumInMemory = ComplexNumber(0, 0);

    /**
   * @brief Last read value.
   */
    ComplexNumber lastValue = ComplexNumber(0, 0);
};

#endif // CALCMEMORY_H
