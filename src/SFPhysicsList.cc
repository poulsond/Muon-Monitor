//
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  Title:  Simple and Fast Physics List                                   //
//  Date:   20 March 2005                                                  //
//  Author: D.H. Wright (SLAC)                                             //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//

#include "SFPhysicsList.hh"

#include "SFDecayPhysics.hh"
#include "SFBosonPhysics.hh"
#include "SFLeptonPhysics.hh"
#include "SFNeutronPhysics.hh"
#include "SFHadronPhysics.hh"
#include "SFOpticalPhysics.hh"
#include "SFIonPhysics.hh"

SFPhysicsList::SFPhysicsList():  G4VModularPhysicsList()
{
  // default cut value  (1.0mm) 
  defaultCutValue = 1.0*mm;
  // SetVerboseLevel(1);

  // Particle decays
  RegisterPhysics( new SFDecayPhysics("decay"));

  // Bosons (gamma + geantinos)
  RegisterPhysics( new SFBosonPhysics("boson"));

  // Leptons
  RegisterPhysics( new SFLeptonPhysics("lepton"));

  // Neutron Physics
  RegisterPhysics( new SFNeutronPhysics("neutron"));

  // Hadron Physics
  RegisterPhysics( new SFHadronPhysics("hadron"));

  // Optical Physics
  RegisterPhysics( new SFOpticalPhysics("optical"));

  // Ion Physics
  RegisterPhysics( new SFIonPhysics("ion"));
}

SFPhysicsList::~SFPhysicsList()
{;}

#include "SFBosonPhysics.hh"

#include "G4ProcessManager.hh"

// processes
#include "G4GammaConversion.hh"
#include "G4ComptonScattering.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4PhotoNuclearProcess.hh"

// models
#include "G4GammaNuclearReaction.hh"
#include "G4TheoFSGenerator.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4QGSMFragmentation.hh"
#include "G4ExcitedStringDecay.hh"
#include "G4GammaParticipants.hh"
#include "G4QGSModel.hh"

#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Boson Physics

SFBosonPhysics::SFBosonPhysics(const G4String& name)
  :  G4VPhysicsConstructor(name)
{;}


SFBosonPhysics::~SFBosonPhysics()
{;}


void SFBosonPhysics::ConstructParticle()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();
  // gamma
  G4Gamma::GammaDefinition();  
}


