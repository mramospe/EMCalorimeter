#ifndef EMCalRunAction_h
#define EMCalRunAction_h 1

#include "EMCalRun.hh"

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "TFile.h"
#include "TTree.h"

class EMCalRunActionMessenger;

class EMCalRunAction : public G4UserRunAction {

public:

  EMCalRunAction();
  virtual ~EMCalRunAction();

  inline  void   CreateNewFile( G4String name );
  virtual void   BeginOfRunAction( const G4Run* );
  virtual void   EndOfRunAction( const G4Run* );
  virtual G4Run* GenerateRun();
  inline  TTree* GetOutputTree();
  inline  void   SetOutputTreeName( G4String name );

protected:
  
  EMCalRunActionMessenger *fMessenger;
  TFile                   *fOutputFile;
  TTree                   *fOutputTree;
  G4String                 fTreeName;
  EMCalRun                *fRun;

};

inline void EMCalRunAction::CreateNewFile( const G4String name ) {

  if ( fOutputFile )
    fOutputFile -> Close();

  fOutputFile = TFile::Open( name.data(), "RECREATE" );

  G4cout << " Created new file with name <" << name << ">" << G4endl;
}

inline TTree* EMCalRunAction::GetOutputTree() { return fOutputTree; }

inline void EMCalRunAction::SetOutputTreeName( G4String name ) {
  fTreeName = name;
  G4cout << " Output tree name changed to <" << name << ">" << G4endl;
}

#endif

