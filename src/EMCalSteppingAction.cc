#include "EMCalSteppingAction.hh"
#include "EMCalEventAction.hh"
#include "EMCalDetectorConstruction.hh"
#include "EMCalRun.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

EMCalSteppingAction::EMCalSteppingAction( EMCalEventAction* eventAction ) :
  G4UserSteppingAction(), fEventAction( eventAction ) { }

EMCalSteppingAction::~EMCalSteppingAction() { }

void EMCalSteppingAction::UserSteppingAction( const G4Step* step ) {

  const EMCalDetectorConstruction* detector
    = static_cast<const EMCalDetectorConstruction*>
    ( G4RunManager::GetRunManager() -> GetUserDetectorConstruction() );

  // Gets the volume associated with the current step
  G4LogicalVolume *volume 
    = step -> GetPreStepPoint() -> GetTouchableHandle()
      -> GetVolume() -> GetLogicalVolume();
      
  // Gets the EMCalRun class
  EMCalRun *run 
    = static_cast<EMCalRun*>( G4RunManager::GetRunManager() -> 
			      GetNonConstCurrentRun() );

  // Checks if we are in scoring volume and if true it gets the energy deposited
  size_t
    imod,
    size = detector -> GetNmodules();
  G4bool
    indetector = false,
    insgvolume = false;
  G4double edepStep;

  imod = 0;
  while ( imod < size && !indetector ) {
    if ( volume == detector -> GetDetector( imod ) ) indetector = true;
    imod++;
  }
  if ( indetector ) {
    edepStep = step -> GetTotalEnergyDeposit();
    // Because of the < while > loop < imod > is one unit greater
    run -> AddEnergyToDetector( edepStep, imod - 1 );
  }
  else {
    imod = 0;
    while ( imod < size && !insgvolume ) {
      if ( volume == detector -> GetSGVolume( imod ) ) insgvolume = true;
      imod++;
    }
    if ( insgvolume ) {
      edepStep = step -> GetTotalEnergyDeposit();
      // Because of the < while > loop < imod > is one unit greater
      run -> AddEnergyToSGVolume( edepStep, imod - 1 );
    }
  }
}
