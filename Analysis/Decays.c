{
  TFile *f = new TFile("10000Mu+.root","READ");

  TTree *fTree = (TTree *)f->Get("fTree");

  //Rebin Number if needed
  Int_t nrebin = 10;
  //Inner and outer radii
  Int_t rinner = 9.91;
  Int_t router = 25.4;
  //Number of hits and created photons
  Int_t NHits; 
  Int_t NPhotons;
  //Photon Wavelengths
  Double_t Wavelength_nm[10000];
  //X, Y, and time coordinates of photon hit
  Double_t PlaneX_cm[10000];
  Double_t PlaneY_cm[10000];
  Double_t PlaneT_ns[10000];
  //X, Y, and Z coordinates of mu initial position
  Double_t PrimePosX_cm;
  Double_t PrimePosY_cm;
  Double_t PrimePosZ_cm;
  //X, Y, and Z coordinates of photon initial position
  Double_t GPrimePosX_cm[10000];
  Double_t GPrimePosY_cm[10000];
  Double_t GPrimePosZ_cm[10000];

  fTree->SetBranchAddress("fNHits",&NHits);
  fTree->SetBranchAddress("fNPhotons",&NPhotons);
  fTree->SetBranchAddress("fPlaneX_cm",PlaneX_cm);
  fTree->SetBranchAddress("fPlaneY_cm",PlaneY_cm);
  fTree->SetBranchAddress("fPlaneT_ns",PlaneT_ns);
  fTree->SetBranchAddress("fPrimePosX_cm",&PrimePosX_cm);
  fTree->SetBranchAddress("fPrimePosY_cm",&PrimePosY_cm);
  fTree->SetBranchAddress("fPrimePosZ_cm",&PrimePosZ_cm);
  fTree->SetBranchAddress("lPrimePosX",GPrimePosX_cm);
  fTree->SetBranchAddress("lPrimePosY",GPrimePosY_cm);
  fTree->SetBranchAddress("lPrimePosZ",GPrimePosZ_cm);
  fTree->SetBranchAddress("fWavelength_nm",Wavelength_nm);

  // Time Histo
  TH1D *TimeHistoInner = new TH1D
    ("TInside Histo", "TInside Histo", 100,0,20000);

  TH1D *TimeHistoOuter = new TH1D
    ("TOutside Histo", "TOutside Histo", 100,0,20000);
  // Mu- position histos
  TH1D *NHitsInner_r = new TH1D
    ("HInside_r Histo", "HInside_r Histo", 100,0,rinner);

  TH1D *NHitsOuter_r = new TH1D
    ("HOutside_r Histo", "HOutside_r Histo", 100,rinner,router);

  TH1D *NHitsInner_z = new TH1D
    ("HInside_z Histo", "HInside_z Histo", 100,-26,26);

  TH1D *NHitsOuter_z = new TH1D
    ("HOutside_z Histo", "HOutside_z Histo", 100,-26,26);
  //Gamma position histos
  /*  TH1D *NHitsInnerG_r = new TH1D
      ("HInsideG_r Histo", "HInsideG_r Histo", 100,0,1000);
      
      TH1D *NHitsOuterG_r = new TH1D
      ("HOutsideG_r Histo", "HOutsideG_r Histo", 100,0,1000);
      
      TH1D *NHitsInnerG_z = new TH1D
      ("HInsideG_z Histo", "HInsideG_z Histo", 100,0,1000);
      
      TH1D *NHitsOuterG_z = new TH1D
      ("HOutsideG_z Histo", "HOutsideG_z Histo", 100,0,1000);
  */

  for(int i=0; i<fTree->GetEntries(); i++){

    fTree->GetEntry(i);

    double r = sqrt(PrimePosX_cm*PrimePosX_cm+PrimePosY_cm*PrimePosY_cm);
    
    if(r<rinner){
      // Hits as a function of mu- position
      NHitsInner_r->Fill(r, NHits);
      NHitsInner_z->Fill(PrimePosZ_cm, NHits);

      for(int j=0; j<NPhotons; j++){
	//Hits as a function of gamma position
	//double R = sqrt(GPrimePosX_cm[j]*GPrimePosX_cm[j]+GPrimePosY_cm[j]*GPrimePosY_cm[j]);
	//NHitsInnerG_r->Fill(R, NHits);
	//NHitsInnerG_z->Fill(GPrimePosZ_cm[j], NHits);
     	//Time Histo
	if(PlaneT_ns[j] != 0) {
	  TimeHistoInner->Fill(PlaneT_ns[j]);
	}
      }
    } else {
      //Hits as a function of mu- position
      NHitsOuter_r->Fill(r, NHits);
      NHitsOuter_z->Fill(PrimePosZ_cm, NHits);
      for(int j=0; j<NPhotons; j++){
	//Hits as a function of gamma position
	//double R = sqrt(GPrimePosX_cm[j]*GPrimePosX_cm[j]+GPrimePosY_cm[j]*GPrimePosY_cm[j]);
	//NHitsOuterG_r->Fill(R, NHits);
	//NHitsOuterG_z->Fill(GPrimePosZ_cm[j], NHits);
	//Time Histo
	if(PlaneT_ns[j] != 0) {
	TimeHistoOuter->Fill(PlaneT_ns[j]);
	}
      }
    }


  }

  TCanvas *c1 = new TCanvas();
  TimeHistoInner->GetXaxis()->SetTitle("Michel Decays");
  TimeHistoInner->GetYaxis()->SetTitle("");
  TimeHistoInner->GetXaxis()->CenterTitle();
  TimeHistoInner->GetYaxis()->CenterTitle();
  TimeHistoInner->SetTitle("");
  TimeHistoInner->GetYaxis()->SetTitleOffset(0.8);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  TimeHistoInner->Draw("hist");

 TCanvas *c2 = new TCanvas();
  TimeHistoOuter->GetXaxis()->SetTitle("Boron Decays");
  TimeHistoOuter->GetYaxis()->SetTitle("");
  TimeHistoOuter->GetXaxis()->CenterTitle();
  TimeHistoOuter->GetYaxis()->CenterTitle();
  TimeHistoOuter->SetTitle("");
  TimeHistoOuter->GetYaxis()->SetTitleOffset(0.8);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  TimeHistoOuter->Draw("hist");

 TCanvas *c3 = new TCanvas();
  NHitsInner_r->GetXaxis()->SetTitle("Inner Radius");
  NHitsInner_r->GetYaxis()->SetTitle("Detections");
  NHitsInner_r->GetXaxis()->CenterTitle();
  NHitsInner_r->GetYaxis()->CenterTitle();
  NHitsInner_r->SetTitle("");
  NHitsInner_r->GetYaxis()->SetTitleOffset(0.8);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  NHitsInner_r->Draw("hist");

 TCanvas *c4 = new TCanvas();
  NHitsInner_z->GetXaxis()->SetTitle("Inner Z Position");
  NHitsInner_z->GetYaxis()->SetTitle("Detections");
  NHitsInner_z->GetXaxis()->CenterTitle();
  NHitsInner_z->GetYaxis()->CenterTitle();
  NHitsInner_z->SetTitle("");
  NHitsInner_z->GetYaxis()->SetTitleOffset(0.8);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  NHitsInner_z->Draw("hist");

 TCanvas *c5 = new TCanvas();
  NHitsOuter_r->GetXaxis()->SetTitle("Outer Radius");
  NHitsOuter_r->GetYaxis()->SetTitle("Detections");
  NHitsOuter_r->GetXaxis()->CenterTitle();
  NHitsOuter_r->GetYaxis()->CenterTitle();
  NHitsOuter_r->SetTitle("");
  NHitsOuter_r->GetYaxis()->SetTitleOffset(0.8);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  NHitsOuter_r->Draw("hist");

 TCanvas *c6 = new TCanvas();
  NHitsOuter_z->GetXaxis()->SetTitle("Outer Z Position");
  NHitsOuter_z->GetYaxis()->SetTitle("Detections");
  NHitsOuter_z->GetXaxis()->CenterTitle();
  NHitsOuter_z->GetYaxis()->CenterTitle();
  NHitsOuter_z->SetTitle("");
  NHitsOuter_z->GetYaxis()->SetTitleOffset(0.8);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleOffset(0.8,"");
  NHitsOuter_z->Draw("hist");
}

