/**
 * @file OwnshipSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief OwnshipSimulator simulators the behavior of an Ownship navigation
 * device.
 */

#ifndef OWNSHIP_SIMULATOR_H_
#define OWNSHIP_SIMULATOR_H_

#include "DeviceSimulator.h"

/**
 * An OwnshipSimulator represents a specific type of a aircraft detection device
 * simulator which simulates the behavior of an actual Ownship navigation
 * device.
 */
class OwnshipSimulator: public DeviceSimulator {
public:
    /**
    * Create a new OwnshipSimulator with the specified flight simulation data
    * and the on the specified network port.
    * @param port the simulation network port
    * @param flight_simulation the flight simulation data to send
    */
    OwnshipSimulator(in_port_t port, FlightSimulation& flight_simulation);

    virtual void SendReports(ServerSocket& client_socket);

    virtual void SendReport(ServerSocket& client_socket,
                            FlightReport& flight_report);
};

#endif
