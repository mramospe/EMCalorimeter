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
//  Defines the messenger for the RunAction class. It implements the options to  //
//  change the output file and tree for the run.                                 //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#include "EMCalRunActionMessenger.hh"


//_______________________________________________________________________________
// Constructor
EMCalRunActionMessenger::EMCalRunActionMessenger( EMCalRunAction *run ) :
  fRunAction( run ) {

  fRunDir = new G4UIdirectory( "/EMCal/run/" );
  fRunDir -> SetGuidance( "Run control" );

  fOutputFileNameCmd
    = new G4UIcmdWithAString( "/EMCal/run/setFileName", this );
  fOutputFileNameCmd -> SetGuidance( "Select the output file name" );
  fOutputFileNameCmd -> SetParameterName( "OutputFileName", false );
  fOutputFileNameCmd -> SetDefaultValue( "EMCalorimeter_Results.root" );
  fOutputFileNameCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  fOutputTreeNameCmd
    = new G4UIcmdWithAString( "/EMCal/run/setTreeName", this );
  fOutputTreeNameCmd -> SetGuidance( "Select the output file name" );
  fOutputTreeNameCmd -> SetParameterName( "OutputTreeName", false );
  fOutputTreeNameCmd -> SetDefaultValue( "DecayTree" );
  fOutputTreeNameCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
}

//_______________________________________________________________________________
// Destructor
EMCalRunActionMessenger::~EMCalRunActionMessenger() {

  delete fRunDir;
  delete fOutputFileNameCmd;
  delete fOutputTreeNameCmd;
}

//_______________________________________________________________________________
// Sets the name of the new file or tree
void EMCalRunActionMessenger::SetNewValue( G4UIcommand *command, G4String value ) {

  if      ( command == fOutputFileNameCmd )
    fRunAction -> CreateNewFile( value );
  else if ( command == fOutputTreeNameCmd )
    fRunAction -> SetOutputTreeName( value );
}
