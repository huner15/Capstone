/*
 * @file Client.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO: Description
 */

#include "Client.h"

void *StartReceiver(void *device_receiver) {
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
        ReportReceiver report_receiver;

        // Create a receiver for every device type.
        OwnshipReceiver ownship_receiver(
                host, (in_port_t) atoi(argv[OWNSHIP_THREAD_INDEX + 2]),
                report_receiver);
        AdsbReceiver adsb_receiver(
                host, (in_port_t) atoi(argv[ADSB_THREAD_INDEX + 2]),
                report_receiver);
        RadarReceiver radar_receiver(
                host, (in_port_t) atoi(argv[RADAR_THREAD_INDEX + 2]),
                report_receiver);
        TcasReceiver tcas_receiver(
                host, (in_port_t) atoi(argv[TCAS_THREAD_INDEX + 2]),
                report_receiver);

        // Create an independent thread for each device receiver.
        pthread_create(&threads[OWNSHIP_THREAD_INDEX], NULL, StartReceiver,
                       (void *) &ownship_receiver);
        pthread_create(&threads[ADSB_THREAD_INDEX], NULL, StartReceiver,
                       (void *) &adsb_receiver);
        pthread_create(&threads[RADAR_THREAD_INDEX], NULL, StartReceiver,
                       (void *) &radar_receiver);
        pthread_create(&threads[TCAS_THREAD_INDEX], NULL, StartReceiver,
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
