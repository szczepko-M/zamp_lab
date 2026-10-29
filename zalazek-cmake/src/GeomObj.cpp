#include "GeomObj.hh"

using namespace std;

GeomObj::GeomObj(const string &Name, Vector3D Pos_m){
    _Name = Name;
    _Pos_m = Pos_m;
}

std::string GeomObj::GetName(){
    return _Name;
}

void GeomObj::SetName(const std:string &Name){
    _Name = Name;
}

Vector3D GeomObj::GetPos_m(){
    return _Pos_m;
}

