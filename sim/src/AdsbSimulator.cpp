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
    AdsBReport adsb_report = flight_report.CreateAdsBReport();
    client_socket << adsb_report;
}
