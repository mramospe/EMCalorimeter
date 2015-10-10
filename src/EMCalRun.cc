#include "G4ParticleGun.hh"

#include "EMCalDetectorConstruction.hh"
#include "EMCalPrimaryGeneratorAction.hh"
#include "EMCalRun.hh"

EMCalRun::EMCalRun() :
  G4Run(),
  fOutputTree( 0 ),
  fVariablesVector( 0 ),
  fTitle( "DetectorEnergy/D:SGVolumeEnergy/D:LostEnergy/D" ) {

  const EMCalDetectorConstruction *detector
   = static_cast<const EMCalDetectorConstruction*>
     ( G4RunManager::GetRunManager() -> GetUserDetectorConstruction() );

  fNbranches       = detector -> GetNmodules() + 1;
  fVariablesVector = new EMCalRun::PhysicalVariables[ fNbranches ];
} 

EMCalRun::~EMCalRun() { delete[] fVariablesVector; }

EMCalRun::PhysicalVariables::PhysicalVariables() :
  DetectorEnergy( 0 ), SGVolumeEnergy( 0 ), LostEnergy( 0 ) { }

EMCalRun::PhysicalVariables::~PhysicalVariables() { }

void EMCalRun::AddEnergyToDetector( G4double edep,
				    G4int    idet ) {

  fVariablesVector[ idet ].DetectorEnergy += edep;
}

void EMCalRun::AddEnergyToSGVolume( G4double edep,
				    G4int    idet ) {

  fVariablesVector[ idet ].SGVolumeEnergy += edep;
}
 
void EMCalRun::Fill() {

  // Obtains the pointer to the particle gun
  const EMCalPrimaryGeneratorAction* generatorAction
   = static_cast<const EMCalPrimaryGeneratorAction*>
     ( G4RunManager::GetRunManager() -> GetUserPrimaryGeneratorAction() );

  const G4ParticleGun* particleGun = generatorAction -> GetParticleGun();

  // Gets the energy of the incident particle
  G4double
    particleEnergy = particleGun -> GetParticleEnergy(),
    detectorEnergy,
    sgvolumeEnergy,
    totalDetectorEnergy = 0,
    totalSGVolumeEnergy = 0;
  
  for ( size_t idet = 1; idet < fNbranches; idet++ ) {

    detectorEnergy = fVariablesVector[ idet ].DetectorEnergy;
    sgvolumeEnergy = fVariablesVector[ idet ].SGVolumeEnergy;

    fVariablesVector[ idet ].LostEnergy
      = particleEnergy - detectorEnergy - sgvolumeEnergy;

    totalDetectorEnergy += detectorEnergy;
    totalSGVolumeEnergy += sgvolumeEnergy;
  }

  fVariablesVector[ 0 ].DetectorEnergy = totalDetectorEnergy;
  fVariablesVector[ 0 ].SGVolumeEnergy = totalSGVolumeEnergy;
  fVariablesVector[ 0 ].LostEnergy
    = particleEnergy - totalDetectorEnergy - totalSGVolumeEnergy;

  fOutputTree -> Fill();
}

void EMCalRun::Reset() {

    for ( size_t idet = 0; idet < fNbranches; idet++ ) {

      fVariablesVector[ idet ].DetectorEnergy  = 0;
      fVariablesVector[ idet ].SGVolumeEnergy  = 0;
      fVariablesVector[ idet ].LostEnergy      = 0;
    }
}
