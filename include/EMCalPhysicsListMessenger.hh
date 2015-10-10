#ifndef EMCalPhysicsListMessenger_h
#define EMCalPhysicsListMessenger_h 1

#include "EMCalPhysicsList.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "globals.hh"

class EMCalPhysicsListMessenger: public G4UImessenger {

public:
  EMCalPhysicsListMessenger( EMCalPhysicsList *physicsList );
  ~EMCalPhysicsListMessenger();

  void SetNewValue( G4UIcommand *command, G4String );

protected:
  EMCalPhysicsList        *fPhysicsList;
  G4UIdirectory           *fPhysicsDir;
  G4UIcmdWithoutParameter *fDecayCmd;
  G4UIcmdWithoutParameter *fEmDNACmd;
  G4UIcmdWithoutParameter *fEmExtraCmd;
  G4UIcmdWithoutParameter *fLivermoreCmd;
  G4UIcmdWithoutParameter *fLivermorePolarizedCmd;
  G4UIcmdWithoutParameter *fPenelopeCmd;
  G4UIcmdWithoutParameter *fEmStandardCmd;
  G4UIcmdWithoutParameter *fEmStandardOpt1Cmd;
  G4UIcmdWithoutParameter *fEmStandardOpt2Cmd;
  G4UIcmdWithoutParameter *fEmStandardOpt3Cmd;
  G4UIcmdWithoutParameter *fRadioactiveDecayCmd;

};

#endif
