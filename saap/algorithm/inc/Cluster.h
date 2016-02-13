/**
* @file Cluster.h
* @author Specific Atomics
* @author Andrea Savage
* @date 1-19-16
* @brief Holds the Cluster struct and cluster correlation headers.
*/

#ifndef SAAS_CLUSTER_H
#define SAAS_CLUSTER_H

#include <stdint.h>
#include "FlightReport.h"
#include <vector>

/**
 * A struct holding a report from a hardware sensor representing
 * a located aircraft by that sensor for the current second.
 */
//typedef struct SurveillanceReport // : public FlightReport
//{
//    Device type; /** Enum for what device this report is from. */
//    int64_t timestamp; /** Timestamp for when this was received. */
//    int32_t bearing; /** Relative heading to the ownship. */
//    int32_t altitude; /** relative geometric altitude from GPS (feet). */
//    float azimuth; /** relative horizontal angle (+/- 180 degrees). */
//    float elevation; /** relative vertical angle from ownship. */
//
//    //Only one of these fields will be set
//    int32_t id; /** ID given by the TCAS or radar hardware. */
//    float tail_number; /** tail number of aircraft */
//
//    //Not instantiated when a TCAS report
//    float range; /** relative distance from ownship (feet). */
//    float latitude; /** latitude (+/- 180 degrees). */
//    float longitude; /** longitude (+/- 180 degrees). */
//    float north; /** relative intruder velocity north (feet/sec). */
//    float east; /** relative intruder velocity east (feet/sec). */
//    float down; /** relative intruder velocity down (feet/sec). */
//} SurveillanceReport;

/**
 * A struct representing one aircraft in the airspace.
 * All Surveillance Reports may not exist.
 */
typedef struct Cluster
{
    /** Report from the TCAS hardware. */
    FlightReport tcas;
    /** Report from the ADS-B hardware. */
    FlightReport adsb;
    /** Report from the radar hardware. */
    FlightReport radar;
    /** Predicted aircraft location for the next second. */
    Velocity prediction;
} Cluster;

int Correlate(std::vector<FlightReport> adsb,
              std::vector<FlightReport> tcas, FlightReport ownship,
              std::vector<FlightReport> radar);

int CheckClusterCount();

float CalcEuclidDistance(FlightReport reportOne, FlightReport
reportTwo);

float CalcDistance(FlightReport reportOne, FlightReport reportTwo);

float CalcSpeed(FlightReport reportOne, FlightReport reportTwo);

float CalcHeading(FlightReport reportOne, FlightReport reportTwo);

#endif //SAAS_CLUSTER_H