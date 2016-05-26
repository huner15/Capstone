/**
 * @file RadarSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief RadarSimulator implements the functionality of a Radar device.
 */

#include "RadarSimulator.h"

RadarSimulator::RadarSimulator(in_port_t port,
                               FlightSimulation &flight_simulation):
        DetectionDeviceSimulator(port, flight_simulation) {
}

void RadarSimulator::SendReport(ServerSocket& client_socket,
                                FlightReport& flight_report) {
    if (flight_report.HasRadarReport()) {
        RadarReport radar_report = flight_report.GetRadarReport();
        client_socket << radar_report;
    }
    else {
        std::cout << "Attempted to send incomplete Radar Report." << std::endl;
    }
}
