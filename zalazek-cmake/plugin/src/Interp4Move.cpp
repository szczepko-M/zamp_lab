#include <iostream>
#include "Set4GeomObjects.hh"
#include "Interp4Move.hh"
#include "GeomObject.hh"
#include <memory>
//#include <cerrno>

#include <unistd.h>
#include <math.h>

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

AbstractInterp4Command* CreateCmdInterp(void){
  return Interp4Move::CreateCmd();
}

Interp4Move::Interp4Move(){}

void Interp4Move::PrintSyntax() const {
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}

void Interp4Move::PrintCmd() const {
  cout << "> Move " << _ObjName << " " << _Speed << " " << _Distance << endl;
}

bool Interp4Move::ReadParams(std::istream& rStrm_CmdList){
  std::string ObjName;
  double Speed, Distance;

  if(!(rStrm_CmdList >> ObjName >> Speed >> Distance)) return false;

  _ObjName = ObjName;
  _Speed = Speed;
  _Distance = Distance;

  return true;
}

bool Interp4Move::ExecCmd(Set4GeomObjects& Scn, ComChannel& Channel){
  std::shared_ptr<GeomObject> pObj = Scn.FindGeomObj(_ObjName);

  if(!pObj){
    std::cerr << "!!! Move: Nie znaleziono obiektu " << _ObjName << " w scenie" << endl;
    return false;
  }

  // tu zaczyna się pierdolnik z ustawieniami obiektów

  /* --- stara definicja ---
  pObj->UsePos_m()[0] += _Distance;

  cout << "# Move: " << _ObjName << ", nowa pozycja: "
    << pObj->GetPos_m()[0] << ", "
    << pObj->GetPos_m()[1] << ", "
    << pObj->GetPos_m()[2] << " " << endl;
  */ 

  int frames = abs(fps * _Distance / _Speed);
  int direction = _Speed / abs(_Speed);

  double delta_dist = _Distance / frames;
  double time_step_us = 1000000 / fps;

  for(int i = 0; i<frames; i++){
    pObj->Lock();

    double y_rad = pObj->GetRotAng_deg()[1] * M_PI / 180.0;
    double z_rad = pObj->GetRotAng_deg()[2] * M_PI / 180.0;

    g3d::Vector curr_pos = pObj->GetPos_m();

    curr_pos[0] += delta_dist * cos(y_rad) * cos(z_rad);
    curr_pos[1] += delta_dist * cos(y_rad) * sin(z_rad);
    curr_pos[2] -= direction * delta_dist * sin(y_rad);

    pObj->UsePos_m(curr_pos);

    std::stringstream info_stream;

    info_stream << "# Move: " << _ObjName << ", nowa pozycja: "
    << curr_pos[0] << ", "
    << curr_pos[1] << ", "
    << curr_pos[2] << " " << endl;

    ComChannel.Lock();
    ComChannel.print(info_stream);
    ComChannel.Unlock();

    pObj->Unlock();
  }

  return true;
}
