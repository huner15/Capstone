/**
 * @file Server.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-25-16
 * @brief The simulation server maintains multiple device simulators on
 * individual threads to simulate flight data.
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

#include "SimulationFlightsIO.h"

#include "DeviceSimulator.h"
#include "DetectionDeviceSimulator.h"
#include "OwnshipSimulator.h"
#include "AdsbSimulator.h"
#include "RadarSimulator.h"
#include "TcasSimulator.h"

/** Expected number of command line arguments. */
const int EXPECTED_ARGUMENTS = 6;

/** Total number of threads. */
const int NUM_THREADS = 4;

/** Self defined thread identification numbers. */
const int OWNSHIP_THREAD_INDEX = 0;
const int ADSB_THREAD_INDEX = 1;
const int RADAR_THREAD_INDEX = 2;
const int TCAS_THREAD_INDEX = 3;

/**
 * Start a multithreaded simulation server which simulates ADS-B, TCAS, Radar,
 * and Ownship devices on separate network ports.
 * usage: run_sim flight_simulation.json ownship_port adsb_port radar_port
 * tcas_port"
 * @param argc the number of command line arguments (including the
 * executable's name)
 * @param argv the command line arguments
 */
int main(int argc, char *argv[]);

#endif
