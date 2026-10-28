#ifndef INTERP4PAUSE_HH
#define INTERP4PAUSE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "AbstractInterp4Command.hh"

class Interp4Pause: public AbstractInterp4Command {
 public:
  Interp4Pause();
  virtual void PrintSyntax() const override;
};

#endif
