/*
 * FlightScenario.h
 * Specific Atomics
 * Kevin Pham, Frank Poole
 * 2-9-16
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
    std::vector<Aircraft> _aircraft;

public:
    FlightScenario(Aircraft ownhip, std::vector<Aircraft> aircraft);
    FlightScenario() {};

    /**
     * Accessor function for the ownship data
     * @return Aircraft with the ownship data
     */
    Aircraft GetOwnship();

    /**
     * Accessor function for all the aircraft in the run.
     * @return vector with all the aircraft data in it.
     */
    std::vector<Aircraft> GetAircraft();

    ~FlightScenario() {};
};

#endif
