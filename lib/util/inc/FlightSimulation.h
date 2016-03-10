/*
 * Simulation.h
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <vector>

#include "Flight.h"

class FlightSimulation {
private:
    std::vector<Flight> _flights;
public:
    FlightSimulation(std::vector<Flight> all_flights);

    std::vector<Flight> GetFlights();

    ~FlightSimulation() {};
};

#endif
