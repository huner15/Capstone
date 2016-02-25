/*
 * @file TcasReceiver.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO make description
 */

#ifndef TCAS_RECEIVER_H_
#define TCAS_RECEIVER_H_

#include <tcas.pb.h>
#include "DeviceReceiver.h"

class TcasReceiver: public DeviceReceiver {
public:
    TcasReceiver(std::string host, in_port_t port,
                 ReportReceiver& report_receiver):
            DeviceReceiver(host, port, report_receiver) {
    };

    void ReceiveReport(ClientSocket& client_socket);

    void PrintReport(TcasReport& tcas_report);
};

#endif
