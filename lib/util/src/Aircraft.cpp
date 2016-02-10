/*
 * Aircraft.cpp
 * Specific Atomics
 * Dat Tran, Frank Poole, Kevin Pham
 * 2-9-16
 * TODO: Description
 */

#include "Aircraft.h"

Aircraft::Aircraft(TailNumber tail_number, FlightPlan flight_plan,
                   bool has_AdsB, bool has_Tcas) {
    _tail_number = tail_number;
    _flight_plan = flight_plan;
    _has_AdsB = has_AdsB;
    _has_Tcas = has_Tcas;
}