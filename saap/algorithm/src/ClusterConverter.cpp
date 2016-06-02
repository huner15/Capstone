#include <iostream>
#include "ClusterConverter.h"

ClusterConverter::ClusterConverter() {
    _corr_aircraft = new vector<CorrelationAircraft *>();
}

std::vector<CorrelationAircraft *> *ClusterConverter::Convert(
        vector<Cluster *> *clusters) {
    CorrelationAircraft *temp;
    pthread_mutex_lock(&corr_aircraft_mutex);
    _corr_aircraft->clear();

    // For every cluster, call ConvertAircraft(), add to _corr_aircraft.
    for (uint32_t i = 0; i < clusters->size(); i++) {
        temp = ConvertAircraft(clusters->at(i));
        _corr_aircraft->push_back(temp);
    }

    pthread_mutex_unlock(&corr_aircraft_mutex);

    return _corr_aircraft;
}

CorrelationAircraft *ClusterConverter::ConvertAircraft(Cluster *cluster) {
    Device type;
    CorrelationAircraft *aircraft;
    std::time_t time;
    TailNumber tail_number = TailNumber("      ");
    TcasID tcas_id = 0;
    RadarID radar_id = 0;
    SphericalCoordinate spherical_coordinate;
    GeographicCoordinate geographic_coordinate;
    Velocity velocity;

    // Set Device type based on the ranking: ads-b is best, tcas, radar.
    if (cluster->_radar != NULL) {
        type = RADAR;
        time = cluster->_radar->GetTime();
        radar_id = cluster->_radar->GetRadarID();
    }
    if (cluster->_tcas != NULL) {
        type = TCAS;
        time = cluster->_tcas->GetTime();
        tcas_id = cluster->_tcas->GetTcasID();
    }
    if (cluster->_adsb != NULL) {
        type = ADSB;
        time = cluster->_adsb->GetTime(); // uses "best" time in order of rank
        tail_number = cluster->_adsb->GetTailNumber();
    }

    // Check for empty clusters.
    if (cluster->_adsb == NULL && cluster->_tcas == NULL
        && cluster->_radar == NULL) {
        printf("Trying to convert empty Cluster to CorrelationAircraft\n");
        return NULL;
    }

    // TODO: Set prediction vectors (Dat).
    Velocity predicted_velocity = Velocity(0, 0, 0);
    GeographicCoordinate predicted_loc = GeographicCoordinate(0, 0, 0);

    DetermineAverages(cluster);
    spherical_coordinate = _sphericalCoordinate;
    geographic_coordinate = _geographicCoordinate;
    velocity = _velocity;

    aircraft = new CorrelationAircraft(time, tail_number, tcas_id, radar_id,
       geographic_coordinate, spherical_coordinate, velocity,
       predicted_velocity, predicted_loc, type);

    return aircraft;
}

void ClusterConverter::DetermineAverages(Cluster *cluster) {
    GeographicCoordinate *adsbG = NULL, *tcasG = NULL, *radarG = NULL;
    SphericalCoordinate *adsbS = NULL, *tcasS = NULL, *radarS = NULL;
    Velocity *adsbV = NULL, *tcasV = NULL, *radarV = NULL;

    // Set Device type based on the ranking: ads-b is best, tcas, radar.
    if (cluster->_radar != NULL) {
        radarG = cluster->_radar->GetGeographicCoordinate();
        radarS = cluster->_radar->GetSphericalCoordinate();
        radarV = cluster->_radar->GetVelocity();
    }
    if (cluster->_tcas != NULL) {
        tcasS = cluster->_tcas->GetSphericalCoordinate();
    }
    if (cluster->_adsb != NULL) {
        adsbG = cluster->_adsb->GetGeographicCoordinate();
        adsbV = cluster->_adsb->GetVelocity();
    }

    _geographicCoordinate = GeographicCoordinate::Average(adsbG, tcasG, radarG);

    _sphericalCoordinate = SphericalCoordinate::Average(adsbS, tcasS, radarS);

    _velocity = Velocity::Average(adsbV, tcasV, radarV);
}