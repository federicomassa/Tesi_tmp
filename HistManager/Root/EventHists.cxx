#include <HistManager/EventHists.h>
#include <vector>
#include <string>
#include <sstream>

EventHists::EventHists(TString name) {
   m_name  = "EventHist_" + name;
   m_label = "Event "; // don't forget the space
}

EventHists::~EventHists() {}

void EventHists::BookHists() {

  std::cout << "Creating histograms for " << m_name << std::endl;

  m_pstrk            = declare1D(m_name, "nPstrk",	     m_label  + "N pseudoTracks in Event",	      8, -0.5, 7.5);  
  m_primary_pstrk    = declare1D(m_name, "nPrimaryPstrk",    m_label  + "N Primary pseudoTracks in Event" ,   4, -0.5, 3.5);
  m_secondary_pstrk  = declare1D(m_name, "nSecondaryPstrk",  m_label  + "N Secondary pseudoTracks in Event",  8, -0.5, 7.5);
  m_lost_pstrk       = declare1D(m_name, "nLostPstrk",       m_label  + "N Lost pseudoTracks in Event",	      4, -0.5, 3.5);
  m_recotrk          = declare1D(m_name, "nRecotrk",	     m_label  + "N recoTracks in Event",  	      15, -0.5, 14.5);  
  m_recotrkwide      = declare1D(m_name, "nRecotrkwide",   m_label  + "N recoTracks in Event",  	   100, -0.5,  99.5);  
  m_sispseed         = declare1D(m_name, "nSispseed",	     m_label  + "N siSpSeeded Tracks in Event",       15, -0.5, 14.5);  
  m_nPixelClusters   = declare1D(m_name, "nPixelClusters",   m_label  + "N Pixel Clusters in Event",          41, -0.5, 40.5);
  m_nSCTClusters     = declare1D(m_name, "nSCTClusters",     m_label  + "N SCT Clusters in Event",            50, 0.0, 500);
  m_nSiClusters      = declare1D(m_name, "nSiClusters",      m_label  + "N Si Clusters in Event",             55, 0.0, 550);
  m_nPixelClusterswide   = declare1D(m_name, "nPixelClusterswide",   m_label  + "N Pixel Clusters in Event",     200, 0.0, 4000);
  m_nSCTClusterswide     = declare1D(m_name, "nSCTClusterswide",     m_label  + "N SCT Clusters in Event",       300, 0.0, 6000);
  m_nSiClusterswide      = declare1D(m_name, "nSiClusterswide",      m_label  + "N Si Clusters in Event",        200, 0.0, 8000);

  m_trigWeight       = declare1D(m_name, "trigWeight", m_label + "trigger weight",10,-0.5,9.5);
  m_muValue          = declare1D(m_name, "muValue", m_label + "pilueup  #mu",30,0.0,30.0);
  m_muValueCorr      = declare1D(m_name, "muValueCorr", m_label + "pilueup  #mu",30,0.0,30.0);

  // For ITk
  m_recotrk1GeV      = declare1D(m_name, "nRecotrk1GeV",    "N recoTracks (p_{T}>1GeV) in Event", 15, -0.5, 14.5);  

  //nFake0X refers to cutoff value of truthMatchProb = 0.X
  m_nFake01      = declare1D(m_name, "nFake01",    "N fake in event", 15, -0.5, 14.5);  
  m_nFake02      = declare1D(m_name, "nFake02",    "N fake in event", 15, -0.5, 14.5);  
  m_nFake03      = declare1D(m_name, "nFake03",    "N fake in event", 15, -0.5, 14.5);
  m_nFake04      = declare1D(m_name, "nFake04",    "N fake in event", 15, -0.5, 14.5);  
  m_nFake05      = declare1D(m_name, "nFake05",    "N fake in event", 15, -0.5, 14.5); 
  m_nFake06      = declare1D(m_name, "nFake06",    "N fake in event", 15, -0.5, 14.5);  
  m_nFake07      = declare1D(m_name, "nFake07",    "N fake in event", 15, -0.5, 14.5);  
  m_nFake08      = declare1D(m_name, "nFake08",    "N fake in event", 15, -0.5, 14.5);  
  m_nFake09      = declare1D(m_name, "nFake09",    "N fake in event", 15, -0.5, 14.5);  

  // nFakeBinXY refers to average number of fake tracks with |eta| in a certain range, see implementation (step in |eta| = 0.2)

  for (int i = 0; i < 16; i++) {
    std::stringstream ss;
    std::string i_str;
    ss << i + 1;
    ss >> i_str;
    m_FakeVsEta.push_back(declare1D(m_name, ("nFake_bin"+i_str).c_str(),"fakes",5,0,5));
  }

  m_recotrk1GeVwide      = declare1D(m_name, "nRecotrk1GeVwide",    "N recoTrackswide (p_{T}>1GeV) in Event", 100, -0.5, 99.5);
  m_average2TrackEta = declare1D(m_name, "average2TrackEta","average #eta of 2 tracks",      30, -3.0, 3.0);
  m_photonEta        = declare1D(m_name, "photonEta",       "photon #eta",                   5, 0.0, 3.0);
  m_photonEta2Track  = declare1D(m_name, "photonEta2Track", "photon #eta",                   5, 0.0, 3.0);

  m_photonProdR        = declare1D(m_name, "photonProdR",       "photon production r[mm]",     50,  0.0, 10.0);
  m_photonProdR2Track  = declare1D(m_name, "photonProdR2Track", "photon production r[mm]",     50,  0.0, 10.0);
  m_photonDecayR       = declare1D(m_name, "photonDecayR",       "photon conversion r[mm]",   55,  0.0, 1100.0);
  m_photonDecayR2Track = declare1D(m_name, "photonDecayR2Track", "photon conversion r[mm]",   55,  0.0, 1100.0);

  m_nTruth        = declare1D(m_name, "nTruth",        "N Truth in Event",  100, -0.5, 99.5);
  m_nChargedTruth = declare1D(m_name, "nChargedTruth", "N ChargedTruth in Event",  100, -0.5, 99.5);
  m_nNeutralTruth = declare1D(m_name, "nNeutralTruth", "N NeutralTruth in Event",  100, -0.5, 99.5);
  m_nTruth1GeV        = declare1D(m_name, "nTruth1GeV",        "N Truth (p_{T}>1GeV) in Event",  100, -0.5, 99.5);
  m_nChargedTruth1GeV = declare1D(m_name, "nChargedTruth1GeV", "N ChargedTruth (p_{T}>1GeV) in Event",  100, -0.5, 99.5);
  m_nNeutralTruth1GeV = declare1D(m_name, "nNeutralTruth1GeV", "N NeutralTruth (p_{T}>1GeV) in Event",  100, -0.5, 99.5);
  m_nIsoTrack        = declare1D(m_name, "nIsoTrack",        m_label  + "N Iso.Track",      10, -0.5, 9.5);
  m_nVertex          = declare1D(m_name, "nVertex",          m_label  + "N vertex",         10, -0.5, 9.5);

  m_effPileupTrack1GeV = declare1D(m_name, "effPileupTrack1GeV", "Efficiency of pileup track (p_{T}>1GeV)",  100, 0.0, 1.0);

  m_effPileupTrack1GeV_vsTruth = declare2D(m_name, "effPileupTrack1GeV_vsTruth", "Truth particles (p_{T}>1GeV)", "Tracks (p_{T}>1GeV)",   10, -0.5, 9.5, 10, -0.5, 9.5); 


} // BookHists

