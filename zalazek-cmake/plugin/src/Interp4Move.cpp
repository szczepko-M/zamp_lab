#include <iostream>
#include "Set4GeomObjects.hh"
#include "Interp4Move.hh"
#include "GeomObject.hh"
#include <memory>
//#include <cerrno>

#include <unistd.h>
#include <math.h>
#include <chrono>
#include <thread>

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
    Channel.print_error("!!! Move: Nie znaleziono obiektu " + _ObjName + " w scenie");
    return false;
  }

  if(_Distance <= 0){
    Channel.print_error("!!! Move: Zerowy/Ujemny dystans dla obiektu " + _ObjName + " w scenie");
    return true;
  }

  if(_Speed == 0){
    Channel.print_error("!!! Move: Zerowa prędkość dla obiektu" + _ObjName + " w scenie");
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

  const int fps = 30;
  const double pi = 3.141;
  const double direction = (_Speed > 0) ? 1.0 : -1.0;
  const int frames = std::max(1, (int)std::ceil(fps * _Distance / std::fabs(_Speed)));
  double delta_dist = _Distance / frames;
  std::chrono::microseconds time_step_us = std::chrono::microseconds(1000000 / fps);

  for(int i = 0; i<frames; i++){
    g3d::Vector curr_pos;
    {
      std::lock_guard<GeomObject> Lock(*pObj);

      double y_rad = pObj->GetRotAng_deg()[1] * pi / 180.0;
      double z_rad = pObj->GetRotAng_deg()[2] * pi / 180.0;

      curr_pos = pObj->GetPos_m();

      curr_pos[0] += direction * delta_dist * std::cos(y_rad) * std::cos(z_rad);
      curr_pos[1] += direction * delta_dist * std::cos(y_rad) * std::sin(z_rad);
      curr_pos[2] -= direction * delta_dist * std::sin(y_rad);

      pObj->UsePos_m() = curr_pos;      

      std::ostringstream info_stream;
      info_stream << "# Move: " << _ObjName << ", nowa pozycja: "
      << curr_pos[0] << ", "
      << curr_pos[1] << ", "
      << curr_pos[2] << " ";

      Channel.print(info_stream.str());
    }
    
    std::this_thread::sleep_for(time_step_us);
  }

  return true;
}
