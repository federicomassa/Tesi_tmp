#include "TFile.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TString.h"
#include <string>
#include <iostream>

void eff_all(const string sample, const bool SaveEfficiencyPlots = false, const bool SaveBiasPlots = false, const bool SaveFakePlots = false, const bool SaveHitsPlots = false) {
  
  string sample_radix = "./" + sample + "/hist-" + sample + "pu"; // example: sample = pi50 --> sample_radix = ./pi50/hist-pi50pu

  TFile* in50 = new TFile((sample_radix + "50.root").c_str());
  TFile* in100 = new TFile((sample_radix + "100.root").c_str());
  TFile* in140 = new TFile((sample_radix + "140.root").c_str());
  TFile* in200 = new TFile((sample_radix + "200.root").c_str());
  TFile* in300 = new TFile((sample_radix + "300.root").c_str());

  TGraphErrors* biasPt50 = (TGraphErrors*) in50->Get("biasPt_Eta");
  TGraphErrors* biasPt100 = (TGraphErrors*) in100->Get("biasPt_Eta");
  TGraphErrors* biasPt140 = (TGraphErrors*) in140->Get("biasPt_Eta");
  TGraphErrors* biasPt200 = (TGraphErrors*) in200->Get("biasPt_Eta");
  TGraphErrors* biasPt300 = (TGraphErrors*) in300->Get("biasPt_Eta");

  TMultiGraph* mg = new TMultiGraph();

  /// CHECK IF TARGET WAS MATCHED CORRECTLY ///
  TH1F* hist_check50 = dynamic_cast<TH1F*>(in50->Get("TrackHist_reco_all__pt"));
  if (hist_check50->GetEntries() == 0) std::cout << "WARNING: " + sample + "pu50 was not correctly target matched" << std::endl;
 
  TH1F* hist_check100 = dynamic_cast<TH1F*>(in100->Get("TrackHist_reco_all__pt"));
  if (hist_check100->GetEntries() == 0) std::cout << "WARNING: " + sample + "pu100 was not correctly target matched" << std::endl;

  TH1F* hist_check140 = dynamic_cast<TH1F*>(in140->Get("TrackHist_reco_all__pt"));
  if (hist_check140->GetEntries() == 0) std::cout << "WARNING: " + sample + "pu140 was not correctly target matched" << std::endl;

  TH1F* hist_check200 = dynamic_cast<TH1F*>(in200->Get("TrackHist_reco_all__pt"));
  if (hist_check200->GetEntries() == 0) std::cout << "WARNING: " + sample + "pu200 was not correctly target matched" << std::endl;

  TH1F* hist_check300 = dynamic_cast<TH1F*>(in300->Get("TrackHist_reco_all__pt"));
  if (hist_check300->GetEntries() == 0) std::cout << "WARNING: " + sample + "pu300 was not correctly target matched" << std::endl;

  delete hist_check50;
  delete hist_check100;
  delete hist_check140;
  delete hist_check200;
  delete hist_check300;

  //////////////

  biasPt50->SetLineColor(kCyan);
  biasPt100->SetLineColor(kBlue);
  biasPt140->SetLineColor(kGreen);
  biasPt200->SetLineColor(kPink-8);
  biasPt300->SetLineColor(kRed);

  mg->Add(biasPt50);
  mg->Add(biasPt100);
  mg->Add(biasPt140);
  mg->Add(biasPt200);
  mg->Add(biasPt300);

  mg->SetTitle("#sigma(p_{T}) vs |#eta|; |#eta|; #sigma(p_{T}) [MeV]");

  TCanvas* canv_pt = new TCanvas();
  mg->Draw("APE");
  mg->GetYaxis()->SetTitleOffset(1.2);
  // mg->GetYaxis()->SetRangeUser(0.0,4500.0);

  TLegend* leg = new TLegend(0.15,0.85,0.4,0.6);
  leg->SetFillColor(0);
  leg->AddEntry(biasPt50, "PU 50", "lp");
  leg->AddEntry(biasPt100, "PU 100", "lp");
  leg->AddEntry(biasPt140, "PU 140", "lp");
  leg->AddEntry(biasPt200, "PU 200", "lp");
  leg->AddEntry(biasPt300, "PU 300", "lp");
  
  leg->Draw();

  if (SaveBiasPlots) {
    canv_pt->Print(("Immagini/" + sample + "_biasPtVsEta.png").c_str(),"png");
      delete canv_pt;
 }

  ////////////////////////////////

  TGraphErrors* biasD050 = (TGraphErrors*) in50->Get("biasD0_Eta");
  TGraphErrors* biasD0100 = (TGraphErrors*) in100->Get("biasD0_Eta");
  TGraphErrors* biasD0140 = (TGraphErrors*) in140->Get("biasD0_Eta");
  TGraphErrors* biasD0200 = (TGraphErrors*) in200->Get("biasD0_Eta");
  TGraphErrors* biasD0300 = (TGraphErrors*) in300->Get("biasD0_Eta");

  TMultiGraph* mg2 = new TMultiGraph();

  biasD050->SetLineColor(kCyan);
  biasD0100->SetLineColor(kBlue);
  biasD0140->SetLineColor(kGreen);
  biasD0200->SetLineColor(kPink-8);
  biasD0300->SetLineColor(kRed);

  mg2->Add(biasD050);
  mg2->Add(biasD0100);
  mg2->Add(biasD0140);
  mg2->Add(biasD0200);
  mg2->Add(biasD0300);

  mg2->SetTitle("#sigma(D0) vs |#eta|; |#eta|; #sigma(D0) [mm]");

  TCanvas* canv_d0 = new TCanvas();
  mg2->Draw("APE");
  mg2->GetYaxis()->SetTitleOffset(1.2);
  // mg2->GetYaxis()->SetRangeUser(0.0,0.05);

  TLegend* leg2 = new TLegend(0.15,0.85,0.4,0.6);
  leg2->SetFillColor(0);
  leg2->AddEntry(biasD050, "PU 50", "lp");
  leg2->AddEntry(biasD0100, "PU 100", "lp");
  leg2->AddEntry(biasD0140, "PU 140", "lp");
  leg2->AddEntry(biasD0200, "PU 200", "lp");
  leg2->AddEntry(biasD0300, "PU 300", "lp");
  
  leg2->Draw();

  if (SaveBiasPlots) {
    canv_d0->Print(("Immagini/" + sample + "_biasD0VsEta.png").c_str(),"png");
      delete canv_d0;

  }


////////////////////////////////

  TGraphErrors* biasZ050 = (TGraphErrors*) in50->Get("biasZ0_Eta");
  TGraphErrors* biasZ0100 = (TGraphErrors*) in100->Get("biasZ0_Eta");
  TGraphErrors* biasZ0140 = (TGraphErrors*) in140->Get("biasZ0_Eta");
  TGraphErrors* biasZ0200 = (TGraphErrors*) in200->Get("biasZ0_Eta");
  TGraphErrors* biasZ0300 = (TGraphErrors*) in300->Get("biasZ0_Eta");

  TMultiGraph* mg3 = new TMultiGraph();

  biasZ050->SetLineColor(kCyan);
  biasZ0100->SetLineColor(kBlue);
  biasZ0140->SetLineColor(kGreen);
  biasZ0200->SetLineColor(kPink-8);
  biasZ0300->SetLineColor(kRed);

  mg3->Add(biasZ050);
  mg3->Add(biasZ0100);
  mg3->Add(biasZ0140);
  mg3->Add(biasZ0200);
  mg3->Add(biasZ0300);

  mg3->SetTitle("#sigma(Z0) vs |#eta|; |#eta|; #sigma(Z0) [mm]");

  TCanvas* canv_z0 = new TCanvas();
  mg3->Draw("APE");
  mg3->GetYaxis()->SetTitleOffset(1.2);
  // mg3->GetYaxis()->SetRangeUser(0.0,0.05);

  TLegend* leg3 = new TLegend(0.15,0.35,0.35,0.15);
  leg3->SetFillColor(0);
  leg3->AddEntry(biasZ050, "PU 50", "lp");
  leg3->AddEntry(biasZ0100, "PU 100", "lp");
  leg3->AddEntry(biasZ0140, "PU 140", "lp");
  leg3->AddEntry(biasZ0200, "PU 200", "lp");
  leg3->AddEntry(biasZ0300, "PU 300", "lp");
  
  leg3->Draw();
  
  if (SaveBiasPlots) {
    canv_z0->Print(("Immagini/" + sample + "_biasZ0VsEta.png").c_str(),"png");
      delete canv_z0;
  }

  
////////////////////////////////

  TGraphErrors* biasQPt50 = (TGraphErrors*) in50->Get("biasQPt_Eta");
  TGraphErrors* biasQPt100 = (TGraphErrors*) in100->Get("biasQPt_Eta");
  TGraphErrors* biasQPt140 = (TGraphErrors*) in140->Get("biasQPt_Eta");
  TGraphErrors* biasQPt200 = (TGraphErrors*) in200->Get("biasQPt_Eta");
  TGraphErrors* biasQPt300 = (TGraphErrors*) in300->Get("biasQPt_Eta");

  TMultiGraph* mg4 = new TMultiGraph();

  biasQPt50->SetLineColor(kCyan);
  biasQPt100->SetLineColor(kBlue);
  biasQPt140->SetLineColor(kGreen);
  biasQPt200->SetLineColor(kPink-8);
  biasQPt300->SetLineColor(kRed);

  mg4->Add(biasQPt50);
  mg4->Add(biasQPt100);
  mg4->Add(biasQPt140);
  mg4->Add(biasQPt200);
  mg4->Add(biasQPt300);

  mg4->SetTitle("p_{T} x #sigma(q/p_{T}) vs |#eta|; |#eta|; p_{T} x #sigma(q/p_{T})");

  TCanvas* canv_qpt = new TCanvas();
  mg4->Draw("APE");
  mg4->GetYaxis()->SetTitleOffset(1.2);
  // mg4->GetYaxis()->SetRangeUser(0.0,0.05);

  TLegend* leg4 = new TLegend(0.15,0.85,0.4,0.6);
  leg4->SetFillColor(0);
  leg4->AddEntry(biasQPt50, "PU 50", "lp");
  leg4->AddEntry(biasQPt100, "PU 100", "lp");
  leg4->AddEntry(biasQPt140, "PU 140", "lp");
  leg4->AddEntry(biasQPt200, "PU 200", "lp");
  leg4->AddEntry(biasQPt300, "PU 300", "lp");
  
  leg4->Draw();
  
  if (SaveBiasPlots) {
    canv_qpt->Print(("Immagini/" + sample + "_biasQPtVsEta.png").c_str(),"png");
      delete canv_qpt;
  }


////////////////////////////////

  TGraphErrors* biasPhi50 = (TGraphErrors*) in50->Get("biasPhi_Eta");
  TGraphErrors* biasPhi100 = (TGraphErrors*) in100->Get("biasPhi_Eta");
  TGraphErrors* biasPhi140 = (TGraphErrors*) in140->Get("biasPhi_Eta");
  TGraphErrors* biasPhi200 = (TGraphErrors*) in200->Get("biasPhi_Eta");
  TGraphErrors* biasPhi300 = (TGraphErrors*) in300->Get("biasPhi_Eta");

  TMultiGraph* mg5 = new TMultiGraph();

  biasPhi50->SetLineColor(kCyan);
  biasPhi100->SetLineColor(kBlue);
  biasPhi140->SetLineColor(kGreen);
  biasPhi200->SetLineColor(kPink-8);
  biasPhi300->SetLineColor(kRed);

  mg5->Add(biasPhi50);
  mg5->Add(biasPhi100);
  mg5->Add(biasPhi140);
  mg5->Add(biasPhi200);
  mg5->Add(biasPhi300);

  mg5->SetTitle("#sigma(Phi) vs |#eta|; |#eta|; #sigma(Phi)");

  TCanvas* canv_phi = new TCanvas();
  mg5->Draw("APE");
  mg5->GetYaxis()->SetTitleOffset(1.2);
  // mg5->GetYaxis()->SetRangeUser(0.0,0.05);

  TLegend* leg5 = new TLegend(0.15,0.85,0.4,0.6);
  leg5->SetFillColor(0);
  leg5->AddEntry(biasPhi50, "PU 50", "lp");
  leg5->AddEntry(biasPhi100, "PU 100", "lp");
  leg5->AddEntry(biasPhi140, "PU 140", "lp");
  leg5->AddEntry(biasPhi200, "PU 200", "lp");
  leg5->AddEntry(biasPhi300, "PU 300", "lp");
  
  leg5->Draw();
  
  if (SaveBiasPlots) {
    canv_phi->Print(("Immagini/" + sample + "_biasPhiVsEta.png").c_str(),"png");
      delete canv_phi;
  }


  ///////////////////////// FAKE PLOTS ////////////////////////

  if (SaveFakePlots) {

    TGraphErrors* fakeGun50 = (TGraphErrors*) in50->Get("fakeGun_average");
    TGraphErrors* fakeGun100 = (TGraphErrors*) in100->Get("fakeGun_average");
    TGraphErrors* fakeGun140 = (TGraphErrors*) in140->Get("fakeGun_average");
    TGraphErrors* fakeGun200 = (TGraphErrors*) in200->Get("fakeGun_average");
    TGraphErrors* fakeGun300 = (TGraphErrors*) in300->Get("fakeGun_average");

    TCanvas* canv_fakeGun = new TCanvas();
    canv_fakeGun->SetName("canv_fakeGun");
    canv_fakeGun->SetTitle("Fake Gun probability");

    TMultiGraph* mgFakeGun = new TMultiGraph();

    fakeGun50->SetLineColor(kCyan);
    fakeGun100->SetLineColor(kBlue);
    fakeGun140->SetLineColor(kGreen);
    fakeGun200->SetLineColor(kPink-8);
    fakeGun300->SetLineColor(kRed);

    mgFakeGun->Add(fakeGun50);
    // mgFakeGun->Add(fakeGun100);
    // mgFakeGun->Add(fakeGun140);
    mgFakeGun->Add(fakeGun200);
    mgFakeGun->Add(fakeGun300);
    
    mgFakeGun->SetTitle("Fake Gun Probability; |#eta|; Fake probability");
    
    mgFakeGun->Draw("APE");
    mgFakeGun->GetYaxis()->SetTitleOffset(1.2);

    TLegend* legFakeGun = new TLegend(0.15,0.85,0.4,0.6);

    legFakeGun->AddEntry(fakeGun50, "PU 50", "lp");
    // legFakeGun->AddEntry(fakeGun100, "PU 100", "lp");
    // legFakeGun->AddEntry(fakeGun140, "PU 140", "lp");
    legFakeGun->AddEntry(fakeGun200, "PU 200", "lp");
    legFakeGun->AddEntry(fakeGun300, "PU 300", "lp");

    legFakeGun->Draw();

    canv_fakeGun->Print(("Immagini/" + sample + "_fakeGun.png").c_str(),"png");
    delete canv_fakeGun;

    ///////// All fakes ///////////

    TGraphErrors* fake50 = (TGraphErrors*) in50->Get("fake_average");
    TGraphErrors* fake100 = (TGraphErrors*) in100->Get("fake_average");
    TGraphErrors* fake140 = (TGraphErrors*) in140->Get("fake_average");
    TGraphErrors* fake200 = (TGraphErrors*) in200->Get("fake_average");
    TGraphErrors* fake300 = (TGraphErrors*) in300->Get("fake_average");

    TCanvas* canv_fake = new TCanvas();
    canv_fake->SetName("canv_fake");
    canv_fake->SetTitle("Fake  probability");

    TMultiGraph* mgFake = new TMultiGraph();

    fake50->SetLineColor(kCyan);
    fake100->SetLineColor(kBlue);
    fake140->SetLineColor(kGreen);
    fake200->SetLineColor(kPink-8);
    fake300->SetLineColor(kRed);

    mgFake->Add(fake50);
    // mgFake->Add(fake100);
    // mgFake->Add(fake140);
    mgFake->Add(fake200);
    mgFake->Add(fake300);
    
    mgFake->SetTitle("Fake  Rate per event; |#eta|; Fake rate");
    
    mgFake->Draw("APE");
    mgFake->GetYaxis()->SetTitleOffset(1.2);

    TLegend* legFake = new TLegend(0.15,0.85,0.4,0.6);

    legFake->AddEntry(fake50, "PU 50", "lp");
    // legFake->AddEntry(fake100, "PU 100", "lp");
    // legFake->AddEntry(fake140, "PU 140", "lp");
    legFake->AddEntry(fake200, "PU 200", "lp");
    legFake->AddEntry(fake300, "PU 300", "lp");

    legFake->Draw();

    canv_fake->Print(("Immagini/" + sample + "_fake.png").c_str(),"png");
    delete canv_fake;
    


  }

  ///////////// EFFICIENCY PLOTS /////////////////

  if (SaveEfficiencyPlots)
    {


      //////// PT ////////

      TCanvas* canv_effPt = new TCanvas();

      TH1F* effPt50 = (TH1F*) in50->Get("eff_ptGun");
      TH1F* effPt100 = (TH1F*) in100->Get("eff_ptGun");
      TH1F* effPt140 = (TH1F*) in140->Get("eff_ptGun");
      TH1F* effPt200 = (TH1F*) in200->Get("eff_ptGun");
      TH1F* effPt300 = (TH1F*) in300->Get("eff_ptGun");
      
      effPt50->SetLineColor(kCyan);
      effPt100->SetLineColor(kBlue);
      effPt140->SetLineColor(kGreen);
      effPt200->SetLineColor(kPink-8);
      effPt300->SetLineColor(kRed);


      effPt50->Draw();
      effPt50->GetYaxis()->SetTitleOffset(1.2);

      effPt100->Draw("same");
      effPt100->GetYaxis()->SetTitleOffset(1.2);

      effPt140->Draw("same");
      effPt140->GetYaxis()->SetTitleOffset(1.2);

      effPt200->Draw("same");
      effPt200->GetYaxis()->SetTitleOffset(1.2);

      effPt300->Draw("same");
      effPt300->GetYaxis()->SetTitleOffset(1.2);

      // mg_effPt->GetYaxis()->SetRangeUser(0.0,0.05);
      
      TLegend* leg_effPt = new TLegend(0.15,0.35,0.35,0.15);
      leg_effPt->SetFillColor(0);
      leg_effPt->AddEntry(effPt50, "PU 50", "lp");
      leg_effPt->AddEntry(effPt100, "PU 100", "lp");
      leg_effPt->AddEntry(effPt140, "PU 140", "lp");
      leg_effPt->AddEntry(effPt200, "PU 200", "lp");
      leg_effPt->AddEntry(effPt300, "PU 300", "lp");
      
      leg_effPt->Draw();
      
      canv_effPt->Print(("Immagini/" + sample + "_effPt.png").c_str(),"png");
      delete canv_effPt;

      //////// ETA ////////

      TCanvas* canv_effEta = new TCanvas();

      TH1F* effEta50 = (TH1F*) in50->Get("eff_eta");
      TH1F* effEta100 = (TH1F*) in100->Get("eff_eta");
      TH1F* effEta140 = (TH1F*) in140->Get("eff_eta");
      TH1F* effEta200 = (TH1F*) in200->Get("eff_eta");
      TH1F* effEta300 = (TH1F*) in300->Get("eff_eta");
      
      effEta50->SetLineColor(kCyan);
      effEta100->SetLineColor(kBlue);
      effEta140->SetLineColor(kGreen);
      effEta200->SetLineColor(kPink-8);
      effEta300->SetLineColor(kRed);


      effEta50->Draw();
      effEta50->GetYaxis()->SetTitleOffset(1.2);

      effEta100->Draw("same");
      effEta100->GetYaxis()->SetTitleOffset(1.2);

      effEta140->Draw("same");
      effEta140->GetYaxis()->SetTitleOffset(1.2);

      effEta200->Draw("same");
      effEta200->GetYaxis()->SetTitleOffset(1.2);

      effEta300->Draw("same");
      effEta300->GetYaxis()->SetTitleOffset(1.2);

      // mg_effEta->GetYaxis()->SetRangeUser(0.0,0.05);
      
      TLegend* leg_effEta = new TLegend(0.15,0.35,0.35,0.15);
      leg_effEta->SetFillColor(0);
      leg_effEta->AddEntry(effEta50, "PU 50", "lp");
      leg_effEta->AddEntry(effEta100, "PU 100", "lp");
      leg_effEta->AddEntry(effEta140, "PU 140", "lp");
      leg_effEta->AddEntry(effEta200, "PU 200", "lp");
      leg_effEta->AddEntry(effEta300, "PU 300", "lp");
      
      leg_effEta->Draw();
      
      canv_effEta->Print(("Immagini/" + sample + "_effEta.png").c_str(),"png");
      delete canv_effEta;

      //////// PHI ////////

      TCanvas* canv_effPhi = new TCanvas();

      TH1F* effPhi50 = (TH1F*) in50->Get("eff_phi");
      TH1F* effPhi100 = (TH1F*) in100->Get("eff_phi");
      TH1F* effPhi140 = (TH1F*) in140->Get("eff_phi");
      TH1F* effPhi200 = (TH1F*) in200->Get("eff_phi");
      TH1F* effPhi300 = (TH1F*) in300->Get("eff_phi");
      
      effPhi50->SetLineColor(kCyan);
      effPhi100->SetLineColor(kBlue);
      effPhi140->SetLineColor(kGreen);
      effPhi200->SetLineColor(kPink-8);
      effPhi300->SetLineColor(kRed);


      effPhi50->Draw();
      effPhi50->GetYaxis()->SetTitleOffset(1.2);

      effPhi100->Draw("same");
      effPhi100->GetYaxis()->SetTitleOffset(1.2);

      effPhi140->Draw("same");
      effPhi140->GetYaxis()->SetTitleOffset(1.2);

      effPhi200->Draw("same");
      effPhi200->GetYaxis()->SetTitleOffset(1.2);

      effPhi300->Draw("same");
      effPhi300->GetYaxis()->SetTitleOffset(1.2);

      // mg_effPhi->GetYaxis()->SetRangeUser(0.0,0.05);
      
      TLegend* leg_effPhi = new TLegend(0.15,0.35,0.35,0.15);
      leg_effPhi->SetFillColor(0);
      leg_effPhi->AddEntry(effPhi50, "PU 50", "lp");
      leg_effPhi->AddEntry(effPhi100, "PU 100", "lp");
      leg_effPhi->AddEntry(effPhi140, "PU 140", "lp");
      leg_effPhi->AddEntry(effPhi200, "PU 200", "lp");
      leg_effPhi->AddEntry(effPhi300, "PU 300", "lp");
      
      leg_effPhi->Draw();
      
      canv_effPhi->Print(("Immagini/" + sample + "_effPhi.png").c_str(),"png");
      delete canv_effPhi; 
    }

  if (SaveHitsPlots) {
  /////////////////////////// HITS PLOTS /////////////////////////

    /////// all tracks /////////

    TCanvas* canv_nSiHits = new TCanvas();
    TCanvas* canv_nPixHits = new TCanvas();
    TCanvas* canv_nSCTHits = new TCanvas();
    
    TH1F* nSiHits50 = dynamic_cast<TH1F*>(in50->Get("TrackHist_reco_all__nSiHits"));
    TH1F* nPixHits50 = dynamic_cast<TH1F*>(in50->Get("TrackHist_reco_all__nPixHits"));
    TH1F* nSCTHits50 = dynamic_cast<TH1F*>(in50->Get("TrackHist_reco_all__nSCTHits"));

    TH1F* nSiHits100 = dynamic_cast<TH1F*>(in100->Get("TrackHist_reco_all__nSiHits"));
    TH1F* nPixHits100 = dynamic_cast<TH1F*>(in100->Get("TrackHist_reco_all__nPixHits"));
    TH1F* nSCTHits100 = dynamic_cast<TH1F*>(in100->Get("TrackHist_reco_all__nSCTHits"));

    TH1F* nSiHits140 = dynamic_cast<TH1F*>(in140->Get("TrackHist_reco_all__nSiHits"));
    TH1F* nPixHits140 = dynamic_cast<TH1F*>(in140->Get("TrackHist_reco_all__nPixHits"));
    TH1F* nSCTHits140 = dynamic_cast<TH1F*>(in140->Get("TrackHist_reco_all__nSCTHits"));

    TH1F* nSiHits200 = dynamic_cast<TH1F*>(in200->Get("TrackHist_reco_all__nSiHits"));
    TH1F* nPixHits200 = dynamic_cast<TH1F*>(in200->Get("TrackHist_reco_all__nPixHits"));
    TH1F* nSCTHits200 = dynamic_cast<TH1F*>(in200->Get("TrackHist_reco_all__nSCTHits"));

    TH1F* nSiHits300 = dynamic_cast<TH1F*>(in300->Get("TrackHist_reco_all__nSiHits"));
    TH1F* nPixHits300 = dynamic_cast<TH1F*>(in300->Get("TrackHist_reco_all__nPixHits"));
    TH1F* nSCTHits300 = dynamic_cast<TH1F*>(in300->Get("TrackHist_reco_all__nSCTHits"));

    nSiHits50->SetLineColor(kCyan);
    nSiHits100->SetLineColor(kBlue);
    nSiHits140->SetLineColor(kGreen);
    nSiHits200->SetLineColor(kPink-8);
    nSiHits300->SetLineColor(kRed);
    
    canv_nSiHits->cd();
  
    nSiHits50->Draw();
    nSiHits50->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHits100->Draw("same");
    nSiHits100->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHits140->Draw("same");
    nSiHits140->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHits200->Draw("same");
    nSiHits200->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHits300->Draw("same");
    nSiHits300->GetYaxis()->SetTitleOffset(1.2);
    
    TLegend* leg_nSiHits = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSiHits->SetFillColor(0);
    leg_nSiHits->AddEntry(nSiHits50, "PU 50", "lp");
    leg_nSiHits->AddEntry(nSiHits100, "PU 100", "lp");
    leg_nSiHits->AddEntry(nSiHits140, "PU 140", "lp");
    leg_nSiHits->AddEntry(nSiHits200, "PU 200", "lp");
    leg_nSiHits->AddEntry(nSiHits300, "PU 300", "lp");
    
    leg_nSiHits->Draw();
    
    canv_nSiHits->Print(("Immagini/" + sample + "_nSiHits.png").c_str(),"png");
    delete canv_nSiHits; 

    ////////

    nPixHits50->SetLineColor(kCyan);
    nPixHits100->SetLineColor(kBlue);
    nPixHits140->SetLineColor(kGreen);
    nPixHits200->SetLineColor(kPink-8);
    nPixHits300->SetLineColor(kRed);
    
    canv_nPixHits->cd();
  
    nPixHits50->Draw();
    nPixHits50->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHits100->Draw("same");
    nPixHits100->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHits140->Draw("same");
    nPixHits140->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHits200->Draw("same");
    nPixHits200->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHits300->Draw("same");
    nPixHits300->GetYaxis()->SetTitleOffset(1.2);
    
    TLegend* leg_nPixHits = new TLegend(0.65,0.6,0.85,0.4);
    leg_nPixHits->SetFillColor(0);
    leg_nPixHits->AddEntry(nPixHits50, "PU 50", "lp");
    leg_nPixHits->AddEntry(nPixHits100, "PU 100", "lp");
    leg_nPixHits->AddEntry(nPixHits140, "PU 140", "lp");
    leg_nPixHits->AddEntry(nPixHits200, "PU 200", "lp");
    leg_nPixHits->AddEntry(nPixHits300, "PU 300", "lp");
    
    leg_nPixHits->Draw();
    
    canv_nPixHits->Print(("Immagini/" + sample + "_nPixHits.png").c_str(),"png");
    delete canv_nPixHits;

    ///////////

    nSCTHits50->SetLineColor(kCyan);
    nSCTHits100->SetLineColor(kBlue);
    nSCTHits140->SetLineColor(kGreen);
    nSCTHits200->SetLineColor(kPink-8);
    nSCTHits300->SetLineColor(kRed);
    
    canv_nSCTHits->cd();
  
    nSCTHits50->Draw();
    nSCTHits50->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHits100->Draw("same");
    nSCTHits100->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHits140->Draw("same");
    nSCTHits140->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHits200->Draw("same");
    nSCTHits200->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHits300->Draw("same");
    nSCTHits300->GetYaxis()->SetTitleOffset(1.2);
    
    TLegend* leg_nSCTHits = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSCTHits->SetFillColor(0);
    leg_nSCTHits->AddEntry(nSCTHits50, "PU 50", "lp");
    leg_nSCTHits->AddEntry(nSCTHits100, "PU 100", "lp");
    leg_nSCTHits->AddEntry(nSCTHits140, "PU 140", "lp");
    leg_nSCTHits->AddEntry(nSCTHits200, "PU 200", "lp");
    leg_nSCTHits->AddEntry(nSCTHits300, "PU 300", "lp");
    
    leg_nSCTHits->Draw();
    
    canv_nSCTHits->Print(("Immagini/" + sample + "_nSCTHits.png").c_str(),"png");
    delete canv_nSCTHits;

    
    //////// Fake tracks ////////
    
    TCanvas* canv_nSiHitsFake = new TCanvas();
    TCanvas* canv_nPixHitsFake = new TCanvas();
    TCanvas* canv_nSCTHitsFake = new TCanvas();
    
					    TH1F* nSiHitsFake50 = dynamic_cast<TH1F*>(in50->Get("TrackHist_reco_all__nFakeSiHits"));
					    TH1F* nPixHitsFake50 = dynamic_cast<TH1F*>(in50->Get("TrackHist_reco_all__nFakePixHits"));
    TH1F* nSCTHitsFake50 = dynamic_cast<TH1F*>(in50->Get("TrackHist_reco_all__nFakeSCTHits"));

    TH1F* nSiHitsFake100 = dynamic_cast<TH1F*>(in100->Get("TrackHist_reco_all__nFakeSiHits"));
    TH1F* nPixHitsFake100 = dynamic_cast<TH1F*>(in100->Get("TrackHist_reco_all__nFakePixHits"));
    TH1F* nSCTHitsFake100 = dynamic_cast<TH1F*>(in100->Get("TrackHist_reco_all__nFakeSCTHits"));

    TH1F* nSiHitsFake140 = dynamic_cast<TH1F*>(in140->Get("TrackHist_reco_all__nFakeSiHits"));
    TH1F* nPixHitsFake140 = dynamic_cast<TH1F*>(in140->Get("TrackHist_reco_all__nFakePixHits"));
    TH1F* nSCTHitsFake140 = dynamic_cast<TH1F*>(in140->Get("TrackHist_reco_all__nFakeSCTHits"));

    TH1F* nSiHitsFake200 = dynamic_cast<TH1F*>(in200->Get("TrackHist_reco_all__nFakeSiHits"));
    TH1F* nPixHitsFake200 = dynamic_cast<TH1F*>(in200->Get("TrackHist_reco_all__nFakePixHits"));
    TH1F* nSCTHitsFake200 = dynamic_cast<TH1F*>(in200->Get("TrackHist_reco_all__nFakeSCTHits"));

    TH1F* nSiHitsFake300 = dynamic_cast<TH1F*>(in300->Get("TrackHist_reco_all__nFakeSiHits"));
    TH1F* nPixHitsFake300 = dynamic_cast<TH1F*>(in300->Get("TrackHist_reco_all__nFakePixHits"));
    TH1F* nSCTHitsFake300 = dynamic_cast<TH1F*>(in300->Get("TrackHist_reco_all__nFakeSCTHits"));
    
    nSiHitsFake50->SetLineColor(kCyan);
    nSiHitsFake100->SetLineColor(kBlue);
    nSiHitsFake140->SetLineColor(kGreen);
    nSiHitsFake200->SetLineColor(kPink-8);
    nSiHitsFake300->SetLineColor(kRed);
    
    canv_nSiHitsFake->cd();
  
    nSiHitsFake50->Draw();
    nSiHitsFake50->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHitsFake100->Draw("same");
    nSiHitsFake100->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHitsFake140->Draw("same");
    nSiHitsFake140->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHitsFake200->Draw("same");
    nSiHitsFake200->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHitsFake300->Draw("same");
    nSiHitsFake300->GetYaxis()->SetTitleOffset(1.2);
    
    TLegend* leg_nSiHitsFake = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSiHitsFake->SetFillColor(0);
    leg_nSiHitsFake->AddEntry(nSiHitsFake50, "PU 50", "lp");
    leg_nSiHitsFake->AddEntry(nSiHitsFake100, "PU 100", "lp");
    leg_nSiHitsFake->AddEntry(nSiHitsFake140, "PU 140", "lp");
    leg_nSiHitsFake->AddEntry(nSiHitsFake200, "PU 200", "lp");
    leg_nSiHitsFake->AddEntry(nSiHitsFake300, "PU 300", "lp");
    
    leg_nSiHitsFake->Draw();
    
    canv_nSiHitsFake->Print(("Immagini/" + sample + "_nSiHitsFake.png").c_str(),"png");
    delete canv_nSiHitsFake; 

    ////////

    nPixHitsFake50->SetLineColor(kCyan);
    nPixHitsFake100->SetLineColor(kBlue);
    nPixHitsFake140->SetLineColor(kGreen);
    nPixHitsFake200->SetLineColor(kPink-8);
    nPixHitsFake300->SetLineColor(kRed);
    
    canv_nPixHitsFake->cd();
  
    nPixHitsFake50->Draw();
    nPixHitsFake50->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHitsFake100->Draw("same");
    nPixHitsFake100->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHitsFake140->Draw("same");
    nPixHitsFake140->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHitsFake200->Draw("same");
    nPixHitsFake200->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHitsFake300->Draw("same");
    nPixHitsFake300->GetYaxis()->SetTitleOffset(1.2);
    
    TLegend* leg_nPixHitsFake = new TLegend(0.65,0.6,0.85,0.4);
    leg_nPixHitsFake->SetFillColor(0);
    leg_nPixHitsFake->AddEntry(nPixHitsFake50, "PU 50", "lp");
    leg_nPixHitsFake->AddEntry(nPixHitsFake100, "PU 100", "lp");
    leg_nPixHitsFake->AddEntry(nPixHitsFake140, "PU 140", "lp");
    leg_nPixHitsFake->AddEntry(nPixHitsFake200, "PU 200", "lp");
    leg_nPixHitsFake->AddEntry(nPixHitsFake300, "PU 300", "lp");
    
    leg_nPixHitsFake->Draw();
    
    canv_nPixHitsFake->Print(("Immagini/" + sample + "_nPixHitsFake.png").c_str(),"png");
    delete canv_nPixHitsFake;

    ///////////

    nSCTHitsFake50->SetLineColor(kCyan);
    nSCTHitsFake100->SetLineColor(kBlue);
    nSCTHitsFake140->SetLineColor(kGreen);
    nSCTHitsFake200->SetLineColor(kPink-8);
    nSCTHitsFake300->SetLineColor(kRed);
    
    canv_nSCTHitsFake->cd();
  
    nSCTHitsFake50->Draw();
    nSCTHitsFake50->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHitsFake100->Draw("same");
    nSCTHitsFake100->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHitsFake140->Draw("same");
    nSCTHitsFake140->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHitsFake200->Draw("same");
    nSCTHitsFake200->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHitsFake300->Draw("same");
    nSCTHitsFake300->GetYaxis()->SetTitleOffset(1.2);
    
    TLegend* leg_nSCTHitsFake = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSCTHitsFake->SetFillColor(0);
    leg_nSCTHitsFake->AddEntry(nSCTHitsFake50, "PU 50", "lp");
    leg_nSCTHitsFake->AddEntry(nSCTHitsFake100, "PU 100", "lp");
    leg_nSCTHitsFake->AddEntry(nSCTHitsFake140, "PU 140", "lp");
    leg_nSCTHitsFake->AddEntry(nSCTHitsFake200, "PU 200", "lp");
    leg_nSCTHitsFake->AddEntry(nSCTHitsFake300, "PU 300", "lp");
    
    leg_nSCTHitsFake->Draw();
    
    canv_nSCTHitsFake->Print(("Immagini/" + sample + "_nSCTHitsFake.png").c_str(),"png");
    delete canv_nSCTHitsFake;

    ////////////// True tracks ////////////////

    TCanvas* canv_nSiHitsTrue = new TCanvas();
    TCanvas* canv_nPixHitsTrue = new TCanvas();
    TCanvas* canv_nSCTHitsTrue = new TCanvas();
    
    TH1F* nSiHitsTrue50 = dynamic_cast<TH1F*>(in50->Get("TrackHist_reco_all__nTrueSiHits"));
    TH1F* nPixHitsTrue50 = dynamic_cast<TH1F*>(in50->Get("TrackHist_reco_all__nTruePixHits"));
    TH1F* nSCTHitsTrue50 = dynamic_cast<TH1F*>(in50->Get("TrackHist_reco_all__nTrueSCTHits"));

    TH1F* nSiHitsTrue100 = dynamic_cast<TH1F*>(in100->Get("TrackHist_reco_all__nTrueSiHits"));
    TH1F* nPixHitsTrue100 = dynamic_cast<TH1F*>(in100->Get("TrackHist_reco_all__nTruePixHits"));
    TH1F* nSCTHitsTrue100 = dynamic_cast<TH1F*>(in100->Get("TrackHist_reco_all__nTrueSCTHits"));

    TH1F* nSiHitsTrue140 = dynamic_cast<TH1F*>(in140->Get("TrackHist_reco_all__nTrueSiHits"));
    TH1F* nPixHitsTrue140 = dynamic_cast<TH1F*>(in140->Get("TrackHist_reco_all__nTruePixHits"));
    TH1F* nSCTHitsTrue140 = dynamic_cast<TH1F*>(in140->Get("TrackHist_reco_all__nTrueSCTHits"));

    TH1F* nSiHitsTrue200 = dynamic_cast<TH1F*>(in200->Get("TrackHist_reco_all__nTrueSiHits"));
    TH1F* nPixHitsTrue200 = dynamic_cast<TH1F*>(in200->Get("TrackHist_reco_all__nTruePixHits"));
    TH1F* nSCTHitsTrue200 = dynamic_cast<TH1F*>(in200->Get("TrackHist_reco_all__nTrueSCTHits"));

    TH1F* nSiHitsTrue300 = dynamic_cast<TH1F*>(in300->Get("TrackHist_reco_all__nTrueSiHits"));
    TH1F* nPixHitsTrue300 = dynamic_cast<TH1F*>(in300->Get("TrackHist_reco_all__nTruePixHits"));
    TH1F* nSCTHitsTrue300 = dynamic_cast<TH1F*>(in300->Get("TrackHist_reco_all__nTrueSCTHits"));
    
    nSiHitsTrue50->SetLineColor(kCyan);
    nSiHitsTrue100->SetLineColor(kBlue);
    nSiHitsTrue140->SetLineColor(kGreen);
    nSiHitsTrue200->SetLineColor(kPink-8);
    nSiHitsTrue300->SetLineColor(kRed);
    
    canv_nSiHitsTrue->cd();
  
    nSiHitsTrue50->Draw();
    nSiHitsTrue50->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHitsTrue100->Draw("same");
    nSiHitsTrue100->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHitsTrue140->Draw("same");
    nSiHitsTrue140->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHitsTrue200->Draw("same");
    nSiHitsTrue200->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHitsTrue300->Draw("same");
    nSiHitsTrue300->GetYaxis()->SetTitleOffset(1.2);
    
    TLegend* leg_nSiHitsTrue = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSiHitsTrue->SetFillColor(0);
    leg_nSiHitsTrue->AddEntry(nSiHitsTrue50, "PU 50", "lp");
    leg_nSiHitsTrue->AddEntry(nSiHitsTrue100, "PU 100", "lp");
    leg_nSiHitsTrue->AddEntry(nSiHitsTrue140, "PU 140", "lp");
    leg_nSiHitsTrue->AddEntry(nSiHitsTrue200, "PU 200", "lp");
    leg_nSiHitsTrue->AddEntry(nSiHitsTrue300, "PU 300", "lp");
    
    leg_nSiHitsTrue->Draw();
    
    canv_nSiHitsTrue->Print(("Immagini/" + sample + "_nSiHitsTrue.png").c_str(),"png");
    delete canv_nSiHitsTrue; 

    ////////

    nPixHitsTrue50->SetLineColor(kCyan);
    nPixHitsTrue100->SetLineColor(kBlue);
    nPixHitsTrue140->SetLineColor(kGreen);
    nPixHitsTrue200->SetLineColor(kPink-8);
    nPixHitsTrue300->SetLineColor(kRed);
    
    canv_nPixHitsTrue->cd();
  
    nPixHitsTrue50->Draw();
    nPixHitsTrue50->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHitsTrue100->Draw("same");
    nPixHitsTrue100->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHitsTrue140->Draw("same");
    nPixHitsTrue140->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHitsTrue200->Draw("same");
    nPixHitsTrue200->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHitsTrue300->Draw("same");
    nPixHitsTrue300->GetYaxis()->SetTitleOffset(1.2);
    
    TLegend* leg_nPixHitsTrue = new TLegend(0.65,0.6,0.85,0.4);
    leg_nPixHitsTrue->SetFillColor(0);
    leg_nPixHitsTrue->AddEntry(nPixHitsTrue50, "PU 50", "lp");
    leg_nPixHitsTrue->AddEntry(nPixHitsTrue100, "PU 100", "lp");
    leg_nPixHitsTrue->AddEntry(nPixHitsTrue140, "PU 140", "lp");
    leg_nPixHitsTrue->AddEntry(nPixHitsTrue200, "PU 200", "lp");
    leg_nPixHitsTrue->AddEntry(nPixHitsTrue300, "PU 300", "lp");
    
    leg_nPixHitsTrue->Draw();
    
    canv_nPixHitsTrue->Print(("Immagini/" + sample + "_nPixHitsTrue.png").c_str(),"png");
    delete canv_nPixHitsTrue;

    ///////////

    nSCTHitsTrue50->SetLineColor(kCyan);
    nSCTHitsTrue100->SetLineColor(kBlue);
    nSCTHitsTrue140->SetLineColor(kGreen);
    nSCTHitsTrue200->SetLineColor(kPink-8);
    nSCTHitsTrue300->SetLineColor(kRed);
    
    canv_nSCTHitsTrue->cd();
  
    nSCTHitsTrue50->Draw();
    nSCTHitsTrue50->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHitsTrue100->Draw("same");
    nSCTHitsTrue100->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHitsTrue140->Draw("same");
    nSCTHitsTrue140->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHitsTrue200->Draw("same");
    nSCTHitsTrue200->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHitsTrue300->Draw("same");
    nSCTHitsTrue300->GetYaxis()->SetTitleOffset(1.2);
    
    TLegend* leg_nSCTHitsTrue = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSCTHitsTrue->SetFillColor(0);
    leg_nSCTHitsTrue->AddEntry(nSCTHitsTrue50, "PU 50", "lp");
    leg_nSCTHitsTrue->AddEntry(nSCTHitsTrue100, "PU 100", "lp");
    leg_nSCTHitsTrue->AddEntry(nSCTHitsTrue140, "PU 140", "lp");
    leg_nSCTHitsTrue->AddEntry(nSCTHitsTrue200, "PU 200", "lp");
    leg_nSCTHitsTrue->AddEntry(nSCTHitsTrue300, "PU 300", "lp");
    
    leg_nSCTHitsTrue->Draw();
    
    canv_nSCTHitsTrue->Print(("Immagini/" + sample + "_nSCTHitsTrue.png").c_str(),"png");
    delete canv_nSCTHitsTrue;


  
  }
}
