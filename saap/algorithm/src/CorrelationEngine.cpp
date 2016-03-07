/**
* @file CorrelationEngine.cpp
* @author Specific Atomics
* @author Andrea Savage
* @date 3-5-16
* @brief The main correlation engine class with most of the distance logic that
 * all of the interchangeable algorithms will be based on.
*/

#include <GenerationMath.h>
#include "CorrelationEngine.h"

using namespace std;

CorrelationEngine::CorrelationEngine() {

}

CorrelationEngine::~CorrelationEngine() {

}

int CorrelationEngine::RunAlgorithm(vector<SurveillanceReport *> *adsb,
    vector<SurveillanceReport *> *tcas,
    vector<SurveillanceReport *> *radar) {
    Cluster *cluster;

    printf("Running top level algorithm\n");

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

int CorrelationEngine::Correlate(vector<SurveillanceReport *> *adsb,
        vector<SurveillanceReport *> *tcas,
        vector<SurveillanceReport *> *radar, bool is_relative) {
    _is_relative = is_relative;

    //mutex lock for using the cluster vectors
    pthread_mutex_lock(&cluster_mutex);
    _clusters.clear();

    if (RunAlgorithm(adsb, radar, tcas) != TRUE) {
        printf("Error with running the Algorithm.\n");
        return EXITVAL;
    }

    //Checks that all SurveillanceReports are in only one Cluster
    if (CheckClusterCount() != TRUE) {
        printf("At least one SurveillanceReport is either not in a cluster or"
                       " in multiple clusters.\n");
        return EXITVAL;
    }

    //lock CorrelationAircraft vectors
    pthread_mutex_lock(&corr_aircraft_mutex);

    //for every cluster, call ConvertAircraft(), add to _corr_aircraft
    for (uint32_t i = 0; i < _clusters.size(); i++) {
        ConvertAircraft(_clusters.at(i));
        _free_clusters.push_back(_clusters.at(i));
    }

    //unlock cluster vectors
    _clusters.clear();
    pthread_mutex_unlock(&cluster_mutex);

    //Send all correlate aircraft to the
    Categorize(&_corr_aircraft);

    //Delete Correlate and Cluster data
    for (int i = 0; i < _corr_aircraft.size(); i++) {
        _free_aircraft.push_back(_corr_aircraft.at(i));
    }

    _corr_aircraft.clear();

    //unlock CorrelationAircraft vectors
    pthread_mutex_unlock(&corr_aircraft_mutex);

    return 0;

}

int CorrelationEngine::ConvertAircraft(Cluster *cluster) {
    Device type;
    CorrelationAircraft *aircraft;

    //Set Device type based on the ranking: ads-b, tcas, radar
    if (cluster->_adsb != NULL) {
        type = ADSB;
    }
    else if (cluster->_tcas != NULL) {
        type = TCAS;
    }
    else if (cluster->_radar != NULL) {
        type = RADAR;
    }
    else {
        printf("Trying to convert empty Cluster to CorrelationAircraft\n");
        return EXITVAL;
    }

    std::time_t time = cluster->_adsb->GetTime();
    TailNumber tail_number = cluster->_adsb->GetTailNumber();
    TcasID tcas_id = cluster->_tcas->GetTcasID();
    RadarID radar_id = cluster->_radar->GetRadarID();

    GeographicCoordinate geographic_coordinate = *
        GeographicCoordinate::Average(cluster->_adsb->GetGeographicCoordinate(),
        cluster->_tcas->GetGeographicCoordinate(),
        cluster->_radar->GetGeographicCoordinate());

    SphericalCoordinate spherical_coordinate = *
        SphericalCoordinate::Average(cluster->_adsb->GetSphericalCoordinate(),
        cluster->_tcas->GetSphericalCoordinate(),
        cluster->_radar->GetSphericalCoordinate());

    Velocity velocity = *Velocity::Average(cluster->_adsb->GetVelocity(),
        cluster->_tcas->GetVelocity(), cluster->_radar->GetVelocity());

    //Set prediction vectors
    Velocity predictedVector = Velocity(0, 0, 0);
    Velocity predictedLoc = Velocity(0, 0, 0);

    aircraft = new CorrelationAircraft(time, tail_number, tcas_id, radar_id,
        geographic_coordinate, spherical_coordinate, velocity, predictedVector,
        predictedLoc, type);

    _corr_aircraft.push_back(aircraft);

    return 0;
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

    if (_free_clusters.empty()) {
        cluster = (Cluster *) malloc(sizeof(Cluster));
    }
    else {
        cluster = _free_clusters.at(_clusters.size() - 1);
        _free_clusters.pop_back();
    }

    cluster->_adsb = NULL;
    cluster->_radar = NULL;
    cluster->_tcas = NULL;
    cluster->_prediction = Velocity(0, 0, 0);

    return cluster;
}

CorrelationAircraft *CorrelationEngine::NewCorrAircraft() {
    CorrelationAircraft *aircraft;

    if (_free_aircraft.empty()) {
        aircraft = (CorrelationAircraft *) malloc(sizeof(CorrelationAircraft));
    }
    else {
        aircraft = _free_aircraft.at(_free_aircraft.size() - 1);
        _free_aircraft.pop_back();
    }

    return aircraft;
}

double CorrelationEngine::CalcDistance(SurveillanceReport *reportOne,
    SurveillanceReport *reportTwo) {
    double distance = CalcHeading(reportOne, reportTwo);
    distance += CalcEuclidDistance(reportOne, reportTwo);
    distance += CalcVelocity(reportOne, reportTwo);

    return cbrt(distance);
}

double CorrelationEngine::CalcHeading(SurveillanceReport *reportOne,
    SurveillanceReport *reportTwo) {
    double difference, azimuth, elevation, metric;

    //ADS-B could not be converted to spherical coordinates
    if (_is_relative == FALSE && (reportOne->GetDevice() == ADSB
        || reportTwo->GetDevice() == ADSB)) {
        //no way to calculate heading for unconverted adsb
        metric = 1;
    }
    //compare most reports by spherical coordinates
    else {
        //calculate azimuth correlation
        difference = reportOne->GetAzimuth() - reportTwo->GetAzimuth();
        azimuth = (MAXAZIMUTHERROR - difference) / MAXAZIMUTHERROR;

        //calculate elevation correlation
        difference = reportOne->GetElevation() - reportTwo->GetElevation();
        elevation = (MAXELEVATIONERROR - difference) / MAXELEVATIONERROR;

        metric = sqrt(elevation + azimuth);
    }

    return metric;
}

double CorrelationEngine::CalcEuclidDistance(SurveillanceReport *reportOne,
    SurveillanceReport *reportTwo) {
    double range, azimuth, elevation, difference, metric;
    SphericalCoordinate coord;
    GeographicCoordinate geoCoord;

    //if possible, use ownship from radar report to convert
    if (_is_relative == FALSE && (reportOne->GetDevice() == RADAR
        || reportTwo->GetDevice() == RADAR)) {
        //report one is the radar report
        if (reportOne->GetDevice() == RADAR) {
            //Create ownship geographical coordinate using Radar's ownship vals
            geoCoord = GeographicCoordinate(reportOne->GetLatitude(),
                reportOne->GetLongitude(), reportOne->GetAltitude());

            //convert TCAS to spherical
            coord = ConvertGeoToSpher(reportTwo->GetGeographicCoordinate(),
                &geoCoord);

            reportTwo->SetSphericalCoordinate(coord);
        }
        else {
            //Create ownship geographical coordinate using Radar's ownship vals
            geoCoord = GeographicCoordinate(reportTwo->GetLatitude(),
                reportTwo->GetLongitude(), reportTwo->GetAltitude());

            //convert TCAS to spherical
            coord = ConvertGeoToSpher(reportOne->GetGeographicCoordinate(),
                &geoCoord);

            reportOne->SetSphericalCoordinate(coord);
        }

        _is_relative = TRUE;
    }

    //check if ADS-B could not be converted to spherical coordinates
    if (_is_relative == FALSE && reportOne->GetDevice() != ADSB
        && reportTwo->GetDevice() != ADSB) {
        //calculate range correlation
        difference = reportOne->GetRange() - reportTwo->GetRange();
        range = (MAXRADARERROR - difference) / MAXRADARERROR;

        metric = range;
    }
    //no way to calculate heading for unconverted adsb, so 1 to not skew result
    else {
        metric = 1;
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
        difference = abs(oneVelocity->north - twoVelocity->north);
        difference += abs(oneVelocity->east - twoVelocity->east);
        difference += abs(oneVelocity->down - twoVelocity->down);

        error = CalcVelocityError(reportOne->GetDevice());
        error += CalcVelocityError(reportTwo->GetDevice());
        metric = (error * difference) / error;
    }
    //Reports can't be compared, so have to be 1 to not skew result
    else {
        metric = 1;
    }

    //The reports are farther apart then the maximum distance
    if (metric < 0) {
        metric = 0;
    }

    return metric;
}

double CorrelationEngine::CalcVelocityError(Device type) {
    double error = 30;

    switch(type) {
        case ADSB:
            error = 15; //feet per second
            break;
        case TCAS:
        case RADAR:
            error = 20; //feet per second
            break;
        default:
            printf("Error: invalid device type\n");
    }

    return error;
}

//TODO take in to account ownship heading should be zero
SphericalCoordinate CorrelationEngine::ConvertGeoToSpher(
    GeographicCoordinate *aircraft, GeographicCoordinate *ownship)
{
    double range, elevation, azimuth, r, z, y, x;

    //use util method to find physical distance between both points
    range = GenerationMath::DistanceBetweenTwoCoordinates(*aircraft, *ownship);

    //set cylindrical values
    z = aircraft->GetAltitude() - ownship->GetAltitude();
    r = sqrt(pow(range, 2) - pow(z, 2));

    //set cartesian coordinates
    x = aircraft->GetLatitude() - ownship->GetLatitude();
    y = aircraft->GetLongitude() - ownship->GetLongitude();

    //Calculate elevation and azimuth
    elevation = atan(r / z);
    azimuth = atan(y / x);

    return SphericalCoordinate(range, elevation, azimuth);
}