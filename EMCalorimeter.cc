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
//  This is the main c++ file to execute the EMCalorimeter application. Physics  //
//  list, detector construction and user initialization are declared here, as    //
//  well as the UI messenger.                                                    //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


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


//_______________________________________________________________________________

int main( int argc, char **argv ) {

  // Detects interactive mode ( if no arguments)  and defines UI session
  G4UIExecutive *ui( 0 );
  if ( argc == 1 ) {
    ui = new G4UIExecutive( argc, argv );
  }

  // Sets the Random engine. The seed is set from the time library
  G4Random::setTheEngine( new CLHEP::RanecuEngine );
  G4Random::setTheSeed( time( 0 ) );

  // Constructs the default run manager
#ifdef G4MULTITHREADED
  G4MTRunManager *runManager = new G4MTRunManager;
#else
  G4RunManager *runManager = new G4RunManager;
#endif

  // Get the pointer to the User Interface manager
  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  // Calls to the detector construction
  runManager -> SetUserInitialization( new EMCalDetectorConstruction );

  // Sets the physics list. This list has to be loaded befor the action initialization,
  // so physics can not be changed during the execution of the program ( once the kernel
  // is initialised ). To modify the physics of the simulation one has to change the 
  // < physics_list.mac > file.
  EMCalPhysicsList *physics_list = new EMCalPhysicsList;
  UImanager -> ApplyCommand( "/control/execute physics_lists.mac" );
  runManager -> SetUserInitialization( physics_list );
    
  // User action initialization
  runManager -> SetUserInitialization( new EMCalActionInitialization );
  
  // Initializes visualization
  G4VisManager *visManager = new G4VisExecutive;
  visManager -> Initialize();

  // Process macro or start UI session
  if ( ! ui ) { 
    // Batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager -> ApplyCommand( command + fileName );
  }
  else { 
    // Interactive mode
    UImanager -> ApplyCommand( "/control/execute init_vis.mac" );
    ui -> SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main program.

#ifdef G4VIS_USE  
  delete visManager;
#endif
  delete runManager;
}
