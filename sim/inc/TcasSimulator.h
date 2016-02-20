/**
 * @file TcasSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#ifndef TCAS_SIMULATOR_H_
#define TCAS_SIMULATOR_H_

#include "DetectionDeviceSimulator.h"

class TcasSimulator: public DetectionDeviceSimulator {
private:
public:
    TcasSimulator(in_port_t port, FlightSimulation *flight_simulation):
            DetectionDeviceSimulator(port, flight_simulation) {};

    void SendReport(ServerSocket& client_socket, FlightReport& flight_report);
};

#endif
