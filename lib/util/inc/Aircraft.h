/*
 * Aircraft.h
 * Specific Atomics
 * Kevin Pham, Frank Poole
 * 2-4-16
 * TODO: Description
 */

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include "FlightPlan.h"
#include "TailNumber.h"

class Aircraft {
private:
    /** Unique string that identifies a specific aircraft. */
    TailNumber _tail_Number;
    
    /**
     * The FlightPlan that contains an aircraft's initial position and
     * all of its different maneuvers.
     */
    FlightPlan _flight_plan;

    /** Flag that determines whether an aircraft has Ads-B capabilities. */
    bool _has_AdsB;
    
    /** Flag that determines whether an aircraft has TCAS capabilities. */
    bool _has_Tcas;

public:
    // TODO: Constructor

    // TODO: Destructor
};

#endif
