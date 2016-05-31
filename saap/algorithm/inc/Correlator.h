/*
 * @file Correlator.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 5-30-16
 * @brief An interface describing the functionality of a sense and avoid
 * processor correlation engine.
 */

#ifndef CORRELATOR_H_
#define CORRELATOR_H_

#include "CorrelationAircraft.h"
#include "ReceivedReports.h"

class Correlator {
public:
    virtual std::vector<CorrelationAircraft *>* Correlate(
            ReceivedReports receivedReports) = 0;
};

#endif
