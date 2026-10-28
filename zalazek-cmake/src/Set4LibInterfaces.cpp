#include "Set4LibInterfaces.hh"

#include <iostream>
#include <stdexcept>

using namespace std;

bool Set4LibInterfaces::AddPlugin(const string &LibName)
{
  shared_ptr<LibInterface> pLib;

  try {
    pLib = make_shared<LibInterface>(LibName);
  } catch (const exception &e) {
    cerr << "!!! " << e.what() << endl;
    return false;
  }

  if (find(pLib->GetCmdName()) != end()) {
    cerr << "!!! Polecenie \"" << pLib->GetCmdName()
         << "\" jest juz obslugiwane przez inna wtyczke (odrzucono \""
         << LibName << "\")." << endl;
    return false;
  }

  (*this)[pLib->GetCmdName()] = pLib;
  return true;
}

shared_ptr<LibInterface> Set4LibInterfaces::FindPlugin(const string &CmdName) const
{
  const_iterator it = find(CmdName);
  if (it == end()) return shared_ptr<LibInterface>();
  return it->second;
}
