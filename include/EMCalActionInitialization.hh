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
//  Defines the ActionInitialization class for the EMCalorimeter application,    //
//  which generates the PrimaryGeneratorAction, RunAction, EventAction and       //
//  SteppingAction.                                                              //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#ifndef EMCalActionInitialization_h
#define EMCalActionInitialization_h 1

#include "G4VUserActionInitialization.hh"


//_______________________________________________________________________________

class EMCalActionInitialization : public G4VUserActionInitialization {

  public:

  // Constructor and destructor
    EMCalActionInitialization();
    virtual ~EMCalActionInitialization();

  // Methods
  virtual void BuildForMaster() const;
  virtual void Build() const;
};

#endif

    
