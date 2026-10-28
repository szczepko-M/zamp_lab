#include "LibInterface.hh"

#include <dlfcn.h>
#include <iostream>
#include <stdexcept>

using namespace std;

LibInterface::LibInterface(const string &LibName)
{
  _LibHandler = dlopen(LibName.c_str(), RTLD_LAZY);
  if (!_LibHandler) {
    const char *pErr = dlerror();
    throw runtime_error("Nie mozna zaladowac wtyczki \"" + LibName + "\": "
                        + (pErr ? pErr : "nieznany blad"));
  }

  void *pFun = dlsym(_LibHandler, "GetCmdName");
  if (!pFun) {
    dlclose(_LibHandler);
    _LibHandler = nullptr;
    throw runtime_error("We wtyczce \"" + LibName
                        + "\" nie znaleziono funkcji GetCmdName");
  }
  const char *(*pGetCmdName)(void) =
        reinterpret_cast<const char *(*)(void)>(pFun);
  _CmdName = pGetCmdName();

  pFun = dlsym(_LibHandler, "CreateCmdInterp");
  if (!pFun) {
    dlclose(_LibHandler);
    _LibHandler = nullptr;
    throw runtime_error("We wtyczce \"" + LibName
                        + "\" nie znaleziono funkcji CreateCmdInterp");
  }
  _pCreateInterp = reinterpret_cast<CreateInterpFun>(pFun);
}

LibInterface::~LibInterface()
{
  if (_LibHandler) dlclose(_LibHandler);
}
