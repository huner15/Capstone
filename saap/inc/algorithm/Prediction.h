//
// Created by andrea on 1/19/16.
//
#ifndef SAAS_PREDICTION_H
#define SAAS_PREDICTION_H

#include "../../../../../.CLion12/system/cmake/generated/5c6d134d/5c6d134d/Debug/lib/gp/capstone-shared/cdti.pb.h"

typedef struct History
{
    Snapshot last;
    Snapshot secondToLast;
    Snapshot thirdToLast;
} History;

typedef struct Snapshot
{
    //Collection<CorrelationAircraft> aircraft;
    int counterVal; //or time_stamp
} Snapshot;

typedef struct CorrelationAircraft
{
    int64_t timestamp; // time of target report
    int32_t id; // ID of target
    int32_t bearing;
    int32_t altitude; // geometric altitude from GPS (feet)
    float range; // intruder relative distance (feet)
    float azimuth; // intruder horizontal angle (+/- 180 degrees)
    float elevation;
    float latitude; // target latitude (+/- 180 degrees)
    float longitude; // target longitude (+/- 180 degrees)
    float tail_number; // ID of target
    float north; // intruder velocity north (feet/sec)
    float east; // intruder velocity east (feet/sec)
    float down;
    Vector predictedVector; //or location
} CorrelationAircraft;

#endif //SAAS_PREDICTION_H
