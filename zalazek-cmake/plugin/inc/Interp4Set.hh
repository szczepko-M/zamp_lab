#ifndef INTERP4SET_HH
#define INTERP4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Set: public AbstractInterp4Command {
  std::string _ObjName;
  int _DistX = 0;
  int _DistY = 0;
  int _DistZ = 0;
  int _AngleX = 0;
  int _AngleY = 0;
  int _AngleZ = 0;

 public:
  Interp4Set();

  void PrintSyntax() const override;
  void PrintCmd() const override;
  bool ReadParams(std::istream& rStrm_CmdList) override;
  bool ExecCmd(Set4GeomObjects& Scn) override;

  static AbstractInterp4Command* CreateCmd();
};

#endif
