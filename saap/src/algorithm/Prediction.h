//
// Created by andrea on 1/19/16.
//
#ifndef SAAS_PREDICTION_H
#define SAAS_PREDICTION_H

#include "../../../../../.CLion12/system/cmake/generated/5c6d134d/5c6d134d/Debug/lib/gp/capstone-shared/cdti.pb.h"

typedef struct History
{
    //Collection<Snapshot> snapshots;
} History;

typedef struct Snapshot
{
    //Collection<CorrelationAircraft> aircraft;
    int counterVal; //or time_stamp
} Snapshot;

typedef struct CorrelationAircraft
{
    //ALL CategorizationAircraft/CDTIReport fields
    Vector predictedVector; //or location
} CorrelationAircraft;

#endif //SAAS_PREDICTION_H
