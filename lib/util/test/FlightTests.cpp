/**
 * @file FlightLegTests.cpp
 * @author Specific Atomics
 * @authors Kevin Pham,
 * @date 2-17-16
 * @brief Tests for correct functionality in Flight.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <FlightSimulation.h>

#include "Flight.h"
#include "../../jsonio/inc/SimulationFlightsIO.h"


/*
 * Checks to make sure that a valid FlightLeg can be created.
 */
TEST(FlightInputConstructor, ValidValues) {
    FlightSimulation fs = SimulationFlightsIO::ReadFile("FlightSimulation.json");
    std::vector<Flight> flights = fs.GetFlights();
    Flight flight = flights.at(0);

    while(flight.HasNextFlightReport()) {
        FlightReport report = flight.NextFlightReport();
        std::cout << report.GetTailNumber().Get() << std::endl;
    }
}