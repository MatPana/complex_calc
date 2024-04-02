#ifndef CALCMEMORY_H
#define CALCMEMORY_H

#include "complexnumber.h"

class CalcMemory {
public:
    CalcMemory();
    ~CalcMemory();

    ComplexNumber readMemory();
    ComplexNumber getLast();

    void updateValue(ComplexNumber read);
    void setMemory(ComplexNumber read);
    void addToMemory(ComplexNumber read);

    void clearMemory();

private:
    ComplexNumber sumInMemory = ComplexNumber(0, 0);
    ComplexNumber lastValue = ComplexNumber(0, 0);
};

#endif // CALCMEMORY_H
