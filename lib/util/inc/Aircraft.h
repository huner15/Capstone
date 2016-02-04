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
#include "TailNumber.h"

class Aircraft {
public:

private:

    /**
     * Unique string that identifies a specific aircraft
     */
    TailNumber _tail_Number;
    
    /**
     * The FlightPlan that contains an aircraft's initial position and
     * all of its different maneuvers.
     */
    FlightPlan _flight_plan;

    /**
     * Flag that determines whether an aircraft has Ads-B capabilities.
     */
    bool _has_AdsB;
    
    /**
    * Flag that determines whether an aircraft has TCAS capabilities.
    */
    bool _has_Tcas;
};

#endif //SAAS_AIRCRAFT_H
