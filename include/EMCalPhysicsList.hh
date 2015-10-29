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
//  Defines the class EMCalModule. The detector is composed by a number of this  //
//  modules, which have two parts, an active part and a shower-generator volume  //
//  ( SGV ).                                                                     //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#ifndef EMCalPhysicsList_h
#define EMCalPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmDNAPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmLivermorePolarizedPhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "globals.hh"


//_______________________________________________________________________________

class EMCalPhysicsListMessenger;

class EMCalPhysicsList: public G4VModularPhysicsList {

public:

  // Constructor and destructor
  EMCalPhysicsList();
  ~EMCalPhysicsList();

  // Methods
  inline void EnableDecay();
  inline void EnableEmDNA();
  inline void EnableEmExtra();
  inline void EnableLivermore();
  inline void EnableLivermorePolarized();
  inline void EnablePenelope();
  inline void EnableEmStandard();
  inline void EnableEmStandardOpt1();
  inline void EnableEmStandardOpt2();
  inline void EnableEmStandardOpt3();
  inline void EnableRadioactiveDecay();

protected:
  
  // Attributes
  EMCalPhysicsListMessenger *fMessenger;
};

// This functions anable the different physics libraries of Geant4
inline void EMCalPhysicsList::EnableDecay() {
  this -> RegisterPhysics( new G4DecayPhysics );
}
inline void EMCalPhysicsList::EnableEmDNA() {
  this -> RegisterPhysics( new G4EmDNAPhysics );
}
inline void EMCalPhysicsList::EnableEmExtra() {
  this -> RegisterPhysics( new G4EmExtraPhysics );
}
inline void EMCalPhysicsList::EnableLivermore() {
  this -> RegisterPhysics( new G4EmLivermorePhysics );
}
inline void EMCalPhysicsList::EnableLivermorePolarized() {
  this -> RegisterPhysics( new G4EmLivermorePolarizedPhysics );
}
inline void EMCalPhysicsList::EnablePenelope() {
  this -> RegisterPhysics( new G4EmPenelopePhysics );
}
inline void EMCalPhysicsList::EnableEmStandard() {
  this -> RegisterPhysics( new G4EmStandardPhysics );
}
inline void EMCalPhysicsList::EnableEmStandardOpt1() {
  this -> RegisterPhysics( new G4EmStandardPhysics_option1 );
}
inline void EMCalPhysicsList::EnableEmStandardOpt2() {
  this -> RegisterPhysics( new G4EmStandardPhysics_option2 );
}
inline void EMCalPhysicsList::EnableEmStandardOpt3() {
  this -> RegisterPhysics( new G4EmStandardPhysics_option3 );
}
inline void EMCalPhysicsList::EnableRadioactiveDecay() {
  this -> RegisterPhysics( new G4RadioactiveDecayPhysics );
}

#endif
