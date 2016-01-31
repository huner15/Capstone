/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-17-2016
 */

#include <pthread.h>

#include <adsb.pb.h>
#include <ownship.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>

// For build testing purposes
#include "vector.h"

#include "ServerSocket.h"

/** Expected number of command line arguments. */
const int EXPECTED_ARGUMENTS = 5;

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
    void(*send)(ServerSocket);
} thread_args_t;

void sendOwnshipReports(ServerSocket ownshipSocket) {
    OwnshipReport ownshipReport;

    while (true) {
        // Set ownship report data fields.
        ownshipReport.set_timestamp(0);
        ownshipReport.set_ownship_latitude(1);
        ownshipReport.set_ownship_longitude(2);
        ownshipReport.set_ownship_altitude(3);
        ownshipReport.set_north(4);
        ownshipReport.set_east(5);
        ownshipReport.set_down(6);

        // Send the ownship report to the client.
        ownshipSocket << ownshipReport;

        // Wait one second before sending the next ownship report.
        sleep(SLEEP_TIME);
    }
}

void sendAdsbReports(ServerSocket adsbSocket) {
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

void sendRadarReports(ServerSocket radarSocket) {
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

void sendTcasReports(ServerSocket tcasSocket) {
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

int startServer(in_port_t port, void(*send)(ServerSocket)) {
    try {
        // Create a server to start listening for connections on the port.
        ServerSocket server(port);
        std::cout << "Listening on: " << port << std::endl;

        while (true) {
            ServerSocket client;
            server.accept(client);
            std::cout << "Client has connected." << std::endl;
            send(client);
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
    std::cout << "Successfully started thread." << std::endl;
    startServer(args->port, args->send);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != EXPECTED_ARGUMENTS) {
        std::cout <<
        "usage: run_sim ownship_port adsb_port radar_port tcas_port" <<
        std::endl;
    }
    else {
        pthread_t threads[NUM_THREADS];
        thread_args_t ownship_args, adsb_args, radar_args, tcas_args;

        ownship_args.id = OWNSHIP_THREAD_INDEX;
        ownship_args.port = (in_port_t) atoi(argv[OWNSHIP_THREAD_INDEX + 1]);
        ownship_args.send = sendOwnshipReports;

        adsb_args.id = ADSB_THREAD_INDEX;
        adsb_args.port = (in_port_t) atoi(argv[ADSB_THREAD_INDEX + 1]);
        adsb_args.send = sendAdsbReports;

        radar_args.id = RADAR_THREAD_INDEX;
        radar_args.port = (in_port_t) atoi(argv[RADAR_THREAD_INDEX + 1]);
        radar_args.send = sendRadarReports;

        tcas_args.id = TCAS_THREAD_INDEX;
        tcas_args.port = (in_port_t) atoi(argv[TCAS_THREAD_INDEX + 1]);
        tcas_args.send = sendTcasReports;

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

    // Deallocate any global objects allocated by the protobuf library.
    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
