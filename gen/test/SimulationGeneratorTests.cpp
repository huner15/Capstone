/*
 * SimulationGeneratorTests.cpp
 * Specific Atomics
 * Kevin Pham
 * 2-28-16
 * Test functionality of SimulationGenerator
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SimulationGenerator.h"




TEST(Test, TestWritingToFile) {

    std::ofstream file_id;
    SimulationGenerator gen("FlightScenarioInput.json");
    Json::Value all_reports;
    all_reports["ownship"] = gen.WriteRadarReports();
    all_reports["adsb"] = gen.WriteAdsbReports();
    all_reports["radar"] = gen.WriteRadarReports();
    all_reports["tcas"] = gen.WriteTcasReports();
    file_id.open("FinalSim.json", std::fstream::out);
    Json::StyledWriter styled_writer;
    file_id << styled_writer.write( all_reports);
    file_id.close();
}