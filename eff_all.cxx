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

  TGraphErrors* biasPt50 = dynamic_cast<TGraphErrors*>( in50->Get("biasPt_Eta"));
  TGraphErrors* biasPt100 = dynamic_cast<TGraphErrors*>( in100->Get("biasPt_Eta"));
  TGraphErrors* biasPt140 = dynamic_cast<TGraphErrors*>( in140->Get("biasPt_Eta"));
  TGraphErrors* biasPt200 = dynamic_cast<TGraphErrors*>( in200->Get("biasPt_Eta"));
  TGraphErrors* biasPt300 = dynamic_cast<TGraphErrors*>( in300->Get("biasPt_Eta"));

  TMultiGraph* mg = new TMultiGraph();

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

  mg->SetTitle("#sigma(p_{T}) vs |#eta|; Truth |#eta|; #sigma(p_{T}) [MeV]");

  TCanvas* canv_pt = new TCanvas();
  mg->Draw("APE");
  mg->GetYaxis()->SetTitleOffset(1.2);
  // mg->GetYaxis()->SetRangeUser(0.0,4500.0);

  TLegend* leg = new TLegend(0.15,0.85,0.4,0.6);
  leg->SetFillColor(0);
  leg->AddEntry(biasPt50, (sample + ": PU 50").c_str(), "lp");
  leg->AddEntry(biasPt100, (sample + ": PU100").c_str(), "lp");
  leg->AddEntry(biasPt140, (sample + ": PU 140").c_str(), "lp");
  leg->AddEntry(biasPt200, (sample + ": PU 200").c_str(), "lp");
  leg->AddEntry(biasPt300, (sample + ": PU 300").c_str(), "lp");
  
  leg->Draw();

  if (SaveBiasPlots) {
    canv_pt->Print(("Immagini/" + sample + "_biasPtVsEta.png").c_str(),"png");
      delete canv_pt;
 }

  ////////////////////////////////

  TGraphErrors* biasD050 = dynamic_cast<TGraphErrors*>( in50->Get("biasD0_Eta"));
  TGraphErrors* biasD0100 = dynamic_cast<TGraphErrors*>( in100->Get("biasD0_Eta"));
  TGraphErrors* biasD0140 = dynamic_cast<TGraphErrors*>( in140->Get("biasD0_Eta"));
  TGraphErrors* biasD0200 = dynamic_cast<TGraphErrors*>( in200->Get("biasD0_Eta"));
  TGraphErrors* biasD0300 = dynamic_cast<TGraphErrors*>( in300->Get("biasD0_Eta"));

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

  mg2->SetTitle("#sigma(D0) vs |#eta|;Truth |#eta|; #sigma(D0) [mm]");

  TCanvas* canv_d0 = new TCanvas();
  mg2->Draw("APE");
  mg2->GetYaxis()->SetTitleOffset(1.2);
  // mg2->GetYaxis()->SetRangeUser(0.0,0.05);

  TLegend* leg2 = new TLegend(0.15,0.85,0.4,0.6);
  leg2->SetFillColor(0);
  leg2->AddEntry(biasD050, (sample + ": PU 50").c_str(), "lp");
  leg2->AddEntry(biasD0100, (sample + ": PU 100").c_str(), "lp");
  leg2->AddEntry(biasD0140, (sample + ": PU 140").c_str(), "lp");
  leg2->AddEntry(biasD0200, (sample + ": PU 200").c_str(), "lp");
  leg2->AddEntry(biasD0300, (sample + ": PU 300").c_str(), "lp");
  
  leg2->Draw();

  if (SaveBiasPlots) {
    canv_d0->Print(("Immagini/" + sample + "_biasD0VsEta.png").c_str(),"png");
      delete canv_d0;

  }


////////////////////////////////

  TGraphErrors* biasZ050 = dynamic_cast<TGraphErrors*>( in50->Get("biasZ0_Eta"));
  TGraphErrors* biasZ0100 = dynamic_cast<TGraphErrors*>( in100->Get("biasZ0_Eta"));
  TGraphErrors* biasZ0140 = dynamic_cast<TGraphErrors*>( in140->Get("biasZ0_Eta"));
  TGraphErrors* biasZ0200 = dynamic_cast<TGraphErrors*>( in200->Get("biasZ0_Eta"));
  TGraphErrors* biasZ0300 = dynamic_cast<TGraphErrors*>( in300->Get("biasZ0_Eta"));

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

  mg3->SetTitle("#sigma(Z0) vs |#eta|;Truth |#eta|; #sigma(Z0) [mm]");

  TCanvas* canv_z0 = new TCanvas();
  mg3->Draw("APE");
  mg3->GetYaxis()->SetTitleOffset(1.2);
  // mg3->GetYaxis()->SetRangeUser(0.0,0.05);

  TLegend* leg3 = new TLegend(0.15,0.35,0.35,0.15);
  leg3->SetFillColor(0);
  leg3->AddEntry(biasZ050, (sample + ": PU 50").c_str(), "lp");
  leg3->AddEntry(biasZ0100, (sample + ": PU 100").c_str(), "lp");
  leg3->AddEntry(biasZ0140, (sample + ": PU 140").c_str(), "lp");
  leg3->AddEntry(biasZ0200, (sample + ": PU 200").c_str(), "lp");
  leg3->AddEntry(biasZ0300, (sample + ": PU 300").c_str(), "lp");
  
  leg3->Draw();
  
  if (SaveBiasPlots) {
    canv_z0->Print(("Immagini/" + sample + "_biasZ0VsEta.png").c_str(),"png");
      delete canv_z0;
  }

  
