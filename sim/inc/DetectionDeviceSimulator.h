/**
 * @file DetectionDeviceSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#ifndef DETECTION_DEVICE_SIMULATOR_H_
#define DETECTION_DEVICE_SIMULATOR_H_

#include "DeviceSimulator.h"

class DetectionDeviceSimulator: public DeviceSimulator {
public:
    DetectionDeviceSimulator(in_port_t port,
                             FlightSimulation *flight_simulation):
            DeviceSimulator(port, flight_simulation) {};

    void SendReports(ServerSocket client_socket);

    virtual void SendReport(ServerSocket client_socket,
                            FlightReport* flight_report) = 0;
};

#endif
