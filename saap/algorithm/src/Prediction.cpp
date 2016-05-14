/**
* @file Prediction.cpp
* @author Specific Atomics
* @author Dat Tran
* @date 1-19-16
* @brief Tracks the last three Snapshot seconds of CorrelationAircraft in the History.
*/

#include "Velocity.h"
#include "Prediction.h"
#include "CorrelationAircraft.h"

Prediction::Prediction() {

}

Prediction::~Prediction() {

}

int Prediction::AddAircraft(CorrelationAircraft *aircraft) {
    int status = 0;

    if (aircraft == NULL) {
        status = 1;
    } else {
        // Empty Snapshot
        if (_current_snapshot->GetAircraft()->empty()) {
            std::vector<CorrelationAircraft> aircraft_list;
            aircraft_list.push_back(*aircraft);
            *_current_snapshot = Snapshot(&aircraft_list, aircraft->GetTime()); // gets first aircraft's timestamp
        } else {
            _current_snapshot->GetAircraft()->push_back(*aircraft);
        }
    }

    return status;
}

void Prediction::TakeSnapshot() {
    _history->AddSnapshot(_current_snapshot);
    _current_snapshot->GetAircraft()->clear();
    _snapshot_counter++;
}

CorrelationAircraft Prediction::SearchTailNum(TailNumber tail_number) {
    CorrelationAircraft aircraft;

    std::vector<CorrelationAircraft> *last = _history->GetLast()->GetAircraft();
    std::vector<CorrelationAircraft> *second_to_last = _history->GetSecondToLast()->GetAircraft();

    // For second to last snapshot
    for (int i = 0; i < second_to_last->size(); i++) {
        if (second_to_last->at(i).GetTailNumber() == tail_number) {
            aircraft = second_to_last->at(i);
        }
    }

    // For last snapshot
    for (int i = 0; i < last->size(); i++) {
        if (last->at(i).GetTailNumber() == tail_number) {
            aircraft = last->at(i);
        }
    }

    return aircraft;
}

History *Prediction::GetHistory() {
    return _history;
}

Snapshot *Prediction::GetCurrentSnapshot() {
    return _current_snapshot;
}

int Prediction::GetSnapshotCounter() {
    return _snapshot_counter;
}

CorrelationAircraft Prediction::SearchTcasID(TcasID tcas_id) {
    CorrelationAircraft aircraft;

    std::vector<CorrelationAircraft> *last = _history->GetLast()->GetAircraft();
    std::vector<CorrelationAircraft> *second_to_last = _history->GetSecondToLast()->GetAircraft();

    // For second to last snapshot
    for (int i = 0; i < second_to_last->size(); i++) {
        if (second_to_last->at(i).GetTcasID().Get() == tcas_id.Get()) {
            aircraft = second_to_last->at(i);
        }
    }

    // For last snapshot
    for (int i = 0; i < last->size(); i++) {
        if (last->at(i).GetTcasID().Get() == tcas_id.Get()) {
            aircraft = last->at(i);
        }
    }

    return aircraft;
}

CorrelationAircraft Prediction::SearchRadarID(RadarID radar_id) {
    CorrelationAircraft aircraft;

    std::vector<CorrelationAircraft> *last = _history->GetLast()->GetAircraft();
    std::vector<CorrelationAircraft> *second_to_last = _history->GetSecondToLast()->GetAircraft();

    // For second to last snapshot
    for (int i = 0; i < second_to_last->size(); i++) {
        if (second_to_last->at(i).GetRadarID().Get() == radar_id.Get()) {
            aircraft = second_to_last->at(i);
        }
    }

    // For last snapshot
    for (int i = 0; i < last->size(); i++) {
        if (last->at(i).GetRadarID().Get() == radar_id.Get()) {
            aircraft = last->at(i);
        }
    }

    return aircraft;
}

Velocity Prediction::PredictVelocity(CorrelationAircraft *aircraft, bool is_relative) {
    Snapshot *last = _history->GetLast();
    Snapshot *second_to_last = _history->GetSecondToLast();

    CorrelationAircraft compare;

    SphericalCoordinate pos1;
    SphericalCoordinate pos2;

    Velocity predicted;

    if (is_relative && !second_to_last->GetAircraft()->empty()) {
        // For second to last snapshot
        for (int i = 0; i < second_to_last->GetAircraft()->size(); i++) {
            if (second_to_last->GetAircraft()->at(i).GetTcasID().Get() == aircraft->GetTcasID().Get()) {
                compare = second_to_last->GetAircraft()->at(i);
                pos1 = compare.GetSphericalCoordinate();
            }
        }

        // For last snapshot
        for (int i = 0; i < last->GetAircraft()->size(); i++) {
            if (last->GetAircraft()->at(i).GetTcasID().Get() == aircraft->GetTcasID().Get()) {
                compare = last->GetAircraft()->at(i);
                pos2 = compare.GetSphericalCoordinate();
            }
        }

        // Vector of aircraft from second to last snapshot
        Saas_Util::Vector<double, 3> vector1;
        vector1.x = pos1.GetRange() * sin(pos1.GetAzimuth()) * cos(pos1.GetElevation());
        vector1.y = pos1.GetRange() * cos(pos1.GetAzimuth()) * cos(pos1.GetElevation());
        vector1.z = -1 * pos1.GetRange() * sin(pos1.GetElevation());

        // Vector of aircraft from last snapshot
        Saas_Util::Vector<double, 3> vector2;
        vector1.x = pos2.GetRange() * sin(pos2.GetAzimuth()) * cos(pos1.GetElevation());
        vector1.y = pos2.GetRange() * cos(pos2.GetAzimuth()) * cos(pos1.GetElevation());
        vector1.z = -1 * pos2.GetRange() * sin(pos2.GetElevation());

        double time_diff = difftime(compare.GetTime(), aircraft->GetTime()); // seconds
        double east = (vector2.x - vector1.x) / time_diff;         // x
        double north = (vector2.y - vector1.y) / time_diff;        // y
        double down = (vector2.z - vector1.z) / time_diff;         // z

        // geodetic to cartesian
        predicted = Velocity(east, down, north);
    }

    return predicted;
}

GeographicCoordinate Prediction::PredictLocation(CorrelationAircraft *aircraft) {
    GenerationMath gen;
    double bearing = aircraft->GetSphericalCoordinate().GetBearing();
    GeographicCoordinate geo = gen.DestinationPoint(aircraft->GetGeographicCoordinate(),
                                                    aircraft->GetPredictedVelocity(), bearing);

    return geo;
}
