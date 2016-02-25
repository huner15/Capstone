/**
 * @file Server.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "Server.h"

void* StartSimulation(void *device_simulator) {
    ((DeviceSimulator *) device_simulator)->Simulate();
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

        // Create a simulator of each device type using the simulation data.
        OwnshipSimulator ownship_simulator(
                (in_port_t) atoi(argv[OWNSHIP_THREAD_INDEX + 2]), fs);
        AdsbSimulator adsb_simulator(
                (in_port_t) atoi(argv[ADSB_THREAD_INDEX + 2]), fs);
        RadarSimulator radar_simulator(
                (in_port_t) atoi(argv[RADAR_THREAD_INDEX + 2]), fs);
        TcasSimulator tcas_simulator(
                (in_port_t) atoi(argv[TCAS_THREAD_INDEX + 2]), fs);

        // Create a new thread for each device simulation.
        pthread_create(&threads[OWNSHIP_THREAD_INDEX], NULL, StartSimulation,
                       (void *) &ownship_simulator);
        pthread_create(&threads[ADSB_THREAD_INDEX], NULL, StartSimulation,
                       (void *) &adsb_simulator);
        pthread_create(&threads[RADAR_THREAD_INDEX], NULL, StartSimulation,
                       (void *) &radar_simulator);
        pthread_create(&threads[TCAS_THREAD_INDEX], NULL, StartSimulation,
                       (void *) &tcas_simulator);

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
