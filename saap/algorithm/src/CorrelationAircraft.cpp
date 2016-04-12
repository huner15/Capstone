/**
* @file CorrelationAircraft.cpp
* @author Specific Atomics
* @author Andrea Savage
* @author Dat Tran
* @date 2-13-16
* @brief Constructs a CorrelationAircraft and converts a Cluster into one
 * most likely CorrelationAircraft.
*/

#include "Cluster.h"
#include "CorrelationAircraft.h"

CorrelationAircraft::CorrelationAircraft(std::time_t time, TailNumber
        tail_number, TcasID tcas_id,
        RadarID radar_id, GeographicCoordinate geographic_coordinate,
        SphericalCoordinate spherical_coordinate, Velocity velocity,
        Velocity predicted_velocity, GeographicCoordinate predicted_location, Device type) {
    _predicted_location = predicted_location;
    _predicted_velocity = predicted_velocity;
    _time = time;
    _tail_number = tail_number;
    _tcas_id = tcas_id;
    _radar_id = radar_id;
    _geographic_coordinate = geographic_coordinate;
    _spherical_coordinate = spherical_coordinate;
    _velocity = velocity;
    _type = type;
}

CDTIPlane CorrelationAircraft::CreateCdtiPlane() {
    CDTIPlane cdti_plane;

    if (_type == ADSB) {
        cdti_plane.set_id(_tail_number.Get());
    }
    else if (_type == TCAS) {
        cdti_plane.set_id(std::to_string(_tcas_id.Get()));
    }
    else if (_type == RADAR) {
        cdti_plane.set_id(std::to_string(_radar_id.Get()));
    }
    Saas_Util::Vector<double, 3> position = _spherical_coordinate
            .ToCartesianCoordinates();
    Vector pos;
    pos.set_n(position.x);
    pos.set_e(position.y);
    pos.set_d(position.z);
    Vector vel;
    vel.set_n(_velocity.x);
    vel.set_e(_velocity.y);
    vel.set_d(_velocity.z);
    cdti_plane.set_allocated_position(&pos);
    cdti_plane.set_allocated_velocity(&vel);

    return cdti_plane;
}

CorrelationAircraft::CorrelationAircraft() {

}

CorrelationAircraft::~CorrelationAircraft() {

}

Velocity CorrelationAircraft::GetPredictedVelocity() const {
    return _predicted_velocity;
}

GeographicCoordinate CorrelationAircraft::GetPredictedLocation() const
{
    return _predicted_location;
}

std::time_t CorrelationAircraft::GetTime() const {
    return _time;
}

TailNumber CorrelationAircraft::GetTailNumber() const {
    return _tail_number;
}

TcasID CorrelationAircraft::GetTcasID() const {
    return _tcas_id;
}

RadarID CorrelationAircraft::GetRadarID() const {
    return _radar_id;
}

GeographicCoordinate CorrelationAircraft::GetGeographicCoordinate() const {
    return _geographic_coordinate;
}

SphericalCoordinate CorrelationAircraft::GetSphericalCoordinate() const {
    return _spherical_coordinate;
}

Velocity CorrelationAircraft::GetVelocity() const {
    return _velocity;
}

Device CorrelationAircraft::GetDeviceType() const {
    return _type;
}
