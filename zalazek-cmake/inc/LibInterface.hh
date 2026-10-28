#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <string>
#include "AbstractInterp4Command.hh"

class LibInterface {
 public:
  typedef AbstractInterp4Command *(*CreateInterpFun)(void);

  explicit LibInterface(const std::string &LibName);

  ~LibInterface();

  LibInterface(const LibInterface &) = delete;
  LibInterface &operator=(const LibInterface &) = delete;

  const std::string &GetCmdName() const { return _CmdName; }

  AbstractInterp4Command *CreateInterp() const { return _pCreateInterp(); }

 private:
  void *_LibHandler = nullptr;
  std::string _CmdName;
  CreateInterpFun _pCreateInterp = nullptr;
};

#endif
