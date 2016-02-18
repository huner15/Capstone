/*
 * @file FlightReport.h
 * @author Specific Atomics
 * @authors Frank Poole, Andy Savage
 * @date 2-13-16
 * @brief TODO: Description
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
#include "Velocity.h"
#include "RadarID.h"
#include "Device.h"

class FlightReport {
private:
    std::time_t _time;
    TailNumber _tail_number;
    TcasID _tcas_id;
    RadarID _radar_id;
    GeographicCoordinate _geographic_coordinate;
    SphericalCoordinate _spherical_coordinate;
    Velocity _velocity;
    Device _type;

public:
    FlightReport();

    FlightReport(std::time_t time, TailNumber tail_number, TcasID tcas_id,
           RadarID radar_id, GeographicCoordinate geographic_coordinate,
           SphericalCoordinate spherical_coordinate, Velocity velocity,
                 Device type);

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

    /**
     * Accessor function for the time of the flight report.
     * @return the time of the flight report
     */
    std::time_t GetTime();

    /**
     * Accessor function for the tail number of the flight report.
     * @return the tailnumber of the flight report.
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
};

#endif
