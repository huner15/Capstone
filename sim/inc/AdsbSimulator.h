/**
 * @file AdsbSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief An AdsbSimulator represents a specific type of a aircraft detection
 * device simulator which simulates the behavior of an actual ADS-B device.
 */

#ifndef ADSB_SIMULATOR_H_
#define ADSB_SIMULATOR_H_

#include "DetectionDeviceSimulator.h"

/**
 * An AdsbSimulator represents a specific type of a aircraft detection device
 * simulator which simulates the behavior of an actual ADS-B device.
 */
class AdsbSimulator: public DetectionDeviceSimulator {
public:
    /**
     * Create a new AdsbSimulator with the specified flight simulation data and
     * the on the specified network port.
     * @param port the simulation network port
     * @param flight_simulation the flight simulation data to send
     */
    AdsbSimulator(in_port_t port, FlightSimulation& flight_simulation);

    virtual void SendReport(ServerSocket& client_socket,
                            FlightReport& flight_report);
};

#endif
