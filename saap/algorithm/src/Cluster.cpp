/**
* @file Cluster.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 3-5-16
* @brief Cluster class so that new can be used to instantiate Cluster
 * objects.
*/

#include "Cluster.h"
#include "SurveillanceReport.h"

Cluster::Cluster() {
    _adsb = NULL;
    _tcas = NULL;
    _radar = NULL;
}

Cluster::~Cluster() {
}

void Cluster::SetADSB(SurveillanceReport *adsb) {
    _adsb = adsb;
}

void Cluster::SetTCAS(SurveillanceReport *tcas) {
    _tcas = tcas;
}

void Cluster::SetRadar(SurveillanceReport *radar) {
    _radar = radar;
}
