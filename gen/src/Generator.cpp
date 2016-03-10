//
// Created by kevin on 3/9/16.
//

#include "Generator.h"
int main(int argc, char *argv[]) {

    if (argc != EXPECTED_ARGUMENTS) {
        std::cout << "usage: run_gen file_name" << std::endl;
    }
    else {
        std::ofstream file_id;
        SimulationGenerator gen(argv[1]);
        file_id.open("FinalSim.json", std::fstream::out);
        Json::StyledWriter styled_writer;
        file_id << styled_writer.write(gen.WriteReports());
        file_id.close();
    }
}