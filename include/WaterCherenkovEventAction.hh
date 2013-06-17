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
// $Id: WaterCherenkovEventAction.hh,v 1.2 2006/06/29 17:53:57 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef WaterCherenkovEventAction_h
#define WaterCherenkovEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"


const G4int kPMax = 10000; // maximum number of photons in event

class G4Event;
class WaterCherenkovRunAction;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class WaterCherenkovEventAction : public G4UserEventAction
{
public:
  WaterCherenkovEventAction(WaterCherenkovRunAction *);
  ~WaterCherenkovEventAction();
  
public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void AddPhoton(){ fNPhotons++; }
  
  void ResetArrays();
  
  void AddLepton(G4ThreeVector initialPos, G4ThreeVector initialMom, 
		 G4int definition)
  {
    if ( leptonNum > kPMax )
      {
	G4cout << " *** Error!: Hit array too small!  Fix me!" << G4endl;
	G4cout << " ***       : Keeping array sized at kPMax: " << kPMax << G4endl;
	leptonNum = kPMax-1; // to prevent exceeding array size
      }
    
    lDefinition[leptonNum] = definition;
    lPrimePosX_cm[leptonNum] = initialPos.x()/cm;
    lPrimePosY_cm[leptonNum] = initialPos.y()/cm;
    lPrimePosZ_cm[leptonNum] = initialPos.z()/cm;
    lPrimeMomX[leptonNum] = initialMom.x()/keV;
    lPrimeMomY[leptonNum] = initialMom.y()/keV;
    lPrimeMomZ[leptonNum] = initialMom.z()/keV;
    leptonNum++;
  }
  
  void AddProcess(G4int interaction, G4ThreeVector eventPos,
		  G4int PDG, G4double interactionTime)
  {
    if ( interactionNum > kPMax )
      {
	G4cout << " *** Error!: Hit array too small!  Fix me!" << G4endl;
	G4cout << " ***       : Keeping array sized at kPMax: " << kPMax << G4endl;
	interactionNum = kPMax-1; // to prevent exceeding array size
      }
   
    lProcessType[interactionNum] = interaction;
    GPrimePosX_cm[interactionNum] = eventPos.x()/cm;
    GPrimePosY_cm[interactionNum] = eventPos.y()/cm;
    GPrimePosZ_cm[interactionNum] = eventPos.z()/cm;
    pDefinition[interactionNum] = PDG;
    linteractionTime_ns[interactionNum] = interactionTime/ns;
    interactionNum++;
  }
  
  void AddHit(G4ThreeVector planePos,   G4double globalTime, 
	      G4ThreeVector initialPos, G4double wavelength)
  {
    if ( fNHits > kPMax )
      {
	G4cout << " *** Error!: Hit array too small!  Fix me!" << G4endl;
	G4cout << " ***       : Keeping array sized at kPMax: " << kPMax << G4endl;
	fNHits = kPMax-1; // to prevent exceeding array size
      }
    fPlaneX_cm[fNHits] = planePos.x()/cm;
    fPlaneY_cm[fNHits] = planePos.y()/cm;
    fPlaneZ_cm[fNHits] = planePos.z()/cm;
    fPlaneT_ns[fNHits] = globalTime/ns;
    fTrackX_cm[fNHits] = initialPos.x()/cm;
    fTrackY_cm[fNHits] = initialPos.y()/cm;
    fTrackZ_cm[fNHits] = initialPos.z()/cm;
    fWavelength_nm[fNHits] = wavelength;
    fNHits++;
  }

  // Optical Photon Stuff //
  int    *GetNHits()      { return &fNHits; }
  int    *GetPhotonHits() { return &fNPhotons; }
  double *GetPlaneX() { return fPlaneX_cm; }
  double *GetPlaneY() { return fPlaneY_cm; }
  double *GetPlaneZ() { return fPlaneZ_cm; }
  double *GetPlaneT() { return fPlaneT_ns; }
  double *GetTrackX() { return fTrackX_cm; }
  double *GetTrackY() { return fTrackY_cm; }
  double *GetTrackZ() { return fTrackZ_cm; }
  double *GetPrimaryPositionX() { return &fPrimePosX_cm; }
  double *GetPrimaryPositionY() { return &fPrimePosY_cm; }
  double *GetPrimaryPositionZ() { return &fPrimePosZ_cm; }
  double *GetPrimaryMomentumX() { return &fPrimeMomX; }
  double *GetPrimaryMomentumY() { return &fPrimeMomY; }
  double *GetPrimaryMomentumZ() { return &fPrimeMomZ; }
  double *GetWavelength()       { return fWavelength_nm; }
  double *GetGPrimaryPositionX() { return GPrimePosX_cm;   }
  double *GetGPrimaryPositionY() { return GPrimePosY_cm;   }
  double *GetGPrimaryPositionZ() { return GPrimePosZ_cm;   }  
  
  // Lepton Stuff //
  int    *GetlDefinition()       { return lDefinition;  }
  int    *GetpDefinition()       { return pDefinition;  }
  int    *GetleptonNum()         { return &leptonNum;   }
  int    *GetinteractionNum()    { return &interactionNum; }
  double *GetlPrimaryPositionX() { return lPrimePosX_cm;   }
  double *GetlPrimaryPositionY() { return lPrimePosY_cm;   }
  double *GetlPrimaryPositionZ() { return lPrimePosZ_cm;   }
  double *GetlPrimaryMomentumX() { return lPrimeMomX;   }
  double *GetlPrimaryMomentumY() { return lPrimeMomY;   }
  double *GetlPrimaryMomentumZ() { return lPrimeMomZ;   }
  
  // Process Stuff //
  int    *GetlProcessType()      { return lProcessType; }
  double *GetinteractionTime()   { return linteractionTime_ns; }

private:
  WaterCherenkovRunAction * theRun;
  
  // Optical Photon Stuff //
  G4int  fNPhotons;
  G4int  fNHits;
  double fPlaneX_cm[kPMax];
  double fPlaneY_cm[kPMax];
  double fPlaneZ_cm[kPMax];
  double fPlaneT_ns[kPMax];
  double fTrackX_cm[kPMax];
  double fTrackY_cm[kPMax];
  double fTrackZ_cm[kPMax];
  double fPrimePosX_cm;
  double fPrimePosY_cm;
  double fPrimePosZ_cm;
  double fPrimeMomX;
  double fPrimeMomY;
  double fPrimeMomZ;
  double fWavelength_nm[kPMax];
  double GPrimePosX_cm[kPMax];
  double GPrimePosY_cm[kPMax];
  double GPrimePosZ_cm[kPMax];
  
  // Lepton Stuff //
  G4int  lDefinition[kPMax];
  G4int  pDefinition[kPMax];
  G4int  leptonNum;
  G4int  interactionNum;
  double lPrimePosX_cm[kPMax];
  double lPrimePosY_cm[kPMax];
  double lPrimePosZ_cm[kPMax];
  double lPrimeMomX[kPMax];
  double lPrimeMomY[kPMax];
  double lPrimeMomZ[kPMax];
  
  // Process Stuff //
  G4int  lProcessType[kPMax];
  double linteractionTime_ns[kPMax];
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
