/**
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-17-2016
 */

#include <iostream>
#include <string>
#include <pthread.h>

#include <adsb.pb.h>
#include <ownship.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>

#include "SimulationFlightsIO.h"

#include "ServerSocket.h"

/** Expected number of command line arguments. */
const int EXPECTED_ARGUMENTS = 6;

/** Total number of threads. */
const int NUM_THREADS = 4;

/** Self defined thread identification numbers. */
const int OWNSHIP_THREAD_INDEX = 0;
const int ADSB_THREAD_INDEX = 1;
const int RADAR_THREAD_INDEX = 2;
const int TCAS_THREAD_INDEX = 3;

/** Time to sleep in seconds before sending the next report. */
const int SLEEP_TIME = 1;

typedef struct thread_args {
    int id;
    in_port_t port;
    void(*send)(ServerSocket, FlightSimulation*);
    FlightSimulation *flightSimulation;
} thread_args_t;

void sendOwnshipReports(ServerSocket ownshipSocket,
                        FlightSimulation *flightSimulation) {
    OwnshipReport ownshipReport;

    std::vector<Flight> flights = flightSimulation->GetFlights();
    for (std::vector<Flight>::size_type i = 0; i < flights.size(); i++) {
        std::vector<FlightReport> reports = flights[i].GetFlightReports();
        /* TODO: Implement once Flight iterator is implemented.
        for (std::vector<FlightReport>::size_type j = 0;
             j < reports.size(); j++) {
            ownshipReport = reports[j].createOwnshipReport();
        }
        */
    }

    // Send the ownship report to the client.
    ownshipSocket << ownshipReport;

    // Wait one second before sending the next ownship report.
    sleep(SLEEP_TIME);
}

void sendAdsbReports(ServerSocket adsbSocket,
                     FlightSimulation *flightSimulation) {
    AdsBReport adsbReport;

    while (true) {
        // Set ADS-B report data fields.
        adsbReport.set_timestamp(7);
        adsbReport.set_latitude(8);
        adsbReport.set_longitude(9);
        adsbReport.set_altitude(10);
        adsbReport.set_tail_number("11");
        adsbReport.set_north(12);
        adsbReport.set_east(13);
        adsbReport.set_down(14);

        // Send the ADS-B Report to the client.
        adsbSocket << adsbReport;

        // Wait one second before sending the next adsb report.
        sleep(SLEEP_TIME);
    }
}

void sendRadarReports(ServerSocket radarSocket,
                      FlightSimulation *flightSimulation) {
    RadarReport radarReport;

    while (true) {
        // Set Radar report data fields.
        radarReport.set_timestamp(15);
        radarReport.set_range(16);
        radarReport.set_azimuth(17);
        radarReport.set_elevation(18);
        radarReport.set_id(19);
        radarReport.set_north(20);
        radarReport.set_east(21);
        radarReport.set_down(22);
        radarReport.set_latitude(23);
        radarReport.set_longitude(24);
        radarReport.set_altitude(25);

        // Send the radar report to the client.
        radarSocket << radarReport;

        // Wait one second before sending the next radar report.
        sleep(SLEEP_TIME);
    }
}

void sendTcasReports(ServerSocket tcasSocket,
                     FlightSimulation *flightSimulation) {
    TcasReport tcasReport;

    while (true) {
        // Set TCAS report data fields.
        tcasReport.set_id(26);
        tcasReport.set_range(27);
        tcasReport.set_altitude(28);
        tcasReport.set_bearing(29);

        // Send the tcas report to the client.
        tcasSocket << tcasReport;

        // Wait one second before sending the next tcas report.
        sleep(SLEEP_TIME);
    }
}

int startServer(in_port_t port, void(*send)(ServerSocket, FlightSimulation*),
                FlightSimulation *flightSimulation) {
    try {
        // Create a server to start listening for connections on the port.
        ServerSocket server(port);

        while (true) {
            ServerSocket client;
            server.accept(client);
            std::cout << "Client has connected." << std::endl;
            send(client, flightSimulation);
        }
    }
    catch (SocketException &e) {
        std::cout << "Exception caught: " << e.description() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void *startThread(void *thread_args) {
    thread_args_t *args = (thread_args_t *) thread_args;
    std::cout << "Successfully started server on port: " << args->port
    << std::endl;
    startServer(args->port, args->send, args->flightSimulation);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != EXPECTED_ARGUMENTS) {
        std::cout <<
        "usage: run_sim flight_simulation.json"
                " ownship_port adsb_port radar_port tcas_port" <<
        std::endl;
    }
    else {
        pthread_t threads[NUM_THREADS];
        thread_args_t ownship_args, adsb_args, radar_args, tcas_args;
        std::string flight_simulation_file_name = argv[1];
        FlightSimulation fs =
                SimulationFlightsIO::ReadFile(flight_simulation_file_name);

        ownship_args.id = OWNSHIP_THREAD_INDEX;
        ownship_args.port = (in_port_t) atoi(argv[OWNSHIP_THREAD_INDEX + 2]);
        ownship_args.send = sendOwnshipReports;
        ownship_args.flightSimulation = &fs;

        adsb_args.id = ADSB_THREAD_INDEX;
        adsb_args.port = (in_port_t) atoi(argv[ADSB_THREAD_INDEX + 2]);
        adsb_args.send = sendAdsbReports;
        adsb_args.flightSimulation = &fs;

        radar_args.id = RADAR_THREAD_INDEX;
        radar_args.port = (in_port_t) atoi(argv[RADAR_THREAD_INDEX + 2]);
        radar_args.send = sendRadarReports;
        radar_args.flightSimulation = &fs;

        tcas_args.id = TCAS_THREAD_INDEX;
        tcas_args.port = (in_port_t) atoi(argv[TCAS_THREAD_INDEX + 2]);
        tcas_args.send = sendTcasReports;
        tcas_args.flightSimulation = &fs;

        // Create a new thread for each device simulation.
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

    // Deallocate any global objects allocated by the protobuf library.
    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
