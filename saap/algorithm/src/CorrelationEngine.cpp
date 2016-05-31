/**
* @file CorrelationEngine.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 3-5-16
* @brief The main correlation engine class with most of the distance logic that
 * all of the interchangeable algorithms will be based on.
*/

#include "CorrelationEngine.h"

using namespace std;

CorrelationEngine::CorrelationEngine() {
    _is_relative = true;
    pthread_mutex_init(&cluster_mutex, NULL);
    pthread_mutex_init(&corr_aircraft_mutex, NULL);
}

CorrelationEngine::~CorrelationEngine() {
}

int CorrelationEngine::GetClusterSize() {
    return _clusters.size();
}

int CorrelationEngine::RunAlgorithm(vector<SurveillanceReport *> *adsb,
    vector<SurveillanceReport *> *tcas,
    vector<SurveillanceReport *> *radar) {
    Cluster *cluster;

    //Create individual clusters for all ads-b reports
    for (int i = 0; i < adsb->size(); i++) {
        cluster = NewCluster();
        cluster->_adsb = adsb->at(i);
        _clusters.push_back(cluster);
    }
    //Create individual clusters for all radar reports
    for (int i = 0; i < radar->size(); i++) {
        if (CompareRadarToClusters(radar->at(i)) == FALSE) {
            cluster = NewCluster();
            cluster->_radar = radar->at(i);
            _clusters.push_back(cluster);
        }
    }
    //Create individual clusters for all tcas reports
    for (int i = 0; i < tcas->size(); i++) {
        if (CompareTcasToClusters(tcas->at(i)) == FALSE) {
            cluster = NewCluster();
            cluster->_tcas = tcas->at(i);
            _clusters.push_back(cluster);
        }
    }

    return 0;
}

double CorrelationEngine::CompareRadarToClusters(SurveillanceReport *report) {
    int index = -1;
    double result = 0, val;

    for (int i = 0; i < _clusters.size(); i++) {
        if (_clusters.at(i)->_adsb != NULL) {
            if ((val = CalcDistance(_clusters.at(i)->_adsb, report)) > result) {
                result = val;
                index = i;
            }
        }

        if (_clusters.at(i)->_tcas != NULL) {
            if ((val = CalcDistance(_clusters.at(i)->_tcas, report)) > result) {
                result = val;
                index = i;
            }
        }
    }

    if (result >= MINDISTANCE) {
        _clusters.at(index)->_radar = report;
        result = TRUE;
    }
    else {
        result = FALSE;
    }

    return result;
}

double CorrelationEngine::CompareTcasToClusters(SurveillanceReport *report) {
    int index = -1;
    double result = 0, val;

    for (int i = 0; i < _clusters.size(); i++) {
        if (_clusters.at(i)->_adsb != NULL) {
            if ((val = CalcDistance(_clusters.at(i)->_adsb, report)) > result) {
                result = val;
                index = i;
            }
        }

        if (_clusters.at(i)->_radar != NULL) {
            if ((val = CalcDistance(_clusters.at(i)->_radar, report)) > result){
                result = val;
                index = i;
            }
        }
    }

    if (result >= MINDISTANCE) {
        _clusters.at(index)->_tcas = report;
        result = TRUE;
    }
    else {
        result = FALSE;
    }

    return result;
}

std::vector<CorrelationAircraft *>* CorrelationEngine::Correlate
        (ReceivedReports reports) {
    CorrelationAircraft *temp;
    _is_relative = reports.MakeRelative();

    vector<SurveillanceReport *> *adsb = reports.GetAdsb();
    vector<SurveillanceReport *> *tcas = reports.GetTcas();
    vector<SurveillanceReport *> *radar = reports.GetRadar();

    // Mutex lock for using the cluster vectors.
    if (mutexs)
        pthread_mutex_lock(&cluster_mutex);

    _corr_aircraft.clear();
    _clusters.clear();

    if (RunAlgorithm(adsb, tcas, radar) != TRUE) {
        printf("Error with running the Algorithm.\n");
        return NULL;
    }

    // Checks that all SurveillanceReports are in only one Cluster.
    if (CheckClusterCount() != TRUE) {
        printf("At least one SurveillanceReport is either not in a cluster or"
                       " in multiple clusters.\n");
        return NULL;
    }

    // Lock CorrelationAircraft vectors.
    if (mutexs)
        pthread_mutex_lock(&corr_aircraft_mutex);

    // For every cluster, call ConvertAircraft(), add to _corr_aircraft.
    for (uint32_t i = 0; i < _clusters.size(); i++) {
        temp = ConvertAircraft(_clusters.at(i));
        _corr_aircraft.push_back(temp);
    }

    // Unlock cluster vectors and CorrelationAircraft vectors.
    if (mutexs) {
        pthread_mutex_unlock(&cluster_mutex);
        pthread_mutex_unlock(&corr_aircraft_mutex);
    }

    return &_corr_aircraft;
}

