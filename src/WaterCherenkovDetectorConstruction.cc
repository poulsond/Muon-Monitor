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

// Ethanol
  G4Material* Ethanol = new G4Material("Ethanol", density = 0.789*g/cm3, nelements=3);
  Ethanol->AddElement(H, 6);  
  Ethanol->AddElement(C, 2);  
  Ethanol->AddElement(O, 1);  
  
// Ethanol and Water Mx
  G4Material* EthanolandWater = new G4Material("EthanolandWater", density = 0.8945*g/cm3, nelements = 2);
  EthanolandWater->AddMaterial(Ethanol, 50.*perCent);
  EthanolandWater->AddMaterial(Water, 50.*perCent);

// POPOP
  G4Material *POPOP = new G4Material("POPOP", density = 364.4*g/mole, nelements = 4);
  POPOP->AddElement(C, 24);
  POPOP->AddElement(H, 16);
  POPOP->AddElement(N, 2);
  POPOP->AddElement(O, 2);
 
// Toluene
  G4Material *Toluene = new G4Material("Toluene", density = 0.87*g/cm3, nelements = 2);
  Toluene->AddElement(C, 7);
  Toluene->AddElement(H, 8);

// PPO
  G4Material *PPO = new G4Material("PPO", density = 1.06*g/cm3, nelements = 4);
  PPO->AddElement(C, 15);
  PPO->AddElement(H, 11);
  PPO->AddElement(N, 1);
  PPO->AddElement(O, 1);

