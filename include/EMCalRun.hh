#ifndef EMCalRun_h
#define EMCalRun_h 1

#include "EMCalDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "globals.hh"

#include "TTree.h"

class EMCalRun : public G4Run {

public:
  EMCalRun();
  virtual ~EMCalRun();

  // Nested struct variable to contain the values of
  // the variables for each module
  struct PhysicalVariables {

    PhysicalVariables();
    ~PhysicalVariables();

    G4double DetectorEnergy;
    G4double SGVolumeEnergy;
    G4double LostEnergy;
  };

  // ----------------------

  // Methods
  void                      AddEnergyToDetector( G4double edep,
						 G4int    idet );
  void                      AddEnergyToSGVolume( G4double edep,
						 G4int    idet );
  void                      Fill( const G4int &evtNb );
  inline size_t             GetNbranches() const;
  inline PhysicalVariables* GetPathTo( size_t index );
  void                      Reset();
  inline void               SetOutputTree( TTree *tree );
  inline G4double*          DetectorEnergyPath();
  inline G4double*          LostEnergyPath();
  inline G4int*             nHitsPath();
  inline G4double*          TrueEnergyPath();
  inline G4double*          SGVolumeEnergyPath();
  inline const char*        Title();

private:
  size_t             fNbranches;
  TTree             *fOutputTree;
  const char        *fTitle;

  // Variables of the complete calorimeter
  G4double           fDetectorEnergy;
  G4double           fLostEnergy;
  G4int              fNhits;
  G4double           fSGVolumeEnergy;
  G4double           fTrueEnergy;
  PhysicalVariables *fVariablesVector;

};

inline size_t EMCalRun::GetNbranches() const { return fNbranches; }

inline EMCalRun::PhysicalVariables* EMCalRun::GetPathTo( size_t index ) {
  return fVariablesVector + index;
}

inline void EMCalRun::SetOutputTree( TTree *tree ) { fOutputTree = tree; }

inline const char* EMCalRun::Title() { return fTitle; }

inline G4double* EMCalRun::DetectorEnergyPath() { return &fDetectorEnergy; }
inline G4double* EMCalRun::LostEnergyPath() { return &fLostEnergy; }
inline G4int*    EMCalRun::nHitsPath() { return &fNhits; }
inline G4double* EMCalRun::SGVolumeEnergyPath() { return &fSGVolumeEnergy; }
inline G4double* EMCalRun::TrueEnergyPath() { return &fTrueEnergy; }

#endif

