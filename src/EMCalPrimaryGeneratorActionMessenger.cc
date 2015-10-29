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
//  Defines the messenger for the PrimaryGeneratorAction class. It implements    //
//  commands to control the emission direction and energy.                       //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#include "EMCalPrimaryGeneratorActionMessenger.hh"
#include "EMCalEmissionEnergy.hh"


//_______________________________________________________________________________
// Constructor
EMCalPrimaryGeneratorActionMessenger::
EMCalPrimaryGeneratorActionMessenger( EMCalPrimaryGeneratorAction *primaryGenAct ) :
  fPrimaryGeneratorAction( primaryGenAct ) {

  // Defines the emission directory
  fEmissionDir = new G4UIdirectory( "/EMCal/emission/" );
  fEmissionDir -> SetGuidance( "Emission control" );

  // Defines the emission direction directory
  fEmissionDirectionDir = new G4UIdirectory( "/EMCal/emission/direction/" );
  fEmissionDirectionDir -> SetGuidance( "Direction emission control" );

  // Defines the emission energy directory
  fEmissionEnergyDir = new G4UIdirectory( "/EMCal/emission/energy/" );
  fEmissionEnergyDir -> SetGuidance( "Energy emission control" );

  // Defines the commands to set the emission direction
  fEmissionDirectionMaxPhiCmd
    = new G4UIcmdWithADouble( "/EMCal/emission/direction/setMaxPhi", this );
  fEmissionDirectionMaxPhiCmd -> SetGuidance( "Select the minimum phi angle of the emission" );
  fEmissionDirectionMaxPhiCmd -> SetParameterName( "EmissionMaxPhi", false );
  fEmissionDirectionMaxPhiCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  fEmissionDirectionMaxThetaCmd
    = new G4UIcmdWithADouble( "/EMCal/emission/direction/setMaxTheta", this );
  fEmissionDirectionMaxThetaCmd -> SetGuidance( "Select the maximum phi angle of the emission" );
  fEmissionDirectionMaxThetaCmd -> SetParameterName( "EmissionMaxTheta", false );
  fEmissionDirectionMaxThetaCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  fEmissionDirectionMinPhiCmd
    = new G4UIcmdWithADouble( "/EMCal/emission/direction/setMinPhi", this );
  fEmissionDirectionMinPhiCmd -> SetGuidance( "Select the minimum phi angle of the emission" );
  fEmissionDirectionMinPhiCmd -> SetParameterName( "EmissionMinPhi", false );
  fEmissionDirectionMinPhiCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  fEmissionDirectionMinThetaCmd
    = new G4UIcmdWithADouble( "/EMCal/emission/direction/setMinTheta", this );
  fEmissionDirectionMinThetaCmd -> SetGuidance( "Select the maximum phi angle of the emission" );
  fEmissionDirectionMinThetaCmd -> SetParameterName( "EmissionMinTheta", false );
  fEmissionDirectionMinThetaCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  // Defines the command to set the energy shape of the emission
  fEnergyShapeCmd = new G4UIcmdWithAString( "/EMCal/emission/energy/setShape", this );
  fEnergyShapeCmd -> SetGuidance( "Select the shape of the energy emission" );
  fEnergyShapeCmd -> SetParameterName( "EnergyShape", false );
  fEnergyShapeCmd -> SetDefaultValue( "Point" );
  fEnergyShapeCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
}

//_______________________________________________________________________________
// Destructor
EMCalPrimaryGeneratorActionMessenger::~EMCalPrimaryGeneratorActionMessenger() {

  delete fEmissionDir;
  delete fEmissionDirectionDir;
  delete fEmissionEnergyDir;
  delete fEmissionDirectionMaxPhiCmd;
  delete fEmissionDirectionMaxThetaCmd;
  delete fEmissionDirectionMinPhiCmd;
  delete fEmissionDirectionMinThetaCmd;
  delete fEnergyShapeCmd;
}

//_______________________________________________________________________________
// Sets the value of one of the attributes
void EMCalPrimaryGeneratorActionMessenger::SetNewValue( G4UIcommand *command, G4String value ) {

  if      ( command == fEnergyShapeCmd )
    fPrimaryGeneratorAction -> SetEnergyShape( value );
  else if ( command == fEmissionDirectionMaxPhiCmd )
    fPrimaryGeneratorAction ->
      SetMaxPhi( fEmissionDirectionMaxPhiCmd -> GetNewDoubleValue( value ) );
  else if ( command == fEmissionDirectionMaxThetaCmd )
    fPrimaryGeneratorAction ->
      SetMaxTheta( fEmissionDirectionMaxThetaCmd -> GetNewDoubleValue( value ) );
  else if ( command == fEmissionDirectionMinPhiCmd )
    fPrimaryGeneratorAction ->
      SetMinPhi( fEmissionDirectionMinPhiCmd -> GetNewDoubleValue( value ) );
  else if ( command == fEmissionDirectionMinThetaCmd )
    fPrimaryGeneratorAction ->
      SetMinTheta( fEmissionDirectionMinThetaCmd -> GetNewDoubleValue( value ) );
  else
    G4cout << "WARNING: Command < " << command << " > not known" << G4endl;
}
