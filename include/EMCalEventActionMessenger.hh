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
//  Defines the messenger for the EventAction class, which has control of the    //
//  output print rate.                                                           //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#ifndef EMCalEventActionMessenger_h
#define EMCalEventActionMessenger_h 1

#include "EMCalEventAction.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "globals.hh"


//_______________________________________________________________________________

class EMCalEventActionMessenger: public G4UImessenger {

public:

  // Constructor and destructor
  EMCalEventActionMessenger( EMCalEventAction *eventAction );
  ~EMCalEventActionMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String value );

protected:

  // Attributes
  EMCalEventAction     *fEventAction;
  G4UIdirectory        *fEventDir;
  G4UIcmdWithAnInteger *fPrintModuleCmd;

};

#endif
