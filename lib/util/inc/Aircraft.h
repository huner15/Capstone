//
// Created by Dat Tran on 2/2/16.
//

#ifndef SAAS_AIRCRAFT_H
#define SAAS_AIRCRAFT_H

#include <FlightPlan.h>


class Aircraft {
private:
    TailNumber tail_number;
    bool has_ADSB;
    bool has_TCAS;
    FlightPlan flight_plan;
public:
};


#endif
