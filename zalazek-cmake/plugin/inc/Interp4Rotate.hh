#ifndef INTERP4ROTATE_HH
#define INTERP4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Rotate: public AbstractInterp4Command {
 public:
  Interp4Rotate();
  virtual void PrintSyntax() const override;
};

#endif
