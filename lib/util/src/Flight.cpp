/*
 * Flight.cpp
 * Specific Atomics
 * Frank Poole, Dat Tran
 * 2-16-16
 * TODO: Description
 */

#include <iostream>
#include "Flight.h"

Flight::Flight(std::vector<FlightReport> const &flight_reports) {
    _flight_reports = flight_reports;
    //_flight_reports_it = _flight_reports.begin();
    //_flight_reports_end = _flight_reports.end();
    _flight_reports_index = 0;

    if (_flight_reports.empty()) {
        throw std::out_of_range ("There is no flight report");
    }
}

std::vector<FlightReport> Flight::GetFlightReports() {
    return _flight_reports;
}

bool Flight::HasNextFlightReport() {
    //return _flight_reports_it != _flight_reports_end;
    return _flight_reports_index < _flight_reports.size();
}

FlightReport Flight::NextFlightReport() {
    //FlightReport flight_report = *_flight_reports_it;
    //++_flight_reports_it;

    //return flight_report;

    //FlightReport flight_report;
    /*
    if (HasNextFlightReport()) {
        flight_report = *_flight_reports_it;
        ++_flight_reports_it;
    }

    return flight_report;
    */

    FlightReport flight_report = _flight_reports[_flight_reports_index];

    if (HasNextFlightReport()) {
        ++_flight_reports_index;
    }

    return flight_report;
}

Flight::~Flight() {
}
