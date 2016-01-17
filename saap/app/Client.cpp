/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-17-2016
 */

#include <string>
#include <iostream>
#include <fstream>

#include <adsb.pb.h>
#include <ownship.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>

#include "ClientSocket.h"

/** Expected number of command line arguments. */
const int EXPECTED_ARGUMENTS = 3;

void printOwnshipReport(OwnshipReport ownshipReport,
                        u_int32_t ownshipReportCount) {
    std::cout << "Received Ownship Report: " << ownshipReportCount << std::endl;
    std::cout << "Timestamp: " << ownshipReport.timestamp() << std::endl;
    std::cout << "Latitude: " << ownshipReport.ownship_latitude() << std::endl;
    std::cout << "Longitude: " << ownshipReport.ownship_longitude() <<
    std::endl;
    std::cout << "Altitude: " << ownshipReport.ownship_altitude() << std::endl;
    std::cout << "North Velocity: " << ownshipReport.north() << std::endl;
    std::cout << "East Velocity: " << ownshipReport.east() << std::endl;
    std::cout << "Down Velocity: " << ownshipReport.down() << std::endl;
}

void printAdsbReport(AdsBReport adsbReport, u_int32_t adsbReportCount) {
    std::cout << "Received ADS-B Report: " << adsbReportCount << std::endl;
    std::cout << "Timestamp: " << adsbReport.timestamp() << std::endl;
    std::cout << "Latitude: " << adsbReport.latitude() << std::endl;
    std::cout << "Longitude: " << adsbReport.longitude() << std::endl;
    std::cout << "Altitude: " << adsbReport.altitude() << std::endl;
    std::cout << "Tail Number: " << adsbReport.tail_number() << std::endl;
    std::cout << "North Velocity: " << adsbReport.north() << std::endl;
    std::cout << "East Velocity: " << adsbReport.east() << std::endl;
    std::cout << "Down Velocity: " << adsbReport.down() << std::endl;
}

void printRadarReport(RadarReport radarReport, u_int32_t radarReportCount) {
    std::cout << "Received Radar Report: " << radarReportCount << std::endl;
    std::cout << "Timestamp: " << radarReport.timestamp() << std::endl;
    std::cout << "Range: " << radarReport.range() << std::endl;
    std::cout << "Azimuth: " << radarReport.azimuth() << std::endl;
    std::cout << "Elevation: " << radarReport.elevation() << std::endl;
    std::cout << "ID: " << radarReport.id() << std::endl;
    std::cout << "North Velocity: " << radarReport.north() << std::endl;
    std::cout << "East Velocity: " << radarReport.east() << std::endl;
    std::cout << "Down Velocity: " << radarReport.down() << std::endl;
    std::cout << "Latitude: " << radarReport.latitude() << std::endl;
    std::cout << "Longitude: " << radarReport.longitude() << std::endl;
    std::cout << "Altitude: " << radarReport.altitude() << std::endl;
}

void printTcasReport(TcasReport tcasReport, u_int32_t tcasReportCount) {
    std::cout << "Received TCAS Report: " << tcasReportCount << std::endl;
    std::cout << "ID: " << tcasReport.id() << std::endl;
    std::cout << "Range: " << tcasReport.range() << std::endl;
    std::cout << "Altitude: " << tcasReport.altitude() << std::endl;
    std::cout << "Bearing: " << tcasReport.bearing() << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != EXPECTED_ARGUMENTS) {
        std::cout << "usage: run_saap host port" << std::endl;
    }
    else {
        try {
            ClientSocket client_socket(argv[1], (in_port_t) atoi(argv[2]));

            OwnshipReport ownshipReport;
            AdsBReport adsbReport;
            RadarReport radarReport;
            TcasReport tcasReport;

            u_int32_t ownshipReportCount = 0;
            u_int32_t adsbReportCount = 0;
            u_int32_t radarReportCount = 0;
            u_int32_t tcasReportCount = 0;

            while (true) {
                // Receive ownship reports from the server.
                client_socket >> ownshipReport;
                client_socket >> adsbReport;
                client_socket >> radarReport;
                client_socket >> tcasReport;

                // Print the reports to standard out.
                printOwnshipReport(ownshipReport, ownshipReportCount++);
                std::cout << std::endl;
                printAdsbReport(adsbReport, adsbReportCount++);
                std::cout << std::endl;
                printRadarReport(radarReport, radarReportCount++);
                std::cout << std::endl;
                printTcasReport(tcasReport, tcasReportCount++);
                std::cout << std::endl;
            }
        }
        catch (SocketException &e) {
            std::cout << "Exception caught: " << e.description() << std::endl;
        }
    }

    // Delete any global objects allocated by the protobuf library.
    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
