/**
 * @file RadarSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "RadarSimulator.h"

void RadarSimulator::SendReport(ServerSocket client_socket,
                                FlightReport *flight_report) {
    RadarReport radar_report = flight_report->CreateRadarReport();
    client_socket << radar_report;
}
