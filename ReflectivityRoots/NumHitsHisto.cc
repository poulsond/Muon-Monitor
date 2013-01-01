{

  TFile *f = new TFile("Ref9HThousandEvents.root","READ");

  TTree *fTree = (TTree *)f->Get("fTree");

  //Int_t nrebin = 10;

  Int_t NHits;
  Int_t NPhotons;
  
  fTree->SetBranchAddress("fNHits",&NHits);
  fTree->SetBranchAddress("fNPhotons",&NPhotons);

  TH1D *Hits[10];

  char histname[200];

  for(int i=0; i<fTree->GetEntries(); i++){

    fTree->GetEntry(i);

    if(NPhotons >0 && NPhotons <500){
      Hits[0] = new TH1D(histname,histname, 33,0,5000);
      Hits[0]->Fill(NHits);
    
    } else if(NPhotons >=500 && NPhotons <1500){
      Hits[1] = new TH1D(histname,histname, 33,0,5000);
      Hits[1]->Fill(NHits);

    } else if(NPhotons >=1500 && NPhotons <2500){
      Hits[2] = new TH1D(histname,histname, 33,0,5000);
      Hits[2]->Fill(NHits);

    } else if(NPhotons >=2500 && NPhotons <3500){
      Hits[3] = new TH1D(histname,histname, 33,0,5000);
      Hits[3]->Fill(NHits);

    } else if(NPhotons >=3500 && NPhotons <4500){
      Hits[4] = new TH1D(histname,histname, 33,0,5000);
      Hits[4]->Fill(NHits);

    } else if(NPhotons >=4500 && NPhotons <5500){
      Hits[5] = new TH1D(histname,histname, 33,0,5000);
      Hits[5]->Fill(NHits);

    } else if(NPhotons >=5500 && NPhotons <6500){
      Hits[6] = new TH1D(histname,histname, 33,0,5000);
      Hits[6]->Fill(NHits);

    } else if(NPhotons >=6500 && NPhotons <7500){
      Hits[7] = new TH1D(histname,histname, 33,0,5000);
      Hits[7]->Fill(NHits);

    } else if(NPhotons >=7500 && NPhotons <8500){
      Hits[8] = new TH1D(histname,histname, 33,0,5000);
      Hits[8]->Fill(NHits);

    } else if(NPhotons >=8500 && NPhotons <10000){
      Hits[9] = new TH1D(histname,histname, 33,0,5000);
      Hits[9]->Fill(NHits);

    }
    
  }

  for(int j=0; j<10; j++){
    
    sprintf(histname, "Hits_%j",j);
    
    Hits[j]->SetLineWidth(2);
    Hits[j]->SetLineWidth(j+1);
    
    if (j==0) Hits[j]->Draw("hist");
    else Hits[j]->Draw("hist same");
  }
}

    
