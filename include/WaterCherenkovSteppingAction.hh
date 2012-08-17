#ifndef WaterCherenkovSteppingAction_h
#define WaterCherenkovSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Track.hh"
#include "globals.hh"


class WaterCherenkovSteppingAction:public G4UserSteppingAction{

  public:
    WaterCherenkovSteppingAction();
    ~WaterCherenkovSteppingAction();

    void UserSteppingAction(const G4Step * theStep);
  
 

    const G4Track *theTrack;
  
    G4LogicalVolume *fPreVolume;
    G4LogicalVolume *fPostVolume;
    G4LogicalVolume *fDetectorVolume;
    G4int fParticleID;


};

#endif

