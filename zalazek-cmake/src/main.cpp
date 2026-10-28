#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "AbstractInterp4Command.hh"
#include "Set4LibInterfaces.hh"

using namespace std;

static const char *PluginNames[] = {
  "libInterp4Move.so",
  "libInterp4Rotate.so",
  "libInterp4Set.so",
  "libInterp4Pause.so"
};

static const char *DefaultCmdFile = "opis_dzialan.cmd";

bool ReadAndPrintSyntaxes(const string &FileName, const Set4LibInterfaces &Plugins)
{
  ifstream CmdFile(FileName);
  if (!CmdFile.is_open()) {
    cerr << "!!! Nie mozna otworzyc pliku: " << FileName << endl;
    return false;
  }

  string CmdName;
  while (CmdFile >> CmdName) {
    shared_ptr<LibInterface> pLib = Plugins.FindPlugin(CmdName);
    if (!pLib) {
      cerr << "!!! Brak wtyczki obslugujacej polecenie: " << CmdName << endl;
      return false;
    }

    unique_ptr<AbstractInterp4Command> pInterp(pLib->CreateInterp());
    if (!pInterp) {
      cerr << "!!! Nie udalo sie utworzyc interpretera polecenia: "
           << CmdName << endl;
      return false;
    }

    pInterp->PrintSyntax();
  }

  // Petla konczy sie przy braku kolejnego slowa: to koniec pliku (sukces)
  // albo blad odczytu.
  if (!CmdFile.eof()) {
    cerr << "!!! Blad odczytu pliku: " << FileName << endl;
    return false;
  }
  return true;
}

int main(int argc, char **argv)
{
  const string CmdFileName = (argc > 1) ? argv[1] : DefaultCmdFile;

  Set4LibInterfaces Plugins;

  for (const char *pName : PluginNames) {
    if (!Plugins.AddPlugin(pName)) return 1;
    cout << ":)  Wtyczka \"" << pName << "\" zostala poprawnie zaladowana." << endl;
  }
  cout << endl;

  if (!ReadAndPrintSyntaxes(CmdFileName, Plugins)) return 1;

  return 0;
}
