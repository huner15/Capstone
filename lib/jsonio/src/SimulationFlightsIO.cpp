//
// Created by KEVIN on 11/27/2015.
//

#include <FlightSimulation.h>
#include "SimulationFlightsIO.h"

using namespace std;

Json::Value SimulationFlightsIO::OpenFile(std::string file_name) {
    Json::Value root;   // will contain the root value after parsing.
    Json::Reader reader;
    //std:string file_dir = "../../lib/jsonio/test/";
    std::string file_dir = "";
    std::string file = file_dir + file_name;
    std::ifstream test(file, std::ifstream::binary);
    bool parsing_successful = reader.parse(test, root, false);

    if (!parsing_successful) {
        // report to the user the failure and their locations in the document.
        std::cout << reader.getFormattedErrorMessages()
        << "\n";
        return Json::nullValue;
    }
    else {
        return root;
    }
}

FlightSimulation SimulationFlightsIO::ReadFile(std::string file_name) {
    return ReadFlightData(file_name);
}

AdsBReport SimulationFlightsIO::SetAdsBReportData(std::time_t time,
                                                  double latitude,
                                                  double longitude,
                                                  double altitude,
                                                  std::string tail_number,
                                                  double north, double east,
                                                  double down) {
    AdsBReport adsBReport;

    adsBReport.set_timestamp(time);
    adsBReport.set_latitude(latitude);
    adsBReport.set_longitude(longitude);
    adsBReport.set_altitude(altitude);
    adsBReport.set_tail_number(tail_number);
    adsBReport.set_north(north);
    adsBReport.set_east(east);
    adsBReport.set_down(down);

    return adsBReport;
}

OwnshipReport SimulationFlightsIO::SetOwnshipReportData(std::time_t time,
                                                        double latitude,
                                                        double longitude,
                                                        double altitude,
                                                        double north,
                                                        double east,
                                                        double down) {
    OwnshipReport ownshipReport;

    ownshipReport.set_timestamp(time);
    ownshipReport.set_ownship_latitude(latitude);
    ownshipReport.set_ownship_longitude(longitude);
    ownshipReport.set_ownship_altitude(altitude);
    ownshipReport.set_north(north);
    ownshipReport.set_east(east);
    ownshipReport.set_down(down);

    return ownshipReport;
}

RadarReport SimulationFlightsIO::SetRadarReportData(std::time_t time,
                                                    double range,
                                                    double azimuth,
                                                    double elevation,
                                                    uint16_t radar_id,
                                                    double latitude,
                                                    double longitude,
                                                    double altitude,
                                                    double north, double east,
                                                    double down) {
    RadarReport radarReport;

    radarReport.set_timestamp(time);
    radarReport.set_range(range);
    radarReport.set_azimuth(azimuth);
    radarReport.set_elevation(elevation);
    radarReport.set_id(radar_id);
    radarReport.set_north(north);
    radarReport.set_east(east);
    radarReport.set_down(down);
    radarReport.set_latitude(latitude);
    radarReport.set_longitude(longitude);
    radarReport.set_altitude(altitude);

    return radarReport;
}

TcasReport SimulationFlightsIO::SetTcasReportData(uint8_t tcas_id, double range,
                                                  double altitude,
                                                  double bearing) {
    TcasReport tcasReport;

    tcasReport.set_id(tcas_id);
    tcasReport.set_range(range);
    tcasReport.set_altitude(altitude);
    tcasReport.set_bearing(bearing);

    return tcasReport;
}


