#include "EMCalPhysicsList.hh"
#include "EMCalPhysicsListMessenger.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

EMCalPhysicsList::EMCalPhysicsList() : G4VModularPhysicsList() {

  fMessenger = new EMCalPhysicsListMessenger( this );
  
  // Sets the verbose level
  this -> SetVerboseLevel( 1 );
}

EMCalPhysicsList::~EMCalPhysicsList() { }


