#ifndef EMCalDetectorConstruction_h
#define EMCalDetectorConstruction_h 1

#include "EMCalModule.hh"

#include "G4RunManager.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"

#include <vector>

// Tells EMCalDetectorConstruction that this class already exists
class EMCalDetectorMessenger;

class EMCalDetectorConstruction : public G4VUserDetectorConstruction {

public:

  // Constructor
  EMCalDetectorConstruction();

  // Destructor
  virtual ~EMCalDetectorConstruction();

  // Main methods
  virtual G4VPhysicalVolume*            Construct();
  inline const G4LogicalVolume*         GetDetector( G4int idet ) const;
  inline const G4LogicalVolume*         GetSGVolume( G4int idet ) const;
  inline std::vector<EMCalModule*>      GetModuleArray() const;
  inline unsigned int                   GetNmodules() const;

  // Messenger methods
  void        DefineMaterials();
  inline void PrintParameters();
  inline void SetDetectorMaterial( G4String material );
  inline void SetDistance( G4double value );
  inline void SetModuleHalfLengthX( G4double hlength );
  inline void SetModuleHalfLengthY( G4double hlength );
  inline void SetModuleHalfLengthZ( G4double hlength );
  inline void SetModuleProportion( G4double proportion );
  inline void SetNxModules( G4int nmodules );
  inline void SetNyModules( G4int nmodules );
  inline void SetNzModules( G4int nmodules );
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
  G4String fDetectorMaterial;
  G4double fDistance;
  G4double fModuleHalfLengthX;
  G4double fModuleHalfLengthY;
  G4double fModuleHalfLengthZ;
  G4double fModuleProportion;
  G4int    fNxModules;
  G4int    fNyModules;
  G4int    fNzModules;
  G4String fSGVolumeMaterial;
  G4String fWorldMaterial;
  G4double fWorldHalfLengthX;
  G4double fWorldHalfLengthY;
  G4double fWorldHalfLengthZ;

};

inline const G4LogicalVolume*
EMCalDetectorConstruction::GetDetector( G4int idet ) const {
  return fDetectorArray.at( idet );
}
inline const G4LogicalVolume*
EMCalDetectorConstruction::GetSGVolume( G4int isgv ) const {
  return fSGVolumeArray.at( isgv );
}
// Returns the array of modules
inline std::vector<EMCalModule*>
EMCalDetectorConstruction::GetModuleArray() const {
  return fModuleArray;
}
// Returns the number of modules
inline unsigned int
EMCalDetectorConstruction::GetNmodules() const {
  return fModuleArray.size();
}


// Prints the parameters of the detector
inline void EMCalDetectorConstruction::PrintParameters() {

  G4cout << " *** Detector parameters ***" << G4endl;
  G4cout << " World material:   \t" << fWorldMaterial    << G4endl;
  G4cout << " Detector material:\t" << fDetectorMaterial << G4endl;
  G4cout << " SGVolume material:\t" << fSGVolumeMaterial << G4endl;
  G4cout << " World dimensions: \t"
	 << G4BestUnit( fWorldHalfLengthX, "Length" ) << "\t"
	 << G4BestUnit( fWorldHalfLengthY, "Length" ) << "\t"
	 << G4BestUnit( fWorldHalfLengthZ, "Length" ) << G4endl;
}
inline void EMCalDetectorConstruction::SetDetectorMaterial( G4String material ) {
  fDetectorMaterial = material;
}
// Sets the distance from the detector to the source
inline void EMCalDetectorConstruction::SetDistance( G4double value ) {
  fDistance = value;
}
inline void EMCalDetectorConstruction::SetModuleHalfLengthX( G4double hlength ) {
  fModuleHalfLengthX = hlength;
}
inline void EMCalDetectorConstruction::SetModuleHalfLengthY( G4double hlength ) {
  fModuleHalfLengthY = hlength;
}
inline void EMCalDetectorConstruction::SetModuleHalfLengthZ( G4double hlength ) {
  fModuleHalfLengthZ = hlength;
}
inline void EMCalDetectorConstruction::SetModuleProportion( G4double proportion ) {
  fModuleProportion = proportion;
}
inline void EMCalDetectorConstruction::SetNxModules( G4int nmodules ) {
  fNxModules = nmodules;
}
inline void EMCalDetectorConstruction::SetNyModules( G4int nmodules ) {
  fNyModules = nmodules;
}
inline void EMCalDetectorConstruction::SetNzModules( G4int nmodules ) {
  fNzModules = nmodules;
}
inline void EMCalDetectorConstruction::SetSGVolumeMaterial( G4String material ) {
  fSGVolumeMaterial = material;
}
inline void EMCalDetectorConstruction::SetWorldHalfLengthX( G4double hlength ) {
  fWorldHalfLengthX = hlength;
}
inline void EMCalDetectorConstruction::SetWorldHalfLengthY( G4double hlength ) {
  fWorldHalfLengthY = hlength;
}
inline void EMCalDetectorConstruction::SetWorldHalfLengthZ( G4double hlength ) {
  fWorldHalfLengthZ = hlength;
}
inline void EMCalDetectorConstruction::SetWorldMaterial( G4String material ) {
  fWorldMaterial = material;
}
// Updates the geometry of the detector
inline void EMCalDetectorConstruction::UpdateGeometry() {
  G4RunManager::GetRunManager() -> DefineWorldVolume( this -> Construct() );
}

#endif

