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
// $Id: WaterCherenkovDetectorMessenger.cc,v 1.3 2006/06/29 17:54:29 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "WaterCherenkovDetectorMessenger.hh"

#include "WaterCherenkovDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterCherenkovDetectorMessenger::WaterCherenkovDetectorMessenger(
          WaterCherenkovDetectorConstruction*
          gcdConstruction):WaterCherenkovConstruction(gcdConstruction)
{
  gasDir = new G4UIdirectory("/WaterCherenkov/detector/");
  gasDir->SetGuidance("Position of Plane");
   
  //planeCmd = new G4UIcmdWithADoubleAndUnit("/gasCherenkov/detector/planePosition", this);
  //planeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);  

  //indexCmd = new G4UIcmdWithADouble("/gasCherenkov/detector/index", this);
  //indexCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  reflectivityCmd = new G4UIcmdWithADouble("/WaterCherenkov/detector/reflectivity", this);
  reflectivityCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterCherenkovDetectorMessenger::~WaterCherenkovDetectorMessenger()
{
  //delete planeCmd;
  delete gasDir;
  delete reflectivityCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovDetectorMessenger::SetNewValue(
                                        G4UIcommand* command, G4String newValue)
{ 
  //if( command == planeCmd ) {
  //    G4double planePos = planeCmd->GetNewDoubleValue(newValue);
  //    WaterCherenkovConstruction->SetDetectorZPosition( planePos );
  //    G4cout << "WaterCherenkovDetectorMessenger command: Setting plane z-position" << G4endl;
  //    G4cout << "to " << planePos/cm << " cm" <<  G4endl;
  //}
  //if( command == indexCmd)
  //  {
  //    G4double index = indexCmd->GetNewDoubleValue(newValue);
  //    WaterCherenkovConstruction->SetIndexRef( index );
  //  }

  if( command == reflectivityCmd ) 
    {
      G4double reflectivity = reflectivityCmd->GetNewDoubleValue(newValue);
      WaterCherenkovConstruction->SetfReflectivity( reflectivity );
      G4cout << "WaterCherenkovDetectorMessenger command: Setting reflectivity of" << G4endl;
      G4cout << " aluminum to " << reflectivity << G4endl;
    } else {
    WaterCherenkovConstruction->SetfReflectivity();
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

