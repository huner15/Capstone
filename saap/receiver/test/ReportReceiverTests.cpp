/*
 * @file ReportReceiverTests.cpp
 * @author Specific Atomics
 * @author Alanna Buss
 * @date 2-18-16
 * @brief Ensure the ReportReceiver works properly
 */

#include <gtest/gtest.h>
#include <ReportReceiver.h>
#include <Device.h>

/*
 * Tests to see that the ownship surveillance report creator is properly
 * functioning.
 */
TEST(ReportReceiverOwnshipSurveillanceReports, SingleReport) {
    OwnshipReport ownshipReport = OwnshipReport();
    std::time_t time = std::time_t(1);
    ownshipReport.set_timestamp(time);
    ownshipReport.set_ownship_latitude(2);
    ownshipReport.set_ownship_longitude(3);
    ownshipReport.set_ownship_altitude(4);
    ownshipReport.set_north(5);
    ownshipReport.set_down(6);
    ownshipReport.set_east(7);



    ReportReceiver reportReceiver = ReportReceiver();
    reportReceiver.ReceiveOwnship(ownshipReport);

    SurveillanceReport * surveillanceReport = reportReceiver.getOwnship();

    EXPECT_EQ(time, surveillanceReport->GetTime());
    EXPECT_EQ(2.0, surveillanceReport->GetLatitude());
    EXPECT_EQ(3, surveillanceReport->GetLongitude());
    EXPECT_EQ(4, surveillanceReport->GetAltitude());
    EXPECT_EQ(5, surveillanceReport->GetVelocity().north);
    EXPECT_EQ(6, surveillanceReport->GetVelocity().down);
    EXPECT_EQ(7, surveillanceReport->GetVelocity().east);
    EXPECT_EQ(OWNSHIP, surveillanceReport->GetDevice());

}

TEST(ReportReceiverOwnshipSurveillanceReport, TwoReports){
    OwnshipReport ownshipReport = OwnshipReport();
    std::time_t time = std::time_t(1);
    ownshipReport.set_timestamp(time);
    ownshipReport.set_ownship_latitude(2);
    ownshipReport.set_ownship_longitude(3);
    ownshipReport.set_ownship_altitude(4);
    ownshipReport.set_north(5);
    ownshipReport.set_down(6);
    ownshipReport.set_east(7);



    ReportReceiver reportReceiver = ReportReceiver();
    reportReceiver.ReceiveOwnship(ownshipReport);

    SurveillanceReport * surveillanceReport = reportReceiver.getOwnship();

    EXPECT_EQ(time, surveillanceReport->GetTime());
    EXPECT_EQ(2.0, surveillanceReport->GetLatitude());
    EXPECT_EQ(3, surveillanceReport->GetLongitude());
    EXPECT_EQ(4, surveillanceReport->GetAltitude());
    EXPECT_EQ(5, surveillanceReport->GetVelocity().north);
    EXPECT_EQ(6, surveillanceReport->GetVelocity().down);
    EXPECT_EQ(7, surveillanceReport->GetVelocity().east);
    EXPECT_EQ(OWNSHIP, surveillanceReport->GetDevice());

    OwnshipReport ownshipReport2 = OwnshipReport();
    std::time_t time2 = std::time_t(8);
    ownshipReport2.set_timestamp(time2);
    ownshipReport2.set_ownship_latitude(9);
    ownshipReport2.set_ownship_longitude(10);
    ownshipReport2.set_ownship_altitude(11);
    ownshipReport2.set_north(12);
    ownshipReport2.set_down(13);
    ownshipReport2.set_east(14);

    reportReceiver.ReceiveOwnship(ownshipReport2);
    surveillanceReport = reportReceiver.getOwnship();


    EXPECT_EQ(time2, surveillanceReport->GetTime());
    EXPECT_EQ(9, surveillanceReport->GetLatitude());
    EXPECT_EQ(10, surveillanceReport->GetLongitude());
    EXPECT_EQ(11, surveillanceReport->GetAltitude());
    EXPECT_EQ(12, surveillanceReport->GetVelocity().north);
    EXPECT_EQ(13, surveillanceReport->GetVelocity().down);
    EXPECT_EQ(14, surveillanceReport->GetVelocity().east);
    EXPECT_EQ(OWNSHIP, surveillanceReport->GetDevice());
}