////////////////////////////////

  TGraphErrors* biasQPt50 = dynamic_cast<TGraphErrors*>( in50->Get("biasQPt_Eta"));
  TGraphErrors* biasQPt100 = dynamic_cast<TGraphErrors*>( in100->Get("biasQPt_Eta"));
  TGraphErrors* biasQPt140 = dynamic_cast<TGraphErrors*>( in140->Get("biasQPt_Eta"));
  TGraphErrors* biasQPt200 = dynamic_cast<TGraphErrors*>( in200->Get("biasQPt_Eta"));
  TGraphErrors* biasQPt300 = dynamic_cast<TGraphErrors*>( in300->Get("biasQPt_Eta"));

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

  mg4->SetTitle("p_{T} x #sigma(q/p_{T}) vs |#eta|;Truth |#eta|; p_{T} x #sigma(q/p_{T})");

  TCanvas* canv_qpt = new TCanvas();
  mg4->Draw("APE");
  mg4->GetYaxis()->SetTitleOffset(1.2);
  // mg4->GetYaxis()->SetRangeUser(0.0,0.05);

  TLegend* leg4 = new TLegend(0.15,0.85,0.4,0.6);
  leg4->SetFillColor(0);
  leg4->AddEntry(biasQPt50, (sample + ": PU 50").c_str(), "lp");
  leg4->AddEntry(biasQPt100, (sample + ": PU 100").c_str(), "lp");
  leg4->AddEntry(biasQPt140, (sample + ": PU 140").c_str(), "lp");
  leg4->AddEntry(biasQPt200, (sample + ": PU 200").c_str(), "lp");
  leg4->AddEntry(biasQPt300, (sample + ": PU 300").c_str(), "lp");
  
  leg4->Draw();
  
  if (SaveBiasPlots) {
    canv_qpt->Print(("Immagini/" + sample + "_biasQPtVsEta.png").c_str(),"png");
      delete canv_qpt;
  }


