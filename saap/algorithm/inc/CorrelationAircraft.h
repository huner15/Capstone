/**
* @file CorrelationAircraft.h
* @author Specific Atomics
* @author Andrea Savage
* @date 2-13-16
* @brief Constructs a CorrelationAircraft and converts a Cluster into one
 * most likely CorrelationAircraft.
*/

#ifndef CORRELATIONAIRCRAFT_H_
#define CORRELATIONAIRCRAFT_H_

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
class CorrelationAircraft {

protected:
    /** Predicted vector the aircraft will be facing in following
    * seconds. */
    Velocity _predictedVector;
    /** Predicted location the aircraft will be at in following seconds. */
    Velocity _predictedLoc;

    std::time_t _time; /** Timestamp for when this was received. */
    TailNumber _tail_number; /** tail number of aircraft */
    TcasID _tcas_id; /** ID given by the TCAS hardware. */
    RadarID _radar_id; /** ID given by the radar hardware. */
    /** latitude, longitude (+/- 180 degrees), and altitude. */
    GeographicCoordinate _geographic_coordinate; /** absolute location data. */
    SphericalCoordinate _spherical_coordinate; /** ownship relative location. */
    Velocity _velocity;  /** relative intruder velocity (feet/sec). */
    Device _type; /** Enum for what device this report is from. */

public:
    /**
     * Creates a new empty CorrelationAircraft.
     */
    CorrelationAircraft();

    /**
     * Creates a new CorrelationAircraft with the needed values.
     */
    CorrelationAircraft(std::time_t time, TailNumber tail_number, TcasID
    tcas_id, RadarID radar_id, GeographicCoordinate geographic_coordinate,
    SphericalCoordinate spherical_coordinate, Velocity velocity,
    Velocity predictedVector, Velocity predictedLoc, Device type);

    /**
     * Deconstructs a new empty CorrelationAircraft.
     */
    ~CorrelationAircraft();

    /**
    * Creates a CDTI plane from the data in this FlightReport
    * @return a CDTI plane made from the data in this FlightReport
    */
    CDTIPlane CreateCdtiPlane();
};

#endif //SAAS_CORRELATIONAIRCRAFT_H
