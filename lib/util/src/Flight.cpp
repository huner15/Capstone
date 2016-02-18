/*
 * Flight.cpp
 * Specific Atomics
 * Frank Poole, Dat Tran
 * 2-16-16
 * TODO: Description
 */

#include "Flight.h"

Flight::Flight(std::vector<FlightReport> const &flight_reports) {
    _flight_reports = flight_reports;

    if (_flight_reports.empty()) {
        throw std::out_of_range ("There is no flight report");
    }
}

std::vector<FlightReport> Flight::GetFlightReports() {
    return _flight_reports;
}

//std::vector<FlightReport>::iterator


Flight::~Flight() {

}
