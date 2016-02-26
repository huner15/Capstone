/**
 * @file TcasSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief An TcasSimulator represents a specific type of a aircraft detection
 * device simulator which simulates the behavior of an actual TCAS device.
 */

#ifndef TCAS_SIMULATOR_H_
#define TCAS_SIMULATOR_H_

#include "DetectionDeviceSimulator.h"

/**
 * An TcasSimulator represents a specific type of a aircraft detection device
 * simulator which simulates the behavior of an actual TCAS device.
 */
class TcasSimulator: public DetectionDeviceSimulator {
public:
    /**
     * Create a new TcasSimulator with the specified flight simulation data and
     * the on the specified network port.
     * @param port the simulation network port
     * @param flight_simulation the flight simulation data to send
     */
    TcasSimulator(in_port_t port, FlightSimulation& flight_simulation);

    virtual void SendReport(ServerSocket& client_socket,
                            FlightReport& flight_report);
};

#endif
