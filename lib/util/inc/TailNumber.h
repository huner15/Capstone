/**
 * @file TailNumber.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-9-16
 * @brief Tail Number describes a aircraft tail number.
 */

#ifndef TAIL_NUMBER_H_
#define TAIL_NUMBER_H_

#include <string>
#include <random>
#include <stdexcept>

/**
 * A tail number represents an aircraft tail number with a length of six
 * alphanumeric characters. This model does not include real life naming
 * restrictions specified by international and national organizations such as
 * indexing characters by country of origin as this may divulge properties of
 * the identified aircraft.
 */
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
     * @param tail_number a six character string
     * @throws std::out_of_range exceptions if the tail number length is not six
     */
    TailNumber(std::string tail_number);

    TailNumber(const TailNumber& other);

    /**
     * Deconstruct a tail number.
     */
    ~TailNumber();

    TailNumber& operator = (const TailNumber &other);

    /**
     * Returns the tail number as a mutable string.
     * @returns the tail number
     */
    std::string Get() const;

    //TailNumber& operator=(const TailNumber& other);

    /**
     * Checks to se if two TailNumbers are the same
     * @return boolean stating whether two booleans are the same.
     */
    bool operator == (TailNumber tail_number);
};

#endif
