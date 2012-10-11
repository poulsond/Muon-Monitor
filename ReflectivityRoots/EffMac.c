{
//
  TFile *f = new TFile("Reflectivity9.root","READ");

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

  //TLegend *PhLeg = new TLegend(0.5,0.5,0.9,0.9);

  //PhLeg->AddEntry(NPhotonsHisto,"Variable NPhotons","l");
  //PhLeg->SetFillStyle(0);
  //PhLeg->SetBordersize(0);
  //PhLeg->Draw();

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

  //TLegend *leg = new TLegend(0.5,0.5,0.9,0.9);

  //leg->AddEntry(NHitsHisto,"Variable NHits","l");
  //leg->SetFillStyle(0);
  //leg->SetBorderSize(0);
  //leg->Draw();

  std::cout<<"The number of detected photons is: "<<NHitsHisto->
Integral()<<std::endl;

  // Efficiency Histogram  

  fTree->Draw("fNPhotons>>temp2(100,0,10000)","","goff");
  TH1D *NumPhotons = (TH1D *)gDirectory->Get("temp2");

  fTree->Draw("fNHits>>temp(100,0,10000)","","goff");
  TH1D *NumHits = (TH1D *)gDirectory->Get("temp");
  
  Int_t Total = 0;

  for(int i=0;i<fTree->GetEntries();i++){
    fTree->GetEntry(i);
        if(NHits!=0){
      Total++;
    }
  }

  Int_t DPhotons = NumHits->Divide(NumPhotons)->Integral();  
  std::cout<<"Total is: "<<Total<<std::endl;
  std::cout<<"DPhotons is: "<<DPhotons<<std::endl;
   
  std::cout<<"The mean efficiency is: "<<DPhotons/Total<<std::endl;
}
