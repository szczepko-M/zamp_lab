#include <iostream>
#include "Interp4Pause.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmdInterp(void);
  const char* GetCmdName(void);
}

const char* GetCmdName(void){
  return "Pause";
}

AbstractInterp4Command* Interp4Pause::CreateCmd(void){
  return new Interp4Pause;
}

AbstractInterp4Command* CreateCmdInterp(void){
  return Interp4Pause::CreateCmd();
}

Interp4Pause::Interp4Pause(){}

void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause  CzasPostoju[ms]" << endl;
}

void Interp4Pause::PrintCmd() const {
  cout << "> Pause: " << _Time << endl;
}

bool Interp4Pause::ReadParams(std::istream& rStrm_CmdList){
  //rStrm_CmdList >> _Time;

  int Time;

  if(!(rStrm_CmdList >> Time)){
    std::cerr << "!!! Pause: Błąd w ładowaniu parametrów" << endl;
    return false;
  }

  if(Time < 0){
    std::cerr << "!!! Pause: Czas nie może być uejmny" << endl;
    return false;
  }

  _Time = Time;

  return true;
}

bool Interp4Pause::ExecCmd(Set4GeomObjects& Scn){
  // wykonanie przerwy w działaniu

  return true;
}