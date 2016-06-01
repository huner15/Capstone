/*
 * @file FakeCorrelator.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 5-30-16
 * @brief A correlator which simply packages input ReceivedReports as output
 * CorrelationAircraft.
 */

#ifndef FAKE_CORRELATOR_H_
#define FAKE_CORRELATOR_H_

#include "Correlator.h"

class FakeCorrelator: public Correlator {
    std::vector<CorrelationAircraft *>* Correlate(
            ReceivedReports receivedReports);
};

#endif
