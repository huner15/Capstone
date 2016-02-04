//
// Created by kevin on 1/20/16.
//

#ifndef SAAS_SIMULATIONREPORT_H
#define SAAS_SIMULATIONREPORT_H


#include <ownship.pb.h>
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
    OwnshipReport GetNextOwnshipReport();

    /**
     * Finds and returns the next TcasReport from an iterator
     * @return TcasReport with the data from the sensor.
     */
    TcasReport GetNextTcasReport();

    /**
     * Finds and returns the next RadarReport from the iterator
     * @return RadarReport with the data from the  sensor.
     */
    RadarReport GetNextRadarReport();

    /**
     * Finds and returns the next AdsbReport from the iterator.
     * @return AdsBReport with the data from the sensor.
     */
    AdsBReport GetNextAdsbReport();

    /**
     * Verifies if there are any more OwnshipReports left.
     * @return true if there are any more OwnshipReports in the vector.
     */
    bool HasNextOwnshipReport();

    /**
     * Verifies if there are any more TcasReports left.
     * @return true if there are any more TcasReports in the vector.
     */
    bool HasNextTcasReport();

    /**
     * Verifies if there are any more RadarReports left.
     * @return true if there are any more RadarReports in the vector.
     */
    bool HasNextRadarReport();

    /**
     * Verifies if there are any more AdsbReports left.
     * @return true if there are any more AdsbReports in the vector.
     */
    bool HasNextAdsbReport();


private:
    std::vector<Json::Value> own_reports_;
    std::vector<Json::Value>::iterator own_it_;
    std::vector<Json::Value> tcas_reports_;
    std::vector<Json::Value>::iterator tcas_it_;
    std::vector<Json::Value> radar_reports_;
    std::vector<Json::Value>::iterator radar_it_;
    std::vector<Json::Value> adsb_reports_;
    std::vector<Json::Value>::iterator adsb_it_;


};


#endif //SAAS_SIMULATIONREPORT_H
