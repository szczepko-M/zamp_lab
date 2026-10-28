#include <iostream>
#include "Interp4Rotate.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmdInterp(void);
  const char* GetCmdName(void);
}

const char* GetCmdName(void)
{
  return "Rotate";
}

AbstractInterp4Command* CreateCmdInterp(void)
{
  return new Interp4Rotate();
}

Interp4Rotate::Interp4Rotate()
{}

void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  NazwaOsi(OX|OY|OZ)  Szybkosc[st/s]  KatObrotu[st]" << endl;
}
