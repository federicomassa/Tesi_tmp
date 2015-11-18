#include "TFile.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TCanvas.h"

void eff_all() {

  TFile* in50 = new TFile("./pi100_50-140-200-300/hist-100pu50.root");
  TFile* in140 = new TFile("./pi100_50-140-200-300/hist-100pu140.root");
  TFile* in200 = new TFile("./pi100_50-140-200-300/hist-100pu200.root");
  TFile* in300 = new TFile("./pi100_50-140-200-300/hist-100pu300.root");


  TGraphErrors* biasPt50 = (TGraphErrors*) in50->Get("biasPt_Eta");
  TGraphErrors* biasPt140 = (TGraphErrors*) in140->Get("biasPt_Eta");
  TGraphErrors* biasPt200 = (TGraphErrors*) in200->Get("biasPt_Eta");
  TGraphErrors* biasPt300 = (TGraphErrors*) in300->Get("biasPt_Eta");

  TMultiGraph* mg = new TMultiGraph();

  biasPt50->SetLineColor(kBlue);
  biasPt140->SetLineColor(kCyan);
  biasPt200->SetLineColor(kGreen);
  biasPt300->SetLineColor(kRed);

  mg->Add(biasPt50);
  mg->Add(biasPt140);
  mg->Add(biasPt200);
  mg->Add(biasPt300);

  mg->SetTitle("#sigma(p_{T}) vs |#eta| - Pi 100 GeV; |#eta|; #sigma(p_{T})");

  TCanvas* canv_pt = new TCanvas();
  mg->Draw("APE");
  mg->GetYaxis()->SetRangeUser(0.0,4500.0);

  TLegend* leg = new TLegend(0.5,0.65,0.88,0.85);
  leg->SetFillColor(0);
  leg->AddEntry(biasPt50, "PU 50", "lp");
  leg->AddEntry(biasPt140, "PU 140", "lp");
  leg->AddEntry(biasPt200, "PU 200", "lp");
  leg->AddEntry(biasPt300, "PU 300", "lp");
  
  leg->Draw();


  ////////////////////////////////

  TGraphErrors* biasD050 = (TGraphErrors*) in50->Get("biasD0_Eta");
  TGraphErrors* biasD0140 = (TGraphErrors*) in140->Get("biasD0_Eta");
  TGraphErrors* biasD0200 = (TGraphErrors*) in200->Get("biasD0_Eta");
  TGraphErrors* biasD0300 = (TGraphErrors*) in300->Get("biasD0_Eta");

  TMultiGraph* mg2 = new TMultiGraph();

  biasD050->SetLineColor(kBlue);
  biasD0140->SetLineColor(kCyan);
  biasD0200->SetLineColor(kGreen);
  biasD0300->SetLineColor(kRed);

  mg2->Add(biasD050);
  mg2->Add(biasD0140);
  mg2->Add(biasD0200);
  mg2->Add(biasD0300);

  mg2->SetTitle("#sigma(D0) vs |#eta| - Pi 100 GeV; |#eta|; #sigma(D0)");

  TCanvas* canv_d0 = new TCanvas();
  mg2->Draw("APE");
  mg2->GetYaxis()->SetRangeUser(0.0,0.5);

  TLegend* leg2 = new TLegend(0.5,0.65,0.88,0.85);

  leg2->SetFillColor(0);
  leg2->AddEntry(biasD050, "PU 50", "lp");
  leg2->AddEntry(biasD0140, "PU 140", "lp");
  leg2->AddEntry(biasD0200, "PU 200", "lp");
  leg2->AddEntry(biasD0300, "PU 300", "lp");  
  leg2->Draw();


  

}
