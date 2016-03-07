/**
* @file SurveillanceReport.h
* @author Specific Atomics
* @author Andrea Savage
* @date 2-13-16
* @brief Constructs a SurveillanceReport and converts a Cluster into one
 * most likely SurveillanceReport.
*/

#ifndef SURV_REPORT_H
#define SURV_REPORT_H

#include <ctime>
#include "SurveillanceReport.h"
#include "TailNumber.h"
#include "TcasID.h"
#include "RadarID.h"
#include "GeographicCoordinate.h"
#include "SphericalCoordinate.h"
#include "Velocity.h"
#include "RadarID.h"
#include "Device.h"

using namespace std;

/**
 * A struct that represents an individual aircraft in the airspace around
 * the ownship. Holds the evaluated current location, heading, elevation,
 * and identifiers from the Surveillance Report or Surveillance Reports
 * that were evaluated to represent this aircraft.
 * All fields may not be populated.
 */
class SurveillanceReport {
protected:
    std::time_t _time; /** Timestamp for when this was received. */
    TailNumber _tail_number; /** tail number of aircraft */
    TcasID _tcas_id; /** ID given by the TCAS hardware. */
    RadarID _radar_id; /** ID given by the radar hardware. */
    /** latitude, longitude (+/- 180 degrees), and altitude. */
    GeographicCoordinate _geographic_coordinate;
    SphericalCoordinate _spherical_coordinate;
    Velocity _velocity;  /** relative intruder velocity (feet/sec). */
    Device _type; /** Enum for what device this report is from. */

public:
    SurveillanceReport();

    SurveillanceReport(std::time_t time, TailNumber tail_number, TcasID
    tcas_id, RadarID radar_id, GeographicCoordinate geographic_coordinate,
    SphericalCoordinate spherical_coordinate, Velocity velocity, Device type);

    /**
     * Accessor function for the time of the flight report.
     * @return the time of the flight report
     */
    std::time_t GetTime();

    /**
     * Accessor function for the tail number of the flight report.
     * @return the tail number of the flight report.
     */
    TailNumber GetTailNumber();

    /**
     * Accessor function for the TcasId of the flight report.
     * @return the TcasId of the flight report
     */
    TcasID GetTcasID();

    /**
     * Accessor function for the RadarId of the flight report.
     * @return the RadarId of the flight report.
     */
    RadarID GetRadarID();

    /**
     * Accessor function for the Geographic coordinate of the flight report.
     * @return the geographic coordinate of the flight report.
     */
    GeographicCoordinate GetGeographicCoordinate();

    /**
     * Accessor function for the spherical coordinate of the flight report.
     * @return the spherical coordinate of the flight report.
     */
    SphericalCoordinate GetSphericalCoordinate();

    /**
     * Accessor function for the velocity of the flight report.
     * @return the velocity of the flight report.
     */
    Velocity GetVelocity();

    /**
     * Accessor function for the device of the flight report.
     * @return the device of the flight report
     */
    Device GetDevice();

    double GetRange() const;

    double GetElevation() const;

    double GetAzimuth() const;

    double GetLatitude() const;

    double GetLongitude() const;

    double GetAltitude() const;

    double GetBearing() const;
};

#endif //SURV_REPORT_H
