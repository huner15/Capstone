/*
 * TcasID.cpp
 * Specific Atomics
 * Frank Poole
 * 2-13-16
 * Implements the functionality of TcasID.
 */

#include "TcasID.h"

TcasID::TcasID() {
    _tcas_id = (uint8_t) ((rand() + 1) % _max_tcas_id);
}

TcasID::TcasID(uint8_t tcas_id) {
    if (tcas_id > 0 && tcas_id <= _max_tcas_id) {
        _tcas_id = tcas_id;
    }
    else {
        throw std::out_of_range("Invalid TCAS ID. Valid TCAS IDs range from 0"
                                        " to 25 inclusive.");
    }
}

TcasID::~TcasID() {
}

uint8_t TcasID::Get() {
    return _tcas_id;
}