TEST(ReportReceiverTcasSurveillanceReports, OneReport){

    TcasReport tcasReport = TcasReport();
    TcasID tcasID = TcasID();
    tcasReport.set_id(tcasID.Get());
    tcasReport.set_altitude(1);
    tcasReport.set_bearing(2);
    tcasReport.set_range(3);

    ReportReceiver reportReceiver = ReportReceiver();

    vector<SurveillanceReport *>* reports = reportReceiver.getTcas();

    EXPECT_EQ(0, reports->size());

    reportReceiver.ReceiveTcas(tcasReport);
    reports = reportReceiver.getTcas();
    EXPECT_EQ(1, reports->size());

    SurveillanceReport * surveillanceReport = reports->at(0);

    EXPECT_EQ(tcasID.Get(), surveillanceReport->GetTcasID().Get());
    EXPECT_EQ(1, surveillanceReport->GetAltitude());
    EXPECT_EQ(2, surveillanceReport->GetBearing());
    EXPECT_EQ(3, surveillanceReport->GetRange());
    EXPECT_EQ(TCAS, surveillanceReport->GetDevice());
}

TEST(ReportReceiverTcasSurveillanceReport, TwoReports){
    TcasReport tcasReport = TcasReport();
    TcasID tcasID = TcasID();
    tcasReport.set_id(tcasID.Get());
    tcasReport.set_altitude(1);
    tcasReport.set_bearing(2);
    tcasReport.set_range(3);

    ReportReceiver reportReceiver = ReportReceiver();

    vector<SurveillanceReport *>* reports = reportReceiver.getTcas();

    EXPECT_EQ(0, reports->size());

    reportReceiver.ReceiveTcas(tcasReport);
    reports = reportReceiver.getTcas();
    EXPECT_EQ(1, reports->size());

    SurveillanceReport * surveillanceReport = reports->at(0);

    EXPECT_EQ(tcasID.Get(), surveillanceReport->GetTcasID().Get());
    EXPECT_EQ(1, surveillanceReport->GetAltitude());
    EXPECT_EQ(2, surveillanceReport->GetBearing());
    EXPECT_EQ(3, surveillanceReport->GetRange());
    EXPECT_EQ(TCAS, surveillanceReport->GetDevice());

    TcasReport tcasReport1 = TcasReport();
    TcasID tcasID1 = TcasID();
    tcasReport1.set_id(tcasID1.Get());
    tcasReport1.set_altitude(4);
    tcasReport1.set_bearing(5);
    tcasReport1.set_range(6);

    reportReceiver.ReceiveTcas(tcasReport1);
    reports = reportReceiver.getTcas();

    EXPECT_EQ(2, reports->size());

    surveillanceReport = reports->at(0);
    EXPECT_EQ(tcasID.Get(), surveillanceReport->GetTcasID().Get());
    EXPECT_EQ(1, surveillanceReport->GetAltitude());
    EXPECT_EQ(2, surveillanceReport->GetBearing());
    EXPECT_EQ(3, surveillanceReport->GetRange());
    EXPECT_EQ(TCAS, surveillanceReport->GetDevice());

    surveillanceReport = reports->at(1);
    EXPECT_EQ(tcasID1.Get(), surveillanceReport->GetTcasID().Get());
    EXPECT_EQ(4, surveillanceReport->GetAltitude());
    EXPECT_EQ(5, surveillanceReport->GetBearing());
    EXPECT_EQ(6, surveillanceReport->GetRange());
    EXPECT_EQ(TCAS, surveillanceReport->GetDevice());
}