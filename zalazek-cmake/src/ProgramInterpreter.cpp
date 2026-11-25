// #include "Set4LibInterfaces.hh"
// #include "Set4GeomObjects.hh"
#include "ProgramInterpreter.hh"
//#include <stream>
#include <iostream>
#include <fstream>
#include <memory>
#include <fstream>
#include <string>
#include <thread>

using namespace std;

static const char *PluginNames[] = {
    "libInterp4Move.so",
    "libInterp4Rotate.so",
    "libInterp4Set.so",
    "libInterp4Pause.so"
};

bool ProgramInterpreter::Init(){
    for(const char *pName : PluginNames){
        if(!_LibManager.AddPlugin(pName)){
            return false;
        }
    }   
    return true;
}

bool ProgramInterpreter::ExecProgram(const char* FileName_Prog){

    // --- wczytanie wtyczek ---
    

    // --- zaczytanie pliku ---
    ifstream CmdFile(FileName_Prog);
    if (!CmdFile.is_open()) {
        _ComChannel.print_error("!!! Nie mozna otworzyc pliku: " + string(FileName_Prog));
        return false;
    }

    // --- część główna programu ---
    string CmdName;
    unsigned CmdNo = 0;

    while (CmdFile >> CmdName) {
        ++CmdNo; // odliczanie komendy z pliku .cmd

        // --- odszukanie wtyczki w bibliotece ---
        shared_ptr<LibInterface> pLib = _LibManager.FindPlugin(CmdName);
        if (!pLib) {
            _ComChannel.print_error("!!! Polecenie " + to_string(CmdNo) + ": brak wtyczki obsługujacej polecenie: " + string(CmdName));
            return false;
        }

        // --- utworzenie interpretera polecenia ---
        unique_ptr<AbstractInterp4Command> pInterp(pLib->CreateInterp());
        if (!pInterp) {
            _ComChannel.print_error("!!! Linia " + to_string(CmdNo) + ": nie udało sie utworzyć interpretera polecenia: " + string(CmdName));
            return false;
        }

        // --- odczytanie parametrów polecenia ---
        {
            lock_guard<ComChannel> Lock(_ComChannel);
            if (!pInterp->ReadParams(CmdFile)) {
                _ComChannel.print_error("!!! Linia " + to_string(CmdNo) + ": niewłasciwe parametry polecenia: " + string(CmdName) + ". Oczekiwana składnia:");
                pInterp->PrintSyntax();
                return false;
            }
        }

        // --- uzyskana, obrobiona komenda , która zostanie wykonana ---
        {
            lock_guard<ComChannel> Lock(_ComChannel);
            pInterp->PrintCmd();
        }
        

        // --- wykonanie obrobionego polecenia ---
        if (!pInterp->ExecCmd(_Scn, _ComChannel)) {
            cerr << "!!! Linia " << CmdNo << ": nieudane wykonanie polecenia "
                << CmdName << endl;
            return false;
        }
    }

    // --- sprawdzenie, czy koniec pliku ---
    if (!CmdFile.eof()) {
        cerr << "!!! Błąd odczytu pliku: " << FileName_Prog << endl;
        return false;
    }

    return true;
}

