/*
 * @file Client.cpp
 * @author Specific Atomics
 * @author Frank Poole, Alanna Buss
 * @date 4-14-16
 * @brief Starts the correlation engine - including receivers for ADS-B, TCAS,
 * Radar, and Ownship devices.
 */

#include "Client.h"

Client::Client(ReportReceiver& report_receiver, CorrelationEngine&
correlation_engine, Categorizer& categorizer,
               std::string sim_host,
               in_port_t ownship_port, in_port_t adsb_port,
               in_port_t radar_port, in_port_t tcas_port,
               std::string cdti_host, in_port_t cdti_port)
        : _report_receiver(report_receiver),
          _correlation_engine(correlation_engine), _categorizer(categorizer),
          _sim_host(sim_host),
          _ownship_port(ownship_port), _adsb_port(adsb_port),
          _radar_port(radar_port), _tcas_port(tcas_port),
          _cdti_host(cdti_host), _cdti_port(cdti_port) {
    _is_connected = true;
    try {
        _cdti_socket = new ClientSocket(cdti_host, cdti_port);
    }
    catch (SocketException exception) {
        std::cout <<
                "Could not connect to CDTI invalid ip address or port number."
        << std::endl;
        exit(EXIT_SUCCESS);
    }
}

void *StartReceiver(void *device_receiver) {
    ((DeviceReceiver *) device_receiver)->Receive();
    pthread_exit(NULL);
}

void* TimerThreadFunction(void *classReference) {
    double elapsed_time = 0;

    clock_t this_time = clock();
    clock_t last_time = this_time;

    // CLOCKS_PER_SEC is how many units clock() has per second.
    while (((Client *) classReference)->GetIsConnected()) {
        this_time = clock();

        elapsed_time += (double) (this_time - last_time);

        last_time = this_time;

        if (elapsed_time > (double) CLOCKS_PER_SEC) {
            elapsed_time -= (double) CLOCKS_PER_SEC;
            ((Client *)classReference)->Process();
        }
    }

    ((Client *) classReference)->Process();

    pthread_exit(NULL);
}

bool Client::StartReceivers() {
    pthread_t threads[NUM_THREADS];
    pthread_t countThread;

    // Create a receiver for every device type.
    OwnshipReceiver ownship_receiver(_sim_host, _ownship_port,
                                     _report_receiver);
    AdsbReceiver adsb_receiver(_sim_host, _adsb_port, _report_receiver);
    RadarReceiver radar_receiver(_sim_host, _radar_port, _report_receiver);
    TcasReceiver tcas_receiver(_sim_host, _tcas_port, _report_receiver);

    // Create an independent thread for each device receiver.
    pthread_create(&threads[OWNSHIP_THREAD_INDEX], NULL, StartReceiver,
                   (void *) &ownship_receiver);
    pthread_create(&threads[ADSB_THREAD_INDEX], NULL, StartReceiver,
                   (void *) &adsb_receiver);
    pthread_create(&threads[RADAR_THREAD_INDEX], NULL, StartReceiver,
                   (void *) &radar_receiver);
    pthread_create(&threads[TCAS_THREAD_INDEX], NULL, StartReceiver,
                   (void *) &tcas_receiver);

    pthread_create(&countThread, NULL, TimerThreadFunction,
                   (void *) this);

    // Wait for all threads to complete.
    pthread_join(threads[OWNSHIP_THREAD_INDEX], NULL);
    pthread_join(threads[ADSB_THREAD_INDEX], NULL);
    pthread_join(threads[RADAR_THREAD_INDEX], NULL);
    pthread_join(threads[TCAS_THREAD_INDEX], NULL);

    _is_connected = false;
    pthread_join(countThread, NULL);

    /* TODO: Join ReportReceiver counter thread and Close correlation and
     * categorization engine. */

    // Delete any global objects allocated by the protobuf library.
    google::protobuf::ShutdownProtobufLibrary();

    return true;
}

bool Client::GetIsConnected() {
    return _is_connected;
}

void Client::Process() {
    ReceivedReports reports = _report_receiver.callCorrelate();
    // TODO: Remove debug print.
    std::cout << "Received ADSB Reports Size: " << reports.GetAdsb()->size() << std::endl;
    std::cout << "Received TCAS Reports Size: " << reports.GetTcas()->size() << std::endl;
    std::cout << "Received Radar Reports Size: " << reports.GetRadar()->size() << std::endl;

    std::vector<CorrelationAircraft *>* corrAircraft =
            _correlation_engine.Correlate(reports);
    // TODO: Remove debug print.
    std::cout << "Correlation Aircraft Size: " << corrAircraft->size() << std::endl;

    if (corrAircraft != NULL) {
        CDTIReport* cdtiReport = _categorizer.Categorize(corrAircraft);
        *_cdti_socket << *cdtiReport;
    }
}
