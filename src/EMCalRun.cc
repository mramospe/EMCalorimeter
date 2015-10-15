#include "G4ParticleGun.hh"

#include "EMCalDetectorConstruction.hh"
#include "EMCalPrimaryGeneratorAction.hh"
#include "EMCalRun.hh"

EMCalRun::EMCalRun() :
  G4Run(),
  fOutputTree( 0 ),
  fDetectorEnergy( 0 ),
  fLostEnergy( 0 ),
  fNdetHits( 0 ),
  fNsgvHits( 0 ),
  fSGVolumeEnergy( 0 ),
  fTrueEnergy( 0 ),
  fVariablesVector( 0 ) {

  const EMCalDetectorConstruction *detector
    = static_cast<const EMCalDetectorConstruction*>
    ( G4RunManager::GetRunManager() -> GetUserDetectorConstruction() );

  // The title depends if shower-generator volume is enabled or not
  if ( detector -> SGVenabled() )
    fTitle = "DetectorEnergy/D:SGVolumeEnergy/D:nDetInteractions/I:nSgvInteractions/I";
  else
    fTitle = "DetectorEnergy/D:nDetInteractions/I";

  fNbranches       = detector -> GetNmodules();
  fVariablesVector = new EMCalRun::PhysicalVariables[ fNbranches ];
} 

EMCalRun::~EMCalRun() { delete[] fVariablesVector; }

EMCalRun::PhysicalVariables::PhysicalVariables() :
  DetectorEnergy( 0 ), SGVolumeEnergy( 0 ), nDetInteractions( 0 ), nSgvInteractions( 0 ) { }

EMCalRun::PhysicalVariables::~PhysicalVariables() { }
 
void EMCalRun::Fill( const G4int &evtNb ) {

  // Gets the pointer to the particle gun
  const EMCalPrimaryGeneratorAction* generatorAction
    = static_cast<const EMCalPrimaryGeneratorAction*>
    ( G4RunManager::GetRunManager() -> GetUserPrimaryGeneratorAction() );
  const G4ParticleGun* particleGun = generatorAction -> GetParticleGun();

  // Gets the pointer to the detector
  const EMCalDetectorConstruction *detector
    = static_cast<const EMCalDetectorConstruction*>
    ( G4RunManager::GetRunManager() -> GetUserDetectorConstruction() );

  // Sets to zero the calorimeter variables and gets the energy of the incident particle
  fDetectorEnergy = 0;
  fLostEnergy     = 0;
  fNdetHits       = 0;
  fNsgvHits       = 0;
  fSGVolumeEnergy = 0;
  fTrueEnergy     = particleGun -> GetParticleEnergy();

  // Gets the energy deposited in each module
  G4double ModDetectorEnergy, ModSGVolumeEnergy;

  if ( detector -> SGVenabled() )
    for ( size_t idet = 0; idet < fNbranches; idet++ ) {

      ModDetectorEnergy = fVariablesVector[ idet ].DetectorEnergy;
      fDetectorEnergy += ModDetectorEnergy;
      if ( ModDetectorEnergy > 0. )
	fNdetHits++;

      ModSGVolumeEnergy = fVariablesVector[ idet ].SGVolumeEnergy;
      fSGVolumeEnergy += ModSGVolumeEnergy;
      if ( ModSGVolumeEnergy > 0. )
	fNsgvHits++;
    }
  else
    for ( size_t idet = 0; idet < fNbranches; idet++ ) {

      ModDetectorEnergy = fVariablesVector[ idet ].DetectorEnergy;
      fDetectorEnergy += ModDetectorEnergy;
      if ( ModDetectorEnergy > 0. )
	fNdetHits++;
    }
    
  // Calculates the energy lost by the calorimeter
  fLostEnergy = fTrueEnergy - fDetectorEnergy;

  // Fills the output tree
  fOutputTree -> Fill();

  // Autosaves the output tree each certain time
  if ( evtNb % 100000 == 0 ) {

    G4cout << "\n ******************************* "   << G4endl;
    G4cout <<   " **** Autosaving output tree *** "   << G4endl;
    G4cout <<   " ******************************* \n" << G4endl;
    fOutputTree -> AutoSave();
  }
}

void EMCalRun::Reset() {

  for ( size_t idet = 0; idet < fNbranches; idet++ ) {

    fVariablesVector[ idet ].DetectorEnergy   = 0;
    fVariablesVector[ idet ].SGVolumeEnergy   = 0;
    fVariablesVector[ idet ].nDetInteractions = 0;
    fVariablesVector[ idet ].nSgvInteractions = 0;
  }
}
