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


#ifndef EMCalEmissionEnergy_h
#define EMCalEmissionEnergy_h 1

#include "Randomize.hh"
#include "globals.hh"

#include <cmath>

class EMCalBreitWignerMessenger;
class EMCalExponentialMessenger;
class EMCalFlatMessenger;
class EMCalGammaMessenger;
class EMCalGaussMessenger;
class EMCalLinearMessenger;
class EMCalPointMessenger;


//_______________________________________________________________________________
// Main virtual class
class EMCalEmissionEnergy {

public:

  // Constructor and destructor
  EMCalEmissionEnergy();
  virtual ~EMCalEmissionEnergy();

  // Virtual method
  virtual G4double GetRandom();

protected:

  // Attribute
  G4double fNorm;
};

//_______________________________________________________________________________
// Emission as a Breit-Wigner distribution function
class EMCalBreitWigner: public EMCalEmissionEnergy {

public:

  // Constructor and destructor
  EMCalBreitWigner();
  ~EMCalBreitWigner();

  // Methods
  G4double    GetRandom();
  inline void SetMean( G4double mean );
  inline void SetWidth( G4double width );

protected:

  // Attributes
  G4double                   fMean;
  EMCalBreitWignerMessenger *fMessenger;
  G4double                   fWidth;
};

inline void EMCalBreitWigner::SetMean( G4double mean ) { fMean = mean; }
inline void EMCalBreitWigner::SetWidth( G4double width ) { fWidth = width; }

//_______________________________________________________________________________
// Emission as an exponential function
class EMCalExponential: public EMCalEmissionEnergy {

public:
  
  // Constructor and destructor
  EMCalExponential();
  ~EMCalExponential();

  // Methods
  void        CalculateNorm();
  G4double    GetRandom();
  inline void SetExpPar( G4double par );
  inline void SetMaxEnergy( G4double energy );
  inline void SetMinEnergy( G4double energy );

protected:

  // Attributes
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

//_______________________________________________________________________________
// Emission in a flat range
class EMCalFlat: public EMCalEmissionEnergy {

public:
  
  // Constructor and destructor
  EMCalFlat();
  ~EMCalFlat();

  // Methods
  G4double    GetRandom();
  inline void SetMaxEnergy( G4double energy );
  inline void SetMinEnergy( G4double energy );

protected:

  // Attributes
  G4double            fMaxEnergy;
  EMCalFlatMessenger *fMessenger;
  G4double            fMinEnergy;
};

inline void EMCalFlat::SetMaxEnergy( G4double energy ) { fMaxEnergy = energy; }
inline void EMCalFlat::SetMinEnergy( G4double energy ) { fMinEnergy = energy; }

//_______________________________________________________________________________
// Emission as a gamma function
class EMCalGamma: public EMCalEmissionEnergy {

public:

  // Constructor and destructor
  EMCalGamma();
  ~EMCalGamma();

  // Methods
  G4double    GetRandom();
  inline void SetK( G4double k );
  inline void SetLambda( G4double lambda );

protected:

  // Attributes
  G4double             fK;
  G4double             fLambda;
  EMCalGammaMessenger *fMessenger;
};

inline void EMCalGamma::SetK( G4double k ) { fK = k; }
inline void EMCalGamma::SetLambda( G4double lambda ) { fLambda = lambda; }

//_______________________________________________________________________________
// Emission as a gaussian function
class EMCalGauss: public EMCalEmissionEnergy {

public:

  // Constructor and destructor
  EMCalGauss();
  ~EMCalGauss();

  // Methods
  G4double    GetRandom();
  inline void SetMean( G4double mean );
  inline void SetSigma( G4double sigma );

protected:

  // Attributes
  G4double             fMean;
  EMCalGaussMessenger *fMessenger;
  G4double             fSigma;
};

inline void EMCalGauss::SetMean( G4double mean ) { fMean = mean; }
inline void EMCalGauss::SetSigma( G4double sigma ) { fSigma = sigma; }

//_______________________________________________________________________________
// Emission in a line
class EMCalLinear: public EMCalEmissionEnergy {

public:

  // Constructor and destructor
  EMCalLinear();
  ~EMCalLinear();

  // Methods
  void        CalculateNorm();
  G4double    GetRandom();
  inline void SetMaxEnergy( G4double energy );
  inline void SetMinEnergy( G4double energy );
  inline void SetMaxMinProp( G4double prop );

protected:

  // Attributes
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

//_______________________________________________________________________________
// Emission with a constant value
class EMCalPoint: public EMCalEmissionEnergy {

public:

  // Constructor and destructor
  EMCalPoint();
  ~EMCalPoint();

  // Methods
  inline G4double GetRandom();
  inline void     SetEnergy( G4double energy );

protected:

  // Attributes
  G4double             fEnergy;
  EMCalPointMessenger *fMessenger;
};
  
inline G4double EMCalPoint::GetRandom() { return fEnergy; }
inline void EMCalPoint::SetEnergy( G4double energy ) { fEnergy = energy; }

#endif
