///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
//                                                                               //
//  AUTHOR: Miguel Ramos Pernas                                                  //
//  e-mail: miguel.ramos.pernas@cern.ch                                          //
//                                                                               //
//  Last update: 29/10/2015                                                      //
//                                                                               //
// ----------------------------------------------------------------------------- //
//                                                                               //
//  Description:                                                                 //
//                                                                               //
//  Defines the PrimaryGeneratorAction class. This class generates the events    //
//  of the simulation, specifying the energy shape, emission direction and type  //
//  of particle.                                                                 //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#ifndef EMCalPrimaryGeneratorActionMessenger_h
#define EMCalPrimaryGeneratorActionMessenger_h 1

#include "EMCalPrimaryGeneratorAction.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"


//_______________________________________________________________________________

class EMCalPrimaryGeneratorActionMessenger: public G4UImessenger {

public:
  
  // Constructor and destructor
  EMCalPrimaryGeneratorActionMessenger( EMCalPrimaryGeneratorAction *primaryGenAct );
  ~EMCalPrimaryGeneratorActionMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String value );

protected:

  // Attributes
  EMCalPrimaryGeneratorAction *fPrimaryGeneratorAction;
  G4UIdirectory               *fEmissionDir;
  G4UIdirectory               *fEmissionDirectionDir;
  G4UIdirectory               *fEmissionEnergyDir;
  G4UIcmdWithAString          *fEnergyShapeCmd;
  G4UIcmdWithAString          *fEmissionDirectionCmd;
  G4UIcmdWithADouble          *fEmissionDirectionMaxPhiCmd;
  G4UIcmdWithADouble          *fEmissionDirectionMaxThetaCmd;
  G4UIcmdWithADouble          *fEmissionDirectionMinPhiCmd;
  G4UIcmdWithADouble          *fEmissionDirectionMinThetaCmd;
};

#endif
