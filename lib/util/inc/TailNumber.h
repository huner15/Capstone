/*
 * TailNumber.h
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef TAIL_NUMBER_H_
#define TAIL_NUMBER_H_

#include <string>

class TailNumber {
private:
    std::string _tail_number;
public:
    TailNumber() {};
    TailNumber(std::string tail_number);
    ~TailNumber();
};

#endif
