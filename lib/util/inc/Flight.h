/**
 * @file ActualFlight.h
 * @author Specific Atomics
 * @authors Frank Poole, Dat Tran
 * @date 2-21-16
 * @brief TODO: Description
 */

#ifndef ACTUAL_FLIGHT_H_
#define ACTUAL_FLIGHT_H_

#include <vector>

#include "FlightReport.h"

class Flight {
private:
    /** A collection of all the flight reports of the Flight*/
    std::vector<FlightReport> _flight_reports;

    /** An integer representing the next flight report in the simulation. */
    int _flight_reports_index;

public:
    Flight();

    Flight(std::vector<FlightReport> const &flight_reports);

    std::vector<FlightReport> GetFlightReports();

    bool HasNextFlightReport();

    FlightReport NextFlightReport();

    ~Flight();
};

#endif
