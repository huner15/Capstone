/**
 * @file DeviceSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#ifndef DEVICE_SIMULATOR_H_
#define DEVICE_SIMULATOR_H_

class DeviceSimulator {
private:
    int _id;
    in_port_t _port;
    FlightSimulation *_flight_simulation;

public:
    DeviceSimulator() {};

    DeviceSimulator(int id, in_port_t port, FlightSimulation *flightSimulation);

    virtual void sendReport(ServerSocket serverSocket,
                            FlightReport* flightReport) = 0;
};

#endif
