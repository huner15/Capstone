/*
 * Categorizer.cpp
 * Specific Atomics
 * Michael Lenz, Dat Tran
 * 2-6-16
 * Adds categories to planes.
*/
#include <cmath>
#include <cdti.pb.h>
#include <CorrelationAircraft.h>
#include <SpecialMath.h>
#include "ClientSocket.h"
#include "FlightReport.h"


ClientSocket socket_to_cdti("localhost", 13000);

double CalculateRange(CDTIPlane plane);
double CalculateCPA(CDTIPlane plane);
void CategorizePlane(CDTIPlane plane);
std::vector<CDTIPlane>* MakeCDTI(std::vector<CorrelationAircraft> aircraft);

/*
 *
 */
void Categorize(std::vector<CorrelationAircraft> aircraft) {
    std::vector<CDTIPlane>* planes = MakeCDTI(aircraft);
    CDTIReport report;

    //call something to translate whatever is given into a list of CDTIplanes
    for(int i = 0; i < planes->size(); i++){
        CategorizePlane(planes->at(i));
        report.mutable_planes()->AddAllocated(&(planes->at(i)));
    }

    socket_to_cdti << report;
}

CDTIPlane MakeCDTIPlane(CorrelationAircraft aircraft)
{
    FlightReport report = aircraft;
    return report.CreateCdtiPlane();
}

std::vector<CDTIPlane>* MakeCDTI(std::vector<CorrelationAircraft> aircraft) {
    std::vector<CDTIPlane>* planes;

    for(int i = 0; i < aircraft.size(); i++)
    {
        planes->push_back(MakeCDTIPlane(aircraft[i]));
    }

    return planes;
}



/**
 * decides where to Categorize a plane
 */
void CategorizePlane(CDTIPlane plane){
    double range = CalculateRange(plane);
    double cpa = CalculateCPA(plane);
    if(range < 2 && abs(plane.position().d()) < 300 && cpa < .5)
        plane.set_severity(plane.RESOLUTION);
    else if(range < 5 && abs(plane.position().d()) < 500 && cpa < 1)
        plane.set_severity(plane.TRAFFIC);
    else if(range < 10 && abs(plane.position().d()) < 1000)
        plane.set_severity(plane.PROXIMATE);


}


/**
 * calculates range to ownship.
 * returns a double representing the planes distance to the ownship
 */
double CalculateRange(CDTIPlane plane) {
    Vector pos = plane.position();
    Saas_Util::Vector<double,3> zero;
    Saas_Util::Vector<double,3> position;
    position.x = pos.n();
    position.y = pos.e();
    position.z = pos.d();
    return SpecialMath::DistanceFormula<double, 3>(position, zero);

}
/**
 * calculates closest point of approach
 * returns a double representing the closest point of approach.
 */
double CalculateCPA(CDTIPlane plane) {
    //since ownship is at (0,0) formula is |c|/sqrt(a^2+b^2)
    Saas_Util::Vector<double, 3> zero;
    Saas_Util::Vector<double, 3> pos;
    Saas_Util::Vector<double, 3> vel;
    pos.x = plane.position().n();
    pos.y = plane.position().e();
    pos.z = plane.position().d();
    vel.x = plane.velocity().n();
    vel.y = plane.velocity().e();
    vel.z = plane.velocity().d();
    return SpecialMath::LineDistance(pos, vel, zero);
}





