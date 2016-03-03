/**
 * @file TcasSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief TcasSimulator implements the functionality of a TCAS device.
 */

#include "TcasSimulator.h"

TcasSimulator::TcasSimulator(in_port_t port,
                             FlightSimulation &flight_simulation):
        DetectionDeviceSimulator(port, flight_simulation) {
}

void TcasSimulator::SendReport(ServerSocket& client_socket,
                                FlightReport& flight_report) {
    TcasReport tcas_report = flight_report.CreateTcasReport();
    client_socket << tcas_report;
}
