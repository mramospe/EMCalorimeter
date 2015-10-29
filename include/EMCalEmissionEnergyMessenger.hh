//////////////////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------------------- //
//                                                                                  //
//  AUTHOR: Miguel Ramos Pernas                                                     //
//  e-mail: miguel.ramos.pernas@cern.ch                                             //
//                                                                                  //
//  Last update: 29/10/2015                                                         //
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


#ifndef EMCalEmissionEnergyMessenger_h
#define EMCalEmissionEnergyMessenger_h 1

#include "EMCalEmissionEnergy.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "globals.hh"


//_______________________________________________________________________________
// Messenger for the Breit-Wigner shape
class EMCalBreitWignerMessenger: public G4UImessenger {

public:

  // Constructor and destructor
  EMCalBreitWignerMessenger( EMCalBreitWigner *randGen );
  ~EMCalBreitWignerMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String value );

protected:

  // Attributes
  EMCalBreitWigner          *fBreitWigner;
  G4UIdirectory             *fDir;
  G4UIcmdWithADoubleAndUnit *fMeanCmd;
  G4UIcmdWithADoubleAndUnit *fWidthCmd;
};

//_______________________________________________________________________________
// Messenger for the exponential shape
class EMCalExponentialMessenger: public G4UImessenger {

public:

  // Constructor and destructor
  EMCalExponentialMessenger( EMCalExponential *randGen );
  ~EMCalExponentialMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String value );

protected:

  // Attributes
  EMCalExponential          *fExponential;
  G4UIcmdWithADoubleAndUnit *fExpParCmd;
  G4UIcmdWithADoubleAndUnit *fMaxEnergyCmd;
  G4UIcmdWithADoubleAndUnit *fMinEnergyCmd;
};

//_______________________________________________________________________________
// Messenger for the flat shape
class EMCalFlatMessenger: public G4UImessenger {

public:

  // Constructor and destructor
  EMCalFlatMessenger( EMCalFlat *randGen );
  ~EMCalFlatMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String value );

protected:

  // Attributes
  EMCalFlat                 *fFlat;
  G4UIcmdWithADoubleAndUnit *fMaxEnergyCmd;
  G4UIcmdWithADoubleAndUnit *fMinEnergyCmd;
};

//_______________________________________________________________________________
// Messenger for the gamma shape
class EMCalGammaMessenger: public G4UImessenger {

public:

  // Constructor and destructor
  EMCalGammaMessenger( EMCalGamma *randGen );
  ~EMCalGammaMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String value );

protected:

  // Attributes
  EMCalGamma         *fGamma;
  G4UIcmdWithADouble *fKcmd;
  G4UIcmdWithADouble *fLambdaCmd;
};

//_______________________________________________________________________________
// Messenger for the gaussian shape
class EMCalGaussMessenger: public G4UImessenger {

public:

  // Constructor and destructor
  EMCalGaussMessenger( EMCalGauss *randGen );
  ~EMCalGaussMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String value );

protected:

  // Attributes
  EMCalGauss                *fGauss;
  G4UIcmdWithADoubleAndUnit *fMeanCmd;
  G4UIcmdWithADoubleAndUnit *fSigmaCmd;
};

//_______________________________________________________________________________
// Messenger for the linear shape
class EMCalLinearMessenger: public G4UImessenger {

public:

  // Constructor and destructor
  EMCalLinearMessenger( EMCalLinear *randGen );
  ~EMCalLinearMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String value );

protected:

  // Attributes
  EMCalLinear               *fLinear;
  G4UIcmdWithADoubleAndUnit *fMaxEnergyCmd;
  G4UIcmdWithADouble        *fMaxMinPropCmd;
  G4UIcmdWithADoubleAndUnit *fMinEnergyCmd;
};

//_______________________________________________________________________________
// Messenger for the point-like emission
class EMCalPointMessenger: public G4UImessenger {

public:

  // Constructor and destructor
  EMCalPointMessenger( EMCalPoint *randGen );
  ~EMCalPointMessenger();

  // Method
  void SetNewValue( G4UIcommand *command, G4String value );

protected:

  // Attributes
  EMCalPoint                *fPoint;
  G4UIcmdWithADoubleAndUnit *fEnergyCmd;
};


#endif
