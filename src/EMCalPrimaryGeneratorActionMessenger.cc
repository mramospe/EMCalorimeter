#include "EMCalPrimaryGeneratorActionMessenger.hh"
#include "EMCalEmissionEnergy.hh"

EMCalPrimaryGeneratorActionMessenger::
EMCalPrimaryGeneratorActionMessenger( EMCalPrimaryGeneratorAction *primaryGenAct ) :
  fPrimaryGeneratorAction( primaryGenAct ) {

  fEmissionDir = new G4UIdirectory( "/EMCal/emission/" );
  fEmissionDir -> SetGuidance( "Emission control" );

  fEmissionDirectionDir = new G4UIdirectory( "/EMCal/emission/direction/" );
  fEmissionDirectionDir -> SetGuidance( "Direction emission control" );

  fEmissionEnergyDir = new G4UIdirectory( "/EMCal/emission/energy/" );
  fEmissionEnergyDir -> SetGuidance( "Energy emission control" );

  fEnergyShapeCmd = new G4UIcmdWithAString( "/EMCal/emission/energy/setShape", this );
  fEnergyShapeCmd -> SetGuidance( "Select the shape of the energy emission" );
  fEnergyShapeCmd -> SetParameterName( "EnergyShape", false );
  fEnergyShapeCmd -> SetDefaultValue( "Point" );
  fEnergyShapeCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
}

EMCalPrimaryGeneratorActionMessenger::~EMCalPrimaryGeneratorActionMessenger() {

  delete fEmissionDir;
  delete fEmissionDirectionDir;
  delete fEmissionEnergyDir;
  delete fEnergyShapeCmd;
}

void EMCalPrimaryGeneratorActionMessenger::
SetNewValue( G4UIcommand *command, G4String value ) {

  if ( command == fEnergyShapeCmd )
    fPrimaryGeneratorAction -> SetEnergyShape( value );
}
