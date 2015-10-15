#ifndef EMCalModule_h
#define EMCalModule_h 1

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4String.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

class EMCalModule {

public:

  // Constructor
  EMCalModule( const G4String &name );

  // Destructor
  ~EMCalModule();

  // Methods
  void                    ConfigureDetector( const G4String &name,
					     G4double        halflengthX,
					     G4double        halflengthY,
					     G4double        halflengthZ,
					     G4Material     *material );
  void                    ConfigureSGVolume( const G4String &name,
					     G4double        halflengthX,
					     G4double        halflengthY,
					     G4double        halflengthZ,
					     G4Material     *material );
  inline G4LogicalVolume* GetLogicalDetector();
  inline G4LogicalVolume* GetLogicalSGVolume();
  inline G4String         GetID() const;
  inline G4Box*           GetSolidDetector();
  inline G4Box*           GetSolidSGVolume();
  inline void             SetDetectorPlacement( G4RotationMatrix *rotation,
						G4ThreeVector     place,
						G4LogicalVolume  *logicalWorld,
						G4bool           &checkOverlaps );
  inline void             SetSGVolumePlacement( G4RotationMatrix *rotation,
						G4ThreeVector     place,
						G4LogicalVolume  *logicalWorld,
						G4bool           &checkOverlaps );
  inline void             SetDetectorVisAttributes( G4VisAttributes *visatt );
  inline void             SetSGVolumeVisAttributes( G4VisAttributes *visatt );

protected:

  // Attributes

  G4String         fID;
  G4LogicalVolume *fLogicalDetector;
  G4LogicalVolume *fLogicalSGVolume;
  G4Box           *fSolidDetector;
  G4Box           *fSolidSGVolume;

};

// Returns the logical detector
inline G4LogicalVolume* EMCalModule::GetLogicalDetector() {
  return fLogicalDetector;
}
// Returns the logical shower-generator-volume
inline G4LogicalVolume* EMCalModule::GetLogicalSGVolume() {
  return fLogicalSGVolume;
}
// Returns the name of the module
inline G4String EMCalModule::GetID() const {
  return fID;
}
// Returns the solid detector
inline G4Box* EMCalModule::GetSolidDetector() { return fSolidDetector; }
// Returns the solid shower-generator-volume
inline G4Box* EMCalModule::GetSolidSGVolume() { return fSolidSGVolume; }
// Sets the placement of the detector
inline void
EMCalModule::SetDetectorPlacement( G4RotationMatrix *rotation,
				   G4ThreeVector     place,
				   G4LogicalVolume  *logicalWorld,
				   G4bool           &checkOverlaps ) {

  new G4PVPlacement( rotation,
		     place,
		     fLogicalDetector,
		     fLogicalDetector -> GetName(),
		     logicalWorld,
		     false,
		     0,
		     checkOverlaps );
}
// Sets the placement of the shower-generator-volume
inline void
EMCalModule::SetSGVolumePlacement( G4RotationMatrix *rotation,
				   G4ThreeVector     place,
				   G4LogicalVolume  *logicalWorld,
				   G4bool           &checkOverlaps ) {

  new G4PVPlacement( rotation,
		     place,
		     fLogicalSGVolume,
		     fLogicalSGVolume -> GetName(),
		     logicalWorld,
		     false,
		     0,
		     checkOverlaps );
}
// Sets the visualization attributes of the detector
inline void EMCalModule::SetDetectorVisAttributes( G4VisAttributes *visatt ) {
  fLogicalDetector -> SetVisAttributes( visatt );
}
// Sets the visualization attributes of the shower-generator-volume
inline void EMCalModule::SetSGVolumeVisAttributes( G4VisAttributes *visatt ) {
  fLogicalSGVolume -> SetVisAttributes( visatt );
}

#endif
