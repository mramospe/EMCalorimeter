#include "EMCalEmissionEnergyMessenger.hh"

// ____________________________________________________

EMCalBreitWignerMessenger::
EMCalBreitWignerMessenger( EMCalBreitWigner *randGen ) :
  fBreitWigner( randGen ) {

  fMeanCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setMean", this );
  fMeanCmd -> SetGuidance( "Select the mean of the distribution" );
  fMeanCmd -> SetParameterName( "Mean", false );
  fMeanCmd -> SetRange( "Mean > 0" );
  fMeanCmd -> SetUnitCategory( "Energy" );
  fMeanCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
      
  fWidthCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setWidth", this );
  fWidthCmd -> SetGuidance( "Select the width of the distribution" );
  fWidthCmd -> SetParameterName( "Width", false );
  fWidthCmd -> SetRange( "Width > 0" );
  fWidthCmd -> SetUnitCategory( "Energy" );
  fWidthCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );  
}

EMCalBreitWignerMessenger::~EMCalBreitWignerMessenger() {

  delete fMeanCmd;
  delete fWidthCmd;
}

void EMCalBreitWignerMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fMeanCmd )
    fBreitWigner -> SetMean( fMeanCmd -> GetNewDoubleValue( value ) );
  if ( command == fWidthCmd )
    fBreitWigner -> SetWidth( fWidthCmd -> GetNewDoubleValue( value ) );
}

// ____________________________________________________

EMCalExponentialMessenger::
EMCalExponentialMessenger( EMCalExponential *randGen ) :
  fExponential( randGen ) {

  fExpParCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setExpPar", this );
  fExpParCmd -> SetGuidance( "Select the exponential parameter of the distribution" );
  fExpParCmd -> SetParameterName( "ExpPar", false );
  fExpParCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );  

  fMaxEnergyCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setMaxEnergy", this );
  fMaxEnergyCmd -> SetGuidance( "Select the maximum energy of the distribution" );
  fMaxEnergyCmd -> SetParameterName( "MaxEnergy", false );
  fMaxEnergyCmd -> SetRange( "MaxEnergy > 0" );
  fMaxEnergyCmd -> SetUnitCategory( "Energy" );
  fMaxEnergyCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
      
  fMinEnergyCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setMinEnergy", this );
  fMinEnergyCmd -> SetGuidance( "Select the minimum energy of the distribution" );
  fMinEnergyCmd -> SetParameterName( "MinEnergy", false );
  fMinEnergyCmd -> SetRange( "MinEnergy > 0" );
  fMinEnergyCmd -> SetUnitCategory( "Energy" );
  fMinEnergyCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
}

EMCalExponentialMessenger::~EMCalExponentialMessenger() {

  delete fExpParCmd;
  delete fMaxEnergyCmd;
  delete fMinEnergyCmd;
}

void EMCalExponentialMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fExpParCmd )
    fExponential -> SetExpPar( fExpParCmd -> GetNewDoubleValue( value ) );
  if ( command == fMaxEnergyCmd )
    fExponential -> SetMaxEnergy( fMaxEnergyCmd -> GetNewDoubleValue( value ) );
  if ( command == fMaxEnergyCmd )
    fExponential -> SetMinEnergy( fMinEnergyCmd -> GetNewDoubleValue( value ) );
}

// ____________________________________________________

EMCalFlatMessenger::
EMCalFlatMessenger( EMCalFlat *randGen ) :
  fFlat( randGen ) {

  fMaxEnergyCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setMaxEnergy", this );
  fMaxEnergyCmd -> SetGuidance( "Select the maximum energy of the distribution" );
  fMaxEnergyCmd -> SetParameterName( "MaxEnergy", false );
  fMaxEnergyCmd -> SetRange( "MaxEnergy > 0" );
  fMaxEnergyCmd -> SetUnitCategory( "Energy" );
  fMaxEnergyCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
      
  fMinEnergyCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setMinEnergy", this );
  fMinEnergyCmd -> SetGuidance( "Select the minimum energy of the distribution" );
  fMinEnergyCmd -> SetParameterName( "MinEnergy", false );
  fMinEnergyCmd -> SetRange( "MinEnergy > 0" );
  fMinEnergyCmd -> SetUnitCategory( "Energy" );
  fMinEnergyCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
}

EMCalFlatMessenger::~EMCalFlatMessenger() {

  delete fMaxEnergyCmd;
  delete fMinEnergyCmd;
}

void EMCalFlatMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fMaxEnergyCmd )
    fFlat -> SetMaxEnergy( fMaxEnergyCmd -> GetNewDoubleValue( value ) );
  if ( command == fMinEnergyCmd )
    fFlat -> SetMinEnergy( fMinEnergyCmd -> GetNewDoubleValue( value ) );
}

// ____________________________________________________

