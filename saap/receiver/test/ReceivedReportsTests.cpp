/*
 * @file ReportReceiverTests.cpp
 * @author Specific Atomics
 * @author Frank Poole
 * @date 5-30-16
 * @brief Ensure the ReceivedReports works properly.
 */

#include <gtest/gtest.h>

#include "ReceivedReports.h"

/**
 * Ensure that the clear function actually clear the individual reports within a
 * Received Report.
 */
TEST(ReceivedReports, Clear) {
    ReceivedReports receivedReports;
    SurveillanceReport surveillanceReport;
    receivedReports.addAdsBReport(&surveillanceReport);
    receivedReports.addRadarReport(&surveillanceReport);
    receivedReports.addAdsBReport(&surveillanceReport);
    receivedReports.Clear();
    ASSERT_TRUE(receivedReports.GetAdsb()->empty());
    ASSERT_TRUE(receivedReports.GetRadar()->empty());
    ASSERT_TRUE(receivedReports.GetTcas()->empty());
}
