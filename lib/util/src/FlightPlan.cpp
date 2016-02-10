/*
 * FlightPlan.cpp
 * Specific Atomics
 * Dat Tran, Frank Poole, Kevin Pham
 * 2-9-16
 * TODO: Description
 */

#include "FlightPlan.h"

FlightPlan::FlightPlan(GeographicCoordinate start_position,
                       std::vector<FlightLeg> flight_legs) {
    _start_position = start_position;
    _flight_legs = flight_legs;
}

