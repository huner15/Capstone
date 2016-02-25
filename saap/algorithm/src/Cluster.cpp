/**
* @file Cluster.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 1-19-16
* @brief Cluster class so that new can be used to instantiate Cluster
 * objects.
*/

#include "Cluster.h"

Cluster::Cluster() {

}

Cluster::~Cluster() {

}

void Cluster::SetADSB(FlightReport *adsb) {
_adsb = adsb;
}

void Cluster::SetTCAS(FlightReport *tcas) {
_tcas = tcas;
}

void Cluster::SetRadar(FlightReport *radar) {
_radar = radar;
}










