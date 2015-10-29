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
//  Defines the RunAction class. This is the class which has control of the      //
//  output file and trees. At the beginning of the run, a new tree is created    //
//  whose branches are set taking into account the number of modules of the      //
//  detector.                                                                    //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#ifndef EMCalRunAction_h
#define EMCalRunAction_h 1

#include "EMCalRun.hh"

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "TFile.h"
#include "TTree.h"


//_______________________________________________________________________________

class EMCalRunActionMessenger;

class EMCalRunAction : public G4UserRunAction {

public:

  // Constructor and destructor
  EMCalRunAction();
  virtual ~EMCalRunAction();

  // Methods
  inline  void   CreateNewFile( G4String name );
  virtual void   BeginOfRunAction( const G4Run* );
  virtual void   EndOfRunAction( const G4Run* );
  virtual G4Run* GenerateRun();
  inline  TTree* GetOutputTree();
  inline  void   SetOutputTreeName( G4String name );

protected:
  
  // Attributes
  EMCalRunActionMessenger *fMessenger;
  TFile                   *fOutputFile;
  TTree                   *fOutputTree;
  G4String                 fTreeName;
  EMCalRun                *fRun;

};

// Creates a new Root file
inline void EMCalRunAction::CreateNewFile( const G4String name ) {

  if ( fOutputFile )
    fOutputFile -> Close();

  fOutputFile = TFile::Open( name.data(), "RECREATE" );

  G4cout << " Created new file with name <" << name << ">" << G4endl;
}
// Gets the output tree class attached to the class ( the current writing tree )
inline TTree* EMCalRunAction::GetOutputTree() { return fOutputTree; }
// Sets the name of the output tree
inline void EMCalRunAction::SetOutputTreeName( G4String name ) {
  fTreeName = name;
  G4cout << " Output tree name changed to <" << name << ">" << G4endl;
}

#endif

