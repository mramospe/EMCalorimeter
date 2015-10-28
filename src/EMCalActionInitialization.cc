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
//  Defines the ActionInitialization class for the EMCalorimeter application,    //
//  which generates the PrimaryGeneratorAction, RunAction, EventAction and       //
//  SteppingAction.                                                              //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#include "EMCalActionInitialization.hh"
#include "EMCalPrimaryGeneratorAction.hh"
#include "EMCalRunAction.hh"
#include "EMCalEventAction.hh"
#include "EMCalSteppingAction.hh"


//_______________________________________________________________________________
// Constructor
EMCalActionInitialization::EMCalActionInitialization() : G4VUserActionInitialization() { }

//_______________________________________________________________________________
// Destructor
EMCalActionInitialization::~EMCalActionInitialization() { }

//_______________________________________________________________________________
// Builds the action for master
void EMCalActionInitialization::BuildForMaster() const { SetUserAction(new EMCalRunAction); }

//_______________________________________________________________________________
// Initializes the different action classes
void EMCalActionInitialization::Build() const {

  SetUserAction( new EMCalPrimaryGeneratorAction );
  SetUserAction( new EMCalRunAction );
  
  EMCalEventAction* eventAction = new EMCalEventAction;
  SetUserAction( eventAction );

  SetUserAction( new EMCalSteppingAction( eventAction ) );
}