CorrelationAircraft *CorrelationEngine::ConvertAircraft(Cluster *cluster) {
    Device type;
    CorrelationAircraft *aircraft;
    std::time_t time;
    TailNumber tail_number = TailNumber("      ");
    TcasID tcas_id = 0;
    RadarID radar_id = 0;
    SphericalCoordinate spherical_coordinate;
    GeographicCoordinate geographic_coordinate;
    Velocity velocity;
    GeographicCoordinate *adsbG = NULL, *tcasG = NULL, *radarG = NULL;
    SphericalCoordinate *adsbS = NULL, *tcasS = NULL, *radarS = NULL;
    Velocity *adsbV = NULL, *tcasV = NULL, *radarV = NULL;

    // Set Device type based on the ranking: ads-b is best, tcas, radar.
    if (cluster->_radar != NULL) {
        type = RADAR;
        time = cluster->_radar->GetTime();
        radar_id = cluster->_radar->GetRadarID();
        radarG = cluster->_radar->GetGeographicCoordinate();
        radarS = cluster->_radar->GetSphericalCoordinate();
        radarV = cluster->_radar->GetVelocity();
    }
    if (cluster->_tcas != NULL) {
        type = TCAS;
        time = cluster->_tcas->GetTime();
        tcas_id = cluster->_tcas->GetTcasID();
        tcasS = cluster->_tcas->GetSphericalCoordinate();
    }
    if (cluster->_adsb != NULL) {
        type = ADSB;
        time = cluster->_adsb->GetTime();
        tail_number = cluster->_adsb->GetTailNumber();
        adsbG = cluster->_adsb->GetGeographicCoordinate();
        adsbV = cluster->_adsb->GetVelocity();
    }

    // Check for empty clusters.
    if (cluster->_adsb == NULL && cluster->_tcas == NULL
        && cluster->_radar == NULL) {
        printf("Trying to convert empty Cluster to CorrelationAircraft\n");
        return NULL;
    }

    geographic_coordinate = GeographicCoordinate::Average(adsbG, tcasG, radarG);

    spherical_coordinate = SphericalCoordinate::Average(adsbS, tcasS, radarS);

    velocity = Velocity::Average(adsbV, tcasV, radarV);

    // TODO: Set prediction vectors (Dat).
    Velocity predicted_velocity = Velocity(0, 0, 0);
    GeographicCoordinate predicted_loc = GeographicCoordinate(0, 0, 0);

    aircraft = new CorrelationAircraft(time, tail_number, tcas_id, radar_id,
        geographic_coordinate, spherical_coordinate, velocity, predicted_velocity,
        predicted_loc, type);

    return aircraft;
}

int CorrelationEngine::CheckClusterCount() {
    int result = 0;

    for (int i = 0; i < _clusters.size(); i++) {
        if (_clusters.at(i)->_tcas == NULL && _clusters.at(i)->_radar == NULL
            && _clusters.at(i)->_adsb == NULL) {
            result = EXITVAL;
        }
    }

    return result;
}

Cluster *CorrelationEngine::NewCluster() {
    Cluster *cluster;

    cluster = new Cluster();
    cluster->_adsb = NULL;
    cluster->_radar = NULL;
    cluster->_tcas = NULL;
    cluster->_prediction = Velocity(0, 0, 0);

    return cluster;
}

double CorrelationEngine::CalcDistance(SurveillanceReport *reportOne,
    SurveillanceReport *reportTwo) {
    double distance = CalcEuclidDistance(reportOne, reportTwo);
    distance *= CalcHeading(reportOne, reportTwo);
    distance *= CalcVelocity(reportOne, reportTwo);

    distance = cbrt(distance);

    // Lowest metric value is 0.
    if (distance < 0) {
        distance = 0;
    }

    return distance;
}

