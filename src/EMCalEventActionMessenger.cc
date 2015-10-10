#include "EMCalEventActionMessenger.hh"

EMCalEventActionMessenger::
EMCalEventActionMessenger( EMCalEventAction *eventAction ) :
  fEventAction( eventAction ) {

  fEventDir
    = new G4UIdirectory( "/EMCal/event" );
  fEventDir -> SetGuidance( "Event control" );

  fPrintModuleCmd
    = new G4UIcmdWithAnInteger( "/EMCal/event/setPrintModule", this );
  fPrintModuleCmd
    -> SetGuidance( "Select the number of events to be reached for printing" );
  fPrintModuleCmd -> SetParameterName( "PrintModule", false );
  fPrintModuleCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

}

EMCalEventActionMessenger::~EMCalEventActionMessenger() {

  delete fEventDir;
  delete fPrintModuleCmd;
}

void EMCalEventActionMessenger::SetNewValue( G4UIcommand *command, G4String value ) {

  if ( command == fPrintModuleCmd )
    fEventAction -> SetPrintModule( fPrintModuleCmd -> GetNewIntValue( value ) );
}
