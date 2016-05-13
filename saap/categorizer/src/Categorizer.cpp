/*
 * Categorizer.cpp
 * Specific Atomics
 * Michael Lenz, Dat Tran, Frank Poole
 * 5-12-2016
 * Generates CDTIReports from a set of Correlation Aircraft and assigns a
 * severity category to all local detected planes.
*/

#include "Categorizer.h"

Categorizer::Categorizer() {
    _ownship_cdti_plane = CreateOwnshipCDTIPlane();
}

CDTIPlane* Categorizer::CreateOwnshipCDTIPlane() {
    /** Allocate memory for the ownship plane. */
    CDTIPlane* ownship = new CDTIPlane();

    /** Set ownship position. */
    Vector* ownship_position = new Vector();
    ownship_position->set_n(0);
    ownship_position->set_e(0);
    ownship_position->set_d(0);
    ownship->set_allocated_position(ownship_position);

    /** Set ownship velocity. */
    Vector* ownship_velocity = new Vector();
    ownship_velocity->set_n(0);
    ownship_velocity->set_e(0);
    ownship_velocity->set_d(0);
    ownship->set_allocated_velocity(ownship_velocity);

    /** Set ownship ID to 0. There may be another CDTI Plane with ID 0 however
     * this should not conflict with correlation as categorization runs after
     * correlation. */
    ownship->set_id("0");

    /** Set ownship severity category to proximate. This value should never be
     * used however a CDTI Plane requires a severity category. */
    ownship->set_severity(CDTIPlane_Severity_PROXIMATE);

    return ownship;
}

Categorizer::~Categorizer() {
    delete _ownship_cdti_plane;
}

CDTIReport* Categorizer::Categorize(
        std::vector<CorrelationAircraft *> *correlation_aircraft) {
    /** Allocate memory for the cdti report. */
    CDTIReport* cdti_report = new CDTIReport();

    /** Set CDTI Report timestamp. */
    // TODO: Use system time for timestamp.
    int64_t timestamp = 0;
    cdti_report->set_timestamp(timestamp);

    /** Use a constant ownship cdti plane to avoid ownship re-initialization. */
    cdti_report->set_allocated_ownship(_ownship_cdti_plane);

    /** Set the CDTI Report traffic advisory message. */
    // TODO: Generate dynamic traffic advisory messages.
    cdti_report->set_advisorymessage("");

    /** Set the overall CDTI Report severity category. */
    /** TODO: Generate a dynamic overall severity - perhaps based on the maximum
        severity of all CDTI planes. */
    cdti_report->set_advisorylevel(CDTIReport_Severity_PROXIMATE);

    // Call something to translate whatever is given into a list of CDTIplanes.
    for (int i = 0; i < correlation_aircraft->size(); ++i) {
        /** Rely on the CorrelationAircraft to set all CDTI plane fields other
         * than the traffic category. */
        CDTIPlane cdti_plane = correlation_aircraft->at(i)->CreateCdtiPlane();

        /** Set the CDTI proximate traffic category. */
        cdti_plane.set_severity(GenerateSeverity(&cdti_plane));

        /** Add the CDTI plane to the CDTI Report. */
        CDTIPlane *set_cdti_plane = cdti_report->add_planes();
        *set_cdti_plane = cdti_plane;
    }

    return cdti_report;
}

/**
 * calculates range to ownship.
 * returns a double representing the planes distance to the ownship
 */
double Categorizer::CalculateRange(CDTIPlane plane) {
    Vector* pos = plane.mutable_position();
    Saas_Util::Vector<double,3> position;

    position.x = pos->n();
    position.y = pos->e();
    position.z = pos->d();

    Saas_Util::Vector<double,3> zero;

    return SpecialMath::DistanceFormula<double, 3>(position, zero);
}

/**
 * Calculates the closest point of approach.
 * returns a double representing the closest point of approach.
 */
double Categorizer::CalculateCPA(CDTIPlane plane) {
    // Since ownship is at (0,0), the formula is |c|/sqrt(a^2+b^2).

    Saas_Util::Vector<double, 3> pos;
    pos.x = plane.position().n();
    pos.y = plane.position().e();
    pos.z = plane.position().d();

    Saas_Util::Vector<double, 3> vel;
    vel.x = plane.velocity().n();
    vel.y = plane.velocity().e();
    vel.z = plane.velocity().d();

    Saas_Util::Vector<double, 3> zero;

    return SpecialMath::LineDistance(pos, vel, zero);
}

/**
 * Decides where to Categorize a plane.
 */
CDTIPlane_Severity Categorizer::GenerateSeverity(CDTIPlane* plane) {
    double range = CalculateRange(*plane);
    double cpa = CalculateCPA(*plane);

    if (range < 2 && abs(plane->position().d()) < 300 && cpa < .5) {
        return plane->RESOLUTION;
    }
    else if (range < 5 && abs(plane->position().d()) < 500 && cpa < 1) {
        return plane->TRAFFIC;
    }
    else if (range < 10 && abs(plane->position().d()) < 1000) {
        return plane->PROXIMATE;
    }
    else {
        return plane->PROXIMATE;
    }
}
