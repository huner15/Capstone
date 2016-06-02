
#include <gtest/gtest.h>
#include <ClusterConverter.h>
#include "CorrelationEngine.h"

TEST(RunAlgorithm, empty) {
    CorrelationEngine engine = CorrelationEngine();
    vector<SurveillanceReport *> radar, tcas, adsb;
    int result;

    result = engine.RunAlgorithm(&adsb, &tcas, &radar);
    EXPECT_EQ(0, result);
    EXPECT_EQ(0, engine.GetClusterSize());
    EXPECT_EQ(0, adsb.size());
    EXPECT_EQ(0, tcas.size());
    EXPECT_EQ(0, radar.size());
}

TEST(RunAlgorithm, oneReport) {
    CorrelationEngine engine = CorrelationEngine();
    vector<SurveillanceReport *> radar, tcas, adsb;
    int result;

    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    SphericalCoordinate spher = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geo = GeographicCoordinate(10, 10, 20);
    SurveillanceReport reportOne;

    reportOne = SurveillanceReport(time, tailNumber,
                                   tcasID, radarID, geo, spher, velocity,
                                   device);
    adsb.push_back(&reportOne);
    result = engine.RunAlgorithm(&adsb, &tcas, &radar);
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, engine.GetClusterSize());
    EXPECT_EQ(1, adsb.size());
    EXPECT_EQ(0, tcas.size());
    EXPECT_EQ(0, radar.size());

    device = TCAS;
    reportOne = SurveillanceReport(time, tailNumber,
                                   tcasID, radarID, geo, spher, velocity,
                                   device);
    tcas.push_back(&reportOne);
    adsb.clear();
    result = engine.RunAlgorithm(&adsb, &tcas, &radar);
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, engine.GetClusterSize());
    EXPECT_EQ(0, adsb.size());
    EXPECT_EQ(1, tcas.size());
    EXPECT_EQ(0, radar.size());

    device = RADAR;
    reportOne = SurveillanceReport(time, tailNumber,
                                   tcasID, radarID, geo, spher, velocity,
                                   device);
    radar.push_back(&reportOne);
    tcas.clear();
    result = engine.RunAlgorithm(&adsb, &tcas, &radar);
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, engine.GetClusterSize());
    EXPECT_EQ(0, adsb.size());
    EXPECT_EQ(0, tcas.size());
    EXPECT_EQ(1, radar.size());
}

TEST(RunAlgorithm, runsFullFunction) {
    CorrelationEngine engine = CorrelationEngine();
    vector<SurveillanceReport *> radar, tcas, adsb;
    int result;

    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    SphericalCoordinate spher = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geo = GeographicCoordinate(10, 10, 20);
    SurveillanceReport reportOne;

    reportOne = SurveillanceReport(time, tailNumber,
                                   tcasID, radarID, geo, spher, velocity, device);
    adsb.push_back(&reportOne);

    device = TCAS;
    reportOne = SurveillanceReport(time, tailNumber,
                                   tcasID, radarID, geo, spher, velocity, device);
    tcas.push_back(&reportOne);

    device = RADAR;
    reportOne = SurveillanceReport(time, tailNumber,
                                   tcasID, radarID, geo, spher, velocity, device);
    radar.push_back(&reportOne);

    result = engine.RunAlgorithm(&adsb, &tcas, &radar);
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, engine.GetClusterSize());
    EXPECT_EQ(1, adsb.size());
    EXPECT_EQ(1, tcas.size());
    EXPECT_EQ(1, radar.size());

    adsb.clear();
    radar.clear();
    tcas.clear();

    //add Surveillance Reports to vectors
    for (int i = 0; i < 3; i++) {
        reportOne = SurveillanceReport(time, tailNumber,
                                       tcasID,
                                       radarID, geo, spher,
                                       velocity, device);
        adsb.push_back(&reportOne);
    }

    device = TCAS;
    for (int i = 0; i < 2; i++) {
        reportOne = SurveillanceReport(time, tailNumber,
                                       tcasID,
                                       radarID, geo, spher,
                                       velocity, device);
        tcas.push_back(&reportOne);
    }

    device = RADAR;
    for (int i = 0; i < 1; i++) {
        reportOne = SurveillanceReport(time, tailNumber,
                                       tcasID,
                                       radarID, geo, spher,
                                       velocity, device);
        radar.push_back(&reportOne);
    }

    result = engine.RunAlgorithm(&adsb, &tcas, &radar);
    EXPECT_EQ(0, result);
    EXPECT_EQ(3, engine.GetClusterSize());
    EXPECT_EQ(3, adsb.size());
    EXPECT_EQ(2, tcas.size());
    EXPECT_EQ(1, radar.size());
}

