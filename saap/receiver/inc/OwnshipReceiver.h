/*
 * @file OwnshipReceiver.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO make description
 */

#ifndef OWNSHIP_RECEIVER_H_
#define OWNSHIP_RECEIVER_H_

#include <ownship.pb.h>
#include "DeviceReceiver.h"

class OwnshipReceiver: public DeviceReceiver {
private:
public:
    OwnshipReceiver(std::string host, in_port_t port):
            DeviceReceiver(host, port) {};

    void ReceiveReport(ClientSocket& client_socket);

    void PrintReport(OwnshipReport& ownshipReport);
};

#endif
