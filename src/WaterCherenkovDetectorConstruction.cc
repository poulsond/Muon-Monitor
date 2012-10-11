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
// $Id: WaterCherenkovDetectorConstruction.cc,v 1.17 2008/07/17 00:32:34 gum Exp $
// GEANT4 tag $Name: geant4-09-02 $

#include "WaterCherenkovDetectorConstruction.hh"
#include "WaterCherenkovDetectorMessenger.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4VisAttributes.hh"
#include "G4OpticalSurface.hh"

//     ---------- Define Functions ----------     //

WaterCherenkovDetectorConstruction::WaterCherenkovDetectorConstruction()
{
  fExpHallX = fExpHallY = fExpHallZ = 5*m;
  fTankX    = fTankY    = fTankZ    = 3*m;

  //probably not needed
  fMirrorX  = 7.62*cm;
  fMirrorY = 10.776*cm;
  fMirrorZ  = 0.5*cm;
  //
  fDetectorPlaneX = 18*cm;
  fDetectorPlaneY = 1*cm;
  fDetectorPlaneZ = 18*cm;
  fDetectorPlanePositionZ = 2*m;
  //
  detectorMessenger = new WaterCherenkovDetectorMessenger(this);

}

WaterCherenkovDetectorConstruction::~WaterCherenkovDetectorConstruction()
{
  delete detectorMessenger;
}

G4VPhysicalVolume* WaterCherenkovDetectorConstruction::Construct()
{

//	------------- Materials -------------     //

  G4double a, z, density;
  G4int nelements;

// Air
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

  G4Material* Air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  Air->AddElement(N, 70.*perCent);
  Air->AddElement(O, 30.*perCent);

// Water
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);

  G4Material* Water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
  Water->AddElement(H, 2);
  Water->AddElement(O, 1);

// Freon
  G4Element* C = new G4Element("Carbon", "C", z=6 , a=12.0*g/mole);

  G4Material* Freon = new G4Material("Freon", density = 176.4*mg/cm3, nelements=2);
  Freon->AddElement(H, 4);
  Freon->AddElement(C, 8);

// Aluminum
  G4Material* Aluminum = new G4Material("Aluminum",z=13, a=26.9815*g/mole, 
                                        density=2.699*g/cm3);

// Carbon
  G4Material* Carbon = new G4Material("Carbon", z=6, a=12.011*g/mole, 
				      density=2.267*g/cm3);

// Silicon
  G4Material* Silicon = new G4Material("Silicon", z=14, a=28.08*g/mole, 
				      density=2.7*g/cm3);
// Glass
  G4Material* Glass = new G4Material("Glass", z=14, a=28.08*g/mole, 
				      density=2.7*g/cm3);

// Vacuum
  G4Material* Vacuum = new G4Material("Vacuum", z=1, a=1*g/mole, 
				      density=0.0*g/cm3);

