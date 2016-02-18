/*
 * TcasID.h
 * Specific Atomics
 * Frank Poole
 * 2-13-16
 * TcasID models the identification number assigned by TCAS devices.
 */

#ifndef INTRUDER_ID_H_
#define INTRUDER_ID_H_

#include <cstdlib>
#include <string>
#include <stdexcept>

/**
 * TcasID models the identification number assigned by TCAS devices when
 * detecting a new object within range. Identification numbers range from 1 to
 * 25.
 */
class TcasID {
private:
    /** TCAS object identification number. */
    uint8_t _tcas_id;

    /** Maximum possible TCAS identification number. */
    static const int _max_tcas_id = 25;

public:
    /**
     * Create a new TcasID with a randomly generated identifier from 1 to 25.
     */
    TcasID();

    /**
     * Create a new TcasID with a specified integer from 1 to 25. If the integer
     * is not from 1 to 25, an exception is thrown.
     * @param tcas_id the TCAS identification number
     * @throws std::out_of_range if the specified integer is not in 1 to 25.
     */
    TcasID(uint8_t tcas_id);

    /**
     * Deconstruct a TcasID.
     */
    ~TcasID();

    /**
     * Return the TCAS object identification number.
     */
    uint8_t Get() const;
};

#endif
