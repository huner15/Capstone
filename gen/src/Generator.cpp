//
// Created by kevin on 3/9/16.
//

#include "Generator.h"

int main() {
    std::ofstream file_id;
    SimulationGenerator gen("FlightScenarioInput.json");
    file_id.open("FinalSim.json", std::fstream::out);
    Json::StyledWriter styled_writer;
    file_id << styled_writer.write( gen.WriteReports());
    file_id.close();
}