// ------------ Generate & Add Material Properties Table ------------ //

  const G4int nEntries = 3;
  G4double PhotonEnergy[nEntries] = {2.0*eV, 3.0*eV, 4.0*eV};
  //  G4double PhotonEnergy[nEntries] = {2.034*eV, 2.532*eV, 3.026*eV, 3.545*eV, 4.002*eV};


  // TODO: add list of 32 energies
  // Water
  const G4int numEntries = 32;
  //  G4double RefractiveIndex1[numEntries] =
  //    {1.3435, 1.3500, 1.3545, 1.358, 1.3600};

    G4double RefractiveIndex1[numEntries] =
              { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
                1.346,  1.3465, 1.347,  1.3475, 1.348,
                1.3485, 1.3492, 1.35,   1.3505, 1.351,
                1.3518, 1.3522, 1.3530, 1.3535, 1.354,
                1.3545, 1.355,  1.3555, 1.356,  1.3568,
                1.3572, 1.358,  1.3585, 1.359,  1.3595,
                1.36,   1.3608};

   // G4double Absorption1[numEntries] =   {3.448, 45.455, 45.455, 27.000, 17.500};

      G4double Absorption1[numEntries] =
               {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
               15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
               45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
               52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
               30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
               17.500*m, 14.500*m };

      G4double ScintilFast[numEntries] =
                { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
                  1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
                  1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
                  1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
                  1.00, 1.00, 1.00, 1.00 };
   
      G4double ScintilSlow[numEntries] =
                { 0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,
                  7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,
                  3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,
                  4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
                  7.00, 6.00, 5.00, 4.00 };

  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
  myMPT1->AddProperty("RINDEX",PhotonEnergy,RefractiveIndex1,nEntries);
  myMPT1->AddProperty("ABSLENGTH",PhotonEnergy,Absorption1,nEntries);
  myMPT1->AddProperty("FASTCOMPONENT",PhotonEnergy,ScintilFast,nEntries);
  myMPT1->AddProperty("SLOWCOMPONENT",PhotonEnergy,ScintilSlow,nEntries);
  
  myMPT1->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  myMPT1->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  myMPT1->AddConstProperty("YIELDRATIO",0.8);
  
  Water->SetMaterialPropertiesTable(myMPT1);
  
  // Set the Birks Constant for the Water scintillator

  Water->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

  // Glass
  G4double Glass_RIND[nEntries]={1.49,1.49,1.49};
  G4double Glass_AbsLength[nEntries]={420.*cm,420.*cm,420.*cm};
  G4MaterialPropertiesTable *Glass_mt = new G4MaterialPropertiesTable();
  Glass_mt->AddProperty("ABSLENGTH",PhotonEnergy,Glass_AbsLength,nEntries);
  Glass_mt->AddProperty("RINDEX",PhotonEnergy,Glass_RIND,nEntries);
  Glass->SetMaterialPropertiesTable(Glass_mt);

  // Aluminum 
  /*
  G4MaterialPropertiesTable* propTableAluminizedMylar = new G4MaterialPropertiesTable();
  const G4int numEntriesAl = 3;
  G4double energiesAl[numEntriesAl] = {2.4*eV,2.8*eV,3.4*eV};
  G4double refractiveIndexAl[numEntriesAl] = {0.87,0.61,0.40};
  G4double absorptionIndexAl[numEntriesAl] = {1.0/0.024*nm,1.0/0.028*nm,1.0/0.034*nm};
  propTableAluminizedMylar->AddProperty("RINDEX",energiesAl,
                                        refractiveIndexAl,numEntriesAl);	
  propTableAluminizedMylar->AddProperty("ABSLENGTH",energiesAl,
                                        absorptionIndexAl,numEntriesAl);
  Aluminum->SetMaterialPropertiesTable(propTableAluminizedMylar);
  */
  

//	------------- Volumes --------------     //

// The experimental Hall
  G4Box* fExpHall_box = new G4Box("World",fExpHallX,fExpHallY,fExpHallZ);

  G4LogicalVolume* fExpHall_log
    = new G4LogicalVolume(fExpHall_box,Air,"World",0,0,0);

  G4VPhysicalVolume* fExpHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),fExpHall_log,"World",0,false,0);

// The Tank
  G4Box* GasTank = new G4Box("Tank",fTankX,fTankY,fTankZ);

  G4LogicalVolume* GasTank_log
    = new G4LogicalVolume(GasTank,Air,"Tank",0,0,0);

  G4VPhysicalVolume* GasTank_phys
    = new G4PVPlacement(0,G4ThreeVector(),GasTank_log,"Tank",
                        fExpHall_log,false,0);
  
