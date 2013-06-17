//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: WaterCherenkovStackingAction.cc,v 1.5 2006/06/29 17:54:34 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "WaterCherenkovStackingAction.hh"
#include "WaterCherenkovEventAction.hh"
#include "G4RunManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterCherenkovStackingAction::WaterCherenkovStackingAction()
  : gammaCounter(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterCherenkovStackingAction::~WaterCherenkovStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
WaterCherenkovStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetCurrentStepNumber() == 0)
    {
      WaterCherenkovEventAction *theEvent =
  	(WaterCherenkovEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
      
      if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) 
	{
	  theEvent -> AddPhoton();
	  if(aTrack->GetParentID()>0)
	    { // particle is secondary
	      gammaCounter++;
	    }
  	}
      
      else if((aTrack->GetDefinition()==G4Electron::ElectronDefinition())   ||
	      (aTrack->GetDefinition()==G4Positron::PositronDefinition())   ||
	      (aTrack->GetDefinition()==G4MuonPlus::MuonPlusDefinition())   ||
	      (aTrack->GetDefinition()==G4MuonMinus::MuonMinusDefinition())   ) 
  	{ 
	  G4ThreeVector PositionVector = aTrack -> GetPosition();
	  G4ThreeVector MomentumVector = aTrack -> GetMomentum();
	  G4int definition = 0;
	  
	  if(aTrack->GetDefinition()==G4Electron::ElectronDefinition())       {definition =  11;}
	  else if(aTrack->GetDefinition()==G4Positron::PositronDefinition())  {definition = -11;}
	  else if(aTrack->GetDefinition()==G4MuonPlus::MuonPlusDefinition())  {definition = -13;}
	  else if(aTrack->GetDefinition()==G4MuonMinus::MuonMinusDefinition()){definition =  13;}
	  
	  theEvent -> AddLepton(PositionVector, MomentumVector, definition);
  	}
      
    }
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovStackingAction::NewStage()
{
  G4cout << "Number of optical photons produced in this event : "
         << gammaCounter << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovStackingAction::PrepareNewEvent()
{ gammaCounter = 0; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
