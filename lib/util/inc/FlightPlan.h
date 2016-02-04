/*
 * FlightPlan.h
 * Specific Atomics
 * Kevin Pham
 * 2-2-16
 * TODO: Decription
 */

#ifndef FLIGHTPLAN_H_
#define FLIGHTPLAN_H_

#include "FlightLeg.h"
#include "GeographicCoordinate.h"
#include <vector>

class FlightPlan {
public:

private:
    /**
     * The starting position of the Flight.
     */
    GeographicCoordinate _start_position;
    /**
     * A collection of all the FlightLegs of this FlightPlan.
     */
    std::vector<FlightLeg> _flight_legs;

};

#endif //SAAS_FLIGHTPLAN_H
