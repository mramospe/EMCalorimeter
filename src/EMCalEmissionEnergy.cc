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
//  Defines the class to simulate the energy shape of the incident particles. This  //
//  class is owned by the EMCalPrimaryGeneratorAction. All the shapes inherit from  //
//  EMCalEmissionEnergy virtual class. Everyone has a different messenger to        //
//  modify the shape parameters. This messenger is destructed with the class, so    //
//  makes the UI to change.                                                         //
//                                                                                  //
// -------------------------------------------------------------------------------- //
//////////////////////////////////////////////////////////////////////////////////////


#include "EMCalEmissionEnergy.hh"
#include "EMCalEmissionEnergyMessenger.hh"

#include "G4PhysicalConstants.hh"


//_______________________________________________________________________________

// --- METHODS FOR EMCalEmissionEnergy CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalEmissionEnergy::EMCalEmissionEnergy() { }

//_______________________________________________________________________________
// Destructor
EMCalEmissionEnergy::~EMCalEmissionEnergy() { }

//_______________________________________________________________________________
// As a virtual class returns zero
G4double EMCalEmissionEnergy::GetRandom() { return 0; }

//_______________________________________________________________________________

// --- METHODS FOR EMCalBreitWigner CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalBreitWigner::EMCalBreitWigner() : EMCalEmissionEnergy() {

  fMessenger = new EMCalBreitWignerMessenger( this );
}

//_______________________________________________________________________________
// Destructor
EMCalBreitWigner::~EMCalBreitWigner() { delete fMessenger; }

//_______________________________________________________________________________
// Returns a random number following a Breit-Wigner distribution
G4double EMCalBreitWigner::GetRandom() {

  return CLHEP::RandBreitWigner::shoot( fMean, fWidth );
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalExponential CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalExponential::EMCalExponential() : EMCalEmissionEnergy() {

  fMessenger = new EMCalExponentialMessenger( this );
}

//_______________________________________________________________________________
// Destructor
EMCalExponential::~EMCalExponential() { delete fMessenger; }

//_______________________________________________________________________________
// Calculates the normalization number for the generator
void EMCalExponential::CalculateNorm() {

  fNorm = fExpPar/( std::exp( fExpPar*fMaxEnergy ) -
		    std::exp( fExpPar*fMinEnergy ) );
}

//_______________________________________________________________________________
// Returns the random number
G4double EMCalExponential::GetRandom() {

  G4double log_arg = std::exp( fExpPar*fMinEnergy ) + fExpPar*G4UniformRand()/fNorm;

    return log_arg/fExpPar;
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalFlat CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalFlat::EMCalFlat() : EMCalEmissionEnergy() {

  fMessenger = new EMCalFlatMessenger( this );
}

//_______________________________________________________________________________
// Destructor
EMCalFlat::~EMCalFlat() { delete fMessenger; }

G4double EMCalFlat::GetRandom() {

  return CLHEP::RandFlat::shoot( fMinEnergy, fMaxEnergy );
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalGamma CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalGamma::EMCalGamma() : EMCalEmissionEnergy() {

  fMessenger = new EMCalGammaMessenger( this );
}

//_______________________________________________________________________________
// Destructor
EMCalGamma::~EMCalGamma() { delete fMessenger; }

//_______________________________________________________________________________
// Returns the random number
G4double EMCalGamma::GetRandom() {

  return CLHEP::RandGamma::shoot( fK, fLambda );
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalGauss CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalGauss::EMCalGauss() : EMCalEmissionEnergy() {

  fMessenger = new EMCalGaussMessenger( this );
}

//_______________________________________________________________________________
// Destructor
EMCalGauss::~EMCalGauss() { delete fMessenger; }

//_______________________________________________________________________________
// Returns the random number
G4double EMCalGauss::GetRandom() {

  return CLHEP::RandGauss::shoot( fMean, fSigma );
}

//_______________________________________________________________________________

// --- METHODS FOR EMCalLinear CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalLinear::EMCalLinear() : EMCalEmissionEnergy() {

  fMessenger = new EMCalLinearMessenger( this );
}

//_______________________________________________________________________________
// Destructor
EMCalLinear::~EMCalLinear() { delete fMessenger; }

//_______________________________________________________________________________
// Calculates the normalization number for the generator
void EMCalLinear::CalculateNorm() {

  G4double x0 = ( fMaxMinProp*fMinEnergy - fMaxEnergy )/( fMaxMinProp - 1. );

  fNorm = 1./( x0*( fMinEnergy - fMaxEnergy ) +
	       ( fMaxEnergy*fMaxEnergy - fMinEnergy*fMinEnergy )/2. );
}

//_______________________________________________________________________________
// Returns the random number
G4double EMCalLinear::GetRandom() {

  G4double
    x0    = ( fMaxMinProp*fMinEnergy - fMaxEnergy )/( fMaxMinProp - 1. ),
    alpha = x0*fMinEnergy - fMinEnergy*fMinEnergy/2. - G4UniformRand()/fNorm;
    
    return x0 - std::sqrt( x0*x0 - 2.*alpha );

}

//_______________________________________________________________________________

// --- METHODS FOR EMCalPoint CLASS ---

//_______________________________________________________________________________
// Constructor
EMCalPoint::EMCalPoint() : EMCalEmissionEnergy() {

  fMessenger = new EMCalPointMessenger( this );
}

//_______________________________________________________________________________
// Destructor
EMCalPoint::~EMCalPoint() { delete fMessenger; }
