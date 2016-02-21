/*
 * @file DeviceReceiver.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO make description
 */

#ifndef DEVICE_RECEIVER_H
#define DEVICE_RECEIVER_H

#include <string>

#include "ClientSocket.h"

class DeviceReceiver {
private:
    std::string _host;
    in_port_t _port;

public:
    DeviceReceiver() {};

    DeviceReceiver(std::string host, in_port_t port);

    void Receive();

    virtual void ReceiveReport(ClientSocket& client_socket) = 0;
};

#endif
