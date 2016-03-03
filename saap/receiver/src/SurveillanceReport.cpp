/**
* @file SurveillanceReport.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 2-13-16
* @brief Constructs a SurveillanceReport and converts a Cluster into one
 * most likely SurveillanceReport.
*/

#include "SurveillanceReport.h"

SurveillanceReport::SurveillanceReport() {

}

SurveillanceReport::SurveillanceReport(std::time_t time, TailNumber tail_number,
    TcasID tcas_id, RadarID radar_id, GeographicCoordinate
    geographic_coordinate, SphericalCoordinate spherical_coordinate, Velocity
    velocity, Device type) {
    _time = time;
    _tail_number = tail_number;
    _tcas_id = tcas_id;
    _radar_id = radar_id;
    _geographic_coordinate = geographic_coordinate;
    _spherical_coordinate = spherical_coordinate;
    _velocity = velocity;
    _type = type;
}