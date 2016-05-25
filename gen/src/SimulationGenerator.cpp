/*
 * SimulationGenerator.h
 * Specific Atomics
 * Kevin Pham
 * 2-28-16
 * Driver for creating SimulationFlights File
 */

#include "GenerationMath.h"
#include <iomanip>
#include "SimulationGenerator.h"


SimulationGenerator::SimulationGenerator(std::string file_name) {
    _flight_scenario = FlightScenarioIO::ReadFile(file_name);
    std::vector<FlightLeg> flight_legs =
            _flight_scenario.GetOwnship().GetFlightPlan().GetFlightLegs();

    _num_aircraft = _flight_scenario.GetAircraft().size();
    _ownship_duration = 0;

    for (int i = 0; i < flight_legs.size(); i++) {
        int duration = flight_legs.at(i).GetDurationAfterManeuver() +
                       flight_legs.at(i).GetDurationOfManeuver();
        Velocity vel = flight_legs.at(i).GetNewRelativeVelocity();
        for (int j = 0; j < duration; j++) {
            _ownship_velocities.push_back(vel);
        }
        _ownship_duration += duration;
    }
}

Json::Value SimulationGenerator::FormatOwnshipReport(std::time_t time,
                                                     double altitude,
                                                     double latitude,
                                                     double longitude,
                                                     double north, double east,
                                                     double down, int index) {
    Json::Value own_report;
    own_report["time"] = ctime(&time);
    own_report["altitude"] = altitude;
    own_report["latitude"] = latitude;
    own_report["longitude"] = longitude;
    own_report["north"] = north;
    own_report["east"] = east;
    own_report["down"] = down;
    own_report["index"] = index;
    return own_report;
}

Json::Value SimulationGenerator::FormatAdsbReport(TailNumber tail_number,
                                                  std::time_t time,
                                                  double altitude,
                                                  double latitude,
                                                  double longitude,
                                                  double north, double east,
                                                  double down, int index,
                                                  int aircraft_num) {
    Json::Value adsb_report;
    adsb_report["tailNumber"] = tail_number.Get();
    adsb_report["time"] = ctime(&time);
    adsb_report["altitude"] = altitude;
    adsb_report["latitude"] = latitude;
    adsb_report["longitude"] = longitude;
    adsb_report["north"] = north;
    adsb_report["east"] = east;
    adsb_report["down"] = down;
    adsb_report["index"] = index;
    adsb_report["aircraft number"] = aircraft_num;
    return adsb_report;

}

Json::Value SimulationGenerator::FormatTcasReport(TcasID id, double altitude,
                                                  double bearing,
                                                  double range, int index,
                                                  int aircraft_num) {
    Json::Value tcas_report;
    tcas_report["id"] = id.Get();
    tcas_report["altitude"] = altitude;
    tcas_report["bearing"] = bearing;
    tcas_report["range"] = range;
    tcas_report["index"] = index;
    tcas_report["aircraft number"] = aircraft_num;

    return tcas_report;
}

Json::Value SimulationGenerator::FormatRadarReport(RadarID id, std::time_t time,
                                                   double range, double azimuth,
                                                   double elevation,
                                                   double altitude,
                                                   double latitude,
                                                   double longitude,
                                                   double north, double east,
                                                   double down, int index,
                                                   int aircraft_num) {
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
    radar_report["index"] = index;
    radar_report["aircraft number"] = aircraft_num;
    return radar_report;
}

std::vector<Aircraft> SimulationGenerator::AllAircraftWithTcas() {
    std::vector<Aircraft> aircraft =
            _flight_scenario.GetAircraft();
    std::vector<Aircraft> TcasAircraft;
    for (int i = 0; i < aircraft.size(); i++) {
        if(aircraft.at(i).HasTcas()) {
            TcasAircraft.push_back(aircraft.at(i));
        }
    }

    return TcasAircraft;
}

