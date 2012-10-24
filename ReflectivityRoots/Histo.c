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
  TFile *f = new TFile("Ref1TThousandEvents.root","READ");

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
  TH1D *NHitsHisto = new TH1D("Number of Hits","Number of Hits",100,0,1000);

  for(int i=0; i<fTree->GetEntries(); i++){
    fTree->GetEntry(i);
    
    NHitsHisto->Fill(NHits);
  }
  
  /*  TCanvas *c1 = new TCanvas("c1","c1", 800, 1000);
  // Add Histo Properties here
  NHitsHisto->GetXaxis()->SetTitle("Number of Photon Detections");
  NHitsHisto->GetYaxis()->SetTitle("Number of Occurances/100000 Events");
  // NHitsHist->SetXTitle() ?
  NHitsHisto->GetXaxis()->CenterTitle();
  NHitsHisto->GetYaxis()->CenterTitle();
  // NHitsHist->CenterYaxis() ?
  NHitsHisto->SetTitle("");
  gStyle->SetPadLeftMargin(0.12);
  //
  NHitsHisto->Draw("hist");
  */

  // Number of Hits with as functions of z and r
  TH1D *NHits_z = new TH1D
    ("Z Hits", "Z Hits", 100,-11,11);
  TH1D *NPhotons_z = new TH1D
    ("NPhotons_z", "NPhotons_z", 100,-11,11);

  TH1D *NHits_r = new TH1D
    ("R Hits", "R Hits", 100,0,11);
  TH1D *NPhotons_r = new TH1D
    ("NPhotons_r", "NPhotons_r", 100,0,11);
  
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
 
  TCanvas *c2 = new TCanvas();
  NHits_z->GetXaxis()->SetTitle("Z Position in Water (cm)");
  NHits_z->GetYaxis()->SetTitle("Number of Photons");
  NHits_z->GetXaxis()->CenterTitle();
  NHits_z->GetYaxis()->CenterTitle();
  NHits_z->SetTitle("");
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  //
  NPhotons_z->SetLineColor(kRed);
  NHits_z->DrawCopy("hist");
  NPhotons_z->DrawCopy("hist same");

  TCanvas *c3 = new TCanvas();
  NHits_z->GetXaxis()->SetTitle("Z Position in Water (cm)");
  NHits_z->GetYaxis()->SetTitle("Efficiency of Detection");
  NHits_z->GetXaxis()->CenterTitle();
  NHits_z->GetYaxis()->CenterTitle();
  NHits_z->SetTitle("");
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  //
  NHits_z->Divide(NPhotons_z);
  NHits_z->DrawCopy("hist");

  TCanvas *c4 = new TCanvas();
  NHits_r->GetXaxis()->SetTitle("R Position in Water (cm)");
  NHits_r->GetYaxis()->SetTitle("Number of Photons");
  NHits_r->GetXaxis()->CenterTitle();
  NHits_r->GetYaxis()->CenterTitle();
  NHits_r->SetTitle("");
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  //
  NPhotons_r->SetLineColor(kRed);
  NHits_r->DrawCopy("hist");
  NPhotons_r->DrawCopy("hist same");
  
  TCanvas *c5 = new TCanvas();
  NHits_r->GetXaxis()->SetTitle("R Position in Water (cm)");
  NHits_r->GetYaxis()->SetTitle("Efficiency of Detection");
  NHits_r->GetXaxis()->CenterTitle();
  NHits_r->GetYaxis()->CenterTitle();
  NHits_r->SetTitle("");
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  //
  NHits_r->Divide(NPhotons_r);
  NHits_r->DrawCopy("hist");
}
   


