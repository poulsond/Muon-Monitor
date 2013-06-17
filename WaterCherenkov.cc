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
// $Id: exampleN06.cc,v 1.15 2008/05/07 10:08:31 allison Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Description: Test of Continuous Process G4Cerenkov
//              and RestDiscrete Process G4Scintillation
//              -- Generation Cerenkov Photons --
//              -- Generation Scintillation Photons --
//              -- Transport of optical Photons --
// Version:     5.0
// Created:     1996-04-30
// Author:      Juliet Armstrong
// mail:        gum@triumf.ca
//     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "G4ios.hh"

#include "WaterCherenkovDetectorConstruction.hh"
#include "ExN06PhysicsList.hh"
#include "SFPhysicsList.hh"
#include "WaterCherenkovPrimaryGeneratorAction.hh"
#include "WaterCherenkovRunAction.hh"
#include "WaterCherenkovEventAction.hh"
#include "WaterCherenkovSteppingAction.hh"
#include "WaterCherenkovStackingAction.hh"
#include "WaterCherenkovSteppingVerbose.hh"

#include "TROOT.h"
#include "time.h"
#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // choose the Random engine
  //
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());

  // Set random seed with system time
  //
  //G4long myseed = 345354;
  //CLHEP::HepRandom::setTheSeed(myseed);
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  
  // User Verbose output class
  //
  G4VSteppingVerbose* verbosity = new WaterCherenkovSteppingVerbose;
  //G4VSteppingVerbose::SetInstance(verbosity);
  
  // Run manager
  //
  G4RunManager* runManager = new G4RunManager;

  // UserInitialization classes - mandatory
  //
  G4VUserDetectorConstruction* detector = new WaterCherenkovDetectorConstruction;
  runManager-> SetUserInitialization(detector);
  //
  G4VUserPhysicsList* physics = new SFPhysicsList;//ExN06PhysicsList; //WaterCherenkovPhysicsList;
  runManager-> SetUserInitialization(physics);
  
#ifdef G4VIS_USE
  // visualization manager
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  // UserAction classes
  //
  WaterCherenkovRunAction * run_action = new WaterCherenkovRunAction;
  runManager->SetUserAction(run_action);
  //
  G4VUserPrimaryGeneratorAction* gen_action = new WaterCherenkovPrimaryGeneratorAction;
  runManager->SetUserAction(gen_action);
  //
  WaterCherenkovEventAction* event_action = new WaterCherenkovEventAction(run_action);
  runManager->SetUserAction(event_action);
  //
  G4UserStackingAction* stacking_action = new WaterCherenkovStackingAction;
  runManager->SetUserAction(stacking_action);
  //
  runManager->SetUserAction(new WaterCherenkovSteppingAction());


  // Initialize G4 kernel
  //
    
  // Get the pointer to the User Interface manager
  //
  G4UImanager* UI = G4UImanager::GetUIpointer(); 
   
  if (argc==1)   // Define UI session for interactive mode
    {
      G4UIsession* session = 0;
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif    
#ifdef G4VIS_USE
      UI->ApplyCommand("/control/execute vis.mac");     
#endif
      session->SessionStart();
      delete session;
   }
   
  else         // Batch mode
   {
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
   }
   
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;
  delete verbosity;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
