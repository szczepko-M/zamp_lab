// #include "Set4LibInterfaces.hh"
// #include "Set4GeomObjects.hh"
#include "ProgramInterpreter.hh"
//#include <stream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static const char *PluginNames[] = {
    "libInterp4Move.so",
    "libInterp4Rotate.so",
    "libInterp4Set.so",
    "libInterp4Pause.so"
};

bool ProgramInterpreter::ExecProgram(const char* FileName_Prog){

    // --- wczytanie wtyczek ---
    for(const char *pName : PluginNames){
        if(!_LibManager.AddPlugin(pName)) return 1;
        std::cout << ":) Wtyczka \"" << pName << "\"zaczytana poprawnie" << std::endl;
    }

    // --- zaczytanie pliku ---
    ifstream CmdFile(FileName_Prog);
    if (!CmdFile.is_open()) {
        cerr << "!!! Nie mozna otworzyc pliku: " << FileName_Prog << endl;
        return false;
    }

    // --- część główna programu ---
    string CmdName;
    while (CmdFile >> CmdName) {

        // --- odnalezienie wtyczki ---
        shared_ptr<LibInterface> pLib = _LibManager.FindPlugin(CmdName);
        if (!pLib) {
            cerr << "!!! Brak wtyczki obslugujacej polecenie: " << CmdName << endl;
            return false;
        }

        // --- stworzenie interpretera ---
        unique_ptr<AbstractInterp4Command> pInterp(pLib->CreateInterp());
        if (!pInterp) {
            cerr << "!!! Nie udalo sie utworzyc interpretera polecenia: "
            << CmdName << endl;
            return false;
        }

        //pInterp->PrintSyntax();

        // --- odczytanie parametrów polecenia ---
        if(!pInterp->ReadParams(CmdFile)){
            cerr << "!!! Niewłaściwe parametry wywołania " << CmdName << endl;
            return false;
        }

        pInterp->PrintCmd();

        if(!pInterp->ExecCmd(_Scn)){
            cerr << "!!! Nieudane wykonanie" << CmdName << endl;
            return false;
        }
    }

    if (!CmdFile.eof()) {
        cerr << "!!! Blad odczytu pliku: " << FileName_Prog << endl;
        return false;
    }

    return true;
}