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
    file_id.open("FinalSim.json", std::fstream::out);
    Json::StyledWriter styled_writer;
    file_id << styled_writer.write( gen.WriteReports());
    file_id.close();
}