#include <iostream>
#include "Interp4Move.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmdInterp(void);
  const char* GetCmdName(void);
}

const char* GetCmdName(void)
{
  return "Move";
}

AbstractInterp4Command* CreateCmdInterp(void)
{
  return new Interp4Move();
}

Interp4Move::Interp4Move()
{}

void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
