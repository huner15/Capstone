/*
 * FlightReport.h
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef ACTUAL_REPORT_H_
#define ACTUAL_REPORT_H_

#include <ctime>

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
};

#endif
