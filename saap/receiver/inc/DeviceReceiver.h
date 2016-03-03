/*
 * @file DeviceReceiver.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-28-16
 * @brief A DeviceReceiver is an abstract representation of an aircraft
 * surveillance device data report receiver.
 */

#ifndef DEVICE_RECEIVER_H_
#define DEVICE_RECEIVER_H_

#include <string>

#include "ClientSocket.h"
#include "ReportReceiver.h"

/**
 * A DeviceReceiver is an abstract representation of an aircraft surveillance
 * device data report receiver. Surveillance device data is expected to received
 * on separate TCP/IP network ports and this abstract receiver is designed to
 * exist in it's own thread. Receiving behavior is dependent on te behavior of
 * ReceiveReport() for a specific device type.
 */
class DeviceReceiver {
private:
    /** Connected device IP address. */
    std::string _host;

    /** Receiver network port. */
    in_port_t _port;

protected:
    /** Sense and avoid engine interface. */
    ReportReceiver _report_receiver;

public:
    /**
     * Create a new DeviceReceiver on the specified network port which connect
     * to the specified host device.
     * @param host the device IP address
     * @param port the network port on which to receive data
     * @param report_receiver the interface to the correlation engine
     */
    DeviceReceiver(std::string host, in_port_t port,
                   ReportReceiver& report_receiver);

    /**
     * Continually wait for and receive reports from the connected device until
     * the connection is severed.
     */
    void Receive();

    /**
     * Receive a single report from the client socket and forward that report to
     * the ReportReceiver.
     * @param client_socket the network socket on which to receive device data
     */
    virtual void ReceiveReport(ClientSocket& client_socket) = 0;
};

#endif