void SFBosonPhysics::ConstructProcess()
{
  //
  // First define the gamma-nuclear models
  //

  // low energy part
  G4GammaNuclearReaction* lowEGammaModel = new G4GammaNuclearReaction();
  lowEGammaModel->SetMaxEnergy(3.5*GeV);
 
  // high energy part
  G4TheoFSGenerator* highEGammaModel = new G4TheoFSGenerator();
  G4GeneratorPrecompoundInterface* preComModel =
    new G4GeneratorPrecompoundInterface();
  highEGammaModel->SetTransport(preComModel);
 
  G4QGSModel<G4GammaParticipants>* theStringModel =
    new G4QGSModel<G4GammaParticipants>;
  G4QGSMFragmentation* fragModel = new G4QGSMFragmentation();
  G4ExcitedStringDecay* stringDecay =
    new G4ExcitedStringDecay(fragModel);
  theStringModel->SetFragmentationModel(stringDecay);
 
  highEGammaModel->SetHighEnergyGenerator(theStringModel);
  highEGammaModel->SetMinEnergy(3.*GeV);
  highEGammaModel->SetMaxEnergy(100.*TeV); 
 
  // Now add the processes to the gamma, including e+e- pair creation, 
  // Compton scattering and photo-electric effect

  G4ProcessManager* pManager = G4Gamma::Gamma()->GetProcessManager();
  pManager->AddDiscreteProcess(new G4GammaConversion());
  pManager->AddDiscreteProcess(new G4ComptonScattering());
  pManager->AddDiscreteProcess(new G4PhotoElectricEffect());

  G4PhotoNuclearProcess* thePhotoNuclearProcess = new G4PhotoNuclearProcess();
  thePhotoNuclearProcess->RegisterMe(lowEGammaModel);
  thePhotoNuclearProcess->RegisterMe(highEGammaModel);
  pManager->AddDiscreteProcess(thePhotoNuclearProcess);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Lepton Physics

#include "SFLeptonPhysics.hh"

#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"

// processes
//#include "G4MultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuonMinusCaptureAtRest.hh"
#include "G4hIonisation.hh"
#include "G4ElectronNuclearProcess.hh"
#include "G4PositronNuclearProcess.hh"
#include "G4Decay.hh"

// models
#include "G4ElectroNuclearReaction.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4TauMinus.hh"
#include "G4TauPlus.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"
#include "G4NeutrinoTau.hh"
#include "G4AntiNeutrinoTau.hh"


SFLeptonPhysics::SFLeptonPhysics(const G4String& name)
  :  G4VPhysicsConstructor(name)
{;}


SFLeptonPhysics::~SFLeptonPhysics()
{;}


void SFLeptonPhysics::ConstructParticle()
{ 
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonMinus::MuonMinusDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4TauMinus::TauMinusDefinition();
  G4TauPlus::TauPlusDefinition();

  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
  G4NeutrinoTau::NeutrinoTauDefinition();
  G4AntiNeutrinoTau::AntiNeutrinoTauDefinition();
}


void SFLeptonPhysics::ConstructProcess()
{
  G4ProcessManager* pManager = 0;

  // Model for e+/e- nuclear reactions
   
  G4ElectroNuclearReaction* theElectronReaction =
    new G4ElectroNuclearReaction();
  
  // Electron physics

  pManager = G4Electron::Electron()->GetProcessManager();
  pManager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4eIonisation(),        -1, 2, 2);
  pManager->AddProcess(new G4eBremsstrahlung(),    -1, 3, 3);  

  G4ElectronNuclearProcess* theElectronNuclearProcess =
    new G4ElectronNuclearProcess();
  theElectronNuclearProcess->RegisterMe(theElectronReaction);
  pManager->AddDiscreteProcess(theElectronNuclearProcess);

  //Positron physics

  pManager = G4Positron::Positron()->GetProcessManager(); 
  pManager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4eIonisation(),        -1, 2, 2);
  pManager->AddProcess(new G4eBremsstrahlung(),    -1, 3, 3);  
  pManager->AddProcess(new G4eplusAnnihilation(),   0,-1, 4);

  G4PositronNuclearProcess* thePositronNuclearProcess =
    new G4PositronNuclearProcess();
  thePositronNuclearProcess->RegisterMe(theElectronReaction);
  pManager->AddDiscreteProcess(thePositronNuclearProcess);

  // Muon-

  pManager = G4MuonMinus::MuonMinus()->GetProcessManager(); 
  pManager->AddProcess(new G4MuMultipleScattering(),    -1, 1, 1);
  pManager->AddProcess(new G4MuIonisation(),          -1, 2, 2);
  pManager->AddProcess(new G4MuBremsstrahlung(),      -1, 3, 3);  
  pManager->AddProcess(new G4MuPairProduction(),      -1, 4, 4);
  pManager->AddRestProcess(new G4MuonMinusCaptureAtRest());
  pManager->AddRestProcess(new G4Decay());

  // Muon+

  pManager = G4MuonPlus::MuonPlus()->GetProcessManager(); 
  pManager->AddProcess(new G4MuMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4MuIonisation(),       -1, 2, 2);
  pManager->AddProcess(new G4MuBremsstrahlung(),   -1, 3, 3);  
  pManager->AddProcess(new G4MuPairProduction(),   -1, 4, 4);
  pManager->AddRestProcess(new G4Decay());

  // Tau-

  pManager = G4TauMinus::TauMinus()->GetProcessManager();
  //  pManager->AddProcess(new G4MultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);
 
  // Tau+

  pManager = G4TauPlus::TauPlus()->GetProcessManager();
  //  pManager->AddProcess(new G4MultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

}
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Hadron Physics

#include "SFHadronPhysics.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

// processes
#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"
//#include "G4MultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4HadronElasticProcess.hh"
#include "G4PionPlusInelasticProcess.hh"
#include "G4PionMinusInelasticProcess.hh"
#include "G4KaonPlusInelasticProcess.hh"
#include "G4KaonMinusInelasticProcess.hh"
#include "G4KaonZeroLInelasticProcess.hh"
#include "G4KaonZeroSInelasticProcess.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4AntiProtonInelasticProcess.hh"
#include "G4AntiNeutronInelasticProcess.hh"
#include "G4LambdaInelasticProcess.hh"
#include "G4AntiLambdaInelasticProcess.hh"
#include "G4SigmaPlusInelasticProcess.hh"
#include "G4SigmaMinusInelasticProcess.hh"
#include "G4AntiSigmaPlusInelasticProcess.hh"
#include "G4AntiSigmaMinusInelasticProcess.hh"
#include "G4XiZeroInelasticProcess.hh"
#include "G4XiMinusInelasticProcess.hh"
#include "G4AntiXiZeroInelasticProcess.hh"
#include "G4AntiXiMinusInelasticProcess.hh"
#include "G4OmegaMinusInelasticProcess.hh"
#include "G4AntiOmegaMinusInelasticProcess.hh"
#include "G4AntiProtonAnnihilationAtRest.hh"
#include "G4AntiNeutronAnnihilationAtRest.hh"
#include "G4PionMinusAbsorptionAtRest.hh"
#include "G4KaonMinusAbsorption.hh"

