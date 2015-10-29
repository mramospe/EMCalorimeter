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


#ifndef EMCalEventAction_h
#define EMCalEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "TTree.h"


//_______________________________________________________________________________

class EMCalEventActionMessenger;

class EMCalEventAction : public G4UserEventAction {

public:

  // Constructor and destructor
  EMCalEventAction();
  virtual ~EMCalEventAction();
    
  // Methods
  virtual void BeginOfEventAction( const G4Event* event );
  virtual void EndOfEventAction( const G4Event* event );
  inline  void SetPrintModule( G4int printModule );

protected:
  
  // Attributes
  EMCalEventActionMessenger *fMessenger;
  G4int                      fPrintModule;

};

void inline EMCalEventAction::SetPrintModule( G4int printModule ) {
  fPrintModule = printModule;
}

#endif

    
