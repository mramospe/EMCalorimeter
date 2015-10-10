#ifndef EMCalEventActionMessenger_h
#define EMCalEventActionMessenger_h 1

#include "EMCalEventAction.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "globals.hh"

class EMCalEventActionMessenger: public G4UImessenger {

public:
  EMCalEventActionMessenger( EMCalEventAction *eventAction );
  ~EMCalEventActionMessenger();

  void SetNewValue( G4UIcommand *command, G4String value );

protected:
  EMCalEventAction     *fEventAction;
  G4UIdirectory        *fEventDir;
  G4UIcmdWithAnInteger *fPrintModuleCmd;

};

#endif
