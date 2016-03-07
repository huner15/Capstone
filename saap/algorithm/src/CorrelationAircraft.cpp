/**
* @file CorrelationAircraft.cpp
* @author Specific Atomics
* @author Andrea Savage
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
        Velocity predictedVector, Velocity predictedLoc, Device type) {
    _predictedLoc = predictedLoc;
    _predictedVector = predictedVector;

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