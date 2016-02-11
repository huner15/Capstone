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


#include <ownship.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>
#include <adsb.pb.h>

#include "ClientSocket.h"

/** Expected number of command line arguments. */
const int EXPECTED_ARGUMENTS = 6;

/** Total number of threads. */
const int NUM_THREADS = 4;

/** Self defined thread identification numbers. */
const int OWNSHIP_THREAD_INDEX = 0;
const int ADSB_THREAD_INDEX = 1;
const int RADAR_THREAD_INDEX = 2;
const int TCAS_THREAD_INDEX = 3;

typedef struct thread_args {
    int id;
    std::string host;
    in_port_t port;
    void(*receive)(ClientSocket);
} thread_args_t;

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

void receiveOwnshipReports(ClientSocket ownshipSocket) {
    OwnshipReport ownshipReport;
    u_int32_t ownshipReportCount = 0;

    while (true) {
        ownshipSocket >> ownshipReport;
        printOwnshipReport(ownshipReport, ownshipReportCount++);
        std::cout << std::endl;
    }
}

void receiveAdsbReports(ClientSocket adsbSocket) {
    AdsBReport adsbReport;
    u_int32_t adsbReportCount = 0;

    while (true) {
        adsbSocket >> adsbReport;
        printAdsbReport(adsbReport, adsbReportCount++);
        std::cout << std::endl;
    }
}

void receiveRadarReports(ClientSocket radarSocket) {
    RadarReport radarReport;
    u_int32_t radarReportCount = 0;

    while (true) {
        radarSocket >> radarReport;
        printRadarReport(radarReport, radarReportCount++);
        std::cout << std::endl;
    }
}

void receiveTcasReports(ClientSocket tcasSocket) {
    TcasReport tcasReport;
    u_int32_t tcasReportCount = 0;

    while (true) {
        tcasSocket >> tcasReport;
        printTcasReport(tcasReport, tcasReportCount++);
        std::cout << std::endl;
    }
}

void startClient(std::string host, const in_port_t port,
                 void(*receive)(ClientSocket)) {
    try {
        ClientSocket client_socket(host, port);
        receive(client_socket);
    }
    catch (SocketException &e) {
        std::cout << "Exception caught: " << e.description() << std::endl;
    }
}

void *startThread(void *thread_args) {
    thread_args_t *args = (thread_args_t *) thread_args;
    std::cout << "Successfully started thread." << std::endl;
    startClient(args->host, args->port, args->receive);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != EXPECTED_ARGUMENTS) {
        std::cout <<
        "usage: run_saap host ownship_port adsb_port radar_port tcas_port" <<
        std::endl;
    }
    else {
        pthread_t threads[NUM_THREADS];
        thread_args_t ownship_args, adsb_args, radar_args, tcas_args;

        ownship_args.id = OWNSHIP_THREAD_INDEX;
        ownship_args.port = (in_port_t) atoi(argv[OWNSHIP_THREAD_INDEX + 2]);
        ownship_args.receive = receiveOwnshipReports;

        adsb_args.id = ADSB_THREAD_INDEX;
        adsb_args.port = (in_port_t) atoi(argv[ADSB_THREAD_INDEX + 2]);
        adsb_args.receive = receiveAdsbReports;

        radar_args.id = RADAR_THREAD_INDEX;
        radar_args.port = (in_port_t) atoi(argv[RADAR_THREAD_INDEX + 2]);
        radar_args.receive = receiveRadarReports;

        tcas_args.id = TCAS_THREAD_INDEX;
        tcas_args.port = (in_port_t) atoi(argv[TCAS_THREAD_INDEX + 2]);
        tcas_args.receive = receiveTcasReports;

        // Fork or thread would probably happen here.
        pthread_create(&threads[OWNSHIP_THREAD_INDEX], NULL, startThread,
                       (void *) &ownship_args);
        pthread_create(&threads[ADSB_THREAD_INDEX], NULL, startThread,
                       (void *) &adsb_args);
        pthread_create(&threads[RADAR_THREAD_INDEX], NULL, startThread,
                       (void *) &radar_args);
        pthread_create(&threads[TCAS_THREAD_INDEX], NULL, startThread,
                       (void *) &tcas_args);

        // Wait for all threads to complete.
        pthread_join(threads[OWNSHIP_THREAD_INDEX], NULL);
        pthread_join(threads[ADSB_THREAD_INDEX], NULL);
        pthread_join(threads[RADAR_THREAD_INDEX], NULL);
        pthread_join(threads[TCAS_THREAD_INDEX], NULL);
    }

    // Delete any global objects allocated by the protobuf library.
    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
