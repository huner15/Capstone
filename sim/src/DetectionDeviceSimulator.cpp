/**
 * @file DetectionDeviceSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief DetectionDeviceSimulator implements the functionality of an abstract
 * device which may send multiple reports per cycle.
 */

#include "DetectionDeviceSimulator.h"

void DetectionDeviceSimulator::SendReports(ServerSocket& client_socket) {
    std::vector<Flight> flights = _flight_simulation.GetFlights();
    Flight ownship_flight = flights[0];
    int report_count = 0;

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

        ++report_count;
        sleep(_SLEEP_TIME);
    }
}
