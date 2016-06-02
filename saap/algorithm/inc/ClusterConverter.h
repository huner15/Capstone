#ifndef SAAS_CLUSTERCONVERTER_H
#define SAAS_CLUSTERCONVERTER_H

#include "Cluster.h"
#include "CorrelationAircraft.h"

using namespace std;

class ClusterConverter {
protected:
    // Holds the Correlation Aircraft objects generated this second
    vector<CorrelationAircraft *> *_corr_aircraft;

    //Holds the calculated average values
    SphericalCoordinate _sphericalCoordinate;
    GeographicCoordinate _geographicCoordinate;
    Velocity _velocity;

    // Mutex locks for using the cluster and corrAircraft vectors.
    pthread_mutex_t corr_aircraft_mutex;

    CorrelationAircraft *ConvertAircraft(Cluster *cluster);

    void DetermineAverages(Cluster *cluster);
public:
    ClusterConverter();

    std::vector<CorrelationAircraft *> *Convert(
            vector<Cluster *> *clusters);
};

#endif //SAAS_CLUSTERCONVERTER_H
