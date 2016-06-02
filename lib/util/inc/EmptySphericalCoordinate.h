//
//#ifndef SAAS_EMPTYSPHERICALCOORDINATE_H
//#define SAAS_EMPTYSPHERICALCOORDINATE_H
//
//#include <cmath>
//#include <vector>
//#include "Vector.h"
//
//#define DEFAULT_AZIMUTH 1
//#define DEFAULT_RANGE 1
//
//class EmptySphericalCoordinate : public SphericalCoordinate {
//private:
//    double _range;
//    double _elevation;
//    double _azimuth;
//
//public:
//    EmptySphericalCoordinate() {};
//
//    ~EmptySphericalCoordinate();
//
//    /**
//     * Accessor for the Range of the Spherical Coordinate.
//     * @return range of the spherical coordinate.
//     */
//    double GetRange() const;
//
//    /**
//     * Accessor for the Elevation of the Spherical Coordinate.
//     * @return Elevation of the spherical coordinate.
//     */
//    double GetElevation() const;
//
//    /**
//     * Accessor for the Azimuth of the Spherical Coordinate.
//     * @return azimuth of the spherical coordinate.
//     */
//    double GetAzimuth() const;
//
//    /**
//     * Accessor for the Bearing of the Spherical Coordinate.
//     * @return bearing of the spherical coordinate.
//     */
//    double GetBearing() const;
//
//    /**
//     * Converts spherical coordinates to cartesian coordinates
//     * @return cartesian coordinates of the spherical coordinate
//     */
//    Saas_Util::Vector<double, 3> ToCartesianCoordinates();
//
//    /**
//     * Return the distance between this and another spherical coordinate.
//     * @param other another spherical coordinate to measure to
//     * @return the distance between the spherical coordinates
//     */
//    double operator- (const SphericalCoordinate& other);
//};
//
//#endif //SAAS_EMPTYSPHERICALCOORDINATE_H
