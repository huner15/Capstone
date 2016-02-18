/**
 * @file RadarSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#ifndef RADAR_SIMULATOR_H_
#define RADAR_SIMULATOR_H_

#include "DeviceSimulator.h"

class RadarSimulator: public DeviceSimulator {
private:
public:
    RadarSimulator(int id, in_port_t port, FlightSimulation *flightSimulation):
            DeviceSimulator(id, port, flightSimulation) {};

    void sendReport(ServerSocket serverSocket, FlightReport* flightReport);
};

#endif
