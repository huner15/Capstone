/**
 * @file DeviceSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "DeviceSimulator.h"

DeviceSimulator::DeviceSimulator(in_port_t port,
                                 FlightSimulation *flight_simulation) {
    _port = port;
    //_server_socket = ServerSocket(port);
    _flight_simulation = flight_simulation;
}

void DeviceSimulator::Simulate() {
    try {
        ServerSocket server_socket = ServerSocket(_port);
        ServerSocket client_socket;
        server_socket.accept(client_socket);
        std::cout << "Client has connected." << std::endl;
        this->SendReports(client_socket);
    }
    catch (SocketException &e) {
        std::cout << "Exception caught: " << e.description() << std::endl;
    }
}
