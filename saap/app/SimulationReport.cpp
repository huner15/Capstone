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
    adsb_reports_ = SimulationFlightsIO::GetAllADSBReports();
    adsb_it_ = adsb_reports_.begin();
    own_reports_ = SimulationFlightsIO::GetALlOwnshipReports();
    own_it_ = own_reports_.begin();
    radar_reports_ = SimulationFlightsIO::GetAllRadarReports();
    radar_it_ = radar_reports_.begin();
    tcas_reports_ = SimulationFlightsIO::GetAllTCASReports();
    tcas_it_ = tcas_reports_.begin();
}

OwnshipReport SimulationReport::GetNextOwnshipReport() {
    Json::Value report = *own_it_;
    OwnshipReport own;
    own.set_timestamp(report["time"].asInt());
    own.set_ownship_latitude(report["latitude"].asFloat());
    own.set_ownship_longitude(report["longitude"].asFloat());
    own.set_ownship_altitude(report["altitude"].asFloat());
    own.set_north(report["north"].asFloat());
    own.set_east(report["east"].asFloat());
    own.set_down(report["down"].asFloat());

    own_it_++;

    return own;

}

bool SimulationReport::HasNextOwnshipReport() {
    return own_it_ < adsb_reports_.end();
}


bool SimulationReport::HasNextTcasReport() {
    return tcas_it_ < tcas_reports_.end();
}

bool SimulationReport::HasNextRadarReport() {
    return radar_it_ < radar_reports_.end();
}

bool SimulationReport::HasNextAdsbReport() {
    return adsb_it_ < adsb_reports_.end();
}

TcasReport SimulationReport::GetNextTcasReport() {
    Json::Value report = *tcas_it_;
    TcasReport tcas;

    tcas.set_id(report["id"].asInt());
    tcas.set_range(report["range"].asInt());
    tcas.set_altitude(report["altitude"].asInt());
    tcas.set_bearing(report["bearing"].asInt());

    tcas_it_++;

    return tcas;
}

RadarReport SimulationReport::GetNextRadarReport() {
    Json::Value report = *radar_it_;
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

    radar_it_++;

    return radar;
}

AdsBReport SimulationReport::GetNextAdsbReport() {
    Json::Value report = *adsb_it_;
    AdsBReport adsb;
    adsb.set_timestamp(report["time"].asInt());
    adsb.set_latitude(report["latitude"].asFloat());
    adsb.set_longitude(report["longitude"].asFloat());
    adsb.set_altitude(report["altitude"].asFloat());
    adsb.set_tail_number(report["tailNo"].asString());
    adsb.set_north(report["north"].asFloat());
    adsb.set_east(report["east"].asFloat());
    adsb.set_down(report["down"].asFloat());


    adsb_it_++;

    return adsb;

}



