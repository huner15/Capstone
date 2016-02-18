/**
 * @file DeviceSimulator.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#include "DeviceSimulator.h"

DeviceSimulator::DeviceSimulator(int id, in_port_t port,
                                 FlightSimulation *flightSimulation) {
    _id = id;
    _port = port;
    _flight_simulation = flightSimulation;
}
