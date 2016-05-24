//
// Created by andrea on 5/19/16.
//

#include <cdti.pb.h>
#include "ProcessorLogger.h"

ProcessorLogger::ProcessorLogger() {
    _surveillanceReportsData.open("ReceivedSurveillanceReports.txt");
    _aircraftData.open("CorrelatedAircraft.txt");
    _cdtiReportData.open("GeneratedCDTIReports.txt");
    _cdtiReportData << "// CDTIPlanes are documented as 'at position:";
    _cdtiReportData << " (x, y, z) going velocity:(north, east, down)";
    _cdtiReportData << " feet/sec'" << endl;

    _snapshotIndex = 0;
}

ProcessorLogger::~ProcessorLogger() {
    _surveillanceReportsData.close();
    _aircraftData.close();
    _cdtiReportData.close();
}

void ProcessorLogger::LogCDTIReport(CDTIReport *report) {
    CDTIPlane *plane;

    _cdtiReportData << "CDTIReport #" << _snapshotIndex << endl;

    _cdtiReportData << "    " << report->planes_size() << " aircraft";
    _cdtiReportData << " at " << report->timestamp() << " seconds" << endl;

    _cdtiReportData << "    Ownship at ";
    writeVector(report->mutable_ownship()->mutable_position());
    _cdtiReportData << " going ";
    writeVector(report->mutable_ownship()->mutable_velocity());
    _cdtiReportData << " feet/second\n" << endl;

    for (int i = 0; i < report->planes_size(); i++) {
        plane = report->mutable_planes(i);

        _cdtiReportData << "    Aircraft #" << i << "\n        at ";
        writeVector(plane->mutable_position());
        _cdtiReportData << " going ";
        writeVector(plane->mutable_velocity());
        _cdtiReportData << " feet/second" << endl;
    }

    _cdtiReportData << endl;
    _snapshotIndex++;
}

void ProcessorLogger::writeVector(Vector *vec) {
    _cdtiReportData << "(" << vec->n() << ", " << vec->e();
    _cdtiReportData << ", " << vec->d() << ")";
}

void ProcessorLogger::LogCorrelationAircraft(
        std::vector<CorrelationAircraft *> *aircraft) {
    CorrelationAircraft *curAircraft;
    Velocity vel;
    GeographicCoordinate geo;
    SphericalCoordinate spher;

    _aircraftData << "Correlation Cycle #" << _snapshotIndex << endl;
    _aircraftData << "      " << aircraft->size();
    _aircraftData << " aircraft correlated" << endl;

    for (int i = 0; i < aircraft->size(); i++) {
        curAircraft = aircraft->at(i);
        vel = curAircraft->GetVelocity();
        geo = curAircraft->GetGeographicCoordinate();
        spher = curAircraft->GetSphericalCoordinate();

        _aircraftData << "\n    Aircraft";

        if (curAircraft->GetTailNumber().Get().compare("      ")) {
            _aircraftData << " \"" << curAircraft->GetTailNumber().Get()<< "\"";
        }

        _aircraftData << " TCAS ID #" << (int) curAircraft->GetTcasID().Get();
        _aircraftData << " Radar ID #" << curAircraft->GetRadarID().Get()
            << endl;

        _aircraftData << "        Correlated at " << (float)
                curAircraft->GetTime() << " seconds" << endl;
        _aircraftData << "        Most High Ranked Report Type in Cluster " <<
                "(ADSB, TCAS, radar): " << curAircraft->GetDeviceType() << endl;

        _aircraftData << "        Moving at (" << vel.north << ", " << vel.east
                << ", " << vel.down << ") feet/second" << endl;

        if (!(geo.GetLatitude() == 0 && geo.GetLongitude() == 0 &&
                geo.GetAltitude() == 0)) {
            _aircraftData << "        Located at latitude: " <<
            geo.GetLatitude();
            _aircraftData << ", longitude: " << geo.GetLongitude();
            _aircraftData << ", and altitude: " << geo.GetAltitude() << endl;
        }

        _aircraftData << "        Relative to ownship at range: " <<
                spher.GetRange() << ", azimuth: " << spher.GetAzimuth();
        _aircraftData << ", elevation: " << spher.GetElevation() << endl;
    }

    _aircraftData << endl;
}