//TODO: Fix Time
FlightSimulation SimulationFlightsIO::ReadFlightData(std::string file_name) {
    Json::Value json_reports = GetReports(file_name);
    std::vector<Flight> all_flights;

    Json::Value adsb_reports = json_reports["adsb"];
    Json::Value tcas_reports = json_reports["tcas"];
    Json::Value radar_reports = json_reports["radar"];
    Json::Value ownship_reports = json_reports["ownship"];

    //std::cout << json_reports << std::endl;
    //std::cout << "number of aircrafts: " << json_reports["numAircraft"] << std::endl;
    for (int i = 1; i <= json_reports["numAircraft"].asInt(); i++) {
        //std::cout << "GETS HERE" << std::endl;
        std::vector<FlightReport> all_flight_reports;
        for (int j = 1; j <= ownship_reports.size(); j++) {
            AdsBReport adsb_report;
            TcasReport tcas_report;
            RadarReport radar_report;
            OwnshipReport ownship_report;
            //std::cout << "GETS HERE2" << std::endl;
            for (int adsb_idx = 0; adsb_idx < adsb_reports.size(); adsb_idx++) {
                //std::cout << "GETS HERE3" << std::endl;

                if (adsb_reports[adsb_idx]["aircraft number"].asInt() == i &&
                    adsb_reports[adsb_idx]["index"].asInt() == j) {
                    std::time_t time = adsb_idx;
                    double latitude = adsb_reports[adsb_idx]["latitude"].asDouble();
                    double longitude = adsb_reports[adsb_idx]["longitude"].asDouble();
                    double altitude = adsb_reports[adsb_idx]["altitude"].asDouble();
                    std::string tail_number = adsb_reports[adsb_idx]["tailNumber"].asString();
                    double north = adsb_reports[adsb_idx]["north"].asDouble();
                    double east = adsb_reports[adsb_idx]["east"].asDouble();
                    double down = adsb_reports[adsb_idx]["down"].asDouble();
                    adsb_report = SetAdsBReportData(time, latitude, longitude,
                                                    altitude, tail_number,
                                                    north, east, down);
                }
            }
            for (int radar_idx = 0;
                 radar_idx < radar_reports.size(); radar_idx++) {
                //std::cout << "radar_idx: " << radar_idx << "size: " << radar_reports.size() << std::endl;
                if (radar_reports[radar_idx]["aircraft number"].asInt() == i &&
                    radar_reports[radar_idx]["index"].asInt() == j) {
                    std::time_t time = radar_idx;
                    double range = radar_reports[radar_idx]["range"].asDouble();
                    double azimuth = radar_reports[radar_idx]["azimuth"].asDouble();
                    double elevation = radar_reports[radar_idx]["elevation"].asDouble();
                    uint16_t radar_id = radar_reports[radar_idx]["id"].asUInt();
                    double latitude = radar_reports[radar_idx]["latitude"].asDouble();
                    double longitude = radar_reports[radar_idx]["longitude"].asDouble();
                    double altitude = radar_reports[radar_idx]["altitude"].asDouble();
                    double north = radar_reports[radar_idx]["north"].asDouble();
                    double east = radar_reports[radar_idx]["east"].asDouble();
                    double down = radar_reports[radar_idx]["down"].asDouble();
                    radar_report = SetRadarReportData(time, range, azimuth,
                                                      elevation, radar_id,
                                                      latitude, longitude,
                                                      altitude, north, east,
                                                      down);
                }

            }

            for (int tcas_idx = 0;
                 tcas_idx < tcas_reports.size(); tcas_idx++) {
                if (tcas_reports[tcas_idx]["aircraft number"].asInt() == i &&
                    tcas_reports[tcas_idx]["index"].asInt() == j) {
                    uint8_t tcas_id = tcas_reports[tcas_idx]["id"].asUInt();
                    double range = tcas_reports[tcas_idx]["range"].asDouble();
                    double altitude = tcas_reports[tcas_idx]["altitude"].asDouble();
                    double bearing = tcas_reports[tcas_idx]["bearing"].asDouble();
                    tcas_report = SetTcasReportData(tcas_id, range, altitude,
                                                    bearing);
                }
            }
            std::time_t time = j;
            double latitude = ownship_reports[j - 1]["latitude"].asDouble();
            double longitude = ownship_reports[j - 1]["longitude"].asDouble();
            double altitude = ownship_reports[j - 1]["altitude"].asDouble();
            double north = ownship_reports[j - 1]["north"].asDouble();
            double east = ownship_reports[j - 1]["east"].asDouble();
            double down = ownship_reports[j - 1]["down"].asDouble();
            ownship_report = SetOwnshipReportData(time, latitude, longitude,
                                                  altitude, north, east, down);

            FlightReport flight_report (adsb_report, radar_report, tcas_report, ownship_report);
            all_flight_reports.push_back(flight_report);
        }
        Flight flight(all_flight_reports);
        all_flights.push_back(flight);


    }

    FlightSimulation flight_simulation(all_flights);

    return flight_simulation;
}

Json::Value SimulationFlightsIO::GetReports(std::string file_name) {
    Json::Value root = OpenFile(file_name);

    return root;
}


Json::Value SimulationFlightsIO::GetSimulationFlights() {
    return Json::nullValue;
}


void SimulationFlightsIO::writeFile(Json::Value value) {
    std::ofstream file_id;
    file_id.open("SimulationFlightOutput", fstream::out);

    Json::Value output;
    //output["value"] = root["val1"].asInt() + root["val2"].asInt();

    Json::Value vec(Json::arrayValue);
    vec.append(Json::Value(1));
    vec.append(Json::Value("ROME"));
    vec.append(Json::Value(true));

    output["array"] = vec;
    //root["output"] = output;

    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(value);

    file_id.close();
}