TEST(Correlate, runsFullFunction) {
    CorrelationEngine engine = CorrelationEngine();
    vector<SurveillanceReport *> radar, tcas, adsb;
    int result;

    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    SphericalCoordinate spher = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geo = GeographicCoordinate(10, 10, 20);
    SurveillanceReport reportOne;

    //add Surveillance Reports to vectors
    for (int i = 0; i < 3; i++) {
        reportOne = SurveillanceReport(time, tailNumber,
                                       tcasID,
                                       radarID, geo, spher,
                                       velocity, device);
        adsb.push_back(&reportOne);
    }

    device = TCAS;
    for (int i = 0; i < 2; i++) {
        reportOne = SurveillanceReport(time, tailNumber,
                                       tcasID,
                                       radarID, geo, spher,
                                       velocity, device);
        tcas.push_back(&reportOne);
    }

    device = RADAR;
    for (int i = 0; i < 1; i++) {
        reportOne = SurveillanceReport(time, tailNumber,
                                       tcasID,
                                       radarID, geo, spher,
                                       velocity, device);
        radar.push_back(&reportOne);
    }

    //Test converted
//    result = engine.Correlate(&adsb, &tcas, &radar, true);
    EXPECT_EQ(3, engine.GetClusterSize());
    EXPECT_EQ(3, adsb.size());
    EXPECT_EQ(2, tcas.size());
    EXPECT_EQ(1, radar.size());

    //Test unconverted
 //   result = engine.Correlate(&adsb, &tcas, &radar, false);
    EXPECT_EQ(3, engine.GetClusterSize());
    EXPECT_EQ(3, adsb.size());
    EXPECT_EQ(2, tcas.size());
    EXPECT_EQ(1, radar.size());
}

TEST(ConvertAircraft, empty) {
    CorrelationEngine engine = CorrelationEngine();
    Cluster *cluster = new Cluster();
    cluster->_adsb = NULL;
    cluster->_radar = NULL;
    cluster->_tcas = NULL;

    CorrelationAircraft *aircraft = engine.ConvertAircraft(cluster);

    ASSERT_TRUE(aircraft == NULL);
}

