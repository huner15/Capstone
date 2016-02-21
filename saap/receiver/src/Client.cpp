/*
 * @file Client.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO: Description
 */

#include "Client.h"

void *startReceiver(void *device_receiver) {
    ((DeviceReceiver *) device_receiver)->Receive();
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
        std::string host (argv[1]);

        // Create a receiver for every device type.
        OwnshipReceiver ownship_receiver(
                host,(in_port_t) atoi(argv[OWNSHIP_THREAD_INDEX + 2]));
        AdsbReceiver adsb_receiver(
                host, (in_port_t) atoi(argv[ADSB_THREAD_INDEX + 2]));
        RadarReceiver radar_receiver(
                host, (in_port_t) atoi(argv[RADAR_THREAD_INDEX + 2]));
        TcasReceiver tcas_receiver(
                host, (in_port_t) atoi(argv[TCAS_THREAD_INDEX + 2]));

        // Create an independent thread for each device receiver.
        pthread_create(&threads[OWNSHIP_THREAD_INDEX], NULL, startReceiver,
                       (void *) &ownship_receiver);
        pthread_create(&threads[ADSB_THREAD_INDEX], NULL, startReceiver,
                       (void *) &adsb_receiver);
        pthread_create(&threads[RADAR_THREAD_INDEX], NULL, startReceiver,
                       (void *) &radar_receiver);
        pthread_create(&threads[TCAS_THREAD_INDEX], NULL, startReceiver,
                       (void *) &tcas_receiver);

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