EMCalGammaMessenger::
EMCalGammaMessenger( EMCalGamma *randGen ) :
  fGamma( randGen ) {

  fKcmd
    = new G4UIcmdWithADouble( "/EMCal/emission/energy/setK", this );
  fKcmd -> SetGuidance( "Select the maximum energy of the distribution" );
  fKcmd -> SetParameterName( "K", false );
  fKcmd -> SetRange( "K > 0" );
  fKcmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
      
  fLambdaCmd
    = new G4UIcmdWithADouble( "/EMCal/emission/energy/setLambda", this );
  fLambdaCmd -> SetGuidance( "Select the minimum energy of the distribution" );
  fLambdaCmd -> SetParameterName( "Lambda", false );
  fLambdaCmd -> SetRange( "Lambda > 0" );
  fLambdaCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
}

EMCalGammaMessenger::~EMCalGammaMessenger() {

  delete fKcmd;
  delete fLambdaCmd;
}

void EMCalGammaMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fKcmd )
    fGamma -> SetK( fKcmd -> GetNewDoubleValue( value ) );
  if ( command == fLambdaCmd )
    fGamma -> SetLambda( fLambdaCmd -> GetNewDoubleValue( value ) );
}

// ____________________________________________________

EMCalGaussMessenger::
EMCalGaussMessenger( EMCalGauss *randGen ) :
  fGauss( randGen ) {

  fMeanCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setMean", this );
  fMeanCmd -> SetGuidance( "Select the mean of the distribution" );
  fMeanCmd -> SetParameterName( "Mean", false );
  fMeanCmd -> SetRange( "Mean > 0" );
  fMeanCmd -> SetUnitCategory( "Energy" );
  fMeanCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
      
  fSigmaCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setSigma", this );
  fSigmaCmd -> SetGuidance( "Select the sigma of the distribution" );
  fSigmaCmd -> SetParameterName( "Sigma", false );
  fSigmaCmd -> SetRange( "Sigma > 0" );
  fSigmaCmd -> SetUnitCategory( "Energy" );
  fSigmaCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );  
}

EMCalGaussMessenger::~EMCalGaussMessenger() {

  delete fMeanCmd;
  delete fSigmaCmd;
}

void EMCalGaussMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fMeanCmd )
    fGauss -> SetMean( fMeanCmd -> GetNewDoubleValue( value ) );
  if ( command == fSigmaCmd )
    fGauss -> SetSigma( fSigmaCmd -> GetNewDoubleValue( value ) );
}

// ____________________________________________________

EMCalLinearMessenger::
EMCalLinearMessenger( EMCalLinear *randGen ) :
  fLinear( randGen ) {

  fMaxEnergyCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setMaxEnergy", this );
  fMaxEnergyCmd -> SetGuidance( "Select the maximum energy of the distribution" );
  fMaxEnergyCmd -> SetParameterName( "MaxEnergy", false );
  fMaxEnergyCmd -> SetRange( "MaxEnergy > 0" );
  fMaxEnergyCmd -> SetUnitCategory( "Energy" );
  fMaxEnergyCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  fMaxMinPropCmd
    = new G4UIcmdWithADouble( "/EMCal/emission/energy/setMaxMinProp", this );
  fMaxMinPropCmd -> SetGuidance( "Select the event proportion max_E/min_E" );
  fMaxMinPropCmd -> SetParameterName( "MaxMinProp", false );
  fMaxMinPropCmd -> SetRange( "MaxMinProp > 0" );
  fMaxMinPropCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
      
  fMinEnergyCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setMinEnergy", this );
  fMinEnergyCmd -> SetGuidance( "Select the minimum energy of the distribution" );
  fMinEnergyCmd -> SetParameterName( "MinEnergy", false );
  fMinEnergyCmd -> SetRange( "MinEnergy > 0" );
  fMinEnergyCmd -> SetUnitCategory( "Energy" );
  fMinEnergyCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
}

EMCalLinearMessenger::~EMCalLinearMessenger() {

  delete fMaxEnergyCmd;
  delete fMaxMinPropCmd;
  delete fMinEnergyCmd;
}

void EMCalLinearMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fMaxEnergyCmd )
    fLinear -> SetMaxEnergy( fMaxEnergyCmd -> GetNewDoubleValue( value ) );
  if ( command == fMinEnergyCmd )
    fLinear -> SetMinEnergy( fMinEnergyCmd -> GetNewDoubleValue( value ) );
}

// ____________________________________________________

EMCalPointMessenger::
EMCalPointMessenger( EMCalPoint *randGen ) :
  fPoint( randGen ) {

  fEnergyCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/emission/energy/setEnergy", this );
  fEnergyCmd -> SetGuidance( "Select the maximum energy of the distribution" );
  fEnergyCmd -> SetParameterName( "Energy", false );
  fEnergyCmd -> SetRange( "Energy > 0" );
  fEnergyCmd -> SetUnitCategory( "Energy" );
  fEnergyCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
}

EMCalPointMessenger::~EMCalPointMessenger() { delete fEnergyCmd; }

void EMCalPointMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fEnergyCmd )
    fPoint -> SetEnergy( fEnergyCmd -> GetNewDoubleValue( value ) );
}
