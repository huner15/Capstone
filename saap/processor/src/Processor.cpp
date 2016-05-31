/*
 * @file Processor.cpp
 * @author Specific Atomics
 * @author Frank Poole, Alanna Buss
 * @date 4-14-16
 * @brief TODO
 */

#include <FakeCorrelator.h>
#include "Processor.h"

int main(int argc, char *argv[]) {
    if (argc == EXPECTED_ARGUMENTS) {
        ReportReceiver report_receiver;
        //TODO make the creation of Correlation Engine based on command line
        // arguments to easily change the Correlation Engine and take out the
        // dependencies
        Categorizer* categorizer = new Categorizer();

        CorrelationEngine correlator = CorrelationEngine();

        Client client(report_receiver, correlator, *categorizer,
                      std::string(argv[1]),
                      (in_port_t) atoi(argv[OWNSHIP_THREAD_INDEX + 2]),
                      (in_port_t) atoi(argv[ADSB_THREAD_INDEX + 2]),
                      (in_port_t) atoi(argv[RADAR_THREAD_INDEX + 2]),
                      (in_port_t) atoi(argv[TCAS_THREAD_INDEX + 2]),
                      std::string(argv[CDTI_INDEX + 2]),
                      (in_port_t) atoi(argv[CDTI_INDEX + 3]));

        client.StartReceivers();
    }
    else {
        std::cout <<
        "usage: run_saap host ownship_port adsb_port radar_port tcas_port "
                "cdti_host cdti_port" <<
        std::endl;
    }
}
