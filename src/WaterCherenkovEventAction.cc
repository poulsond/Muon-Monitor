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
//
// $Id: WaterCherenkovEventAction.cc,v 1.3 2006/06/29 17:54:20 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#include "WaterCherenkovEventAction.hh"
#include "WaterCherenkovRunAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
WaterCherenkovEventAction::WaterCherenkovEventAction(WaterCherenkovRunAction *theRA): theRun(theRA)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
WaterCherenkovEventAction::~WaterCherenkovEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void WaterCherenkovEventAction::BeginOfEventAction(const G4Event* anEvent)
{
  fNHits = 0;
  fNPhotons = 0;
  indexnum = 0;
  ResetArrays();
  fPrimePosX = anEvent->GetPrimaryVertex()->GetX0()/cm;
  fPrimePosY = anEvent->GetPrimaryVertex()->GetY0()/cm;
  fPrimePosZ = anEvent->GetPrimaryVertex()->GetZ0()/cm;
  fPrimeMomX = anEvent->GetPrimaryVertex()->GetPrimary()->GetPx();
  fPrimeMomY = anEvent->GetPrimaryVertex()->GetPrimary()->GetPy();
  fPrimeMomZ = anEvent->GetPrimaryVertex()->GetPrimary()->GetPz();

  //The following six lines may not be neccessary 
  //lPrimePosX[indexnum] = anEvent->GetPrimaryVertex()->GetX0()/cm;
  //lPrimePosY[indexnum] = anEvent->GetPrimaryVertex()->GetY0()/cm;
  //lPrimePosZ[indexnum] = anEvent->GetPrimaryVertex()->GetZ0()/cm;
  //lPrimeMomX[indexnum] = anEvent->GetPrimaryVertex()->GetPrimary()->GetPx();
  //lPrimeMomY[indexnum] = anEvent->GetPrimaryVertex()->GetPrimary()->GetPy();
  //lPrimeMomZ[indexnum] = anEvent->GetPrimaryVertex()->GetPrimary()->GetPz();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovEventAction::ResetArrays()
{
  for(G4int i = 0; i<kPMax; i++)
  {
    fPlaneX[i] = 0;
    fPlaneY[i] = 0;
    fPlaneZ[i] = 0;
    fPlaneT[i] = 0;
    fTrackX[i] = 0;
    fTrackY[i] = 0;
    fTrackZ[i] = 0;
    fWavelength[i] = 0;
    lDefinition[i] = 0;
    lPrimePosX[i] = 0;
    lPrimePosY[i] = 0;
    lPrimePosZ[i] = 0;
    lPrimeMomX[i] = 0;
    lPrimeMomY[i] = 0;
    lPrimeMomZ[i] = 0;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void WaterCherenkovEventAction::EndOfEventAction(const G4Event*)
{
  if(fNHits >= 0)
    {
    	theRun->GetTree()->Fill();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
