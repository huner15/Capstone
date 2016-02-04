/*
 * FlightScenario.h
 * Specific Atomics
 * Kevin Pham
 * 2-2-16
 * TODO: Description
 */

#ifndef FLIGHTSCENARIO_H_
#define FLIGHTSCENARIO_H_

#include <Vector.h>
#include <Aircraft.h>
#include <vector>


class FlightScenario {
public:

private:
    /**
     * Aircraft that contains starting position and flight plan
     * for ownship.
     */
    Aircraft _ownship;
    
    /**
     * A collection of all the aircraft in this specific
     * FlightScenario
     */
    std::vector<Aircraft> aircraft;
};

#endif //SAAS_FLIGHTSCENARIO_H
