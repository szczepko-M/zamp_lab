#ifndef INTERP4SET_HH
#define INTERP4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Set: public AbstractInterp4Command {
 public:
  Interp4Set();
  virtual void PrintSyntax() const override;
};

#endif
