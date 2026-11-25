#include <iostream>
#include <fstream>
#include <memory>
#include <string>
//#include "AbstractInterp4Command.hh"
//#include "Set4LibInterfaces.hh"
#include "ProgramInterpreter.hh"
#include <functional>
#include <thread>

using namespace std;

static const char *DefaultCmdFile_1 = "../zalazek-cmake/opis_dzialan_1.cmd";
static const char *DefaultCmdFile_2 = "../zalazek-cmake/opis_dzialan_2.cmd";

// --- funkcja do thread'a ---
static void RunProgram(ProgramInterpreter &Interp, const char* cmdfilename, bool &result){
    result = Interp.ExecProgram(cmdfilename);
}

int main(int argc, char **argv){
  const char* CmdFileName_1 = (argc > 2) ? argv[1] : DefaultCmdFile_1;
  const char* CmdFileName_2 = (argc > 2) ? argv[2] : DefaultCmdFile_2;

  ProgramInterpreter prog_interp;

  if(!prog_interp.Init()){
    return 1;
  }

  bool prog_OK_1 = false;
  bool prog_OK_2 = false;

  thread Th_1(RunProgram, ref(prog_interp), CmdFileName_1, ref(prog_OK_1));
  thread Th_2(RunProgram, ref(prog_interp), CmdFileName_2, ref(prog_OK_2));

  Th_1.join();
  Th_2.join();

  cout << "Thread 1: " << prog_OK_1 << endl;
  cout << "Thread_2: " << prog_OK_2 << endl;

  bool final_result = (prog_OK_1 && prog_OK_2) ? 0 : 1;

  return final_result;
}
