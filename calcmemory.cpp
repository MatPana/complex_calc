#include "calcmemory.h"

CalcMemory::CalcMemory() {}

CalcMemory::~CalcMemory() {}

ComplexNumber CalcMemory::readMemory() {
    return sumInMemory;
}

ComplexNumber CalcMemory::getLast() {
    return lastValue;
};

void CalcMemory::clearMemory() {
    sumInMemory = ComplexNumber(0, 0);
};

void CalcMemory::updateValue(ComplexNumber read) {
    lastValue = read;
};

void CalcMemory::setMemory(ComplexNumber read) {
    sumInMemory = read;
};

void CalcMemory::addToMemory(ComplexNumber read) {
    sumInMemory = sumInMemory.add(read);
};
