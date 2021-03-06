// WARNING: without truth match probability!!
// WARNING: ptGun limits have to be changed depending on generated pt
// WARNING: passCut set to true (no cut on hits number)

#include <HistManager/TrackHists.h>
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertex.h"
#include <HistManager/TrackHelper.h>
#include <TMath.h>
#include <sstream>

TrackHists::TrackHists(TString name) {
  m_name = "TrackHist_" + name;
  m_label = "Track "; // don't forget the space
  m_isPseudo = false;
  if (m_name.Contains("pseudo")) { m_label = "Pseduotrack "; m_isPseudo = true; }
}

TrackHists::~TrackHists() {}

void TrackHists::BookHists() {

  std::cout << "Creating histograms for " << m_name << std::endl;
  // from truth particle itself
  m_prodR         = declare1D(m_name, "prodR",         "production R [mm]", 110,    0.0, 1100.0);
  m_prodZ         = declare1D(m_name, "prodZ",         "production Z [mm]", 310,    0.0, 3100.0);
  m_truthPt       = declare1D(m_name, "truthPt",       "Truth p_{T} [GeV]", 200,    0.0, 2000.0); 
  m_truthPtnarrow = declare1D(m_name, "truthPtnarrow", "Truth p_{T} [GeV]", 200,    0.0,   50.0); 
  m_truthEta      = declare1D(m_name, "truthEta",      "Truth #eta",         60,   -3.0,    3.0); 
  m_truthPhi      = declare1D(m_name, "truthPhi",      "Truth #phi",         64,   -3.2,    3.2); 
  m_truthD0       = declare1D(m_name, "truthD0",       "Truth d_{0} [mm]",	100,   -0.1,    0.1); 
  m_truthD0_wide  = declare1D(m_name, "truthD0_wide",  "Truth d_{0} [mm]",  100,   -2.0,    2.0); 
  m_truthZ0       = declare1D(m_name, "truthZ0",       "Truth z_{0} [mm]",  100, -200.0,  200.0); 

  m_biasPt  = declare1D(m_name, "biasPt",  "#sigma(p_{T}) [MeV]",        100, -8000.0,8000.0); 
  m_biasQPt = declare1D(m_name, "biasQPt", "p_{T} x #sigma(q/p_{T}) [MeV^{-1}]", 100,    -0.2,   0.2); 
  m_biasEta = declare1D(m_name, "biasEta", "#sigma(#eta)", 			         100,   -2e-3,  2e-3); 
  m_biasPhi = declare1D(m_name, "biasPhi", "#sigma(#phi)", 			         100,	  -2.5e-3,  2.5e-3); 
  m_biasD0  = declare1D(m_name, "biasD0",  "#sigma(d_{0}) [mm]",         100,    -0.2,   0.2); 
  m_biasZ0  = declare1D(m_name, "biasZ0",  "#sigma(z_{0}) [mm]",         100,    -0.8,   0.8); 

  m_biasPt_bin1  = declare1D(m_name, "biasPt_bin1",  "#sigma(p_{T})(|#eta|<0.2) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin2  = declare1D(m_name, "biasPt_bin2",  "#sigma(p_{T})(|#eta|<0.4) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin3  = declare1D(m_name, "biasPt_bin3",  "#sigma(p_{T})(|#eta|<0.6) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin4  = declare1D(m_name, "biasPt_bin4",  "#sigma(p_{T})(|#eta|<0.8) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin5  = declare1D(m_name, "biasPt_bin5",  "#sigma(p_{T})(|#eta|<1.0) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin6  = declare1D(m_name, "biasPt_bin6",  "#sigma(p_{T})(|#eta|<1.2) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin7  = declare1D(m_name, "biasPt_bin7",  "#sigma(p_{T})(|#eta|<1.4) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin8  = declare1D(m_name, "biasPt_bin8",  "#sigma(p_{T})(|#eta|<1.6) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin9  = declare1D(m_name, "biasPt_bin9",  "#sigma(p_{T})(|#eta|<1.8) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin10 = declare1D(m_name, "biasPt_bin10", "#sigma(p_{T})(|#eta|<2.0) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin11 = declare1D(m_name, "biasPt_bin11", "#sigma(p_{T})(|#eta|<2.2) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin12 = declare1D(m_name, "biasPt_bin12", "#sigma(p_{T})(|#eta|<2.4) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin13 = declare1D(m_name, "biasPt_bin13", "#sigma(p_{T})(|#eta|<2.6) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin14 = declare1D(m_name, "biasPt_bin14", "#sigma(p_{T})(|#eta|<2.8) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin15 = declare1D(m_name, "biasPt_bin15", "#sigma(p_{T})(|#eta|<3.0) [MeV]", 100,-8000.0,8000.0); 
  m_biasPt_bin16 = declare1D(m_name, "biasPt_bin16", "#sigma(p_{T})(|#eta|<3.2) [MeV]", 100,-8000.0,8000.0); 

  m_biasQPt_bin1  = declare1D(m_name, "biasQPt_bin1",  "#sigma(q/p_{T})(|#eta|<0.2) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin2  = declare1D(m_name, "biasQPt_bin2",  "#sigma(q/p_{T})(|#eta|<0.4) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin3  = declare1D(m_name, "biasQPt_bin3",  "#sigma(q/p_{T})(|#eta|<0.6) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin4  = declare1D(m_name, "biasQPt_bin4",  "#sigma(q/p_{T})(|#eta|<0.8) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin5  = declare1D(m_name, "biasQPt_bin5",  "#sigma(q/p_{T})(|#eta|<1.0) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin6  = declare1D(m_name, "biasQPt_bin6",  "#sigma(q/p_{T})(|#eta|<1.2) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin7  = declare1D(m_name, "biasQPt_bin7",  "#sigma(q/p_{T})(|#eta|<1.4) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin8  = declare1D(m_name, "biasQPt_bin8",  "#sigma(q/p_{T})(|#eta|<1.6) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin9  = declare1D(m_name, "biasQPt_bin9",  "#sigma(q/p_{T})(|#eta|<1.8) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin10 = declare1D(m_name, "biasQPt_bin10", "#sigma(q/p_{T})(|#eta|<2.0) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin11 = declare1D(m_name, "biasQPt_bin11", "#sigma(q/p_{T})(|#eta|<2.2) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin12 = declare1D(m_name, "biasQPt_bin12", "#sigma(q/p_{T})(|#eta|<2.4) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin13 = declare1D(m_name, "biasQPt_bin13", "#sigma(q/p_{T})(|#eta|<2.6) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin14 = declare1D(m_name, "biasQPt_bin14", "#sigma(q/p_{T})(|#eta|<2.8) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin15 = declare1D(m_name, "biasQPt_bin15", "#sigma(q/p_{T})(|#eta|<3.0) [MeV^{-1}]", 100,-0.2, 0.2); 
  m_biasQPt_bin16 = declare1D(m_name, "biasQPt_bin16", "#sigma(q/p_{T})(|#eta|<3.2) [MeV^{-1}]", 100,-0.2, 0.2); 

  m_biasPhi_bin1  = declare1D(m_name, "biasPhi_bin1",  "#sigma(#phi)(|#eta|<0.2)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin2  = declare1D(m_name, "biasPhi_bin2",  "#sigma(#phi)(|#eta|<0.4)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin3  = declare1D(m_name, "biasPhi_bin3",  "#sigma(#phi)(|#eta|<0.6)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin4  = declare1D(m_name, "biasPhi_bin4",  "#sigma(#phi)(|#eta|<0.8)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin5  = declare1D(m_name, "biasPhi_bin5",  "#sigma(#phi)(|#eta|<1.0)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin6  = declare1D(m_name, "biasPhi_bin6",  "#sigma(#phi)(|#eta|<1.2)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin7  = declare1D(m_name, "biasPhi_bin7",  "#sigma(#phi)(|#eta|<1.4)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin8  = declare1D(m_name, "biasPhi_bin8",  "#sigma(#phi)(|#eta|<1.6)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin9  = declare1D(m_name, "biasPhi_bin9",  "#sigma(#phi)(|#eta|<1.8)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin10 = declare1D(m_name, "biasPhi_bin10", "#sigma(#phi)(|#eta|<2.0)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin11 = declare1D(m_name, "biasPhi_bin11", "#sigma(#phi)(|#eta|<2.2)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin12 = declare1D(m_name, "biasPhi_bin12", "#sigma(#phi)(|#eta|<2.4)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin13 = declare1D(m_name, "biasPhi_bin13", "#sigma(#phi)(|#eta|<2.6)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin14 = declare1D(m_name, "biasPhi_bin14", "#sigma(#phi)(|#eta|<2.8)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin15 = declare1D(m_name, "biasPhi_bin15", "#sigma(#phi)(|#eta|<3.0)", 100, -2.5e-3, 2.5e-3); 
  m_biasPhi_bin16 = declare1D(m_name, "biasPhi_bin16", "#sigma(#phi)(|#eta|<3.2)", 100, -2.5e-3, 2.5e-3); 

  m_biasD0_bin1  = declare1D(m_name, "biasD0_bin1",  "#sigma(d_{0})(|#eta|<0.2) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin2  = declare1D(m_name, "biasD0_bin2",  "#sigma(d_{0})(|#eta|<0.4) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin3  = declare1D(m_name, "biasD0_bin3",  "#sigma(d_{0})(|#eta|<0.6) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin4  = declare1D(m_name, "biasD0_bin4",  "#sigma(d_{0})(|#eta|<0.8) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin5  = declare1D(m_name, "biasD0_bin5",  "#sigma(d_{0})(|#eta|<1.0) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin6  = declare1D(m_name, "biasD0_bin6",  "#sigma(d_{0})(|#eta|<1.2) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin7  = declare1D(m_name, "biasD0_bin7",  "#sigma(d_{0})(|#eta|<1.4) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin8  = declare1D(m_name, "biasD0_bin8",  "#sigma(d_{0})(|#eta|<1.6) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin9  = declare1D(m_name, "biasD0_bin9",  "#sigma(d_{0})(|#eta|<1.8) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin10 = declare1D(m_name, "biasD0_bin10", "#sigma(d_{0})(|#eta|<2.0) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin11 = declare1D(m_name, "biasD0_bin11", "#sigma(d_{0})(|#eta|<2.2) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin12 = declare1D(m_name, "biasD0_bin12", "#sigma(d_{0})(|#eta|<2.4) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin13 = declare1D(m_name, "biasD0_bin13", "#sigma(d_{0})(|#eta|<2.6) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin14 = declare1D(m_name, "biasD0_bin14", "#sigma(d_{0})(|#eta|<2.8) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin15 = declare1D(m_name, "biasD0_bin15", "#sigma(d_{0})(|#eta|<3.0) [mm]",	 100,   -0.2,   0.2); 
  m_biasD0_bin16 = declare1D(m_name, "biasD0_bin16", "#sigma(d_{0})(|#eta|<3.2) [mm]",	 100,   -0.2,   0.2); 


  m_biasZ0_bin1  = declare1D(m_name, "biasZ0_bin1",  "#sigma(z_{0})(|#eta|<0.2) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin2  = declare1D(m_name, "biasZ0_bin2",  "#sigma(z_{0})(|#eta|<0.4) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin3  = declare1D(m_name, "biasZ0_bin3",  "#sigma(z_{0})(|#eta|<0.6) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin4  = declare1D(m_name, "biasZ0_bin4",  "#sigma(z_{0})(|#eta|<0.8) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin5  = declare1D(m_name, "biasZ0_bin5",  "#sigma(z_{0})(|#eta|<1.0) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin6  = declare1D(m_name, "biasZ0_bin6",  "#sigma(z_{0})(|#eta|<1.2) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin7  = declare1D(m_name, "biasZ0_bin7",  "#sigma(z_{0})(|#eta|<1.4) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin8  = declare1D(m_name, "biasZ0_bin8",  "#sigma(z_{0})(|#eta|<1.6) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin9  = declare1D(m_name, "biasZ0_bin9",  "#sigma(z_{0})(|#eta|<1.8) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin10 = declare1D(m_name, "biasZ0_bin10", "#sigma(z_{0})(|#eta|<2.0) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin11 = declare1D(m_name, "biasZ0_bin11", "#sigma(z_{0})(|#eta|<2.2) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin12 = declare1D(m_name, "biasZ0_bin12", "#sigma(z_{0})(|#eta|<2.4) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin13 = declare1D(m_name, "biasZ0_bin13", "#sigma(z_{0})(|#eta|<2.6) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin14 = declare1D(m_name, "biasZ0_bin14", "#sigma(z_{0})(|#eta|<2.8) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin15 = declare1D(m_name, "biasZ0_bin15", "#sigma(z_{0})(|#eta|<3.0) [mm]",  100,   -0.8,   0.8); 
  m_biasZ0_bin16 = declare1D(m_name, "biasZ0_bin16", "#sigma(z_{0})(|#eta|<3.2) [mm]",  100,   -0.8,   0.8); 

  /* track parameterization */
  m_qoverp      = declare1D(m_name, "qoverp",      "#frac{q}{p} [GeV]", 200,  -2e-3,   2e-3); 
  m_pt          = declare1D(m_name, "pt",          "p_{T} [GeV]",       25,    0.0, 10.0); // IT WAS FROM 0 TO 2000 
  m_ptGun          = declare1D(m_name, "ptGun",          "p_{T} [GeV]",       5,    1.0, 0.0);
  m_ptnarrow    = declare1D(m_name, "ptnarrow",    "p_{T} [GeV]",       200,    0.0,   50.0); 
  m_eta         = declare1D(m_name, "eta",         "#eta",               60,   -3.0,    3.0); 
  m_phi         = declare1D(m_name, "phi",         "#phi",               70,   -3.5,    3.5); // IT WAS FROM -3.2 TO 3.2, 64 BINS 
  m_phiTruth         = declare1D(m_name, "phiTruth",         "#phi",               70,   -3.5,    3.5); // IT WAS FROM -3.2 TO 3.2, 64 BINS 
  m_d0          = declare1D(m_name, "d0",          "d_{0} [mm]",        100,   -2.0,    2.0); 
  m_z0          = declare1D(m_name, "z0",          "z_{0} [mm]",        100, -200.0,  200.0); 
  m_z0Corr1     = declare1D(m_name, "z0Corr1",     "z_{0} at PV [mm]",   80,   -8.0,    8.0); 
  m_z0Corr2     = declare1D(m_name, "z0Corr2",     "z_{0} at PV [mm]",   80,   -8.0,    8.0); 

  // Added by Federico Massa
  m_x0          = declare1D(m_name, "x0",          "x_{0} [mm]",        250, -500.0,  500.0); 

  m_y0          = declare1D(m_name, "y0",          "y_{0} [mm]",        250, -500.0,  500.0); 

  /* m_fake          = declare1D(m_name, "fake",          "fake tracks/ev",        20, -0.5,  19.5); // fake tracks per event
     m_fakeAverage = declare2D(m_name, "fakeAverage",          "truth matching prob; # average fake tracks",        20, 0,1,20,-0.5,19.5); // average fake tracks as a function of truthMatchProb */


  /* track parameterization errors */
  m_qoverp_err = declare1D(m_name, "qoverp_err", "#sigma #frac{q}{p} [GeV]", 200, 0.0,2e-5); 
  m_eta_err    = declare1D(m_name, "eta_err",    "#sigma #eta",              100, 0.0, 3.0); 
  m_d0_err     = declare1D(m_name, "d0_err",     "#sigma d_{0}",             100, 0.0, 0.2); 
  m_d0signif   = declare1D(m_name, "d0signif",   "d_{0} Significance",       100,-5.0, 5.0); 
  m_z0_err     = declare1D(m_name, "z0_err",     "#sigma z_{0}",             100, 0.0, 2.0); 
  m_phi_err    = declare1D(m_name, "phi_err",    "#sigma #phi",              100,-3.5, 3.5); 

  m_d0sign      = declare1D(m_name, "d0sign",      "signed IP [mm]",         100,   -10.0,   15.0); 
  m_d0signsig   = declare1D(m_name, "d0signsig",   "signed IP significance", 150,   -10.0,   20.0); 
  m_d0signsigP  = declare1D(m_name, "d0signsigP",  "signed IP significance", 150,   -10.0,   20.0); 
  m_d0signsigN  = declare1D(m_name, "d0signsigN",  "signed IP significance", 150,   -10.0,   20.0); 

  /* track properties */
  m_nPixHits = declare1D(m_name, "nPixHits", "N Pixel Hits",   8, -0.5, 15.5); 
  m_nSCTHits = declare1D(m_name, "nSCTHits", "N SCT Hits",     12, -0.5, 23.5); 
  m_nSiHits  = declare1D(m_name, "nSiHits",  "N Silicon Hits", 30, -0.5, 29.5);

  m_eta_nPixHits = declare2D(m_name, "eta_nPixHits", "|#eta|", "N Pixel Hits",   30, 0, 3.0, 16, -0.5, 15.5); 
  m_eta_nSCTHits = declare2D(m_name, "eta_nSCTHits", "|#eta|", "N SCT Hits",	   30, 0, 3.0, 25, -0.5, 24.5); 
  m_eta_nSiHits  = declare2D(m_name, "eta_nSiHits",  "|#eta|", "N Silicon Hits", 30, 0, 3.0, 30, -0.5, 29.5);


  // hits of true tracks (not fake)
  m_nTruePixHits = declare1D(m_name, "nTruePixHits", "N Pixel Hits of true tracks",   8, -0.5, 15.5); 
  m_nTrueSCTHits = declare1D(m_name, "nTrueSCTHits", "N SCT Hits of true tracks",	   12, -0.5, 23.5); 
  m_nTrueSiHits  = declare1D(m_name, "nTrueSiHits",  "N Silicon Hits of true tracks", 15, -0.5, 29.5);

  m_eta_nTruePixHits = declare2D(m_name, "eta_nTruePixHits", "|#eta|", "N Pixel Hits in true tracks",   30, 0, 3.0, 16, -0.5, 15.5); 
  m_eta_nTrueSCTHits = declare2D(m_name, "eta_nTrueSCTHits", "|#eta|", "N SCT Hits in true tracks",	   30, 0, 3.0, 25, -0.5, 24.5); 
  m_eta_nTrueSiHits  = declare2D(m_name, "eta_nTrueSiHits",  "|#eta|", "N Silicon Hits in true tracks", 30, 0, 3.0, 30, -0.5, 29.5);

  // hits of fake tracks
  m_nFakePixHits = declare1D(m_name, "nFakePixHits", "N Pixel Hits of fake tracks",   8, -0.5, 15.5); 
  m_nFakeSCTHits = declare1D(m_name, "nFakeSCTHits", "N SCT Hits of fake tracks",	   12, -0.5, 23.5); 
  m_nFakeSiHits  = declare1D(m_name, "nFakeSiHits",  "N Silicon Hits of fake tracks", 15, -0.5, 29.5);

  m_eta_nFakePixHits = declare2D(m_name, "eta_nFakePixHits", "|#eta|", "N Pixel Hits in fake tracks",   30, 0, 3.0, 16, -0.5, 15.5); 
  m_eta_nFakeSCTHits = declare2D(m_name, "eta_nFakeSCTHits", "|#eta|", "N SCT Hits in fake tracks",	   30, 0, 3.0, 25, -0.5, 24.5); 
  m_eta_nFakeSiHits  = declare2D(m_name, "eta_nFakeSiHits",  "|#eta|", "N Silicon Hits in fake tracks", 30, 0, 3.0, 30, -0.5, 29.5);


  m_nGangedPix         = declare1D(m_name, "nGangedPix",         m_label + "N Pixel Ganged Hits",     8, -0.5,  7.5); 
  m_nGangedPixFF       = declare1D(m_name, "nGangedPixFF",       m_label + "N Pixel Ganged FF Hits",  6, -0.5,  5.5); 
  m_nPixLay            = declare1D(m_name, "nPixLay",            m_label + "N Pixel Layers",         10, -0.5,  9.5); 
  m_nPixSharedHits     = declare1D(m_name, "nPixSharedHits",     m_label + "N Pixel Shared Hits",     8, -0.5,  7.5); 
  m_nPixSplitHits      = declare1D(m_name, "nPixSplitHits",      m_label + "N Pixel Split Hits",      8, -0.5,  7.5); 
  m_nPixSpoiltHits     = declare1D(m_name, "nPixSpoiltHits",     m_label + "N Pixel Spoilt Hits",     8, -0.5,  7.5); 
  m_nPixOutliers       = declare1D(m_name, "nPixOutliers",       m_label + "N Pixel Outliers",        8, -0.5,  7.5); 
  m_nPixHoles          = declare1D(m_name, "nPixHoles",          m_label + "N Pixel Holes",           8, -0.5,  7.5); 
  m_nPixelDeadSensors  = declare1D(m_name, "nPixelDeadSensors",  m_label + "N Pixel Dead Sensors",    8, -0.5,  7.5); 
  m_nSCTSharedHits     = declare1D(m_name, "nSCTSharedHits",     m_label + "N SCT Shared Hits",      11, -0.5, 10.5); 
  m_nSCTSpoiltHits     = declare1D(m_name, "nSCTSpoiltHits",     m_label + "N SCT Spoilt Hits",      11, -0.5, 10.5); 
  m_nSCTOutliers       = declare1D(m_name, "nSCTOutliers",	     m_label + "N SCT Outliers",          8, -0.5,  7.5); 
  m_nSCTHoles          = declare1D(m_name, "nSCTHoles",	         m_label + "N SCT Holes",             8, -0.5,  7.5); 
  m_nSCTDoubleHoles    = declare1D(m_name, "nSCTDoubleHoles",    m_label + "N SCT Double Holes",      8, -0.5,  7.5); 
  m_nSCTDeadSensors    = declare1D(m_name, "nSCTDeadSensors",    m_label + "N SCT Dead Sensors",      5, -0.5,  4.5);
  m_nSiDeadSensors     = declare1D(m_name, "nSiDeadSensors",     m_label + "N Silicon Dead Sensors",  9, -0.5,  8.5);

  m_nTRTHits     = declare1D(m_name, "nTRTHits",     m_label + "N TRT Hits",                41, -0.5, 40.5 ); 
  m_nTRTOutliers = declare1D(m_name, "nTRTOutliers", m_label + "N TRT Outliers",            11, -0.5, 10.5 ); 
  m_nTRTHoles    = declare1D(m_name, "nTRTHoles",    m_label + "N TRT Holes",               11, -0.5, 10.5 ); 
  m_nTRTHTHits   = declare1D(m_name, "nTRTHTHits",   m_label + "N High Threshold TRT Hits", 31, -0.5, 30.5 ); 

  m_chiSqPerDof  = declare1D(m_name, "chiSqPerDof",  m_label + "#chi^{2}/DOF", 120,  0.0, 12.0);
  m_nOutliers    = declare1D(m_name, "nOutliers",    m_label + "N Outliers",    20, -0.5, 19.5);
  m_stdDevChi2OS = declare1D(m_name, "stdDevChi2OS", m_label + "100x Std. Dev. #chi^{2} from surface", 100, 0.0, 500.0);

  m_eProbComb = declare1D(m_name, "eProbComb", m_label + "e Prob Comb", 20, 0.0, 1.0); 
  m_eProbHT   = declare1D(m_name, "eProbHT",   m_label + "e Prob HT",   20, 0.0, 1.0); 
  m_eProbToT  = declare1D(m_name, "eProbToT",  m_label + "e Prob ToT",  20, 0.0, 1.0); 
  m_eProbBrem = declare1D(m_name, "eProbBrem", m_label + "e Prob Brem", 20, 0.0, 1.0); 

  m_truthMatchProb = declare1D(m_name, "truthMatchProb", m_label + "Truth Match \"Prob\"", 20, 0.0, 1.0);

  m_matchingDR = declare1D(m_name, "matchingDR", "#Delta R", 100, 0.0, 0.1); 

  m_abseta       = declare1D(m_name, "abseta",        "|#eta|", 15, 0.0, 3.0);
  m_absetaGun       = declare1D(m_name, "absetaGun",        "|#eta_Gun|", 30, 0.0, 3.0);
  m_abseta_dr001 = declare1D(m_name, "abseta_dr001", "|#eta|", 15, 0.0, 3.0); 
  m_abseta_dr002 = declare1D(m_name, "abseta_dr002", "|#eta|", 15, 0.0, 3.0); 
  m_abseta_dr003 = declare1D(m_name, "abseta_dr003", "|#eta|", 15, 0.0, 3.0); 
  m_abseta_dr004 = declare1D(m_name, "abseta_dr004", "|#eta|", 15, 0.0, 3.0); 
  m_abseta_dr005 = declare1D(m_name, "abseta_dr005", "|#eta|", 15, 0.0, 3.0); 
  m_abseta_dr006 = declare1D(m_name, "abseta_dr006", "|#eta|", 15, 0.0, 3.0); 
  m_abseta_dr007 = declare1D(m_name, "abseta_dr007", "|#eta|", 15, 0.0, 3.0); 
  m_abseta_dr008 = declare1D(m_name, "abseta_dr008", "|#eta|", 15, 0.0, 3.0); 
  m_abseta_dr009 = declare1D(m_name, "abseta_dr009", "|#eta|", 15, 0.0, 3.0); 

  for (int i = 0; i < m_FakeBin; i++) {
    std::stringstream ss;
    TString i_str;
    ss << (i+1);
    ss >> i_str;
    // m_FakeVsEta.push_back(new TH1F(m_name + "fakeBin" + i_str, "Particle gun fake; nFake; #", 2, 0.0,2.0));
    m_FakeGunVsEta.push_back(declare1D(m_name, "fakeGun_bin"+i_str,"fakes", 2,0.0,2.0));

  }

} // BookHists

void TrackHists::FillHists(const xAOD::TrackParticle* trk, float weight) const {

  if(m_usedBarcodes.size() > 100) { 
    std::cout << "WARNING::TrackHists " << m_name << " has " << m_usedBarcodes.size() 
      << " barcodes marked as used" << std::endl;
  }

  // only fill histogram 1 time per truth particle
//  if(  trk->isAvailable< int >("barcode")  ) {
//    // if used already - return!!
//    if( m_usedBarcodes.find((int)trk->auxdata< int >( "barcode" )) != m_usedBarcodes.end() ){
//      return;
//    }
//    m_usedBarcodes.insert( (int)trk->auxdata< int >( "barcode" ) );
//  }

  uint8_t getInt(0);   // for accessing summary information
  float   getFlt(0.0); // for accessing summary information
  const xAOD::ParametersCovMatrix_t covTrk = trk->definingParametersCovMatrix();
  float d0err = sqrt(covTrk(0,0));
  float d0signif = trk->d0()/d0err;
  float z0err = sqrt(covTrk(1,1));

  const xAOD::TruthParticle *truthParticle = xAOD::TrackHelper::truthParticle(trk);
  
  /* track parameterization */
  m_qoverp       ->Fill(trk->qOverP(),weight); 
  m_pt           ->Fill(trk->pt()*1e-3,weight); 
  m_ptGun        ->Fill(trk->pt()*1e-3,weight); 
  m_ptnarrow     ->Fill(trk->pt()*1e-3,weight); 
  m_eta          ->Fill(trk->eta(),weight);
  m_d0           ->Fill(trk->d0(),weight); 
  m_z0           ->Fill(trk->z0(),weight); 
  m_phi          ->Fill(trk->phi(),weight); 

  float signQ = 0.0;
  if (trk->isAvailable<int>("signToQuark")) { signQ = trk->auxdata<int>("signToQuark"); }

  m_d0sign    ->Fill(trk->d0()*signQ,weight); 
  m_d0signsig ->Fill(trk->d0()*signQ/d0err,weight); 

  if (trk->d0()*signQ/d0err>0.0) {
    m_d0signsigP ->Fill(trk->d0()*signQ/d0err,weight); 
  }
  else {
    m_d0signsigN ->Fill(trk->d0()*signQ/d0err,weight); 
  }

  if (trk->isAvailable<float>("z0Corr1")) { m_z0Corr1 -> Fill(trk->auxdata<float>("z0Corr1"),weight); }
  if (trk->isAvailable<float>("z0Corr2")) { m_z0Corr2 -> Fill(trk->auxdata<float>("z0Corr2"),weight); }

  // Added by Federico Massa
  if (trk->isAvailable<float>("x0")) {m_x0 -> Fill(trk->auxdata<float>("x0"),weight);}
  if (trk->isAvailable<float>("y0")) {m_y0 -> Fill(trk->auxdata<float>("y0"),weight);}


  /* track parameterization errors */
  m_qoverp_err -> Fill(sqrt(covTrk(4,4)),weight); 
  m_eta_err    -> Fill(sqrt(covTrk(3,3)),weight);  // really theta - FIXME
  m_d0_err     -> Fill(d0err,weight);
  m_d0signif   -> Fill(d0signif,weight);
  m_z0_err     -> Fill(sqrt(covTrk(1,1)),weight); 
  m_phi_err    -> Fill(sqrt(covTrk(2,2)),weight); 

  //vx, vy, vz
  //parameterX, parameterY, parameterZ
  //parameterPX, parameterPY, parameterPZ
  //trackParameterCovarianceMatrices
  //parameterPosition
  //chiSquared  -> function
  //numberDoF   -> function
  //chiSqPerDoF
  //trackFitter
  //particleHypothesis
  //trackProperties
  //patternRecoInfo

  /* track properties */
  
  trk->summaryValue(getInt,xAOD::numberOfPixelHits); int nPixHits = getInt;
  trk->summaryValue(getInt,xAOD::numberOfSCTHits);   int nSCTHits = getInt;
  int nSiHits  = xAOD::TrackHelper::numberOfSiHits(trk);
  m_nPixHits -> Fill(1.0*nPixHits);
  m_nSCTHits -> Fill(1.0*nSCTHits); 
  m_nSiHits  -> Fill(1.0*nSiHits);
  
  if (truthParticle) {
  m_eta_nPixHits -> Fill(TMath::Abs(truthParticle->eta()),1.0*nPixHits);
  m_eta_nSCTHits -> Fill(TMath::Abs(trk->eta()),1.0*nSCTHits); 
  m_eta_nSiHits  -> Fill(TMath::Abs(trk->eta()),1.0*nSiHits);
  }

  if (!xAOD::TrackHelper::isFake(trk)) {
    m_nTruePixHits -> Fill(1.0*nPixHits);
    m_nTrueSCTHits -> Fill(1.0*nSCTHits); 
    m_nTrueSiHits  -> Fill(1.0*nSiHits);  

    if (truthParticle) {
    m_eta_nTruePixHits -> Fill(TMath::Abs(trk->eta()),1.0*nPixHits);
    m_eta_nTrueSCTHits -> Fill(TMath::Abs(trk->eta()),1.0*nSCTHits); 
    m_eta_nTrueSiHits  -> Fill(TMath::Abs(trk->eta()),1.0*nSiHits);
    }
  }

  else {
    m_nFakePixHits -> Fill(1.0*nPixHits);
    m_nFakeSCTHits -> Fill(1.0*nSCTHits); 
    m_nFakeSiHits  -> Fill(1.0*nSiHits);  
    
    if (truthParticle) {
    m_eta_nFakePixHits -> Fill(TMath::Abs(trk->eta()),1.0*nPixHits);
    m_eta_nFakeSCTHits -> Fill(TMath::Abs(trk->eta()),1.0*nSCTHits); 
    m_eta_nFakeSiHits  -> Fill(TMath::Abs(trk->eta()),1.0*nSiHits);
    }
  }  


  trk->summaryValue(getInt,xAOD::numberOfGangedPixels);       m_nGangedPix        -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfGangedFlaggedFakes); m_nGangedPixFF      -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfContribPixelLayers); m_nPixLay           -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelSharedHits);    m_nPixSharedHits    -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelSplitHits);     m_nPixSplitHits     -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelSpoiltHits);    m_nPixSpoiltHits    -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelOutliers);      m_nPixOutliers      -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelHoles);         m_nPixHoles         -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelDeadSensors);   m_nPixelDeadSensors -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfSCTSharedHits);      m_nSCTSharedHits    -> Fill(getInt,weight); 
  trk->summaryValue(getInt,xAOD::numberOfSCTSpoiltHits);      m_nSCTSpoiltHits    -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfSCTOutliers);        m_nSCTOutliers      -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfSCTHoles);           m_nSCTHoles         -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfSCTDoubleHoles);     m_nSCTDoubleHoles   -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfSCTDeadSensors);     m_nSCTDeadSensors   -> Fill(getInt,weight);

  m_nSiDeadSensors -> Fill(xAOD::TrackHelper::numberOfSiDeadSensors(trk),weight);

  trk->summaryValue(getInt,xAOD::numberOfTRTHits);              m_nTRTHits     -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfTRTOutliers);          m_nTRTOutliers -> Fill(getInt,weight); 
  trk->summaryValue(getInt,xAOD::numberOfTRTHoles);             m_nTRTHoles    -> Fill(getInt,weight); 
  trk->summaryValue(getInt,xAOD::numberOfTRTHighThresholdHits); m_nTRTHTHits   -> Fill(getInt,weight); 
  //numberOfTRTHighThresholdOutliers
  //numberOfTRTDeadStraws
  //numberOfTRTTubeHits
  //numberOfTRTXenonHits
  //numberOfPrecisionLayers
  //numberOfPrecisionHoleLayers
  //numberOfPhiLayers
  //numberOfPhiHoleLayers
  //numberOfTriggerEtaLayers
  //numberOfTriggerEtaHoleLayers

  m_chiSqPerDof -> Fill(xAOD::TrackHelper::chiSqPerDoF(trk),weight);

  trk->summaryValue(getInt,xAOD::numberOfOutliersOnTrack);   m_nOutliers    -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::standardDeviationOfChi2OS); m_stdDevChi2OS -> Fill(getInt,weight);

  trk->summaryValue(getFlt,xAOD::eProbabilityComb); m_eProbComb -> Fill(getFlt,weight);
  trk->summaryValue(getFlt,xAOD::eProbabilityHT);   m_eProbHT   -> Fill(getFlt,weight);
  trk->summaryValue(getFlt,xAOD::eProbabilityToT);  m_eProbToT  -> Fill(getFlt,weight);
  trk->summaryValue(getFlt,xAOD::eProbabilityBrem); m_eProbBrem -> Fill(getFlt,weight);

  //===========================
  // Efficiency and fake study
  //===========================

  if (truthParticle) {

    if (truthParticle->hasProdVtx()) {
      m_prodR -> Fill(truthParticle->prodVtx()->perp(),weight);
      m_prodZ -> Fill(truthParticle->prodVtx()->z(),weight);
    }



    float truthd0 = 0.0;
    if (truthParticle->isAvailable<float>("d0")) {
      truthd0 = truthParticle->auxdata<float>("d0");
    }

    float truthz0 = 0.0;
    if (truthParticle->isAvailable<float>("z0")) {
      truthz0 = truthParticle->auxdata<float>("z0");
    }

    m_truthPt       -> Fill(truthParticle->pt()*1e-3,weight);
    m_truthPtnarrow -> Fill(truthParticle->pt()*1e-3,weight);
    m_truthEta      -> Fill(truthParticle->eta(),weight);
    m_truthPhi      -> Fill(truthParticle->phi(),weight);
    m_truthD0       -> Fill(truthd0,weight);
    m_truthZ0       -> Fill(truthz0,weight);

    float sigPt  = trk->pt()-truthParticle->pt();
    float sigQPt = (trk->charge()/trk->pt()-truthParticle->charge()/truthParticle->pt())*truthParticle->pt();
    float sigEta = trk->eta()-truthParticle->eta();
    float sigPhi = TVector2::Phi_mpi_pi(trk->phi()-truthParticle->phi());
    float sigD0  = trk->d0()-truthd0;
    float sigZ0  = trk->z0()-truthz0;

    m_biasPt  -> Fill(sigPt);
    m_biasQPt -> Fill(sigQPt);
    m_biasEta -> Fill(sigEta);
    m_biasPhi -> Fill(sigPhi);
    m_biasD0  -> Fill(sigD0);
    m_biasZ0  -> Fill(sigZ0);

    //changed from trk->eta() to truthParticle->eta()    
    if (TMath::Abs(truthParticle->eta())<0.2) {
      m_biasPt_bin1  -> Fill(sigPt);
      m_biasQPt_bin1 -> Fill(sigQPt);
      m_biasPhi_bin1 -> Fill(sigPhi);
      m_biasD0_bin1  -> Fill(sigD0);
      m_biasZ0_bin1  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<0.4) {
      m_biasPt_bin2  -> Fill(sigPt);
      m_biasQPt_bin2 -> Fill(sigQPt);
      m_biasPhi_bin2 -> Fill(sigPhi);
      m_biasD0_bin2  -> Fill(sigD0);
      m_biasZ0_bin2  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<0.6) {
      m_biasPt_bin3  -> Fill(sigPt);
      m_biasQPt_bin3 -> Fill(sigQPt);
      m_biasPhi_bin3 -> Fill(sigPhi);
      m_biasD0_bin3  -> Fill(sigD0);
      m_biasZ0_bin3  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<0.8) {
      m_biasPt_bin4  -> Fill(sigPt);
      m_biasQPt_bin4 -> Fill(sigQPt);
      m_biasPhi_bin4 -> Fill(sigPhi);
      m_biasD0_bin4  -> Fill(sigD0);
      m_biasZ0_bin4  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<1.0) {
      m_biasPt_bin5  -> Fill(sigPt);
      m_biasQPt_bin5 -> Fill(sigQPt);
      m_biasPhi_bin5 -> Fill(sigPhi);
      m_biasD0_bin5  -> Fill(sigD0);
      m_biasZ0_bin5  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<1.2) {
      m_biasPt_bin6  -> Fill(sigPt);
      m_biasQPt_bin6 -> Fill(sigQPt);
      m_biasPhi_bin6 -> Fill(sigPhi);
      m_biasD0_bin6  -> Fill(sigD0);
      m_biasZ0_bin6  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<1.4) {
      m_biasPt_bin7  -> Fill(sigPt);
      m_biasQPt_bin7 -> Fill(sigQPt);
      m_biasPhi_bin7 -> Fill(sigPhi);
      m_biasD0_bin7  -> Fill(sigD0);
      m_biasZ0_bin7  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<1.6) {
      m_biasPt_bin8  -> Fill(sigPt);
      m_biasQPt_bin8 -> Fill(sigQPt);
      m_biasPhi_bin8 -> Fill(sigPhi);
      m_biasD0_bin8  -> Fill(sigD0);
      m_biasZ0_bin8  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<1.8) {
      m_biasPt_bin9  -> Fill(sigPt);
      m_biasQPt_bin9 -> Fill(sigQPt);
      m_biasPhi_bin9 -> Fill(sigPhi);
      m_biasD0_bin9  -> Fill(sigD0);
      m_biasZ0_bin9  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<2.0) {
      m_biasPt_bin10  -> Fill(sigPt);
      m_biasQPt_bin10 -> Fill(sigQPt);
      m_biasPhi_bin10 -> Fill(sigPhi);
      m_biasD0_bin10  -> Fill(sigD0);
      m_biasZ0_bin10  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<2.2) {
      m_biasPt_bin11  -> Fill(sigPt);
      m_biasQPt_bin11 -> Fill(sigQPt);
      m_biasPhi_bin11 -> Fill(sigPhi);
      m_biasD0_bin11  -> Fill(sigD0);
      m_biasZ0_bin11  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<2.4) {
      m_biasPt_bin12  -> Fill(sigPt);
      m_biasQPt_bin12 -> Fill(sigQPt);
      m_biasPhi_bin12 -> Fill(sigPhi);
      m_biasD0_bin12  -> Fill(sigD0);
      m_biasZ0_bin12  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<2.6) {
      m_biasPt_bin13  -> Fill(sigPt);
      m_biasQPt_bin13 -> Fill(sigQPt);
      m_biasPhi_bin13 -> Fill(sigPhi);
      m_biasD0_bin13  -> Fill(sigD0);
      m_biasZ0_bin13  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<2.8) {
      m_biasPt_bin14  -> Fill(sigPt);
      m_biasQPt_bin14 -> Fill(sigQPt);
      m_biasPhi_bin14 -> Fill(sigPhi);
      m_biasD0_bin14  -> Fill(sigD0);
      m_biasZ0_bin14  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<3.0) {
      m_biasPt_bin15  -> Fill(sigPt);
      m_biasQPt_bin15 -> Fill(sigQPt);
      m_biasPhi_bin15 -> Fill(sigPhi);
      m_biasD0_bin15  -> Fill(sigD0);
      m_biasZ0_bin15  -> Fill(sigZ0);
    }
    else if (TMath::Abs(truthParticle->eta())<3.2) {
      m_biasPt_bin16  -> Fill(sigPt);
      m_biasQPt_bin16 -> Fill(sigQPt);
      m_biasPhi_bin16 -> Fill(sigPhi);
      m_biasD0_bin16  -> Fill(sigD0);
      m_biasZ0_bin16  -> Fill(sigZ0);
    }
  
    int bin = TMath::FloorNint(TMath::Abs(truthParticle->eta())/3.2*float(m_FakeBin));
    if (xAOD::TrackHelper::isFake(trk)) m_FakeGunVsEta.at(bin)->Fill(1.0);
    else m_FakeGunVsEta.at(bin)->Fill(0.0);
  

  }


  if (trk->isAvailable<float>("matchedDR")) {
    bool passCut = false;

    float mindR = trk->auxdata<float>("matchedDR");
    float prob = xAOD::TrackHelper::truthMatchProb(trk);
    m_truthMatchProb -> Fill(prob);

    // passCut=true;
    //    if (nSiHits>8) { passCut=true; }
    //    if (nSiHits>9) { passCut=true; }
    if (nSiHits>10) { passCut=true; }

    if (passCut) {
      //      if (prob>0.95) { //don't use it for now
      
      m_absetaGun    -> Fill(TMath::Abs(trk->eta()),weight);
      m_abseta   -> Fill(TMath::Abs(truthParticle->eta()),weight); //used for efficiency
      m_phiTruth  -> Fill(truthParticle->phi(),weight); //used for efficiency

      m_matchingDR -> Fill(mindR);
      if (mindR<0.01) { m_abseta_dr001 -> Fill(TMath::Abs(truthParticle->eta())); }
      if (mindR<0.02) { m_abseta_dr002 -> Fill(TMath::Abs(truthParticle->eta())); }
      if (mindR<0.03) { m_abseta_dr003 -> Fill(TMath::Abs(truthParticle->eta())); }
      if (mindR<0.04) { m_abseta_dr004 -> Fill(TMath::Abs(truthParticle->eta())); }
      if (mindR<0.05) { m_abseta_dr005 -> Fill(TMath::Abs(truthParticle->eta())); }
      if (mindR<0.06) { m_abseta_dr006 -> Fill(TMath::Abs(truthParticle->eta())); }
      if (mindR<0.07) { m_abseta_dr007 -> Fill(TMath::Abs(truthParticle->eta())); }
      if (mindR<0.08) { m_abseta_dr008 -> Fill(TMath::Abs(truthParticle->eta())); }
      if (mindR<0.09) { m_abseta_dr009 -> Fill(TMath::Abs(truthParticle->eta())); }
      //  } closed prob 
    }
  }
  
} // FillHists

