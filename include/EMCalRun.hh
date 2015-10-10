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
  void                      Fill();
  inline size_t             GetNbranches() const;
  inline PhysicalVariables* GetPathTo( size_t index );
  void                      Reset();
  inline void               SetOutputTree( TTree *tree );
  inline const char*        Title();

private:
  size_t             fNbranches;
  TTree             *fOutputTree;
  PhysicalVariables *fVariablesVector;
  const char        *fTitle;

};

inline size_t EMCalRun::GetNbranches() const { return fNbranches; }

inline EMCalRun::PhysicalVariables* EMCalRun::GetPathTo( size_t index ) {
  return fVariablesVector + index;
}

inline void EMCalRun::SetOutputTree( TTree *tree ) { fOutputTree = tree; }

inline const char* EMCalRun::Title() { return fTitle; }

#endif

