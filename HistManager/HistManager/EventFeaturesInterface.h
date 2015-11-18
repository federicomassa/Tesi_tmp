#ifndef HistManager_EventFeaturesInterface_H
#define HistManager_EventFeaturesInterface_H

// c++ include(s):
#include <iostream>

class EventFeatures {

  public:
    unsigned int	nPseudoTracks;
    unsigned int	nSecondaryPseudoTracks;    
    unsigned int	nPrimaryPseudoTracks;	
    unsigned int	nLostPseudoTracks;	     
    unsigned int	nRecoTracks;
    unsigned int	nRecoTracks1GeV;

    unsigned int        nFk01;
    unsigned int        nFk02;
    unsigned int        nFk03;
    unsigned int        nFk04;
    unsigned int        nFk05;
    unsigned int        nFk06;
    unsigned int        nFk07;
    unsigned int        nFk08;
    unsigned int        nFk09;

    unsigned int        nFkBin[16];

    unsigned int	nSiSpSeeds;
    unsigned int	nPixelClusters;
    unsigned int	nSCTClusters; 
    unsigned int	nSiClusters; 
    unsigned int  trigCounter;
    float         muValue;
    float         muValueCorr;

    // for ITk
    float average2TrackEta;
    float photonEta;
    float photonProdR;
    float photonDecayR;
    unsigned int  nTruth;
    unsigned int  nChargedTruth;
    unsigned int  nNeutralTruth;
    unsigned int  nTruth1GeV;
    unsigned int  nChargedTruth1GeV;
    unsigned int  nNeutralTruth1GeV;
    unsigned int nIsoTrack;
    unsigned int nVertex;

    EventFeatures() {
      nPseudoTracks = -1;
      nSecondaryPseudoTracks = -1;
      nPrimaryPseudoTracks = -1; 
      nRecoTracks = -1;
      nRecoTracks1GeV = -1;
      nFk01 = -1;
      nFk02 = -1;
      nFk03 = -1;
      nFk04 = -1;
      nFk05 = -1;
      nFk06 = -1;
      nFk07 = -1;
      nFk08 = -1;
      nFk09 = -1;
      nSiSpSeeds = -1;
      nPixelClusters = -1;
      nSCTClusters = -1;
      nSiClusters = -1;
      trigCounter = -1;
      muValue = 0.0;
      muValueCorr = 0.0;
      average2TrackEta = 0.0;
      photonEta = -100.0;
      photonProdR = -100.0;
      photonDecayR = -100.0;
      nTruth = -1;
      nChargedTruth = -1;
      nNeutralTruth = -1;
      nTruth1GeV = -1;
      nChargedTruth1GeV = -1;
      nNeutralTruth1GeV = -1;
      nIsoTrack = -1;
      nVertex = -1;
    };

    void dumpInfo() {
      std::cout << "*************************************** " << std::endl;
      std::cout << "  " << std::endl;
      std::cout << "nPseudoTracks in Event: "          <<  nPseudoTracks	<< std::endl;
      std::cout << "nPrimaryPseudoTracks in Event : "  <<  nPrimaryPseudoTracks	<< std::endl;	
      std::cout << "nSecondaryPseudoTracks in Event: " <<  nSecondaryPseudoTracks   << std::endl;
      std::cout << "nLostPseudoTracks in Event: "      <<  nLostPseudoTracks   << std::endl;
      std::cout << "nRecoTracks in Event: "	     <<  nRecoTracks   << std::endl;
      std::cout << "nSiSpSeeds in Event: "             <<  nSiSpSeeds    << std::endl;
      std::cout << "nPixelClusters in Event: "         <<  nPixelClusters << std::endl;
      std::cout << "nSCTClusters in Event: "           <<  nSCTClusters  << std::endl;
      std::cout << "nSiClusters in Event: "            <<  nSiClusters  << std::endl;    
      std::cout << "  " << std::endl;    
      std::cout << "*************************************** " << std::endl;    
    };  

};
#endif //ParticleAnalysis_EventFeaturesInterface_H
