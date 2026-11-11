#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH

#include "Set4LibInterfaces.hh"
#include "Set4GeomObjects.hh"

class ProgramInterpreter{
    Set4LibInterfaces _LibManager;
    Set4GeomObjects _Scn;

    public:
        bool ExecProgram(const char* FileName_Prog);
        
};



#endif