// NE-216
  G4Material *NE = new G4Material("NE-216", density = 0.885*g/cm3, nelements = 3);
  NE->AddMaterial(Toluene, 89.12*perCent);
  NE->AddMaterial(PPO, 10.66*perCent);
  NE->AddMaterial(POPOP, 0.22*perCent);

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

  const G4int nEntries = 32;
  //  const G4int NumEntries = 7;

  G4double PhotonEnergy[nEntries] =
            { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
              2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
              2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
              2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
              2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
              3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
              3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
              3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };

  /*G4double ScintEnergies[NumEntries] =
            { 2.691*eV, 2.839*eV, 2.947*eV, 3.094*eV,
              3.257*eV, 3.4388*eV, 3.641*eV };
  */
  G4double RefractiveIndexWater[nEntries] =
            { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
              1.346,  1.3465, 1.347,  1.3475, 1.348,
              1.3485, 1.3492, 1.35,   1.3505, 1.351,
              1.3518, 1.3522, 1.3530, 1.3535, 1.354,
              1.3545, 1.355,  1.3555, 1.356,  1.3568,
              1.3572, 1.358,  1.3585, 1.359,  1.3595,
              1.36,   1.3608 };

  G4double Absorption[nEntries] =
           { fAbsConstant*3.448*m,  fAbsConstant*4.082*m,   fAbsConstant*6.329*m, 
	     fAbsConstant*9.174*m,  fAbsConstant*12.346*m,  fAbsConstant*13.889*m,
	     fAbsConstant*15.152*m,  fAbsConstant*17.241*m,  fAbsConstant*18.868*m,
	     fAbsConstant*20.000*m,  fAbsConstant*26.316*m,  fAbsConstant*35.714*m,
	     fAbsConstant*45.455*m,  fAbsConstant*47.619*m,  fAbsConstant*52.632*m,
	     fAbsConstant*52.632*m,  fAbsConstant*55.556*m,  fAbsConstant*52.632*m,
	     fAbsConstant*52.632*m,  fAbsConstant*47.619*m,  fAbsConstant*45.455*m,
	     fAbsConstant*41.667*m,  fAbsConstant*37.037*m,  fAbsConstant*33.333*m,
	     fAbsConstant*30.000*m,  fAbsConstant*28.500*m,  fAbsConstant*27.000*m, 
	     fAbsConstant*24.500*m,  fAbsConstant*22.000*m,  fAbsConstant*19.500*m,
	     fAbsConstant*17.500*m,  fAbsConstant*14.500*m };
  
  G4double RefractiveIndexEthanol[nEntries];
  for(int i = 0; i < nEntries; i++){
    double lambda = 1.23779*(eV*mm)/PhotonEnergy[i];
    double n = 1.35265 + 0.00306*1/lambda*1/lambda + 0.00002*1/lambda*1/lambda*1/lambda*1/lambda;
    RefractiveIndexEthanol[i] = n;
  } 
  
  /*G4double PlasticAbs[NumEntries] = 
           { 3.1*m, 3.5*m, 5.1*m, 5.7*m, 7.8*m, 8.3*m, 8.2*m };
  */
  G4double RefractiveIndexPlastic[nEntries];
  G4double PlastFast[nEntries];
  G4double PlasticAbs[nEntries];
  //G4double PlastSlow[NumEntries];
  for(int i = 0; i < nEntries; i++){
    RefractiveIndexPlastic[i] = 1.523;
    PlastFast[i] = 3.5;
    PlasticAbs[i] = 1.5*m;
    //    PlastSlow[i] = 17.61;
  }

  G4double ScintilFast[nEntries] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };

  G4double ScintilSlow[nEntries] =
            { 0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,
              7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,
              3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,
              4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
              7.00, 6.00, 5.00, 4.00 };

  G4MaterialPropertiesTable* WaterMPT = new G4MaterialPropertiesTable();
  WaterMPT->AddProperty("RINDEX",PhotonEnergy,RefractiveIndexWater,nEntries);
  WaterMPT->AddProperty("ABSLENGTH",PhotonEnergy,Absorption,nEntries);
  //WaterMPT->AddProperty("FASTCOMPONENT",PhotonEnergy,ScintilFast,nEntries);
  //WaterMPT->AddProperty("SLOWCOMPONENT",PhotonEnergy,ScintilSlow,nEntries);
  
  //WaterMPT->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  //WaterMPT->AddConstProperty("RESOLUTIONSCALE",1.0);
  //WaterMPT->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  //WaterMPT->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  //WaterMPT->AddConstProperty("YIELDRATIO",0.8);
  
  Water->SetMaterialPropertiesTable(WaterMPT);

  G4MaterialPropertiesTable* PlasticMPT = new G4MaterialPropertiesTable();
  PlasticMPT->AddProperty("RINDEX",PhotonEnergy,RefractiveIndexPlastic,nEntries);
  PlasticMPT->AddProperty("ABSLENGTH",PhotonEnergy,PlasticAbs,nEntries);
  PlasticMPT->AddProperty("FASTCOMPONENT",PhotonEnergy,PlastFast,nEntries);
  // PlasticMPT->AddProperty("SLOWCOMPONENT",ScintEnergies,PlastSlow,nEntries);
  
  PlasticMPT->AddConstProperty("SCINTILLATIONYIELD",15000/MeV);
  PlasticMPT->AddConstProperty("RESOLUTIONSCALE",1.0);
  PlasticMPT->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  //  PlasticMPT->AddConstProperty("SLOWTIMECONSTANT",1.*ns);
  //PlasticMPT->AddConstProperty("YIELDRATIO",0.895);
  
  NE->SetMaterialPropertiesTable(PlasticMPT);
  
  G4MaterialPropertiesTable* EthanolMPT = new G4MaterialPropertiesTable();
  EthanolMPT->AddProperty("RINDEX",PhotonEnergy,RefractiveIndexEthanol,nEntries);
  EthanolMPT->AddProperty("ABSLENGTH",PhotonEnergy,Absorption,nEntries);
  //EthanolMPT->AddProperty("FASTCOMPONENT",PhotonEnergy,ScintilFast,nEntries);
  //EthanolMPT->AddProperty("SLOWCOMPONENT",PhotonEnergy,ScintilSlow,nEntries);
  
  //EthanolMPT->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  //EthanolMPT->AddConstProperty("RESOLUTIONSCALE",1.0);
  //EthanolMPT->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  //EthanolMPT->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  //EthanolMPT->AddConstProperty("YIELDRATIO",0.8);
  
  Ethanol->SetMaterialPropertiesTable(EthanolMPT);
  
  // Set the Birks Constant for the Water scintillator

  //Water->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
  NE->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
  //Ethanol->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

  // Glass
  G4double Glass_RIND[nEntries]=
           {1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
	    1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
	    1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,1.49,
	    1.49,1.49,1.49,1.49,1.49};

  G4double Glass_AbsLength[nEntries]=
           {420.*cm,420.*cm,420.*cm,420.*cm,420.*cm,420.*cm,
	    420.*cm,420.*cm,420.*cm,420.*cm,420.*cm,420.*cm,
	    420.*cm,420.*cm,420.*cm,420.*cm,420.*cm,420.*cm,
	    420.*cm,420.*cm,420.*cm,420.*cm,420.*cm,420.*cm,
	    420.*cm,420.*cm,420.*cm,420.*cm,420.*cm,420.*cm,
	    420.*cm,420.*cm};

  G4MaterialPropertiesTable *Glass_mt = new G4MaterialPropertiesTable();
  Glass_mt->AddProperty("ABSLENGTH",PhotonEnergy,Glass_AbsLength,nEntries);
  Glass_mt->AddProperty("RINDEX",PhotonEnergy,Glass_RIND,nEntries);
  Glass->SetMaterialPropertiesTable(Glass_mt);  

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
  //  G4Box* CarbonCan = new G4Box("CarbonCan",
  //		       25.4*cm,25.4*cm,25.4*cm);  

  G4LogicalVolume* CarbonCan_log = 
    new G4LogicalVolume(CarbonCan,Carbon,"CarbonCan_log",0,0,0);

  G4VPhysicalVolume* CarbonCan_phys =
    new G4PVPlacement(0,G4ThreeVector(0,0,0),CarbonCan_log,"CarbonCan_phys",
		      GasTank_log,false,0);

  // The NE-216 Veto
  G4Tubs *Scintillator = new G4Tubs("Scintillator",0,11.16*cm+0.25*cm,11.16*cm+0.25*cm,
				    0*deg, 360*deg);

  Scintillator_log = new G4LogicalVolume(Scintillator, NE,"Scintillator_log",0,0,0);
  
  Scintillator_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),Scintillator_log,"Scintillator_phys",
					CarbonCan_log,false,0);

