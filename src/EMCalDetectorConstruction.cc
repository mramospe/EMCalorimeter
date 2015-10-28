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
//  Defines the ActionInitialization class for the EMCalorimeter application,    //
//  which generates the PrimaryGeneratorAction, RunAction, EventAction and       //
//  SteppingAction.                                                              //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#include "EMCalDetectorConstruction.hh"
#include "EMCalDetectorMessenger.hh"
#include "EMCalSteppingAction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

#include <sstream>


//_______________________________________________________________________________
// Constructor
EMCalDetectorConstruction::EMCalDetectorConstruction() :
  G4VUserDetectorConstruction() {

  fMessenger = new EMCalDetectorMessenger( this );

  // Default values
  fWorldMaterial    = "G4_AIR";
  fDetectorMaterial = "G4_SODIUM_IODIDE";
  fSGVolumeMaterial = "G4_Pb";

  // World size
  fWorldHalfLengthX = 10*m;
  fWorldHalfLengthY = 10*m;
  fWorldHalfLengthZ = 10*m;

  // Module size
  fModuleHalfLengthX = 4*m;
  fModuleHalfLengthY = 3*m;
  fModuleHalfLengthZ = 0.5*m;

  // Number of modules in x-y-z axis
  fNxModules = 3;
  fNyModules = 3;
  fNzModules = 3;

  // Distance from the source to the detector
  fDistance = 7*m;

  // Enables by default the shower-generator volume
  fSGVolume = true;

  // Proportion detector_width/complete_width
  fModuleProportion = 1*m/( 1*m + 5*cm );

  // Colours of the detector
  fDetectorColour = G4Colour( 0. , 0.6, 0.1, 0.85 );
  fSGVolumeColour = G4Colour( 0.6, 0.6, 0.6, 1.   );

  // Defines the materials
  this -> DefineMaterials();
}

//_______________________________________________________________________________
// Destructor
EMCalDetectorConstruction::~EMCalDetectorConstruction() {

  delete fMessenger;

  for ( std::vector<EMCalModule*>::iterator it = fModuleArray.begin();
	it != fModuleArray.end(); it++ ) delete *it;
}

