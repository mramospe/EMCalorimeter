#ifndef EMCalSteppingAction_h
#define EMCalSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <vector>

class EMCalEventAction;

class G4LogicalVolume;

/// Stepping action class

class EMCalSteppingAction : public G4UserSteppingAction {

public:
  EMCalSteppingAction(EMCalEventAction* eventAction);
  virtual ~EMCalSteppingAction();

  // method from the base class
  virtual void UserSteppingAction(const G4Step*);

private:
  EMCalEventAction              *fEventAction;
  std::vector<G4LogicalVolume*>  fDetectorArray;
  std::vector<G4LogicalVolume*>  fSGVolumeArray;
};

#endif
