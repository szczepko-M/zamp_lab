#include <iostream>
#include "Interp4Rotate.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmdInterp(void);
  const char* GetCmdName(void);
}

const char* GetCmdName(void){
  return "Rotate";
}

AbstractInterp4Command* Interp4Rotate::CreateCmd(void){
  return new Interp4Rotate;
}

AbstractInterp4Command* CreateCmdInterp(void){
  return Interp4Rotate::CreateCmd();
}

Interp4Rotate::Interp4Rotate()
{}

void Interp4Rotate::PrintSyntax() const{
  cout << "   Rotate  NazwaObiektu  NazwaOsi(OX|OY|OZ)  Szybkosc[st/s]  KatObrotu[st]" << endl;
}

void Interp4Rotate::PrintCmd() const {
  cout << "> Rotate " << _ObjName << " " << _Axis << " " << _AngularSpeed
  << " " << _Rotation << endl;
}
bool Interp4Rotate::ReadParams(std::istream& rStrm_CmdList){
  std::string ObjName, Axis;
  double AngularSpeed, Rotation;

  if(!(rStrm_CmdList >> ObjName >> Axis >> AngularSpeed >> Rotation)){
    std::cerr << "!!! Rotate: Błąd w ładowaniu parametrów" << endl;
    return false;
  }

  if(Axis != "OX" && Axis != "OY" && Axis != "OZ"){
    std::cerr << "!!! Rotate: nieznana os \"" << Axis << "\" (dozwolone: OX, OY, OZ)" << endl;
    return false;
  }

  _ObjName = ObjName;
  _Axis = Axis;
  _AngularSpeed = AngularSpeed;
  _Rotation = Rotation;

  return true;
}

bool Interp4Rotate::ExecCmd(Set4GeomObjects& Scn){
  // wykonanie rotacji

  return true;
}