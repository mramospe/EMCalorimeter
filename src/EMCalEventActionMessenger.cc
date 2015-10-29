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
//  Defines the messenger for the EventAction class, which has control of the    //
//  output print rate.                                                           //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#include "EMCalEventActionMessenger.hh"

//_______________________________________________________________________________
// Constructor
EMCalEventActionMessenger::EMCalEventActionMessenger( EMCalEventAction *eventAction ) :
  fEventAction( eventAction ) {

  fEventDir
    = new G4UIdirectory( "/EMCal/event/" );
  fEventDir -> SetGuidance( "Event control" );

  fPrintModuleCmd
    = new G4UIcmdWithAnInteger( "/EMCal/event/setPrintModule", this );
  fPrintModuleCmd
    -> SetGuidance( "Select the number of events to be reached for printing" );
  fPrintModuleCmd -> SetParameterName( "PrintModule", false );
  fPrintModuleCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

}

//_______________________________________________________________________________
// Destructor
EMCalEventActionMessenger::~EMCalEventActionMessenger() {

  delete fEventDir;
  delete fPrintModuleCmd;
}

//_______________________________________________________________________________
// Modifies one attribute of the EventAction class
void EMCalEventActionMessenger::SetNewValue( G4UIcommand *command, G4String value ) {

  if ( command == fPrintModuleCmd )
    fEventAction -> SetPrintModule( fPrintModuleCmd -> GetNewIntValue( value ) );
}
