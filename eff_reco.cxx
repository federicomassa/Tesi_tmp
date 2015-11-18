#include "TH1F.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TMath.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void eff(const char* filename = "./output/hist-sample1.root") {

  TFile* in = new TFile(filename, "UPDATE");

  double TargetEnergy;

  string TargetEnergy_str = "";
  string filename_str(filename);
  for (unsigned int i = filename_str.find("hist-")+5+2; i < filename_str.find(".root"); i++) {
    TargetEnergy_str += filename_str[i];
  }

  {
    stringstream ss;
    ss << TargetEnergy_str;
    ss >> TargetEnergy;
  }
 

  int pt_bin = 25;
  int ptGun_bin = 40;
  int eta_bin = 60;
  int phi_bin = 70;
  int abseta_bin = int(float(eta_bin)/2.0);

  int tot_truth = 0;
  int tot_tracks = 0;
  double tot_eff;

  //=======================
  // tk = track hist
  // tr = truth hist
  // eff_ = efficiency hist
  // fake_ = fake hist
  //=======================

  TH1F* tk_pt = (TH1F*) in->Get("TrackHist_TrackAll__pt");
  TH1F* tr_pt = (TH1F*) in->Get("TruthHist_TruthAll__pt");
  TH1F* eff_pt = new TH1F("eff_pt", "Track reco efficiency vs pt;pt [GeV];efficiency", pt_bin + 1, 0, 10); //+1 for overflow
  
  TH1F* tk_ptGun = (TH1F*) in->Get("TrackHist_reco_all__ptGun");
  TH1F* tr_ptGun = (TH1F*) in->Get("TruthHist_stable__ptGun");
  TH1F* eff_ptGun = new TH1F("eff_ptGun", "Track reco efficiency vs pt;pt [GeV];efficiency", ptGun_bin, TargetEnergy-10, TargetEnergy+10);
    
  TH1F* tk_eta = (TH1F*) in->Get("TrackHist_reco_all__abseta");
  TH1F* tr_eta = (TH1F*) in->Get("TruthHist_stable__abseta");
  TH1F* eff_eta = new TH1F("eff_eta", "Track reco efficiency vs eta;eta;efficiency", abseta_bin, 0.0, 3.0);

  TH1F* tk_absetaGun = (TH1F*) in->Get("TrackHist_reco_all__absetaGun");
  TH1F* tr_absetaGun = (TH1F*) in->Get("TruthHist_stable__absetaGun");
  TH1F* eff_absetaGun = new TH1F("eff_absetaGun", "Track reco efficiency vs |eta|_gun;|eta|;efficiency", abseta_bin, 0.0, 3.0);

  TH1F* tk_phi = (TH1F*) in->Get("TrackHist_reco_all__phi");
  TH1F* tr_phi = (TH1F*) in->Get("TruthHist_stable__phi");
  TH1F* eff_phi = new TH1F("eff_phi", "Track reco efficiency vs phi;phi;efficiency", phi_bin, -3.5, 3.5);

  /////////////
  TGraphErrors* fakeGun_average = new TGraphErrors(16);

  fakeGun_average -> SetName("fakeGun_average");
  fakeGun_average -> SetTitle("Fake probability;|#eta|;fake probability");
  
  std::vector<TH1F*> fakeGun_hists;
  for (int i = 0; i < 16; i++) {
    stringstream ss;
    TString i_str;
    ss << (i+1);
    ss >> i_str;
    fakeGun_hists.push_back((TH1F*) in->Get("TrackHist_reco_all__fakeGun_bin"+i_str));
  }

  ////////////////
  TGraphErrors* fake_average = new TGraphErrors(16);

  fake_average -> SetName("fake_average");
  fake_average -> SetTitle("Fake Tracks per event;|#eta|;#fake/ev");
  
  std::vector<TH1F*> fake_hists;
  for (int i = 0; i < 16; i++) {
    stringstream ss;
    TString i_str;
    ss << (i+1);
    ss >> i_str;
    fake_hists.push_back((TH1F*) in->Get("EventHist_all__nFake_bin"+i_str));
  }


  TGraphErrors* biasPt_Eta = new TGraphErrors(16);
  biasPt_Eta -> SetName("biasPt_Eta");
  biasPt_Eta -> SetTitle("#sigma(p_{T}) vs #eta;|#eta|;#sigma(p_{T}) [MeV]");

  TGraphErrors* biasD0_Eta = new TGraphErrors(16);
  biasD0_Eta -> SetName("biasD0_Eta");
  biasD0_Eta -> SetTitle("#sigma(D0) vs #eta;|#eta|;#sigma(D0) [mm]");

  TGraphErrors* biasZ0_Eta = new TGraphErrors(16);
  biasZ0_Eta -> SetName("biasZ0_Eta");
  biasZ0_Eta -> SetTitle("#sigma(Z0) vs #eta;|#eta|;#sigma(Z0) [mm]");

  TGraphErrors* biasQPt_Eta = new TGraphErrors(16);
  biasQPt_Eta -> SetName("biasQPt_Eta");
  biasQPt_Eta -> SetTitle("#p_{T} x sigma(q/Pt) vs |#eta|;|#eta|;#p_{T} x sigma(q/Pt)");

  TGraphErrors* biasPhi_Eta = new TGraphErrors(16);
  biasPhi_Eta -> SetName("biasPhi_Eta");
  biasPhi_Eta -> SetTitle("#sigma(Phi) vs #eta;|#eta|;#sigma(Phi)");

  //===================
  //Fill the histograms
  //===================
  
  for (int i = 0; i < pt_bin + 1; i++) { //+1 for overflow
    if (tr_pt->GetBinContent(i+1) != 0) {
      eff_pt->SetBinContent(i+1, float(tk_pt->GetBinContent(i+1))/float(tr_pt->GetBinContent(i+1)));
      eff_pt->SetBinError(i+1, TMath::Sqrt(eff_pt->GetBinContent(i+1)*(1-eff_pt->GetBinContent(i+1))/float(tr_pt->GetBinContent(i+1))));
      tot_truth += tr_pt->GetBinContent(i+1);
      tot_tracks += tk_pt->GetBinContent(i+1);
    }
    else 
      eff_pt->SetBinContent(i+1, 0);
  }

  for (int i = 0; i < ptGun_bin; i++) {
    if (tr_ptGun->GetBinContent(i+1) != 0) {
      eff_ptGun->SetBinContent(i+1, float(tk_ptGun->GetBinContent(i+1))/float(tr_ptGun->GetBinContent(i+1)));
      eff_ptGun->SetBinError(i+1, TMath::Sqrt(eff_ptGun->GetBinContent(i+1)*(1-eff_ptGun->GetBinContent(i+1))/float(tr_ptGun->GetBinContent(i+1))));
    }
    else 
      eff_ptGun->SetBinContent(i+1, 0);
  }


  for (int i = 0; i < eta_bin; i++) {
    if (tr_eta->GetBinContent(i+1) != 0) {
      eff_eta->SetBinContent(i+1, float(tk_eta->GetBinContent(i+1))/float(tr_eta->GetBinContent(i+1)));
      eff_eta->SetBinError(i+1, TMath::Sqrt(eff_eta->GetBinContent(i+1)*(1-eff_eta->GetBinContent(i+1))/float(tr_eta->GetBinContent(i+1))));
    }
    else 
      eff_eta->SetBinContent(i+1, 0);
  }



  for (int i = 0; i < abseta_bin; i++) {
    if (tr_absetaGun->GetBinContent(i+1) != 0) {
      eff_absetaGun->SetBinContent(i+1, float(tk_absetaGun->GetBinContent(i+1))/float(tr_absetaGun->GetBinContent(i+1)));
      eff_absetaGun->SetBinError(i+1, TMath::Sqrt(eff_absetaGun->GetBinContent(i+1)*(1-eff_absetaGun->GetBinContent(i+1))/float(tr_absetaGun->GetBinContent(i+1))));
    }
    else 
      eff_absetaGun->SetBinContent(i+1, 0);
  }



  for (int i = 0; i < phi_bin; i++) {
    if (tr_phi->GetBinContent(i+1) != 0) {
      eff_phi->SetBinContent(i+1, float(tk_phi->GetBinContent(i+1))/float(tr_phi->GetBinContent(i+1)));
      eff_phi->SetBinError(i+1, TMath::Sqrt(eff_phi->GetBinContent(i+1)*(1-eff_phi->GetBinContent(i+1))/float(tr_phi->GetBinContent(i+1))));
    }
    else 
      eff_phi->SetBinContent(i+1, 0);
  }

  // fake_average -> SetPoint(0, 0.1, fake_01->GetMean());  
  // fake_average -> SetPointError(0,0.0,fake_01->GetMeanError());
  // fake_average -> SetPoint(1, 0.2, fake_02->GetMean());
  // fake_average -> SetPointError(1,0.0,fake_02->GetMeanError());
  // fake_average -> SetPoint(2, 0.3, fake_03->GetMean());
  // fake_average -> SetPointError(2,0.0,fake_03->GetMeanError());
  // fake_average -> SetPoint(3, 0.4, fake_04->GetMean());
  // fake_average -> SetPointError(3,0.0,fake_04->GetMeanError());
  // fake_average -> SetPoint(4, 0.5, fake_05->GetMean());
  // fake_average -> SetPointError(4,0.0,fake_05->GetMeanError());
  // fake_average -> SetPoint(5, 0.6, fake_06->GetMean());
  // fake_average -> SetPointError(5,0.0,fake_06->GetMeanError());
  // fake_average -> SetPoint(6, 0.7, fake_07->GetMean());
  // fake_average -> SetPointError(6,0.0,fake_07->GetMeanError());
  // fake_average -> SetPoint(7, 0.8, fake_08->GetMean());
  // fake_average -> SetPointError(7,0.0,fake_08->GetMeanError());
  // fake_average -> SetPoint(8, 0.9, fake_09->GetMean());
  // fake_average -> SetPointError(8,0.0,fake_09->GetMeanError());

  for (int i = 0; i < 16; i++) {
    stringstream ss;
    TString i_str;
    ss << i;
    ss >> i_str;
   
    fakeGun_average -> SetPoint(i,3.2/16*float(i)+3.2/16/2, fakeGun_hists.at(i)->GetMean());
    fakeGun_average -> SetPointError(i, 3.2/16/2, fakeGun_hists.at(i)->GetMeanError()); 

    fake_average -> SetPoint(i,3.2/16*float(i)+3.2/16/2, fake_hists.at(i)->GetMean());
    fake_average -> SetPointError(i, 3.2/16/2, fake_hists.at(i)->GetMeanError()); 
  }

  // bias Pt
  // CHANGED FROM eff.cxx: use truthMatch: trackHist_reco
  string biasPt_str = "TrackHist_reco_all__biasPt_bin";
  string biasD0_str = "TrackHist_reco_all__biasD0_bin";
  string biasZ0_str = "TrackHist_reco_all__biasZ0_bin";
  string biasQPt_str = "TrackHist_reco_all__biasQPt_bin";
  string biasPhi_str = "TrackHist_reco_all__biasPhi_bin";
  
  for (int i = 1; i <= 16; i++) {

    stringstream ss;
    string bin_str = "";
    ss << i;
    ss >> bin_str;

    string biasPtBin_str = biasPt_str + bin_str;
    string biasD0Bin_str = biasD0_str + bin_str;
    string biasZ0Bin_str = biasZ0_str + bin_str;
    string biasQPtBin_str = biasQPt_str + bin_str;
    string biasPhiBin_str = biasPhi_str + bin_str;

    Double_t RMSVal = ((TH1F*) in->Get(biasPtBin_str.c_str()))->GetRMS();
    Double_t RMSErrorVal = ((TH1F*) in->Get(biasPtBin_str.c_str()))->GetRMSError();
    biasPt_Eta -> SetPoint(i-1,0.1 + 0.2*float(i-1),RMSVal);
    biasPt_Eta -> SetPointError(i-1,0.0, RMSErrorVal);

    RMSVal = ((TH1F*) in->Get(biasD0Bin_str.c_str()))->GetRMS();
    RMSErrorVal = ((TH1F*) in->Get(biasD0Bin_str.c_str()))->GetRMSError();
    biasD0_Eta -> SetPoint(i-1,0.1 + 0.2*float(i-1),RMSVal);
    biasD0_Eta -> SetPointError(i-1,0.0, RMSErrorVal);

    RMSVal = ((TH1F*) in->Get(biasZ0Bin_str.c_str()))->GetRMS();
    RMSErrorVal = ((TH1F*) in->Get(biasZ0Bin_str.c_str()))->GetRMSError();
    biasZ0_Eta -> SetPoint(i-1,0.1 + 0.2*float(i-1),RMSVal);
    biasZ0_Eta -> SetPointError(i-1,0.0, RMSErrorVal);

    RMSVal = ((TH1F*) in->Get(biasQPtBin_str.c_str()))->GetRMS();
    RMSErrorVal = ((TH1F*) in->Get(biasQPtBin_str.c_str()))->GetRMSError();
    biasQPt_Eta -> SetPoint(i-1,0.1 + 0.2*float(i-1),RMSVal);
    biasQPt_Eta -> SetPointError(i-1,0.0, RMSErrorVal);

    RMSVal = ((TH1F*) in->Get(biasPhiBin_str.c_str()))->GetRMS();
    RMSErrorVal = ((TH1F*) in->Get(biasPhiBin_str.c_str()))->GetRMSError();
    biasPhi_Eta -> SetPoint(i-1,0.1 + 0.2*float(i-1),RMSVal);
    biasPhi_Eta -> SetPointError(i-1,0.0, RMSErrorVal);

  }


  //Print on stdout total efficiency

  tot_eff = float(tot_tracks)/float(tot_truth);

  std::cout << "Average efficiency: " << 
    tot_eff << 
    " +/- " <<
    TMath::Sqrt(tot_eff*(1-tot_eff)/float(tot_truth)) <<
    std::endl;

  //Finalize

  eff_pt        ->   Write();
  eff_ptGun     ->   Write();
  eff_eta       ->   Write();
  eff_absetaGun ->   Write();
  eff_phi       ->   Write();
  fakeGun_average->   Write();
  fake_average  ->   Write();
  biasPt_Eta    ->   Write();
  biasD0_Eta    ->   Write();
  biasZ0_Eta    ->   Write();
  biasQPt_Eta   ->   Write();
  biasPhi_Eta   ->   Write();

  delete tk_pt;
  delete tr_pt;
  delete eff_pt;
  
  delete tk_ptGun;
  delete tr_ptGun;
  delete eff_ptGun;


  delete tk_eta;
  delete tr_eta;
  delete eff_eta;

  delete tk_absetaGun;
  delete tr_absetaGun;
  delete eff_absetaGun;


  delete tk_phi;
  delete tr_phi;
  delete eff_phi;

  delete fakeGun_average;
  delete fake_average;
  delete biasPt_Eta;
  delete biasD0_Eta;

  in            ->   Close();
}
