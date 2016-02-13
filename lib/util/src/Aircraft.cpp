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

TailNumber Aircraft::GetTailNumber() {
    return _tail_number;
}

FlightPlan Aircraft::GetFlightPlan() {
    return _flight_plan;
}

bool Aircraft::HasAdsB() {
    return _has_AdsB;
}

bool Aircraft::HasTcas() {
    return _has_Tcas;
}

bool Aircraft::operator==(Aircraft aircraft) {
    return (aircraft.GetTailNumber() == _tail_number &&
        aircraft.GetFlightPlan() == _flight_plan &&
        aircraft.HasAdsB() == _has_AdsB &&
        aircraft.HasTcas() == _has_Tcas);
}