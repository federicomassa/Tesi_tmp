#include "TFile.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TCanvas.h"

void eff_all() {

  TFile* in50 = new TFile("./mu100_pu50-100-200-300/hist-mu100pu50.root");
  TFile* in100 = new TFile("./mu100_pu50-100-200-300/hist-mu100pu100.root");
  TFile* in200 = new TFile("./mu100_pu50-100-200-300/hist-mu100pu200.root");
  TFile* in300 = new TFile("./mu100_pu50-100-200-300/hist-mu100pu300.root");


  TGraphErrors* biasPt50 = (TGraphErrors*) in50->Get("biasPt_Eta");
  TGraphErrors* biasPt100 = (TGraphErrors*) in100->Get("biasPt_Eta");
  TGraphErrors* biasPt200 = (TGraphErrors*) in200->Get("biasPt_Eta");
  TGraphErrors* biasPt300 = (TGraphErrors*) in300->Get("biasPt_Eta");

  TMultiGraph* mg = new TMultiGraph();

  biasPt50->SetLineColor(kBlue);
  biasPt100->SetLineColor(kCyan);
  biasPt200->SetLineColor(kGreen);
  biasPt300->SetLineColor(kRed);

  mg->Add(biasPt50);
  mg->Add(biasPt100);
  mg->Add(biasPt200);
  mg->Add(biasPt300);

  mg->SetTitle("#sigma(p_{T}) vs |#eta| - Mu 100 GeV; |#eta|; #sigma(p_{T})");

  TCanvas* canv_pt = new TCanvas();
  mg->Draw("APE");
  mg->GetYaxis()->SetRangeUser(0.0,4500.0);

  TLegend* leg = new TLegend(0.5,0.65,0.88,0.85);
  leg->SetFillColor(0);
  leg->AddEntry(biasPt50, "PU 50", "lp");
  leg->AddEntry(biasPt100, "PU 100", "lp");
  leg->AddEntry(biasPt200, "PU 200", "lp");
  leg->AddEntry(biasPt300, "PU 300", "lp");
  
  leg->Draw();


  ////////////////////////////////

  TGraphErrors* biasD050 = (TGraphErrors*) in50->Get("biasD0_Eta");
  TGraphErrors* biasD0100 = (TGraphErrors*) in100->Get("biasD0_Eta");
  TGraphErrors* biasD0200 = (TGraphErrors*) in200->Get("biasD0_Eta");
  TGraphErrors* biasD0300 = (TGraphErrors*) in300->Get("biasD0_Eta");

  TMultiGraph* mg2 = new TMultiGraph();

  biasD050->SetLineColor(kBlue);
  biasD0100->SetLineColor(kCyan);
  biasD0200->SetLineColor(kGreen);
  biasD0300->SetLineColor(kRed);

  mg2->Add(biasD050);
  mg2->Add(biasD0100);
  mg2->Add(biasD0200);
  mg2->Add(biasD0300);

  mg2->SetTitle("#sigma(D0) vs |#eta| - Mu 100 GeV; |#eta|; #sigma(D0)");

  TCanvas* canv_d0 = new TCanvas();
  mg2->Draw("APE");
  mg2->GetYaxis()->SetRangeUser(0.0,0.5);

  TLegend* leg2 = new TLegend(0.5,0.65,0.88,0.85);

  leg2->SetFillColor(0);
  leg2->AddEntry(biasD050, "PU 50", "lp");
  leg2->AddEntry(biasD0100, "PU 100", "lp");
  leg2->AddEntry(biasD0200, "PU 200", "lp");
  leg2->AddEntry(biasD0300, "PU 300", "lp");  
  leg2->Draw();


  

}
