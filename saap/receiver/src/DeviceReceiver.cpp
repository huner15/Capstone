/*
 * @file DeviceReceiver.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO make description
 */

#include "DeviceReceiver.h"

DeviceReceiver::DeviceReceiver(std::string host, in_port_t port) {
    _host = host;
    _port = port;
}

void DeviceReceiver::Receive() {
    try {
        ClientSocket client_socket(_host, _port);
        std::cout << "Connected to device at " << _host << ", on port "<< _port
        << std::endl;

        try {
            while (true) {
                ReceiveReport(client_socket);
            }
        }
        catch (SocketException& exception) {
            std::cout << "Device connection closed." <<std::endl;
        }
    }
    catch (SocketException &e) {
        std::cout << "Exception caught: " << e.description() << std::endl;
    }
}
