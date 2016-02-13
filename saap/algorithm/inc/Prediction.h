/**
* @file Prediction.h
* @author Specific Atomics
* @author Andrea Savage
* @date 1-19-16
* @brief Holds the Prediction history structs.
*/

#ifndef SAAS_PREDICTION_H
#define SAAS_PREDICTION_H

#include "CorrelationAircraft.h"
#include "Velocity.h"

using namespace std;

/**
 * A struct that holds the layout of the airspace during one
 * evaluation of the Correlation Engine. The location, heading,
 * identifiers, and elevation are recorded for each aircraft.
 */
typedef struct Snapshot
{
    vector<CorrelationAircraft> aircraft; /** Collection of aircraft. */
    int64_t counterVal; /** Timestamp to order the Snapshots. */
} Snapshot;

/*
 * A struct to hold the last three Snapshots of the airspace.
 */
typedef struct History
{
    Snapshot last; /** The most recent Snapshot. */
    Snapshot secondToLast; /** The second to last Snapshot. */
    Snapshot thirdToLast; /** The third most recent Snapchat. */
} History;

Velocity PredictVector(CorrelationAircraft aircraft);

CorrelationAircraft SearchRadarID(int radarID);

CorrelationAircraft SearchTailNum(int tailNum);

int AddAircraft(CorrelationAircraft aircraft);

int AddSnapshot();

#endif //SAAS_PREDICTION_H
