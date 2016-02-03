//
// Created by Dat Tran on 2/2/16.
//

#ifndef SAAS_FLIGHTPLAN_H
#define SAAS_FLIGHTPLAN_H

#include <vector>
#include "FlightLeg.h"

class FlightPlan {
private:
    Vector3D start_position;
    std::vector <FlightLeg> flight_legs;
public:
};

#endif