TEST(ConvertAircraft, oneReport) {
    CorrelationEngine engine = CorrelationEngine();
    Cluster *cluster = new Cluster();
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    SphericalCoordinate spher = SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate geo = GeographicCoordinate(10, 10, 20);
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
        radarID, geo, spher, velocity, device);

    //ADSB
    cluster->_adsb = &reportOne;
    cluster->_radar = NULL;
    cluster->_tcas = NULL;

    CorrelationAircraft *aircraft = engine.ConvertAircraft(cluster);
    ASSERT_FALSE(aircraft == NULL);
    EXPECT_EQ(ADSB, aircraft->GetDeviceType());
    EXPECT_EQ(geo.GetAltitude(), aircraft->GetGeographicCoordinate().GetAltitude());
    EXPECT_EQ(spher.GetRange(), aircraft->GetSphericalCoordinate().GetRange());
    //    EXPECT_EQ(1, aircraft->GetTime());
    EXPECT_EQ(1, aircraft->GetVelocity().North());
    EXPECT_EQ(2, aircraft->GetVelocity().East());
    EXPECT_EQ(3, aircraft->GetVelocity().Down());

    //TCAS
    cluster->_adsb = NULL;
    cluster->_radar = NULL;
    cluster->_tcas = &reportOne;

    aircraft = engine.ConvertAircraft(cluster);
    ASSERT_FALSE(aircraft == NULL);
    EXPECT_EQ(TCAS, aircraft->GetDeviceType());
    EXPECT_EQ(geo.GetAltitude(), aircraft->GetGeographicCoordinate().GetAltitude());
    EXPECT_EQ(spher.GetRange(), aircraft->GetSphericalCoordinate().GetRange());
    //    EXPECT_EQ(1, aircraft->GetTime());
    EXPECT_EQ(1, aircraft->GetVelocity().North());
    EXPECT_EQ(2, aircraft->GetVelocity().East());
    EXPECT_EQ(3, aircraft->GetVelocity().Down());

    //RADAR
    cluster->_adsb = NULL;
    cluster->_radar = &reportOne;
    cluster->_tcas = NULL;

    aircraft = engine.ConvertAircraft(cluster);
    ASSERT_FALSE(aircraft == NULL);
    EXPECT_EQ(RADAR, aircraft->GetDeviceType());
    EXPECT_EQ(geo.GetAltitude(), aircraft->GetGeographicCoordinate().GetAltitude());
    EXPECT_EQ(spher.GetRange(), aircraft->GetSphericalCoordinate().GetRange());
    //    EXPECT_EQ(1, aircraft->GetTime());
    EXPECT_EQ(1.5, aircraft->GetVelocity().North());
    EXPECT_EQ(0.5, aircraft->GetVelocity().East());
    EXPECT_EQ(1, aircraft->GetVelocity().Down());
}

TEST(ConvertAircraft, twoReport) {
    CorrelationEngine engine = CorrelationEngine();
    Cluster *cluster = new Cluster();
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    SphericalCoordinate *spher = NULL;
    Device device = ADSB;
    Velocity velocity = Velocity(1, 2, 3);
    GeographicCoordinate *geo = NULL;
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, *geo, *spher,
                                                      velocity, device);

    spher = new SphericalCoordinate(5, 10, 20);
    device = RADAR;
    geo = new GeographicCoordinate(10, 10, 20);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, *geo, *spher,
                                                      velocity, device);

    //ADSB
    cluster->_adsb = &reportOne;
    cluster->_radar = &reportTwo;
    cluster->_tcas = NULL;

    CorrelationAircraft *aircraft = engine.ConvertAircraft(cluster);
    ASSERT_FALSE(aircraft == NULL);
    EXPECT_EQ(ADSB, aircraft->GetDeviceType());
    EXPECT_EQ(geo->GetAltitude(), aircraft->GetGeographicCoordinate()
            .GetAltitude());
    EXPECT_EQ(spher->GetRange(), aircraft->GetSphericalCoordinate().GetRange());
