
#include <gtest/gtest.h>
#include "CorrelationEngine.h"

TEST(NewCluster, simpleAllocate) {
    CorrelationEngine engine = CorrelationEngine();

    Cluster *result = engine.NewCluster();
    ASSERT_FALSE(result == NULL);
    EXPECT_EQ(NULL, result->_adsb);
    EXPECT_EQ(NULL, result->_tcas);
    EXPECT_EQ(NULL, result->_radar);

    //change cluster values
    result->_adsb = new SurveillanceReport();
    result->_tcas = new SurveillanceReport();
    result->_radar = new SurveillanceReport();
//
//    //add to free list
//    engine.AddFreeCluster(0);
//
    result = engine.NewCluster();
    ASSERT_FALSE(result == NULL);
    EXPECT_EQ(NULL, result->_adsb);
    EXPECT_EQ(NULL, result->_tcas);
    EXPECT_EQ(NULL, result->_radar);
}

TEST(NewCluster, stressTest) {
    CorrelationEngine engine = CorrelationEngine();
    Cluster *result = NULL, *keptOne = NULL, *keptTwo = NULL;
    int max = 80; //max number of Surveillance Reports in one second
    int keptIndexOne = 30, keptIndexTwo = max;

    //allocate new clusters
    for (int index = 0; index <= max; index++) {
        if (index == keptIndexOne) {
            keptOne = engine.NewCluster();
        }
        else if (index == keptIndexTwo) {
            keptTwo = engine.NewCluster();
        }
        else {
            result = engine.NewCluster();
        }
    }

    //check kept clusters
    ASSERT_FALSE(keptOne == NULL);
    EXPECT_EQ(NULL, keptOne->_adsb);
    EXPECT_EQ(NULL, keptOne->_tcas);
    EXPECT_EQ(NULL, keptOne->_radar);
    ASSERT_FALSE(keptTwo == NULL);
    EXPECT_EQ(NULL, keptTwo->_adsb);
    EXPECT_EQ(NULL, keptTwo->_tcas);
    EXPECT_EQ(NULL, keptTwo->_radar);

    //change kept clusters' variables
    keptOne->_adsb = new SurveillanceReport();
    keptOne->_tcas = new SurveillanceReport();
    keptOne->_radar = new SurveillanceReport();
    keptTwo->_radar = new SurveillanceReport();

    //check kept clusters
    ASSERT_FALSE(keptOne == NULL);
    ASSERT_FALSE(keptOne->_adsb == NULL);
    ASSERT_FALSE(keptOne->_radar == NULL);
    ASSERT_FALSE(keptOne->_tcas == NULL);
    ASSERT_FALSE(keptTwo == NULL);
    EXPECT_EQ(NULL, keptTwo->_adsb);
    EXPECT_EQ(NULL, keptTwo->_tcas);
    ASSERT_FALSE(keptTwo->_radar == NULL);

//    //add clusters to free list
//    for (int index = 0; index <= max; index++) {
//        if (index != keptIndexOne && index != keptIndexTwo) {
//            engine.AddFreeCluster(index);
//        }
//    }

    //Reaccess freed list clusters
    for (int index = 0; index < (max - 1); index++) {
        result = engine.NewCluster();
    }

    //check last cluster from freed list
    ASSERT_FALSE(result == NULL);
    EXPECT_EQ(NULL, result->_adsb);
    EXPECT_EQ(NULL, result->_tcas);
    EXPECT_EQ(NULL, result->_radar);

    //check newly allocated (not from free list)
    result = engine.NewCluster();
    ASSERT_FALSE(result == NULL);
    EXPECT_EQ(NULL, result->_adsb);
    EXPECT_EQ(NULL, result->_tcas);
    EXPECT_EQ(NULL, result->_radar);

    //Recheck kept cluster values
    ASSERT_FALSE(keptOne == NULL);
    ASSERT_FALSE(keptOne->_adsb == NULL);
    ASSERT_FALSE(keptOne->_radar == NULL);
    ASSERT_FALSE(keptOne->_tcas == NULL);
    ASSERT_FALSE(keptTwo == NULL);
    EXPECT_EQ(NULL, keptTwo->_adsb);
    EXPECT_EQ(NULL, keptTwo->_tcas);
    ASSERT_FALSE(keptTwo->_radar == NULL);
}

TEST(NewCorrelationAircraft, simpleAllocate) {
    CorrelationEngine engine = CorrelationEngine();

    CorrelationAircraft *result = engine.NewCorrAircraft();
    ASSERT_FALSE(result == NULL);

    //change cluster values
    result->SetType(ADSB);

    //add to free list
    engine.AddFreeAircraft(0);

    result = engine.NewCorrAircraft();
    ASSERT_FALSE(result == NULL);
    EXPECT_EQ(ADSB, result->GetDeviceType());
}

TEST(NewCorrelationAircraft, stressTest) {
    CorrelationEngine engine = CorrelationEngine();
    CorrelationAircraft *result = NULL, *keptOne = NULL, *keptTwo = NULL;
    int max = 80; //max number of Surveillance Reports in one second
    int keptIndexOne = 30, keptIndexTwo = max;

    //allocate new clusters
    for (int index = 0; index <= max; index++) {
        if (index == keptIndexOne) {
            keptOne = engine.NewCorrAircraft();
        }
        else if (index == keptIndexTwo) {
            keptTwo = engine.NewCorrAircraft();
        }
        else {
            result = engine.NewCorrAircraft();
        }
    }

    //check kept clusters
    ASSERT_FALSE(keptOne == NULL);
    EXPECT_EQ(NULL, keptOne->GetDeviceType());
    ASSERT_FALSE(keptTwo == NULL);
    EXPECT_EQ(NULL, keptTwo->GetDeviceType());

    //change kept clusters' variables
    keptOne->SetType(ADSB);
    keptTwo->SetType(RADAR);

    //check kept clusters
    ASSERT_FALSE(keptOne == NULL);
    EXPECT_EQ(ADSB, keptOne->GetDeviceType());
    ASSERT_FALSE(keptTwo == NULL);
    EXPECT_EQ(RADAR, keptTwo->GetDeviceType());

    //add clusters to free list
    for (int index = 0; index <= max; index++) {
        if (index != keptIndexOne && index != keptIndexTwo) {
            engine.AddFreeAircraft(index);
        }
    }

    //Reaccess freed list clusters
    for (int index = 0; index < (max - 1); index++) {
        result = engine.NewCorrAircraft();
    }

    //check last cluster from freed list
    ASSERT_FALSE(result == NULL);

    //check newly allocated (not from free list)
    result = engine.NewCorrAircraft();
    ASSERT_FALSE(result == NULL);

    //Recheck kept cluster values
    ASSERT_FALSE(keptOne == NULL);
    EXPECT_EQ(ADSB, keptOne->GetDeviceType());
    ASSERT_FALSE(keptTwo == NULL);
    EXPECT_EQ(RADAR, keptTwo->GetDeviceType());
}
