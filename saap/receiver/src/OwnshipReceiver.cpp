/*
 * @file OwnshipReceiver.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO make description
 */

#include "OwnshipReceiver.h"

void OwnshipReceiver::ReceiveReport(ClientSocket &client_socket) {
    OwnshipReport ownshipReport;
    client_socket >> ownshipReport;
    PrintReport(ownshipReport);
    std::cout << std::endl;
}

void OwnshipReceiver::PrintReport(OwnshipReport& ownship_report) {
    std::cout << "Received Ownship Report" << std::endl;
    std::cout << "Timestamp: " << ownship_report.timestamp() << std::endl;
    std::cout << "Latitude: " << ownship_report.ownship_latitude() << std::endl;
    std::cout << "Longitude: " << ownship_report.ownship_longitude() <<
    std::endl;
    std::cout << "Altitude: " << ownship_report.ownship_altitude() << std::endl;
    std::cout << "North Velocity: " << ownship_report.north() << std::endl;
    std::cout << "East Velocity: " << ownship_report.east() << std::endl;
    std::cout << "Down Velocity: " << ownship_report.down() << std::endl;
}
