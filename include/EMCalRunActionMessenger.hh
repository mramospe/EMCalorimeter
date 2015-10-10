#ifndef EMCalRunActionMessenger_h
#define EMCalRunActionMessenger_h 1

#include "EMCalRunAction.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "globals.hh"

class EMCalRunActionMessenger: public G4UImessenger {

public:
  EMCalRunActionMessenger( EMCalRunAction *run );
  ~EMCalRunActionMessenger();

  void SetNewValue( G4UIcommand *command, G4String value );

protected:
  EMCalRunAction     *fRunAction;
  G4UIdirectory      *fRunDir;
  G4UIcmdWithAString *fOutputFileNameCmd;
  G4UIcmdWithAString *fOutputTreeNameCmd;

};

#endif
