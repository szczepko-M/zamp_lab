#ifndef INTERP4MOVE_HH
#define INTERP4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Move: public AbstractInterp4Command {
 public:
  Interp4Move();
  virtual void PrintSyntax() const override;
};

#endif