void EventHists::FillHists(EventFeatures &evt, float weight) const {
  m_pstrk              -> Fill(evt.nPseudoTracks,weight);
  m_primary_pstrk      -> Fill(evt.nPrimaryPseudoTracks,weight);
  m_secondary_pstrk    -> Fill(evt.nSecondaryPseudoTracks,weight);
  m_lost_pstrk         -> Fill(evt.nLostPseudoTracks,weight);
  m_recotrk            -> Fill(evt.nRecoTracks,weight);   
  m_recotrkwide        -> Fill(evt.nRecoTracks,weight);   
  m_sispseed           -> Fill(evt.nSiSpSeeds,weight);   
  m_nPixelClusters     -> Fill(evt.nPixelClusters,weight); 
  m_nSCTClusters       -> Fill(evt.nSCTClusters,weight); 
  m_nSiClusters        -> Fill(evt.nPixelClusters+evt.nSCTClusters,weight); 
  m_nPixelClusterswide -> Fill(evt.nPixelClusters,weight); 
  m_nSCTClusterswide   -> Fill(evt.nSCTClusters,weight); 
  m_nSiClusterswide    -> Fill(evt.nPixelClusters+evt.nSCTClusters,weight); 
  m_trigWeight         -> Fill(evt.trigCounter,weight);
  m_muValue            -> Fill(evt.muValue,weight);
  m_muValueCorr        -> Fill(evt.muValueCorr,weight);

  m_recotrk1GeV  -> Fill(evt.nRecoTracks1GeV,weight);   
  m_recotrk1GeVwide  -> Fill(evt.nRecoTracks1GeV,weight);   
 
  m_nFake01        -> Fill(evt.nFk01,weight);
  m_nFake02        -> Fill(evt.nFk02,weight);
  m_nFake03        -> Fill(evt.nFk03,weight);
  m_nFake04        -> Fill(evt.nFk04,weight);
  m_nFake05        -> Fill(evt.nFk05,weight);
  m_nFake06        -> Fill(evt.nFk06,weight);
  m_nFake07        -> Fill(evt.nFk07,weight);
  m_nFake08        -> Fill(evt.nFk08,weight);
  m_nFake09        -> Fill(evt.nFk09,weight);
  
  
  for (int i = 0; i < 16; i++) {
    m_FakeVsEta.at(i) -> Fill(evt.nFkBin[i], weight);
  }

  m_nIsoTrack    -> Fill(1.0*evt.nIsoTrack,weight);
  m_nVertex      -> Fill(1.0*evt.nVertex,weight);

  if (evt.nRecoTracks==2) {
    m_average2TrackEta -> Fill( evt.average2TrackEta,weight);
  }

  if (evt.photonEta>-50.0) {
    m_photonEta -> Fill(TMath::Abs(evt.photonEta),weight);
    if (TMath::Abs(evt.photonEta)<0.5) {
      m_photonProdR  -> Fill(evt.photonProdR,weight);
      m_photonDecayR -> Fill(evt.photonDecayR,weight);
    }
    if (evt.nRecoTracks==2) {
      m_photonEta2Track -> Fill(TMath::Abs(evt.photonEta),weight);
      if (TMath::Abs(evt.photonEta)<0.5) {
        m_photonProdR2Track  -> Fill(evt.photonProdR,weight);
        m_photonDecayR2Track -> Fill(evt.photonDecayR,weight);
      }
    }
  }

  m_nTruth        -> Fill(1.0*evt.nTruth,weight);
  m_nChargedTruth -> Fill(1.0*evt.nChargedTruth,weight);
  m_nNeutralTruth -> Fill(1.0*evt.nNeutralTruth,weight);
  m_nTruth1GeV        -> Fill(1.0*evt.nTruth1GeV,weight);
  m_nChargedTruth1GeV -> Fill(1.0*evt.nChargedTruth1GeV,weight);
  m_nNeutralTruth1GeV -> Fill(1.0*evt.nNeutralTruth1GeV,weight);

  if (evt.nChargedTruth1GeV>0 && evt.nRecoTracks1GeV>1) {
    m_effPileupTrack1GeV -> Fill(1.0*(evt.nRecoTracks1GeV-1.0)/evt.nChargedTruth1GeV,weight);
    m_effPileupTrack1GeV_vsTruth -> Fill(1.0*evt.nChargedTruth1GeV,1.0*evt.nRecoTracks1GeV-1.0,weight); //-1 because the muon is not considered in truth count
  }


}

