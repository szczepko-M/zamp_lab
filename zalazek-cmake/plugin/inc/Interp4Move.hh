#ifndef INTERP4MOVE_HH
#define INTERP4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"
#include "Set4GeomObjects.hh"
#include "GeomObject.hh"

class Interp4Move: public AbstractInterp4Command {
  std::string _ObjName;
  int _Speed = 0;
  int _Distance = 0;

  public:
    Interp4Move();

    void PrintSyntax() const override;
    void PrintCmd() const override;
    bool ReadParams(std::istream& rStrm_CmdList) override;
    bool ExecCmd(Set4GeomObjects& Scn) override;

    static AbstractInterp4Command* CreateCmd();

};

#endif