void ProcessorLogger::LogReceivedReports(ReceivedReports *reports) {
    vector<SurveillanceReport *> *rep = reports->GetAdsb();
    SurveillanceReport *ownship = reports->GetOwnship();

    _surveillanceReportsData << "Received Reports Cycle #" << _snapshotIndex
        << endl;
    _surveillanceReportsData << "      Ownship:" << endl;
    _surveillanceReportsData << "        Moving at (" <<
        ownship->GetVelocity()->north << ", " << ownship->GetVelocity()->east
        << ", " << ownship->GetVelocity()->down << ") feet/second" << endl;

    _surveillanceReportsData << "        Located at latitude: ";
    _surveillanceReportsData <<ownship->GetGeographicCoordinate()->GetLatitude()
        << ", longitude: " << ownship->GetGeographicCoordinate()->GetLongitude()
        << ", and altitude: " <<
        ownship->GetGeographicCoordinate()->GetAltitude() << endl;

    //ADS-B Reports
    _surveillanceReportsData << "\n    ADS-B reports: " << rep->size() << endl;

    for (int i = 0; i < rep->size(); i++) {
        _surveillanceReportsData << "      Aircraft \"" <<
            rep->at(i)->GetTailNumber().Get() << "\"" << endl;
        _surveillanceReportsData << "        Correlated at " <<
            rep->at(i)->GetTime() << " seconds" << endl;

        _surveillanceReportsData << "        Moving at (" <<
            rep->at(i)->GetVelocity()->north << ", " <<
            rep->at(i)->GetVelocity()->east << ", " <<
            rep->at(i)->GetVelocity()->down << ") feet/second" << endl;

        _surveillanceReportsData << "        Located at latitude: " <<
            rep->at(i)->GetGeographicCoordinate()->GetLatitude() << ", " <<
            "longitude: " << rep->at(i)->GetGeographicCoordinate()
                    ->GetLongitude() << ", and altitude: " <<
            rep->at(i)->GetGeographicCoordinate()->GetAltitude() << endl;
    }

    //TCAS Reports
    rep = reports->GetTcas();
    _surveillanceReportsData << "\n    TCAS-B reports: " << rep->size() << endl;

    for (int i = 0; i < rep->size(); i++) {
        _surveillanceReportsData << "      Aircraft #" <<
                (int) rep->at(i)->GetTcasID().Get() << endl;
        _surveillanceReportsData << "        Correlated at " <<
            rep->at(i)->GetTime() << " seconds" << endl;

        _surveillanceReportsData << "        Relative to ownship at range: " <<
            rep->at(i)->GetSphericalCoordinate()->GetRange() << ", azimuth: " <<
            rep->at(i)->GetSphericalCoordinate()->GetAzimuth() << ", elevation"
            << ": " << rep->at(i)->GetSphericalCoordinate()->GetElevation()
            << endl;
    }

    //Radar Reports
    rep = reports->GetRadar();
    _surveillanceReportsData << "\n    Radar reports: " << rep->size() << endl;

    for (int i = 0; i < rep->size(); i++) {
        _surveillanceReportsData << "      Aircraft #" <<
            rep->at(i)->GetRadarID().Get() << endl;
        _surveillanceReportsData << "        Correlated at " <<
            rep->at(i)->GetTime() << " seconds" << endl;

        _surveillanceReportsData << "        Moving at (" <<
            rep->at(i)->GetVelocity()->north << ", " <<
            rep->at(i)->GetVelocity()->east << ", " <<
            rep->at(i)->GetVelocity()->down << ") feet/second" << endl;

        _surveillanceReportsData << "        Located at latitude: " <<
            rep->at(i)->GetGeographicCoordinate()->GetLatitude() <<
            ", longitude: " <<
            rep->at(i)->GetGeographicCoordinate()->GetLongitude() <<
            ", and altitude: " <<
            rep->at(i)->GetGeographicCoordinate()->GetAltitude() << endl;


        _surveillanceReportsData << "        Relative to ownship at range: " <<
            rep->at(i)->GetSphericalCoordinate()->GetRange() << ", azimuth: " <<
            rep->at(i)->GetSphericalCoordinate()->GetAzimuth() << ", elevation"
            << ": " << rep->at(i)->GetSphericalCoordinate()->GetElevation()
            << endl;
    }

    _surveillanceReportsData << endl;
}