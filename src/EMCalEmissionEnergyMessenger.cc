//////////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------------- //
//                                                                                  //
//  AUTHOR: Miguel Ramos Pernas                                                     //
//  e-mail: miguel.ramos.pernas@cern.ch                                             //
//                                                                                  //
//  Last update: 26/10/2015                                                         //
//                                                                                  //
// -------------------------------------------------------------------------------- //
//                                                                                  //
//  Description:                                                                    //
//                                                                                  //
//  Implements the messenger to control the energy emission of the simulation. For  //
//  each different energy shape there is an specific messenger.                     //
//                                                                                  //
// -------------------------------------------------------------------------------- //
//////////////////////////////////////////////////////////////////////////////////////


#include "EMCalEmissionEnergyMessenger.hh"


//_______________________________________________________________________________

// --- METHODS FOR EMCalBreitWignerMessenger CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalBreitWignerMessenger::EMCalBreitWignerMessenger( EMCalBreitWigner *randGen ) :
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

//_______________________________________________________________________________
// Destructor
EMCalBreitWignerMessenger::~EMCalBreitWignerMessenger() {

  delete fMeanCmd;
  delete fWidthCmd;
}

//_______________________________________________________________________________
// Modifies the value of one of the attributes
void EMCalBreitWignerMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fMeanCmd )
    fBreitWigner -> SetMean( fMeanCmd -> GetNewDoubleValue( value ) );
  if ( command == fWidthCmd )
    fBreitWigner -> SetWidth( fWidthCmd -> GetNewDoubleValue( value ) );
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalExponentialMessenger CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalExponentialMessenger::EMCalExponentialMessenger( EMCalExponential *randGen ) :
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

//_______________________________________________________________________________
// Destructor
EMCalExponentialMessenger::~EMCalExponentialMessenger() {

  delete fExpParCmd;
  delete fMaxEnergyCmd;
  delete fMinEnergyCmd;
}

//_______________________________________________________________________________
// Modifies the value of one of the attributes
void EMCalExponentialMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fExpParCmd )
    fExponential -> SetExpPar( fExpParCmd -> GetNewDoubleValue( value ) );
  if ( command == fMaxEnergyCmd )
    fExponential -> SetMaxEnergy( fMaxEnergyCmd -> GetNewDoubleValue( value ) );
  if ( command == fMaxEnergyCmd )
    fExponential -> SetMinEnergy( fMinEnergyCmd -> GetNewDoubleValue( value ) );
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalFlatMessenger CLASS ---

//_______________________________________________________________________________
// Constructor
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

//_______________________________________________________________________________
// Destructor
EMCalFlatMessenger::~EMCalFlatMessenger() {

  delete fMaxEnergyCmd;
  delete fMinEnergyCmd;
}

//_______________________________________________________________________________
// Modifies the value of one of the attributes
void EMCalFlatMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fMaxEnergyCmd )
    fFlat -> SetMaxEnergy( fMaxEnergyCmd -> GetNewDoubleValue( value ) );
  if ( command == fMinEnergyCmd )
    fFlat -> SetMinEnergy( fMinEnergyCmd -> GetNewDoubleValue( value ) );
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalGammaMessenger CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalGammaMessenger::EMCalGammaMessenger( EMCalGamma *randGen ) :
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

//_______________________________________________________________________________
// Destructor
EMCalGammaMessenger::~EMCalGammaMessenger() {

  delete fKcmd;
  delete fLambdaCmd;
}

//_______________________________________________________________________________
// Modifies the value of one of the attributes
void EMCalGammaMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fKcmd )
    fGamma -> SetK( fKcmd -> GetNewDoubleValue( value ) );
  if ( command == fLambdaCmd )
    fGamma -> SetLambda( fLambdaCmd -> GetNewDoubleValue( value ) );
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalGaussMessenger CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalGaussMessenger::EMCalGaussMessenger( EMCalGauss *randGen ) :
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

//_______________________________________________________________________________
// Destructor
EMCalGaussMessenger::~EMCalGaussMessenger() {

  delete fMeanCmd;
  delete fSigmaCmd;
}

//_______________________________________________________________________________
// Modifies the value of one of the attributes
void EMCalGaussMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fMeanCmd )
    fGauss -> SetMean( fMeanCmd -> GetNewDoubleValue( value ) );
  if ( command == fSigmaCmd )
    fGauss -> SetSigma( fSigmaCmd -> GetNewDoubleValue( value ) );
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalLinearMessenger CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalLinearMessenger::EMCalLinearMessenger( EMCalLinear *randGen ) :
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

//_______________________________________________________________________________
// Destructor
EMCalLinearMessenger::~EMCalLinearMessenger() {

  delete fMaxEnergyCmd;
  delete fMaxMinPropCmd;
  delete fMinEnergyCmd;
}

//_______________________________________________________________________________
// Modifies the value of one of the attributes
void EMCalLinearMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fMaxEnergyCmd )
    fLinear -> SetMaxEnergy( fMaxEnergyCmd -> GetNewDoubleValue( value ) );
  if ( command == fMinEnergyCmd )
    fLinear -> SetMinEnergy( fMinEnergyCmd -> GetNewDoubleValue( value ) );
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalPointMessenger CLASS ---

//_______________________________________________________________________________
// Constructor
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

//_______________________________________________________________________________
// Destructor
EMCalPointMessenger::~EMCalPointMessenger() { delete fEnergyCmd; }

//_______________________________________________________________________________
// Modifies the value of one of the attributes
void EMCalPointMessenger::SetNewValue( G4UIcommand *command, G4String value ) {
  
  if ( command == fEnergyCmd )
    fPoint -> SetEnergy( fEnergyCmd -> GetNewDoubleValue( value ) );
}
