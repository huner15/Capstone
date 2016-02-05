/*
 * FlightPlan.h
 * Specific Atomics
 * Kevin Pham, Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef FLIGHT_PLAN_H_
#define FLIGHT_PLAN_H_

#include <vector>

#include "GeographicCoordinate.h"
#include "FlightLeg.h"

class FlightPlan {
private:
    /** The starting position of the Flight. */
    GeographicCoordinate _start_position;

    /** A collection of all the FlightLegs of this FlightPlan. */
    std::vector<FlightLeg> _flight_legs;

public:
    // TODO: Constructor

    // TODO: Destructor
};

#endif