// The Carbon Cylindrical Tube
  G4Tubs* CarbonCan = new G4Tubs("CarbonCan",0,25.4*cm,25.4*cm,
				    0*deg,360*deg);

  G4LogicalVolume* CarbonCan_log = 
    new G4LogicalVolume(CarbonCan,Carbon,"CarbonCan_log",0,0,0);

  G4VPhysicalVolume* CarbonCan_phys =
    new G4PVPlacement(0,G4ThreeVector(0,0,0),CarbonCan_log,"CarbonCan_phys",
		      GasTank_log,false,0);

// The Can of Aluminum
   G4Tubs* AlCan = new G4Tubs("AlCan",0,10.16*cm+0.25*cm,10.16*cm+0.25*cm,
				    0*deg,360*deg);

   G4LogicalVolume* AlCan_log = 
    new G4LogicalVolume(AlCan,Aluminum,"AlCan_log",0,0,0);

   G4VPhysicalVolume* AlCan_phys =
    new G4PVPlacement(0,G4ThreeVector(0,0,0),AlCan_log,"AlCan_phys",
		      CarbonCan_log,false,0);

// The Can of Water
   G4Tubs* WaterCan = new G4Tubs("WaterCan",0*cm,10.16*cm-0.25*cm,10.16*cm-0.25*cm,
				    0*deg,360*deg);

   G4LogicalVolume* WaterCan_log = 
    new G4LogicalVolume(WaterCan,Water,"WaterCan_log",0,0,0);

   G4VPhysicalVolume* WaterCan_phys =
    new G4PVPlacement(0,G4ThreeVector(0,0,0),WaterCan_log,"WaterCan_phys",
		      AlCan_log,false,0);

// The Can of Silicon
   G4Tubs* GlassCan = new G4Tubs("GlassCan",0*cm,2.54*cm,7.6075*cm,
				    0*deg,360*deg);

   G4LogicalVolume* GlassCan_log = 
    new G4LogicalVolume(GlassCan,Silicon,"GlassCan_log",0,0,0);

// The Can of Vacuum
   G4Tubs* VCan = new G4Tubs("VCan",0*cm,2.2225*cm,7.29*cm,0*deg,360*deg);
   G4LogicalVolume* VCan_log = new G4LogicalVolume(VCan,Vacuum,"VCan_log",0,0,0);

// The Glass Disks
   G4Tubs* SDisk = new G4Tubs("SDisk",0*cm, 2.54*cm, 0.15*cm, 0*deg, 360*deg);
   G4LogicalVolume* SDisk_log = new G4LogicalVolume(SDisk,Glass,"SDisk_log",0,0,0);
   
// The Detectors
   G4Tubs* detector = new G4Tubs("Detector",0*cm, 2.54*cm, 0.01*mm, 0*deg, 360*deg);
   fDetectorLogical = new G4LogicalVolume(detector,Water,"DetectorLogical",0,0,0);
  
// The PMTs physical volumes
   G4VPhysicalVolume* GlassCan_phys;
   G4VPhysicalVolume* VCan_phys;
   G4VPhysicalVolume* SDisk_phys;

   for(G4int i = 0; i < 5; i++)
     {
       G4int angle = 90*i;

        GlassCan_phys = new G4PVPlacement(0,
					  G4ThreeVector(cos(angle*deg)*6*cm,
					  sin(angle*deg)*6*cm,
					  17.7925*cm-0.249*cm),
					  GlassCan_log,"GlassCan_phys",
					  CarbonCan_log,false, i);

	VCan_phys = new G4PVPlacement(0,
				       G4ThreeVector(cos(angle*deg)*6*cm,
				       sin(angle*deg)*6*cm,
				       17.7925*cm-0.3175*cm-0.249*cm),
				       VCan_log, "VCan_Phys",
				       CarbonCan_log, false, i);
       
	 SDisk_phys = new G4PVPlacement(0,
					G4ThreeVector(cos(angle*deg)*6*cm,
					sin(angle*deg)*6*cm,
					10.16*cm-0.25*cm-0.18*cm),
					SDisk_log, "SDisk_phys",
					WaterCan_log, false, i);
       
       fDetectorPhysical = new G4PVPlacement(0,
					     G4ThreeVector(cos(angle*deg)*6*cm,
					     sin(angle*deg)*6*cm,
					     10.16*cm-0.25*cm-0.01*cm),
					     fDetectorLogical, "PhotonDetector",
					     WaterCan_log, false, i);
     }

