/*
 * IntruderID.h
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef INTRUDER_ID_H_
#define INTRUDER_ID_H_

#include <string>

class TcasID {
private:
    uint8_t _intruder_id;
public:
    TcasID() {};

    TcasID(uint8_t intruder_id);

    ~TcasID();

    uint8_t Get();
};

#endif
