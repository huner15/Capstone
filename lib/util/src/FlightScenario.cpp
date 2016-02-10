/*
 * FlightScenario.cpp
 * Specific Atomics
 * Frank Poole, Kevin Pham
 * 2-9-16
 * TODO: Description
 */

#include "FlightScenario.h"

FlightScenario::FlightScenario(Aircraft ownship,
                               std::vector<Aircraft> aircraft) {
    _ownship = ownship;
    _aircraft = aircraft;
}