//	------------- Surfaces --------------     //

// Aluminum Surface 
  G4OpticalSurface* OpAlSurface = new G4OpticalSurface("OpAlSurface");
  OpAlSurface->SetType(dielectric_metal);
  OpAlSurface->SetFinish(polished);
  //  OpAlSurface->SetModel(unified);

  G4LogicalBorderSurface* AluminumSurface = new G4LogicalBorderSurface(
		 "AluminumSurface",WaterCan_phys,AlCan_phys,OpAlSurface);

  G4MaterialPropertiesTable* myMPT3 = new G4MaterialPropertiesTable();
  G4double backscatter[nEntries] = {0.1,0.1,0.1};
  G4double reflectivity[nEntries] = {fReflectivity,fReflectivity,fReflectivity}; //should not be zero!
  G4double efficiency[nEntries] = {0.5,0.7,0.9};
  G4double rindex2[nEntries] = {1.3,1.35,1.4};
  G4double specularlobe[nEntries] = {0.3,0.3,0.3};
  G4double specularspike[nEntries] = {0.2,0.2,0.2};

  myMPT3 -> AddProperty("BACKSCATTERCONSTANT",PhotonEnergy,backscatter,nEntries);
  myMPT3 -> AddProperty("REFLECTIVITY",PhotonEnergy,reflectivity,nEntries);
  myMPT3 -> AddProperty("EFFICIENCY",PhotonEnergy,efficiency,nEntries);
  myMPT3 -> AddProperty("RINDEX",PhotonEnergy,rindex2,nEntries);
  // myMPT3 -> AddProperty("SPECULARLOBECONSTANT",PhotonEnergy,specularlobe,nEntries);
  // myMPT3 -> AddProperty("SPECULARSPIKECONSTANT",PhotonEnergy,specularspike,nEntries);

  OpAlSurface->SetMaterialPropertiesTable(myMPT3);

// Glass Disk Surface
  G4OpticalSurface* OpGlSurface = new G4OpticalSurface("OpGlSurface");
  OpGlSurface->SetType(dielectric_dielectric);
  OpGlSurface->SetFinish(ground);
  OpGlSurface->SetModel(glisur);

  G4LogicalBorderSurface* GlSkinSurface = new G4LogicalBorderSurface(
		 "GlSkinSurface",WaterCan_phys,SDisk_phys,OpGlSurface);

  G4MaterialPropertiesTable* myMPT4 = new G4MaterialPropertiesTable();
  G4double backscatter2[nEntries] = {0.1,0.1,0.1};
  G4double reflectivity2[nEntries] = {fReflectivity2,fReflectivity2,fReflectivity2};
  G4double efficiency2[nEntries] = {0.5,0.5,0.5};

  myMPT4 -> AddProperty("BACKSCATTERCONSTANT",PhotonEnergy,backscatter2,nEntries);
  myMPT4 -> AddProperty("REFLECTIVITY",PhotonEnergy,reflectivity2,nEntries);
  myMPT4 -> AddProperty("EFFICIENCY",PhotonEnergy,efficiency2,nEntries);
 
  OpGlSurface->SetMaterialPropertiesTable(myMPT4);

//     ---------- Visualization Attributes ----------     //

   G4VisAttributes *DetVisAtt = new G4VisAttributes(G4Color(0.14, 0.73, 0.14));
   DetVisAtt->SetVisibility(true);
   DetVisAtt->SetForceWireframe(true);
   fDetectorLogical->SetVisAttributes(DetVisAtt);

   //always return the physical World
   return fExpHall_phys;
}
