/**
 * @file DetectionDeviceSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "DetectionDeviceSimulator.h"

void DetectionDeviceSimulator::SendReports(ServerSocket& client_socket) {
    std::vector<Flight> flights = _flight_simulation->GetFlights();
    Flight ownship_flight = flights[0];

    while (ownship_flight.HasNextFlightReport()) {
        ownship_flight.NextFlightReport();
        for (std::vector<Flight>::size_type i = 1; i < flights.size(); i++) {
            Flight detected_flight = flights[i];
            if (detected_flight.HasNextFlightReport()) {
                FlightReport detected_report =
                        detected_flight.NextFlightReport();
                this->SendReport(client_socket, detected_report);
            }
        }

        sleep(1);
    }
}
