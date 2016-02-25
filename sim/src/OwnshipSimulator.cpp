/**
 * @file OwnshipSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "OwnshipSimulator.h"

void OwnshipSimulator::SendReports(ServerSocket& client_socket) {
    std::vector<Flight> flights = _flight_simulation.GetFlights();
    Flight ownship_flight = flights[0];

    while (ownship_flight.HasNextFlightReport()) {

        FlightReport flight_report = ownship_flight.NextFlightReport();

        this->SendReport(client_socket, flight_report);
        //std::cout << "TailNumber: " << flight_report.GetTailNumber().Get().c_str() << std::endl;
        sleep(1);
    }
}

void OwnshipSimulator::SendReport(ServerSocket& client_socket,
                                  FlightReport& flight_report) {
    OwnshipReport ownship_report = flight_report.CreateOwnshipReport();
    client_socket << ownship_report;
}
