/*
 * FlightScenario.h
 * Specific Atomics
 * Kevin Pham
 * 2-2-16
 * TODO: Decription
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
     * The ownships latitude, longitude, and altitude in
     * a 3D Vector
     */
    Vector3D _ownship_start;
    /**
     * A collection of all the aircraft in this specific
     * FlightScenario
     */
    std::vector<Aircraft> aircraft;
};

#endif //SAAS_FLIGHTSCENARIO_H
