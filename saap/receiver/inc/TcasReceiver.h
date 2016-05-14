/*
 * @file TcasReceiver.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-28-16
 * @brief An TcasReceiver is a DeviceReceiver which implements the functionality
 * necessary to receive reports from a TCAS device.
 */

#ifndef TCAS_RECEIVER_H_
#define TCAS_RECEIVER_H_

#include <tcas.pb.h>

#include "DeviceReceiver.h"

/**
 * An TcasReceiver is a DeviceReceiver which implements the functionality
 * necessary to receive reports from a TCAS device.
 */
class TcasReceiver: public DeviceReceiver {
public:
    /**
     * Create a new TcasReceiver on the specified network port which connect
     * to the specified host device.
     * @param host the device IP address
     * @param port the network port on which to receive data
     * @param report_receiver the interface to the correlation engine
     */
    TcasReceiver(std::string host, in_port_t port,
                 ReportReceiver& report_receiver):
            DeviceReceiver(host, port, report_receiver) {
    };

    virtual void ReceiveReport(ClientSocket& client_socket);

    /**
     * Print the contents of an TcasReport to standard out.
     */
    static void PrintReport(TcasReport& tcas_report);
};

#endif
