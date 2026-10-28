#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include <map>
#include <memory>
#include <string>
#include "LibInterface.hh"

class Set4LibInterfaces
  : public std::map<std::string, std::shared_ptr<LibInterface>> {
 public:
  bool AddPlugin(const std::string &LibName);

  std::shared_ptr<LibInterface> FindPlugin(const std::string &CmdName) const;
};

#endif
