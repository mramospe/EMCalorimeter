#include "EMCalPhysicsListMessenger.hh"

EMCalPhysicsListMessenger::
EMCalPhysicsListMessenger( EMCalPhysicsList *physicsList ) :
  fPhysicsList( physicsList ) {

  fPhysicsDir
    = new G4UIdirectory( "/EMCal/physics/" );
  fPhysicsDir -> SetGuidance( "Physics control" );

  fDecayCmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enableDecay", this );
  fDecayCmd -> SetGuidance( "Enables Decay physics" );
  fDecayCmd -> AvailableForStates( G4State_PreInit );

  fEmDNACmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enableEmDNA", this );
  fEmDNACmd -> SetGuidance( "Enables EmDNA physics" );
  fEmDNACmd -> AvailableForStates( G4State_PreInit );

  fEmExtraCmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enableEmExtra", this );
  fEmExtraCmd -> SetGuidance( "Enables EmExtra physics" );
  fEmExtraCmd -> AvailableForStates( G4State_PreInit );

  fLivermoreCmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enableLivermore", this );
  fLivermoreCmd -> SetGuidance( "Enables Livermore physics" );
  fLivermoreCmd -> AvailableForStates( G4State_PreInit );

  fLivermorePolarizedCmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enableLivermorePolarized", this );
  fLivermorePolarizedCmd -> SetGuidance( "Enables LivermorePolarized physics" );
  fLivermorePolarizedCmd -> AvailableForStates( G4State_PreInit );

  fPenelopeCmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enablePenelope", this );
  fPenelopeCmd -> SetGuidance( "Enables Penelope physics" );
  fPenelopeCmd -> AvailableForStates( G4State_PreInit );

  fEmStandardCmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enableEmStandard", this );
  fEmStandardCmd -> SetGuidance( "Enables EmStandard physics" );
  fEmStandardCmd -> AvailableForStates( G4State_PreInit );

  fEmStandardOpt1Cmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enableEmStandard_option1", this );
  fEmStandardOpt1Cmd -> SetGuidance( "Enables EmStandard_option1 physics" );
  fEmStandardOpt1Cmd -> AvailableForStates( G4State_PreInit );

  fEmStandardOpt2Cmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enableEmStandard_option2", this );
  fEmStandardOpt2Cmd -> SetGuidance( "Enables EmStandard_option2 physics" );
  fEmStandardOpt2Cmd -> AvailableForStates( G4State_PreInit );

  fEmStandardOpt3Cmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enableEmStandard_option3", this );
  fEmStandardOpt3Cmd -> SetGuidance( "Enables EmStandard_option3 physics" );
  fEmStandardOpt3Cmd -> AvailableForStates( G4State_PreInit );

  fRadioactiveDecayCmd
    = new G4UIcmdWithoutParameter( "/EMCal/physics/enableRadioactiveDecay", this );
  fRadioactiveDecayCmd -> SetGuidance( "Enables RadioactiveDecay physics" );
  fRadioactiveDecayCmd -> AvailableForStates( G4State_PreInit );
}

EMCalPhysicsListMessenger::~EMCalPhysicsListMessenger() {

  delete fPhysicsDir;
  delete fDecayCmd;
  delete fEmDNACmd;
  delete fEmExtraCmd;
  delete fLivermoreCmd;
  delete fLivermorePolarizedCmd;
  delete fPenelopeCmd;
  delete fEmStandardCmd;
  delete fEmStandardOpt1Cmd;
  delete fEmStandardOpt2Cmd;
  delete fEmStandardOpt3Cmd;
  delete fRadioactiveDecayCmd;
}

void EMCalPhysicsListMessenger::SetNewValue( G4UIcommand *command, G4String ) {

  if ( command == fDecayCmd )
    fPhysicsList -> EnableDecay();
  if ( command == fEmDNACmd )
    fPhysicsList -> EnableEmDNA();
  if ( command == fEmExtraCmd )
    fPhysicsList -> EnableEmExtra();
  if ( command == fLivermoreCmd )
    fPhysicsList -> EnableLivermore();
  if ( command == fLivermorePolarizedCmd )
    fPhysicsList -> EnableLivermorePolarized();
  if ( command == fPenelopeCmd )
    fPhysicsList -> EnablePenelope();
  if ( command == fEmStandardCmd )
    fPhysicsList -> EnableEmStandard();
  if ( command == fEmStandardOpt1Cmd )
    fPhysicsList -> EnableEmStandardOpt1();
  if ( command == fEmStandardOpt2Cmd )
    fPhysicsList -> EnableEmStandardOpt2();
  if ( command == fEmStandardOpt3Cmd )
    fPhysicsList -> EnableEmStandardOpt3();
  if ( command == fRadioactiveDecayCmd )
    fPhysicsList -> EnableRadioactiveDecay();
}

