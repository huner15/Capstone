/*
 * FlightLeg.cpp
 * Specific Atomics
 * Dat Tran, Frank Poole, Kevin Pham
 * 2-9-16
 * TODO: Description
 */

#include "FlightLeg.h"

FlightLeg::FlightLeg(double duration_of_maneuver, double duration_after_maneuver,
                     Vector3D new_relative_velocity) {
    if(duration_after_maneuver >= 0 && duration_of_maneuver > 0) {


        _duration_of_maneuver = duration_of_maneuver;
        _duration_after_maneuver = duration_after_maneuver;
        _new_relative_velocity = new_relative_velocity;
    }
    else {
        std::domain_error( "Invalid duration value");
    }
}

double FlightLeg::GetDurationOfManeuver() {
    return _duration_of_maneuver;
}

double FlightLeg::GetDurationAfterManeuver() {
    return _duration_after_maneuver;
}

Vector3D FlightLeg::GetNewRelativeVelocity() {
    return _new_relative_velocity;
}

bool FlightLeg::operator==(FlightLeg flightLeg) const  {
    return (_duration_of_maneuver == flightLeg.GetDurationOfManeuver()
        && _duration_after_maneuver == flightLeg.GetDurationAfterManeuver()
        && _new_relative_velocity.x == flightLeg.GetNewRelativeVelocity().x
        && _new_relative_velocity.y == flightLeg.GetNewRelativeVelocity().y
        && _new_relative_velocity.z == flightLeg.GetNewRelativeVelocity().z);
}
