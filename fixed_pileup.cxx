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


void fixed_pileup(string particle, unsigned int pileup, bool SaveBiasPlots = false) {

  string Energy1 = "15";
  string Energy2 = "50";
  string Energy3 = "100";
  string pileup_str;
  pileup_str = std::to_string(pileup);

  string path1 = particle + Energy1 + "/hist-" + particle + Energy1 + "pu" + pileup_str + ".root";
  string path2 = particle + Energy2 + "/hist-" + particle + Energy2 + "pu" + pileup_str + ".root";
  string path3 = particle + Energy3 + "/hist-" + particle + Energy3 + "pu" + pileup_str + ".root";

  TFile* sample1 = new TFile(path1.c_str());
  TFile* sample2 = new TFile(path2.c_str());
  TFile* sample3 = new TFile(path3.c_str());

  if (SaveBiasPlots) {
    //////////// BIAS PLOTS ///////////////

    TGraphErrors* biasPtVsEta1 = dynamic_cast<TGraphErrors*>(sample1->Get("biasPt_Eta"));
    CHECK_PTR(biasPtVsEta1);

    TGraphErrors* biasQPtVsEta1 = dynamic_cast<TGraphErrors*>(sample1->Get("biasQPt_Eta"));
    CHECK_PTR(biasQPtVsEta1);

    TGraphErrors* biasD0VsEta1 = dynamic_cast<TGraphErrors*>(sample1->Get("biasD0_Eta"));
    CHECK_PTR(biasD0VsEta1);

    TGraphErrors* biasPhiVsEta1 = dynamic_cast<TGraphErrors*>(sample1->Get("biasPhi_Eta"));
    CHECK_PTR(biasPhiVsEta1);

    //////

    TGraphErrors* biasPtVsEta2 = dynamic_cast<TGraphErrors*>(sample2->Get("biasPt_Eta"));
    CHECK_PTR(biasPtVsEta2);

    TGraphErrors* biasQPtVsEta2 = dynamic_cast<TGraphErrors*>(sample2->Get("biasQPt_Eta"));
    CHECK_PTR(biasQPtVsEta2);

    TGraphErrors* biasD0VsEta2 = dynamic_cast<TGraphErrors*>(sample2->Get("biasD0_Eta"));
    CHECK_PTR(biasD0VsEta2);

    TGraphErrors* biasPhiVsEta2 = dynamic_cast<TGraphErrors*>(sample2->Get("biasPhi_Eta"));
    CHECK_PTR(biasPhiVsEta2);

    //////

    TGraphErrors* biasPtVsEta3 = dynamic_cast<TGraphErrors*>(sample3->Get("biasPt_Eta"));
    CHECK_PTR(biasPtVsEta3);

    TGraphErrors* biasQPtVsEta3 = dynamic_cast<TGraphErrors*>(sample3->Get("biasQPt_Eta"));
    CHECK_PTR(biasQPtVsEta3);

    TGraphErrors* biasD0VsEta3 = dynamic_cast<TGraphErrors*>(sample3->Get("biasD0_Eta"));
    CHECK_PTR(biasD0VsEta3);

    TGraphErrors* biasPhiVsEta3 = dynamic_cast<TGraphErrors*>(sample3->Get("biasPhi_Eta"));
    CHECK_PTR(biasPhiVsEta3);


    /////// DRAW BIAS PT /////

    TCanvas* canv_Pt = new TCanvas();
    
    TMultiGraph* mg_Pt = new TMultiGraph;
    mg_Pt   -> SetName("biasPtVsEta_fixedPU");
    mg_Pt   -> SetTitle(("Bias p_{T} vs |#eta| at fixed <#mu> = " + pileup_str + ";truth |#eta|;#sigma(p_{T}) [MeV]").c_str());

    biasPtVsEta1     ->SetLineColor(kRed);
    biasPtVsEta2     ->SetLineColor(kBlue);
    biasPtVsEta3     ->SetLineColor(kGreen);
  
    biasPtVsEta1     ->SetMarkerStyle(33);
    biasPtVsEta2     ->SetMarkerStyle(33);
    biasPtVsEta3     ->SetMarkerStyle(33);

    biasPtVsEta1     ->SetMarkerColor(kRed);
    biasPtVsEta2     ->SetMarkerColor(kBlue);
    biasPtVsEta3     ->SetMarkerColor(kGreen);  

    mg_Pt->Add(biasPtVsEta1);
    mg_Pt->Add(biasPtVsEta2);
    mg_Pt->Add(biasPtVsEta3);

    mg_Pt     -> Draw("APE");
    mg_Pt     -> GetYaxis() -> SetTitleOffset(1.2);
    mg_Pt     -> GetYaxis() -> SetRangeUser(0.0,5000);

    TLegend* leg_Pt = new TLegend(0.15,0.85,0.4,0.6);
    leg_Pt->AddEntry(biasPtVsEta1, (particle + Energy1 + "pu" + pileup_str).c_str(), "lp");
    leg_Pt->AddEntry(biasPtVsEta2, (particle + Energy2 + "pu" + pileup_str).c_str(), "lp");
    leg_Pt->AddEntry(biasPtVsEta3, (particle + Energy3 + "pu" + pileup_str).c_str(), "lp");

    leg_Pt  -> SetFillColor(0);
    leg_Pt  -> Draw();

    canv_Pt -> Print(("Immagini/" + particle + "pu" + pileup_str + "_biasPtVsEta.png").c_str(), "png");
    delete canv_Pt;

    /////// DRAW BIAS QPT /////

    TCanvas* canv_QPt = new TCanvas();
    
    TMultiGraph* mg_QPt = new TMultiGraph;
    mg_QPt   -> SetName("biasQPtVsEta_fixedPU");
    mg_QPt   -> SetTitle(("Bias q/p_{T} vs |#eta| at fixed <#mu> = " + pileup_str + ";truth |#eta|;p_{T} x #sigma(q/p_{T})").c_str());

    biasQPtVsEta1     ->SetLineColor(kRed);
    biasQPtVsEta2     ->SetLineColor(kBlue);
    biasQPtVsEta3     ->SetLineColor(kGreen);
  
    biasQPtVsEta1     ->SetMarkerStyle(33);
    biasQPtVsEta2     ->SetMarkerStyle(33);
    biasQPtVsEta3     ->SetMarkerStyle(33);

    biasQPtVsEta1     ->SetMarkerColor(kRed);
    biasQPtVsEta2     ->SetMarkerColor(kBlue);
    biasQPtVsEta3     ->SetMarkerColor(kGreen);  

    mg_QPt->Add(biasQPtVsEta1);
    mg_QPt->Add(biasQPtVsEta2);
    mg_QPt->Add(biasQPtVsEta3);

    mg_QPt     -> Draw("APE");
    mg_QPt     -> GetYaxis() -> SetTitleOffset(1.2);
    mg_QPt     -> GetYaxis() -> SetRangeUser(0.0,0.2);

    TLegend* leg_QPt = new TLegend(0.15,0.85,0.4,0.6);
    leg_QPt->AddEntry(biasQPtVsEta1, (particle + Energy1 + "pu" + pileup_str).c_str(), "lp");
    leg_QPt->AddEntry(biasQPtVsEta2, (particle + Energy2 + "pu" + pileup_str).c_str(), "lp");
    leg_QPt->AddEntry(biasQPtVsEta3, (particle + Energy3 + "pu" + pileup_str).c_str(), "lp");

    leg_QPt  -> SetFillColor(0);
    leg_QPt  -> Draw();

    canv_QPt -> Print(("Immagini/" + particle + "pu" + pileup_str + "_biasQPtVsEta.png").c_str(), "png");
    delete canv_QPt;

    /////// DRAW BIAS D0 /////

    TCanvas* canv_D0 = new TCanvas();
    
    TMultiGraph* mg_D0 = new TMultiGraph;
    mg_D0   -> SetName("biasD0VsEta_fixedPU");
    mg_D0   -> SetTitle(("Bias D0 vs |#eta| at fixed <#mu> = " + pileup_str + ";truth |#eta|;#sigma(D0) [mm]").c_str());

    biasD0VsEta1     ->SetLineColor(kRed);
    biasD0VsEta2     ->SetLineColor(kBlue);
    biasD0VsEta3     ->SetLineColor(kGreen);
  
    biasD0VsEta1     ->SetMarkerStyle(33);
    biasD0VsEta2     ->SetMarkerStyle(33);
    biasD0VsEta3     ->SetMarkerStyle(33);

    biasD0VsEta1     ->SetMarkerColor(kRed);
    biasD0VsEta2     ->SetMarkerColor(kBlue);
    biasD0VsEta3     ->SetMarkerColor(kGreen);  

    mg_D0->Add(biasD0VsEta1);
    mg_D0->Add(biasD0VsEta2);
    mg_D0->Add(biasD0VsEta3);

    mg_D0     -> Draw("APE");
    mg_D0     -> GetYaxis() -> SetTitleOffset(1.2);
    mg_D0     -> GetYaxis() -> SetRangeUser(0.0,0.08);

    TLegend* leg_D0 = new TLegend(0.15,0.85,0.4,0.6);
    leg_D0->AddEntry(biasD0VsEta1, (particle + Energy1 + "pu" + pileup_str).c_str(), "lp");
    leg_D0->AddEntry(biasD0VsEta2, (particle + Energy2 + "pu" + pileup_str).c_str(), "lp");
    leg_D0->AddEntry(biasD0VsEta3, (particle + Energy3 + "pu" + pileup_str).c_str(), "lp");

    leg_D0  -> SetFillColor(0);
    leg_D0  -> Draw();

    canv_D0 -> Print(("Immagini/" + particle + "pu" + pileup_str + "_biasD0VsEta.png").c_str(), "png");
    delete canv_D0;

    /////// DRAW BIAS PHI /////

    TCanvas* canv_Phi = new TCanvas();
    
    TMultiGraph* mg_Phi = new TMultiGraph;
    mg_Phi   -> SetName("biasPhiVsEta_fixedPU");
    mg_Phi   -> SetTitle(("Bias Phi vs |#eta| at fixed <#mu> = " + pileup_str + ";truth |#eta|;#sigma(Phi)").c_str());

    biasPhiVsEta1     ->SetLineColor(kRed);
    biasPhiVsEta2     ->SetLineColor(kBlue);
    biasPhiVsEta3     ->SetLineColor(kGreen);
  
    biasPhiVsEta1     ->SetMarkerStyle(33);
    biasPhiVsEta2     ->SetMarkerStyle(33);
    biasPhiVsEta3     ->SetMarkerStyle(33);

    biasPhiVsEta1     ->SetMarkerColor(kRed);
    biasPhiVsEta2     ->SetMarkerColor(kBlue);
    biasPhiVsEta3     ->SetMarkerColor(kGreen);  

    mg_Phi->Add(biasPhiVsEta1);
    mg_Phi->Add(biasPhiVsEta2);
    mg_Phi->Add(biasPhiVsEta3);

    mg_Phi     -> Draw("APE");
    mg_Phi     -> GetYaxis() -> SetTitleOffset(1.35);
    mg_Phi     -> GetYaxis() -> SetRangeUser(0.0,1E-3);

    TLegend* leg_Phi = new TLegend(0.15,0.85,0.4,0.6);
    leg_Phi->AddEntry(biasPhiVsEta1, (particle + Energy1 + "pu" + pileup_str).c_str(), "lp");
    leg_Phi->AddEntry(biasPhiVsEta2, (particle + Energy2 + "pu" + pileup_str).c_str(), "lp");
    leg_Phi->AddEntry(biasPhiVsEta3, (particle + Energy3 + "pu" + pileup_str).c_str(), "lp");

    leg_Phi  -> SetFillColor(0);
    leg_Phi  -> Draw();

    canv_Phi -> Print(("Immagini/" + particle + "pu" + pileup_str + "_biasPhiVsEta.png").c_str(), "png");
    delete canv_Phi;



  }
}
