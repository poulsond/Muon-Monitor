//
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  Title:  Neutron Physics for Simple and Fast Physics List               //
//  Date:   20 March 2005                                                  //
//  Author: D.H. Wright (SLAC)                                             //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//

#ifndef SFNeutronPhysics_h
#define SFNeutronPhysics_h 1

#include "G4VPhysicsConstructor.hh"

class SFNeutronPhysics : public G4VPhysicsConstructor
{
public: 
  SFNeutronPhysics(const G4String& name ="neutron");
  virtual ~SFNeutronPhysics();

  // This method will be invoked in the Construct() method. 
  // each particle type will be instantiated
  virtual void ConstructParticle();
 
  // This method will be invoked in the Construct() method.
  // each physics process will be instantiated and
  // registered to the process manager of each particle type 
  virtual void ConstructProcess();

};

#endif
