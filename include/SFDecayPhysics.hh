#ifndef SFDecayPhysics_h
#define SFDecayPhysics_h 1

#include "G4VPhysicsConstructor.hh"
#include "G4Decay.hh"


class SFDecayPhysics : public G4VPhysicsConstructor
{
public: 
  SFDecayPhysics(const G4String& name = "decay");
  virtual ~SFDecayPhysics();

  // This method will be invoked in the Construct() method.
  // each particle type will be instantiated
  virtual void ConstructParticle();

  // This method will be invoked in the Construct() method.
  // each physics process will be instantiated and
  // registered to the process manager of each particle type 
  virtual void ConstructProcess();

protected:
  G4Decay fDecayProcess;
};


#endif
