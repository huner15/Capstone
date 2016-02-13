/*
 * FlightPlan.h
 * Specific Atomics
 * Kevin Pham, Frank Poole
 * 2-9-16
 * TODO: Description
 */

#ifndef FLIGHT_PLAN_H_
#define FLIGHT_PLAN_H_

#include <vector>

#include "GeographicCoordinate.h"
#include "FlightLeg.h"

class FlightPlan {
private:
    /** The starting position of the Flight. */
    GeographicCoordinate _start_position;

    /** A collection of all the FlightLegs of this FlightPlan. */
    std::vector<FlightLeg> _flight_legs;

public:
    FlightPlan() {};
    FlightPlan(GeographicCoordinate start_position,
                std::vector<FlightLeg> const  &flight_legs);

    /**
     * Accessor for the starting position of this flight plan.
     * @return The Geographic Coordinating indicating the starting position.
     */
    GeographicCoordinate GetStartPosition();

    /**
     * Accessor for the all the flight legs in this flight plan.
     * @return A vector containing all the flight legs for this flight plan.
     */
    std::vector<FlightLeg> GetFlightLegs();

    /**
     * Checks to see if two FlightPlans are the same
     * @return boolean stating whether two FlightPlans are the same.
     */
    bool operator==(FlightPlan plan) const;

    ~FlightPlan() {};
};

#endif
