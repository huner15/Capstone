/*
 * FlightLeg.h
 * Specific Atomics
 * Kevin Pham
 * 2-2-16
 * TODO: Decription
 */

#ifndef FLIGHTLEG_H_
#define FLIGHTLEG_H_

#include "Vector.h"

class FlightLeg {
public:

private:

    /**
     * Duration that a turn will take to complete in seconds.
     */
    double _duration_of_maneuver;
    /**
     *  Duration that an aircraft will continue moving at a velocity
     *  after the maneuver is complete in seconds.
     */
    double _duration_after_maneuver;
    /**
     * The next relative velocity that the aircraft will reach
     * in this leg.
     */
    Vector3D _newRelativeVelocity;
};

#endif //SAAS_FLIGHTLEG_H
