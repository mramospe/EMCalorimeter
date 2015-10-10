#include "EMCalModule.hh"

EMCalModule::EMCalModule( const G4String &name ) :
  fID( name ),
  fLogicalDetector( 0 ),
  fLogicalSGVolume( 0 ),
  fSolidDetector( 0 ),
  fSolidSGVolume( 0 ) { }

EMCalModule::~EMCalModule() { }

void EMCalModule::ConfigureDetector( const G4String &name,
						 G4double        halflengthX,
						 G4double        halflengthY,
						 G4double        halflengthZ,
						 G4Material     *material ) {

  fSolidDetector = new G4Box( name,
			      halflengthX,
			      halflengthY,
			      halflengthZ );
                
  fLogicalDetector = new G4LogicalVolume( fSolidDetector,
					  material,
					  name );
}

void EMCalModule::ConfigureSGVolume( const G4String &name,
						 G4double        halflengthX,
						 G4double        halflengthY,
						 G4double        halflengthZ,
						 G4Material     *material ) {

  fSolidSGVolume = new G4Box( name,
			      halflengthX,
			      halflengthY,
			      halflengthZ );
                
  fLogicalSGVolume = new G4LogicalVolume( fSolidSGVolume,
					  material,
					  name );
}