// The Carbon Disk
  G4Tubs* CarbonDisk = new G4Tubs("CarbonDisk",0,9*cm,0.5*cm,
				 0*deg,360*deg);

  CarbonDisk_log = 
    new G4LogicalVolume(CarbonDisk,Carbon,"CarbonDisk_log",0,0,0);

  CarbonDisk_phys =
    new G4PVPlacement(0,G4ThreeVector(0,0,11.16*cm-0.25*cm),CarbonDisk_log,"CarbonDisk_phys",
		      Scintillator_log,false,0);
  
  // The Can of Aluminum
  G4Tubs* AlCan = new G4Tubs("AlCan",0,10.16*cm+0.25*cm,10.16*cm+0.25*cm,
  			     0*deg,360*deg);
  //  G4Box* AlCan = new G4Box("AlCan",
  //		   10.16*cm+.25*cm,10.16*cm+.25*cm,10.16*cm+.25*cm);
  //G4Tubs* AlCan = new G4Tubs("AlCan",0,13.16*cm+0.25*cm,13.16*cm+0.25*cm,
  //		     0*deg,360*deg);  

  G4LogicalVolume *AlCan_log = new G4LogicalVolume(AlCan,Aluminum,"AlCan_log",0,0,0);

  G4VPhysicalVolume *AlCan_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),AlCan_log,"AlCan_phys",
				 Scintillator_log,false,0);
  
  // The Can of Water
  G4Tubs* WaterCan = new G4Tubs("WaterCan",0*cm,10.16*cm-0.25*cm,10.16*cm-0.25*cm,
				0*deg,360*deg);
  //   G4Box* WaterCan = new G4Box("WaterCan",
  //		       10.16*cm-0.25*cm,10.16*cm-0.25*cm,10.16*cm-0.25*cm);
  //  G4Tubs* WaterCan = new G4Tubs("WaterCan",0*cm,13.16*cm-0.25*cm,13.16*cm-0.25*cm,
  //			0*deg,360*deg);
  
  WaterCan_log = new G4LogicalVolume(WaterCan,Water,"WaterCan_log",0,0,0);
  
  WaterCan_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),WaterCan_log,"WaterCan_phys",
				    AlCan_log,false,0);
  
  // The Can of Silicon
  G4Tubs* GlassCan = new G4Tubs("GlassCan",0*cm,2.54*cm,7.6075*cm/*6.1075*cm*/
				,0*deg,360*deg);
  
  G4LogicalVolume* GlassCan_log = 
    new G4LogicalVolume(GlassCan,Silicon,"GlassCan_log",0,0,0);
  
  // The Can of Vacuum
  G4Tubs* VCan = new G4Tubs("VCan",0*cm,2.2225*cm,7.29*cm/*5.79*cm*/,0*deg,360*deg);
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
  
  for(G4int i = 0; i < 4; i++)
    {
      G4int angle = 90*i;
      
      GlassCan_phys = new G4PVPlacement(0,
                          G4ThreeVector(cos(angle*deg)*6*cm/*change*/,
			  sin(angle*deg)*6*cm,
                /*change*/17.7925*cm-0.249*cm),
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
   OpAlSurface->SetModel(glisur);
   //OpAlSurface->SetModel(unified);
   
   
   G4LogicalBorderSurface* AluminumSurface = new G4LogicalBorderSurface(
		  "AluminumSurface",WaterCan_phys,AlCan_phys,OpAlSurface);

   G4MaterialPropertiesTable* Alu_MPT = new G4MaterialPropertiesTable();
   
   G4double backscatter[nEntries];
 
   G4double reflectivity[nEntries];

   G4double efficiency[nEntries];

   G4double rindex2[nEntries];

   G4double specularlobe[nEntries];

   G4double specularspike[nEntries];

  for(int i=0; i<nEntries; i++) {
    backscatter[i] = 0.1;
    reflectivity[i] = fReflectivity;
    efficiency[i] = 0.5 + i*(0.4/nEntries);
    rindex2[i] = 1.3 + i*(0.1/nEntries);
    specularlobe[i] = 0.3;
    specularspike[i] = 0.2;
  }

  Alu_MPT -> AddProperty("BACKSCATTERCONSTANT",PhotonEnergy,backscatter,nEntries);
  Alu_MPT -> AddProperty("REFLECTIVITY",PhotonEnergy,reflectivity,nEntries);
  Alu_MPT -> AddProperty("EFFICIENCY",PhotonEnergy,efficiency,nEntries);
  Alu_MPT -> AddProperty("RINDEX",PhotonEnergy,rindex2,nEntries);
  Alu_MPT -> AddProperty("SPECULARLOBECONSTANT",PhotonEnergy,specularlobe,nEntries);
  Alu_MPT -> AddProperty("SPECULARSPIKECONSTANT",PhotonEnergy,specularspike,nEntries);

  OpAlSurface->SetMaterialPropertiesTable(Alu_MPT);

// Glass Disk Surface
  G4OpticalSurface* OpGlSurface = new G4OpticalSurface("OpGlSurface");
  OpGlSurface->SetType(dielectric_dielectric);
  OpGlSurface->SetFinish(ground);
  OpGlSurface->SetModel(glisur);

  G4LogicalBorderSurface* GlSkinSurface = new G4LogicalBorderSurface(
		 "GlSkinSurface",WaterCan_phys,SDisk_phys,OpGlSurface);

  G4MaterialPropertiesTable* Glass_MPT = new G4MaterialPropertiesTable();
 
  G4double backscatterGlass[nEntries];// = {0.1,0.1,0.1};
  G4double efficiencyGlass[nEntries];// = {0.5,0.5,0.5};

  for(int i=0; i<nEntries; i++) {
    backscatterGlass[i] = 0.1;
    efficiencyGlass[i] = 0.5;
  }

  Glass_MPT -> AddProperty("BACKSCATTERCONSTANT",PhotonEnergy,backscatterGlass,nEntries);
  Glass_MPT -> AddProperty("EFFICIENCY",PhotonEnergy,efficiencyGlass,nEntries);
 
  OpGlSurface->SetMaterialPropertiesTable(Glass_MPT);

//     ---------- Visualization Attributes ----------     //

   G4VisAttributes *DetVisAtt = new G4VisAttributes(G4Color(0.14, 0.73, 0.14));
   DetVisAtt->SetVisibility(true);
   DetVisAtt->SetForceWireframe(true);
   fDetectorLogical->SetVisAttributes(DetVisAtt);

   //always return the physical World
   return fExpHall_phys;
}
