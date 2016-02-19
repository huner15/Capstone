/**
 * @file Server.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "Server.h"

void *startSimulation(void *device_simulator) {
    ((DeviceSimulator*) device_simulator)->Simulate();
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
        FlightSimulation fs = SimulationFlightsIO::ReadFile(argv[1]);

        OwnshipSimulator ownship_simulator(
                (in_port_t) atoi(argv[OWNSHIP_THREAD_INDEX + 2]), &fs);
        /*
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
        */

        // Create a new thread for each device simulation.
        pthread_create(&threads[OWNSHIP_THREAD_INDEX], NULL, startSimulation,
                       (void *) &ownship_simulator);
        /*
        pthread_create(&threads[ADSB_THREAD_INDEX], NULL, startThread,
                       (void *) &adsb_args);
        pthread_create(&threads[RADAR_THREAD_INDEX], NULL, startThread,
                       (void *) &radar_args);
        pthread_create(&threads[TCAS_THREAD_INDEX], NULL, startThread,
                       (void *) &tcas_args);
        */

        // Wait for all threads to complete.
        pthread_join(threads[OWNSHIP_THREAD_INDEX], NULL);
        /*
        pthread_join(threads[ADSB_THREAD_INDEX], NULL);
        pthread_join(threads[RADAR_THREAD_INDEX], NULL);
        pthread_join(threads[TCAS_THREAD_INDEX], NULL);
        */
    }

    // Deallocate any global objects allocated by the protobuf library.
    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
