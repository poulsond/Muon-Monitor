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
// $Id: WaterCherenkovPhysicsListMessenger.hh,v 1.2 2006/06/29 17:54:02 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef WaterCherenkovPhysicsListMessenger_h
#define WaterCherenkovPhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class WaterCherenkovPhysicsList;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class WaterCherenkovPhysicsListMessenger: public G4UImessenger
{
  public:  
    WaterCherenkovPhysicsListMessenger(WaterCherenkovPhysicsList* );
   ~WaterCherenkovPhysicsListMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:  
    WaterCherenkovPhysicsList*     pPhysicsList;
    
    G4UIdirectory*        WaterCherenkovDir;
    G4UIdirectory*        physDir;
    G4UIcmdWithAnInteger* verboseCmd;
    G4UIcmdWithAnInteger* cerenkovCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

