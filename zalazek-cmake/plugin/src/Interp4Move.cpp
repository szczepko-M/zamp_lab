#include <iostream>
#include "Set4GeomObjects.hh"
#include "Interp4Move.hh"
#include "GeomObj.hh"
#include <memory>
//#include <cerrno>

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmdInterp(void);
  const char* GetCmdName(void);
}

const char* GetCmdName(void) {
  return "Move";
}

AbstractInterp4Command* Interp4Move::CreateCmd(void) {
  return new Interp4Move;
}

AbstractInterp4Command* CreateCmd(void){
  return Interp4Move::CreateCmd();
}

Interp4Move::Interp4Move(){}

void Interp4Move::PrintSyntax() const {
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}

void Interp4Move::PrintCmd() const {
  cout << "Move " << _ObjName << " " << _Speed << " " << _Distance << endl;
}

bool Interp4Move::ReadParams(std::istream& rStrm_CmdList){
  rStrm_CmdList >> _ObjName >> _Speed >> _Distance;

  if(rStrm_CmdList.fail()){
    std::cerr << "!!! Błąd w ładowaniu parametrów" << endl;
    return false;
  }

  return true;
}

bool Interp4Move::ExecCmd(Set4GeomObjects& Scn){
  std::shared_ptr<GeomObj> pObj = Scn.FindGeomObj(_ObjName);

  if(!pObj){
    std::cerr << "!!! Move: Nie znaleziono obiektu " << _ObjName << " w scenie" << endl;
    return false;
  }

  // pObj->UsePos_m()[0] += _Distance;

  cout << "Move: " << _ObjName << ", nowa pozycja: "
    << pObj->GetPos_m()[0] << ", "
    << pObj->GetPos_m()[1] << ", "
    << pObj->GetPos_m()[2] << " " << endl;

  return true;
}
