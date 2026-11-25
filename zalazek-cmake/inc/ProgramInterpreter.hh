#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH

#include "Set4LibInterfaces.hh"
#include "Set4GeomObjects.hh"
#include "ComChannel.hh"

class ProgramInterpreter{
    Set4LibInterfaces _LibManager;
    Set4GeomObjects _Scn;
    ComChannel _ComChannel;

    public:
        bool Init();
        bool ExecProgram(const char* FileName_Prog);
};



#endif