// cross sections
#include "G4PiNuclearCrossSection.hh"
#include "G4ProtonInelasticCrossSection.hh"
#include "G4BGGNucleonInelasticXS.hh"

// models
#include "G4LElastic.hh"
#include "G4CascadeInterface.hh"
#include "G4LEPionPlusInelastic.hh"
#include "G4LEPionMinusInelastic.hh"
#include "G4LEKaonPlusInelastic.hh"
#include "G4LEKaonMinusInelastic.hh"
#include "G4LEKaonZeroLInelastic.hh"
#include "G4LEKaonZeroSInelastic.hh"
#include "G4LEProtonInelastic.hh"
#include "G4LFission.hh"
#include "G4LCapture.hh"
#include "G4LEAntiProtonInelastic.hh"
#include "G4LEAntiNeutronInelastic.hh"
#include "G4LELambdaInelastic.hh"
#include "G4LEAntiLambdaInelastic.hh"
#include "G4LESigmaPlusInelastic.hh"
#include "G4LESigmaMinusInelastic.hh"
#include "G4LEAntiSigmaPlusInelastic.hh"
#include "G4LEAntiSigmaMinusInelastic.hh"
#include "G4LEXiZeroInelastic.hh"
#include "G4LEXiMinusInelastic.hh"
#include "G4LEAntiXiZeroInelastic.hh"
#include "G4LEAntiXiMinusInelastic.hh"
#include "G4LEOmegaMinusInelastic.hh"
#include "G4LEAntiOmegaMinusInelastic.hh"
#include "G4HEPionPlusInelastic.hh"
#include "G4HEPionMinusInelastic.hh"
#include "G4HEKaonPlusInelastic.hh"
#include "G4HEKaonMinusInelastic.hh"
#include "G4HEKaonZeroLongInelastic.hh"
#include "G4HEKaonZeroShortInelastic.hh"
#include "G4HEProtonInelastic.hh"
#include "G4HEAntiProtonInelastic.hh"
#include "G4HEAntiNeutronInelastic.hh"
#include "G4HELambdaInelastic.hh"
#include "G4HEAntiLambdaInelastic.hh"
#include "G4HESigmaPlusInelastic.hh"
#include "G4HESigmaMinusInelastic.hh"
#include "G4HEAntiSigmaPlusInelastic.hh"
#include "G4HEAntiSigmaMinusInelastic.hh"
#include "G4HEXiZeroInelastic.hh"
#include "G4HEXiMinusInelastic.hh"
#include "G4HEAntiXiZeroInelastic.hh"
#include "G4HEAntiXiMinusInelastic.hh"
#include "G4HEOmegaMinusInelastic.hh"
#include "G4HEAntiOmegaMinusInelastic.hh"

SFHadronPhysics::SFHadronPhysics(const G4String& name)
  :G4VPhysicsConstructor(name)
{;}

SFHadronPhysics::~SFHadronPhysics()
{;}


void SFHadronPhysics::ConstructParticle()
{
  //  Construct all mesons
  G4MesonConstructor pMesonConstructor;
  pMesonConstructor.ConstructParticle();

  //  Construct all baryons
  G4BaryonConstructor pBaryonConstructor;
  pBaryonConstructor.ConstructParticle();

  //  Construct  resonaces and quarks
  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();  
}


