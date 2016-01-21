//
// Created by kevin on 1/20/16.
//

#ifndef SAAS_SIMULATIONREPORT_H
#define SAAS_SIMULATIONREPORT_H


#include "ownship.pb.h"
#include <tcas.pb.h>
#include <adsb.pb.h>
#include <radar.pb.h>



class SimulationReport {
public:

    /**
     * Constructor for a SimulationReport
     */
    SimulationReport();

    /**
     * Finds and returns the next OwnshipReport from an iterator
     * @return OwnshipReport the next report
     */
    OwnshipReport getNextOwnshipReport();

    /**
     * Finds and returns the next TcasReport from an iterator
     * @return TcasReport with the data from the sensor.
     */
    TcasReport getNextTcasReport();

    /**
     * Finds and returns the next RadarReport from the iterator
     * @return RadarReport with the data from the  sensor.
     */
    RadarReport getNextRadarReport();

    /**
     * Finds and returns the next AdsbReport from the iterator.
     * @return AdsBReport with the data from the sensor.
     */
    AdsBReport getNextAdsbReport();

    /**
     * Verifies if there are any more OwnshipReports left.
     * @return true if there are any more OwnshipReports in the vector.
     */
    bool hasNextOwnshipReport();

    /**
     * Verifies if there are any more TcasReports left.
     * @return true if there are any more TcasReports in the vector.
     */
    bool hasNextTcasReport();

    /**
     * Verifies if there are any more RadarReports left.
     * @return true if there are any more RadarReports in the vector.
     */
    bool hasNextRadarReport();

    /**
     * Verifies if there are any more AdsbReports left.
     * @return true if there are any more AdsbReports in the vector.
     */
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
