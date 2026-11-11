#ifndef INTERP4ROTATE_HH
#define INTERP4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Rotate: public AbstractInterp4Command {
  std::string _ObjName;
  std::string _Axis; // może jakiś enum coś ten ?
  int _AngularSpeed = 0;
  int _Rotation = 0;

  public:
    Interp4Rotate();

    //void PrintSyntax() const override;
    void PrintSyntax() const override;
    void PrintCmd() const override;
    bool ReadParams(std::istream& rStrm_CmdList) override;
    bool ExecCmd(Set4GeomObjects& Scn) override;

    static AbstractInterp4Command* CreateCmd();

};

#endif
