#include "EMCalEmissionEnergy.hh"
#include "EMCalEmissionEnergyMessenger.hh"

#include "G4PhysicalConstants.hh"

EMCalEmissionEnergy::EMCalEmissionEnergy() { }

EMCalEmissionEnergy::~EMCalEmissionEnergy() { }

G4double EMCalEmissionEnergy::GetRandom() { return 0; }

// ____________________________________________________

EMCalBreitWigner::EMCalBreitWigner() : EMCalEmissionEnergy() {

  fMessenger = new EMCalBreitWignerMessenger( this );
}

EMCalBreitWigner::~EMCalBreitWigner() { delete fMessenger; }

G4double EMCalBreitWigner::GetRandom() {

  return CLHEP::RandBreitWigner::shoot( fMean, fWidth );
}

// ____________________________________________________

EMCalExponential::EMCalExponential() : EMCalEmissionEnergy() {

  fMessenger = new EMCalExponentialMessenger( this );
}

EMCalExponential::~EMCalExponential() { delete fMessenger; }

void EMCalExponential::CalculateNorm() {

  fNorm = fExpPar/( std::exp( fExpPar*fMaxEnergy ) -
		    std::exp( fExpPar*fMinEnergy ) );
}

G4double EMCalExponential::GetRandom() {

  G4double log_arg = std::exp( fExpPar*fMinEnergy ) + fExpPar*G4UniformRand()/fNorm;

    return log_arg/fExpPar;
}

// ____________________________________________________

EMCalFlat::EMCalFlat() : EMCalEmissionEnergy() {

  fMessenger = new EMCalFlatMessenger( this );
}

EMCalFlat::~EMCalFlat() { delete fMessenger; }

G4double EMCalFlat::GetRandom() {

  return CLHEP::RandFlat::shoot( fMinEnergy, fMaxEnergy );
}

// ____________________________________________________

EMCalGamma::EMCalGamma() : EMCalEmissionEnergy() {

  fMessenger = new EMCalGammaMessenger( this );
}

EMCalGamma::~EMCalGamma() { delete fMessenger; }

G4double EMCalGamma::GetRandom() {

  return CLHEP::RandGamma::shoot( fK, fLambda );
}

// ____________________________________________________

EMCalGauss::EMCalGauss() : EMCalEmissionEnergy() {

  fMessenger = new EMCalGaussMessenger( this );
}

EMCalGauss::~EMCalGauss() { delete fMessenger; }

G4double EMCalGauss::GetRandom() {

  return CLHEP::RandGauss::shoot( fMean, fSigma );
}

// ____________________________________________________

EMCalLinear::EMCalLinear() : EMCalEmissionEnergy() {

  fMessenger = new EMCalLinearMessenger( this );
}

EMCalLinear::~EMCalLinear() { delete fMessenger; }

void EMCalLinear::CalculateNorm() {

  G4double x0 = ( fMaxMinProp*fMinEnergy - fMaxEnergy )/( fMaxMinProp - 1. );

  fNorm = 1./( x0*( fMinEnergy - fMaxEnergy ) +
	       ( fMaxEnergy*fMaxEnergy - fMinEnergy*fMinEnergy )/2. );
}

G4double EMCalLinear::GetRandom() {

  G4double
    x0    = ( fMaxMinProp*fMinEnergy - fMaxEnergy )/( fMaxMinProp - 1. ),
    alpha = x0*fMinEnergy - fMinEnergy*fMinEnergy/2. - G4UniformRand()/fNorm;
    
    return x0 - std::sqrt( x0*x0 - 2.*alpha );

}

// ____________________________________________________

EMCalPoint::EMCalPoint() : EMCalEmissionEnergy() {

  fMessenger = new EMCalPointMessenger( this );
}

EMCalPoint::~EMCalPoint() { delete fMessenger; }
