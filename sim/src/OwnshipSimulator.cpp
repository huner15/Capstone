/**
 * @file OwnshipSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "OwnshipSimulator.h"

void OwnshipSimulator::SendReports(ServerSocket client_socket) {
    // TODO: Resolve object referencing errors and enable dynamic data.
    /*
    std::vector<Flight> flights = _flight_simulation->GetFlights();
    Flight ownship_flight = flights[0];

    while (ownship_flight.HasNextFlightReport()) {
        FlightReport ownship_report = ownship_flight.NextFlightReport();
        this->SendReport(client_socket, flight_report);
        sleep(1);
    }
    */

    OwnshipReport ownship_report;
    while (true) {
        ownship_report.set_timestamp(0);
        ownship_report.set_ownship_latitude(1);
        ownship_report.set_ownship_longitude(2);
        ownship_report.set_ownship_altitude(3);
        ownship_report.set_north(4);
        ownship_report.set_east(5);
        ownship_report.set_down(6);

        client_socket << ownship_report;

        sleep(1);
    }
}

void OwnshipSimulator::SendReport(ServerSocket client_socket,
                                  FlightReport flight_report) {
    OwnshipReport ownship_report = flight_report.CreateOwnshipReport();
    client_socket << ownship_report;
}
