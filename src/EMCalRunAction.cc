#include "EMCalRunActionMessenger.hh"
#include "EMCalModule.hh"
#include "EMCalRunAction.hh"
#include "EMCalPrimaryGeneratorAction.hh"
#include "EMCalDetectorConstruction.hh"
#include "EMCalRun.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

EMCalRunAction::EMCalRunAction() :
  G4UserRunAction(),
  fOutputFile( 0 ),
  fOutputTree( 0 ),
  fTreeName( "DecayTree" ) {

  fMessenger = new EMCalRunActionMessenger( this );
}

EMCalRunAction::~EMCalRunAction() {

  delete fMessenger;

  if ( fOutputFile )
    fOutputFile -> Close();
}

G4Run* EMCalRunAction::GenerateRun() {

  // If the file does not exist it is created
  if ( !fOutputFile )
    this -> CreateNewFile( "EMCalorimeter_Results.root" );

  // The EMCalRun class is initiated
  fRun = new EMCalRun;

  return fRun;
}

void EMCalRunAction::BeginOfRunAction( const G4Run* ) { 

  // Creates a new tree
  fOutputFile -> cd();
  fOutputTree = new TTree( fTreeName.data(), fTreeName.data(), 0 );

  // Gives the path of the output tree to the EMCalRun class
  fRun -> SetOutputTree( fOutputTree );

  // Creates the structure of the output tree
  const EMCalDetectorConstruction *detector =
    static_cast<const EMCalDetectorConstruction*>
    ( G4RunManager::GetRunManager() -> GetUserDetectorConstruction() );

  // Sets the branches for the variables of the complete detector.
  if ( detector -> SGVenabled() ) {
    fOutputTree -> Branch( "DetectorEnergy", fRun -> DetectorEnergyPath(), "DetectorEnergy/D" );
    fOutputTree -> Branch( "SGVolumeEnergy", fRun -> SGVolumeEnergyPath(), "SGVolumeEnergy/D" );
    fOutputTree -> Branch( "LostEnergy"    , fRun -> LostEnergyPath()    , "LostEnergy/D"     );
    fOutputTree -> Branch( "TrueEnergy"    , fRun -> TrueEnergyPath()    , "TrueEnergy/D"     );
    fOutputTree -> Branch( "nDetHits"      , fRun -> nDetHitsPath()      , "nDetHits/I"       );
    fOutputTree -> Branch( "nSgvHits"      , fRun -> nSgvHitsPath()      , "nSgvHits/I"       );
  }
  else {
    fOutputTree -> Branch( "DetectorEnergy", fRun -> DetectorEnergyPath(), "DetectorEnergy/D" );
    fOutputTree -> Branch( "LostEnergy"    , fRun -> LostEnergyPath()    , "LostEnergy/D"     );
    fOutputTree -> Branch( "TrueEnergy"    , fRun -> TrueEnergyPath()    , "TrueEnergy/D"     );
    fOutputTree -> Branch( "nDetHits"      , fRun -> nDetHitsPath()      , "nDetHits/I"       );
  }

  // Sets the branches for each of the modules. If there is only one module the branches are
  // not created.
  std::vector<EMCalModule*> marray = detector -> GetModuleArray();
  if ( marray.size() > 1 )
    for ( size_t idet = 0; idet < marray.size(); idet++ )
      fOutputTree -> Branch( ( marray[ idet ] -> GetID() ).data(),
			     fRun -> GetPathTo( idet ),
			     fRun -> Title() );

  // Informs the runManager to save random number seed
  G4RunManager::GetRunManager() -> SetRandomNumberStore( false );
}

void EMCalRunAction::EndOfRunAction( const G4Run *run ) {

  // Gets the number of the event. If zero it returns.
  G4int nofEvents = run -> GetNumberOfEvent();
  if ( nofEvents == 0 ) return;

  G4cout << "  Data saved in file:\t" << fOutputFile -> GetName() << G4endl;
  G4cout << "  Output tree:       \t" << fOutputTree -> GetName() << G4endl;
  G4cout << "=================================================="  << G4endl;

  // Autosaves the output tree
  fOutputTree -> AutoSave();
}
