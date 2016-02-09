/*
 * TailNumber.h
 * Specific Atomics
 * Frank Poole
 * 2-8-16
 * TODO: Description
 */

#ifndef TAIL_NUMBER_H_
#define TAIL_NUMBER_H_

#include <string>

class TailNumber {
private:
    /** Tail number identifier. */
    std::string _tail_number;

    /** Length of a tail number identification in characters. */
    static const size_t _length = 6;

public:
    /**
     * Create a randomly generated alphanumeric tail number.
     */
    TailNumber();

    /**
     * Create a tail number using a specified six character string.
     * @param tail_number the tail number
     */
    TailNumber(std::string tail_number);

    /**
     * Deconstruct a tail number.
     */
    ~TailNumber();

    /**
     * Return the tail number.
     * @returns the tail number
     */
    std::string GetTailNumber();
};

#endif
