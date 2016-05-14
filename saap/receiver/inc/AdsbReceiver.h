/*
 * @file AdsbReceiver.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-28-16
 * @brief An AdsbReceiver is a DeviceReceiver which implements the functionality
 * necessary to receive reports from an ADS-B device.
 */

#ifndef ADSB_RECEIVER_H_
#define ADSB_RECEIVER_H_

#include <adsb.pb.h>

#include "DeviceReceiver.h"

/**
 * An AdsbReceiver is a DeviceReceiver which implements the functionality
 * necessary to receive reports from an ADS-B device.
 */
class AdsbReceiver: public DeviceReceiver {
public:
    /**
     * Create a new AdsbReceiver on the specified network port which connect
     * to the specified host device.
     * @param host the device IP address
     * @param port the network port on which to receive data
     * @param report_receiver the interface to the correlation engine
     */
    AdsbReceiver(std::string host, in_port_t port,
                 ReportReceiver& report_receiver);

    virtual void ReceiveReport(ClientSocket& client_socket);

    /**
     * Print the contents of an AdsbReport to standard out.
     */
    static void PrintReport(AdsBReport& ownshipReport);
};

#endif
