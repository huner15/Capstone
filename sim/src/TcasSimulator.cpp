/**
 * @file TcasSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "TcasSimulator.h"

void TcasSimulator::SendReport(ServerSocket client_socket,
                                FlightReport flight_report) {
    TcasReport tcas_report = flight_report.CreateTcasReport();
    client_socket << tcas_report;
}
