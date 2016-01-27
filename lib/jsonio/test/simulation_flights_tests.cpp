//
// Created by kevin on 1/20/16.
//

#include <SimulationFlightsIO.h>
#include <gtest/gtest.h>

TEST(GetSimulationFlights, CorrectNumberOfFlights) {
    Json::Value simulation_flights =
            SimulationFlightsIO::getSimulationFlights();

    ASSERT_EQ(8, simulation_flights.size());
}

TEST(GetAdsBReports, CorrectData) {
    std::vector<Json::Value> adsb_reports =
            SimulationFlightsIO::getAllADSBReports();

    ASSERT_EQ("12ASX3", adsb_reports[0]["tailNo"].asString());
    ASSERT_EQ(1, adsb_reports[0]["time"].asInt());
    ASSERT_EQ(10, adsb_reports[0]["latitude"].asFloat());
    ASSERT_EQ(12, adsb_reports[0]["longitude"].asFloat());
    ASSERT_EQ(20000, adsb_reports[0]["altitude"].asFloat());
    ASSERT_EQ(4, adsb_reports[0]["north"].asFloat());
    ASSERT_EQ(56, adsb_reports[0]["east"].asFloat());
    ASSERT_EQ(245, adsb_reports[0]["down"].asFloat());
}

TEST(GetAdsBReports, CorectNumberOfReports) {
    std::vector<Json::Value> adsb_reports =
            SimulationFlightsIO::getAllADSBReports();

    ASSERT_EQ(8, adsb_reports.size());
}



TEST(GetTcasReports, CorrectNumberOfReports) {
    std::vector<Json::Value> tcas_reports =
            SimulationFlightsIO::getAllTCASReports();

    ASSERT_EQ(8, tcas_reports.size());
}

TEST(GetTcasReports, CorrectData) {
    std::vector<Json::Value> tcas_reports =
            SimulationFlightsIO::getAllTCASReports();

    ASSERT_EQ(1, tcas_reports[0]["id"].asInt());
    ASSERT_EQ(12000, tcas_reports[0]["altitude"].asFloat());
    ASSERT_EQ(120, tcas_reports[0]["bearing"].asInt());
    ASSERT_EQ(2, tcas_reports[0]["range"].asInt());
}

TEST(GetOwnshipReports, CorrectNumberOfReports) {
    std::vector<Json::Value> ownship_reports =
            SimulationFlightsIO::getALlOwnshipReports();

    ASSERT_EQ(8, ownship_reports.size());
}

TEST(GetOwnshipReports, CorrectData) {
    std::vector<Json::Value> ownship_reports =
            SimulationFlightsIO::getALlOwnshipReports();

    ASSERT_EQ(1, ownship_reports[0]["time"].asInt());
    ASSERT_EQ(30500, ownship_reports[0]["altitude"].asFloat());
    ASSERT_EQ(21, ownship_reports[0]["latitude"].asFloat());
    ASSERT_EQ(78, ownship_reports[0]["longitude"].asFloat());
    ASSERT_EQ(4, ownship_reports[0]["north"].asFloat());
    ASSERT_EQ(56, ownship_reports[0]["east"].asFloat());
    ASSERT_EQ(245, ownship_reports[0]["down"].asFloat());
}

TEST(GetRadarReports, CorrectNumberOfReports) {
    std::vector<Json::Value> radar_reports =
            SimulationFlightsIO::getAllRadarReports();

    ASSERT_EQ(8, radar_reports.size());
}

TEST(GetRadarReports, CorrectData) {
    std::vector<Json::Value> radar_reports =
            SimulationFlightsIO::getAllRadarReports();

    ASSERT_EQ(1, radar_reports[0]["time"].asInt());
    ASSERT_EQ(2, radar_reports[0]["range"].asInt());
    ASSERT_EQ(120, radar_reports[0]["azimuth"].asInt());
    ASSERT_EQ(30, radar_reports[0]["elevation"].asFloat());
    ASSERT_EQ(20000, radar_reports[0]["altitude"].asFloat());
    ASSERT_EQ(23, radar_reports[0]["latitude"].asFloat());
    ASSERT_EQ(34, radar_reports[0]["longitude"].asFloat());
    ASSERT_EQ(4, radar_reports[0]["north"].asFloat());
    ASSERT_EQ(56, radar_reports[0]["east"].asFloat());
    ASSERT_EQ(245, radar_reports[0]["down"].asFloat());
}