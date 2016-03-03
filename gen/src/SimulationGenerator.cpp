/*
 * SimulationGenerator.h
 * Specific Atomics
 * Kevin Pham
 * 2-28-16
 * Driver for creating SimulationFlights File
 */

#include <GenerationMath.h>
#include <iomanip>
#include "SimulationGenerator.h"


SimulationGenerator::SimulationGenerator(std::string file_name) {
    _flight_scenario = FlightScenarioIO::ReadFile(file_name);
    std::vector<FlightLeg> flight_legs =
            _flight_scenario.GetOwnship().GetFlightPlan().GetFlightLegs();

    for (int i = 0; i < flight_legs.size(); i++) {
        int duration = flight_legs.at(i).GetDurationAfterManeuver() +
                       flight_legs.at(i).GetDurationOfManeuver();
        Velocity vel = flight_legs.at(i).GetNewRelativeVelocity();
        for (int j = 0; j < duration; j++) {
            _ownship_velocities.push_back(vel);
        }
    }
}

Json::Value SimulationGenerator::FormatOwnshipReport(std::time_t time,
                                                     double altitude,
                                                     double latitude,
                                                     double longitude,
                                                     double north, double east,
                                                     double down) {
    Json::Value own_report;
    own_report["time"] = ctime(&time);
    own_report["altitude"] = altitude;
    own_report["latitude"] = latitude;
    own_report["longitude"] = longitude;
    own_report["north"] = north;
    own_report["east"] = east;
    own_report["down"] = down;
    return own_report;
}

Json::Value SimulationGenerator::FormatAdsbReport(TailNumber tail_number,
                                                  std::time_t time,
                                                  double altitude,
                                                  double latitude,
                                                  double longitude,
                                                  double north, double east,
                                                  double down) {
    Json::Value adsb_report;
    adsb_report["tailNumber"] = tail_number.Get();
    adsb_report["time"] = ctime(&time);
    adsb_report["altitude"] = altitude;
    adsb_report["latitude"] = latitude;
    adsb_report["longitude"] = longitude;
    adsb_report["north"] = north;
    adsb_report["east"] = east;
    adsb_report["down"] = down;
    return adsb_report;

}

Json::Value SimulationGenerator::FormatTcasReport(TcasID id, double altitude,
                                                  double bearing,
                                                  double range) {
    Json::Value tcas_report;
    tcas_report["id"] = id.Get();
    tcas_report["altitude"] = altitude;
    tcas_report["bearing"] = bearing;
    tcas_report["range"] = range;

    return tcas_report;
}

Json::Value SimulationGenerator::FormatRadarReport(RadarID id, std::time_t time,
                                                   double range, double azimuth,
                                                   double elevation,
                                                   double altitude,
                                                   double latitude,
                                                   double longitude,
                                                   double north, double east,
                                                   double down) {
    Json::Value radar_report;
    radar_report["id"] = id.Get();
    radar_report["time"] = ctime(&time);
    radar_report["range"] = range;
    radar_report["azimuth"] = azimuth;
    radar_report["elevation"] = elevation;
    radar_report["altitude"] = altitude;
    radar_report["latitude"] = latitude;
    radar_report["longitude"] = longitude;
    radar_report["north"] = north;
    radar_report["east"] = east;
    radar_report["down"] = down;
    return radar_report;
}

Json::Value SimulationGenerator::WriteTcasReports() {
    Json::Value reports(Json::arrayValue);
    std::vector<Aircraft> aircraft =
            _flight_scenario.GetAircraft();

    for (int k = 0; k < aircraft.size(); k++) {
        std::vector<FlightLeg> flight_legs =
                aircraft.at(k).GetFlightPlan().GetFlightLegs();
        GeographicCoordinate start_pos =
                aircraft.at(k).GetFlightPlan().GetStartPosition();
        GeographicCoordinate cur_pos = start_pos;
        double cur_bearing = 36.0;
        int time = 0;
        for (int i = 0; i < flight_legs.size(); i++) {
            int duration = flight_legs.at(i).GetDurationAfterManeuver() +
                           flight_legs.at(i).GetDurationOfManeuver();
            Velocity vel = flight_legs.at(i).GetNewRelativeVelocity() +
                           _ownship_velocities.at(time);
            for (int j = 0; j < duration; j++) {
                GeographicCoordinate new_pos = GenerationMath::
                DestinationPoint(
                        cur_pos, vel, cur_bearing);
                GeographicCoordinate own_pos = _ownship_positions.at(time);
                double range = GenerationMath::DistanceBetweenTwoCoordinates(
                        new_pos, own_pos);
                cur_bearing = fmod(
                        GenerationMath::AbsoluteBearingBetweenTwoCoordinates(
                                new_pos, cur_pos) + 180.0, 360.0);
                double rel_bearing = cur_bearing - _ownship_bearings.at(time);
                //std::cout << "New bearing: " << cur_bearing << std::endl;
                cur_pos = new_pos;
                time++;
                reports.append(
                        FormatTcasReport(TcasID(),
                                         cur_pos.GetAltitude() -
                                         own_pos.GetLatitude(),
                                         rel_bearing, range));
            }
        }

    }
    //std::cout << std::defaultfloat << std::setprecision(10) << reports <<
    //std::endl;
    return reports;
}

