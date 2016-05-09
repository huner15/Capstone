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

#include "DeviceReceiver.h"
#include "OwnshipReceiver.h"
#include "AdsbReceiver.h"
#include "RadarReceiver.h"
#include "TcasReceiver.h"

/** Expected number of command line arguments. */
const int EXPECTED_ARGUMENTS = 7;

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

    /** Host machine IP address. */
    std::string _host;

    /** Device simulator port numbers. */
    in_port_t _ownship_port;
    in_port_t _adsb_port;
    in_port_t _radar_port;
    in_port_t _tcas_port;

    /** CDTI port number. */
    in_port_t _cdti_port;

    /** Stops the TimerThreadFunction when false */
    bool _is_connected;




public:
    Client(ReportReceiver& report_receiver, in_port_t ownship_port,
           in_port_t adsb_port, in_port_t radar_port, in_port_t tcas_port,
           in_port_t cdti_port);

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
