#ifndef EMCalActionInitialization_h
#define EMCalActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class EMCalActionInitialization : public G4VUserActionInitialization
{
  public:
    EMCalActionInitialization();
    virtual ~EMCalActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
