
#include "WaterCherenkovSteppingAction.hh"
#include "WaterCherenkovEventAction.hh"
#include "WaterCherenkovDetectorConstruction.hh"

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
  
  fScintillatorVolume = 
    ((WaterCherenkovDetectorConstruction*)G4RunManager::GetRunManager()
     ->GetUserDetectorConstruction())->GetScintillatorLogicalVolume();
  
  fWaterVolume =
    ((WaterCherenkovDetectorConstruction*)G4RunManager::GetRunManager()
     ->GetUserDetectorConstruction())->GetWaterLogicalVolume();

  fCarbonDiskVolume =
    ((WaterCherenkovDetectorConstruction*)G4RunManager::GetRunManager()
     ->GetUserDetectorConstruction())->GetCarbonDiskLogicalVolume();

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
  
  //Record the event type when the primary particle changes
  if(theStep->GetPostStepPoint()->GetProcessDefinedStep() != 0){
    //this returns a G4String
    G4String processname = theStep->GetPostStepPoint()->
      GetProcessDefinedStep()->GetProcessName();
    
      //There's also ->GetProcessType() at the end of that which returns
      // type G4ProcessType, which is an enum defined thusly:
      // 0: undefined          4: Hadronic
      // 1: transportation     5: Photolepton_hadron
      // 2: electromagnetic    6: Decay
      // 3: optical            7: General
      //
      // G4ProcessType, as an enum, can be cast as an int:
    G4int processtype = (G4int)theStep->GetPostStepPoint()->
      GetProcessDefinedStep()->GetProcessType();
    
    //If it's particle transport or "undefined" we don't care, so         
    if(processtype>1){
      double interactionTime = theStep->GetPostStepPoint()->GetGlobalTime();
      G4int PDG = theStep->GetTrack()->GetDefinition()->GetPDGEncoding();
      G4int interaction  = processtype;
      G4ThreeVector eventPos = theStep->GetPostStepPoint()->GetPosition();
      theEvent->AddProcess(interaction, eventPos, PDG, interactionTime);
    }
  }

  //record the photon when it enters the detector volume
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
	      //  G4cout << "HIT DETECTED! About to AddHit..." << G4endl;
	      theEvent->AddHit(planePosition, globalTime, initialPosition, wavelength);
	      theStep->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
	    }
	}
    }

  // Attempt to make a veto
  /*  if(fPostVolume == fScintillatorVolume && fPostVolume != fWaterVolume)
    {
      if(theStep->GetTrack()->GetDefinition() == G4Electron::ElectronDefinition() || theStep->GetTrack()->GetDefinition() == G4Positron::PositronDefinition()){
	if(theStep->GetTrack()->GetVelocity()/(m/s) > 224844343)
	  {
	    int veto = 1;
	    theEvent->AddVeto(veto);
	  } 
      } 
      }*/
}
