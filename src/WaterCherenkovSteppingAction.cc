
#include "WaterCherenkovSteppingAction.hh"
#include "WaterCherenkovEventAction.hh"
#include "WaterCherenkovDetectorConstruction.hh"
#include "WaterCherenkovPhysicsList.hh"

///     Geant4 package includes
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

WaterCherenkovSteppingAction::WaterCherenkovSteppingAction()
{
}

WaterCherenkovSteppingAction::~WaterCherenkovSteppingAction()
{
}

//---------------------------------------------------------------------------// 

void WaterCherenkovSteppingAction::UserSteppingAction(const G4Step *theStep)
{
  fDetectorVolume = 
  ((WaterCherenkovDetectorConstruction*)G4RunManager::GetRunManager()
   ->GetUserDetectorConstruction())->GetDetectorLogicalVolume();

  WaterCherenkovEventAction *theEvent =
  (WaterCherenkovEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();

  fPreVolume = theStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume();
  //fPostVolume = theStep->GetPostStepPoint()->GetLogicalVolume();
  
  if(theStep->GetPostStepPoint()->GetPhysicalVolume())
    {
       fPostVolume = theStep->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume();
    }
     
  else 
    {
        fPostVolume = NULL;
    }
    
 
  if(fPostVolume == fDetectorVolume)
    {
    if(fPreVolume !=fDetectorVolume)
      {
      if(theStep->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
	{
	  // then we have just entered the detector plane, so let's record the
	  // useful info (the track has the GetVertexPosition, GetGlobalTime,
	  // Get Position at the plane)

	  G4ThreeVector planePosition = theStep->GetPostStepPoint()->GetPosition();
	  double globalTime = theStep->GetPostStepPoint()->GetGlobalTime();
	  // Get initial position of track
	  G4ThreeVector initialPosition = theStep->GetTrack()->GetVertexPosition();
	  double wavelength = 
	    (197*2*3.14159)/
	    (theStep->GetPostStepPoint()->GetTotalEnergy()/eV);
          // because hbar*c = 197MeV*fm = 197 eV*nm
	  //G4cout << "Particle Identity = " << theStep->GetTrack()->GetDefinition() << G4endl;
	  G4cout << "HIT DETECTED! About to AddHit..." << G4endl;
	  theEvent->AddHit(planePosition, globalTime, initialPosition, wavelength);
	  
	  theStep->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
	}
    }
  }
  
}


