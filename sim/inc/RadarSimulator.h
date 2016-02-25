/**
 * @file RadarSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#ifndef RADAR_SIMULATOR_H_
#define RADAR_SIMULATOR_H_

#include "DetectionDeviceSimulator.h"

class RadarSimulator: public DetectionDeviceSimulator {
private:
public:
    RadarSimulator(in_port_t port, FlightSimulation& flight_simulation):
            DetectionDeviceSimulator(port, flight_simulation) {};

    void SendReport(ServerSocket& client_socket, FlightReport& flight_report);
};

#endif
