///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
//                                                                               //
//  AUTHOR: Miguel Ramos Pernas                                                  //
//  e-mail: miguel.ramos.pernas@cern.ch                                          //
//                                                                               //
//  Last update: 26/10/2015                                                      //
//                                                                               //
// ----------------------------------------------------------------------------- //
//                                                                               //
//  Description:                                                                 //
//                                                                               //
//  Defines the messenger to manage the physics used in the simulation. It is    //
//  designed to enable the libraries specified in the configuration file.        //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#ifndef EMCalPhysicsListMessenger_h
#define EMCalPhysicsListMessenger_h 1

#include "EMCalPhysicsList.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "globals.hh"


//_______________________________________________________________________________

class EMCalPhysicsListMessenger: public G4UImessenger {

public:

  // Constructor and destructor
  EMCalPhysicsListMessenger( EMCalPhysicsList *physicsList );
  ~EMCalPhysicsListMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String );

protected:

  // Attributes
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
