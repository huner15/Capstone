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
    _duration_of_maneuver = duration_of_maneuver;
    _duration_after_maneuver = duration_after_maneuver;
    _new_relative_velocity = new_relative_velocity;
}
