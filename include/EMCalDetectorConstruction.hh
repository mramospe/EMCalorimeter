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


#ifndef EMCalDetectorConstruction_h
#define EMCalDetectorConstruction_h 1

#include "EMCalModule.hh"

#include "G4RunManager.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "G4Colour.hh"
#include "globals.hh"

#include <vector>


//_______________________________________________________________________________

class EMCalDetectorMessenger;

class EMCalDetectorConstruction : public G4VUserDetectorConstruction {

public:

  // Constructor
  EMCalDetectorConstruction();

  // Destructor
  virtual ~EMCalDetectorConstruction();

  // Main methods
  virtual G4VPhysicalVolume*       Construct();
  inline const G4LogicalVolume*    GetDetector( G4int idet ) const;
  inline const G4LogicalVolume*    GetSGVolume( G4int idet ) const;
  inline std::vector<EMCalModule*> GetModuleArray() const;
  inline size_t                    GetNmodules() const;
  inline G4bool                    SGVenabled() const;

  // Messenger methods
  void        DefineMaterials();
  inline void PrintParameters();
  inline void SetDetectorColour( G4String key );
  inline void SetDetectorMaterial( G4String material );
  inline void SetDistance( G4double value );
  inline void SetModuleHalfLengthX( G4double hlength );
  inline void SetModuleHalfLengthY( G4double hlength );
  inline void SetModuleHalfLengthZ( G4double hlength );
  inline void SetModuleProportion( G4double proportion );
  inline void SetNxModules( G4int nmodules );
  inline void SetNyModules( G4int nmodules );
  inline void SetNzModules( G4int nmodules );
  inline void SetSGVolume( G4bool dec );
  inline void SetSGVolumeColour( G4String key );
  inline void SetSGVolumeMaterial( G4String material );
  inline void SetWorldHalfLengthX( G4double hlength );
  inline void SetWorldHalfLengthY( G4double hlength );
  inline void SetWorldHalfLengthZ( G4double hlength );
  inline void SetWorldMaterial( G4String material );
  inline void UpdateGeometry();

protected:

  // Main attributes
  EMCalDetectorMessenger        *fMessenger;
  std::vector<EMCalModule*>      fModuleArray;
  std::vector<G4LogicalVolume*>  fSGVolumeArray;
  std::vector<G4LogicalVolume*>  fDetectorArray;

  // Messenger attributes
  G4Colour fDetectorColour;
  G4String fDetectorMaterial;
  G4double fDistance;
  G4double fModuleHalfLengthX;
  G4double fModuleHalfLengthY;
  G4double fModuleHalfLengthZ;
  G4double fModuleProportion;
  G4int    fNxModules;
  G4int    fNyModules;
  G4int    fNzModules;
  G4bool   fSGVolume;
  G4Colour fSGVolumeColour;
  G4String fSGVolumeMaterial;
  G4String fWorldMaterial;
  G4double fWorldHalfLengthX;
  G4double fWorldHalfLengthY;
  G4double fWorldHalfLengthZ;
};

//_______________
// INLINE METHODS

