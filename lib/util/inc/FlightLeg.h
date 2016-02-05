/*
 * FlightLeg.h
 * Specific Atomics
 * Kevin Pham, Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef FLIGHT_LEG_H_
#define FLIGHT_LEG_H_

#include "Vector.h"

class FlightLeg {
private:
    /** Duration that a turn will take to complete in seconds. */
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
    Vector3D _new_relative_velocity;

public:

};

#endif
