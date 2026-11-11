#include <iostream>
#include "Interp4Set.hh"

#include "Set4GeomObjects.hh"
#include "GeomObject.hh"


using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmdInterp(void);
  const char* GetCmdName(void);
}

const char* GetCmdName(void){
  return "Set";
}

AbstractInterp4Command* Interp4Set::CreateCmd(void){
  return new Interp4Set;
}

AbstractInterp4Command* CreateCmdInterp(void){
  return Interp4Set::CreateCmd();
}

Interp4Set::Interp4Set(){}

void Interp4Set::PrintSyntax() const{
  cout << "   Set  NazwaObiektu  Wsp_x[m]  Wsp_y[m]  Wsp_z[m]  KatOX[st]  KatOY[st]  KatOZ[st]" << endl;
}

void Interp4Set::PrintCmd() const {
  cout << "> Set: " << _ObjName << " " << _DistX << " " << _DistY << " " << _DistZ <<
  " " << _AngleX << " " << _AngleY << " " << _AngleZ << endl;
}

bool Interp4Set::ReadParams(std::istream& rStrm_CmdList){
  std::string ObjName;
  double distX, distY, distZ, angleX, angleY, angleZ;


  if(!(rStrm_CmdList >> ObjName >> distX >> distY >> distZ >> angleX >> angleY >> angleZ)){
    std::cerr << "!!! Set: Błąd w ładowaniu parametrów" << endl;
    return false;
  }

  _ObjName = ObjName;
  _DistX = distX;
  _DistY = distY;
  _DistZ = distZ;
  _AngleX = angleX;
  _AngleY = angleY;
  _AngleZ = angleZ;

  return true;
}


bool Interp4Set::ExecCmd(Set4GeomObjects& Scn){
  std::shared_ptr<GeomObject> pObj = Scn.FindGeomObj(_ObjName);

  if(!pObj){
    std::cout << "!!! Set: Nie znaleziono obiektu " << _ObjName << " w scenie. Tworzenie nowego obiektu..." << endl;
    
    if(!Scn.AddGeomObj(_ObjName)){
      return false;
    }

    pObj = Scn.FindGeomObj(_ObjName);
  }

  // --- tutaj musi być coś w stylu wstawiania parametrów objektu
  // pObj->UsePos_m()[0] = _DistX;
  // pObj->

  pObj->UsePos_m() = g3d::Vector(_DistX, _DistY, _DistZ);

  cout << "# Wykonano operację Set na obiekcie " << _ObjName << endl;

  return true;
}