Json::Value SimulationGenerator::WriteTcasReports() {
    Json::Value reports(Json::arrayValue);
    std::vector<Aircraft> aircraft = AllAircraftWithTcas();

    //Loops through each aircraft in the simulation
    for (int k = 0; k < aircraft.size(); k++) {
        std::vector<FlightLeg> flight_legs =
                aircraft.at(k).GetFlightPlan().GetFlightLegs();
        GeographicCoordinate start_pos =
                aircraft.at(k).GetFlightPlan().GetStartPosition();
        GeographicCoordinate cur_pos = start_pos;
        double cur_bearing = 0.0;
        int time = 0;
        Velocity vel;

        //Loop through each flight leg
        for (int i = 0; i < flight_legs.size(); i++) {
            int duration = flight_legs.at(i).GetDurationAfterManeuver() +
                           flight_legs.at(i).GetDurationOfManeuver();
            vel = flight_legs.at(i).GetNewRelativeVelocity() +
                           _ownship_velocities.at(time);

            //For the length of the flight leg, calculate a report for each second
            for (int j = 0; j < duration; j++) {
                GeographicCoordinate new_pos = GenerationMath::
                DestinationPoint(
                        cur_pos, vel, cur_bearing);
                GeographicCoordinate own_pos = _ownship_positions.at(time);
                double range = GenerationMath::DistanceBetweenTwoCoordinates(
                        new_pos, own_pos);
                range = GenerationMath::FeetToNauticalMiles(range);
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
                                         own_pos.GetAltitude(),
                                         rel_bearing, range, time, k+1));
            }
        }

        //If the duration of the intruder aircraft's maneuvers is less than ownship,
        //make sure it continues in the same direction for the whole sim.
        while(time < _ownship_duration) {
            GeographicCoordinate new_pos = GenerationMath::
            DestinationPoint(
                    cur_pos, vel, cur_bearing);
            GeographicCoordinate own_pos = _ownship_positions.at(time);
            double range = GenerationMath::DistanceBetweenTwoCoordinates(
                    new_pos, own_pos);
            range = GenerationMath::FeetToNauticalMiles(range);
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
                                     own_pos.GetAltitude(),
                                     rel_bearing, range, time, k+1));
        }

    }

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
        double cur_bearing = 0.0;
        int time = 0;
        Velocity vel;

        for (int i = 0; i < flight_legs.size(); i++) {
            int duration = flight_legs.at(i).GetDurationAfterManeuver() +
                           flight_legs.at(i).GetDurationOfManeuver();
            vel = flight_legs.at(i).GetNewRelativeVelocity() +
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

                double elevation = GenerationMath::ToDegrees(atan(
                        (new_pos.GetAltitude() -
                         own_pos.GetAltitude()) / range));

                cur_pos = new_pos;
                time++;
                if (azimuth <= 180.0 && azimuth >= -180.0 &&
                    elevation <= 90.0 && elevation >= -90.0) {
                    reports.append(
                        FormatRadarReport(RadarID(), time, range, azimuth,
                                          elevation, own_pos.GetAltitude(),
                                          own_pos.GetLatitude(),
                                          own_pos.GetLongitude(),
                                          vel.North(), vel.East(), vel.Down(), time,
                                          k+1));
                }
            }
        }
        while(time < _ownship_duration) {
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

            double elevation = GenerationMath::ToDegrees(atan(
                    (new_pos.GetAltitude() -
                     own_pos.GetAltitude()) / range));

            cur_pos = new_pos;
            time++;
            if (azimuth <= 180.0 && azimuth >= -180.0 &&
                elevation <= 90.0 && elevation >= -90.0) {
                reports.append(
                        FormatRadarReport(RadarID(), time, range, azimuth,
                                          elevation, own_pos.GetAltitude(),
                                          own_pos.GetLatitude(),
                                          own_pos.GetLongitude(),
                                          vel.North(), vel.East(), vel.Down(), time,
                                          k + 1));
            }
        }
    }

    return reports;
}

