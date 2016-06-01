/**
 * @file AdsbSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief AdsbSimulator implements the functionality of an ADS-B device.
 */

#include "AdsbSimulator.h"

AdsbSimulator::AdsbSimulator(in_port_t port,
                             FlightSimulation &flight_simulation):
        DetectionDeviceSimulator(port, flight_simulation) {
};

void AdsbSimulator::SendReport(ServerSocket& client_socket,
                               FlightReport& flight_report) {
    if (flight_report.HasAsdbReport()) {
        AdsBReport adsb_report = flight_report.GetAdsbReport();
        client_socket << adsb_report;
    }
    else {
        std::cout << "Attempted to send incomplete ADS-B Report." << std::endl;
    }
}
