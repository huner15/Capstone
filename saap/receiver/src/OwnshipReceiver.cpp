/*
 * @file OwnshipReceiver.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-28-16
 * @brief Implements the functionality of OwnshipReceiver.
 */

#include "OwnshipReceiver.h"

OwnshipReceiver::OwnshipReceiver(std::string host, in_port_t port,
                                 ReportReceiver& report_receiver):
        DeviceReceiver(host, port, report_receiver) {
}

void OwnshipReceiver::ReceiveReport(ClientSocket &client_socket) {
    OwnshipReport ownship_report;
    client_socket >> ownship_report;
    _report_receiver.ReceiveOwnship(ownship_report);
    PrintReport(ownship_report);
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
