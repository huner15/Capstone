/*
 * @file OwnshipReceiver.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-28-16
 * @brief An OwnshipReceiver is a DeviceReceiver which implements the
 * functionality necessary to receive reports from an Ownship navigation device.
 */

#ifndef OWNSHIP_RECEIVER_H_
#define OWNSHIP_RECEIVER_H_

#include <ownship.pb.h>

#include "DeviceReceiver.h"

/**
 * An OwnshipReceiver is a DeviceReceiver which implements the functionality
 * necessary to receive reports from an Ownship navigation device.
 */
class OwnshipReceiver: public DeviceReceiver {
public:
    /**
    * Create a new OwnshipReceiver on the specified network port which connect
    * to the specified host device.
    * @param host the device IP address
    * @param port the network port on which to receive data
    * @param report_receiver the interface to the correlation engine
    */
    OwnshipReceiver(std::string host, in_port_t port,
                    ReportReceiver& report_receiver);

    virtual void ReceiveReport(ClientSocket& client_socket);

    /**
     * Print the contents of an OwnshipReport to standard out.
     */
    void PrintReport(OwnshipReport& ownshipReport);
};

#endif
