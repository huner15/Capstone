//
// Created by andrea on 1/19/16.
//
#ifndef SAAS_CLUSTER_H
#define SAAS_CLUSTER_H

#include "Prediction.h"

using namespace std;

/**
 * A struct representing one aircraft in the airspace.
 * All Surveillance Reports may not exist.
 */
typedef struct Cluster
{
    /** Report from the TCAS hardware. */
    SurveillanceReport tcas;
    /** Report from the ADS-B hardware. */
    SurveillanceReport adsb;
    /** Report from the radar hardware. */
    SurveillanceReport radar;
    /** Predicted aircraft location for the next second. */
    Vector prediction;
} Cluster;

/**
 * Enum representing the different device types a report
 * can be received from.
 * radar, TCAS, or ADS_B
 */
enum Device {radar, TCAS, ADS_B};

/**
 * A struct holding a report from a hardware sensor representing
 * a located aircraft by that sensor for the current second.
 */
class SurveillanceReport : public FlightRport
{
    Device type; /** Enum for what device this report is from. */
    int64_t timestamp; /** Timestamp for when this was received. */
    int32_t bearing; /** Relative heading to the ownship. */
    int32_t altitude; /** relative geometric altitude from GPS (feet). */
    float azimuth; /** relative horizontal angle (+/- 180 degrees). */
    float elevation; /** relative vertical angle from ownship. */

    //Only one of these fields will be set
    int32_t id; /** ID given by the TCAS or radar hardware. */
    float tail_number; /** tail number of aircraft */

    //Not instantiated when a TCAS report
    float range; /** relative distance from ownship (feet). */
    float latitude; /** latitude (+/- 180 degrees). */
    float longitude; /** longitude (+/- 180 degrees). */
    float north; /** relative intruder velocity north (feet/sec). */
    float east; /** relative intruder velocity east (feet/sec). */
    float down; /** relative intruder velocity down (feet/sec). */
} SurveillanceReport;

float calcEuclidDistance(SurveillanceReport reportOne, SurveillanceReport reportTwo);

float calcDistance(SurveillanceReport reportOne, SurveillanceReport reportTwo);

float calcSpeed(SurveillanceReport reportOne, SurveillanceReport reportTwo);

float calcHeading(SurveillanceReport reportOne, SurveillanceReport reportTwo);

#endif //SAAS_CLUSTER_H