//
// Created by andrea on 1/19/16.
//
#ifndef SAAS_CLUSTER_H
#define SAAS_CLUSTER_H

#include "Prediction.h"

typedef struct Cluster
{
    //Collection<Report> tcas;
    //Collection<Report> adsb;
    //Collection<Report> radar;
    Vector prediction;
} Cluster;

typedef struct SurveillanceReport
{
    int clusterCount;
    //sfixed64 timestamp; // time of target report
    //sfixed32 id; // ID of target
    //sfixed32 range; // relative distance (Nautical Miles)
    //sfixed32 bearing;
    //sfixed32 altitude; // geometric altitude from GPS (feet)
    float range; // intruder relative distance (feet)
    float azimuth; // intruder horizontal angle (+/- 180 degrees)
    float elevation;
    float latitude; // target latitude (+/- 180 degrees)
    float longitude; // target longitude (+/- 180 degrees)
    float tail_number; // ID of target
    float north; // intruder velocity north (feet/sec)
    float east; // intruder velocity east (feet/sec)
    float down;
} SurveillanceReport;

#endif //SAAS_CLUSTER_H