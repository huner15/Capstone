//
// Created by andrea on 1/19/16.
//
#ifndef SAAS_CLUSTER_H
#define SAAS_CLUSTER_H

#include "Prediction.h"

using namespace std;

typedef struct Cluster
{
    SurveillanceReport tcas;
    SurveillanceReport adsb;
    SurveillanceReport radar;
    //Vector<Point> prediction;
} Cluster;

enum Device {radar, TCAS, ADS_B};

typedef struct SurveillanceReport
{
    Device type;
    int clusterCount;
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
} SurveillanceReport;

float calcEuclidDistance(SurveillanceReport reportOne, SurveillanceReport reportTwo);

float calcDistance(SurveillanceReport reportOne, SurveillanceReport reportTwo);

float calcSpeed(SurveillanceReport reportOne, SurveillanceReport reportTwo);

float calcHeading(SurveillanceReport reportOne, SurveillanceReport reportTwo);

#endif //SAAS_CLUSTER_H