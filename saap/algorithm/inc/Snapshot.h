/**
* @file Snapshot.h
* @author Specific Atomics
* @author Dat Tran
* @date 2-24-16
* @brief Represents the layout of the airspace during one evaluation of the Correlation Engine.
*/

#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <ctime>
#include <vector>
#include "CorrelationAircraft.h"

/**
 * A Snapshot represents the airspace at one point in time.
 */
class Snapshot {
private:
    /** The collection of aircraft. */
    std::vector<CorrelationAircraft> * _aircraft;
    /** A timestamp of when the Snapshot was taken. */
    std::time_t _timestamp;
public:
    Snapshot();
    /**
     * Constructor to create a Snapshot
     *
     * @param aircraft Collection of aircraft
     * @param time_stamp Timestamp to order the snapshots
     */
    Snapshot(std::vector<CorrelationAircraft> *aircraft, std::time_t timestamp);
    ~Snapshot();
    /**
     * Accessor to aircraft collection
     *
     * @return The collection of aircraft
     */
    std::vector<CorrelationAircraft> *GetAircraft() const;

    /**
     * Accessor to timestamp
     *
     * @return Timestamp of snapshot
     */
    std::time_t GetTimestamp() const;
};

#endif //SNAPSHOT_H


