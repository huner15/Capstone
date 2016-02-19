/**
 * @file OwnshipSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "OwnshipSimulator.h"

void OwnshipSimulator::SendReports(ServerSocket client_socket) {
    std::vector<Flight> flights = _flight_simulation->GetFlights();
    Flight ownship_flight = flights[0];

    while (ownship_flight.HasNextFlightReport()) {
        FlightReport ownship_report = ownship_flight.NextFlightReport();
        this->SendReport(client_socket, ownship_report);
        sleep(1);
    }
}

void OwnshipSimulator::SendReport(ServerSocket client_socket,
                                  FlightReport flight_report) {
    //OwnshipReport ownship_report = flight_report.CreateOwnshipReport();
    OwnshipReport ownshipReport;

    ownshipReport.set_timestamp(0);
    ownshipReport.set_ownship_latitude(1);
    ownshipReport.set_ownship_longitude(2);
    ownshipReport.set_ownship_altitude(3);
    ownshipReport.set_north(4);
    ownshipReport.set_east(5);
    ownshipReport.set_down(6);

    client_socket << ownshipReport;
}
