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
std::vector<CDTIPlane> MakeCDTI(std::vector<CorrelationAircraft*>* aircraft);

/*
 *
 */
void Categorize(std::vector<CorrelationAircraft *> *aircraft) {
    std::vector<CDTIPlane> planes; // = MakeCDTI(aircraft);
    CDTIReport *report = new CDTIReport();
    int64_t t = 1;
    report->set_timestamp(t);
    CDTIPlane* ownship = new CDTIPlane();
    Vector* pv = new Vector();

    printf("printCategorizereport\n");

    pv->set_d(5);
    pv->set_e(3);
    pv->set_n(4);
    CDTIPlane *plane = new CDTIPlane();
    plane->set_severity(CDTIPlane_Severity_TRAFFIC);
    plane->set_allocated_velocity(pv);
    plane->set_allocated_position(pv);
    plane->set_id("23");

    pv->set_d(5);
    pv->set_e(3);
    pv->set_n(4);
    ownship->set_allocated_position(pv);
    ownship->set_allocated_velocity(pv);
    ownship->set_id("2");
    ownship->set_severity(CDTIPlane_Severity_TRAFFIC);
    report->set_allocated_ownship(ownship);
    report->set_advisorymessage("message");
    report->set_advisorylevel(CDTIReport_Severity_TRAFFIC);
    CDTIPlane *set = report->add_planes();
    *set = *plane;
   // report->mutable_planes()->AddAllocated(plane);
    //call something to translate whatever is given into a list of CDTIplanes
//    for(int i = 0; i < planes.size(); i++){
//        CategorizePlane(planes.at(i));
//        report->mutable_planes()->AddAllocated(&(planes.at(i)));
//    }

    cout << ownship->id();

    socket_to_cdti << *report;
}

CDTIPlane MakeCDTIPlane(CorrelationAircraft* aircraft)
{
    return aircraft->CreateCdtiPlane();
}

std::vector<CDTIPlane> MakeCDTI(std::vector<CorrelationAircraft*> *aircraft) {
    std::vector<CDTIPlane> planes;

    for(int i = 0; i < aircraft->size(); i++)
    {
        planes.push_back(MakeCDTIPlane(aircraft->at(i)));
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





