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
//  Defines the Run class. This class fills the output tree each time and event  //
//  finishes. Thus it has access to the detector information and to the          //
//  RunAction class.                                                             //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#ifndef EMCalRun_h
#define EMCalRun_h 1

#include "EMCalDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "globals.hh"

#include "TTree.h"


//_______________________________________________________________________________

class EMCalRun : public G4Run {

public:

  // Constructor and destructor
  EMCalRun();
  virtual ~EMCalRun();

  // Nested struct variable to contain the values of the variables for
  // each module
  struct PhysicalVariables {

    PhysicalVariables();
    ~PhysicalVariables();

    G4double DetectorEnergy;
    G4double SGVolumeEnergy;
    G4int    nDetInteractions;
    G4int    nSgvInteractions;
  };

  // Methods
  inline void               AddEnergyToDetector( G4double edep,
						 G4int    idet );
  inline void               AddEnergyToSGVolume( G4double edep,
						 G4int    idet );
  void                      Fill( const G4int &evtNb );
  inline size_t             GetNbranches() const;
  inline PhysicalVariables* GetPathTo( size_t index );
  void                      Reset();
  inline void               SetOutputTree( TTree *tree );
  inline G4double*          DetectorEnergyPath();
  inline G4double*          LostEnergyPath();
  inline G4int*             nDetHitsPath();
  inline G4int*             nSgvHitsPath();
  inline G4double*          TrueEnergyPath();
  inline G4double*          SGVolumeEnergyPath();
  inline const char*        Title();

private:

  // Attributes
  size_t             fNbranches;
  TTree             *fOutputTree;
  const char        *fTitle;

  // Attributes that are variables of the complete calorimeter
  G4double           fDetectorEnergy;
  G4double           fLostEnergy;
  G4int              fNdetHits;
  G4int              fNsgvHits;
  G4double           fSGVolumeEnergy;
  G4double           fTrueEnergy;
  PhysicalVariables *fVariablesVector;

};

// Adds energy to the detector at position < idet >
inline void EMCalRun::AddEnergyToDetector( G4double edep,
					   G4int    idet ) {
  fVariablesVector[ idet ].DetectorEnergy += edep;
  fVariablesVector[ idet ].nDetInteractions++;
}
// Adds energy to the shower-generator volume at position < idet >
inline void EMCalRun::AddEnergyToSGVolume( G4double edep,
					   G4int    idet ) {
  fVariablesVector[ idet ].SGVolumeEnergy += edep;
  fVariablesVector[ idet ].nSgvInteractions++;
}
// Gets the number of branches in the tree
inline size_t EMCalRun::GetNbranches() const { return fNbranches; }
// Gets the path to the variables associated with the module at position < index >
inline EMCalRun::PhysicalVariables* EMCalRun::GetPathTo( size_t index ) {
  return fVariablesVector + index;
}
// Sets the output tree pointer
inline void        EMCalRun::SetOutputTree( TTree *tree ) { fOutputTree = tree; }
// Sets the title of the calorimeter variables
inline const char* EMCalRun::Title()                      { return fTitle; }
// Returns the path for the different attributes
inline G4double*   EMCalRun::DetectorEnergyPath()         { return &fDetectorEnergy; }
inline G4double*   EMCalRun::LostEnergyPath()             { return &fLostEnergy; }
inline G4int*      EMCalRun::nDetHitsPath()               { return &fNdetHits; }
inline G4int*      EMCalRun::nSgvHitsPath()               { return &fNsgvHits; }
inline G4double*   EMCalRun::SGVolumeEnergyPath()         { return &fSGVolumeEnergy; }
inline G4double*   EMCalRun::TrueEnergyPath()             { return &fTrueEnergy; }

#endif

