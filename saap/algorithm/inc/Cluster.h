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
#include "CorrelationAircraft.h"
#include <vector>

#define TRUE 0
#define FALSE 1

using namespace std;

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
              std::vector<FlightReport> tcas, std::vector<FlightReport> radar);

int CheckClusterCount();

float CalcEuclidDistance(FlightReport reportOne, FlightReport
reportTwo);

/*
     * Converts a Cluster to a CorrelationAircraft, calculate
     * correct location, heading, etc.
     * This means that this cluster has been determined
     * to be exactly one aircraft.
     *
     * @param cluster The cluster to convert
     * @return CDTIReport The generated report
     */
//CorrelationAircraft& ConvertAircraft(Cluster& cluster);

float CalcDistance(FlightReport& reportOne, FlightReport& reportTwo);

float CalcSpeed(FlightReport& reportOne, FlightReport& reportTwo);

float CalcHeading(FlightReport& reportOne, FlightReport& reportTwo);

int CompareReports(vector<FlightReport>& reports);

#endif //SAAS_CLUSTER_H