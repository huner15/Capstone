/*
 * @file TcasReceiver.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-28-16
 * @brief Implements the functionality of TcasReceiver.
 */

#include "TcasReceiver.h"

void TcasReceiver::ReceiveReport(ClientSocket &client_socket) {
    TcasReport tcas_report;
    client_socket >> tcas_report;
    _report_receiver.ReceiveTcas(tcas_report);
#ifdef DEBUG
    PrintReport(tcas_report);
#endif
}

void TcasReceiver::PrintReport(TcasReport &tcas_report) {
    std::cout << "Received TCAS Report" << std::endl;
    std::cout << "ID: " << tcas_report.id() << std::endl;
    std::cout << "Range: " << tcas_report.range() << std::endl;
    std::cout << "Altitude: " << tcas_report.altitude() << std::endl;
    std::cout << "Bearing: " << tcas_report.bearing() << std::endl;
}