//_______________________________________________________________________________
// Constructs the detector
G4VPhysicalVolume* EMCalDetectorConstruction::Construct() {

  // If the modules are defined they are deleted. Since G4LogicalVolume can not be destroyed,
  // because are owned by the RunManager, the SGVolume and Detector arrays are reinitialised.
  fDetectorArray = std::vector<G4LogicalVolume*>();
  if ( fSGVolume )
    fSGVolumeArray = std::vector<G4LogicalVolume*>();
  fModuleArray.clear();

  // Get nist material manager
  G4NistManager *nist = G4NistManager::Instance();

  // Activates checking for overlaps ( < true > for debugging )
  bool checkOverlaps = false;

  // Materials definition
  G4Material
    *worldMaterial = nist -> FindOrBuildMaterial( fWorldMaterial ),
    *detMaterial   = nist -> FindOrBuildMaterial( fDetectorMaterial ),
    *sgvMaterial   = nist -> FindOrBuildMaterial( fSGVolumeMaterial );

  if ( !worldMaterial )
    worldMaterial = G4Material::GetMaterial( fWorldMaterial );
  if ( !detMaterial )
    detMaterial = G4Material::GetMaterial( fDetectorMaterial );
  if ( !sgvMaterial )
    sgvMaterial = G4Material::GetMaterial( fSGVolumeMaterial );

  // ----------------------------------
  // World construction
  
  G4Box *solidWorld =    
    new G4Box( "World",
	       fWorldHalfLengthX,
	       fWorldHalfLengthY,
	       fWorldHalfLengthZ );
      
  G4LogicalVolume *logicWorld =         
    new G4LogicalVolume( solidWorld,
                         worldMaterial,
                         "World" );
                                   
  G4VPhysicalVolume *physWorld = 
    new G4PVPlacement( 0,
		       G4ThreeVector(),
		       logicWorld,
		       "World",
		       0,
		       false,
		       0,
		       checkOverlaps );

  logicWorld -> SetVisAttributes( G4VisAttributes::GetInvisible() );
  
  // -------------------------------------------------------------------------------
  // Detector construction
  std::stringstream  modName, detName, sgvName;

  // If the shower-generator volume is not enabled the proportion is set to one
  if ( !fSGVolume )
    fModuleProportion = 1;

  G4double
    detHalfLengthX = fModuleHalfLengthX/fNxModules,
    detHalfLengthY = fModuleHalfLengthY/fNyModules,
    detHalfLengthZ = fModuleHalfLengthZ/fNzModules*fModuleProportion,
    sgvHalfLengthZ = fModuleHalfLengthZ/fNzModules*( 1 - fModuleProportion ),
    xpos, ypos;

  G4ThreeVector sgvPosition, detPosition;

  EMCalModule *module;

  for ( G4int zdet = 0; zdet < fNzModules; zdet++ ) {

    sgvPosition.setZ( fDistance +
		      ( 2.*zdet + 1 )*sgvHalfLengthZ +
		      2.*zdet*detHalfLengthZ );
    detPosition.setZ( fDistance +
		      ( 2.*zdet + 1 )*detHalfLengthZ +
		      2.*( zdet + 1 )*sgvHalfLengthZ );

    for ( G4int ydet = 0; ydet < fNyModules; ydet++ ) {

      ypos = -fModuleHalfLengthY + ( 2.*ydet + 1 )*detHalfLengthY;

      for ( G4int xdet = 0; xdet < fNxModules; xdet++ ) {

	xpos = -fModuleHalfLengthX + ( 2.*xdet + 1 )*detHalfLengthX;

	// Name for the module branches
	modName.str( "" );
	modName << "Mod_";
	modName << xdet;
	modName << ydet;
	modName << zdet;

	// Creates a new module
	module = new EMCalModule( modName.str() );

	// Name for the detector and shower-generator-volume
	detName.str( "" );
	detName << "Detector_";
	detName << xdet;
	detName << ydet;
	detName << zdet;
	detPosition.setX( xpos );
	detPosition.setY( ypos );

	// Configures both detector and shower-generator-volume
	module -> ConfigureDetector( detName.str(),
				     detHalfLengthX,
				     detHalfLengthY,
				     detHalfLengthZ,
				     detMaterial );
	module -> SetDetectorPlacement( 0,
					detPosition,
					logicWorld,
					checkOverlaps );
	module -> SetDetectorVisAttributes( new G4VisAttributes( fDetectorColour ) );

	fDetectorArray.push_back( module -> GetLogicalDetector() );

	// If the shower-generator volume is enabled it is created
	if ( fSGVolume ) {

	  sgvName.str( "" );
	  sgvName << "SGVolume_";
	  sgvName << xdet;
	  sgvName << ydet;
	  sgvName << zdet;
	  sgvPosition.setX( xpos );
	  sgvPosition.setY( ypos );

	  module -> ConfigureSGVolume( sgvName.str(),
				       detHalfLengthX,
				       detHalfLengthY,
				       sgvHalfLengthZ,
				       sgvMaterial );

	  module -> SetSGVolumePlacement( 0,
					  sgvPosition,
					  logicWorld,
					  checkOverlaps );
	  module -> SetSGVolumeVisAttributes( new G4VisAttributes( fSGVolumeColour ) );

	  fSGVolumeArray.push_back( module -> GetLogicalSGVolume() );
	}

	fModuleArray.push_back( module );
      }
    }
  }

  return physWorld;
}

