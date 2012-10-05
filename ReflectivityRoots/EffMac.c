{
//
  TFile *f = new TFile("WaterCherenkovReflectivity1.root","READ");

  TTree *fTree = (TTree *)f->Get("fTree");

// Total # of Photons Created Histogram

  TH1D *NPhotonsHisto = new TH1D
("NPhotonsHisto","NPhotonsHisto",100,0,10000);

  Int_t NPhotons;

  fTree->SetBranchAddress("fNPhotons",&NPhotons);

  for(int i=0;i<fTree->GetEntries();i++){
	fTree->GetEntry(i);

	if(NPhotons!=0)NPhotonsHisto->Fill(NPhotons);
  }

  new TCanvas();
  NPhotonsHisto->Draw("hist");

  TLegend *PhLeg = new TLegend(0.5,0.5,0.9,0.9);

  PhLeg->AddEntry(NPhotonsHisto,"Variable NPhotons","l");
//  PhLeg->SetFillStyle(0);
//  PhLeg->SetBordersize(0);
  PhLeg->Draw();

  std::cout<<"The number of photons created is:  "<<NPhotonsHisto->Integral()<<std::endl;

// Number of Photons Detected Histogram

  TH1D *NHitsHisto = new TH1D
("NHitsHisto","NHitsHisto",100,0,10000);

  Int_t NHits;

  fTree->SetBranchAddress("fNHits",&NHits);

  for(int i=0;i<fTree->GetEntries();i++){
	fTree->GetEntry(i);

	if(NHits!=0)NHitsHisto->Fill(NHits);
  } 

  new TCanvas();
  NHitsHisto->Draw("hist");

  TLegend *leg = new TLegend(0.5,0.5,0.9,0.9);

  leg->AddEntry(NHitsHisto,"Variable NHits","l");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->Draw();

  std::cout<<"The number of detected photons is: "<<NHitsHisto->
Integral()<<std::endl;

  Int_t DPhotons = NHitsHisto->Integral();
  Int_t CPhotons = NPhotonsHisto->Integral();
 
  std::cout<<"The overall efficiency is: "<<DPhotons/CPhotons<<std::endl;
}
