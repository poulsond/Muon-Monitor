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
  TFile *f = new TFile("WaterCherenkov.root","READ");

  TTree *fTree = (TTree *)f->Get("fTree");

  Int_t nrebin = 10;
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
  
  // Number of Muon Events as a function of z and r
  TH1D *MuonPos_z = new TH1D
    ("ZPos", "ZPos", 100,-11,11);
  TH1D *MuonPos_r = new TH1D
    ("RPos", "RPos", 100,0,11);

  /*TH1D *NRatio_z = new TH1D
    ("Ratio_z","Ratio_z", 100,0,11);
  TH1D *NRatio_r = new TH1D
  ("Ratio_r","Ratio_r", 100,0,11);*/
  

  for(int i=0; i<fTree->GetEntries(); i++){
    fTree->GetEntry(i);

    double r = sqrt(PrimePosX_cm*PrimePosX_cm+PrimePosY_cm*PrimePosY_cm);

    // Fill tree with NHits and NPhotons as a function of z 
    NHits_z->Fill(PrimePosZ_cm, NHits);
    NPhotons_z->Fill(PrimePosZ_cm, NPhotons);
    // NRatio_z->Fill(PrimePosZ_cm, NHits/NPhotons);

    // Fill tree with NHits and NPhotons as a function of r
    NHits_r->Fill(r, NHits);
    NPhotons_r->Fill(r, NPhotons);
    //NRatio_r->Fill(r, NHits/NPhotons);

    // Fill tree with Prime Position of Muon as function of z/r
    MuonPos_z->Fill(PrimePosZ_cm);
    MuonPos_r->Fill(r);
  }
 
  TCanvas *c2 = new TCanvas();
  NHits_z->GetXaxis()->SetTitle("Z Position in Water (cm)");
  NHits_z->GetYaxis()->SetTitle("Number of Photons");
  NHits_z->GetXaxis()->CenterTitle();
  NHits_z->GetYaxis()->CenterTitle();
  NHits_z->SetTitle("");
  NHits_z->GetYaxis()->SetTitleOffset(0.8);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  //
  NHits_z->SetLineWidth(2);
  NHits_z->Sumw2();
  NPhotons_z->Sumw2();
  //
  NPhotons_z->SetLineColor(kRed);
  NPhotons_z->SetLineWidth(2);
  NHits_z->SetLineWidth(2);
  // 
  NHits_z->Rebin(nrebin);
  NPhotons_z->Rebin(nrebin);
  NHits_z->DrawCopy("hist");
  NPhotons_z->DrawCopy("hist same");

  TCanvas *c3 = new TCanvas();
  NHits_z->GetXaxis()->SetTitle("Z Position in Water (cm)");
  NHits_z->GetYaxis()->SetTitle("Efficiency of Detection");
  NHits_z->GetXaxis()->CenterTitle();
  NHits_z->GetYaxis()->CenterTitle();
  NHits_z->SetTitle("");
  NHits_z->GetYaxis()->SetTitleOffset(0.8);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  // Efficiency is correlated. Can't use Sumw2. Need Binomial errorsl.
  NHits_z->Divide(NHits_z,NPhotons_z,1,1,"B");
  NHits_z->SetLineWidth(2);
  //
  NHits_z->DrawCopy("E");
  NHits_z->DrawCopy("hist same");

  TCanvas *c4 = new TCanvas();
  NHits_r->GetXaxis()->SetTitle("R Position in Water (cm)");
  NHits_r->GetYaxis()->SetTitle("Number of Photons");
  NHits_r->GetXaxis()->CenterTitle();
  NHits_r->GetYaxis()->CenterTitle();
  NHits_r->SetTitle("");
  NHits_r->GetYaxis()->SetTitleOffset(0.8);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  //
  NHits_r->SetLineWidth(2);
  NHits_r->Sumw2();
  NPhotons_r->Sumw2();
  //
  NPhotons_r->SetLineColor(kRed);
  NPhotons_r->SetLineWidth(2);
  NHits_r->SetLineWidth(2);
  //
  NHits_r->Rebin(nrebin);
  NPhotons_r->Rebin(nrebin);
  NHits_r->DrawCopy("hist");
  NPhotons_r->DrawCopy("hist same");
  
  TCanvas *c5 = new TCanvas();
  NHits_r->GetXaxis()->SetTitle("R Position in Water (cm)");
  NHits_r->GetYaxis()->SetTitle("Efficiency of Detection");
  NHits_r->GetXaxis()->CenterTitle();
  NHits_r->GetYaxis()->CenterTitle();
  NHits_r->SetTitle("");
  NHits_r->GetYaxis()->SetTitleOffset(0.8);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  // Efficiency is correlated. Can't use Sumw2. Need Binomial erroBrsl.
  NHits_r->Divide(NHits_r,NPhotons_r,1,1,"B");
  NHits_r->DrawCopy("E");
  NHits_r->DrawCopy("hist same");

  TCanvas *c6 = new TCanvas();
  MuonPos_z->SetLineWidth(2);
  MuonPos_z->Sumw2();
  MuonPos_z->Rebin(nrebin);
  MuonPos_z->DrawCopy("E");
  
  TCanvas *c7 = new TCanvas();
  MuonPos_r->SetLineWidth(2);
  MuonPos_r->Sumw2();
  MuonPos_r->Rebin(nrebin);
  MuonPos_r->DrawCopy("E");

  // Reconstruct Efficiency Histograms with new error values
  TH1D *NHits_z2 = (TH1D *)NHits_z->Clone("NHits_z2");
  
  for(int i=1; i<NHits_z2->GetNbinsX()+1; i++){
    float newerror = NHits_z->GetBinError(i) * NHits_z->GetBinError(i);
    if( MuonPos_z->GetBinContent(i) !=0){
      newerror+= ( MuonPos_z->GetBinError(i)/MuonPos_z->GetBinContent(i)
		   * MuonPos_z->GetBinError(i)/MuonPos_z->GetBinContent(i) );
    }
    NHits_z2->SetBinError(i, sqrt(newerror));
  }

  TH1D *NHits_r2 = (TH1D *)NHits_r->Clone("NHits_r2");
  
  for(int i=1; i<NHits_r2->GetNbinsX()+1; i++){
    float newerror = NHits_r->GetBinError(i) * NHits_r->GetBinError(i);
    if( MuonPos_r->GetBinContent(i) !=0){
      newerror+= ( MuonPos_r->GetBinError(i)/MuonPos_r->GetBinContent(i)
		   * MuonPos_r->GetBinError(i)/MuonPos_r->GetBinContent(i) );
    }
    NHits_r2->SetBinError(i, sqrt(newerror));
  }

  TCanvas *c8 = new TCanvas();
  NHits_z2->SetLineWidth(2);
  NHits_z2->DrawCopy("E");

  TCanvas *c9 = new TCanvas();
  NHits_r2->SetLineWidth(2);
  NHits_r2->DrawCopy("E");
}
   


