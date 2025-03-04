/*
 * @file Processor.cpp
 * @author Specific Atomics
 * @author Frank Poole, Alanna Buss
 * @date 4-14-16
 * @brief TODO
 */

#include "Processor.h"

int main(int argc, char *argv[]) {
    if (argc == EXPECTED_ARGUMENTS) {
        ReportReceiver report_receiver;
        Client client(report_receiver,
                      (in_port_t) atoi(argv[OWNSHIP_THREAD_INDEX + 2]),
                      (in_port_t) atoi(argv[ADSB_THREAD_INDEX + 2]),
                      (in_port_t) atoi(argv[RADAR_THREAD_INDEX + 2]),
                      (in_port_t) atoi(argv[TCAS_THREAD_INDEX + 2]),
                      (in_port_t) atoi(argv[CDTI_INDEX + 2]));

        client.Process();
    }
    else {
        std::cout <<
        "usage: run_saap host ownship_port adsb_port radar_port tcas_port "
                "cdti_port" <<
        std::endl;
    }
}
