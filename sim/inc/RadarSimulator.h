/**
 * @file RadarSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief An RadarSimulator represents a specific type of a aircraft detection
 * device simulator which simulates the behavior of an actual Radar device.
 */

#ifndef RADAR_SIMULATOR_H_
#define RADAR_SIMULATOR_H_

#include "DetectionDeviceSimulator.h"

/**
 * An RadarSimulator represents a specific type of a aircraft detection device
 * simulator which simulates the behavior of an actual Radar device.
 */
class RadarSimulator: public DetectionDeviceSimulator {
public:
    /**
     * Create a new RadarSimulator with the specified flight simulation data and
     * the on the specified network port.
     * @param port the simulation network port
     * @param flight_simulation the flight simulation data to send
     */
    RadarSimulator(in_port_t port, FlightSimulation& flight_simulation);

    virtual void SendReport(ServerSocket& client_socket,
                            FlightReport& flight_report);
};

#endif
