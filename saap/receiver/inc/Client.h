/*
 * @file Client.h
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO make description
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "DeviceReceiver.h"
#include "OwnshipReceiver.h"
#include "AdsbReceiver.h"
#include "RadarReceiver.h"
#include "TcasReceiver.h"

/** Expected number of command line arguments. */
const int EXPECTED_ARGUMENTS = 6;

/** Total number of threads. */
const int NUM_THREADS = 4;

/** Self defined thread identification numbers. */
const int OWNSHIP_THREAD_INDEX = 0;
const int ADSB_THREAD_INDEX = 1;
const int RADAR_THREAD_INDEX = 2;
const int TCAS_THREAD_INDEX = 3;

#endif
