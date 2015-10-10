#ifndef EMCalEventAction_h
#define EMCalEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "TTree.h"

class EMCalEventActionMessenger;

class EMCalEventAction : public G4UserEventAction {

public:
  EMCalEventAction();
  virtual ~EMCalEventAction();
    
  virtual void BeginOfEventAction( const G4Event* event );
  virtual void EndOfEventAction( const G4Event* event );
  inline  void SetPrintModule( G4int printModule );

protected:
  EMCalEventActionMessenger *fMessenger;
  G4int                      fPrintModule;

};

void inline EMCalEventAction::SetPrintModule( G4int printModule ) {
  fPrintModule = printModule;
}

#endif

    
