#include <iostream>
#include "Interp4Rotate.hh"
#include "GeomObject.hh"
#include "Set4GeomObjects.hh"
#include <memory>
#include <cmath>

#include <thread>

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

bool Interp4Rotate::ExecCmd(Set4GeomObjects& Scn, ComChannel& Channel){
  std::shared_ptr<GeomObject> pObj = Scn.FindGeomObj(_ObjName);

  if(!pObj){
    Channel.print_error("!!! Move: Nie znaleziono obiektu " + _ObjName + " w scenie");
    return false;
  }

  const int fps = 30;
  const double direction = (_AngularSpeed > 0) ? 1.0 : -1.0;
  const int frames = std::max(1, (int)std::ceil(fps * _Rotation / std::fabs(_AngularSpeed)));
  double delta_angle = _Rotation / frames;
  std::chrono::microseconds time_step_us = std::chrono::microseconds(1000000 / fps);

  for(int i=0; i<frames; i++){
    g3d::Vector curr_angle;
    {
      std::lock_guard<GeomObject> Lock(*pObj);

      curr_angle = pObj->GetRotAng_deg();

      if(_Axis == "OX"){
        pObj->UseRotAng_deg()[0] = std::fmod((pObj->UseRotAng_deg()[0] + delta_angle), 360);
      }
      else if(_Axis == "OY"){
        pObj->UseRotAng_deg()[1] = std::fmod((pObj->UseRotAng_deg()[1] + delta_angle), 360);
      }
      else{
        pObj->UseRotAng_deg()[2] = std::fmod((pObj->UseRotAng_deg()[2] + delta_angle), 360);
      }
    

      std::ostringstream info_stream;
      info_stream << "# Rotatr: " << _ObjName << ", nowa pozycja: "
      << curr_angle[0] << ", "
      << curr_angle[1] << ", "
      << curr_angle[2];

      Channel.print(info_stream.str());
    }

    std::this_thread::sleep_for(time_step_us);
  }  

  return true;
}