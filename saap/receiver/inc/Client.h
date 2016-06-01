/*
 * @file Client.h
 * @author Specific Atomics
 * @author Frank Poole, Alanna Buss
 * @date 4-14-16
 * @brief Declares constants used by the client application.
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <cdti.pb.h>

#include "DeviceReceiver.h"
#include "OwnshipReceiver.h"
#include "AdsbReceiver.h"
#include "RadarReceiver.h"
#include "TcasReceiver.h"
#include "CorrelationEngine.h"
#include "Categorizer.h"
//#include "ClusterConverter.h"
#include "ProcessorLogger.h"

class ProcessorLogger;

/** Expected number of command line arguments. */
const int EXPECTED_ARGUMENTS = 8;

/** Total number of threads. */
const int NUM_THREADS = 4;

/** Self defined thread identification numbers. */
const int OWNSHIP_THREAD_INDEX = 0;
const int ADSB_THREAD_INDEX = 1;
const int RADAR_THREAD_INDEX = 2;
const int TCAS_THREAD_INDEX = 3;

/** CDTI argument index reference. */
const int CDTI_INDEX = 4;

class Client {
private:
    /** Correlation engine report receiver. */
    ReportReceiver& _report_receiver;

    /** Correlation Engine to send ReceivedReports to */
    Correlator& _correlator;

    /**ClusterConverter to send Clusters to */
  //  ClusterConverter &_converter;

    /** Categorizer to send CorrelationAircraft to */
    Categorizer& _categorizer;

    /** Simulator host machine IP address. */
    std::string _sim_host;

    /** Device simulator port numbers. */
    in_port_t _ownship_port;
    in_port_t _adsb_port;
    in_port_t _radar_port;
    in_port_t _tcas_port;

    /** CDTI host machine IP adrress. */
    std::string _cdti_host;

    /** CDTI port number. */
    in_port_t _cdti_port;

    /** CDTI socket connected to cdti_host on cdti_port */
    ClientSocket* _cdti_socket;
    bool _is_cdti_connected;

    /** Stops the TimerThreadFunction when false */
    bool _is_connected;

    /** Count completed processing steps. */
    int _processing_step;

    /** Logger that documents each of the received data types. */
    ProcessorLogger* _logger;

    ReceivedReports *Convert(ReceivedReports *reports);

public:
    Client(ReportReceiver& report_receiver, Correlator&
           correlation_engine,
           Categorizer& categorizer,
           std::string sim_host,
           in_port_t ownship_port, in_port_t adsb_port,
           in_port_t radar_port, in_port_t tcas_port,
           std::string cdti_host, in_port_t cdti_port);

    bool StartReceivers();

    /**
     * Gets whether the Client is connected to the SimulationServer
     * @return true if the Client is connected to the SimulationServer, false
     * if not.
     */
    bool GetIsConnected();

    /**
     * Calls the functions in ReportReceiver, CorrelationEngine and
     * CategorizationEngine to get all of the data moved. Once a verifier is
     * created it should be called with the second by second data in this
     * function
     */
    void Process();
};

#endif
