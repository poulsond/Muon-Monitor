//
////////////////////////////////////////////////////////////////
//                                                            //
//  Title:  Simple and Fast Physics List                      //
//  Date:   20 March 2005                                     //
//  Author: D.H. Wright (SLAC)                                //
//                                                            //
////////////////////////////////////////////////////////////////
//

#ifndef SFPhysicsList_h
#define SFPhysicsList_h 1

#include "G4VModularPhysicsList.hh"


class SFPhysicsList: public G4VModularPhysicsList
{
public:
  SFPhysicsList();
  virtual ~SFPhysicsList();
  
  virtual void SetCuts();
};

#endif