double CorrelationEngine::CalcHeading(SurveillanceReport *reportOne,
    SurveillanceReport *reportTwo) {
    double difference, azimuth, elevation = 0, metric;

    // Check if ADS-B could be converted to spherical coordinates.
    if (_is_relative || (reportOne->GetDevice() != TCAS
        && reportTwo->GetDevice() != TCAS)) {
        // No way to calculate heading for unconverted ADSB.
        metric = 1;
    }
    // Compare most reports by spherical coordinates.
    else {
        // Calculate azimuth correlation.
        difference = abs(reportOne->GetAzimuth() - reportTwo->GetAzimuth());
        azimuth = (MAXAZIMUTHERROR - difference) / MAXAZIMUTHERROR;
        elevation = 1;

        // Calculate elevation correlation.
        if (reportOne->GetDevice() != TCAS && reportTwo->GetDevice() != TCAS) {
            difference = abs(reportOne->GetElevation() -
                reportTwo->GetElevation());
            elevation = (MAXELEVATIONERROR - difference) / MAXELEVATIONERROR;
        }

        metric = sqrt(elevation * azimuth);
    }

    // The reports are farther apart then the maximum distance.
    if (metric < 0) {
        metric = 0;
    }

    return metric;
}

double CorrelationEngine::CalcEuclidDistance(SurveillanceReport *reportOne,
    SurveillanceReport *reportTwo) {
    double range, difference, metric;
    SphericalCoordinate newCoord;
    GeographicCoordinate geoCoord;

    //if possible, use ownship from radar report to convert
        if (!_is_relative && reportOne->GetDevice() == RADAR
            && reportTwo->GetDevice() == ADSB) {
            //Create ownship geographical coordinate using Radar's ownship vals
            geoCoord = GeographicCoordinate(reportOne->GetLatitude(),
                reportOne->GetLongitude(), reportOne->GetAltitude());

            //convert TCAS to spherical
            newCoord = ReportReceiver::ConvertGeoToSphericalCoordinates
                 (reportTwo->GetGeographicCoordinate(), &geoCoord);

            reportTwo->SetSphericalCoordinate(newCoord);
        }
        else if (!_is_relative && reportTwo->GetDevice() == RADAR
            && reportOne->GetDevice() == ADSB) {
            //Create ownship geographical coordinate using Radar's ownship vals
            geoCoord = GeographicCoordinate(reportTwo->GetLatitude(),
                reportTwo->GetLongitude(), reportTwo->GetAltitude());

            //convert TCAS to spherical
            newCoord = ReportReceiver::ConvertGeoToSphericalCoordinates
                (reportOne->GetGeographicCoordinate(), &geoCoord);

            reportOne->SetSphericalCoordinate(newCoord);
        }

    // Check if ADS-B could be converted to spherical coordinates.
    if (_is_relative || (reportOne->GetDevice() != TCAS
        && reportTwo->GetDevice() != TCAS)) {
        // Calculate range correlation.
        difference = abs(reportOne->GetRange() - reportTwo->GetRange());
        range = (MAXRADARERROR - difference) / MAXRADARERROR;

        metric = range;
    }
    // No way to calculate heading for unconverted ADSB, so 1 to not skew result.
    else {
        metric = 1;
    }

    // The reports are farther apart then the maximum distance.
    if (metric < 0) {
        metric = 0;
    }

    return metric;
}

double CorrelationEngine::CalcVelocity(SurveillanceReport *reportOne,
    SurveillanceReport *reportTwo) {
    Velocity *oneVelocity = reportOne->GetVelocity();
    Velocity *twoVelocity = reportTwo->GetVelocity();
    double metric = 0, error, difference;

    /**
     * Checks if both reports are not TCAS,
     * or that the TCAS report has a prediction vector
     */
    if (reportOne->GetDevice() != TCAS && reportTwo->GetDevice() != TCAS) {
        difference = abs(oneVelocity->North() - twoVelocity->North());
        difference += abs(oneVelocity->East() - twoVelocity->East());
        difference += abs(oneVelocity->Down() - twoVelocity->Down());

        error = CalcVelocityError(reportOne->GetDevice());
        error += CalcVelocityError(reportTwo->GetDevice());
        metric = (error * difference) / error;
    }
    // Reports can't be compared, so has to be 1 to not skew result.
    else {
        metric = 1;
    }

    // The reports are farther apart then the maximum distance.
    if (metric < 0) {
        metric = 0;
    }

    return metric;
}

double CorrelationEngine::CalcVelocityError(Device type) {
    double error = -100;

    switch(type) {
        case ADSB:
            error = 15; // Feet per second
            break;
        case TCAS:
            // Same behavior as Radar.
        case RADAR:
            error = 20; // Feet per second
            break;
        default:
            printf("Error: invalid device type\n");
    }

    return error;
}
