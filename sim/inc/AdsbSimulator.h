/**
 * @file AdsbSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#ifndef ADSB_SIMULATOR_H_
#define ADSB_SIMULATOR_H_

#include "DetectionDeviceSimulator.h"

class AdsbSimulator: public DetectionDeviceSimulator {
private:
public:
    AdsbSimulator(in_port_t port, FlightSimulation& flight_simulation):
            DetectionDeviceSimulator(port, flight_simulation) {};

    void SendReport(ServerSocket& client_socket, FlightReport& flight_report);
};

#endif
