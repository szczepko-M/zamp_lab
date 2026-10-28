#include <iostream>
#include "Interp4Pause.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmdInterp(void);
  const char* GetCmdName(void);
}

const char* GetCmdName(void)
{
  return "Pause";
}

AbstractInterp4Command* CreateCmdInterp(void)
{
  return new Interp4Pause();
}

Interp4Pause::Interp4Pause()
{}

void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause  CzasPostoju[ms]" << endl;
}
