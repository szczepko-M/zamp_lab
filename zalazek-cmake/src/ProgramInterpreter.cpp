// #include "Set4LibInterfaces.hh"
// #include "Set4GeomObjects.hh"
#include "ProgramInterpreter.hh"
//#include <stream>
#include <iostream>
#include <sstream>
#include <memory>
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
        if(!_LibManager.AddPlugin(pName)){
            return false;
        }
        
        // cout << ":) Wtyczka \"" << pName << "\" została zaczytana poprawnie" << endl;
    }

    // --- zaczytanie pliku ---
    ifstream CmdFile(FileName_Prog);
    if (!CmdFile.is_open()) {
        cerr << "!!! Nie mozna otworzyc pliku: " << FileName_Prog << endl;
        return false;
    }

    // --- część główna programu ---
    string Line;
    unsigned LineNo = 0;

    while (getline(CmdFile, Line)) {
        ++LineNo; // odliczanie linii z pliku .cmd
        if (!Line.empty() && Line.back() == '\r') Line.pop_back(); //usunięcie znaków \r

        istringstream LineStrm(Line);
        string CmdName;
        if (!(LineStrm >> CmdName)) continue; //przypadek pustej linii

        // --- odszukanie wtyczki w bibliotece ---
        shared_ptr<LibInterface> pLib = _LibManager.FindPlugin(CmdName);
        if (!pLib) {
            cerr << "!!! Linia " << LineNo << ": brak wtyczki obsługujacej polecenie: "
                << CmdName << endl;
            return false;
        }

        // --- utworzenie interpretera polecenia ---
        unique_ptr<AbstractInterp4Command> pInterp(pLib->CreateInterp());
        if (!pInterp) {
            cerr << "!!! Linia " << LineNo << ": nie udało sie utworzyć interpretera polecenia: "
                << CmdName << endl;
            return false;
        }

        // --- odczytanie parametrów polecenia ---
        if (!pInterp->ReadParams(LineStrm)) {
            cerr << "!!! Linia " << LineNo << ": niewłasciwe parametry polecenia "
                << CmdName << ". Oczekiwana składnia:" << endl;
            pInterp->PrintSyntax();
            return false;
        }

        // --- opcjonalne, jeśli jest dodatkowy parametr ---
        string Extra;
        if (LineStrm >> Extra) {
            cerr << "!!! Linia " << LineNo << ": nadmiarowy parametr \"" << Extra
                << "\" w poleceniu " << CmdName << ". Oczekiwana składnia:" << endl;
            pInterp->PrintSyntax();
            return false;
        }

        // --- uzyskana, obrobiona komenda , która zostanie wykonana ---
        pInterp->PrintCmd();

        // --- wykonanie obrobionego polecenia ---
        if (!pInterp->ExecCmd(_Scn)) {
            cerr << "!!! Linia " << LineNo << ": nieudane wykonanie polecenia "
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