//    EXPECT_EQ(1, aircraft->GetTime());
    EXPECT_EQ(1, aircraft->GetVelocity().North());
    EXPECT_EQ(2, aircraft->GetVelocity().East());
    EXPECT_EQ(3, aircraft->GetVelocity().Down());

    //TCAS
    device = TCAS;
    reportTwo = SurveillanceReport(time, tailNumber, tcasID,
        radarID, *geo, *spher, velocity, device);

    cluster->_adsb = &reportOne;
    cluster->_radar = NULL;
    cluster->_tcas = &reportTwo;

    aircraft = engine.ConvertAircraft(cluster);
    ASSERT_FALSE(aircraft == NULL);
    EXPECT_EQ(ADSB, aircraft->GetDeviceType());
    EXPECT_EQ(geo->GetAltitude(), aircraft->GetGeographicCoordinate()
            .GetAltitude());
    EXPECT_EQ(spher->GetRange(), aircraft->GetSphericalCoordinate().GetRange());
    //    EXPECT_EQ(1, aircraft->GetTime());
    EXPECT_EQ(1, aircraft->GetVelocity().North());
    EXPECT_EQ(2, aircraft->GetVelocity().East());
    EXPECT_EQ(3, aircraft->GetVelocity().Down());

    //RADAR
    device = RADAR;
    reportOne = SurveillanceReport(time, tailNumber, tcasID,
                                   radarID, *geo, *spher, velocity, device);

    cluster->_adsb = NULL;
    cluster->_radar = &reportOne;
    cluster->_tcas = &reportTwo;

    aircraft = engine.ConvertAircraft(cluster);
    ASSERT_FALSE(aircraft == NULL);
    EXPECT_EQ(TCAS, aircraft->GetDeviceType());
    EXPECT_EQ(geo->GetAltitude(), aircraft->GetGeographicCoordinate()
            .GetAltitude());
    EXPECT_EQ(spher->GetRange(), aircraft->GetSphericalCoordinate().GetRange());
    //    EXPECT_EQ(1, aircraft->GetTime());
    EXPECT_EQ(1, aircraft->GetVelocity().North());
    EXPECT_EQ(2, aircraft->GetVelocity().East());
    EXPECT_EQ(3, aircraft->GetVelocity().Down());
}


TEST(ConvertingClusters, allReportTypes) {
    ClusterConverter converter = ClusterConverter();
    std::vector<Cluster *> *clusters = new vector<Cluster *>();
    Cluster *cluster = new Cluster();
    std::time_t time = 1;
    TailNumber tailNumber = TailNumber();
    TcasID tcasID = TcasID();
    RadarID radarID = RadarID();
    SphericalCoordinate *spher = new SphericalCoordinate(5, 10, 20);
    Device device = ADSB;
    Velocity *velocity = NULL;
    GeographicCoordinate *geo = NULL;
    SurveillanceReport reportOne = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, *geo, *spher,
                                                      *velocity, device);

    device = RADAR;
    geo = new GeographicCoordinate(10, 10, 20);
    SurveillanceReport reportTwo = SurveillanceReport(time, tailNumber, tcasID,
                                                      radarID, *geo, *spher,
                                                      *velocity, device);

    device = TCAS;
    velocity = new Velocity(1, 2, 3);
    SurveillanceReport reportThree = SurveillanceReport(time, tailNumber,
        tcasID, radarID, *geo, *spher, *velocity, device);

    cluster->_adsb = &reportOne;
    cluster->_radar = &reportTwo;
    cluster->_tcas = &reportThree;
    clusters->push_back(cluster);

    cluster = new Cluster();
    cluster->_radar = &reportTwo;
    clusters->push_back(cluster);

    cluster = new Cluster();
    cluster->_adsb = &reportOne;
    clusters->push_back(cluster);

    cluster = new Cluster();
    cluster->_tcas = &reportThree;
    clusters->push_back(cluster);

    vector<CorrelationAircraft *> *aircraft = converter.Convert(clusters);

    ASSERT_FALSE(aircraft == NULL);
    ASSERT_TRUE(aircraft->size() == 4);

    EXPECT_EQ(ADSB, aircraft->at(0)->GetDeviceType());
    EXPECT_EQ(RADAR, aircraft->at(1)->GetDeviceType());
    EXPECT_EQ(ADSB, aircraft->at(2)->GetDeviceType());
    EXPECT_EQ(TCAS, aircraft->at(3)->GetDeviceType());

   // EXPECT_EQ(1, aircraft->at(0)->GetTime());
    EXPECT_EQ(reportTwo.GetAltitude(),
              aircraft->at(1)->GetGeographicCoordinate().GetAltitude());
    EXPECT_EQ(1, reportThree.GetVelocity()->North());
}