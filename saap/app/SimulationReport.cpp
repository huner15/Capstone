//
// Created by kevin on 1/20/16.
//


#include <tcas.pb.h>
#include <ownship.pb.h>
#include <radar.pb.h>
#include <adsb.pb.h>
#include "SimulationFlightsIO.h"
#include "SimulationReport.h"

using namespace std;

SimulationReport::SimulationReport() {
    adsbReports = SimulationFlightsIO::getAllADSBReports();
    adsbIt = adsbReports.begin();
    ownReports = SimulationFlightsIO::getALlOwnshipReports();
    ownIt = ownReports.begin();
    radarReports = SimulationFlightsIO::getAllRadarReports();
    radarIt = radarReports.begin();
    tcasReports = SimulationFlightsIO::getAllTCASReports();
    tcasIt = tcasReports.begin();
}

OwnshipReport SimulationReport::getNextOwnshipReport() {
    Json::Value report = *ownIt;
    OwnshipReport own;
    own.set_timestamp(report["time"].asInt());
    own.set_ownship_latitude(report["latitude"].asFloat());
    own.set_ownship_longitude(report["longitude"].asFloat());
    own.set_ownship_altitude(report["altitude"].asFloat());
    own.set_north(report["north"].asFloat());
    own.set_east(report["east"].asFloat());
    own.set_down(report["down"].asFloat());

    ownIt++;

    return own;

}

bool SimulationReport::hasNextOwnshipReport() {
    return ownIt < adsbReports.end();
}


bool SimulationReport::hasNextTcasReport() {
    return tcasIt < tcasReports.end();
}

bool SimulationReport::hasNextRadarReport() {
    return radarIt < radarReports.end();
}
bool SimulationReport::hasNextAdsbReport() {
    return adsbIt < adsbReports.end();
}

TcasReport SimulationReport::getNextTcasReport() {
    Json::Value report = *tcasIt;
    TcasReport tcas;

    tcas.set_id(report["id"].asInt());
    tcas.set_range(report["range"].asInt());
    tcas.set_altitude(report["altitude"].asInt());
    tcas.set_bearing(report["bearing"].asInt());

    tcasIt++;

    return tcas;
}

RadarReport SimulationReport::getNextRadarReport() {
    Json::Value report = *radarIt;
    RadarReport radar;
    radar.set_timestamp(report["time"].asInt());
    radar.set_range(report["range"].asFloat());
    radar.set_azimuth(report["azimuth"].asFloat());
    radar.set_elevation(report["elevation"].asFloat());
    radar.set_id(report["id"].asInt());
    radar.set_north(report["north"].asFloat());
    radar.set_east(report["east"].asFloat());
    radar.set_down(report["down"].asFloat());
    radar.set_latitude(report["latitude"].asFloat());
    radar.set_longitude(report["longitude"].asFloat());
    radar.set_altitude(report["altitude"].asFloat());

    radarIt++;

    return radar;
}

AdsBReport SimulationReport::getNextAdsbReport() {
    Json::Value report = *adsbIt;
    AdsBReport adsb;
    adsb.set_timestamp(report["time"].asInt());
    adsb.set_latitude(report["latitude"].asFloat());
    adsb.set_longitude(report["longitude"].asFloat());
    adsb.set_altitude(report["altitude"].asFloat());
    adsb.set_tail_number(report["tailNo"].asString());
    adsb.set_north(report["north"].asFloat());
    adsb.set_east(report["east"].asFloat());
    adsb.set_down(report["down"].asFloat());


    adsbIt++;

    return adsb;

}



