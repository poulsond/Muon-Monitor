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
// $Id: WaterCherenkovPrimaryGeneratorAction.cc,v 1.6 2006/06/29 17:54:27 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "WaterCherenkovPrimaryGeneratorAction.hh"
#include "WaterCherenkovPrimaryGeneratorMessenger.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "TF1.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterCherenkovPrimaryGeneratorAction::WaterCherenkovPrimaryGeneratorAction()
{
  G4Gun = new G4ParticleGun();
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterCherenkovPrimaryGeneratorAction::~WaterCherenkovPrimaryGeneratorAction()
{
  delete G4Gun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4Gun->SetParticleMomentumDirection(G4ThreeVector(1,0,0));
 
  //should be in cyclindrical coordinates
  G4double MaxRadius = 15.0*cm; //can is 10.15cm
  G4double X = (G4UniformRand()-0.5)*2*MaxRadius;
  G4double Y = (G4UniformRand()-0.5)*2*MaxRadius;
  G4double Z = (G4UniformRand()-0.5)*2*MaxRadius;

  while(sqrt(X*X+Y*Y)>MaxRadius){
      X = (G4UniformRand()-0.5)*2*MaxRadius;
      Y = (G4UniformRand()-0.5)*2*MaxRadius;
  }

  G4Gun->SetParticlePosition(G4ThreeVector(X, Y, Z));
  G4Gun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
 if (G4Gun->GetParticleDefinition()->GetParticleName() != "opticalphoton")
   {
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the GPS is not an opitcalphoton" << G4endl;
     return;
   }
   	       
 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = G4Gun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton); 
 G4double modul2       = product*product;

 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product; 
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 G4Gun->SetParticlePolarization(polar);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
