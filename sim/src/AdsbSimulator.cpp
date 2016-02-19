/**
 * @file AdsbSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "AdsbSimulator.h"

void AdsbSimulator::SendReport(ServerSocket client_socket,
                               FlightReport flight_report) {
    AdsBReport adsb_report = flight_report.CreateAdsBReport();
    client_socket << adsb_report;
}
