//
// Created by kevin on 1/20/16.
//

#ifndef SAAS_SIMULATIONREPORT_H
#define SAAS_SIMULATIONREPORT_H


#include "../../../../.CLion12/system/cmake/generated/e2817c85/e2817c85/Debug/lib/gp/capstone-shared/ownship.pb.h"
#include "../../../../.CLion12/system/cmake/generated/e2817c85/e2817c85/Debug/lib/gp/capstone-shared/tcas.pb.h"
#include "../../../../.CLion12/system/cmake/generated/e2817c85/e2817c85/Debug/lib/gp/capstone-shared/adsb.pb.h"
#include "../../../../.CLion12/system/cmake/generated/e2817c85/e2817c85/Debug/lib/gp/capstone-shared/radar.pb.h"

class SimulationReport {
public:

    SimulationReport();

    OwnshipReport getNextOwnshipReport();
    TcasReport getNextTcasReport();
    RadarReport getNextRadarReport();
    AdsBReport getNextAdsbReport();

    bool hasNextOwnshipReport();
    bool hasNextTcasReport();
    bool hasNextRadarReport();
    bool hasNextAdsbReport();


private:
    std::vector<Json::Value> ownReports;
    std::vector<Json::Value>::iterator ownIt;
    std::vector<Json::Value> tcasReports;
    std::vector<Json::Value>::iterator tcasIt;
    std::vector<Json::Value> radarReports;
    std::vector<Json::Value>::iterator radarIt;
    std::vector<Json::Value> adsbReports;
    std::vector<Json::Value>::iterator adsbIt;


};


#endif //SAAS_SIMULATIONREPORT_H
