//
//#include "EmptySphericalCoordinate.h"
//
//EmptySphericalCoordinate::EmptySphericalCoordinate() {
//    _range = DEFAULT_RANGE;
//    _elevation = 0;
//    _azimuth = DEFAULT_AZIMUTH;
//}
//
//EmptySphericalCoordinate::~EmptySphericalCoordinate() {
//}
//
//double EmptySphericalCoordinate::GetRange() const {
//    return _range;
//}
//
//double EmptySphericalCoordinate::GetElevation() const {
//    return _elevation;
//}
//
//double EmptySphericalCoordinate::GetAzimuth() const {
//    return _azimuth;
//}
//
//double EmptySphericalCoordinate::GetBearing() const {
//    return _azimuth;
//}
//
//Saas_Util::Vector<double, 3> EmptySphericalCoordinate::ToCartesianCoordinates() {
//    Saas_Util::Vector<double, 3> cartesian;
//    cartesian.x = _range * sin(_elevation) * cos(_azimuth);
//    cartesian.y = _range * sin(_elevation) * sin(_azimuth);
//    cartesian.z = _range * cos(_elevation);
//    return cartesian;
//}
//
//double EmptySphericalCoordinate::operator-(const SphericalCoordinate &other) {
//    return sqrt(pow(this->GetRange(), 2) + pow(other.GetRange(), 2) -
//                2 * this->GetRange() * other.GetRange() *
//                (sin(this->GetElevation()) * sin(other.GetElevation() *
//                                                 cos(this->GetAzimuth() -
//                                                     other.GetAzimuth()) +
//                                                 cos(this->GetElevation()) *
//                                                 cos(other.GetElevation()))));
//}
//
