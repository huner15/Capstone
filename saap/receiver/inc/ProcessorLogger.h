//
// Created by andrea on 5/19/16.
//

#ifndef PROCESSORLOGGER_H
#define PROCESSORLOGGER_H

#include "Client.h"
#include "ReceivedReports.h"
#include "CorrelationAircraft.h"
#include <cdti.pb.h>
#include <fstream>

class ProcessorLogger {
public:
    ProcessorLogger();

    ~ProcessorLogger();

    void LogCDTIReport(CDTIReport *report);

    void LogCorrelationAircraft(std::vector<CorrelationAircraft *> *aircraft);

    void LogReceivedReports(ReceivedReports *reports);

private:
    std::ofstream _cdtiReportData;

    std::ofstream _aircraftData;

    std::ofstream _surveillanceReportsData;

    int _snapshotIndex;

    void writeVector(Vector *vec);
};

#endif //SAAS_PROCESSORLOGGER_H
