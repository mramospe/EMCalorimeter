///////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------- //
//                                                                               //
//  AUTHOR: Miguel Ramos Pernas                                                  //
//  e-mail: miguel.ramos.pernas@cern.ch                                          //
//                                                                               //
//  Last update: 29/10/2015                                                      //
//                                                                               //
// ----------------------------------------------------------------------------- //
//                                                                               //
//  Description:                                                                 //
//                                                                               //
//  Defines the class EMCalModule. The detector is composed by a number of this  //
//  modules, which have two parts, an active part and a shower-generator volume  //
//  ( SGV ).                                                                     //
//                                                                               //
// ----------------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////////////


#include "EMCalModule.hh"


//_______________________________________________________________________________
// Constructor
EMCalModule::EMCalModule( const G4String &name ) :
  fID( name ),
  fLogicalDetector( 0 ),
  fLogicalSGVolume( 0 ),
  fSolidDetector( 0 ),
  fSolidSGVolume( 0 ) { }

//_______________________________________________________________________________
// Destructor
EMCalModule::~EMCalModule() { }

//_______________________________________________________________________________
// Configures the detector volume of the module
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

//_______________________________________________________________________________
// Configures the shower-generator volume of the module
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
