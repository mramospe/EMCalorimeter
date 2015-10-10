#ifndef EMCalPrimaryGeneratorActionMessenger_h
#define EMCalPrimaryGeneratorActionMessenger_h 1

#include "EMCalPrimaryGeneratorAction.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "globals.hh"

class EMCalPrimaryGeneratorActionMessenger: public G4UImessenger {

public:
  EMCalPrimaryGeneratorActionMessenger( EMCalPrimaryGeneratorAction *primaryGenAct );
  ~EMCalPrimaryGeneratorActionMessenger();

  void SetNewValue( G4UIcommand *command, G4String value );

protected:
  EMCalPrimaryGeneratorAction *fPrimaryGeneratorAction;
  G4UIdirectory               *fEmissionDir;
  G4UIdirectory               *fEmissionDirectionDir;
  G4UIdirectory               *fEmissionEnergyDir;
  G4UIcmdWithAString          *fEnergyShapeCmd;
};

#endif
