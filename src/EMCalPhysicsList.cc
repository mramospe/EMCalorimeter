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
//  Defines the class to manage the physics libraries of Geant4. This class is   //
//  initialized in the main function.                                            //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#include "EMCalPhysicsList.hh"
#include "EMCalPhysicsListMessenger.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"


//_______________________________________________________________________________
// Constructor
EMCalPhysicsList::EMCalPhysicsList() : G4VModularPhysicsList() {

  fMessenger = new EMCalPhysicsListMessenger( this );
  
  // Sets the verbose level
  this -> SetVerboseLevel( 1 );
}

//_______________________________________________________________________________
// Destructor
EMCalPhysicsList::~EMCalPhysicsList() { }


