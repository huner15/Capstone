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


    //Checks to make sure there is atleast one flight leg to
    // determine initial velocity.
    if(_flight_legs.size() < 1) {
        throw std::out_of_range ("There must be atleast one flight leg");
    }
}

GeographicCoordinate FlightPlan::GetStartPosition() {
    return _start_position;
}

std::vector<FlightLeg> FlightPlan::GetFlightLegs() {
    return _flight_legs;
}

