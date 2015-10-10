#ifndef EMCalEmissionEnergy_h
#define EMCalEmissionEnergy_h 1

#include "globals.hh"
#include "Randomize.hh"

#include <cmath>

class EMCalBreitWignerMessenger;
class EMCalExponentialMessenger;
class EMCalFlatMessenger;
class EMCalGammaMessenger;
class EMCalGaussMessenger;
class EMCalLinearMessenger;
class EMCalPointMessenger;

class EMCalEmissionEnergy {

public:
  EMCalEmissionEnergy();
  virtual ~EMCalEmissionEnergy();

  virtual G4double GetRandom();

protected:
  G4double fNorm;
};

// ____________________________________________________

class EMCalBreitWigner: public EMCalEmissionEnergy {

public:
  EMCalBreitWigner();
  ~EMCalBreitWigner();

  G4double    GetRandom();
  inline void SetMean( G4double mean );
  inline void SetWidth( G4double width );

protected:
  G4double                   fMean;
  EMCalBreitWignerMessenger *fMessenger;
  G4double                   fWidth;
};

inline void EMCalBreitWigner::SetMean( G4double mean ) { fMean = mean; }
inline void EMCalBreitWigner::SetWidth( G4double width ) { fWidth = width; }

// ____________________________________________________

class EMCalExponential: public EMCalEmissionEnergy {

public:
  EMCalExponential();
  ~EMCalExponential();

  void        CalculateNorm();
  G4double    GetRandom();
  inline void SetExpPar( G4double par );
  inline void SetMaxEnergy( G4double energy );
  inline void SetMinEnergy( G4double energy );

protected:
  G4double                   fExpPar;
  G4double                   fMaxEnergy;
  EMCalExponentialMessenger *fMessenger;
  G4double                   fMinEnergy;
};

inline void EMCalExponential::SetExpPar( G4double par ) {
  fExpPar = par;
  this -> CalculateNorm();
}
inline void EMCalExponential::SetMaxEnergy( G4double energy ) {
  fMaxEnergy = energy;
  this -> CalculateNorm();
}
inline void EMCalExponential::SetMinEnergy( G4double energy ) {
  fMinEnergy = energy;
  this -> CalculateNorm();
}

// ____________________________________________________

class EMCalFlat: public EMCalEmissionEnergy {

public:
  EMCalFlat();
  ~EMCalFlat();

  G4double    GetRandom();
  inline void SetMaxEnergy( G4double energy );
  inline void SetMinEnergy( G4double energy );

protected:
  G4double            fMaxEnergy;
  EMCalFlatMessenger *fMessenger;
  G4double            fMinEnergy;
};

inline void EMCalFlat::SetMaxEnergy( G4double energy ) { fMaxEnergy = energy; }
inline void EMCalFlat::SetMinEnergy( G4double energy ) { fMinEnergy = energy; }

// ____________________________________________________

class EMCalGamma: public EMCalEmissionEnergy {

public:
  EMCalGamma();
  ~EMCalGamma();

  G4double    GetRandom();
  inline void SetK( G4double k );
  inline void SetLambda( G4double lambda );

protected:
  G4double             fK;
  G4double             fLambda;
  EMCalGammaMessenger *fMessenger;
};

inline void EMCalGamma::SetK( G4double k ) { fK = k; }
inline void EMCalGamma::SetLambda( G4double lambda ) { fLambda = lambda; }

// ____________________________________________________

class EMCalGauss: public EMCalEmissionEnergy {

public:
  EMCalGauss();
  ~EMCalGauss();

  G4double    GetRandom();
  inline void SetMean( G4double mean );
  inline void SetSigma( G4double sigma );

protected:
  G4double             fMean;
  EMCalGaussMessenger *fMessenger;
  G4double             fSigma;
};

inline void EMCalGauss::SetMean( G4double mean ) { fMean = mean; }
inline void EMCalGauss::SetSigma( G4double sigma ) { fSigma = sigma; }

// ____________________________________________________

class EMCalLinear: public EMCalEmissionEnergy {

public:
  EMCalLinear();
  ~EMCalLinear();

  void        CalculateNorm();
  G4double    GetRandom();
  inline void SetMaxEnergy( G4double energy );
  inline void SetMinEnergy( G4double energy );
  inline void SetMaxMinProp( G4double prop );

protected:
  G4double              fMaxEnergy;
  G4double              fMaxMinProp;
  EMCalLinearMessenger *fMessenger;
  G4double              fMinEnergy;
};

inline void EMCalLinear::SetMaxEnergy( G4double energy ) {
  fMaxEnergy = energy;
  this -> CalculateNorm();
}
inline void EMCalLinear::SetMinEnergy( G4double energy ) {
  fMinEnergy = energy;
  this -> CalculateNorm();
}
inline void EMCalLinear::SetMaxMinProp( G4double prop ) {
  fMaxMinProp = prop;
  this -> CalculateNorm();
}

// ____________________________________________________

class EMCalPoint: public EMCalEmissionEnergy {

public:
  EMCalPoint();
  ~EMCalPoint();

  inline G4double GetRandom();
  inline void     SetEnergy( G4double energy );

protected:
  G4double             fEnergy;
  EMCalPointMessenger *fMessenger;
};
  
inline G4double EMCalPoint::GetRandom() { return fEnergy; }
inline void EMCalPoint::SetEnergy( G4double energy ) { fEnergy = energy; }

#endif
