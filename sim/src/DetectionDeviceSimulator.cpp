/**
 * @file DetectionDeviceSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "DetectionDeviceSimulator.h"

void DetectionDeviceSimulator::SendReports(ServerSocket client_socket) {
    std::vector<Flight> flights = _flight_simulation->GetFlights();
    Flight ownship_flight = flights[0];

    while (ownship_flight.HasNextFlightReport()) {
        for (std::vector<Flight>::size_type i = 1; i < flights.size(); i++) {
            Flight detectedFlight = flights[i];
            if (detectedFlight.HasNextFlightReport()) {
                FlightReport detected_report = detectedFlight.NextFlightReport();
                this->SendReport(client_socket, detected_report);
            }
        }

        sleep(1);
    }
}