void SFHadronPhysics::ConstructProcess()
{
  // Hadronic Elastic Process and Model (the same for all hadrons)

  G4HadronElasticProcess* elasticProcess = new G4HadronElasticProcess();
  G4LElastic* elasticModel = new G4LElastic();
  elasticProcess->RegisterMe(elasticModel);

  // Hadronic inelastic models

  G4LEKaonZeroInelastic* LEPk0LModel = new G4LEKaonZeroInelastic();

  G4LEKaonZeroInelastic* LEPk0SModel = new G4LEKaonZeroInelastic();

  //  
  G4ProcessManager * pManager = 0;

  ///////////////////
  //               //
  //  pi+ physics  //
  //               //
  ///////////////////

  pManager = G4PionPlus::PionPlus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);
 
  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4PionPlusInelasticProcess* pipinelProc = new G4PionPlusInelasticProcess();
  G4PiNuclearCrossSection* pion_XC = new G4PiNuclearCrossSection();
  pipinelProc->AddDataSet(pion_XC);

  G4LEPionPlusInelastic* LEPpipModel = new G4LEPionPlusInelastic();
  pipinelProc->RegisterMe(LEPpipModel);
  G4HEPionPlusInelastic* HEPpipModel = new G4HEPionPlusInelastic();
  pipinelProc->RegisterMe(HEPpipModel);

  pManager->AddDiscreteProcess(pipinelProc);

  ///////////////////
  //               //
  //  pi- physics  //
  //               //
  ///////////////////

  pManager = G4PionMinus::PionMinus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4PionMinusInelasticProcess* piminelProc = new G4PionMinusInelasticProcess();
  piminelProc->AddDataSet(pion_XC);

  G4LEPionMinusInelastic* LEPpimModel = new G4LEPionMinusInelastic();
  piminelProc->RegisterMe(LEPpimModel);
  G4HEPionMinusInelastic* HEPpimModel = new G4HEPionMinusInelastic();
  piminelProc->RegisterMe(HEPpimModel);

  pManager->AddDiscreteProcess(piminelProc);

  // pi- absorption at rest
  G4PionMinusAbsorptionAtRest* pimAbsorb = new G4PionMinusAbsorptionAtRest();
  pManager->AddRestProcess(pimAbsorb);
   
  ///////////////////
  //               //
  //  K+ physics   //
  //               //
  ///////////////////

  pManager = G4KaonPlus::KaonPlus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4KaonPlusInelasticProcess* kpinelProc = new G4KaonPlusInelasticProcess();
  G4LEKaonPlusInelastic* LEPkpModel = new G4LEKaonPlusInelastic();
  kpinelProc->RegisterMe(LEPkpModel);
  G4HEKaonPlusInelastic* HEPkpModel = new G4HEKaonPlusInelastic();
  kpinelProc->RegisterMe(HEPkpModel);
  pManager->AddDiscreteProcess(kpinelProc);

  ///////////////////
  //               //
  //  K- physics   //
  //               //
  ///////////////////

  pManager = G4KaonMinus::KaonMinus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4KaonMinusInelasticProcess* kminelProc = new G4KaonMinusInelasticProcess();

  G4LEKaonMinusInelastic* LEPkmModel = new G4LEKaonMinusInelastic();
  kminelProc->RegisterMe(LEPkmModel);
  G4HEKaonMinusInelastic* HEPkmModel = new G4HEKaonMinusInelastic();
  kminelProc->RegisterMe(HEPkmModel);

  pManager->AddDiscreteProcess(kminelProc);

  // K- absorption at rest
  G4KaonMinusAbsorption* kmAbsorb = new G4KaonMinusAbsorption();
  pManager->AddRestProcess(kmAbsorb);

  ///////////////////
  //               //
  //  K0L physics  //
  //               //
  ///////////////////

  pManager = G4KaonZeroLong::KaonZeroLong()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4KaonZeroLInelasticProcess* k0LinelProc = new G4KaonZeroLInelasticProcess();

  k0LinelProc->RegisterMe(LEPk0LModel);
  G4HEKaonZeroLongInelastic* HEPk0LModel = new G4HEKaonZeroLongInelastic();
  k0LinelProc->RegisterMe(HEPk0LModel);

  pManager->AddDiscreteProcess(k0LinelProc);

  ///////////////////
  //               //
  //  K0S physics  //
  //               //
  ///////////////////

  pManager = G4KaonZeroShort::KaonZeroShort()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4KaonZeroSInelasticProcess* k0SinelProc = new G4KaonZeroSInelasticProcess();

  k0SinelProc->RegisterMe(LEPk0SModel);
  G4HEKaonZeroShortInelastic* HEPk0SModel = new G4HEKaonZeroShortInelastic();
  k0SinelProc->RegisterMe(HEPk0SModel);

  pManager->AddDiscreteProcess(k0SinelProc);

  ///////////////////
  //               //
  //    Proton     //
  //               //
  ///////////////////

  pManager = G4Proton::Proton()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4ProtonInelasticProcess* pinelProc = new G4ProtonInelasticProcess();

  G4LEProtonInelastic* LEPpModel = new G4LEProtonInelastic();
  pinelProc->RegisterMe(LEPpModel);
  G4HEProtonInelastic* HEPpModel = new G4HEProtonInelastic();
  pinelProc->RegisterMe(HEPpModel);

  pManager->AddDiscreteProcess(pinelProc);

  ///////////////////
  //               //
  //  Anti-Proton  //
  //               //
  ///////////////////

  pManager = G4AntiProton::AntiProton()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4AntiProtonInelasticProcess* apinelProc = 
    new G4AntiProtonInelasticProcess();
  G4LEAntiProtonInelastic* LEPapModel = new G4LEAntiProtonInelastic(); 
  apinelProc->RegisterMe(LEPapModel);
  G4HEAntiProtonInelastic* HEPapModel = new G4HEAntiProtonInelastic(); 
  apinelProc->RegisterMe(HEPapModel);
  pManager->AddDiscreteProcess(apinelProc);

  // anti-proton annihilation at rest
  G4AntiProtonAnnihilationAtRest* apAnnihil = 
    new G4AntiProtonAnnihilationAtRest();
  pManager->AddRestProcess(apAnnihil);
  
  ///////////////////
  //               //
  // Anti-Neutron  //
  //               //
  ///////////////////

  pManager = G4AntiNeutron::AntiNeutron()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4AntiNeutronInelasticProcess* aninelProc = 
    new G4AntiNeutronInelasticProcess();
  G4LEAntiNeutronInelastic* LEPanModel = new G4LEAntiNeutronInelastic(); 
  aninelProc->RegisterMe(LEPanModel);
  G4HEAntiNeutronInelastic* HEPanModel = new G4HEAntiNeutronInelastic(); 
  aninelProc->RegisterMe(HEPanModel);
  pManager->AddDiscreteProcess(aninelProc);

  // anti-neutron annihilation at rest
  G4AntiNeutronAnnihilationAtRest* anAnnihil = 
    new G4AntiNeutronAnnihilationAtRest();
  pManager->AddRestProcess(anAnnihil);

  ///////////////////
  //               //
  //    Lambda     //
  //               //
  ///////////////////

  pManager = G4Lambda::Lambda()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4LambdaInelasticProcess* linelProc = 
    new G4LambdaInelasticProcess();
  G4LELambdaInelastic* LEPlModel = new G4LELambdaInelastic(); 
  linelProc->RegisterMe(LEPlModel);
  G4HELambdaInelastic* HEPlModel = new G4HELambdaInelastic(); 
  linelProc->RegisterMe(HEPlModel);
  pManager->AddDiscreteProcess(linelProc);

  ///////////////////
  //               //
  //  Anti-Lambda  //
  //               //
  ///////////////////

  pManager = G4AntiLambda::AntiLambda()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4AntiLambdaInelasticProcess* alinelProc = 
    new G4AntiLambdaInelasticProcess();
  G4LEAntiLambdaInelastic* LEPalModel = new G4LEAntiLambdaInelastic(); 
  alinelProc->RegisterMe(LEPalModel);
  G4HEAntiLambdaInelastic* HEPalModel = new G4HEAntiLambdaInelastic(); 
  alinelProc->RegisterMe(HEPalModel);
  pManager->AddDiscreteProcess(alinelProc);

  ///////////////////
  //               //
  //    Sigma-     //
  //               //
  ///////////////////

  pManager = G4SigmaMinus::SigmaMinus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4SigmaMinusInelasticProcess* sminelProc = 
    new G4SigmaMinusInelasticProcess();
  G4LESigmaMinusInelastic* LEPsmModel = new G4LESigmaMinusInelastic(); 
  sminelProc->RegisterMe(LEPsmModel);
  G4HESigmaMinusInelastic* HEPsmModel = new G4HESigmaMinusInelastic(); 
  sminelProc->RegisterMe(HEPsmModel);
  pManager->AddDiscreteProcess(sminelProc);

  ///////////////////
  //               //
  //  Anti-Sigma-  //
  //               //
  ///////////////////

  pManager = G4AntiSigmaMinus::AntiSigmaMinus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4AntiSigmaMinusInelasticProcess* asminelProc = 
    new G4AntiSigmaMinusInelasticProcess();
  G4LEAntiSigmaMinusInelastic* LEPasmModel = 
    new G4LEAntiSigmaMinusInelastic(); 
  asminelProc->RegisterMe(LEPasmModel);
  G4HEAntiSigmaMinusInelastic* HEPasmModel = 
    new G4HEAntiSigmaMinusInelastic(); 
  asminelProc->RegisterMe(HEPasmModel);
  pManager->AddDiscreteProcess(asminelProc);

  ///////////////////
  //               //
  //    Sigma+     //
  //               //
  ///////////////////

  pManager = G4SigmaPlus::SigmaPlus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4SigmaPlusInelasticProcess* spinelProc = new G4SigmaPlusInelasticProcess();
  G4LESigmaPlusInelastic* LEPspModel = new G4LESigmaPlusInelastic(); 
  spinelProc->RegisterMe(LEPspModel);
  G4HESigmaPlusInelastic* HEPspModel = new G4HESigmaPlusInelastic(); 
  spinelProc->RegisterMe(HEPspModel);
  pManager->AddDiscreteProcess(spinelProc);

  ///////////////////
  //               //
  //  Anti-Sigma+  //
  //               //
  ///////////////////

  pManager = G4AntiSigmaPlus::AntiSigmaPlus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4AntiSigmaPlusInelasticProcess* aspinelProc = 
    new G4AntiSigmaPlusInelasticProcess();
  G4LEAntiSigmaPlusInelastic* LEPaspModel = 
    new G4LEAntiSigmaPlusInelastic(); 
  aspinelProc->RegisterMe(LEPaspModel);
  G4HEAntiSigmaPlusInelastic* HEPaspModel = 
    new G4HEAntiSigmaPlusInelastic(); 
  aspinelProc->RegisterMe(HEPaspModel);
  pManager->AddDiscreteProcess(aspinelProc);

  ///////////////////
  //               //
  //      Xi-      //
  //               //
  ///////////////////

  pManager = G4XiMinus::XiMinus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4XiMinusInelasticProcess* xminelProc = new G4XiMinusInelasticProcess();
  G4LEXiMinusInelastic* LEPxmModel = new G4LEXiMinusInelastic(); 
  xminelProc->RegisterMe(LEPxmModel);
  G4HEXiMinusInelastic* HEPxmModel = new G4HEXiMinusInelastic(); 
  xminelProc->RegisterMe(HEPxmModel);
  pManager->AddDiscreteProcess(xminelProc);

  ///////////////////
  //               //
  //   Anti-Xi-    //
  //               //
  ///////////////////

  pManager = G4AntiXiMinus::AntiXiMinus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4AntiXiMinusInelasticProcess* axminelProc = 
    new G4AntiXiMinusInelasticProcess();
  G4LEAntiXiMinusInelastic* LEPaxmModel = new G4LEAntiXiMinusInelastic(); 
  axminelProc->RegisterMe(LEPaxmModel);
  G4HEAntiXiMinusInelastic* HEPaxmModel = new G4HEAntiXiMinusInelastic(); 
  axminelProc->RegisterMe(HEPaxmModel);
  pManager->AddDiscreteProcess(axminelProc);

  ///////////////////
  //               //
  //      Xi0      //
  //               //
  ///////////////////

  pManager = G4XiZero::XiZero()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4XiZeroInelasticProcess* x0inelProc = new G4XiZeroInelasticProcess();
  G4LEXiZeroInelastic* LEPx0Model = new G4LEXiZeroInelastic(); 
  x0inelProc->RegisterMe(LEPx0Model);
  G4HEXiZeroInelastic* HEPx0Model = new G4HEXiZeroInelastic(); 
  x0inelProc->RegisterMe(HEPx0Model);
  pManager->AddDiscreteProcess(x0inelProc);

  ///////////////////
