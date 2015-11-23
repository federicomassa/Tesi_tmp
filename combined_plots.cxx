// Combines two samples and produces plots.

#include <string>
#include <sstream>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <iostream>

#define CHECK_PTR(PTR) \
  if (PTR == 0) std::cout << "ERROR: " << #PTR << \
		  "was not correctly recovered" << std::endl;


void combined_plots(string sample1, string sample2, bool SaveBiasPlots = false, unsigned int pileup1 = 50, unsigned int pileup2 = 200) {

  string path1 = sample1 + "/hist-" + sample1 + "pu";
  string path2 = sample2 + "/hist-" + sample2 + "pu";
  
  string pileup1_str = std::to_string(pileup1);
  string pileup2_str = std::to_string(pileup2);

  TFile* sample1_Pu1 = new TFile((path1+pileup1_str+".root").c_str());
  TFile* sample1_Pu2 = new TFile((path1+pileup2_str+".root").c_str());

  TFile* sample2_Pu1 = new TFile((path2+pileup1_str+".root").c_str());
  TFile* sample2_Pu2 = new TFile((path2+pileup2_str+".root").c_str());

  if (SaveBiasPlots) {
    //////////// BIAS PLOTS ///////////////

    TGraphErrors* biasPtVsEtaPu1_sample1 = dynamic_cast<TGraphErrors*>(sample1_Pu1->Get("biasPt_Eta"));
    CHECK_PTR(biasPtVsEtaPu1_sample1);

    TGraphErrors* biasQPtVsEtaPu1_sample1 = dynamic_cast<TGraphErrors*>(sample1_Pu1->Get("biasQPt_Eta"));
    CHECK_PTR(biasQPtVsEtaPu1_sample1);

    TGraphErrors* biasD0VsEtaPu1_sample1 = dynamic_cast<TGraphErrors*>(sample1_Pu1->Get("biasD0_Eta"));
    CHECK_PTR(biasD0VsEtaPu1_sample1);    

    TGraphErrors* biasPhiVsEtaPu1_sample1 = dynamic_cast<TGraphErrors*>(sample1_Pu1->Get("biasPhi_Eta"));
    CHECK_PTR(biasPhiVsEtaPu1_sample1);    

    /////

    TGraphErrors* biasPtVsEtaPu2_sample1 = dynamic_cast<TGraphErrors*>(sample1_Pu2->Get("biasPt_Eta"));
    CHECK_PTR(biasPtVsEtaPu2_sample1);

    TGraphErrors* biasQPtVsEtaPu2_sample1 = dynamic_cast<TGraphErrors*>(sample1_Pu2->Get("biasQPt_Eta"));
    CHECK_PTR(biasQPtVsEtaPu2_sample1);

    TGraphErrors* biasD0VsEtaPu2_sample1 = dynamic_cast<TGraphErrors*>(sample1_Pu2->Get("biasD0_Eta"));
    CHECK_PTR(biasD0VsEtaPu2_sample1);    

    TGraphErrors* biasPhiVsEtaPu2_sample1 = dynamic_cast<TGraphErrors*>(sample1_Pu2->Get("biasPhi_Eta"));
    CHECK_PTR(biasPhiVsEtaPu2_sample1);    
  
    ////////

    TGraphErrors* biasPtVsEtaPu1_sample2 = dynamic_cast<TGraphErrors*>(sample2_Pu1->Get("biasPt_Eta"));
    CHECK_PTR(biasPtVsEtaPu1_sample2);

    TGraphErrors* biasQPtVsEtaPu1_sample2 = dynamic_cast<TGraphErrors*>(sample2_Pu1->Get("biasQPt_Eta"));
    CHECK_PTR(biasQPtVsEtaPu1_sample2);

    TGraphErrors* biasD0VsEtaPu1_sample2 = dynamic_cast<TGraphErrors*>(sample2_Pu1->Get("biasD0_Eta"));
    CHECK_PTR(biasD0VsEtaPu1_sample2);    

    TGraphErrors* biasPhiVsEtaPu1_sample2 = dynamic_cast<TGraphErrors*>(sample2_Pu1->Get("biasPhi_Eta"));
    CHECK_PTR(biasPhiVsEtaPu1_sample2);    


    TGraphErrors* biasPtVsEtaPu2_sample2 = dynamic_cast<TGraphErrors*>(sample2_Pu2->Get("biasPt_Eta"));
    CHECK_PTR(biasPtVsEtaPu2_sample2);

    TGraphErrors* biasQPtVsEtaPu2_sample2 = dynamic_cast<TGraphErrors*>(sample2_Pu2->Get("biasQPt_Eta"));
    CHECK_PTR(biasQPtVsEtaPu2_sample2);

    TGraphErrors* biasD0VsEtaPu2_sample2 = dynamic_cast<TGraphErrors*>(sample2_Pu2->Get("biasD0_Eta"));
    CHECK_PTR(biasD0VsEtaPu2_sample2);    

    TGraphErrors* biasPhiVsEtaPu2_sample2 = dynamic_cast<TGraphErrors*>(sample2_Pu2->Get("biasPhi_Eta"));
    CHECK_PTR(biasPhiVsEtaPu2_sample2);    


    /////// DRAW BIAS PT /////

    TCanvas* canv_Pt = new TCanvas();

    TMultiGraph* mg_Pt = new TMultiGraph;
    mg_Pt   -> SetName("biasPtVsEta_combined");
    mg_Pt   -> SetTitle("#sigma(p_{T}) vs |#eta|;truth |#eta|;#sigma(p_{T}) [MeV]");

    biasPtVsEtaPu1_sample1     -> SetLineColor(kRed);
    biasPtVsEtaPu2_sample1     -> SetLineColor(kBlue);
    biasPtVsEtaPu1_sample2     -> SetLineColor(kRed);
    biasPtVsEtaPu2_sample2     -> SetLineColor(kBlue);
  
    biasPtVsEtaPu1_sample1     ->SetMarkerStyle(1);
    biasPtVsEtaPu2_sample1    ->SetMarkerStyle(1);
    biasPtVsEtaPu1_sample2     ->SetMarkerStyle(33);
    biasPtVsEtaPu2_sample2    ->SetMarkerStyle(33);   

    biasPtVsEtaPu1_sample1     ->SetMarkerColor(kRed);
    biasPtVsEtaPu2_sample1    ->SetMarkerColor(kBlue);
    biasPtVsEtaPu1_sample2     ->SetMarkerColor(kRed);
    biasPtVsEtaPu2_sample2    ->SetMarkerColor(kBlue);   

    mg_Pt->Add(biasPtVsEtaPu1_sample1);
    mg_Pt->Add(biasPtVsEtaPu2_sample1);
    mg_Pt->Add(biasPtVsEtaPu1_sample2);
    mg_Pt->Add(biasPtVsEtaPu2_sample2);

    mg_Pt     -> Draw("APE");
    mg_Pt     -> GetYaxis() -> SetTitleOffset(1.2);
    mg_Pt     -> GetYaxis() -> SetRangeUser(0.0,5000);

    TLegend* leg_Pt = new TLegend(0.15,0.85,0.4,0.6);
    leg_Pt->AddEntry(biasPtVsEtaPu1_sample1, (sample1 + "pu" + pileup1_str).c_str(), "lp");
    leg_Pt->AddEntry(biasPtVsEtaPu2_sample1, (sample1 + "pu" + pileup2_str).c_str(), "lp");
    leg_Pt->AddEntry(biasPtVsEtaPu1_sample2, (sample2 + "pu" + pileup1_str).c_str(), "lp");
    leg_Pt->AddEntry(biasPtVsEtaPu2_sample2, (sample2 + "pu" + pileup2_str).c_str(), "lp");

    leg_Pt  -> SetFillColor(0);
    leg_Pt  -> Draw();

    canv_Pt -> Print(("Immagini/" + sample1 + sample2 + "pu" + pileup1_str + pileup2_str + "_biasPtVsEta.png").c_str(), "png");
    delete canv_Pt;

    /////// DRAW BIAS QPT /////

    TCanvas* canv_QPt = new TCanvas();

    TMultiGraph* mg_QPt = new TMultiGraph;
    mg_QPt   -> SetName("biasQPtVsEta_combined");
    mg_QPt   -> SetTitle("#sigma(q/p_{T}) vs |#eta|;truth |#eta|;p_{T} x #sigma(q/p_{T})");

    biasQPtVsEtaPu1_sample1     ->SetLineColor(kRed);
    biasQPtVsEtaPu2_sample1    ->SetLineColor(kBlue);
    biasQPtVsEtaPu1_sample2     ->SetLineColor(kRed);
    biasQPtVsEtaPu2_sample2    ->SetLineColor(kBlue);
  
    biasQPtVsEtaPu1_sample1     ->SetMarkerStyle(1);
    biasQPtVsEtaPu2_sample1    ->SetMarkerStyle(1);
    biasQPtVsEtaPu1_sample2     ->SetMarkerStyle(33);
    biasQPtVsEtaPu2_sample2    ->SetMarkerStyle(33);   

    biasQPtVsEtaPu1_sample1     ->SetMarkerColor(kRed);
    biasQPtVsEtaPu2_sample1    ->SetMarkerColor(kBlue);
    biasQPtVsEtaPu1_sample2     ->SetMarkerColor(kRed);
    biasQPtVsEtaPu2_sample2    ->SetMarkerColor(kBlue);

    mg_QPt->Add(biasQPtVsEtaPu1_sample1);
    mg_QPt->Add(biasQPtVsEtaPu2_sample1);
    mg_QPt->Add(biasQPtVsEtaPu1_sample2);
    mg_QPt->Add(biasQPtVsEtaPu2_sample2);

    mg_QPt     -> Draw("APE");
    mg_QPt     -> GetYaxis() -> SetTitleOffset(1.2);
    mg_QPt     -> GetYaxis() -> SetRangeUser(0.0,0.2);

    TLegend* leg_QPt = new TLegend(0.15,0.85,0.4,0.6);
    leg_QPt->AddEntry(biasQPtVsEtaPu1_sample1, (sample1 + "pu" + pileup1_str).c_str(), "lp");
    leg_QPt->AddEntry(biasQPtVsEtaPu2_sample1, (sample1 + "pu" + pileup2_str).c_str(), "lp");
    leg_QPt->AddEntry(biasQPtVsEtaPu1_sample2, (sample2 + "pu" + pileup1_str).c_str(), "lp");
    leg_QPt->AddEntry(biasQPtVsEtaPu2_sample2, (sample2 + "pu" + pileup2_str).c_str(), "lp");

    leg_QPt  -> SetFillColor(0);
    leg_QPt  -> Draw();

    canv_QPt -> Print(("Immagini/" + sample1 + sample2 + "pu" + pileup1_str + pileup2_str + "_biasQPtVsEta.png").c_str(), "png");
    delete canv_QPt;

    /////// DRAW BIAS D0 /////

    TCanvas* canv_D0 = new TCanvas();

    TMultiGraph* mg_D0 = new TMultiGraph;
    mg_D0   -> SetName("biasD0VsEta_combined");
    mg_D0   -> SetTitle("#sigma(D0) vs |#eta|;truth |#eta|;#sigma(D0) [mm]");

    biasD0VsEtaPu1_sample1     ->SetLineColor(kRed);
    biasD0VsEtaPu2_sample1    ->SetLineColor(kBlue);
    biasD0VsEtaPu1_sample2     ->SetLineColor(kRed);
    biasD0VsEtaPu2_sample2    ->SetLineColor(kBlue);

    biasD0VsEtaPu1_sample1     ->SetMarkerStyle(1);
    biasD0VsEtaPu2_sample1    ->SetMarkerStyle(1);
    biasD0VsEtaPu1_sample2     ->SetMarkerStyle(33);
    biasD0VsEtaPu2_sample2    ->SetMarkerStyle(33);   

    biasD0VsEtaPu1_sample1     ->SetMarkerColor(kRed);
    biasD0VsEtaPu2_sample1    ->SetMarkerColor(kBlue);
    biasD0VsEtaPu1_sample2     ->SetMarkerColor(kRed);
    biasD0VsEtaPu2_sample2    ->SetMarkerColor(kBlue);
  
    mg_D0->Add(biasD0VsEtaPu1_sample1);
    mg_D0->Add(biasD0VsEtaPu2_sample1);
    mg_D0->Add(biasD0VsEtaPu1_sample2);
    mg_D0->Add(biasD0VsEtaPu2_sample2);

    mg_D0     -> Draw("APE");
    mg_D0     -> GetYaxis() -> SetTitleOffset(1.2);
    mg_D0     -> GetYaxis() -> SetRangeUser(0.0,0.08);

    TLegend* leg_D0 = new TLegend(0.15,0.85,0.4,0.6);
    leg_D0->AddEntry(biasD0VsEtaPu1_sample1, (sample1 + "pu" + pileup1_str).c_str(), "lp");
    leg_D0->AddEntry(biasD0VsEtaPu2_sample1, (sample1 + "pu" + pileup2_str).c_str(), "lp");
    leg_D0->AddEntry(biasD0VsEtaPu1_sample2, (sample2 + "pu" + pileup1_str).c_str(), "lp");
    leg_D0->AddEntry(biasD0VsEtaPu2_sample2, (sample2 + "pu" + pileup2_str).c_str(), "lp");

    leg_D0  -> SetFillColor(0);
    leg_D0  -> Draw();

    canv_D0 -> Print(("Immagini/" + sample1 + sample2 + "pu" + pileup1_str + pileup2_str + "_biasD0VsEta.png").c_str(), "png");
    delete canv_D0;

    /////// DRAW BIAS PHI /////

    TCanvas* canv_Phi = new TCanvas();

    TMultiGraph* mg_Phi = new TMultiGraph;
    mg_Phi   -> SetName("biasPhiVsEta_combined");
    mg_Phi   -> SetTitle("#sigma(Phi) vs |#eta|;truth |#eta|;#sigma(Phi)");

    biasPhiVsEtaPu1_sample1     ->SetLineColor(kRed);
    biasPhiVsEtaPu2_sample1    ->SetLineColor(kBlue);
    biasPhiVsEtaPu1_sample2     ->SetLineColor(kRed);
    biasPhiVsEtaPu2_sample2    ->SetLineColor(kBlue);

    biasPhiVsEtaPu1_sample1     ->SetMarkerStyle(1);
    biasPhiVsEtaPu2_sample1    ->SetMarkerStyle(1);
    biasPhiVsEtaPu1_sample2     ->SetMarkerStyle(33);
    biasPhiVsEtaPu2_sample2    ->SetMarkerStyle(33);   

    biasPhiVsEtaPu1_sample1     ->SetMarkerColor(kRed);
    biasPhiVsEtaPu2_sample1    ->SetMarkerColor(kBlue);
    biasPhiVsEtaPu1_sample2     ->SetMarkerColor(kRed);
    biasPhiVsEtaPu2_sample2    ->SetMarkerColor(kBlue);
  
    mg_Phi->Add(biasPhiVsEtaPu1_sample1);
    mg_Phi->Add(biasPhiVsEtaPu2_sample1);
    mg_Phi->Add(biasPhiVsEtaPu1_sample2);
    mg_Phi->Add(biasPhiVsEtaPu2_sample2);

    mg_Phi     -> Draw("APE");
    mg_Phi     -> GetYaxis() -> SetTitleOffset(1.35);
    mg_Phi     -> GetYaxis() -> SetRangeUser(0.0,1E-3);

    TLegend* leg_Phi = new TLegend(0.15,0.85,0.4,0.6);
    leg_Phi->AddEntry(biasPhiVsEtaPu1_sample1, (sample1 + "pu" + pileup1_str).c_str(), "lp");
    leg_Phi->AddEntry(biasPhiVsEtaPu2_sample1, (sample1 + "pu" + pileup2_str).c_str(), "lp");
    leg_Phi->AddEntry(biasPhiVsEtaPu1_sample2, (sample2 + "pu" + pileup1_str).c_str(), "lp");
    leg_Phi->AddEntry(biasPhiVsEtaPu2_sample2, (sample2 + "pu" + pileup2_str).c_str(), "lp");

    leg_Phi  -> SetFillColor(0);
    leg_Phi  -> Draw();

    canv_Phi -> Print(("Immagini/" + sample1 + sample2 + "pu" + pileup1_str + pileup2_str + "_biasPhiVsEta.png").c_str(), "png");
    delete canv_Phi;

  }


}