Json::Value SimulationGenerator::WriteRadarReports() {
    Json::Value reports(Json::arrayValue);
    std::vector<Aircraft> aircraft =
            _flight_scenario.GetAircraft();

    for (int k = 0; k < aircraft.size(); k++) {
        std::vector<FlightLeg> flight_legs =
                aircraft.at(k).GetFlightPlan().GetFlightLegs();
        GeographicCoordinate start_pos =
                aircraft.at(k).GetFlightPlan().GetStartPosition();
        GeographicCoordinate cur_pos = start_pos;
        double cur_bearing = 36.0;
        int time = 0;
        for (int i = 0; i < flight_legs.size(); i++) {
            int duration = flight_legs.at(i).GetDurationAfterManeuver() +
                           flight_legs.at(i).GetDurationOfManeuver();
            Velocity vel = flight_legs.at(i).GetNewRelativeVelocity() +
                           _ownship_velocities.at(time);
            for (int j = 0; j < duration; j++) {
                GeographicCoordinate new_pos = GenerationMath::
                DestinationPoint(
                        cur_pos, vel, cur_bearing);
                GeographicCoordinate own_pos = _ownship_positions.at(time);
                double range = GenerationMath::DistanceBetweenTwoCoordinates(
                        new_pos, own_pos);

                cur_bearing = fmod(
                        GenerationMath::AbsoluteBearingBetweenTwoCoordinates(
                                new_pos, cur_pos) + 180.0, 360.0);

                double azimuth =
                        GenerationMath::AbsoluteBearingBetweenTwoCoordinates(
                                own_pos, new_pos)
                        - _ownship_bearings.at(time);

                double elevation = atan(
                        (new_pos.GetAltitude() -
                         own_pos.GetAltitude()) / range);

                //std::cout << "New bearing: " << cur_bearing << std::endl;
                cur_pos = new_pos;
                time++;
                reports.append(
                        FormatRadarReport(RadarID(), time, range, azimuth,
                                          elevation, own_pos.GetAltitude(),
                                          own_pos.GetLatitude(),
                                          own_pos.GetLongitude(),
                                          vel.north, vel.east, vel.down));
            }
        }

    }
    //std::cout << std::defaultfloat << std::setprecision(10) << reports <<
    //std::endl;
    return reports;
}


Json::Value SimulationGenerator::WriteAdsbReports() {
    Json::Value reports(Json::arrayValue);
    std::vector<Aircraft> aircraft =
            _flight_scenario.GetAircraft();

    for (int k = 0; k < aircraft.size(); k++) {
        std::vector<FlightLeg> flight_legs =
                aircraft.at(k).GetFlightPlan().GetFlightLegs();
        GeographicCoordinate start_pos =
                aircraft.at(k).GetFlightPlan().GetStartPosition();
        GeographicCoordinate cur_pos = start_pos;
        double cur_bearing = 36.0;
        int time = 0;
        for (int i = 0; i < flight_legs.size(); i++) {
            int duration = flight_legs.at(i).GetDurationAfterManeuver() +
                           flight_legs.at(i).GetDurationOfManeuver();
            Velocity vel = flight_legs.at(i).GetNewRelativeVelocity() -
                           _ownship_velocities.at(time);
            for (int j = 0; j < duration; j++) {
                GeographicCoordinate new_pos = GenerationMath::
                DestinationPoint(
                        cur_pos, vel, cur_bearing);
                cur_bearing = fmod(
                        GenerationMath::AbsoluteBearingBetweenTwoCoordinates(
                                new_pos, cur_pos) + 180.0, 360.0);
                //std::cout << "New bearing: " << cur_bearing << std::endl;
                cur_pos = new_pos;
                time++;
                reports.append(
                        FormatAdsbReport(aircraft.at(k).GetTailNumber(), time,
                                         cur_pos.GetAltitude(),
                                         cur_pos.GetLatitude(),
                                         cur_pos.GetLongitude(),
                                         vel.north, vel.east,
                                         vel.down));
            }
        }

    }
    //std::cout << std::defaultfloat << std::setprecision(10) << reports <<
    //std::endl;
    return reports;
}


Json::Value SimulationGenerator::WriteOwnshipReports() {
    Json::Value file;
    Json::Value reports(Json::arrayValue);
    std::vector<FlightLeg> flight_legs =
            _flight_scenario.GetOwnship().GetFlightPlan().GetFlightLegs();
    GeographicCoordinate start_pos =
            _flight_scenario.GetOwnship().GetFlightPlan().GetStartPosition();
    GeographicCoordinate cur_pos = start_pos;
    double cur_bearing = 36.0;
    int time = 0;
    for (int i = 0; i < flight_legs.size(); i++) {
        int duration = flight_legs.at(i).GetDurationAfterManeuver() +
                       flight_legs.at(i).GetDurationOfManeuver();
        Velocity vel = flight_legs.at(i).GetNewRelativeVelocity();
        for (int j = 0; j < duration; j++) {
            GeographicCoordinate new_pos = GenerationMath::DestinationPoint(
                    cur_pos, vel, cur_bearing);
            cur_bearing = fmod(
                    GenerationMath::AbsoluteBearingBetweenTwoCoordinates(
                            new_pos, cur_pos) + 180.0, 360.0);
            _ownship_bearings.push_back(cur_bearing);
            _ownship_positions.push_back(new_pos);
            //std::cout << "New bearing: " << cur_bearing << std::endl;
            cur_pos = new_pos;
            time++;
            reports.append(FormatOwnshipReport(time, cur_pos.GetAltitude(),
                                               cur_pos.GetLatitude(),
                                               cur_pos.GetLongitude(),
                                               vel.north, vel.east, vel.down));
        }
    }


    std::cout << std::defaultfloat << std::setprecision(10) << reports <<
    std::endl;
    return reports;
}

