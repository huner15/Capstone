/*
 * FlightReport.h
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef ACTUAL_REPORT_H_
#define ACTUAL_REPORT_H_

#include <ownship.pb.h>
#include <adsb.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>

#include <ctime>
#include <vector>

#include "TailNumber.h"
#include "TcasID.h"
#include "RadarID.h"
#include "GeographicCoordinate.h"
#include "SphericalCoordinate.h"
#include "Vector.h"
#include "RadarID.h"

class FlightReport {
private:
    std::time_t _time;
    TailNumber _tail_number;
    TcasID _tcas_id;
    RadarID _radar_id;
    GeographicCoordinate _geographic_coordinate;
    SphericalCoordinate _spherical_coordinate;
    Vector3D _velocity;
public:
    FlightReport(std::time_t time, TailNumber tail_number, TcasID tcas_id,
           RadarID radar_id, GeographicCoordinate geographic_coordinate,
           SphericalCoordinate spherical_coordinate, Vector3D velocity);

    ~FlightReport();

    /**
     * Creates an ownship report from the data from this FlightReport.
     * @return an ownship report made from the data in this FlightReport.
     */

    OwnshipReport createOwnshipReport();

    /**
     * Creates an ADS-B report from the data in this FlightReport.
     * @return an ADS-B report made from the data in this FlightReport.
     */

    AdsBReport createAdsBReport();

    /**
     * Creates a radar report from the data in this FlightReport.
     * @return a radar report made from the data in this FlightReport.
     */

    RadarReport createRadarReport();

    /**
     * Creates a TCAS report from the data in this FlightReport
     * @return a radar report made from the data in this FlightReport.
     */
    TcasReport createTcasReport();

    /**
     * Compares all three components of velocity between this FlightReport
     * and another. For any component of the velocity is missing from either
     * report a null value is put in its place.
     * @param other The FlightReport we are comparing against.
     * @return A vector with the comparisons between the individual
     * components of velocity.
     */


    std::vector<float> CompareVelocity (FlightReport other);

    /**
     * Compares the ranges between this FlightReport and another.
     * @param other The FlightReport we are comparing against.
     * @return the difference between this FlightReport's range and other's
     */
    float CompareRange (FlightReport other);


    /**
     * Compares the latitude and longitude between this FlightReport and
     * another. If a TCAS report is used for either of the FlightReports
     * return 0.
     * @param other The surveillance report we are comparing against.
     * @return the difference between this FlightReport's longitude and
     * latitude and other's. Returns 0 if either of the FlightReports is a
     * TCAS report.
     */
    float CompareLatitudeLongitude (FlightReport other);


    /**
     * Compares the altitudes between this FlightReport and another.
     * @param other The FlightReport we are comparing against.
     * @return the difference between this FlightReport's altitude and other's
     */
    float CompareAltitude (FlightReport other);


    /**
     * Compares the azimuth between this FlightReport and another.
     * @param other The FlightReport we are comparing against
     * @return the difference between this FlightReport's azimuth and other's
     */
    float CompareAzimuth (FlightReport other);


    /**
     * Compares the bearing between this FlightReport and another.
     * @param other The FlightReport we are comparing against.
     * @return the difference between this FlightReport's bearing and other's.
     */
    float CompareBearing (FlightReport other);



};

#endif
