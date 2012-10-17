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
{
  Tfile *f = new Tfile("WCRef9100000Events.root","READ");
  TTree *fTree = (TTree *)f->Get("fTree");

  Int_t NHits;
  Int_t NPhotons;
  Int_t PlaneX;
  Int_t PlaneY;
  Int_t PlaneZ;
  Int_t PrimePosX_cm;
  Int_t PrimePosY_cm;
  Int_t PrimePosZ_cm; 

  fTree->SetBranchAddress("fNHits",&NHits);
  fTree->SetBranchAddress("fNPhotons",&NPhotons);
  fTree->SetBranchAddress("fPlaneX",&PlaneX);
  fTree->SetBranchAddress("fPlaneY",&PlaneY);
  fTree->SetBranchAddress("fPlaneZ",&PlaneZ);
  fTree->SetBranchAddress("fPrimePosX_cm",&PrimePosX_cm);
  fTree->SetBranchAddress("fPrimePosY_cm",&PrimePosY_cm);
  fTree->SetBranchAddress("fPrimePosZ_cm",&PrimePosZ_cm);

  // Number of Hits Histogram
  TH1D *HitsHist = new TH1D
    ("Hits Histogram","Hits Histogram",100,0,10000);

  for(int i=0; i<fTree->GetEntries(); i++){
    fTree->GetEntry(i);
    
    HitsHisto->Fill(NHits);
  }

  // Number of Hits with Zcuts
  TH1D *ZHitsHist = new TH1D
    ("Z Hits", "Z Hits", 100,0,10000);

   