std::vector<Aircraft> SimulationGenerator::AllAircraftWithAdsb() {
    std::vector<Aircraft> aircraft =
            _flight_scenario.GetAircraft();
    std::vector<Aircraft> AdsbAircraft;
    for (int i = 0; i < aircraft.size(); i++) {
        if(aircraft.at(i).HasAdsB()) {
            AdsbAircraft.push_back(aircraft.at(i));
        }
    }

    return AdsbAircraft;
}

Json::Value SimulationGenerator::WriteAdsbReports() {
    Json::Value reports(Json::arrayValue);
    std::vector<Aircraft> aircraft = AllAircraftWithAdsb();

    for (int k = 0; k < aircraft.size(); k++) {
        std::vector<FlightLeg> flight_legs =
                aircraft.at(k).GetFlightPlan().GetFlightLegs();
        GeographicCoordinate start_pos =
                aircraft.at(k).GetFlightPlan().GetStartPosition();
        GeographicCoordinate cur_pos = start_pos;
        double cur_bearing = 0.0;
        int time = 0;
        Velocity vel;
        for (int i = 0; i < flight_legs.size(); i++) {
            int duration = flight_legs.at(i).GetDurationAfterManeuver() +
                           flight_legs.at(i).GetDurationOfManeuver();
            vel = flight_legs.at(i).GetNewRelativeVelocity() +
                    _ownship_velocities.at(time);
            for (int j = 0; j < duration; j++) {
                GeographicCoordinate new_pos = GenerationMath::
                DestinationPoint(
                        cur_pos, vel, cur_bearing);
                cur_bearing = fmod(
                        GenerationMath::AbsoluteBearingBetweenTwoCoordinates(
                                new_pos, cur_pos) + 180.0, 360.0);
                cur_pos = new_pos;
                time++;
                reports.append(
                        FormatAdsbReport(aircraft.at(k).GetTailNumber(), time,
                                         cur_pos.GetAltitude(),
                                         cur_pos.GetLatitude(),
                                         cur_pos.GetLongitude(),
                                         vel.North(), vel.East(),
                                         vel.Down(), time, k + 1));
            }
        }
        while(time < _ownship_duration) {
            GeographicCoordinate new_pos = GenerationMath::
            DestinationPoint(
                    cur_pos, vel, cur_bearing);
            cur_bearing = fmod(
                    GenerationMath::AbsoluteBearingBetweenTwoCoordinates(
                            new_pos, cur_pos) + 180.0, 360.0);
            cur_pos = new_pos;
            time++;
            reports.append(
                    FormatAdsbReport(aircraft.at(k).GetTailNumber(), time,
                                     cur_pos.GetAltitude(),
                                     cur_pos.GetLatitude(),
                                     cur_pos.GetLongitude(),
                                     vel.North(), vel.East(),
                                     vel.Down(), time, k + 1));
        }

    }
    //std::cout << std::defaultfloat << std::setprecision(10) << reports <<
    //std::endl;
    return reports;
}

int SimulationGenerator::GetNumberOfAircraft() {
    return _num_aircraft;
}

Json::Value SimulationGenerator::WriteOwnshipReports() {
    Json::Value file;
    Json::Value reports(Json::arrayValue);
    std::vector<FlightLeg> flight_legs =
            _flight_scenario.GetOwnship().GetFlightPlan().GetFlightLegs();
    GeographicCoordinate start_pos =
            _flight_scenario.GetOwnship().GetFlightPlan().GetStartPosition();
    GeographicCoordinate cur_pos = start_pos;
    double cur_bearing = 0.0;
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
                                               vel.North(), vel.East(),
                                               vel.Down(),
            time));
        }
    }

    return reports;
}

Json::Value SimulationGenerator::WriteReports() {
    Json::Value all_reports;
    all_reports["ownship"] = WriteOwnshipReports();
    all_reports["adsb"] = WriteAdsbReports();
    all_reports["radar"] = WriteRadarReports();
    all_reports["tcas"] = WriteTcasReports();
    all_reports["numAircraft"] = GetNumberOfAircraft();
    return all_reports;
}

