/**
* @file CorrelationAircraft.h
* @author Specific Atomics
* @author Andrea Savage
* @date 2-13-16
* @brief Constructs a CorrelationAircraft and converts a Cluster into one
 * most likely CorrelationAircraft.
*/

#ifndef SAAS_CORRELATIONAIRCRAFT_H
#define SAAS_CORRELATIONAIRCRAFT_H

#include "Cluster.h"
#include "FlightReport.h"
#include "Velocity.h"

using namespace std;

/**
 * A struct that represents an individual aircraft in the airspace around
 * the ownship. Holds the evaluated current location, heading, elevation,
 * and identifiers from the Surveillance Report or Surveillance Reports
 * that were evaluated to represent this aircraft.
 * All fields may not be populated.
 */
class CorrelationAircraft: public FlightReport {
protected:
    /** Predicted vector the aircraft will be facing in following
    * seconds. */
    Velocity _predictedVector;
    /** Predicted location the aircraft will be at in following seconds. */
    Velocity _predictedLoc;
public:
    CorrelationAircraft();

    CorrelationAircraft(std::time_t time, TailNumber tail_number, TcasID
    tcas_id, RadarID radar_id, GeographicCoordinate geographic_coordinate,
    SphericalCoordinate spherical_coordinate, Velocity velocity,
    Velocity predictedVector, Velocity predictedLoc, Device type);

    /*
     * Converts a Cluster to a CorrelationAircraft, calculate
     * correct location, heading, etc.
     * This means that this cluster has been determined
     * to be exactly one aircraft.
     *
     * @param cluster The cluster to convert
     * @return CDTIReport The generated report
     */
    CorrelationAircraft ConvertAircraft(Cluster cluster);
};

#endif //SAAS_CORRELATIONAIRCRAFT_H