#ifndef SFDecayPhysics_h
#define SFDecayPhysics_h 1

#include "G4VPhysicsConstructor.hh"
#include "G4Decay.hh"


  class SFDecayPhysics : public G4VPhysicsConstructor
  {
  public: 
    SFDecayPhysics(const G4String& name = "decay");
    virtual ~SFDecayPhysics();

    // This method will be invoked in the Construct() method.
    // each particle type will be instantiated
    virtual void ConstructParticle();

    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type 
    virtual void ConstructProcess();

  protected:
    G4Decay fDecayProcess;
  };


#endif
  //               //
  //   Anti-Xi0    //
  //               //
  ///////////////////

  pManager = G4AntiXiZero::AntiXiZero()->GetProcessManager();

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4AntiXiZeroInelasticProcess* ax0inelProc = 
    new G4AntiXiZeroInelasticProcess();
  G4LEAntiXiZeroInelastic* LEPax0Model = new G4LEAntiXiZeroInelastic(); 
  ax0inelProc->RegisterMe(LEPax0Model);
  G4HEAntiXiZeroInelastic* HEPax0Model = new G4HEAntiXiZeroInelastic(); 
  ax0inelProc->RegisterMe(HEPax0Model);
  pManager->AddDiscreteProcess(ax0inelProc);

  ///////////////////
  //               //
  //    Omega-     //
  //               //
  ///////////////////

  pManager = G4OmegaMinus::OmegaMinus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4OmegaMinusInelasticProcess* ominelProc = 
    new G4OmegaMinusInelasticProcess();
  G4LEOmegaMinusInelastic* LEPomModel = new G4LEOmegaMinusInelastic(); 
  ominelProc->RegisterMe(LEPomModel);
  G4HEOmegaMinusInelastic* HEPomModel = new G4HEOmegaMinusInelastic(); 
  ominelProc->RegisterMe(HEPomModel);
  pManager->AddDiscreteProcess(ominelProc);

  ///////////////////
  //               //
  //  Anti-Omega-  //
  //               //
  ///////////////////

  pManager = G4AntiOmegaMinus::AntiOmegaMinus()->GetProcessManager();

  // EM processes
  pManager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4AntiOmegaMinusInelasticProcess* aominelProc = 
    new G4AntiOmegaMinusInelasticProcess();
  G4LEAntiOmegaMinusInelastic* LEPaomModel = 
    new G4LEAntiOmegaMinusInelastic(); 
  aominelProc->RegisterMe(LEPaomModel);
  G4HEAntiOmegaMinusInelastic* HEPaomModel = 
    new G4HEAntiOmegaMinusInelastic(); 
  aominelProc->RegisterMe(HEPaomModel);
  pManager->AddDiscreteProcess(aominelProc);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Neutron Physics

