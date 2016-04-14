/*
 * @file Generator.cpp
 * @author Specific Atomics
 * @authors Kevin Pham, Frank Poole
 * @date 4-13-16
 * @brief TODO: Description
 */

#include "Generator.h"

int main(int argc, char *argv[]) {

    if (argc == EXPECTED_ARGUMENTS) {
        try {
            SimulationGenerator gen(argv[1]);

            std::ofstream file_id;
            file_id.open(argv[2], std::fstream::out);
            Json::StyledWriter styled_writer;
            file_id << styled_writer.write(gen.WriteReports());
            file_id.close();
        }
        catch (std::invalid_argument exception) {
            std::cout << "Invalid generation file." << std::endl;
        }
    }
    else {
        std::cout << "usage: run_gen input_file_name output_file_name"
        << std::endl;
    }
}
