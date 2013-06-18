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
// $Id: WaterCherenkovRunAction.cc,v 1.10 2006/06/29 17:54:31 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Make this appear first!
#include "G4Timer.hh"

#include "WaterCherenkovRunAction.hh"
#include "WaterCherenkovRunMessenger.hh"
#include "WaterCherenkovEventAction.hh"
#include "WaterCherenkovDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterCherenkovRunAction::WaterCherenkovRunAction()
{
  //create a messenger for this class
  runMessenger = new WaterCherenkovRunMessenger(this);
  
  G4cout << "The Name of the file is actually " << fFileName << G4endl;

  timer = new G4Timer;
  fFile = new TFile();
  fTree = new TTree();
  mTree = new TTree();
  
  // create a messenger for the reflectivity here?
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterCherenkovRunAction::~WaterCherenkovRunAction()
{
  delete timer;
  delete runMessenger;
  //don't delete the tree! closing the file does that. I know it's stupid.
  //delete fTree;
  delete fFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovRunAction::BeginOfRunAction(const G4Run* aRun)
{
  TFile *tempFile = new TFile(fFileName.c_str(), "RECREATE");
  fFile = tempFile;
  InitializeTree();
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
  timer->Start();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovRunAction::EndOfRunAction(const G4Run* aRun)
{
  G4cout << "ending run" << G4endl;
  timer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent() 
         << " " << *timer << G4endl;
  G4cout << "Writing file" << G4endl;
  fFile->Write();
  G4cout << "Closing File" << G4endl;
  fFile->Close();
  G4cout << "hplanck  " << h_Planck << G4endl;
  G4cout << "c light  " << c_light << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//---------------------------------------------------------------------------// 
void WaterCherenkovRunAction::InitializeTree()
{
  
  WaterCherenkovEventAction *theEvent =
  (WaterCherenkovEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();

  TTree *tempTree = new TTree("fTree", "");
  tempTree->Branch("interactionNum",theEvent->GetinteractionNum(),   "interactionNum/I");
  tempTree->Branch("fNHits",        theEvent->GetNHits(),            "fNHits/I");
  tempTree->Branch("leptonNum",     theEvent->GetleptonNum(),        "leptonNum/I");
  tempTree->Branch("fNPhotons",     theEvent->GetPhotonHits(),       "fNPhotons/I");
  tempTree->Branch("fPlaneX_cm",    theEvent->GetPlaneX(),           "fPlaneX_cm[fNHits]/D");
  tempTree->Branch("fPlaneY_cm",    theEvent->GetPlaneY(),           "fPlaneY_cm[fNHits]/D");
  tempTree->Branch("fPlaneZ_cm",    theEvent->GetPlaneZ(),           "fPlaneZ_cm[fNHits]/D");
  tempTree->Branch("fPlaneT_ns",    theEvent->GetPlaneT(),           "fPlaneT_ns[fNHits]/D");
  tempTree->Branch("fTrackX_cm",    theEvent->GetTrackX(),           "fTrackX_cm[fNHits]/D");
  tempTree->Branch("fTrackY_cm",    theEvent->GetTrackY(),           "fTrackY_cm[fNHits]/D");
  tempTree->Branch("fTrackZ_cm",    theEvent->GetTrackZ(),           "fTrackZ_cm[fNHits]/D");
  tempTree->Branch("fPrimePosX_cm", theEvent->GetPrimaryPositionX(), "fPrimePosX_cm/D");
  tempTree->Branch("fPrimePosY_cm", theEvent->GetPrimaryPositionY(), "fPrimePosY_cm/D");
  tempTree->Branch("fPrimePosZ_cm", theEvent->GetPrimaryPositionZ(), "fPrimePosZ_cm/D");
  tempTree->Branch("fPrimeMomX",    theEvent->GetPrimaryMomentumX(), "fPrimeMomX/D");
  tempTree->Branch("fPrimeMomY",    theEvent->GetPrimaryMomentumY(), "fPrimeMomY/D");
  tempTree->Branch("fPrimeMomZ",    theEvent->GetPrimaryMomentumZ(), "fPrimeMomZ/D");
  tempTree->Branch("fWavelength_nm",theEvent->GetWavelength(),       "fWavelength_nm[fNHits]/D");
  tempTree->Branch("lPrimePosX_cm", theEvent->GetlPrimaryPositionX(),"lPrimePosX_cm[leptonNum]/D");
  tempTree->Branch("lPrimePosY_cm", theEvent->GetlPrimaryPositionY(),"lPrimePosY_cm[leptonNum]/D");
  tempTree->Branch("lPrimePosZ_cm", theEvent->GetlPrimaryPositionZ(),"lPrimePosZ_cm[leptonNum]/D"); 
  tempTree->Branch("lPrimeMomX",    theEvent->GetlPrimaryMomentumX(),"lPrimeMomX[leptonNum]/D");
  tempTree->Branch("lPrimeMomY",    theEvent->GetlPrimaryMomentumY(),"lPrimeMomY[leptonNum]/D");
  tempTree->Branch("lPrimeMomZ",    theEvent->GetlPrimaryMomentumZ(),"lPrimeMomZ[leptonNum]/D");
  tempTree->Branch("lDefinition",   theEvent->GetlDefinition(),      "lDefinition[leptonNum]/I");
  tempTree->Branch("lProcessType",  theEvent->GetlProcessType(),     "lProcessType[interactionNum]/I");
  tempTree->Branch("GPrimePosX_cm", theEvent->GetGPrimaryPositionX(),"GPrimePosX_cm[interactionNum]/D");
  tempTree->Branch("GPrimePosY_cm", theEvent->GetGPrimaryPositionY(),"GPrimePosY_cm[interactionNum]/D");
  tempTree->Branch("GPrimePosZ_cm", theEvent->GetGPrimaryPositionZ(),"GPrimePosZ_cm[interactionNum]/D"); 
  tempTree->Branch("pDefinition",   theEvent->GetpDefinition(),      "pDefinition[interactionNum]/I");
  tempTree->Branch("linteractionTime_ns",    theEvent->GetinteractionTime(), "linteractionTime_ns[interactionNum]/D"); 
  tempTree->Branch("vetoNum",       theEvent->GetVetoNum(),          "vetoNum/I"); 
  tempTree->Branch("OhNoVeto",      theEvent->GetOhNoVeto(),         "OhNoVeto[vetoNum]/I"); 

  fTree = tempTree;

  TTree *memoTree = new TTree("memoTree", "");
  // absConstant
  G4double AbsConstant = 0;
  memoTree->Branch("AbsConstant", &AbsConstant, "AbsConstant/D");

  // reflectivity  
  G4double Reflectivity = 0;
  memoTree->Branch("Reflectivity", &Reflectivity,  "Reflectivity/D");

  // mTree
  mTree = memoTree;

  WaterCherenkovDetectorConstruction *Detector =
    (WaterCherenkovDetectorConstruction*)G4RunManager::GetRunManager()->GetUserDetectorConstruction();
  
  //  WaterCherenkovPrimaryGeneratorAction *Generator = 
  //    (WaterCherenkovPrimaryGeneratorAction*)G4RunManager::GetRunManager()->GetUsergeneratorAction();

  Reflectivity = Detector->GetReflectivity();
  AbsConstant = Detector->GetAbsConstant();
  mTree->Fill();
}
