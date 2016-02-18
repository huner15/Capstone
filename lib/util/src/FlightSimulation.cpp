/*
 * FlightSimulation.cpp
 * Specific Atomics
 * Frank Poole
 * 1-31-16
 * TODO: Description
 */

#include <iostream>
#include "FlightSimulation.h"

FlightSimulation::FlightSimulation(std::vector<Flight> all_flights) {
    _flights = all_flights;
}

std::vector<Flight> FlightSimulation::GetFlights() {
    return _flights;
}

