/*
 * @file CategorizerTests.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 5-13-16
 * @brief Ensures the functionality of Categorizer.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Categorizer.h"

class CategorizerTest : public ::testing::Test {
protected:
    CategorizerTest() {
        _categorizer = new Categorizer();

        _correlation_aircraft_0 = new std::vector<CorrelationAircraft *>;
        CorrelationAircraft * _aircraft0 = new CorrelationAircraft(
                0, TailNumber("mytail"), TcasID(1), RadarID(2),
                GeographicCoordinate(3.0, 4.0 , 5.0),
                SphericalCoordinate(6.0, 7.0, 8.0),
                Velocity(9.0, 10.0, 11.0),
                Velocity(12.0, 13.0, 14.0),
                GeographicCoordinate(15.0, 16.0, 17.0),
                ADSB);
        _correlation_aircraft_0->push_back(_aircraft0);
    }

    virtual ~CategorizerTest() {
        delete(_aircraft0);
        delete(_correlation_aircraft_0);
        delete(_categorizer);
    }

    virtual void SetUp() {
        _cdti_report = _categorizer->Categorize(_correlation_aircraft_0);
    }

    virtual void TearDown() {
        delete(_cdti_report);
    }

    Categorizer* _categorizer;
    std::vector<CorrelationAircraft *> *_correlation_aircraft_0;
    CorrelationAircraft *_aircraft0;
    CDTIReport* _cdti_report;
};

/** Verify the output CDTI report has the timestamp field filled. */
TEST_F(CategorizerTest, HasTimeStamp) {
    ASSERT_TRUE(_cdti_report->has_timestamp());
}

/** Verify the output CDTI report has the Ownship field filled. */
TEST_F(CategorizerTest, HasOwnShip) {
    ASSERT_TRUE(_cdti_report->has_ownship());
}

/** Verify the output CDTI report has the Advisory Level field filled. */
TEST_F(CategorizerTest, HasAdvisoryLevel) {
    ASSERT_TRUE(_cdti_report->has_advisorylevel());
}

/** Verify the output CDTI Report has the Advisory Message field filled. */
TEST_F(CategorizerTest, HasAdvisoryMessage) {
    ASSERT_TRUE(_cdti_report->has_advisorymessage());
}

/** Verify the output CDTI Report Ownship has a relative position of (0, 0, 0) -
 * Ownship is the origin of the Sense and Avoid System. */
TEST_F(CategorizerTest, OwnshipPosition) {
    ASSERT_EQ(0.0, _cdti_report->ownship().position().n());
    ASSERT_EQ(0.0, _cdti_report->ownship().position().e());
    ASSERT_EQ(0.0, _cdti_report->ownship().position().d());
}

TEST_F(CategorizerTest, OwnshipVelocity) {
    ASSERT_EQ(0.0, _cdti_report->ownship().velocity().n());
    ASSERT_EQ(0.0, _cdti_report->ownship().velocity().e());
    ASSERT_EQ(0.0, _cdti_report->ownship().velocity().d());
}

/** TODO: Continue writing value based tests for CDTI Report timestamp,
 * Ownship value, Advisory Level, Advisory Message, and CDTI Plane
 * Advisory Levels. */
