/**
 * @file DeviceSimulator.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief A Device Simulator is an abstract representation of an aircraft
 * surveillance device simulator.
 */

#ifndef DEVICE_SIMULATOR_H_
#define DEVICE_SIMULATOR_H_

#include "ServerSocket.h"
#include "FlightSimulation.h"

/**
 * A DeviceSimulator is an abstract representation of an aircraft surveillance
 * device simulator. A device simulation occurs on a separate TCP/IP network
 * port and is designed to exist on a separate thread. The simulation behavior
 * is dependent on the behavior of SendReports() which in turn is dependent on
 * the behavior of SendReport().
 */
class DeviceSimulator {
protected:
    /** Device simulation network port. */
    in_port_t _port;

    /** Device flight simulation data. */
    FlightSimulation& _flight_simulation;

    /** Time to sleep in seconds before sending the next report. */
    const static int _SLEEP_TIME = 1;

public:
    /**
     * Create a new Device Simulator on the specified network port, which will
     * send the specified flight simulation data.
     * @param port the simulation network port
     * @param flight_simulation the flight simulation data to send
     */
    DeviceSimulator(in_port_t port, FlightSimulation& flight_simulation);

    /**
     * Simulate a aircraft surveillance device by sending simulation data to a
     * connected client at 1 Hz.
     */
    void Simulate();

    /**
     * Send all device reports of this device simulation type to the client
     * connected on the client port.
     * @param client_socket the TCP/Ip network socket on which a simulation
     * sense and avoid processor device receiver client is connected.
     */
    virtual void SendReports(ServerSocket& client_socket) = 0;

    /**
     * Send a single device data report to the client connected on the TCP/IP
     * network socket using the specified flight report.
     * @param client_socket the TCP/Ip network socket on which a simulation
     * sense and avoid processor device receiver client is connected.
     */
    virtual void SendReport(ServerSocket& client_socket,
                            FlightReport& flight_report) = 0;
};

#endif