//_______________________________________________________________________________
// Defines different materials
void EMCalDetectorConstruction::DefineMaterials() { 

  // Atomic number and atomic mass
  G4double Z, A;
  
  // Defines different elements
  G4Element *H  = new G4Element( "Hydrogen" , "H" , Z = 1. , A =    1.00794*g/mole );
  G4Element *N  = new G4Element( "Nitrogen" , "N" , Z = 7. , A =   14.00674*g/mole );
  G4Element *O  = new G4Element( "Oxygen"   , "O" , Z = 8. , A =    15.9994*g/mole );
  G4Element *Ge = new G4Element( "Germanium", "Ge", Z = 32., A =      72.61*g/mole );
  G4Element *Bi = new G4Element( "Bismuth"  , "Bi", Z = 83., A =  208.98038*g/mole );
  G4Element *Na = new G4Element( "Sodium"   , "Na", Z = 11., A =   22.98977*g/mole );
  G4Element *I  = new G4Element( "Iodine"   , "I",  Z = 53., A =  126.90447*g/mole );
  G4Element *Ba = new G4Element( "Barium"   , "Ba", Z = 56., A =    137.327*g/mole );
  G4Element *F  = new G4Element( "Fluorine" , "F",  Z = 9. , A = 18.9984032*g/mole );
  G4Element *C  = new G4Element( "Carbon"   , "C",  Z = 6. , A =    12.0107*g/mole );
  G4Element *Ce = new G4Element( "Cerium"   , "Ce", Z = 58., A =    140.116*g/mole );
  G4Element *Cs = new G4Element( "Cesium"   , "Cs", Z = 55., A =  132.90545*g/mole );
  G4Element *La = new G4Element( "Lanthanum", "La", Z = 57., A =   138.9055*g/mole );
  G4Element *Br = new G4Element( "Bromine"  , "Br", Z = 35., A =     79.904*g/mole );
  G4Element *Lu = new G4Element( "Lutecium" , "Lu", Z = 71., A =    174.967*g/mole );
  G4Element *S  = new G4Element( "Sulphur"  , "S",  Z = 16., A =     32.066*g/mole );
  G4Element *Cd = new G4Element( "Cadmium"  , "Cd", Z = 48., A =    112.411*g/mole );
  G4Element *Zn = new G4Element( "Zinc"     , "Zn", Z = 30., A =      65.39*g/mole );
  G4Element *Te = new G4Element( "Tellurium", "Te", Z = 52., A =     127.60*g/mole );
  G4Element *W  = new G4Element( "Tungsten" , "W" , Z = 74., A =     183.84*g/mole );
  G4Element *Pb = new G4Element( "Lead"     , "Pb", Z = 82., A =     207.20*g/mole );

  // Defines the materials
  G4double density, fractionmass;
  G4int    ncomponents, natoms;
  
  G4Material *Vacuum =
    new G4Material( "Galactic",
		    Z = 1., A = 1.01*g/mole,
		    density = CLHEP::universe_mean_density,
		    kStateGas, 3.e-18*pascal, 2.73*kelvin );
  Vacuum -> SetChemicalFormula( "NOMATTER" );

  // Air ( default 1.290*mg/cm3 )
  density = 1.290*mg/cm3;
  G4Material *Air = 
    new G4Material( "Air", density, ncomponents = 2 );
  Air -> AddElement( N, fractionmass = 70.*perCent );
  Air -> AddElement( O, fractionmass = 30.*perCent );
  
  // Isobutane ( default  2.67*mg/cm3 STP )
  density = 2.67*mg/cm3;
  G4Material *isobutane = 
    new G4Material( "isoC4H10STP", density, ncomponents = 2 ) ;
  isobutane -> AddElement( C, 4 );
  isobutane -> AddElement( H, 10 );
  
  // Isobutane ( default  2.67*mg/cm3 STP )
  density = 2.67*mg/cm3;
  G4Material *isobutane01 = 
    new G4Material( "isoC4H10_0.1", 0.001*density, ncomponents = 2 ) ;
  isobutane01 -> AddElement( C, 4 );
  isobutane01 -> AddElement( H, 10 );

  G4Material *isobutane1 = 
    new G4Material( "isoC4H10_1", 0.01*density, ncomponents = 2 ) ;
  isobutane1 -> AddElement( C, 4 );
  isobutane1 -> AddElement( H, 10 );

  G4Material *isobutane10 = 
    new G4Material( "isoC4H10_10", 0.1*density, ncomponents = 2 ) ;
  isobutane10 -> AddElement( C, 4 );
  isobutane10 -> AddElement( H, 10 );

  G4Material *isobutane50 = 
    new G4Material( "isoC4H10_50", 0.5*density, ncomponents = 2 ) ;
  isobutane50 -> AddElement( C, 4 );
  isobutane50 -> AddElement( H, 10 );

  // Methane ( default  0.7174*mg/cm3 STP )
  density = 0.7174*mg/cm3;
  G4Material *methane = 
    new G4Material( "CH4", density, ncomponents = 2 ) ;
  methane -> AddElement( C, 1 );
  methane -> AddElement( H, 4 );
  
  // Propane ( default  2.005*mg/cm3 STP )
  density = 2.005*mg/cm3;
  G4Material *propane = 
    new G4Material( "C3H8", density, ncomponents = 2 ) ;
  propane -> AddElement( C, 3 );
  propane -> AddElement( H, 8 ); 

  // Benzene ( default  0.8786*g/cm3 STP )
  density = 0.8786*g/cm3;
  G4Material *benzene = 
    new G4Material( "C6H6", density, ncomponents = 2 ) ;
  benzene -> AddElement( C, 6 );
  benzene -> AddElement( H, 6 ); 


  G4Material *H2O = 
    new G4Material( "Water", density = 1.000*g/cm3, ncomponents = 2 );
  H2O -> AddElement( H, natoms = 2 );
  H2O -> AddElement( O, natoms = 1 );
  H2O -> SetChemicalFormula( "H_2O" );
  H2O -> GetIonisation(  ) -> SetMeanExcitationEnergy( 75.0*eV );
  
  G4Material *BGO = 
    new G4Material( "BGO", density = 7.10*g/cm3, ncomponents = 3 );
  BGO -> AddElement( O , natoms = 12 );
  BGO -> AddElement( Ge, natoms = 3 );
  BGO -> AddElement( Bi, natoms = 4 );  
  
  G4Material *SodiumIodide = 
    new G4Material( "NaI", density = 3.67*g/cm3, ncomponents = 2 );
  SodiumIodide -> AddElement( Na , natoms = 1 );
  SodiumIodide -> AddElement( I , natoms = 1 );

  G4Material *BariumFluoride = 
    new G4Material( "BaF", density = 4.89*g/cm3, ncomponents = 2 );
  BariumFluoride -> AddElement( Ba , natoms = 1 );
  BariumFluoride -> AddElement( F , natoms = 2 );

  G4Material * CesiumIodide= 
    new G4Material( "CsI", density = 4.51*g/cm3, ncomponents = 2 );
  CesiumIodide -> AddElement( Cs, natoms = 1 );
  CesiumIodide -> AddElement( I, natoms = 1 );
  
  G4Material *CeriumFluoride = 
    new G4Material( "CeF3", density = 6.16*g/cm3, ncomponents = 2 );
  CeriumFluoride -> AddElement( Ce , natoms = 1 );
  CeriumFluoride -> AddElement( F , natoms = 3 );
  
  G4Material *LantanumBromide = 
    new G4Material( "LaBr3", density = 5.29*g/cm3, ncomponents = 2 );
  LantanumBromide -> AddElement( La , natoms = 1 );
  LantanumBromide -> AddElement( Br , natoms = 3 );
  
  G4Material * LSO= 
    new G4Material( "LSO", density = 7.4*g/cm3, ncomponents = 3 );
  LSO -> AddElement( Lu , natoms = 2 );
  LSO -> AddElement( S , natoms = 1 );
  LSO -> AddElement( O , natoms = 5 );

  G4Material *CdZnTe=
    new G4Material( "CdZnTe", density = 5.78*g/cm3, ncomponents = 3 );
  CdZnTe -> AddElement( Cd, natoms = 9 );
  CdZnTe -> AddElement( Zn, natoms = 1 );
  CdZnTe -> AddElement( Te, natoms = 10 );

  G4Material *PWO=
    new G4Material( "PWO", density = 8.28*g/cm3, ncomponents = 3 );
  PWO -> AddElement( Pb, natoms = 1 );
  PWO -> AddElement( W, natoms = 1 );
  PWO -> AddElement( O, natoms = 4 );

  // Deuterium at 0.1 atm
  G4Material *Deuterium = 
    new G4Material( "Deuterium", density = 0.0169*g/cm3, ncomponents = 2 );
  Deuterium -> AddElement( H, natoms=1 );
  Deuterium -> AddElement( H, natoms=1 );
  
  new G4Material( "Silicon"    , Z = 14., A =  28.09*g/mole, density = 2.330*g/cm3 );
  new G4Material( "Germanium"  , Z = 32., A =  72.61*g/mole, density = 5.323*g/cm3 );
  new G4Material( "Iron"       , Z = 26., A =  55.85*g/mole, density = 7.870*g/cm3 );
  new G4Material( "Tungsten"   , Z = 74., A = 183.85*g/mole, density = 19.30*g/cm3 );
  new G4Material( "Lead"       , Z = 82., A = 207.19*g/mole, density = 11.35*g/cm3 );
  new G4Material( "Uranium"    , Z = 92., A = 238.03*g/mole, density = 18.95*g/cm3 );
}
