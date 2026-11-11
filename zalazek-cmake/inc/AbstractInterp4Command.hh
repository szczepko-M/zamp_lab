#ifndef ABSTRACTINTERP4COMMAND_HH
#define ABSTRACTINTERP4COMMAND_HH

#include <iosfwd>

class Set4GeomObjects;

class AbstractInterp4Command {
 public:
  virtual ~AbstractInterp4Command() {}

  virtual void PrintSyntax() const = 0;
  virtual void PrintCmd() const = 0;
  virtual bool ReadParams(std::istream& rStrm_CmdList) = 0;
  virtual bool ExecCmd(Set4GeomObjects& Scn) = 0;
};

#endif