// Returns a constant pointer to the logical detector at position < idet >
inline const G4LogicalVolume*
EMCalDetectorConstruction::GetDetector( G4int idet ) const {
  return fDetectorArray.at( idet );
}
// Returns a constant pointer to the shower-generator volume array at position < isgv >
inline const G4LogicalVolume*
EMCalDetectorConstruction::GetSGVolume( G4int isgv ) const {
  return fSGVolumeArray.at( isgv );
}
// Returns the constant array of modules
inline std::vector<EMCalModule*>
EMCalDetectorConstruction::GetModuleArray() const {
  return fModuleArray;
}
// Returns the number of modules
inline size_t
EMCalDetectorConstruction::GetNmodules() const {
  return fModuleArray.size();
}
// Tells if the shower-generator volumes are enabled
inline G4bool
EMCalDetectorConstruction::SGVenabled() const {
  return fSGVolume;
}
// Prints the parameters of the detector
inline void EMCalDetectorConstruction::PrintParameters() {

  G4cout << " *** Detector parameters ***" << G4endl;
  G4cout << " World material:   \t" << fWorldMaterial    << G4endl;
  G4cout << " Detector material:\t" << fDetectorMaterial << G4endl;
  if ( fSGVolume )
    G4cout << " SGVolume material:\t" << fSGVolumeMaterial << G4endl;
  G4cout << " World dimensions: \t"
	 << G4BestUnit( fWorldHalfLengthX, "Length" ) << "\t"
	 << G4BestUnit( fWorldHalfLengthY, "Length" ) << "\t"
	 << G4BestUnit( fWorldHalfLengthZ, "Length" ) << G4endl;
  G4cout << " Number of modules ( Nx, Ny, Nz ):\t"
	 << fNxModules << "\t"
	 << fNyModules << "\t"
	 << fNzModules << G4endl;
  G4cout << " Size of the modules ( X, Y, Z ): \t"
	 << fModuleHalfLengthX << "\t"
	 << fModuleHalfLengthY << "\t"
	 << fModuleHalfLengthZ << G4endl;
  if ( fSGVolume )
    G4cout << " Detector/module proportion:      \t" << fModuleProportion << G4endl;
  G4cout << " Distance to source:              \t" << fDistance << G4endl;
}
// Sets the detector colour given its name
inline void EMCalDetectorConstruction::SetDetectorColour( G4String key ) {
  G4Colour::GetColour( key, fDetectorColour );
}
// Sets the detector material, defined at NIST or in the DefineMaterials method
inline void EMCalDetectorConstruction::SetDetectorMaterial( G4String material ) {
  fDetectorMaterial = material;
}
// Sets the distance from the detector to the source
inline void EMCalDetectorConstruction::SetDistance( G4double value ) {
  fDistance = value;
}
// Sets the half lengths of the modules
inline void EMCalDetectorConstruction::SetModuleHalfLengthX( G4double hlength ) {
  fModuleHalfLengthX = hlength;
}
inline void EMCalDetectorConstruction::SetModuleHalfLengthY( G4double hlength ) {
  fModuleHalfLengthY = hlength;
}
inline void EMCalDetectorConstruction::SetModuleHalfLengthZ( G4double hlength ) {
  fModuleHalfLengthZ = hlength;
}
// Sets the proportion between the detector part and the entire module. The other part
// corresponds to the shower-generator module, if enabled. Otherwise the proportion will
// be set to one.
inline void EMCalDetectorConstruction::SetModuleProportion( G4double proportion ) {
  fModuleProportion = proportion;
}
// Sets the number of modules in each space direction
inline void EMCalDetectorConstruction::SetNxModules( G4int nmodules ) {
  fNxModules = nmodules;
}
inline void EMCalDetectorConstruction::SetNyModules( G4int nmodules ) {
  fNyModules = nmodules;
}
inline void EMCalDetectorConstruction::SetNzModules( G4int nmodules ) {
  fNzModules = nmodules;
}
// Enables or disables the shower-generator volumes
inline void EMCalDetectorConstruction::SetSGVolume( G4bool dec ) {
  fSGVolume = dec;
}
// Sets the colour of the shower-generator volumes given its name
inline void EMCalDetectorConstruction::SetSGVolumeColour( G4String key ) {
  G4Colour::GetColour( key, fSGVolumeColour );
}
// Sets the shower-generator volume material, defined at NIST or in the
// DefineMaterials method
inline void EMCalDetectorConstruction::SetSGVolumeMaterial( G4String material ) {
  fSGVolumeMaterial = material;
}
// Sets the dimensions of the world
inline void EMCalDetectorConstruction::SetWorldHalfLengthX( G4double hlength ) {
  fWorldHalfLengthX = hlength;
}
inline void EMCalDetectorConstruction::SetWorldHalfLengthY( G4double hlength ) {
  fWorldHalfLengthY = hlength;
}
inline void EMCalDetectorConstruction::SetWorldHalfLengthZ( G4double hlength ) {
  fWorldHalfLengthZ = hlength;
}
// Sets the material of the world
inline void EMCalDetectorConstruction::SetWorldMaterial( G4String material ) {
  fWorldMaterial = material;
}
// Updates the geometry of the detector
inline void EMCalDetectorConstruction::UpdateGeometry() {
  G4RunManager::GetRunManager() -> DefineWorldVolume( this -> Construct() );
}

#endif

