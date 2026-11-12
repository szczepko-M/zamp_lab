#include "GeomObject.hh"
//#include "g3dVector.hh"

//using namespace std;

GeomObject::GeomObject(const std::string& Name, const g3d::Vector& Pos_m, const g3d::Vector& RotAng_deg) : _Pos_m(Pos_m), _RotAng_deg(RotAng_deg), _Name(Name)
{}