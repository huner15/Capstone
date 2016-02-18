/*
 * @file FlightReportTests.cpp
 * @author SpecificAtomics
 * @author Alanna Buss
 * @date 2-18-16
 * @brief  Ensures the functionality of FlightReport.
 */

#include <gtest/gtest.h>
#include <FlightReport.h>

/*
 * Tests to see that FlightReport returns what it is given with its get
 * functions.
 */
TEST(FlightReportConstructor, Assignment){
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 20,
                                                                     30);
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(15, 25, 35);
    Velocity velocity = Velocity(2, 3, 4);
    Device device = ADSB;

    FlightReport flightReport = FlightReport(time, tailNumber, tcasID,
                                             radarID, geographicCoordinate,
                                             sphericalCoordinate, velocity,
                                             device);

    EXPECT_EQ(1, flightReport.GetTime());
    EXPECT_EQ(tailNumber.Get(), flightReport.GetTailNumber().Get());
    EXPECT_EQ(tcasID.Get(), flightReport.GetTcasID().Get());
    EXPECT_EQ(radarID.Get(), flightReport.GetRadarID().Get());
    EXPECT_EQ(geographicCoordinate.GetAltitude(), flightReport
            .GetGeographicCoordinate().GetAltitude());
    EXPECT_EQ(geographicCoordinate.GetLatitude(), flightReport
            .GetGeographicCoordinate().GetLatitude());
    EXPECT_EQ(geographicCoordinate.GetLongitude(), flightReport
            .GetGeographicCoordinate().GetLongitude());
    EXPECT_EQ(sphericalCoordinate.GetAzimuth(), flightReport
            .GetSphericalCoordinate().GetAzimuth());
    EXPECT_EQ(sphericalCoordinate.GetBearing(), flightReport
            .GetSphericalCoordinate().GetBearing());
    EXPECT_EQ(sphericalCoordinate.GetElevation(), flightReport
            .GetSphericalCoordinate().GetElevation());
    EXPECT_EQ(sphericalCoordinate.GetRange(), flightReport
            .GetSphericalCoordinate().GetRange());
    EXPECT_EQ(velocity.north, flightReport.GetVelocity().north);
    EXPECT_EQ(velocity.east, flightReport.GetVelocity().east);
    EXPECT_EQ(velocity.down, flightReport.GetVelocity().down);
    EXPECT_EQ(device, flightReport.GetDevice());

}

/*
 * Tests to see if FlightReport correctly makes an ownship report.
 */
TEST(FlightReportMakeOwnshipReport, Creation){
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 20,
                                                                     30);
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(15, 25, 35);
    Velocity velocity = Velocity(2, 3, 4);
    Device device = ADSB;

    FlightReport flightReport = FlightReport(time, tailNumber, tcasID,
                                             radarID, geographicCoordinate,
                                             sphericalCoordinate, velocity,
                                             device);
    OwnshipReport ownshipReport = flightReport.CreateOwnshipReport();

    EXPECT_EQ(time, ownshipReport.timestamp());
    EXPECT_EQ(geographicCoordinate.GetLatitude(), ownshipReport
            .ownship_latitude());
    EXPECT_EQ(geographicCoordinate.GetLongitude(), ownshipReport
            .ownship_longitude());
    EXPECT_EQ(geographicCoordinate.GetAltitude(), ownshipReport
            .ownship_altitude());
    EXPECT_EQ(velocity.north, ownshipReport.north());
    EXPECT_EQ(velocity.east, ownshipReport.east());
    EXPECT_EQ(velocity.down, ownshipReport.down());
}

/*
 * Tests to see if Flight Report correctly creates ADSB reports
 */

TEST(FlightReportMakeADSBReport, Creation) {
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 20,
                                                                     30);
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(15, 25, 35);
    Velocity velocity = Velocity(2, 3, 4);
    Device device = ADSB;

    FlightReport flightReport = FlightReport(time, tailNumber, tcasID,
                                             radarID, geographicCoordinate,
                                             sphericalCoordinate, velocity,
                                             device);

    AdsBReport adsBReport = flightReport.CreateAdsBReport();

    EXPECT_EQ(time, adsBReport.timestamp());
    EXPECT_EQ(geographicCoordinate.GetLatitude(), adsBReport.latitude());
    EXPECT_EQ(geographicCoordinate.GetLongitude(), adsBReport.longitude());
    EXPECT_EQ(geographicCoordinate.GetAltitude(), adsBReport.altitude());
    EXPECT_EQ(tailNumber.Get(), adsBReport.tail_number());
    EXPECT_EQ(velocity.north, adsBReport.north());
    EXPECT_EQ(velocity.down, adsBReport.down());
    EXPECT_EQ(velocity.east, adsBReport.east());
}

/*
 * Tests to see if FlightReport correctly creates radar reports.
 */
TEST(FlightReportMakeRadarReport, Creation) {
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 20,
                                                                     30);
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(15, 25, 35);
    Velocity velocity = Velocity(2, 3, 4);
    Device device = ADSB;

    FlightReport flightReport = FlightReport(time, tailNumber, tcasID,
                                             radarID, geographicCoordinate,
                                             sphericalCoordinate, velocity,
                                             device);

    RadarReport radarReport = flightReport.CreateRadarReport();

    EXPECT_EQ(time, radarReport.timestamp());
    EXPECT_EQ(sphericalCoordinate.GetRange(), radarReport.range());
    EXPECT_EQ(sphericalCoordinate.GetAzimuth(), radarReport.azimuth());
    EXPECT_EQ(sphericalCoordinate.GetElevation(), radarReport.elevation());
    EXPECT_EQ(velocity.north, radarReport.north());
    EXPECT_EQ(velocity.down, radarReport.down());
    EXPECT_EQ(velocity.east, radarReport.east());
    EXPECT_EQ(radarID.Get(), radarReport.id());
    EXPECT_EQ(geographicCoordinate.GetAltitude(), radarReport.altitude());
    EXPECT_EQ(geographicCoordinate.GetLongitude(), radarReport.longitude());
    EXPECT_EQ(geographicCoordinate.GetLatitude(), radarReport.latitude());
}

/*
 * Tests to see if FlightReport correctly creates TCAS reports
 */
TEST(FlightReportMakeTCASReport, Creation) {
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    GeographicCoordinate geographicCoordinate = GeographicCoordinate(10, 20,
                                                                     30);
    SphericalCoordinate sphericalCoordinate = SphericalCoordinate(15, 25, 35);
    Velocity velocity = Velocity(2, 3, 4);
    Device device = ADSB;

    FlightReport flightReport = FlightReport(time, tailNumber, tcasID,
                                             radarID, geographicCoordinate,
                                             sphericalCoordinate, velocity,
                                             device);

    TcasReport tcasReport = flightReport.CreateTcasReport();

    EXPECT_EQ(tcasID.Get(), tcasReport.id());
    EXPECT_EQ(sphericalCoordinate.GetRange(), tcasReport.range());
    EXPECT_EQ(sphericalCoordinate.GetBearing(), tcasReport.bearing());
    EXPECT_EQ(geographicCoordinate.GetAltitude(), tcasReport.altitude());
}