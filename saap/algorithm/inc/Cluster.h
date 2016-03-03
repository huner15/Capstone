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
#include "CorrelationAircraft.h"
#include "SurveillanceReport.h"
#include <vector>

#define TRUE 0
#define FALSE 1

using namespace std;

/**
 * A class representing one aircraft in the airspace.
 * All Surveillance Reports may not exist.
 */
class Cluster {
public:
    /** Report from the TCAS hardware. */
    SurveillanceReport *_tcas;
    /** Report from the ADS-B hardware. */
    SurveillanceReport *_adsb;
    /** Report from the radar hardware. */
    SurveillanceReport *_radar;
    /** Predicted aircraft location for the next second. */
    Velocity _prediction;

    Cluster();

    ~Cluster();

    void SetRadar(SurveillanceReport *radar);

    void SetADSB(SurveillanceReport *adsb);

    void SetTCAS(SurveillanceReport *tcas);
};

#endif //SAAS_CLUSTER_H