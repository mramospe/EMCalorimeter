#include "EMCalPrimaryGeneratorAction.hh"
#include "EMCalPrimaryGeneratorActionMessenger.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

EMCalPrimaryGeneratorAction::EMCalPrimaryGeneratorAction() :
  G4VUserPrimaryGeneratorAction(), fParticleGun( 0 ) {

  fMessenger = new EMCalPrimaryGeneratorActionMessenger( this );

  fParticleGun = new G4ParticleGun( 1 );

  // By default emission is point-like with an energy of 6 MeV
  fEmissionEnergy = new EMCalPoint;
  static_cast<EMCalPoint*>( fEmissionEnergy ) -> SetEnergy( 6.*MeV );

  // Particle definition ( gamma by default )
  G4ParticleTable      *particleTable = G4ParticleTable::GetParticleTable();
  G4String              particleName  = "gamma";
  G4ParticleDefinition *particle
    = particleTable -> FindParticle( particleName );
  fParticleGun -> SetParticleDefinition( particle );
}

EMCalPrimaryGeneratorAction::~EMCalPrimaryGeneratorAction() { delete fParticleGun; }

void EMCalPrimaryGeneratorAction::GeneratePrimaries( G4Event *event ) {
  
  fParticleGun -> SetParticleEnergy( fEmissionEnergy -> GetRandom() );
  fParticleGun -> SetParticlePosition( G4ThreeVector( 0, 0, 0 ) );
  fParticleGun -> SetParticleMomentumDirection( G4ThreeVector( 0., 0., 1.) );

  fParticleGun -> GeneratePrimaryVertex( event );
}

void EMCalPrimaryGeneratorAction::SetEnergyShape( G4String shape ) {

  delete fEmissionEnergy;

  if ( shape == "Breit-Wigner" )
    fEmissionEnergy = new EMCalBreitWigner;
  else if ( shape == "Exponential" )
    fEmissionEnergy = new EMCalExponential;
  else if ( shape == "Flat" )
    fEmissionEnergy = new EMCalFlat;
  else if ( shape == "Gamma" )
    fEmissionEnergy = new EMCalGamma;
  else if ( shape == "Gauss" )
    fEmissionEnergy = new EMCalGauss;
  else if ( shape == "Linear" )
    fEmissionEnergy = new EMCalLinear;
  else if ( shape == "Point" )
    fEmissionEnergy = new EMCalPoint;
  else {

    G4cout << "Energy shape <" << shape << "> not known" << G4endl;
    G4cout << "Energy emission set to default values" << G4endl;

    fEmissionEnergy = new EMCalPoint;
    static_cast<EMCalPoint*>( fEmissionEnergy ) -> SetEnergy( 6*MeV );
  }
}
