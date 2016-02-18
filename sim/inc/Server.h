/**
 * @file Server.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-18-16
 * @brief TODO: Description
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

#include <adsb.pb.h>
#include <ownship.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>

#include "SimulationFlightsIO.h"
#include "ServerSocket.h"
#include "DeviceSimulator.h"
#include "RadarSimulator.h"

/** Expected number of command line arguments. */
const int EXPECTED_ARGUMENTS = 6;

/** Total number of threads. */
const int NUM_THREADS = 4;

/** Self defined thread identification numbers. */
const int OWNSHIP_THREAD_INDEX = 0;
const int ADSB_THREAD_INDEX = 1;
const int RADAR_THREAD_INDEX = 2;
const int TCAS_THREAD_INDEX = 3;

/** Time to sleep in seconds before sending the next report. */
const int SLEEP_TIME = 1;

int main(int argc, char *argv[]);

#endif
