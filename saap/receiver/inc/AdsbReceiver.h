/*
 * @file AdsbReceiver.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO make description
 */

#ifndef ADSB_RECEIVER_H_
#define ADSB_RECEIVER_H_

#include <adsb.pb.h>
#include "DeviceReceiver.h"

class AdsbReceiver: public DeviceReceiver {
public:
    AdsbReceiver(std::string host, in_port_t port,
                 ReportReceiver& report_receiver);

    void ReceiveReport(ClientSocket& client_socket);

    void PrintReport(AdsBReport& ownshipReport);
};

#endif
