/**
 * @file OwnshipSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#ifndef OWNSHIP_SIMULATOR_H_
#define OWNSHIP_SIMULATOR_H_

#include "DeviceSimulator.h"

class OwnshipSimulator: public DeviceSimulator {
public:
    OwnshipSimulator(in_port_t port, FlightSimulation& flight_simulation):
            DeviceSimulator(port, flight_simulation) {};

    void SendReports(ServerSocket& client_socket);

    void SendReport(ServerSocket& client_socket, FlightReport& flight_report);
};

#endif
