#include <iostream>
#include "Interp4Set.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmdInterp(void);
  const char* GetCmdName(void);
}

const char* GetCmdName(void)
{
  return "Set";
}

AbstractInterp4Command* CreateCmdInterp(void)
{
  return new Interp4Set();
}

Interp4Set::Interp4Set()
{}

void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  Wsp_x[m]  Wsp_y[m]  Wsp_z[m]  KatOX[st]  KatOY[st]  KatOZ[st]" << endl;
}
