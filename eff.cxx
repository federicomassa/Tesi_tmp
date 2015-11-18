#include "TH1F.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TMath.h"
#include <iostream>
#include <string>
#include <sstream>

void eff(const char* filename = "./output/hist-sample1.root") {

  TFile* in = new TFile(filename, "UPDATE");

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
  

  TH1F* tk_ptGun = (TH1F*) in->Get("TrackHist_TrackAll__ptGun");
  TH1F* tr_ptGun = (TH1F*) in->Get("TruthHist_TruthAll__ptGun");
  TH1F* eff_ptGun = new TH1F("eff_ptGun", "Track reco efficiency vs pt;pt [GeV];efficiency", ptGun_bin, 40, 60);


  TH1F* tk_eta = (TH1F*) in->Get("TrackHist_TrackAll__eta");
  TH1F* tr_eta = (TH1F*) in->Get("TruthHist_TruthAll__eta");
  TH1F* eff_eta = new TH1F("eff_eta", "Track reco efficiency vs eta;eta;efficiency", eta_bin, -3, 3);



  TH1F* tk_absetaGun = (TH1F*) in->Get("TrackHist_TrackAll__absetaGun");
  TH1F* tr_absetaGun = (TH1F*) in->Get("TruthHist_TruthAll__absetaGun");
  TH1F* eff_absetaGun = new TH1F("eff_absetaGun", "Track reco efficiency vs |eta|_gun;|eta|;efficiency", abseta_bin, 0.0, 3.0);



  TH1F* tk_phi = (TH1F*) in->Get("TrackHist_TrackAll__phi");
  TH1F* tr_phi = (TH1F*) in->Get("TruthHist_TruthAll__phi");
  TH1F* eff_phi = new TH1F("eff_phi", "Track reco efficiency vs phi;phi;efficiency", phi_bin, -3.5, 3.5);

  TGraphErrors* fake_average = new TGraphErrors(9);
  fake_average -> SetName("fake_average");
  fake_average -> SetTitle("Fake Tracks per event;truthMatchProb;#fake/ev");
  TH1F* fake_01 = (TH1F*) in->Get("EventHist_all__nFake01"); 
  TH1F* fake_02 = (TH1F*) in->Get("EventHist_all__nFake02");
  TH1F* fake_03 = (TH1F*) in->Get("EventHist_all__nFake03");
  TH1F* fake_04 = (TH1F*) in->Get("EventHist_all__nFake04");
  TH1F* fake_05 = (TH1F*) in->Get("EventHist_all__nFake05");
  TH1F* fake_06 = (TH1F*) in->Get("EventHist_all__nFake06");
  TH1F* fake_07 = (TH1F*) in->Get("EventHist_all__nFake07");
  TH1F* fake_08 = (TH1F*) in->Get("EventHist_all__nFake08");
  TH1F* fake_09 = (TH1F*) in->Get("EventHist_all__nFake09");

  TGraphErrors* biasPt_Eta = new TGraphErrors(16);
  biasPt_Eta -> SetName("biasPt_Eta");
  biasPt_Eta -> SetTitle("#sigma(p_{T}) vs #eta;|#eta|;#sigma(p_{T})");

  TGraphErrors* biasD0_Eta = new TGraphErrors(16);
  biasD0_Eta -> SetName("biasD0_Eta");
  biasD0_Eta -> SetTitle("#sigma(D0) vs #eta;|#eta|;#sigma(D0)");

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

  fake_average -> SetPoint(0, 0.1, fake_01->GetMean());  
  fake_average -> SetPointError(0,0.0,fake_01->GetMeanError());
  fake_average -> SetPoint(1, 0.2, fake_02->GetMean());
  fake_average -> SetPointError(1,0.0,fake_02->GetMeanError());
  fake_average -> SetPoint(2, 0.3, fake_03->GetMean());
  fake_average -> SetPointError(2,0.0,fake_03->GetMeanError());
  fake_average -> SetPoint(3, 0.4, fake_04->GetMean());
  fake_average -> SetPointError(3,0.0,fake_04->GetMeanError());
  fake_average -> SetPoint(4, 0.5, fake_05->GetMean());
  fake_average -> SetPointError(4,0.0,fake_05->GetMeanError());
  fake_average -> SetPoint(5, 0.6, fake_06->GetMean());
  fake_average -> SetPointError(5,0.0,fake_06->GetMeanError());
  fake_average -> SetPoint(6, 0.7, fake_07->GetMean());
  fake_average -> SetPointError(6,0.0,fake_07->GetMeanError());
  fake_average -> SetPoint(7, 0.8, fake_08->GetMean());
  fake_average -> SetPointError(7,0.0,fake_08->GetMeanError());
  fake_average -> SetPoint(8, 0.9, fake_09->GetMean());
  fake_average -> SetPointError(8,0.0,fake_09->GetMeanError());

  // bias Pt

  string biasPt_str = "TrackHist_TrackAll__biasPt_bin";
  string biasD0_str = "TrackHist_TrackAll__biasD0_bin";
  
  for (int i = 1; i <= 16; i++) {

    stringstream ss;
    string bin_str = "";
    ss << i;
    ss >> bin_str;
    ss.clear();

    string biasPtBin_str = biasPt_str + bin_str;
    string biasD0Bin_str = biasD0_str + bin_str;

    Double_t RMSVal = ((TH1F*) in->Get(biasPtBin_str.c_str()))->GetRMS();
    Double_t RMSErrorVal = ((TH1F*) in->Get(biasPtBin_str.c_str()))->GetRMSError();
    biasPt_Eta -> SetPoint(i-1,0.1 + 0.2*float(i-1),RMSVal);
    biasPt_Eta -> SetPointError(i-1,0.0, RMSErrorVal);

    RMSVal = ((TH1F*) in->Get(biasD0Bin_str.c_str()))->GetRMS();
    RMSErrorVal = ((TH1F*) in->Get(biasD0Bin_str.c_str()))->GetRMSError();
    biasD0_Eta -> SetPoint(i-1,0.1 + 0.2*float(i-1),RMSVal);
    biasD0_Eta -> SetPointError(i-1,0.0, RMSErrorVal);
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
  fake_average  ->   Write();
  biasPt_Eta    ->   Write();
  biasD0_Eta    ->   Write();

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

  delete fake_average;
  delete biasPt_Eta;
  delete biasD0_Eta;

  in            ->   Close();
}
