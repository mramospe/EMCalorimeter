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
//  Defines the EventAction class for the EMCalActionInitialization. This class  //
//  modifies RunAction to be reset each time an event finalizes. It controls     //
//  the output print rate and the information displayed.                         //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#include "EMCalEventAction.hh"
#include "EMCalEventActionMessenger.hh"
#include "EMCalRun.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include <iomanip>


//_______________________________________________________________________________
// Constructor
EMCalEventAction::EMCalEventAction() :
  G4UserEventAction(), fPrintModule( 1 ) {

  fMessenger = new EMCalEventActionMessenger( this );
} 

//_______________________________________________________________________________
// Destructor
EMCalEventAction::~EMCalEventAction() { delete fMessenger; }

//_______________________________________________________________________________
// All the functions that are called each time an event starts
void EMCalEventAction::BeginOfEventAction( const G4Event* ) {

  // Restarts the values of the energy for all the modules
  EMCalRun *run 
    = static_cast<EMCalRun*>( G4RunManager::GetRunManager() -> 
			      GetNonConstCurrentRun() );
  run -> Reset();
}

//_______________________________________________________________________________
// All the functions that are called each time an event ends
void EMCalEventAction::EndOfEventAction( const G4Event *event ) {

  // Gets the current run
  EMCalRun *run 
    = static_cast<EMCalRun*>( G4RunManager::GetRunManager() -> 
			      GetNonConstCurrentRun() );

  // Gets the number of the event and passes it to the EMCalRun class
  G4int evtNb = event -> GetEventID();
  run -> Fill( evtNb );

  if ( evtNb % fPrintModule == 0 ) {

    G4cout << " ================================================="   << G4endl;
    G4cout << " Events processed: " << evtNb << G4endl;
    CLHEP::HepRandom::showEngineStatus();
    G4cout << " =================================================\n" << G4endl;
  }
}
