// sample pt 15,50,100 GeV, fixed pileup = 50
// makes multigraph with pt and d0 resolution

#include "TFile.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TCanvas.h"

void eff_all() {

  TFile* in15 = new TFile("./pi15-50-100_pu50/hist-pi15pu50.root");
  TFile* in50 = new TFile("./pi15-50-100_pu50/hist-pi50pu50.root");
  TFile* in100 = new TFile("./pi15-50-100_pu50/hist-pi100pu50.root");

  TGraphErrors* biasPt15 = (TGraphErrors*) in15->Get("biasPt_Eta");
  TGraphErrors* biasPt50 = (TGraphErrors*) in50->Get("biasPt_Eta");
  TGraphErrors* biasPt100 = (TGraphErrors*) in100->Get("biasPt_Eta");

  TMultiGraph* mg = new TMultiGraph();

  biasPt15->SetLineColor(kBlue);
  biasPt50->SetLineColor(kRed);
  biasPt100->SetLineColor(kGreen);

  mg->Add(biasPt15);
  mg->Add(biasPt50);
  mg->Add(biasPt100);


  mg->SetTitle("#sigma(p_{T}) vs |#eta| - Pi PU 50; |#eta|; #sigma(p_{T}) [MeV]");

  TCanvas* canv_pt = new TCanvas();
  mg->Draw("APE");
  mg->GetYaxis()->SetRangeUser(0.0,4500.0);

  TLegend* leg = new TLegend(0.5,0.65,0.88,0.85);
  leg->SetFillColor(0);
  leg->AddEntry(biasPt15, "PT 15 GeV", "lp");
  leg->AddEntry(biasPt50, "PT 50 GeV", "lp");
  leg->AddEntry(biasPt100, "PT 100 GeV", "lp");

  
  leg->Draw();


  ////////////////////////////////

  TGraphErrors* biasD015 = (TGraphErrors*) in15->Get("biasD0_Eta");
  TGraphErrors* biasD050 = (TGraphErrors*) in50->Get("biasD0_Eta");
  TGraphErrors* biasD0100 = (TGraphErrors*) in100->Get("biasD0_Eta");


  TMultiGraph* mg2 = new TMultiGraph();

  biasD015->SetLineColor(kBlue);
  biasD050->SetLineColor(kRed);
  biasD0100->SetLineColor(kGreen);

  mg2->Add(biasD015);
  mg2->Add(biasD050);
  mg2->Add(biasD0100);


  mg2->SetTitle("#sigma(D0) vs |#eta| - PU 50; |#eta|; #sigma(D0) [mm]");

  TCanvas* canv_d0 = new TCanvas();
  mg2->Draw("APE");
  mg2->GetYaxis()->SetRangeUser(0.0,0.05);

  TLegend* leg2 = new TLegend(0.5,0.65,0.88,0.85);

  leg2->SetFillColor(0);
  leg2->AddEntry(biasD015, "PT 15 GeV", "lp");
  leg2->AddEntry(biasD050, "PT 50 GeV", "lp");
  leg2->AddEntry(biasD0100, "PT 100 GeV", "lp");

  leg2->Draw();


  

}
