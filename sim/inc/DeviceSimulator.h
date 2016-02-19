/**
 * @file DeviceSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#ifndef DEVICE_SIMULATOR_H_
#define DEVICE_SIMULATOR_H_

#include "ServerSocket.h"
#include "FlightSimulation.h"

class DeviceSimulator {
protected:
    in_port_t _port;
    //ServerSocket _server_socket;

    FlightSimulation *_flight_simulation;

public:
    DeviceSimulator(in_port_t port, FlightSimulation *flight_simulation);

    void Simulate();

    virtual void SendReports(ServerSocket client_socket) = 0;

    virtual void SendReport(ServerSocket client_socket,
                            FlightReport* flight_report) = 0;
};

#endif