////////////////////////////////

  TGraphErrors* biasPhi50 = dynamic_cast<TGraphErrors*>( in50->Get("biasPhi_Eta"));
  TGraphErrors* biasPhi100 = dynamic_cast<TGraphErrors*>( in100->Get("biasPhi_Eta"));
  TGraphErrors* biasPhi140 = dynamic_cast<TGraphErrors*>( in140->Get("biasPhi_Eta"));
  TGraphErrors* biasPhi200 = dynamic_cast<TGraphErrors*>( in200->Get("biasPhi_Eta"));
  TGraphErrors* biasPhi300 = dynamic_cast<TGraphErrors*>( in300->Get("biasPhi_Eta"));

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

  mg5->SetTitle("#sigma(Phi) vs |#eta|;Truth |#eta|; #sigma(Phi)");

  TCanvas* canv_phi = new TCanvas();
  mg5->Draw("APE");
  mg5->GetYaxis()->SetTitleOffset(1.2);
  // mg5->GetYaxis()->SetRangeUser(0.0,0.05);

  TLegend* leg5 = new TLegend(0.15,0.85,0.4,0.6);
  leg5->SetFillColor(0);
  leg5->AddEntry(biasPhi50, (sample + ": PU 50").c_str(), "lp");
  leg5->AddEntry(biasPhi100, (sample + ": PU 100").c_str(), "lp");
  leg5->AddEntry(biasPhi140, (sample + ": PU 140").c_str(), "lp");
  leg5->AddEntry(biasPhi200, (sample + ": PU 200").c_str(), "lp");
  leg5->AddEntry(biasPhi300, (sample + ": PU 300").c_str(), "lp");
  
  leg5->Draw();
  
  if (SaveBiasPlots) {
    canv_phi->Print(("Immagini/" + sample + "_biasPhiVsEta.png").c_str(),"png");
      delete canv_phi;
  }


  ///////////////////////// FAKE PLOTS ////////////////////////

  if (SaveFakePlots) {

    TGraphErrors* fakeGun50 = dynamic_cast<TGraphErrors*>( in50->Get("fakeGun_average"));
    TGraphErrors* fakeGun100 = dynamic_cast<TGraphErrors*>( in100->Get("fakeGun_average"));
    TGraphErrors* fakeGun140 = dynamic_cast<TGraphErrors*>( in140->Get("fakeGun_average"));
    TGraphErrors* fakeGun200 = dynamic_cast<TGraphErrors*>( in200->Get("fakeGun_average"));
    TGraphErrors* fakeGun300 = dynamic_cast<TGraphErrors*>( in300->Get("fakeGun_average"));

    TCanvas* canv_fakeGun = new TCanvas();
    canv_fakeGun->SetName("canv_fakeGun");
    canv_fakeGun->SetTitle("Fake Gun probability");

    TMultiGraph* mgFakeGun = new TMultiGraph();

    fakeGun50->SetLineColor(kCyan);
    fakeGun100->SetLineColor(kPink - 8);
    fakeGun140->SetLineColor(kGreen);
    fakeGun200->SetLineColor(kBlue);
    fakeGun300->SetLineColor(kRed);

    fakeGun50->SetMarkerStyle(20);
    fakeGun100->SetMarkerStyle(21);
    fakeGun140->SetMarkerStyle(22);
    fakeGun200->SetMarkerStyle(29);
    fakeGun300->SetMarkerStyle(33);

    fakeGun50->SetMarkerColor(kCyan);
    fakeGun100->SetMarkerColor(kPink-8);
    fakeGun140->SetMarkerColor(kGreen);
    fakeGun200->SetMarkerColor(kBlue);
    fakeGun300->SetMarkerColor(kRed);


    mgFakeGun->Add(fakeGun50);
    // mgFakeGun->Add(fakeGun100);
    // mgFakeGun->Add(fakeGun140);
    mgFakeGun->Add(fakeGun200);
    mgFakeGun->Add(fakeGun300);
    
    mgFakeGun->SetTitle("Fake Gun Probability;Truth |#eta|; Fake probability");
    
    mgFakeGun->Draw("APE");
    mgFakeGun->GetYaxis()->SetTitleOffset(1.2);
    mgFakeGun->GetYaxis()->SetRangeUser(0.0,0.07);

    TLegend* legFakeGun = new TLegend(0.15,0.85,0.4,0.6);

    legFakeGun->AddEntry(fakeGun50, (sample + ": PU 50").c_str(), "lp");
    // legFakeGun->AddEntry(fakeGun100, (sample + ": PU 100").c_str(), "lp");
    // legFakeGun->AddEntry(fakeGun140, (sample + ": PU 140").c_str(), "lp");
    legFakeGun->AddEntry(fakeGun200, (sample + ": PU 200").c_str(), "lp");
    legFakeGun->AddEntry(fakeGun300, (sample + ": PU 300").c_str(), "lp");

    legFakeGun->Draw();

    canv_fakeGun->Print(("Immagini/" + sample + "_fakeGun.png").c_str(),"png");
    delete canv_fakeGun;

    ///////// All fakes ///////////

    TGraphErrors* fake50 = dynamic_cast<TGraphErrors*>( in50->Get("fake_average"));
    TGraphErrors* fake100 = dynamic_cast<TGraphErrors*>( in100->Get("fake_average"));
    TGraphErrors* fake140 = dynamic_cast<TGraphErrors*>( in140->Get("fake_average"));
    TGraphErrors* fake200 = dynamic_cast<TGraphErrors*>( in200->Get("fake_average"));
    TGraphErrors* fake300 = dynamic_cast<TGraphErrors*>( in300->Get("fake_average"));

    TCanvas* canv_fake = new TCanvas();
    canv_fake->SetName("canv_fake");
    canv_fake->SetTitle("Fake rate");

    TMultiGraph* mgFake = new TMultiGraph();

    fake50->SetLineColor(kCyan);
    fake100->SetLineColor(kPink - 8);
    fake140->SetLineColor(kGreen);
    fake200->SetLineColor(kBlue);
    fake300->SetLineColor(kRed);

    fake50->SetMarkerStyle(20);
    fake100->SetMarkerStyle(21);
    fake140->SetMarkerStyle(22);
    fake200->SetMarkerStyle(29);
    fake300->SetMarkerStyle(33);

    fake50->SetMarkerColor(kCyan);
    fake100->SetMarkerColor(kPink-8);
    fake140->SetMarkerColor(kGreen);
    fake200->SetMarkerColor(kBlue);
    fake300->SetMarkerColor(kRed);

    mgFake->Add(fake50);
    // mgFake->Add(fake100);
    // mgFake->Add(fake140);
    mgFake->Add(fake200);
    mgFake->Add(fake300);
    
    mgFake->SetTitle("Fake  Rate;Truth |#eta|; Fake rate");
    
    mgFake->Draw("APE");
    mgFake->GetYaxis()->SetTitleOffset(1.35);
    mgFake->GetYaxis()->SetRangeUser(0.0,0.0035);

    TLegend* legFake = new TLegend(0.15,0.85,0.4,0.6);

    legFake->AddEntry(fake50, (sample + ": PU 50").c_str(), "lp");
    // legFake->AddEntry(fake100, (sample + ": PU 100").c_str(), "lp");
    // legFake->AddEntry(fake140, (sample + ": PU 140").c_str(), "lp");
    legFake->AddEntry(fake200, (sample + ": PU 200").c_str(), "lp");
    legFake->AddEntry(fake300, (sample + ": PU 300").c_str(), "lp");

    legFake->Draw();

    canv_fake->Print(("Immagini/" + sample + "_fake.png").c_str(),"png");
    delete canv_fake;
    


  }

  ///////////// EFFICIENCY PLOTS /////////////////

  if (SaveEfficiencyPlots)
    {


      //////// PT ////////

      TCanvas* canv_effPt = new TCanvas();

      TH1F* effPt50 = dynamic_cast<TH1F*>( in50->Get("eff_ptGun"));
      TH1F* effPt100 = dynamic_cast<TH1F*>( in100->Get("eff_ptGun"));
      TH1F* effPt140 = dynamic_cast<TH1F*>( in140->Get("eff_ptGun"));
      TH1F* effPt200 = dynamic_cast<TH1F*>( in200->Get("eff_ptGun"));
      TH1F* effPt300 = dynamic_cast<TH1F*>( in300->Get("eff_ptGun"));
      
      effPt50->SetLineColor(kCyan);
      effPt100->SetLineColor(kBlue);
      effPt140->SetLineColor(kGreen);
      effPt200->SetLineColor(kPink-8);
      effPt300->SetLineColor(kRed);

      effPt50->SetMarkerStyle(20);
      effPt100->SetMarkerStyle(21);
      effPt140->SetMarkerStyle(22);
      effPt200->SetMarkerStyle(29);
      effPt300->SetMarkerStyle(33);

      effPt50->SetMarkerColor(kCyan);
      effPt100->SetMarkerColor(kBlue);
      effPt140->SetMarkerColor(kGreen);
      effPt200->SetMarkerColor(kPink-8);
      effPt300->SetMarkerColor(kRed);

      

      effPt50->Draw();
      effPt50->SetStats(0);
      effPt50->GetYaxis()->SetTitleOffset(1.2);
      effPt50->GetYaxis()->SetRangeUser(0.0,1.0);

      effPt100->Draw("same");
      effPt100->SetStats(0);
      effPt100->GetYaxis()->SetTitleOffset(1.2);
      effPt100->GetYaxis()->SetRangeUser(0.0,1.0);

      effPt140->Draw("same");
      effPt140->SetStats(0);
      effPt140->GetYaxis()->SetTitleOffset(1.2);
      effPt140->GetYaxis()->SetRangeUser(0.0,1.0);

      effPt200->Draw("same");
      effPt200->SetStats(0);
      effPt200->GetYaxis()->SetTitleOffset(1.2);
      effPt200->GetYaxis()->SetRangeUser(0.0,1.0);

      effPt300->Draw("same");
      effPt300->SetStats(0);
      effPt300->GetYaxis()->SetTitleOffset(1.2);
      effPt300->GetYaxis()->SetRangeUser(0.0,1.0);

      // mg_effPt->GetYaxis()->SetRangeUser(0.0,0.05);
      
      TLegend* leg_effPt = new TLegend(0.15,0.35,0.35,0.15);
      leg_effPt->SetFillColor(0);
      leg_effPt->AddEntry(effPt50, (sample + ": PU 50").c_str(), "lp");
      leg_effPt->AddEntry(effPt100, (sample + ": PU 100").c_str(), "lp");
      leg_effPt->AddEntry(effPt140, (sample + ": PU 140").c_str(), "lp");
      leg_effPt->AddEntry(effPt200, (sample + ": PU 200").c_str(), "lp");
      leg_effPt->AddEntry(effPt300, (sample + ": PU 300").c_str(), "lp");
      
      leg_effPt->Draw();
      
      canv_effPt->Print(("Immagini/" + sample + "_effPt.png").c_str(),"png");
      delete canv_effPt;

      //////// ETA ////////

      TCanvas* canv_effEta = new TCanvas();

      TH1F* effEta50 = dynamic_cast<TH1F*>( in50->Get("eff_eta"));
      TH1F* effEta100 = dynamic_cast<TH1F*>( in100->Get("eff_eta"));
      TH1F* effEta140 = dynamic_cast<TH1F*>( in140->Get("eff_eta"));
      TH1F* effEta200 = dynamic_cast<TH1F*>( in200->Get("eff_eta"));
      TH1F* effEta300 = dynamic_cast<TH1F*>( in300->Get("eff_eta"));
      
      effEta50->SetLineColor(kCyan);
      effEta100->SetLineColor(kBlue);
      effEta140->SetLineColor(kGreen);
      effEta200->SetLineColor(kPink-8);
      effEta300->SetLineColor(kRed);

      effEta50->SetMarkerStyle(20);
      effEta100->SetMarkerStyle(21);
      effEta140->SetMarkerStyle(22);
      effEta200->SetMarkerStyle(29);
      effEta300->SetMarkerStyle(33);

      effEta50->SetMarkerColor(kCyan);
      effEta100->SetMarkerColor(kBlue);
      effEta140->SetMarkerColor(kGreen);
      effEta200->SetMarkerColor(kPink-8);
      effEta300->SetMarkerColor(kRed);

      effEta50->Draw();
      effEta50->SetStats(0);
      effEta50->GetYaxis()->SetTitleOffset(1.2);
      effEta50->GetYaxis()->SetRangeUser(0.0,1.0);

      effEta100->Draw("same");
      effEta100->SetStats(0);
      effEta100->GetYaxis()->SetTitleOffset(1.2);
      effEta100->GetYaxis()->SetRangeUser(0.0,1.0);

      effEta140->Draw("same");
      effEta140->SetStats(0);
      effEta140->GetYaxis()->SetTitleOffset(1.2);
      effEta140->GetYaxis()->SetRangeUser(0.0,1.0);

      effEta200->Draw("same");
      effEta200->SetStats(0);
      effEta200->GetYaxis()->SetTitleOffset(1.2);
      effEta200->GetYaxis()->SetRangeUser(0.0,1.0);

      effEta300->Draw("same");
      effEta300->SetStats(0);
      effEta300->GetYaxis()->SetTitleOffset(1.2);
      effEta300->GetYaxis()->SetRangeUser(0.0,1.0);

      // mg_effEta->GetYaxis()->SetRangeUser(0.0,0.05);
      
      TLegend* leg_effEta = new TLegend(0.15,0.35,0.35,0.15);
      leg_effEta->SetFillColor(0);
      leg_effEta->AddEntry(effEta50, (sample + ": PU 50").c_str(), "lp");
      leg_effEta->AddEntry(effEta100, (sample + ": PU 100").c_str(), "lp");
      leg_effEta->AddEntry(effEta140, (sample + ": PU 140").c_str(), "lp");
      leg_effEta->AddEntry(effEta200, (sample + ": PU 200").c_str(), "lp");
      leg_effEta->AddEntry(effEta300, (sample + ": PU 300").c_str(), "lp");
      
      leg_effEta->Draw();
      
      canv_effEta->Print(("Immagini/" + sample + "_effEta.png").c_str(),"png");
      delete canv_effEta;

      //////// PHI ////////

      TCanvas* canv_effPhi = new TCanvas();

      TH1F* effPhi50 = dynamic_cast<TH1F*>( in50->Get("eff_phi"));
      TH1F* effPhi100 = dynamic_cast<TH1F*>( in100->Get("eff_phi"));
      TH1F* effPhi140 = dynamic_cast<TH1F*>( in140->Get("eff_phi"));
      TH1F* effPhi200 = dynamic_cast<TH1F*>( in200->Get("eff_phi"));
      TH1F* effPhi300 = dynamic_cast<TH1F*>( in300->Get("eff_phi"));
      
      effPhi50->SetLineColor(kCyan);
      effPhi100->SetLineColor(kBlue);
      effPhi140->SetLineColor(kGreen);
      effPhi200->SetLineColor(kPink-8);
      effPhi300->SetLineColor(kRed);

      effPhi50->SetMarkerStyle(20);
      effPhi100->SetMarkerStyle(21);
      effPhi140->SetMarkerStyle(22);
      effPhi200->SetMarkerStyle(29);
      effPhi300->SetMarkerStyle(33);

      effPhi50->SetMarkerColor(kCyan);
      effPhi100->SetMarkerColor(kBlue);
      effPhi140->SetMarkerColor(kGreen);
      effPhi200->SetMarkerColor(kPink-8);
      effPhi300->SetMarkerColor(kRed);

      effPhi50->Draw();
      effPhi50->SetStats(0);
      effPhi50->GetYaxis()->SetTitleOffset(1.2);
      effPhi50->GetYaxis()->SetRangeUser(0.0,1.0);

      effPhi100->Draw("same");
      effPhi100->SetStats(0);
      effPhi100->GetYaxis()->SetTitleOffset(1.2);
      effPhi100->GetYaxis()->SetRangeUser(0.0,1.0);

      effPhi140->Draw("same");
      effPhi140->SetStats(0);
      effPhi140->GetYaxis()->SetTitleOffset(1.2);
      effPhi140->GetYaxis()->SetRangeUser(0.0,1.0);

      effPhi200->Draw("same");
      effPhi200->SetStats(0);
      effPhi200->GetYaxis()->SetTitleOffset(1.2);
      effPhi200->GetYaxis()->SetRangeUser(0.0,1.0);

      effPhi300->Draw("same");
      effPhi300->SetStats(0);
      effPhi300->GetYaxis()->SetTitleOffset(1.2);
      effPhi300->GetYaxis()->SetRangeUser(0.0,1.0);

      // mg_effPhi->GetYaxis()->SetRangeUser(0.0,0.05);
      
      TLegend* leg_effPhi = new TLegend(0.15,0.35,0.35,0.15);
      leg_effPhi->SetFillColor(0);
      leg_effPhi->AddEntry(effPhi50, (sample + ": PU 50").c_str(), "lp");
      leg_effPhi->AddEntry(effPhi100, (sample + ": PU 100").c_str(), "lp");
      leg_effPhi->AddEntry(effPhi140, (sample + ": PU 140").c_str(), "lp");
      leg_effPhi->AddEntry(effPhi200, (sample + ": PU 200").c_str(), "lp");
      leg_effPhi->AddEntry(effPhi300, (sample + ": PU 300").c_str(), "lp");
      
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
    nSiHits100->SetLineColor(kPink -8);
    nSiHits140->SetLineColor(kGreen);
    nSiHits200->SetLineColor(kBlue);
    nSiHits300->SetLineColor(kRed);
    
    canv_nSiHits->cd();
  
    nSiHits50->Draw();
    // nSiHits50->SetStats(0);
    nSiHits50->GetYaxis()->SetTitleOffset(1.2);
    nSiHits50->SetMarkerStyle(20);
    nSiHits50->SetMarkerColor(kCyan);

    // nSiHits100->Draw("same");
    // nSiHits100->SetStats(0);
    // nSiHits100->GetYaxis()->SetTitleOffset(1.2);
    
    // nSiHits140->Draw("same");
    // nSiHits140->SetStats(0);
    // nSiHits140->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHits200->Draw("same");
    // nSiHits200->SetStats(0);
    nSiHits200->GetYaxis()->SetTitleOffset(1.2);
    nSiHits200->SetMarkerStyle(21);
    nSiHits200->SetMarkerColor(kBlue);

    nSiHits300->Draw("same");
    // nSiHits300->SetStats(0);
    nSiHits300->GetYaxis()->SetTitleOffset(1.2);
    nSiHits300->SetMarkerStyle(22);
    nSiHits300->SetMarkerColor(kRed);

    
    TLegend* leg_nSiHits = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSiHits->SetFillColor(0);
    leg_nSiHits->AddEntry(nSiHits50, (sample + ": PU 50").c_str(), "lp");
    // leg_nSiHits->AddEntry(nSiHits100, (sample + ": PU 100").c_str(), "lp");
    // leg_nSiHits->AddEntry(nSiHits140, (sample + ": PU 140").c_str(), "lp");
    leg_nSiHits->AddEntry(nSiHits200, (sample + ": PU 200").c_str(), "lp");
    leg_nSiHits->AddEntry(nSiHits300, (sample + ": PU 300").c_str(), "lp");
    
    leg_nSiHits->Draw();
    
    canv_nSiHits->Print(("Immagini/" + sample + "_nSiHits.png").c_str(),"png");
    delete canv_nSiHits; 

    ////////

    nPixHits50->SetLineColor(kCyan);
    nPixHits100->SetLineColor(kPink -8);
    nPixHits140->SetLineColor(kGreen);
    nPixHits200->SetLineColor(kBlue);
    nPixHits300->SetLineColor(kRed);
    
    canv_nPixHits->cd();
 
    nPixHits50->Draw();
    // nPixHits50->SetStats(0);
    nPixHits50->GetYaxis()->SetTitleOffset(1.2);
    nPixHits50->SetMarkerStyle(20);
    nPixHits50->SetMarkerColor(kCyan);


    // nPixHits100->Draw("same");
    // nPixHits100->SetStats(0);
    // nPixHits100->GetYaxis()->SetTitleOffset(1.2);
    
    // nPixHits140->Draw("same");
    // nPixHits140->SetStats(0);
    // nPixHits140->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHits200->Draw("same");
    // nPixHits200->SetStats(0);
    nPixHits200->GetYaxis()->SetTitleOffset(1.2);
    nPixHits200->SetMarkerStyle(21);
    nPixHits200->SetMarkerColor(kBlue);

    
    nPixHits300->Draw("same");
    // nPixHits300->SetStats(0);
    nPixHits300->GetYaxis()->SetTitleOffset(1.2);
    nPixHits300->SetMarkerStyle(22);
    nPixHits300->SetMarkerColor(kRed);

    
    TLegend* leg_nPixHits = new TLegend(0.65,0.6,0.85,0.4);
    leg_nPixHits->SetFillColor(0);
    leg_nPixHits->AddEntry(nPixHits50, (sample + ": PU 50").c_str(), "lp");
    // leg_nPixHits->AddEntry(nPixHits100, (sample + ": PU 100").c_str(), "lp");
    // leg_nPixHits->AddEntry(nPixHits140, (sample + ": PU 140").c_str(), "lp");
    leg_nPixHits->AddEntry(nPixHits200, (sample + ": PU 200").c_str(), "lp");
    leg_nPixHits->AddEntry(nPixHits300, (sample + ": PU 300").c_str(), "lp");
    
    leg_nPixHits->Draw();
    
    canv_nPixHits->Print(("Immagini/" + sample + "_nPixHits.png").c_str(),"png");
    delete canv_nPixHits;

    ///////////

    nSCTHits50->SetLineColor(kCyan);
    nSCTHits100->SetLineColor(kPink -8);
    nSCTHits140->SetLineColor(kGreen);
    nSCTHits200->SetLineColor(kBlue);
    nSCTHits300->SetLineColor(kRed);
    
    canv_nSCTHits->cd();
 
    nSCTHits50->Draw();
    // nSCTHits50->SetStats(0);
    nSCTHits50->GetYaxis()->SetTitleOffset(1.2);
    nSCTHits50->SetMarkerStyle(20);
    nSCTHits50->SetMarkerColor(kCyan);

    // nSCTHits100->Draw("same");
    // nSCTHits100->SetStats(0);
    // nSCTHits100->GetYaxis()->SetTitleOffset(1.2);
    
    // nSCTHits140->Draw("same");
    // nSCTHits140->SetStats(0);
    // nSCTHits140->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHits200->Draw("same");
    // nSCTHits200->SetStats(0);
    nSCTHits200->GetYaxis()->SetTitleOffset(1.2);
    nSCTHits200->SetMarkerStyle(21);
    nSCTHits200->SetMarkerColor(kBlue);
    
    nSCTHits300->Draw("same");
    // nSCTHits300->SetStats(0);
    nSCTHits300->GetYaxis()->SetTitleOffset(1.2);
    nSCTHits300->SetMarkerStyle(22);
    nSCTHits300->SetMarkerColor(kRed);     

    TLegend* leg_nSCTHits = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSCTHits->SetFillColor(0);
    leg_nSCTHits->AddEntry(nSCTHits50, (sample + ": PU 50").c_str(), "lp");
    // leg_nSCTHits->AddEntry(nSCTHits100, (sample + ": PU 100").c_str(), "lp");
    // leg_nSCTHits->AddEntry(nSCTHits140, (sample + ": PU 140").c_str(), "lp");
    leg_nSCTHits->AddEntry(nSCTHits200, (sample + ": PU 200").c_str(), "lp");
    leg_nSCTHits->AddEntry(nSCTHits300, (sample + ": PU 300").c_str(), "lp");
    
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
    nSiHitsFake100->SetLineColor(kPink -8);
    nSiHitsFake140->SetLineColor(kGreen);
    nSiHitsFake200->SetLineColor(kBlue);
    nSiHitsFake300->SetLineColor(kRed);
    
    canv_nSiHitsFake->cd();
 
    nSiHitsFake50->Draw();
    // nSiHitsFake50->SetStats(0);
    nSiHitsFake50->GetYaxis()->SetTitleOffset(1.2);
    nSiHitsFake50->SetMarkerStyle(20);
    nSiHitsFake50->SetMarkerColor(kCyan);    

    // nSiHitsFake100->Draw("same");
    // nSiHitsFake100->SetStats(0);
    // nSiHitsFake100->GetYaxis()->SetTitleOffset(1.2);
    
    // nSiHitsFake140->Draw("same");
    // nSiHitsFake140->SetStats(0);
    // nSiHitsFake140->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHitsFake200->Draw("same");
    // nSiHitsFake200->SetStats(0);
    nSiHitsFake200->GetYaxis()->SetTitleOffset(1.2);
    nSiHitsFake200->SetMarkerStyle(21);
    nSiHitsFake200->SetMarkerColor(kBlue);    

    
    nSiHitsFake300->Draw("same");
    // nSiHitsFake300->SetStats(0);
    nSiHitsFake300->GetYaxis()->SetTitleOffset(1.2);
    nSiHitsFake300->SetMarkerStyle(22);
    nSiHitsFake300->SetMarkerColor(kRed);    

     
    TLegend* leg_nSiHitsFake = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSiHitsFake->SetFillColor(0);
    leg_nSiHitsFake->AddEntry(nSiHitsFake50, (sample + ": PU 50").c_str(), "lp");
    // leg_nSiHitsFake->AddEntry(nSiHitsFake100, (sample + ": PU 100").c_str(), "lp");
    // leg_nSiHitsFake->AddEntry(nSiHitsFake140, (sample + ": PU 140").c_str(), "lp");
    leg_nSiHitsFake->AddEntry(nSiHitsFake200, (sample + ": PU 200").c_str(), "lp");
    leg_nSiHitsFake->AddEntry(nSiHitsFake300, (sample + ": PU 300").c_str(), "lp");
    
    leg_nSiHitsFake->Draw();
    
    canv_nSiHitsFake->Print(("Immagini/" + sample + "_nSiHitsFake.png").c_str(),"png");
    delete canv_nSiHitsFake; 

    ////////

    nPixHitsFake50->SetLineColor(kCyan);
    nPixHitsFake100->SetLineColor(kPink -8);
    nPixHitsFake140->SetLineColor(kGreen);
    nPixHitsFake200->SetLineColor(kBlue);
    nPixHitsFake300->SetLineColor(kRed);
    
    canv_nPixHitsFake->cd();
 
    nPixHitsFake50->Draw();
    // nPixHitsFake50->SetStats(0);
    nPixHitsFake50->GetYaxis()->SetTitleOffset(1.2);
    nPixHitsFake50->SetMarkerStyle(20);
    nPixHitsFake50->SetMarkerColor(kCyan);    

    // nPixHitsFake100->Draw("same");
    // nPixHitsFake100->SetStats(0);
    // nPixHitsFake100->GetYaxis()->SetTitleOffset(1.2);
    
    // nPixHitsFake140->Draw("same");
    // nPixHitsFake140->SetStats(0);
    // nPixHitsFake140->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHitsFake200->Draw("same");
    // nPixHitsFake200->SetStats(0);
    nPixHitsFake200->GetYaxis()->SetTitleOffset(1.2);
    nPixHitsFake200->SetMarkerStyle(21);
    nPixHitsFake200->SetMarkerColor(kBlue);    
    
    nPixHitsFake300->Draw("same");
    // nPixHitsFake300->SetStats(0);
    nPixHitsFake300->GetYaxis()->SetTitleOffset(1.2);
    nPixHitsFake300->SetMarkerStyle(22);
    nPixHitsFake300->SetMarkerColor(kRed);    
    
    TLegend* leg_nPixHitsFake = new TLegend(0.65,0.6,0.85,0.4);
    leg_nPixHitsFake->SetFillColor(0);
    leg_nPixHitsFake->AddEntry(nPixHitsFake50, (sample + ": PU 50").c_str(), "lp");
    // leg_nPixHitsFake->AddEntry(nPixHitsFake100, (sample + ": PU 100").c_str(), "lp");
    // leg_nPixHitsFake->AddEntry(nPixHitsFake140, (sample + ": PU 140").c_str(), "lp");
    leg_nPixHitsFake->AddEntry(nPixHitsFake200, (sample + ": PU 200").c_str(), "lp");
    leg_nPixHitsFake->AddEntry(nPixHitsFake300, (sample + ": PU 300").c_str(), "lp");
    
    leg_nPixHitsFake->Draw();
    
    canv_nPixHitsFake->Print(("Immagini/" + sample + "_nPixHitsFake.png").c_str(),"png");
    delete canv_nPixHitsFake;

    ///////////

    nSCTHitsFake50->SetLineColor(kCyan);
    nSCTHitsFake100->SetLineColor(kPink -8);
    nSCTHitsFake140->SetLineColor(kGreen);
    nSCTHitsFake200->SetLineColor(kBlue);
    nSCTHitsFake300->SetLineColor(kRed);
    
    canv_nSCTHitsFake->cd();
 
    nSCTHitsFake50->Draw();
    // nSCTHitsFake50->SetStats(0);
    nSCTHitsFake50->GetYaxis()->SetTitleOffset(1.2);
    nSCTHitsFake50->SetMarkerStyle(20);
    nSCTHitsFake50->SetMarkerColor(kCyan);    

    // nSCTHitsFake100->Draw("same");
    // nSCTHitsFake100->SetStats(0);
    // nSCTHitsFake100->GetYaxis()->SetTitleOffset(1.2);
    
    // nSCTHitsFake140->Draw("same");
    // nSCTHitsFake140->SetStats(0);
    // nSCTHitsFake140->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHitsFake200->Draw("same");
    // nSCTHitsFake200->SetStats(0);
    nSCTHitsFake200->GetYaxis()->SetTitleOffset(1.2);
    nSCTHitsFake200->SetMarkerStyle(21);
    nSCTHitsFake200->SetMarkerColor(kBlue);    
    
    nSCTHitsFake300->Draw("same");
    // nSCTHitsFake300->SetStats(0);
    nSCTHitsFake300->GetYaxis()->SetTitleOffset(1.2);
    nSCTHitsFake300->SetMarkerStyle(22);
    nSCTHitsFake300->SetMarkerColor(kRed);         

    TLegend* leg_nSCTHitsFake = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSCTHitsFake->SetFillColor(0);
    leg_nSCTHitsFake->AddEntry(nSCTHitsFake50, (sample + ": PU 50").c_str(), "lp");
    // leg_nSCTHitsFake->AddEntry(nSCTHitsFake100, (sample + ": PU 100").c_str(), "lp");
    // leg_nSCTHitsFake->AddEntry(nSCTHitsFake140, (sample + ": PU 140").c_str(), "lp");
    leg_nSCTHitsFake->AddEntry(nSCTHitsFake200, (sample + ": PU 200").c_str(), "lp");
    leg_nSCTHitsFake->AddEntry(nSCTHitsFake300, (sample + ": PU 300").c_str(), "lp");
    
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
    nSiHitsTrue100->SetLineColor(kPink -8);
    nSiHitsTrue140->SetLineColor(kGreen);
    nSiHitsTrue200->SetLineColor(kBlue);
    nSiHitsTrue300->SetLineColor(kRed);
    
    canv_nSiHitsTrue->cd();
 
    nSiHitsTrue50->Draw();
    // nSiHitsTrue50->SetStats(0);
    nSiHitsTrue50->GetYaxis()->SetTitleOffset(1.2);
    nSiHitsTrue50->SetMarkerStyle(20);
    nSiHitsTrue50->SetMarkerColor(kCyan);    
    
    // nSiHitsTrue100->Draw("same");
    // nSiHitsTrue100->SetStats(0);
    // nSiHitsTrue100->GetYaxis()->SetTitleOffset(1.2);
    
    // nSiHitsTrue140->Draw("same");
    // nSiHitsTrue140->SetStats(0);
    // nSiHitsTrue140->GetYaxis()->SetTitleOffset(1.2);
    
    nSiHitsTrue200->Draw("same");
    // nSiHitsTrue200->SetStats(0);
    nSiHitsTrue200->GetYaxis()->SetTitleOffset(1.2);
    nSiHitsTrue200->SetMarkerStyle(21);
    nSiHitsTrue200->SetMarkerColor(kBlue);    
    
    nSiHitsTrue300->Draw("same");
    // nSiHitsTrue300->SetStats(0);
    nSiHitsTrue300->GetYaxis()->SetTitleOffset(1.2);
    nSiHitsTrue300->SetMarkerStyle(22);
    nSiHitsTrue300->SetMarkerColor(kRed);         

    TLegend* leg_nSiHitsTrue = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSiHitsTrue->SetFillColor(0);
    leg_nSiHitsTrue->AddEntry(nSiHitsTrue50, (sample + ": PU 50").c_str(), "lp");
    // leg_nSiHitsTrue->AddEntry(nSiHitsTrue100, (sample + ": PU 100").c_str(), "lp");
    // leg_nSiHitsTrue->AddEntry(nSiHitsTrue140, (sample + ": PU 140").c_str(), "lp");
    leg_nSiHitsTrue->AddEntry(nSiHitsTrue200, (sample + ": PU 200").c_str(), "lp");
    leg_nSiHitsTrue->AddEntry(nSiHitsTrue300, (sample + ": PU 300").c_str(), "lp");
    
    leg_nSiHitsTrue->Draw();
    
    canv_nSiHitsTrue->Print(("Immagini/" + sample + "_nSiHitsTrue.png").c_str(),"png");
    delete canv_nSiHitsTrue; 

    ////////

    nPixHitsTrue50->SetLineColor(kCyan);
    nPixHitsTrue100->SetLineColor(kPink -8);
    nPixHitsTrue140->SetLineColor(kGreen);
    nPixHitsTrue200->SetLineColor(kBlue);
    nPixHitsTrue300->SetLineColor(kRed);
    
    canv_nPixHitsTrue->cd();
 
    nPixHitsTrue50->Draw();
    // nPixHitsTrue50->SetStats(0);
    nPixHitsTrue50->GetYaxis()->SetTitleOffset(1.2);
    nPixHitsTrue50->SetMarkerStyle(20);
    nPixHitsTrue50->SetMarkerColor(kCyan);        

    // nPixHitsTrue100->Draw("same");
    // nPixHitsTrue100->SetStats(0);
    // nPixHitsTrue100->GetYaxis()->SetTitleOffset(1.2);
    
    // nPixHitsTrue140->Draw("same");
    // nPixHitsTrue140->SetStats(0);
    // nPixHitsTrue140->GetYaxis()->SetTitleOffset(1.2);
    
    nPixHitsTrue200->Draw("same");
    // nPixHitsTrue200->SetStats(0);
    nPixHitsTrue200->GetYaxis()->SetTitleOffset(1.2);
    nPixHitsTrue200->SetMarkerStyle(21);
    nPixHitsTrue200->SetMarkerColor(kBlue);        
    
    nPixHitsTrue300->Draw("same");
    // nPixHitsTrue300->SetStats(0);
    nPixHitsTrue300->GetYaxis()->SetTitleOffset(1.2);
    nPixHitsTrue300->SetMarkerStyle(22);
    nPixHitsTrue300->SetMarkerColor(kRed);        
    
    TLegend* leg_nPixHitsTrue = new TLegend(0.65,0.6,0.85,0.4);
    leg_nPixHitsTrue->SetFillColor(0);
    leg_nPixHitsTrue->AddEntry(nPixHitsTrue50, (sample + ": PU 50").c_str(), "lp");
    // leg_nPixHitsTrue->AddEntry(nPixHitsTrue100, (sample + ": PU 100").c_str(), "lp");
    // leg_nPixHitsTrue->AddEntry(nPixHitsTrue140, (sample + ": PU 140").c_str(), "lp");
    leg_nPixHitsTrue->AddEntry(nPixHitsTrue200, (sample + ": PU 200").c_str(), "lp");
    leg_nPixHitsTrue->AddEntry(nPixHitsTrue300, (sample + ": PU 300").c_str(), "lp");
    
    leg_nPixHitsTrue->Draw();
    
    canv_nPixHitsTrue->Print(("Immagini/" + sample + "_nPixHitsTrue.png").c_str(),"png");
    delete canv_nPixHitsTrue;

    ///////////

    nSCTHitsTrue50->SetLineColor(kCyan);
    nSCTHitsTrue100->SetLineColor(kPink -8);
    nSCTHitsTrue140->SetLineColor(kGreen);
    nSCTHitsTrue200->SetLineColor(kBlue);
    nSCTHitsTrue300->SetLineColor(kRed);
    
    canv_nSCTHitsTrue->cd();
 

    nSCTHitsTrue50->Draw();
    // nSCTHitsTrue50->SetStats(0);
    nSCTHitsTrue50->GetYaxis()->SetTitleOffset(1.2);
    nSCTHitsTrue50->SetMarkerStyle(20);
    nSCTHitsTrue50->SetMarkerColor(kCyan);        

    // nSCTHitsTrue100->Draw("same");
    // nSCTHitsTrue100->SetStats(0);
    // nSCTHitsTrue100->GetYaxis()->SetTitleOffset(1.2);
    
    // nSCTHitsTrue140->Draw("same");
    // nSCTHitsTrue140->SetStats(0);
    // nSCTHitsTrue140->GetYaxis()->SetTitleOffset(1.2);
    
    nSCTHitsTrue200->Draw("same");
    // nSCTHitsTrue200->SetStats(0);
    nSCTHitsTrue200->GetYaxis()->SetTitleOffset(1.2);
    nSCTHitsTrue200->SetMarkerStyle(21);
    nSCTHitsTrue300->SetMarkerColor(kBlue);        
    
    nSCTHitsTrue300->Draw("same");
    // nSCTHitsTrue300->SetStats(0);
    nSCTHitsTrue300->GetYaxis()->SetTitleOffset(1.2);
    nSCTHitsTrue300->SetMarkerStyle(22);
    nSCTHitsTrue300->SetMarkerColor(kRed);        
  
    TLegend* leg_nSCTHitsTrue = new TLegend(0.65,0.6,0.85,0.4);
    leg_nSCTHitsTrue->SetFillColor(0);
    leg_nSCTHitsTrue->AddEntry(nSCTHitsTrue50, (sample + ": PU 50").c_str(), "lp");
    // leg_nSCTHitsTrue->AddEntry(nSCTHitsTrue100, (sample + ": PU 100").c_str(), "lp");
    // leg_nSCTHitsTrue->AddEntry(nSCTHitsTrue140, (sample + ": PU 140").c_str(), "lp");
    leg_nSCTHitsTrue->AddEntry(nSCTHitsTrue200, (sample + ": PU 200").c_str(), "lp");
    leg_nSCTHitsTrue->AddEntry(nSCTHitsTrue300, (sample + ": PU 300").c_str(), "lp");
    
    leg_nSCTHitsTrue->Draw();
    
    canv_nSCTHitsTrue->Print(("Immagini/" + sample + "_nSCTHitsTrue.png").c_str(),"png");
    delete canv_nSCTHitsTrue;


  
  }
}
