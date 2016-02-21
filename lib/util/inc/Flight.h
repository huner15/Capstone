/*
 * ActualFlight.h
 * Specific Atomics
 * Frank Poole, Dat Tran
 * 2-16-16
 * TODO: Description
 */

#ifndef ACTUAL_FLIGHT_H_
#define ACTUAL_FLIGHT_H_

#include <vector>
#include "FlightReport.h"

class Flight {
private:
    /** A collection of all the flight reports of the Flight*/
    std::vector<FlightReport> _flight_reports;
    //std::vector<FlightReport>::iterator _flight_reports_it;
    //std::vector<FlightReport>::iterator _flight_reports_end;
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
