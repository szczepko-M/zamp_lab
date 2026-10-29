#ifndef ABSTRACTINTERP4COMMAND_HH
#define ABSTRACTINTERP4COMMAND_HH

class AbstractInterp4Command {
 public:
  virtual ~AbstractInterp4Command() {}
  virtual void PrintSyntax() const = 0;
  // virtual bool ReadParams()
};

#endif
