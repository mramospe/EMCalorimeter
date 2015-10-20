#ifndef EMCalPrimaryGeneratorAction_h
#define EMCalPrimaryGeneratorAction_h 1

#include "EMCalEmissionEnergy.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class EMCalPrimaryGeneratorActionMessenger;

class G4Event;

class EMCalPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

public:
  EMCalPrimaryGeneratorAction();    
  virtual ~EMCalPrimaryGeneratorAction();

  virtual void         GeneratePrimaries( G4Event *event );         
  const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  void                 SetEnergyShape( G4String shape );
  inline void          SetMaxPhi( G4double value );
  inline void          SetMaxTheta( G4double value );
  inline void          SetMinPhi( G4double value );
  inline void          SetMinTheta( G4double value );
  
protected:
  EMCalEmissionEnergy                  *fEmissionEnergy;
  EMCalPrimaryGeneratorActionMessenger *fMessenger;
  G4ParticleGun                        *fParticleGun;
  G4String                              fParticleName;
  G4double                              fMaxPhi;
  G4double                              fMaxTheta;
  G4double                              fMinPhi;
  G4double                              fMinTheta;

};

inline void EMCalPrimaryGeneratorAction::SetMaxPhi( G4double value )   { fMaxPhi   = value; }
inline void EMCalPrimaryGeneratorAction::SetMaxTheta( G4double value ) { fMaxTheta = value; }
inline void EMCalPrimaryGeneratorAction::SetMinPhi( G4double value )   { fMinPhi   = value; }
inline void EMCalPrimaryGeneratorAction::SetMinTheta( G4double value ) { fMinTheta = value; }

#endif


