/*
 * @file ReportReceiverTests.cpp
 * @author Specific Atomics
 * @author Alanna Buss
 * @date 2-18-16
 * @brief Ensure the ReportReceiver works properly
 */

#include <gtest/gtest.h>
#include <ReportReceiver.h>

/*
 * Tests to see that the ownship surveillance report creator is properly
 * functioning.
 */
TEST(ReportReceiverOwnshipSurveillanceReports, SingleReport) {
    OwnshipReport ownshipReport = OwnshipReport();
    ownshipReport.set_timestamp(1);
    ownshipReport.set_ownship_latitude(2);
    ownshipReport.set_ownship_longitude(3);
    ownshipReport.set_ownship_altitude(4);
    ownshipReport.set_north(5);
    ownshipReport.set_down(6);
    ownshipReport.set_east(7);

    //ReportReceiver reportReceiver = ReportReceiver();
    //reportReceiver.ReceiveOwnship(ownshipReport);
    //SurveillanceReport surveillanceReport = reportReceiver.getOwnship();

    //EXPECT_EQ(1, surveillanceReport.getTime());
    //EXPECT_EQ(2, surveillanceReport.getLatitude());
    EXPECT_EQ(3, 2);
}
