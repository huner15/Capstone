/**
* @file CorrelationAircraft.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 2-13-16
* @brief Constructs a CorrelationAircraft and converts a Cluster into one
 * most likely CorrelationAircraft.
*/

#include <FlightReport.h>
#include "Cluster.h"
#include "CorrelationAircraft.h"
#include "Velocity.h"
#include <ctime>

CorrelationAircraft::CorrelationAircraft(std::time_t time, TailNumber
        tail_number, TcasID tcas_id,
        RadarID radar_id, GeographicCoordinate geographic_coordinate,
        SphericalCoordinate spherical_coordinate, Velocity velocity,
        Velocity predictedVector, Velocity predictedLoc, Device type) {
    _predictedLoc = predictedLoc;
    _predictedVector = predictedVector;
    FlightReport(time, tail_number, tcas_id, radar_id, geographic_coordinate,
            spherical_coordinate, velocity, type);
}


CorrelationAircraft::CorrelationAircraft() {

}