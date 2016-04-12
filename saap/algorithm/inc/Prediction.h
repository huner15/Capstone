/**
* @file Prediction.h
* @author Specific Atomics
* @author Dat Tran
* @date 1-19-16
* @brief Utilized for predictions to support correlation algorithm
*/

#ifndef PREDICTION_H
#define PREDICTION_H

#include "CorrelationAircraft.h"
#include "History.h"
#include "Snapshot.h"
#include "Velocity.h"

/**
 * The prediction class utilizes the history and interpolates data to support the correlation algorithm
 */
class Prediction {
private:
    /** A history of the airspace */
    History *_history;
    /** The current snapshot*/
    Snapshot *_current_snapshot;
    /** A snapshot counter*/
    int _snapshot_counter = 0;
public:
    Prediction();
    ~Prediction();
    /*
     * Converts a Cluster to a CDTIReport and adds
     * the CDTIReport to the current Snapshot.
     * Checks if Snapshot.aircraft is initialized
     *
     * @param aircraft The Correlation Aircraft to add
     * @return int 0 for success, 1 for an error
     */
    int AddAircraft(CorrelationAircraft *aircraft);

    /*
     * Writes the current Snapshot to the History
     * file and increments the Snapshot counter.
     * Called when all current Reports have been
     * processed by the SAAP.
     * Creates History and History file if not
     * already initialized.
     *
     */
    void TakeSnapshot();

    /**
     * Accessor to history
     *
     * @return The history of the airspace
     */
    History* GetHistory();

    /**
     * Accessor to current snapshot
     *
     * @return The current snapshot
     */
    Snapshot* GetCurrentSnapshot();

    /**
     * Accessor to the snapshot counter
     *
     * @return The number of snapshots taken
     */
    int GetSnapshotCounter();

    /*
     * Looks for the given tailNum in the last three
     * Snapshots of the History.
     *
     * @param tail_num the tail number to search for
     * @return Cluster the found cluster(s) or NULL
     * if none located.
     */
    CorrelationAircraft SearchTailNum(TailNumber tail_number);

    /*
     * Looks for the given TCAS ID in the last three
     * Snapshots of the History.
     *
     * @param tcas_id the tail number to search for
     * @return Cluster the found cluster(s) or NULL
     * if none located.
     */
    CorrelationAircraft SearchTcasID(TcasID tcas_id);

    /*
     * Looks for the given radarID in the last three
     * Snapshots of the History.
     *
     * @param radarID The ID number to search for
     * @return Cluster the found cluster(s) or NULL
     * if none located.
     */
    CorrelationAircraft SearchRadarID(RadarID radar_id);

    /*
     * Calculates the predicted velocity for the given
     * CorrelationAircraft data.
     *
     * @param aircraft The aircraft to evaluate a prediction velocity for
     * @return Vector The predicted aircraft trajectory
     */
    Velocity PredictVelocity(CorrelationAircraft *aircraft, bool is_relative);

    /**
     * Calculates the predicted location for the CorrelationAircraft data
     *
     * @param aircraft The aircraft to evaluate a predicted location for
     * @return The predicted location
     */
    GeographicCoordinate PredictLocation(CorrelationAircraft *aircraft);
};
#endif //PREDICTION_H
