/**
 * @file DeviceSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "DeviceSimulator.h"

DeviceSimulator::DeviceSimulator(in_port_t port,
                                 FlightSimulation& flight_simulation):
        _flight_simulation(flight_simulation) {
    _port = port;
}

void DeviceSimulator::Simulate() {
    try {
        ServerSocket server_socket = ServerSocket(_port);
        std::cout << "Simulator running on port: " << _port << std::endl;
        ServerSocket client_socket;
        server_socket.accept(client_socket);
        std::cout << "Client has connected on port: " << _port << std::endl;
        this->SendReports(client_socket);
        std::cout << "Closing connection on port: " << _port << std::endl;
    }
    catch (SocketException &e) {
        std::cout << "Exception caught: " << e.description() << std::endl;
    }
}
