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
  
protected:
  EMCalEmissionEnergy                  *fEmissionEnergy;
  EMCalPrimaryGeneratorActionMessenger *fMessenger;
  G4ParticleGun                        *fParticleGun;
  G4String                              fParticleName;
  G4ThreeVector                         fParticlePosition;

};

#endif


