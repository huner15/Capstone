/*
 * FlightScenario.h
 * Specific Atomics
 * Kevin Pham, Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef FLIGHT_SCENARIO_H_
#define FLIGHT_SCENARIO_H_

#include <vector>

#include "Vector.h"
#include "Aircraft.h"

class FlightScenario {
private:
    /** Ownship aircraft. */
    Aircraft _ownship;
    
    /** A collection of all unique aircraft in the flight scenario. */
    std::vector<Aircraft> aircraft;

public:
    // TODO: Constructor

    // TODO: Destructor
};

#endif
