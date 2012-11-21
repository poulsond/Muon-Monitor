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
// $Id: WaterCherenkovPhysicsList.cc,v 1.16 2008/11/21 01:09:56 gum Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ios.hh"
#include <iomanip>

#include "globals.hh"
#include "WaterCherenkovPhysicsList.hh"
#include "WaterCherenkovPhysicsListMessenger.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"
#include "G4MuonDecayChannel.hh"
#include "G4DecayProducts.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterCherenkovPhysicsList::WaterCherenkovPhysicsList() :  G4VUserPhysicsList()
{
  theCerenkovProcess           = 0;
  theScintillationProcess      = 0;
  theAbsorptionProcess         = 0;
  theRayleighScatteringProcess = 0;
  theBoundaryProcess           = 0;
  
  pMessenger = new WaterCherenkovPhysicsListMessenger(this);  
  SetVerboseLevel(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

WaterCherenkovPhysicsList::~WaterCherenkovPhysicsList() { delete pMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program.

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
  ConstructIons();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructIons()
{
  G4Deuteron::DeuteronDefinition();
  G4Triton::TritonDefinition();
  G4He3::He3Definition();
  G4Alpha::AlphaDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructBosons()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructLeptons()
{
  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
  G4TauPlus::TauPlusDefinition();
  G4TauMinus::TauMinusDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructMesons()
{
 //  mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructBaryons()
{
//  baryons
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
  G4Lambda::LambdaDefinition();
  G4AntiLambda::AntiLambdaDefinition();
  G4OmegaMinus::OmegaMinusDefinition();
  G4AntiOmegaMinus::AntiOmegaMinusDefinition();
  G4SigmaPlus::SigmaPlusDefinition();
  G4AntiSigmaPlus::AntiSigmaPlusDefinition();
  G4SigmaMinus::SigmaMinusDefinition();
  G4AntiSigmaMinus::AntiSigmaMinusDefinition();
  G4SigmaZero::SigmaZeroDefinition();
  G4AntiSigmaZero::AntiSigmaZeroDefinition();
  G4XiMinus::XiMinusDefinition();
  G4AntiXiMinus::AntiXiMinusDefinition();
  G4XiZero::XiZeroDefinition();
  G4AntiXiZero::AntiXiZeroDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructOp();
  ConstructGeneral();
  ConstructHP();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Decay.hh"
#include "G4RadioactiveDecay.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructGeneral()
{
  
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while( (*theParticleIterator)() )
    {
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();
      
      if (theDecayProcess->IsApplicable(*particle)&&!particle->IsShortLived()) 
	{ 
	  if(theParticleIterator-> value() == G4MuonPlus::MuonPlusDefinition())
	    { 
	      G4cout << "particle is a mu+! adding decay process..." << G4endl;
	    }
	  if(theParticleIterator-> value() == G4MuonMinus::MuonMinusDefinition())
	    { 
	      G4cout << "particle is a mu-! adding decay process..." << G4endl;
	    }

	  pmanager ->AddProcess(theDecayProcess);
	  // set ordering for PostStepDoIt and AtRestDoIt
	  pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
	  pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
	}
    }
  
//  // Declare radioactive decay to the GenericIon in the IonTable.
//   const G4IonTable *theIonTable = 
//     G4ParticleTable::GetParticleTable()->GetIonTable();
//   G4RadioactiveDecay *theRadioactiveDecay = new G4RadioactiveDecay();

//   for (G4int i=0; i<theIonTable->Entries(); i++) 
//     {
//       G4String particleName = theIonTable->GetParticle(i)->GetParticleName();
//       G4String particleType = theIonTable->GetParticle(i)->GetParticleType();
      
//       if (particleName == "GenericIon") 
// 	{
// 	  G4ProcessManager* pmanager = 
// 	    theIonTable->GetParticle(i)->GetProcessManager();
// 	  pmanager->SetVerboseLevel(VerboseLevel);
// 	  pmanager ->AddProcess(theRadioactiveDecay);
// 	  pmanager ->SetProcessOrdering(theRadioactiveDecay, idxPostStep);
// 	  pmanager ->SetProcessOrdering(theRadioactiveDecay, idxAtRest);
// 	} 
//     }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructDP()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if ( particleName == "lambda" ) {
      // lambda
      // Construct Processes for lambda
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "antilambda" ) {
      // antilambda
      // Construct Processes for antilambda
      pmanager->AddProcess(new G4Decay());
    
    } else if( particleName == "omega-" ) {
      // omega-
      // Construct Processes for omega-
      pmanager->AddProcess(new G4Decay());
    
    } else if( particleName == "anti_omega-" ) {
      // anti_omega-
      // Construct Processes for anti_omega-
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "sigma+" ) {
      // sigma+
      // Construct Processes for sigma+
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "anti_sigma+" ) {
      // anti_sigma+
      // Construct Processes for anti_sigma+
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "sigma-" ) {
      // sigma-
      // Construct Processes for sigma-
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "anti_sigma-" ) {
      // anti_sigma-
      // Construct Processes for anti_sigma-
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "sigma0" ) {
      // sigma0
      // Construct Processes for sigma0
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "anti_sigma0" ) {
      // anti_sigma0
      // Construct Processes for anti_sigma0
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "xi-" ) {
      // xi-
      // Construct Processes for xi-
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "anti_xi-" ) {
      // anti_xi-
      // Construct Processes for anti_xi-
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "xi0" ) {
      // xi0
      // Construct Processes for xi0
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "anti_xi0" ) {
      // anti_xi0
      // Construct Processes for anti_xi0
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "kaon0L" ) {
      // kaon0L
      // Construct Processes for kaon0L
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "kaon0S" ) {
      // kaon0S
      // Construct Processes for kaon0S
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "pi+" ) {
      // pi+
      // Construct Processes for pi+
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "pi-" ) {
      // pi-
      // Construct Processes for pi-
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "pi0" ) {
      // pi0
      // Construct Processes for pi0
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "kaon+" ) {
      // kaon+
      // Construct Processes for kaon+
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "kaon-" ) {
      // kaon-
      // Construct Processes for kaon-
      pmanager->AddProcess(new G4Decay());    

    } else if( particleName == "mu+" ) {
      // mu+
      // Construct Processes for mu+
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "mu-" ) {
      // mu-
      // Construct Processes for mu-
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "tau+" ) {
      // tau+
      // Construct Processes for tau+
      pmanager->AddProcess(new G4Decay());

    } else if( particleName == "tau-" ) {
      // tau-
      // Construct Processes for tau-
      pmanager->AddProcess(new G4Decay());
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4HadronElasticProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4NeutronCaptureAtRest.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4DeuteronInelasticProcess.hh"
#include "G4TritonInelasticProcess.hh"
#include "G4AlphaInelasticProcess.hh"
#include "G4LambdaInelasticProcess.hh"
#include "G4AntiLambdaInelasticProcess.hh"
#include "G4OmegaMinusInelasticProcess.hh"
#include "G4AntiOmegaMinusInelasticProcess.hh"
#include "G4QCaptureAtRest.hh"
#include "G4SigmaPlusInelasticProcess.hh"
#include "G4AntiSigmaPlusInelasticProcess.hh"
#include "G4SigmaMinusInelasticProcess.hh"
#include "G4AntiSigmaMinusInelasticProcess.hh"
#include "G4XiMinusInelasticProcess.hh"
#include "G4AntiXiMinusInelasticProcess.hh"
#include "G4XiZeroInelasticProcess.hh"
#include "G4AntiXiZeroInelasticProcess.hh"
#include "G4KaonZeroLInelasticProcess.hh"
#include "G4KaonZeroSInelasticProcess.hh"
#include "G4PionPlusInelasticProcess.hh"
#include "G4PionMinusInelasticProcess.hh"
#include "G4PionMinusAbsorptionAtRest.hh"
#include "G4KaonPlusInelasticProcess.hh"
#include "G4KaonMinusInelasticProcess.hh"
#include "G4KaonMinusAbsorption.hh"
#include "G4KaonMinusAbsorptionAtRest.hh"
#include "G4MuonNucleusProcess.hh"
#include "G4MuNuclearInteraction.hh"
#include "G4MuonMinusCaptureAtRest.hh"
#include "G4ElectronNuclearProcess.hh"
#include "G4PositronNuclearProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructHP()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if ( particleName == "neutron" ) {
      // neutron
      // Costruct Processes for neutron
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4NeutronInelasticProcess());
      pmanager->AddRestProcess(new G4NeutronCaptureAtRest());
      pmanager->AddDiscreteProcess(new G4HadronCaptureProcess());

    } else if( particleName == "deuteron" ) {
      // deuteron
      // Construct Processes for deuteron
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4DeuteronInelasticProcess());

    } else if( particleName == "triton" ) {
      // triton
      // Construct Processes for triton
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4TritonInelasticProcess());

    } else if( particleName == "He3" ) {
      // He3
      // Construct Processes for He3
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());

    } else if( particleName == "alpha" ) {
      // alpha
      // Construct Processes for alpha
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4AlphaInelasticProcess());
    
    } else if( particleName == "lambda" ) {
      // lambda
      // Construct Processes for lambda
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4LambdaInelasticProcess());

    } else if( particleName == "antilambda" ) {
      // antilambda
      // Construct Processes for antilambda
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4AntiLambdaInelasticProcess());
    
    } else if( particleName == "omega-" ) {
      // omega-
      // Construct Processes for omega-
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4OmegaMinusInelasticProcess());
      pmanager->AddRestProcess(new G4QCaptureAtRest());

    } else if( particleName == "anti_omega-" ) {
      // anti_omega-
      // Construct Processes for anti_omega-
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4AntiOmegaMinusInelasticProcess());

    } else if( particleName == "sigma+" ) {
      // sigma+
      // Construct Processes for sigma+
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4SigmaPlusInelasticProcess());

    } else if( particleName == "anti_sigma+" ) {
      // anti_sigma+
      // Construct Processes for anti_sigma+
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4AntiSigmaPlusInelasticProcess());
      pmanager->AddRestProcess(new G4QCaptureAtRest());

    } else if( particleName == "sigma-" ) {
      // sigma-
      // Construct Processes for sigma-
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4SigmaMinusInelasticProcess());
      pmanager->AddRestProcess(new G4QCaptureAtRest());

    } else if( particleName == "anti_sigma-" ) {
      // anti_sigma-
      // Construct Processes for anti_sigma-
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4AntiSigmaMinusInelasticProcess());

    } else if( particleName == "xi-" ) {
      // xi-
      // Construct Processes for xi-
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4XiMinusInelasticProcess());
      pmanager->AddRestProcess(new G4QCaptureAtRest());

    } else if( particleName == "anti_xi-" ) {
      // anti_xi-
      // Construct Processes for anti_xi-
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4AntiXiMinusInelasticProcess());

    } else if( particleName == "xi0" ) {
      // xi0
      // Construct Processes for xi0
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4XiZeroInelasticProcess());

    } else if( particleName == "anti_xi0" ) {
      // anti_xi0
      // Construct Processes for anti_xi0
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4AntiXiZeroInelasticProcess());

    } else if( particleName == "kaon0L" ) {
      // kaon0L
      // Construct Processes for kaon0L
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4KaonZeroLInelasticProcess());

    } else if( particleName == "pi+" ) {
      // pi+
      // Construct Processes for pi+
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4PionPlusInelasticProcess());

    } else if( particleName == "pi-" ) {
      // pi-
      // Construct Processes for pi-
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4PionMinusInelasticProcess());
      pmanager->AddRestProcess(new G4PionMinusAbsorptionAtRest());
      pmanager->AddRestProcess(new G4QCaptureAtRest());

    } else if( particleName == "kaon+" ) {
      // kaon+
      // Construct Processes for kaon+
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4KaonPlusInelasticProcess());

    } else if( particleName == "kaon-" ) {
      // kaon-
      // Construct Processes for kaon-
      pmanager->AddDiscreteProcess(new G4HadronElasticProcess());
      pmanager->AddDiscreteProcess(new G4KaonMinusInelasticProcess());
      pmanager->AddRestProcess(new G4KaonMinusAbsorption());
      pmanager->AddRestProcess(new G4KaonMinusAbsorptionAtRest());
      pmanager->AddRestProcess(new G4QCaptureAtRest());

    } else if( particleName == "mu+" ) {
      // mu+
      // Construct Processes for mu+
      pmanager->AddDiscreteProcess(new G4MuonNucleusProcess());
      pmanager->AddDiscreteProcess(new G4MuNuclearInteraction());

    } else if( particleName == "mu-" ) {
      // mu-
      // Construct Processes for mu-
      pmanager->AddDiscreteProcess(new G4MuonNucleusProcess());
      pmanager->AddDiscreteProcess(new G4MuNuclearInteraction());
      pmanager->AddRestProcess(new G4MuonMinusCaptureAtRest());

    } else if( particleName == "e+" ) {
      // e+
      // Construct Processes for e+
      pmanager->AddDiscreteProcess(new G4PositronNuclearProcess());

    } else if( particleName == "e-" ) {
      // e-
      // Construct Processes for e-
      pmanager->AddDiscreteProcess(new G4ElectronNuclearProcess());

    } else if( particleName == "tau-" ) {
      // tau-
      // Construct Processes for tau-
      pmanager->AddRestProcess(new G4QCaptureAtRest());
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4MultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuonMinusCaptureAtRest.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4Cerenkov.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {
      // gamma
      // Construct processes for gamma
      pmanager->AddDiscreteProcess(new G4GammaConversion());
      pmanager->AddDiscreteProcess(new G4ComptonScattering());
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());
      
    } else if (particleName == "e-") {
      //electron
      // Construct processes for electron
      pmanager->AddProcess(new G4MultipleScattering(),-1, 1, 1);
      pmanager->AddProcess(new G4eIonisation(),       -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung(),   -1, 3, 3);

    } else if (particleName == "e+") {
      //positron
      // Construct processes for positron
      pmanager->AddProcess(new G4MultipleScattering(),-1, 1, 1);
      pmanager->AddProcess(new G4eIonisation(),       -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung(),   -1, 3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation(),  0,-1, 4);

    } else if( particleName == "mu+" ) {
     //muon
     // Construct processes for muon
     pmanager->AddProcess(new G4MultipleScattering(),-1, 1, 1);
     pmanager->AddProcess(new G4MuIonisation(),      -1, 2, 2);
     pmanager->AddProcess(new G4MuBremsstrahlung(),  -1, 3, 3);
     pmanager->AddProcess(new G4MuPairProduction(),  -1, 4, 4);
    
    } else if( particleName == "mu-" ) {
     //muon
     // Construct processes for muon
     pmanager->AddProcess(new G4MultipleScattering(),   -1, 1, 1);
     pmanager->AddProcess(new G4MuIonisation(),         -1, 2, 2);
     pmanager->AddProcess(new G4MuBremsstrahlung(),     -1, 3, 3);
     pmanager->AddProcess(new G4MuPairProduction(),     -1, 4, 4);
     pmanager->AddProcess(new G4MuonMinusCaptureAtRest(),0,-1,-1);

    } else if( particleName == "deuteron" ) {
      // deuteron
      // Construct processes for deuteron
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation(),       -1, 2, 2);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "triton" ) {
      // triton
      // Construct processes for triton
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation(),       -1, 2, 2);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "He3" ) {
      // He3
      // Construct Processes for He3
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation(),       -1, 2, 2);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "alpha" ) {
      // alpha
      // Construct Processes for alpha
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation(),       -1, 2, 2);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "omega-" ) {
      // omega-
      // Construct Processes for omega-
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "anti_omega-" ) {
      // anti_omega-
      // Construct Processes for anti_omega-
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "sigma+" ) {
      // sigma+
      // Construct Processes for sigma+
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "anti_sigma+" ) {
      // anti_sigma+
      // Construct Processes for anti_sigma+
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "sigma-" ) {
      // sigma-
      // Construct Processes for sigma-
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "anti_sigma-" ) {
      // anti_sigma-
      // Construct Processes for anti_sigma-
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "xi-" ) {
      // xi-
      // Construct Processes for xi-
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "anti_xi-" ) {
      // anti_xi-
      // Construct Processes for anti_xi-
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "pi+" ) {
      // pi+
      // Construct Processes for pi+
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "pi-" ) {
      // pi-
      // Construct Processes for pi-
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "kaon+" ) {
      // kaon+
      // Construct Processes for kaon+
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "kaon-" ) {
      // kaon-
      // Construct Processes for kaon-
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "tau+" ) {
      // tau+
      // Construct Processes for tau+
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else if( particleName == "tau-" ) {
      // tau-
      // Construct Processes for tau-
      pmanager->AddProcess(new G4MultipleScattering(),  -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation(),         -1, 2, 2);
      pmanager->AddProcess(new G4Cerenkov());

    } else {
      if ((particle->GetPDGCharge() != 0.0) &&
          (particle->GetParticleName() != "chargedgeantino")) {
     // all others charged particles except geantino
       pmanager->AddProcess(new G4MultipleScattering(),-1,1,1);
       pmanager->AddProcess(new G4hIonisation(),       -1,2,2);
      }
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::ConstructOp()
{
  theCerenkovProcess      = new G4Cerenkov("Cerenkov");
  theScintillationProcess = new G4Scintillation("Scintillation");
  theAbsorptionProcess    = new G4OpAbsorption();
  theRayleighScatteringProcess = new G4OpRayleigh();
  theBoundaryProcess      = new G4OpBoundaryProcess();

//   theCerenkovProcess->DumpPhysicsTable();
//   theScintillationProcess->DumpPhysicsTable();
//   theAbsorptionProcess->DumpPhysicsTable();
//   theRayleighScatteringProcess->DumpPhysicsTable();

//  SetVerbose(verbose);
  
  theCerenkovProcess->SetMaxNumPhotonsPerStep(30);
  theCerenkovProcess->SetMaxBetaChangePerStep(10.0);
  theCerenkovProcess->SetTrackSecondariesFirst(true);
  
  theScintillationProcess->SetScintillationYieldFactor(1.);
  theScintillationProcess->SetTrackSecondariesFirst(true);

  // Use Birks Correction in the Scintillation process

  G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
  theScintillationProcess->AddSaturation(emSaturation);

  G4OpticalSurfaceModel themodel = unified;
  theBoundaryProcess->SetModel(themodel);

  theParticleIterator->reset();
  while( (*theParticleIterator)() )
    {
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();
      
      if (theCerenkovProcess->IsApplicable(*particle)) 
	{
	  //G4cout << "NOTE: particleName = " << particleName << G4endl;
	  pmanager->AddProcess(theCerenkovProcess);
	  pmanager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
	}
      
//       if (theScintillationProcess->IsApplicable(*particle)) 
// 	{
// 	  G4cout << "setting scintillation process " << G4endl;
// 	  pmanager->AddProcess(theScintillationProcess);
// 	  pmanager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
// 	  pmanager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
// 	}
      
      if (particleName == "opticalphoton") 
	{
	  G4cout << " AddDiscreteProcess to gamma or opticalphoton" << G4endl;
	  pmanager->AddDiscreteProcess(theAbsorptionProcess);
	  pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
	  pmanager->AddDiscreteProcess(theBoundaryProcess);
	}
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::SetVerbose(G4int verbose)
{
  theCerenkovProcess->SetVerboseLevel(verbose);
  theScintillationProcess->SetVerboseLevel(verbose);
  theAbsorptionProcess->SetVerboseLevel(verbose);
  theRayleighScatteringProcess->SetVerboseLevel(verbose);
  theBoundaryProcess->SetVerboseLevel(verbose);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::SetNbOfPhotonsCerenkov(G4int MaxNumber)
{  
  theCerenkovProcess->SetMaxNumPhotonsPerStep(MaxNumber);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void WaterCherenkovPhysicsList::SetCuts()
{
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
  //   the default cut value for all particle types
  // 
  SetCutsWithDefault();
  
  if (verboseLevel>0) DumpCutValuesTable();   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
