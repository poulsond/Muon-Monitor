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

    void SetDetectorZPosition(G4double aVal) { fDetectorPlanePositionZ = aVal; }
    void SetfReflectivity(G4double bVal = 1.0) { fReflectivity = bVal; }
    void SetfReflectivity2(G4double cVal = 0.9) { fReflectivity2 = cVal; }

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
    G4double fReflectivity2;

    WaterCherenkovDetectorMessenger *detectorMessenger;

    G4LogicalVolume *fDetectorLogical;
    G4VPhysicalVolume *fDetectorPhysical;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*WaterCherenkovDetectorConstruction_h*/
