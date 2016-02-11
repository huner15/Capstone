//
// Created by andrea on 1/19/16.
//
#ifndef SAAS_PREDICTION_H
#define SAAS_PREDICTION_H

#include "../../../../../.CLion12/system/cmake/generated/5c6d134d/5c6d134d/Debug/lib/gp/capstone-shared/cdti.pb.h"

/*
 * A struct to hold the last three Snapshots of the airspace.
 */
typedef struct History
{
    Snapshot last; /** The most recent Snapshot. */
    Snapshot secondToLast; /** The second to last Snapshot. */
    Snapshot thirdToLast; /** The third most recent Snapchat. */
} History;

/**
 * A struct that holds the layout of the airspace during one
 * evaluation of the Correlation Engine. The location, heading,
 * identifiers, and elevation are recorded for each aircraft.
 */
typedef struct Snapshot
{
    //Collection<CorrelationAircraft> aircraft; /** Collection of aircraft. */
    int64_t counterVal; /** Timestamp to order the Snapshots. */
} Snapshot;

/**
 * A struct that represents an individual aircraft in the airspace around
 * the ownship. Holds the evaluated current location, heading, elevation,
 * and identifiers from the Surveillance Report or Surveillance Reports
 * that were evaluated to represent this aircraft.
 * All fields may not be populated.
 */
typedef struct CorrelationAircraft
{
    int32_t bearing; /** Relative heading to the ownship. */
    int32_t altitude; /** relative geometric altitude from GPS (feet). */
    float azimuth; /** relative horizontal angle (+/- 180 degrees). */
    float elevation; /** relative vertical angle from ownship. */

    //Only one of these fields will be set
    int32_t tID; /** ID given by the TCAS hardware. */
    int32_t rID; /** ID given by the radar hardware. */
    float tail_number; /** tail number of aircraft */

    //Not instantiated when only have TCAS report and history
    float range; /** relative distance from ownship (feet). */
    float latitude; /** latitude (+/- 180 degrees). */
    float longitude; /** longitude (+/- 180 degrees). */

    //Not instantiated when only have TCAS report (can be calculated with history)
    float north; /** relative intruder velocity north (feet/sec). */
    float east; /** relative intruder velocity east (feet/sec). */
    float down; /** relative intruder velocity down (feet/sec). */

    /** Predicted vector the aircraft will be facing in following seconds. */
    Vector predictedVector;
    /** Predicted location the aircraft will be at in following seconds. */
    Vector predictedLoc;
} CorrelationAircraft;

#endif //SAAS_PREDICTION_H
