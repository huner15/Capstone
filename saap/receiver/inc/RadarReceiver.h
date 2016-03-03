/*
 * @file RadarReceiver.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-28-16
 * @brief An RadarReceiver is a DeviceReceiver which implements the
 * functionality necessary to receive reports from an Radar device.
 */

#ifndef RADAR_RECEIVER_H_
#define RADAR_RECEIVER_H_

#include <radar.pb.h>

#include "DeviceReceiver.h"

/**
 * An RadarReceiver is a DeviceReceiver which implements the functionality
 * necessary to receive reports from a Radar device.
 */
class RadarReceiver: public DeviceReceiver {
public:
    /**
     * Create a new RadarReceiver on the specified network port which connect
     * to the specified host device.
     * @param host the device IP address
     * @param port the network port on which to receive data
     * @param report_receiver the interface to the correlation engine
     */
    RadarReceiver(std::string host, in_port_t port,
                  ReportReceiver& report_receiver);

    virtual void ReceiveReport(ClientSocket& client_socket);

    /**
     * Print the contents of a RadarReport.
     */
    void PrintReport(RadarReport& radar_report);
};

#endif
