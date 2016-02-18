/*
 * @file FlightReport.h
 * @author Specific Atomics
 * @authors Frank Poole, Andy Savage, Dat Tran
 * @date 2-13-16
 * @brief TODO: Description
 */

#ifndef ACTUAL_REPORT_H_
#define ACTUAL_REPORT_H_

#include <ownship.pb.h>
#include <adsb.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>
#include <cdti.pb.h>
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
     * @return a TCAS report made from the data in this FlightReport.
     */
    TcasReport createTcasReport();

    /**
     * Creates a CDTI plane from the data in this FlightReport
     * @return a CDTI plane made from the data in this FlightReport
     */
    CDTIPlane CreateCdtiPlane();


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