#include "SFNeutronPhysics.hh"

#include "G4ParticleTable.hh"

// processes
#include "G4ProcessManager.hh"
#include "G4HadronElasticProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"

// cross sections

// models
#include "G4LElastic.hh"
#include "G4LENeutronInelastic.hh"
#include "G4LFission.hh"
#include "G4LCapture.hh"

SFNeutronPhysics::SFNeutronPhysics(const G4String& name)
  :G4VPhysicsConstructor(name)
{;}

SFNeutronPhysics::~SFNeutronPhysics()
{;}


void SFNeutronPhysics::ConstructParticle()
{
  //  No need to construct anything here as long as 
  //  SFHadronPhysics is constructed
}


void SFNeutronPhysics::ConstructProcess()
{

  G4ProcessManager* pManager = G4Neutron::Neutron()->GetProcessManager();

  // Neutron elastic process, models and cross sections

  G4HadronElasticProcess* elasticProcess = new G4HadronElasticProcess();


  G4LElastic* theLElasticModel = new G4LElastic();

  elasticProcess->RegisterMe(theLElasticModel);
  pManager->AddDiscreteProcess(elasticProcess);

  // Neutron inelastic process, models and cross sections
  // Use Quark-Gluon String Model between 15 GeV and 100 TeV

  G4NeutronInelasticProcess* ninelProc = new G4NeutronInelasticProcess();

  // Use LEP model between 9.5 and 25 GeV
  G4LENeutronInelastic* LEPnModel = new G4LENeutronInelastic();

  ninelProc->RegisterMe(LEPnModel);

  // Neutron-induced fission process, models and cross sections

  G4HadronFissionProcess* neutronFission = new G4HadronFissionProcess();
  G4LFission* theLFissionModel = new G4LFission();
  theLFissionModel->SetMaxEnergy(20.*TeV);
  neutronFission->RegisterMe(theLFissionModel);
  pManager->AddDiscreteProcess(neutronFission);

  // Neutron capture process, models and cross sections

  G4HadronCaptureProcess* neutronCapture = new G4HadronCaptureProcess();
  G4LCapture* theLCaptureModel = new G4LCapture();
  theLCaptureModel->SetMaxEnergy(20.*TeV);
  neutronCapture->RegisterMe(theLCaptureModel);
  pManager->AddDiscreteProcess(neutronCapture);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Optical Physics

#include "G4LossTableManager.hh"

//Processes
#include "G4OpBoundaryProcess.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4EmSaturation.hh"

SFOpticalPhysics::SFOpticalPhysics(const G4String& name)
  :  G4VPhysicsConstructor(name)
{;}


SFOpticalPhysics::~SFOpticalPhysics()
{;}


void SFOpticalPhysics::ConstructParticle()
{
  // Construct Optical Photons
  G4OpticalPhoton::OpticalPhotonDefinition();
}

void SFOpticalPhysics::ConstructProcess()
{
  G4Cerenkov *theCerenkovProcess           = new G4Cerenkov("Cerenkov");
  G4Scintillation *theScintillationProcess = new G4Scintillation("Scintillation");
  G4OpAbsorption *theAbsorptionProcess     = new G4OpAbsorption();
  G4OpRayleigh *theRayleighScatteringProcess = new G4OpRayleigh();
  G4OpBoundaryProcess *theBoundaryProcess  = new G4OpBoundaryProcess();

  //  theCerenkovProcess->DumpPhysicsTable();
  //  theScintillationProcess->DumpPhysicsTable();
  //  theAbsorptionProcess->DumpPhysicsTable();
  //  theRayleighScatteringProcess->DumpPhysicsTable();

  G4int verbose = 1;
  theCerenkovProcess->SetVerboseLevel(verbose);
  theScintillationProcess->SetVerboseLevel(verbose);
  theAbsorptionProcess->SetVerboseLevel(verbose);
  theRayleighScatteringProcess->SetVerboseLevel(verbose);
  theBoundaryProcess->SetVerboseLevel(verbose);  

  
  theCerenkovProcess->SetMaxNumPhotonsPerStep(20);
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
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    if (theCerenkovProcess->IsApplicable(*particle)) {
      pmanager->AddProcess(theCerenkovProcess);
      pmanager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
    }
    if (theScintillationProcess->IsApplicable(*particle)) {
      pmanager->AddProcess(theScintillationProcess);
      pmanager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
      pmanager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
    }
    if (particleName == "opticalphoton") {
      G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
      pmanager->AddDiscreteProcess(theAbsorptionProcess);
      pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
      pmanager->AddDiscreteProcess(theBoundaryProcess);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Ion Physics

#include "SFIonPhysics.hh"

#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"
#include "G4IonConstructor.hh"
#include "G4ParticleTypes.hh"

// processes
//#include "G4MultipleScattering.hh"
//#include "G4VMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4HadronElasticProcess.hh"
#include "G4HadronInelasticProcess.hh"
#include "G4DeuteronInelasticProcess.hh"
#include "G4TritonInelasticProcess.hh"
#include "G4AlphaInelasticProcess.hh"
#include "G4RadioactiveDecay.hh"

// models
#include "G4LElastic.hh"
#include "G4LEAlphaInelastic.hh"
#include "G4LEDeuteronInelastic.hh"
#include "G4LETritonInelastic.hh"

// cross sections


SFIonPhysics::SFIonPhysics(const G4String& name)
  :  G4VPhysicsConstructor(name)
{;}


SFIonPhysics::~SFIonPhysics()
{;}


void SFIonPhysics::ConstructParticle()
{ 
  // Construct light ions (d, t, 3He, alpha, and generic ion)
  G4IonConstructor ionConstruct;
  ionConstruct.ConstructParticle();
}


void SFIonPhysics::ConstructProcess()
{
  // Hadronic Elastic Process and Model (for all ions except generic ion)

  G4HadronElasticProcess* elasticProcess = new G4HadronElasticProcess();
  G4LElastic* elasticModel = new G4LElastic();
  elasticProcess->RegisterMe(elasticModel);

  // Hadronic inelastic models

  G4ProcessManager * pManager = 0;
  
  ///////////////////
  //               //
  //   Deuteron    //
  //               //
  ///////////////////

  pManager = G4Deuteron::Deuteron()->GetProcessManager();

  // EM processes
  //  pManager->AddProcess(new G4VMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4DeuteronInelasticProcess* dinelProc = new G4DeuteronInelasticProcess();
  dinelProc->RegisterMe( new G4LEDeuteronInelastic() );
  pManager->AddDiscreteProcess(dinelProc);

  ///////////////////
  //               //
  //    Triton     //
  //               //
  ///////////////////

  pManager = G4Triton::Triton()->GetProcessManager(); 

  // EM processes
  //  pManager->AddProcess(new G4VMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4hIonisation(),        -1, 2, 2);

  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4TritonInelasticProcess* tinelProc = new G4TritonInelasticProcess();
  tinelProc->RegisterMe( new G4LETritonInelastic() );
  pManager->AddDiscreteProcess(tinelProc);

  ///////////////////
  //               //
  //      3He      //
  //               //
  ///////////////////

  pManager = G4He3::He3()->GetProcessManager(); 

  // EM processes
  //  pManager->AddProcess(new G4VMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4ionIonisation(),      -1, 2, 2);

  // hadron inelastic

  ///////////////////
  //               //
  //     Alpha     //
  //               //
  ///////////////////

  pManager = G4Alpha::Alpha()->GetProcessManager(); 

  // EM processes
  //  pManager->AddProcess(new G4VMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4ionIonisation(),      -1, 2, 2);
  
  // hadron elastic
  pManager->AddDiscreteProcess(elasticProcess);

  // hadron inelastic
  G4AlphaInelasticProcess* ainelProc = new G4AlphaInelasticProcess();
  ainelProc->RegisterMe( new G4LEAlphaInelastic() );
  pManager->AddDiscreteProcess(ainelProc);

  ///////////////////
  //               //
  //  generic ion  //
  //               //
  ///////////////////

  pManager = G4GenericIon::GenericIon()->GetProcessManager();

  // EM processes for generic ion
  //  pManager->AddProcess(new G4VMultipleScattering(), -1, 1, 1);
  pManager->AddProcess(new G4ionIonisation(),      -1, 2, 2);
 
  // hadron inelastic
  
  // radioactive 
  pManager->AddRestProcess(new G4RadioactiveDecay());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Decay Physics

#include "SFDecayPhysics.hh"
#include "G4ProcessManager.hh"


SFDecayPhysics::SFDecayPhysics(const G4String& name)
  :  G4VPhysicsConstructor(name)
{;}

SFDecayPhysics::~SFDecayPhysics()
{;}

void SFDecayPhysics::ConstructParticle()
{;}

void SFDecayPhysics::ConstructProcess()
{
  // Add Decay Process
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    // Addition for mu-   
    if(particle->GetPDGEncoding() == 13) particle->SetPDGStable(false);
    // Normal
    if (fDecayProcess.IsApplicable(*particle)) { 
      pmanager ->AddProcess(&fDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrderingToFirst(&fDecayProcess, idxPostStep);
      pmanager ->SetProcessOrderingToFirst(&fDecayProcess, idxAtRest);
    }
  }
}

void SFPhysicsList::SetCuts()
{
  // Use default cut values gamma and e processes
  SetCutsWithDefault();   
}
