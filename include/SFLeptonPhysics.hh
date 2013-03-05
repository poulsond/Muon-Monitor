//
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  Title:  Lepton Physics for Simple and Fast Physics List                //
//  Date:   22 March 2005                                                  //
//  Author: D.H. Wright (SLAC)                                             //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//

#ifndef SFLeptonPhysics_h
#define SFLeptonPhysics_h 1

#include "G4VPhysicsConstructor.hh"


class SFLeptonPhysics : public G4VPhysicsConstructor
{
public: 
  SFLeptonPhysics(const G4String& name ="lepton");
  virtual ~SFLeptonPhysics();

  // This method will be invoked in the Construct() method. 
  // each particle type will be instantiated
  virtual void ConstructParticle();
 
  // This method will be invoked in the Construct() method.
  // each physics process will be instantiated and
  // registered to the process manager of each particle type 
  virtual void ConstructProcess();

};

#endif
