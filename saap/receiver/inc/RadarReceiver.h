/*
 * @file RadarReceiver.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO make description
 */

#ifndef RADAR_RECEIVER_H_
#define RADAR_RECEIVER_H_

#include <radar.pb.h>
#include "DeviceReceiver.h"

class RadarReceiver: public DeviceReceiver {
public:
    RadarReceiver(std::string host, in_port_t port):
    DeviceReceiver(host, port) {};

    void ReceiveReport(ClientSocket& client_socket);

    void PrintReport(RadarReport& radar_report);
};

#endif
