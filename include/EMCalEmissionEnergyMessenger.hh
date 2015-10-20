#ifndef EMCalEmissionEnergyMessenger_h
#define EMCalEmissionEnergyMessenger_h 1

#include "EMCalEmissionEnergy.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "globals.hh"

// ____________________________________________________

class EMCalBreitWignerMessenger: public G4UImessenger {

public:
EMCalBreitWignerMessenger( EMCalBreitWigner *randGen );
~EMCalBreitWignerMessenger();

void SetNewValue( G4UIcommand *command, G4String value );

protected:
  EMCalBreitWigner          *fBreitWigner;
  G4UIdirectory             *fDir;
  G4UIcmdWithADoubleAndUnit *fMeanCmd;
  G4UIcmdWithADoubleAndUnit *fWidthCmd;
};

// ____________________________________________________

class EMCalExponentialMessenger: public G4UImessenger {

public:
EMCalExponentialMessenger( EMCalExponential *randGen );
~EMCalExponentialMessenger();

void SetNewValue( G4UIcommand *command, G4String value );

protected:
EMCalExponential          *fExponential;
G4UIcmdWithADoubleAndUnit *fExpParCmd;
G4UIcmdWithADoubleAndUnit *fMaxEnergyCmd;
G4UIcmdWithADoubleAndUnit *fMinEnergyCmd;
};

// ____________________________________________________

class EMCalFlatMessenger: public G4UImessenger {

public:
EMCalFlatMessenger( EMCalFlat *randGen );
~EMCalFlatMessenger();

void SetNewValue( G4UIcommand *command, G4String value );

protected:
EMCalFlat                 *fFlat;
G4UIcmdWithADoubleAndUnit *fMaxEnergyCmd;
G4UIcmdWithADoubleAndUnit *fMinEnergyCmd;
};

// ____________________________________________________

class EMCalGammaMessenger: public G4UImessenger {

public:
EMCalGammaMessenger( EMCalGamma *randGen );
~EMCalGammaMessenger();

void SetNewValue( G4UIcommand *command, G4String value );

protected:
EMCalGamma         *fGamma;
G4UIcmdWithADouble *fKcmd;
G4UIcmdWithADouble *fLambdaCmd;
};

// ____________________________________________________

class EMCalGaussMessenger: public G4UImessenger {

public:
EMCalGaussMessenger( EMCalGauss *randGen );
~EMCalGaussMessenger();

void SetNewValue( G4UIcommand *command, G4String value );

protected:
EMCalGauss                *fGauss;
G4UIcmdWithADoubleAndUnit *fMeanCmd;
G4UIcmdWithADoubleAndUnit *fSigmaCmd;
};

// ____________________________________________________

class EMCalLinearMessenger: public G4UImessenger {

public:
EMCalLinearMessenger( EMCalLinear *randGen );
~EMCalLinearMessenger();

void SetNewValue( G4UIcommand *command, G4String value );

protected:
EMCalLinear               *fLinear;
G4UIcmdWithADoubleAndUnit *fMaxEnergyCmd;
G4UIcmdWithADouble        *fMaxMinPropCmd;
G4UIcmdWithADoubleAndUnit *fMinEnergyCmd;
};

// ____________________________________________________

class EMCalPointMessenger: public G4UImessenger {

public:
EMCalPointMessenger( EMCalPoint *randGen );
~EMCalPointMessenger();

void SetNewValue( G4UIcommand *command, G4String value );

protected:
EMCalPoint                *fPoint;
G4UIcmdWithADoubleAndUnit *fEnergyCmd;
};


#endif
