/**
* @file CorrelationEngine.h
* @author Specific Atomics
* @author Andrea Savage
* @date 2-23-16
* @brief The main correlation engine class with most of the distance logic that
 * all of the intserchangeable algorithms will be based on.
*/

#ifndef SAAS_CORRELATIONENGINE_H
#define SAAS_CORRELATIONENGINE_H

using namespace std;

class CorrelationEngine {
public:
    vector<Cluster *> _clusters;
    vector<Cluster *> _free_clusters;
    vector<CorrelationAircraft *> _corr_aircraft;
    vector<CorrelationAircraft *> _free_aircraft;

    CorrelationEngine();

    ~CorrelationEngine();

    void RunAlgorithm();

    int Correlate(vector<SurveillanceReport *> *adsb,
        vector<SurveillanceReport *> *tcas,vector<SurveillanceReport *> *radar,
        bool ifRelative);

    int ConvertAircraft(Cluster *cluster);

    int CheckClusterCount();

    Cluster *newCluster();

    CorrelationAircraft *newCorrAircraft();

    float CalcDistance(SurveillanceReport *reportOne, SurveillanceReport
        *reportTwo);

    float CalcHeading(SurveillanceReport *reportOne,
                                          SurveillanceReport *reportTwo);

    float CalcSpeed(SurveillanceReport *reportOne,
                                          SurveillanceReport *reportTwo);

    float CalcEuclidDistance(SurveillanceReport *reportOne,
                                                SurveillanceReport *reportTwo);
};

#endif