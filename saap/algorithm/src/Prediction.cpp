/**
* @file Prediction.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 1-19-16
* @brief Tracks the last three Snapshot seconds of CorrelationAircraft in the History.
*/

#include <Vector.h>
#include "Prediction.h"
#include "Cluster.h"

History history;
int snapshotCounter = 0;
Snapshot curSnapshot;

/*
 * Writes the current Snapshot to the History
 * file and increments the Snapshot counter.
 * Called when all current Reports have been
 * processed by the SAAP.
 * Creates History and History file if not
 * already initialized.
 *
 * @return int 0 for success, 1 for an error
 */
int addSnapshot();

/*
 * Converts a Cluster to a CDTIReport and adds
 * the CDTIReport to the current Snapshot.
 * Checks if Snapshot.aircraft is initialized
 *
 * @param aircraft The Correlation Aircraft to add
 * @return int 0 for success, 1 for an error
 */
int addAircraft(CorrelationAircraft aircraft);

/*
 * Looks for the given tailNum in the last three
 * Snapshots of the History.
 *
 * @param tailNum the tail number to search for
 * @return Cluster the found cluster(s) or NULL
 * if none located.
 */
CorrelationAircraft searchTailNum(int tailNum);

/*
 * Looks for the given radarID in the last three
 * Snapshots of the History.
 *
 * @param radarID The ID number to search for
 * @return Cluster the found cluster(s) or NULL
 * if none located.
 */
CorrelationAircraft searchRadarID(int radarID);

/*
 * Calculates the prediction vector for the given
 * CorrelationAircraft data.
 *
 * @param aircraft The aircraft to evaluate a prediction
 * vector for
 * r@return Vector The predicted aircraft trajectory
 */
Vector3D predictVector(CorrelationAircraft aircraft);