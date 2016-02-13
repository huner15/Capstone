/*
 * FlightLeg.h
 * Specific Atomics
 * Kevin Pham, Frank Poole
 * 2-9-16
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

    FlightLeg() {};
    FlightLeg(double duration_of_maneuver, double duration_after_maneuver,
        Vector3D new_relative_velocity);

    /**
     * Accessor for the duration of maneuver for this flight leg.
     * @return the duration of the maneuver
     */
    double GetDurationOfManeuver();

    /**
     * Accessor for the duration a velocity is maintained after the
     * maneuver is completed.
     * @return the duration after a maneuver is completed.
     */
    double GetDurationAfterManeuver();

    /**
     * Accessor for the 3D vector that represents the target velocity
     * for this flight leg.
     * @return the new target relative velocity for this flight leg.
     */
    Vector3D GetNewRelativeVelocity();

    /**
     * Checks to see if two FlightLegs are equal.
     * @return boolean stating whether two FlightLegs are equal
     */
    bool operator==(FlightLeg flightLeg) const;

    ~FlightLeg() {} ;
};

#endif
