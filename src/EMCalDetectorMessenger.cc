///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
//                                                                               //
//  AUTHOR: Miguel Ramos Pernas                                                  //
//  e-mail: miguel.ramos.pernas@cern.ch                                          //
//                                                                               //
//  Last update: 26/10/2015                                                      //
//                                                                               //
// ----------------------------------------------------------------------------- //
//                                                                               //
//  Description:                                                                 //
//                                                                               //
//  This is the messenger for the EMCalDetectorConstruction class. All commands  //
//  are available in the states PreInit and Idle.                                //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#include "EMCalDetectorMessenger.hh"


//_______________________________________________________________________________
// Constructor
EMCalDetectorMessenger::
EMCalDetectorMessenger( EMCalDetectorConstruction *detector ) : fDetector( detector ) {

  // Defines the detector directories
  fEMCalDir = new G4UIdirectory( "/EMCal/" );
  fEMCalDir -> SetGuidance( "UI commands of EMCal program" );

  fDetDir = new G4UIdirectory( "/EMCal/detector/" );
  fDetDir -> SetGuidance( "Detector control" );

  // To define the detector colour
  fDetectorColourCmd
    = new G4UIcmdWithAString( "/EMCal/detector/setDetectorColour", this );
  fDetectorColourCmd -> SetGuidance( "Colour of the detector volume" );
  fDetectorColourCmd -> SetParameterName( "DetectorColour", false );
  fDetectorColourCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  // To define the detector material
  fDetectorMaterialCmd
    = new G4UIcmdWithAString( "/EMCal/detector/setDetectorMaterial", this );
  fDetectorMaterialCmd -> SetGuidance( "Select the world material" );
  fDetectorMaterialCmd -> SetParameterName( "DetectorMaterial", false );
  fDetectorMaterialCmd -> SetDefaultValue( "G4_SODIUM_IODIDE" );
  fDetectorMaterialCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  // Distance from source
  fDistanceCmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/detector/setDistance", this );
  fDistanceCmd -> SetGuidance( "Distance from the source to the detector" );
  fDistanceCmd -> SetParameterName( "Distance", false );
  fDistanceCmd -> SetRange( "Distance > 0" );
  fDistanceCmd -> SetUnitCategory( "Length" );
  fDistanceCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  // Modules' size
  fModuleHalfLengthXcmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/detector/setModuleHalfLengthX", this );
  fModuleHalfLengthXcmd -> SetGuidance( "Select the x-halflength of the modules" );
  fModuleHalfLengthXcmd -> SetParameterName( "ModuleHalfLengthX", false );
  fModuleHalfLengthXcmd -> SetRange( "ModuleHalfLengthX > 0" );
  fModuleHalfLengthXcmd -> SetUnitCategory( "Length" );
  fModuleHalfLengthXcmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  fModuleHalfLengthYcmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/detector/setModuleHalfLengthY", this );
  fModuleHalfLengthYcmd -> SetGuidance( "Select the y-halflength of the modules" );
  fModuleHalfLengthYcmd -> SetParameterName( "ModuleHalfLengthY", false );
  fModuleHalfLengthYcmd -> SetRange( "ModuleHalfLengthY > 0" );
  fModuleHalfLengthYcmd -> SetUnitCategory( "Length" );
  fModuleHalfLengthYcmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  fModuleHalfLengthZcmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/detector/setModuleHalfLengthZ", this );
  fModuleHalfLengthZcmd -> SetGuidance( "Select the z-halflength of the modules" );
  fModuleHalfLengthZcmd -> SetParameterName( "ModuleHalfLengthZ", false );
  fModuleHalfLengthZcmd -> SetRange( "ModuleHalfLengthZ > 0" );
  fModuleHalfLengthZcmd -> SetUnitCategory( "Length" );
  fModuleHalfLengthZcmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  // Proportion of the detector
  fModuleProportionCmd
    = new G4UIcmdWithADouble( "/EMCal/detector/setModuleProportion", this );
  fModuleProportionCmd ->
    SetGuidance( "Set width proportion of the detector in the module" );
  fModuleProportionCmd -> SetParameterName( "ModuleProportion", false );
  fModuleProportionCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );  

  // Number of modules in each direction
  fNxModulesCmd
    = new G4UIcmdWithAnInteger( "/EMCal/detector/setNxModules", this );
  fNxModulesCmd -> SetGuidance( "Set the number of X-modules" );
  fNxModulesCmd -> SetParameterName( "NxModules", false );
  fNxModulesCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );  

  fNyModulesCmd
    = new G4UIcmdWithAnInteger( "/EMCal/detector/setNyModules", this );
  fNyModulesCmd -> SetGuidance( "Set the number of X-modules" );
  fNyModulesCmd -> SetParameterName( "NyModules", false );
  fNyModulesCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );  

  fNzModulesCmd
    = new G4UIcmdWithAnInteger( "/EMCal/detector/setNzModules", this );
  fNzModulesCmd -> SetGuidance( "Set the number of X-modules" );
  fNzModulesCmd -> SetParameterName( "NzModules", false );
  fNzModulesCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );  

  // Print command
  fPrintCmd = new G4UIcmdWithoutParameter( "/EMCal/detector/printParameters", this );
  fPrintCmd -> SetGuidance("Prints geometry");
  fPrintCmd -> AvailableForStates( G4State_Idle );

  fSGVolumeCmd
    = new G4UIcmdWithABool( "/EMCal/detector/SGVenabled", this );
  fSGVolumeCmd -> SetGuidance( "Enable or disable the shower-generator volume" );
  fSGVolumeCmd -> SetParameterName( "SGVolume", false );
  fSGVolumeCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  // To define the shower-generator volume colour
  fSGVolumeColourCmd
    = new G4UIcmdWithAString( "/EMCal/detector/setSGVolumeColour", this );
  fSGVolumeColourCmd -> SetGuidance( "Colour of the detector volume" );
  fSGVolumeColourCmd -> SetParameterName( "SGVolumeColour", false );
  fSGVolumeColourCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  // To define the shower-generator volume material
  fSGVolumeMaterialCmd
    = new G4UIcmdWithAString( "/EMCal/detector/setSGVolumeMaterial", this );
  fSGVolumeMaterialCmd -> SetGuidance( "Select the world material" );
  fSGVolumeMaterialCmd -> SetParameterName( "SGVolumeMaterial", false );
  fSGVolumeMaterialCmd -> SetDefaultValue( "G4_Pb" );
  fSGVolumeMaterialCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  // Command to update the geometry
  fUpdateCmd = new G4UIcmdWithoutParameter( "/EMCal/detector/update", this );
  fUpdateCmd -> SetGuidance( "Update geometry" );
  fUpdateCmd -> SetGuidance( "This command MUST be applied before \"beamOn\"" );
  fUpdateCmd -> AvailableForStates( G4State_Idle );

  // To change the world parameters
  fWorldMaterialCmd
    = new G4UIcmdWithAString( "/EMCal/detector/setWorldMaterial", this );
  fWorldMaterialCmd -> SetGuidance( "Select the world material" );
  fWorldMaterialCmd -> SetParameterName( "WorldMaterial", false );
  fWorldMaterialCmd -> SetDefaultValue( "G4_AIR" );
  fWorldMaterialCmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  fWorldHalfLengthXcmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/detector/setWorldHalfLengthX", this );
  fWorldHalfLengthXcmd -> SetGuidance( "Select the x-halflength of the world" );
  fWorldHalfLengthXcmd -> SetParameterName( "WorldHalfLengthX", false );
  fWorldHalfLengthXcmd -> SetRange( "WorldHalfLengthX > 0" );
  fWorldHalfLengthXcmd -> SetUnitCategory( "Length" );
  fWorldHalfLengthXcmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  fWorldHalfLengthYcmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/detector/setWorldHalfLengthY", this );
  fWorldHalfLengthYcmd -> SetGuidance( "Select the y-halflength of the world" );
  fWorldHalfLengthYcmd -> SetParameterName( "WorldHalfLengthY", false );
  fWorldHalfLengthYcmd -> SetRange( "WorldHalfLengthY > 0" );
  fWorldHalfLengthYcmd -> SetUnitCategory( "Length" );
  fWorldHalfLengthYcmd -> AvailableForStates( G4State_PreInit, G4State_Idle );

  fWorldHalfLengthZcmd
    = new G4UIcmdWithADoubleAndUnit( "/EMCal/detector/setWorldHalfLengthZ", this );
  fWorldHalfLengthZcmd -> SetGuidance( "Select the z-halflength of the world" );
  fWorldHalfLengthZcmd -> SetParameterName( "WorldHalfLengthZ", false );
  fWorldHalfLengthZcmd -> SetRange( "WorldHalfLengthZ > 0" );
  fWorldHalfLengthZcmd -> SetUnitCategory( "Length" );
  fWorldHalfLengthZcmd -> AvailableForStates( G4State_PreInit, G4State_Idle );
}

