/*
 * @file DeviceReceiver.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief Implements the functionality of a DeviceReceiver.
 */

#include "DeviceReceiver.h"

DeviceReceiver::DeviceReceiver(std::string host, in_port_t port,
                               ReportReceiver& report_receiver):
        _report_receiver(report_receiver) {
    _host = host;
    _port = port;
}

void DeviceReceiver::Receive() {
    try {
        ClientSocket client_socket(_host, _port);
        std::cout << "Connected to " << _host << " on port "<< _port
        << std::endl;

        try {
            while (true) {
                ReceiveReport(client_socket);
            }
        }
        catch (SocketException& exception) {
            std::cout << "Device connection closed on port " << _port
            << std::endl;
        }
    }
    catch (SocketException &e) {
        std::cout << "Exception caught: " << e.description() << std::endl;
    }
}
