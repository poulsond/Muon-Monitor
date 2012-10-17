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

void Histo()
{
  TFile *f = new TFile("Ref9HThousandEvents.root","READ");

  TTree *fTree = (TTree *)f->Get("fTree");

  Int_t NHits;  
  Int_t NPhotons;
  Double_t PlaneX[10000];
  Double_t PlaneY[10000];
  Double_t PlaneZ[10000];
  Double_t PrimePosX_cm;
  Double_t PrimePosY_cm;
  Double_t PrimePosZ_cm;
 

  fTree->SetBranchAddress("fNHits",&NHits);
  fTree->SetBranchAddress("fNPhotons",&NPhotons);
  fTree->SetBranchAddress("fPlaneX_cm",PlaneX);
  fTree->SetBranchAddress("fPlaneY_cm",PlaneY);
  fTree->SetBranchAddress("fPlaneZ_cm",PlaneZ);
  fTree->SetBranchAddress("fPrimePosX_cm",&PrimePosX_cm);
  fTree->SetBranchAddress("fPrimePosY_cm",&PrimePosY_cm);
  fTree->SetBranchAddress("fPrimePosZ_cm",&PrimePosZ_cm);

  // Number of Hits Histogram
  TH1D *NHitsHisto = new TH1D("Number of Hits","Number of Hits",100,0,10000);

  for(int i=0; i<fTree->GetEntries(); i++){
    fTree->GetEntry(i);
    
    NHitsHisto->Fill(NHits);
  }
  
  new TCanvas();
  NHitsHisto->Draw("hist");


  // Number of Hits with as functions of z and r
  TH1D *NHits_z = new TH1D
    ("Z Hits", "Z Hits", 100,-15,15);
  TH1D *NPhotons_z = new TH1D
    ("NPhotons_z", "NPhotons_z", 100,-15,15);

  TH1D *NHits_r = new TH1D
    ("R Hits", "R Hits", 100,0,12);
  TH1D *NPhotons_r = new TH1D
    ("NPhotons_r", "NPhotons_r", 100,0,12);
  
  for(int i=0; i<fTree->GetEntries(); i++){
    fTree->GetEntry(i);

    double r = sqrt(PrimePosX_cm*PrimePosX_cm+PrimePosY_cm*PrimePosY_cm);

    // Fill tree with NHits and NPhotons as a function of z 
    NHits_z->Fill(PrimePosZ_cm, NHits);
    NPhotons_z->Fill(PrimePosZ_cm, NPhotons);

    // Fill tree with NHits and NPhotons as a function of r
    NHits_r->Fill(r, NHits);
    NPhotons_r->Fill(r, NPhotons);
  }
 
  new TCanvas();
  NPhotons_z->SetLineColor(kRed);
  NHits_z->DrawCopy("hist");
  NPhotons_z->DrawCopy("hist same");
  
  new TCanvas();
  NHits_z->Divide(NPhotons_z);
  NHits_z->DrawCopy("hist");

  new TCanvas();
  NPhotons_r->SetLineColor(kRed);
  NHits_r->DrawCopy("hist");
  NPhotons_r->DrawCopy("hist same");
  
  new TCanvas();
  NHits_r->Divide(NPhotons_r);
  NHits_r->DrawCopy("hist");
}
   


