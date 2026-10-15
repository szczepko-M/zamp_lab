#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "AbstractInterp4Command.hh"

using namespace std;

#define PLUGIN_NAME__move "libInterp4Move.so"


int main()
{
  void *pLibHnd_Move = dlopen(PLUGIN_NAME__move,RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmdInterp_Move)(void);
  void *pFun;

  if (pLibHnd_Move) {
    cout << endl
	 << ":)  Wtyczka \"" << PLUGIN_NAME__move << "\" zostala poprawnie zaladowana."
	 << endl;
  } else {
     cerr << "!!! Brak wtyczki: " PLUGIN_NAME__move << endl;
     return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmdInterp");
  if (pFun) {
    cout  << ":)  Funkcja \"CreateCmdInterp\" zostala znaleziona we wtyczce "
	  << "\"" << PLUGIN_NAME__move << "\"." << endl;
  } else {
     cerr << "!!! Nie znaleziono funkcji CreateCmdInterp" << endl;
     return 1;
  }
  pCreateCmdInterp_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);


  AbstractInterp4Command *pInterp = pCreateCmdInterp_Move();

  cout << endl;
  pInterp->PrintSyntax();
  cout << endl;
  
  delete pInterp;

  dlclose(pLibHnd_Move);
}
