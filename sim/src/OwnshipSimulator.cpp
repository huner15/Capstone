/**
 * @file OwnshipSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief OwnshipSimulator implements the functionality of an Ownship navigation
 * device.
 */

#include "OwnshipSimulator.h"

OwnshipSimulator::OwnshipSimulator(in_port_t port,
                                   FlightSimulation &flight_simulation):
        DeviceSimulator(port, flight_simulation) {
};

void OwnshipSimulator::SendReports(ServerSocket& client_socket) {
    std::vector<Flight> flights = _flight_simulation.GetFlights();
    Flight ownship_flight = flights[0];

    while (ownship_flight.HasNextFlightReport()) {
        FlightReport flight_report = ownship_flight.NextFlightReport();
        this->SendReport(client_socket, flight_report);
        sleep(_SLEEP_TIME);
    }
}

void OwnshipSimulator::SendReport(ServerSocket& client_socket,
                                  FlightReport& flight_report) {
    if (flight_report.HasOwnshipReport()) {
        OwnshipReport ownship_report = flight_report.GetOwnshipReport();
        client_socket << ownship_report;
    }
}
