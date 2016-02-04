/*
 * Aircraft.h
 * Specific Atomics
 * Kevin Pham
 * 2-2-16
 * TODO: Decription
 */

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include "FlightPlan.h"

class Aircraft {
public:

private:

    /**
     * Unique string that identifies a specific aircraft
     */
    std::string _tail_Number;
    /**
     * Flag that determines whether an aircraft has AdsB capabilities.
     */
    bool _has_AdsB;
    /**
    * Flag that determines whether an aircraft has Tcas capabilities.
    */
    bool _has_Tcas;
    /**
     * The FlightPlan that contains an aircrafts initial position and
     * all of its different maneuvers.
     */
    FlightPlan _flight_plan;
};

#endif //SAAS_AIRCRAFT_H
