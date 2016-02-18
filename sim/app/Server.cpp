/**
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 2-18-2016
 */

#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>

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
    void(*send)(ServerSocket, FlightReport*);
    FlightSimulation *flightSimulation;
    bool isOwnship;
} thread_args_t;

void sendOwnshipReports(ServerSocket ownshipSocket,
                        FlightReport *flightReport) {
    OwnshipReport ownshipReport = flightReport->CreateOwnshipReport();

    // Send the ownship report to the client.
    ownshipSocket << ownshipReport;
}

void sendAdsbReports(ServerSocket adsbSocket, FlightReport *flightReport) {
    AdsBReport adsbReport = flightReport->CreateAdsBReport();

    // Send the ADS-B Report to the client.
    adsbSocket << adsbReport;
}

void sendRadarReports(ServerSocket radarSocket, FlightReport *flightReport) {
    RadarReport radarReport = flightReport->CreateRadarReport();

    // Send the radar report to the client.
    radarSocket << radarReport;
}

void sendTcasReports(ServerSocket tcasSocket, FlightReport *flightReport) {
    TcasReport tcasReport = flightReport->CreateTcasReport();

    // Send the tcas report to the client.
    tcasSocket << tcasReport;
}

int startServer(in_port_t port, void(*send)(ServerSocket, FlightReport*),
                FlightSimulation *flightSimulation, bool isOwnship) {
    try {
        // Create a server to start listening for connections on the port.
        ServerSocket server(port);

        //while (true) {
            ServerSocket client;
            server.accept(client);
            std::cout << "Client has connected." << std::endl;

            std::vector<Flight> flights = flightSimulation->GetFlights();
            Flight ownshipFlight = flights[0];

            while (ownshipFlight.HasNextFlightReport()) {
                std::cout << "true!!!" << std::endl;
                if (isOwnship) {
                    FlightReport ownshipReport =
                            ownshipFlight.NextFlightReport();
                    send(client, &ownshipReport);
                }
                else {
                    for (std::vector<Flight>::size_type i = 1;
                         i < flights.size(); i++) {
                        Flight detectedFlight = flights[i];
                        if (detectedFlight.HasNextFlightReport()) {
                            FlightReport otherReport =
                                    detectedFlight.NextFlightReport();
                            send(client, &otherReport);
                        }
                    }
                }

                // Wait one second before sending the next ownship report.
                sleep(SLEEP_TIME);
                //usleep(1000);
            }
        //}
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
    startServer(args->port, args->send, args->flightSimulation,
                args->isOwnship);
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
        ownship_args.isOwnship = true;

        adsb_args.id = ADSB_THREAD_INDEX;
        adsb_args.port = (in_port_t) atoi(argv[ADSB_THREAD_INDEX + 2]);
        adsb_args.send = sendAdsbReports;
        adsb_args.flightSimulation = &fs;
        adsb_args.isOwnship = false;

        radar_args.id = RADAR_THREAD_INDEX;
        radar_args.port = (in_port_t) atoi(argv[RADAR_THREAD_INDEX + 2]);
        radar_args.send = sendRadarReports;
        radar_args.flightSimulation = &fs;
        radar_args.isOwnship = false;

        tcas_args.id = TCAS_THREAD_INDEX;
        tcas_args.port = (in_port_t) atoi(argv[TCAS_THREAD_INDEX + 2]);
        tcas_args.send = sendTcasReports;
        tcas_args.flightSimulation = &fs;
        tcas_args.isOwnship = false;

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
