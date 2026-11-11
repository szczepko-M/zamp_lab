#ifndef INTERP4PAUSE_HH
#define INTERP4PAUSE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Pause: public AbstractInterp4Command {

  int _Time = 0;

  public:
    Interp4Pause();

    void PrintSyntax() const override;
    void PrintCmd() const override;
    bool ReadParams(std::istream& rStrm_CmdList) override;
    bool ExecCmd(Set4GeomObjects& Scn) override;

    static AbstractInterp4Command* CreateCmd();
};

#endif
