/*
 * @file TcasReceiver.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 2-21-16
 * @brief TODO: Description
 */

#include "TcasReceiver.h"

void TcasReceiver::ReceiveReport(ClientSocket &client_socket) {
    TcasReport tcas_report;
    client_socket >> tcas_report;
    PrintReport(tcas_report);
    std::cout << std::endl;
}

void TcasReceiver::PrintReport(TcasReport &tcas_report) {
    std::cout << "Received TCAS Report" << std::endl;
    std::cout << "ID: " << tcas_report.id() << std::endl;
    std::cout << "Range: " << tcas_report.range() << std::endl;
    std::cout << "Altitude: " << tcas_report.altitude() << std::endl;
    std::cout << "Bearing: " << tcas_report.bearing() << std::endl;
}
