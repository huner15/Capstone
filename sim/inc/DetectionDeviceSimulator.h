/**
 * @file DetectionDeviceSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief A Detection Device Simulator represents the subset of Device
 * Simulators which may send multiple reports within each 1 Hz logic cycle.
 */

#ifndef DETECTION_DEVICE_SIMULATOR_H_
#define DETECTION_DEVICE_SIMULATOR_H_

#include "DeviceSimulator.h"

/**
 * A Detection Device Simulator represents the abstract subset of
 * DeviceSimulators which may send multiple reports within each 1 Hz logic
 * cycle.
 */
class DetectionDeviceSimulator: public DeviceSimulator {
public:
    /**
     * Create a new DetectionDeviceSimulator on the specified TCP/IP network
     * port and using the specified flight simulation data.
     * @param port the simulation network port
     * @param flight_simulation the flight simulation data to send
     */
    DetectionDeviceSimulator(in_port_t port,
                             FlightSimulation& flight_simulation):
            DeviceSimulator(port, flight_simulation) {};

    virtual void SendReports(ServerSocket& client_socket);

    virtual void SendReport(ServerSocket& client_socket,
                            FlightReport& flight_report) = 0;
};

#endif
