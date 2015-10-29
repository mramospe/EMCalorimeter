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
//  Defines the PrimaryGeneratorAction class. This class generates the events    //
//  of the simulation, specifying the energy shape, emission direction and type  //
//  of particle.                                                                 //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


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

#include <cmath>


//_______________________________________________________________________________
// Constructor
EMCalPrimaryGeneratorAction::EMCalPrimaryGeneratorAction() :
  G4VUserPrimaryGeneratorAction(),
  fParticleGun( 0 ),
  fMaxPhi( 0 ),
  fMaxTheta( 0 ),
  fMinPhi( 0 ),
  fMinTheta( 0 ) {

  fMessenger = new EMCalPrimaryGeneratorActionMessenger( this );

  fParticleGun = new G4ParticleGun( 1 );

  // By default emission is point-like with an energy of 6 MeV and unitary vector ( 0, 0, 0 )
  fEmissionEnergy = new EMCalPoint;
  static_cast<EMCalPoint*>( fEmissionEnergy ) -> SetEnergy( 6.*MeV );

  // Particle definition ( gamma by default )
  G4ParticleTable      *particleTable = G4ParticleTable::GetParticleTable();
  G4String              particleName  = "gamma";
  G4ParticleDefinition *particle
    = particleTable -> FindParticle( particleName );
  fParticleGun -> SetParticleDefinition( particle );
}

//_______________________________________________________________________________
// Destructor
EMCalPrimaryGeneratorAction::~EMCalPrimaryGeneratorAction() { delete fParticleGun; }

//_______________________________________________________________________________
// This method sets the direction, energy and type for the incident particle
void EMCalPrimaryGeneratorAction::GeneratePrimaries( G4Event *event ) {
  
  // Sets the particle energy
  fParticleGun -> SetParticleEnergy( fEmissionEnergy -> GetRandom() );
  // Sets the particle position
  fParticleGun -> SetParticlePosition( G4ThreeVector( 0, 0, 0 ) );
  // Sets the momentum of the incident particle
  G4double
    phi   = CLHEP::RandFlat::shoot( fMinPhi  , fMaxPhi   ),
    theta = CLHEP::RandFlat::shoot( fMinTheta, fMaxTheta ),
    sinth = std::sin( theta );
  fParticleGun -> SetParticleMomentumDirection( G4ThreeVector( sinth*std::cos( phi ),
							       sinth*std::sin( phi ),
							       std::cos( theta ) ) );

  fParticleGun -> GeneratePrimaryVertex( event );
}

//_______________________________________________________________________________
// Sets the shape of the energy of the incident particle
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
  }
}