//_______________________________________________________________________________
// Destructor
EMCalDetectorMessenger::~EMCalDetectorMessenger() {

  delete fEMCalDir;
  delete fDetDir;
  delete fDetectorColourCmd;
  delete fDetectorMaterialCmd;
  delete fDistanceCmd;
  delete fModuleHalfLengthXcmd;
  delete fModuleHalfLengthYcmd;
  delete fModuleHalfLengthZcmd;
  delete fModuleProportionCmd;
  delete fNxModulesCmd;
  delete fNyModulesCmd;
  delete fNzModulesCmd;
  delete fPrintCmd;
  delete fSGVolumeCmd;
  delete fSGVolumeColourCmd;
  delete fSGVolumeMaterialCmd;
  delete fUpdateCmd;
  delete fWorldHalfLengthXcmd;
  delete fWorldHalfLengthYcmd;
  delete fWorldHalfLengthZcmd;
  delete fWorldMaterialCmd;
}

//_______________________________________________________________________________
// Method to set a new value
void EMCalDetectorMessenger::SetNewValue( G4UIcommand *command, G4String value ) {

  // Detector parameters
  if      ( command == fDetectorColourCmd )
    fDetector -> SetDetectorColour( value );
  else if ( command == fDetectorMaterialCmd )
    fDetector -> SetDetectorMaterial( value );
  else if ( command == fDistanceCmd )
    fDetector -> SetDistance( fDistanceCmd -> GetNewDoubleValue( value ) );

  // Module parameters
  else if ( command == fModuleHalfLengthXcmd )
    fDetector ->
      SetModuleHalfLengthX( fModuleHalfLengthXcmd -> GetNewDoubleValue( value ) );
  else if ( command == fModuleHalfLengthYcmd )
    fDetector ->
      SetModuleHalfLengthY( fModuleHalfLengthYcmd -> GetNewDoubleValue( value ) );
  else if ( command == fModuleHalfLengthZcmd )
    fDetector ->
      SetModuleHalfLengthZ( fModuleHalfLengthZcmd -> GetNewDoubleValue( value ) );
  else if ( command == fModuleProportionCmd )
    fDetector ->
      SetModuleProportion( fModuleProportionCmd -> GetNewDoubleValue( value ) );
  else if ( command == fNxModulesCmd )
    fDetector ->
      SetNxModules( fNxModulesCmd -> GetNewIntValue( value ) );
  else if ( command == fNyModulesCmd )
    fDetector ->
      SetNyModules( fNyModulesCmd -> GetNewIntValue( value ) );
  else if ( command == fNzModulesCmd )
    fDetector ->
      SetNzModules( fNzModulesCmd -> GetNewIntValue( value ) );

  // To print the detector parameters
  else if ( command == fPrintCmd )
    fDetector -> PrintParameters();

  // SGV parameters
  else if ( command == fSGVolumeCmd )
    fDetector -> SetSGVolume( fSGVolumeCmd -> GetNewBoolValue( value ) );
  else if ( command == fSGVolumeColourCmd )
    fDetector -> SetSGVolumeColour( value );
  else if ( command == fSGVolumeMaterialCmd )
    fDetector -> SetSGVolumeMaterial( value );

  // To update the geometry
  else if ( command == fUpdateCmd )
    fDetector -> UpdateGeometry();

  // World parameters
  else if ( command == fWorldHalfLengthXcmd )
    fDetector -> SetWorldHalfLengthX( fWorldHalfLengthXcmd -> GetNewDoubleValue( value ) );
  else if ( command == fWorldHalfLengthYcmd )
    fDetector ->
      SetWorldHalfLengthY( fWorldHalfLengthYcmd -> GetNewDoubleValue( value ) );
  else if ( command == fWorldHalfLengthZcmd )
    fDetector ->
      SetWorldHalfLengthZ( fWorldHalfLengthZcmd -> GetNewDoubleValue( value ) );
  else if ( command == fWorldMaterialCmd )
    fDetector -> SetWorldMaterial( value );

  // Otherwise a message is sent
  else
    G4cout << "WARNING: Command with name: < " << command << " > not known" << G4endl;
}
