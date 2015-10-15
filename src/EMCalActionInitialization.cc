#include "EMCalActionInitialization.hh"
#include "EMCalPrimaryGeneratorAction.hh"
#include "EMCalRunAction.hh"
#include "EMCalEventAction.hh"
#include "EMCalSteppingAction.hh"

EMCalActionInitialization::EMCalActionInitialization()
 : G4VUserActionInitialization()
{}

EMCalActionInitialization::~EMCalActionInitialization()
{}

void EMCalActionInitialization::BuildForMaster() const
{
  SetUserAction(new EMCalRunAction);
}

void EMCalActionInitialization::Build() const
{

  SetUserAction(new EMCalPrimaryGeneratorAction);
  SetUserAction( new EMCalRunAction );
  
  EMCalEventAction* eventAction = new EMCalEventAction;
  SetUserAction(eventAction);

  SetUserAction(new EMCalSteppingAction(eventAction));
}
