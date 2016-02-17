/*
 * @file Device.h
 * @author Specific Atomics
 * @authors Andy Savage, Frank Poole
 * @date 2-13-16
 * @brief Device enumerates the possible surveillance device types: Radar, TCAS,
 * and ADS-B.
 */

#ifndef DEVICE_H_
#define DEVICE_H_

/**
 * Enum representing the different device types a report can be received from:
 * Radar, TCAS, or ADS-B.
 */
enum Device {ADSB, TCAS, RADAR, OWNSHIP};

#endif
