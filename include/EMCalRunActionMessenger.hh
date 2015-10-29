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
//  Defines the messenger for the RunAction class. It implements the options to  //
//  change the output file and tree for the run.                                 //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#ifndef EMCalRunActionMessenger_h
#define EMCalRunActionMessenger_h 1

#include "EMCalRunAction.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "globals.hh"


//_______________________________________________________________________________

class EMCalRunActionMessenger: public G4UImessenger {

public:

  // Constructor and destructor
  EMCalRunActionMessenger( EMCalRunAction *run );
  ~EMCalRunActionMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String value );

protected:

  // Attributes
  EMCalRunAction     *fRunAction;
  G4UIdirectory      *fRunDir;
  G4UIcmdWithAString *fOutputFileNameCmd;
  G4UIcmdWithAString *fOutputTreeNameCmd;
};

#endif
