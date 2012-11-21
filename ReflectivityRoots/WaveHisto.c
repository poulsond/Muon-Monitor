//
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"

void WaveHisto()
{
  TFile *f = new TFile("WaterCherenkov.root","READ");

  TTree *fTree = (TTree *)f->Get("fTree");

  Int_t nrebin = 10;
  Int_t NHits;  
  Int_t NPhotons;
  Double_t Wavelength_nm[10000];
  Double_t PlaneX_cm[10000];
  Double_t PlaneY_cm[10000];
  Double_t PlaneZ_cm[10000];
  Double_t PrimePosX_cm;
  Double_t PrimePosY_cm;
  Double_t PrimePosZ_cm;
 

  fTree->SetBranchAddress("fNHits",&NHits);
  fTree->SetBranchAddress("fNPhotons",&NPhotons);
  fTree->SetBranchAddress("fPlaneX_cm",PlaneX_cm);
  fTree->SetBranchAddress("fPlaneY_cm",PlaneY_cm);
  fTree->SetBranchAddress("fPlaneZ_cm",PlaneZ_cm);
  fTree->SetBranchAddress("fPrimePosX_cm",&PrimePosX_cm);
  fTree->SetBranchAddress("fPrimePosY_cm",&PrimePosY_cm);
  fTree->SetBranchAddress("fPrimePosZ_cm",&PrimePosZ_cm);
  fTree->SetBranchAddress("fWavelength_nm",Wavelength_nm);

  // Histos
  TH1D *Wavelength = new TH1D
    ("Wavelength","Wavelength", 100, 0, 1000);

  TH1D *PlaneX = new TH1D
    ("X","X", 100, 0, 1000);

  TH1D *PlaneY = new TH1D
    ("Y","Y", 100, 0, 1000);

  TH1D *PlaneZ = new TH1D
    ("Z","Z", 100, 0, 1000);

  // Fill
  for(int i=0; i<fTree->GetEntries(); i++){
    fTree->GetEntry(i);

    double r = sqrt(PrimePosX_cm*PrimePosX_cm+PrimePosY_cm*PrimePosY_cm);

    for(int j=0; j<fPlaneX_cm[]->GetEntries(); j++) {
    // Fill tree with Plane Positions
    PlaneX->Fill(PlaneX_cm);
    }

    for(int j=0; j<fPlaneY_cm[]->GetEntries(); j++) {
    // Fill tree with Plane Positions
    PlaneX->Fill(PlaneY_cm);
    }

    for(int j=0; j<fPlaneZ_cm[]->GetEntries(); j++) {
    // Fill tree with Plane Positions
    PlaneX->Fill(PlaneZ_cm);
    }
  }
}
