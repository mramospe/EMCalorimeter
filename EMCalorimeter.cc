#include "EMCalDetectorConstruction.hh"
#include "EMCalActionInitialization.hh"
#include "EMCalPhysicsList.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

#include <ctime>

int main( int argc, char **argv ) {

  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive *ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive( argc, argv );
  }

  // Choose the Random engine
  G4Random::setTheEngine( new CLHEP::RanecuEngine );
  G4Random::setTheSeed( time( 0 ) );

  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager *runManager = new G4MTRunManager;
#else
  G4RunManager *runManager = new G4RunManager;
#endif

  // Get the pointer to the User Interface manager
  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager -> SetUserInitialization( new EMCalDetectorConstruction );

  // Physics list
  EMCalPhysicsList *physics_list = new EMCalPhysicsList;
  UImanager -> ApplyCommand( "/control/execute physics_lists.mac" );
  runManager -> SetUserInitialization( physics_list );
    
  // User action initialization
  runManager -> SetUserInitialization( new EMCalActionInitialization );
  
  // Initialize visualization
  G4VisManager *visManager = new G4VisExecutive;
  visManager -> Initialize();

  // Process macro or start UI session
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager -> ApplyCommand( command + fileName );
  }
  else { 
    // interactive mode
    UImanager -> ApplyCommand( "/control/execute init_vis.mac" );
    ui -> SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !

#ifdef G4VIS_USE  
  delete visManager;
#endif
  delete runManager;
}
