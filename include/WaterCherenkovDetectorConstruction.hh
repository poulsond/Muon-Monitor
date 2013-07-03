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
// $Id: WaterCherenkovDetectorConstruction.hh,v 1.5 2006/06/29 17:53:55 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef WaterCherenkovDetectorConstruction_h
#define WaterCherenkovDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class WaterCherenkovDetectorMessenger;

class WaterCherenkovDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  WaterCherenkovDetectorConstruction();
  ~WaterCherenkovDetectorConstruction();
  
  G4VPhysicalVolume* Construct();
  
  G4LogicalVolume* GetDetectorLogicalVolume() { return fDetectorLogical; }
  G4VPhysicalVolume* GetDetectorPhysicalVolume() { return fDetectorPhysical; }
  G4LogicalVolume* GetScintillatorLogicalVolume() { return Scintillator_log; }
  G4VPhysicalVolume* GetScintillatorPhysicalVolume() { return Scintillator_phys; }
  G4LogicalVolume* GetWaterLogicalVolume() { return WaterCan_log; }
  G4VPhysicalVolume* GetWaterPhysicalVolume() { return WaterCan_phys; }
  G4LogicalVolume* GetCarbonDiskLogicalVolume() { return CarbonDisk_log; }
  G4VPhysicalVolume* GetCarbonDiskPhysicalVolume() { return CarbonDisk_phys; }
   
  void SetDetectorZPosition(G4double aVal) { fDetectorPlanePositionZ = aVal; }
  void SetfReflectivity(G4double bVal = 0.9) { fReflectivity = bVal; }
  void SetfAbsConstant(G4double cVal = 1) { fAbsConstant = cVal; }
  G4double GetReflectivity() {
    return fReflectivity;
  }
  G4double GetAbsConstant() {
    return fAbsConstant;
  }

  private:
    G4double fExpHallX;
    G4double fExpHallY;
    G4double fExpHallZ;

    G4double fTankX;
    G4double fTankY;
    G4double fTankZ;

    G4double fMirrorX;
    G4double fMirrorY;
    G4double fMirrorZ;

    G4double fDetectorPlaneX;
    G4double fDetectorPlaneY;
    G4double fDetectorPlaneZ;

    G4double fDetectorPlanePositionZ;

    G4double fReflectivity;
    G4double fAbsConstant;

    WaterCherenkovDetectorMessenger *detectorMessenger;

    G4LogicalVolume *fDetectorLogical;
    G4VPhysicalVolume *fDetectorPhysical;
    G4LogicalVolume *Scintillator_log;
    G4VPhysicalVolume *Scintillator_phys;
    G4LogicalVolume *WaterCan_log;
    G4VPhysicalVolume *WaterCan_phys;
    G4LogicalVolume *CarbonDisk_log;
    G4VPhysicalVolume *CarbonDisk_phys;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*WaterCherenkovDetectorConstruction_h*/
