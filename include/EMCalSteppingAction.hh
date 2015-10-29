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
//  Defines the SteppingAction class. This class takes the information obtained  //
//  in each step and saves it in the Run class.                                  //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#ifndef EMCalSteppingAction_h
#define EMCalSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <vector>

class EMCalEventAction;
class G4LogicalVolume;


//_______________________________________________________________________________

class EMCalSteppingAction : public G4UserSteppingAction {

public:

  // Constructor and destructor
  EMCalSteppingAction(EMCalEventAction* eventAction);
  virtual ~EMCalSteppingAction();

  // Method
  virtual void UserSteppingAction(const G4Step*);

private:

  // Attribute
  EMCalEventAction              *fEventAction;
};

#endif
