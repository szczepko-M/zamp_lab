#include "GeomObj.hh"
#include "g3dVector.hh"

using namespace std;

GeomObj::GeomObj(const string &Name, g3d::Vector Pos_m){
    _Name = Name;
    _Pos_m = Pos_m;
}

std::string GeomObj::GetName() const {
    return _Name;
}

void GeomObj::SetName(const std::string &Name) {
    _Name = Name;
}

g3d::Vector GeomObj::GetPos_m() const {
    return _Pos_m;
}
