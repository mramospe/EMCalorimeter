
#include "EMCalEventAction.hh"
#include "EMCalEventActionMessenger.hh"
#include "EMCalRun.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include <iomanip>

EMCalEventAction::EMCalEventAction() :
  G4UserEventAction(), fPrintModule( 1 ) {

  fMessenger = new EMCalEventActionMessenger( this );
} 

EMCalEventAction::~EMCalEventAction() { delete fMessenger; }

void EMCalEventAction::BeginOfEventAction( const G4Event* ) {

  // Restarts the values of the energy for all the modules
  EMCalRun *run 
    = static_cast<EMCalRun*>( G4RunManager::GetRunManager() -> 
			      GetNonConstCurrentRun() );

  run -> Reset();
}

void EMCalEventAction::EndOfEventAction( const G4Event *event ) {

  // Finally fills the tree with the values
  EMCalRun *run 
    = static_cast<EMCalRun*>( G4RunManager::GetRunManager() -> 
			      GetNonConstCurrentRun() );

  // Gets the number of the event and passes it to the RunManager
  G4int evtNb = event -> GetEventID();
  run -> Fill( evtNb );

  if ( evtNb % fPrintModule == 0 ) {

    G4cout << std::setfill( '-' ) << std::setw( 30 ) << G4endl;
    G4cout << " Events processed: " << evtNb << G4endl;
    CLHEP::HepRandom::showEngineStatus();
    G4cout << std::setfill( '-' ) << std::setw( 30 ) << G4endl;
  }
}
