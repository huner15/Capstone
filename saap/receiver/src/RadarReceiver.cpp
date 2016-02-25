/*
 * @file RadarReceiver.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO make description
 */

#include "RadarReceiver.h"

RadarReceiver::RadarReceiver(std::string host, in_port_t port,
                             ReportReceiver &report_receiver):
        DeviceReceiver(host, port, report_receiver) {
}

void RadarReceiver::ReceiveReport(ClientSocket& client_socket) {
    RadarReport radar_report;
    client_socket >> radar_report;
    _report_receiver.ReceiveRadar(radar_report);
}

void RadarReceiver::PrintReport(RadarReport& radar_report) {
    std::cout << "Received Radar Report" << std::endl;
    std::cout << "Timestamp: " << radar_report.timestamp() << std::endl;
    std::cout << "Range: " << radar_report.range() << std::endl;
    std::cout << "Azimuth: " << radar_report.azimuth() << std::endl;
    std::cout << "Elevation: " << radar_report.elevation() << std::endl;
    std::cout << "ID: " << radar_report.id() << std::endl;
    std::cout << "North Velocity: " << radar_report.north() << std::endl;
    std::cout << "East Velocity: " << radar_report.east() << std::endl;
    std::cout << "Down Velocity: " << radar_report.down() << std::endl;
    std::cout << "Latitude: " << radar_report.latitude() << std::endl;
    std::cout << "Longitude: " << radar_report.longitude() << std::endl;
    std::cout << "Altitude: " << radar_report.altitude() << std::endl;
}
