#ifndef HistManager_TrackHists_H
#define HistManager_TrackHists_H

#include "HistManager/ManageHists.h"
#include <set>
#include <sstream>
#include <TMath.h>

#ifndef __MAKECINT__
#include "xAODTracking/TrackParticle.h"
#endif // not __MAKECINT__

class TrackHists : public ManageHists {

  public:

    TrackHists(TString name);
    ~TrackHists();

    void BookHists();
#ifndef __MAKECINT__
    void FillHists(const xAOD::TrackParticle* trk, float weight) const;


    //* Determine if the TruthParticle has been used before */
    bool hasBeenUsed( const xAOD::TrackParticle* trk) {
      if (m_usedBarcodes.find(trk->auxdata<int>("barcode"))==m_usedBarcodes.end()) { return false; } 
      else { return true; }
    }

    //* Determine if the TruthParticle has been used before */
    void resetBarcodes() {
      m_usedBarcodes.clear();
    }

#endif // not __MAKECINT__

  private:

    TString m_name;
    TString m_label;
    bool m_isPseudo;
    mutable std::set<int> m_usedBarcodes; //!
    int m_FakeBin = 16;
  public:

    /* particle properties */
    TH1F* m_prodR; //!
    TH1F* m_prodZ; //!
    TH1F* m_truthPt; //!
    TH1F* m_truthPtnarrow; //!
    TH1F* m_truthEta; //!
    TH1F* m_truthD0; //!
    TH1F* m_truthD0_wide; //!
    TH1F* m_truthZ0; //!
    TH1F* m_truthPhi; //!
    TH1F* m_biasPt; //!
    TH1F* m_biasQPt; //!
    TH1F* m_biasEta; //!
    TH1F* m_biasPhi; //!
    TH1F* m_biasD0; //!
    TH1F* m_biasZ0; //!

    TH1F* m_biasPt_bin1; //!
    TH1F* m_biasPt_bin2; //!
    TH1F* m_biasPt_bin3; //!
    TH1F* m_biasPt_bin4; //!
    TH1F* m_biasPt_bin5; //!
    TH1F* m_biasPt_bin6; //!
    TH1F* m_biasPt_bin7; //!
    TH1F* m_biasPt_bin8; //!
    TH1F* m_biasPt_bin9; //!
    TH1F* m_biasPt_bin10; //!
    TH1F* m_biasPt_bin11; //!
    TH1F* m_biasPt_bin12; //!
    TH1F* m_biasPt_bin13; //!
    TH1F* m_biasPt_bin14; //!
    TH1F* m_biasPt_bin15; //!
    TH1F* m_biasPt_bin16; //!

    TH1F* m_biasQPt_bin1; //!
    TH1F* m_biasQPt_bin2; //!
    TH1F* m_biasQPt_bin3; //!
    TH1F* m_biasQPt_bin4; //!
    TH1F* m_biasQPt_bin5; //!
    TH1F* m_biasQPt_bin6; //!
    TH1F* m_biasQPt_bin7; //!
    TH1F* m_biasQPt_bin8; //!
    TH1F* m_biasQPt_bin9; //!
    TH1F* m_biasQPt_bin10; //!
    TH1F* m_biasQPt_bin11; //!
    TH1F* m_biasQPt_bin12; //!
    TH1F* m_biasQPt_bin13; //!
    TH1F* m_biasQPt_bin14; //!
    TH1F* m_biasQPt_bin15; //!
    TH1F* m_biasQPt_bin16; //!

    TH1F* m_biasPhi_bin1; //!
    TH1F* m_biasPhi_bin2; //!
    TH1F* m_biasPhi_bin3; //!
    TH1F* m_biasPhi_bin4; //!
    TH1F* m_biasPhi_bin5; //!
    TH1F* m_biasPhi_bin6; //!
    TH1F* m_biasPhi_bin7; //!
    TH1F* m_biasPhi_bin8; //!
    TH1F* m_biasPhi_bin9; //!
    TH1F* m_biasPhi_bin10; //!
    TH1F* m_biasPhi_bin11; //!
    TH1F* m_biasPhi_bin12; //!
    TH1F* m_biasPhi_bin13; //!
    TH1F* m_biasPhi_bin14; //!
    TH1F* m_biasPhi_bin15; //!
    TH1F* m_biasPhi_bin16; //!

    TH1F* m_biasD0_bin1; //!
    TH1F* m_biasD0_bin2; //!
    TH1F* m_biasD0_bin3; //!
    TH1F* m_biasD0_bin4; //!
    TH1F* m_biasD0_bin5; //!
    TH1F* m_biasD0_bin6; //!
    TH1F* m_biasD0_bin7; //!
    TH1F* m_biasD0_bin8; //!
    TH1F* m_biasD0_bin9; //!
    TH1F* m_biasD0_bin10; //!
    TH1F* m_biasD0_bin11; //!
    TH1F* m_biasD0_bin12; //!
    TH1F* m_biasD0_bin13; //!
    TH1F* m_biasD0_bin14; //!
    TH1F* m_biasD0_bin15; //!
    TH1F* m_biasD0_bin16; //!

    TH1F* m_biasZ0_bin1; //!
    TH1F* m_biasZ0_bin2; //!
    TH1F* m_biasZ0_bin3; //!
    TH1F* m_biasZ0_bin4; //!
    TH1F* m_biasZ0_bin5; //!
    TH1F* m_biasZ0_bin6; //!
    TH1F* m_biasZ0_bin7; //!
    TH1F* m_biasZ0_bin8; //!
    TH1F* m_biasZ0_bin9; //!
    TH1F* m_biasZ0_bin10; //!
    TH1F* m_biasZ0_bin11; //!
    TH1F* m_biasZ0_bin12; //!
    TH1F* m_biasZ0_bin13; //!
    TH1F* m_biasZ0_bin14; //!
    TH1F* m_biasZ0_bin15; //!
    TH1F* m_biasZ0_bin16; //!
    
    // Fakes
    std::vector<TH1F*> m_FakeGunVsEta; //!

    /* track parameterization */
    TH1F* m_qoverp; //!     
    TH1F* m_pt; //!
    TH1F* m_ptGun; //!
    TH1F* m_ptnarrow; //!       
    TH1F* m_eta; //!        
    TH1F* m_absetaGun; //!
    TH1F* m_phi; //!        
    TH1F* m_phiTruth; //!        
    TH1F* m_d0; //!       
    TH1F* m_z0; //!       
    TH1F* m_z0Corr1; //!       
    TH1F* m_z0Corr2; //!       

    // Added by Federico Massa
    TH1F* m_x0; //!
    TH1F* m_y0; //!

    /* track parameterization errors */
    TH1F* m_qoverp_err; //!       
    TH1F* m_eta_err; //!        
    TH1F* m_d0_err; //!       
    TH1F* m_d0signif; //!       
    TH1F* m_z0_err; //!       
    TH1F* m_phi_err; //!        

    TH1F* m_d0sign; //!       
    TH1F* m_d0signsig; //!       
    TH1F* m_d0signsigP; //!       
    TH1F* m_d0signsigN; //!       

    /* track properties */
    TH1F* m_nPixHits; //! 
    TH1F* m_nSCTHits; //! 
    TH1F* m_nSiHits; //!

    TH2F* m_eta_nPixHits; //!
    TH2F* m_eta_nSCTHits; //!
    TH2F* m_eta_nSiHits; //!

    TH1F* m_nTruePixHits; //! 
    TH1F* m_nTrueSCTHits; //! 
    TH1F* m_nTrueSiHits; //!

    TH2F* m_eta_nTruePixHits; //!
    TH2F* m_eta_nTrueSCTHits; //!
    TH2F* m_eta_nTrueSiHits; //!

    TH1F* m_nFakePixHits; //! 
    TH1F* m_nFakeSCTHits; //! 
    TH1F* m_nFakeSiHits; //!

    TH2F* m_eta_nFakePixHits; //!
    TH2F* m_eta_nFakeSCTHits; //!
    TH2F* m_eta_nFakeSiHits; //!

    TH1F* m_nGangedPix; //! 
    TH1F* m_nGangedPixFF; //! 
    TH1F* m_nPixLay; //! 
    TH1F* m_nPixSharedHits; //!        
    TH1F* m_nPixSplitHits; //!        
    TH1F* m_nPixSpoiltHits; //!       
    TH1F* m_nPixOutliers; //!       
    TH1F* m_nPixHoles; //!        
    TH1F* m_nPixelDeadSensors; //! 
    TH1F* m_nSCTSharedHits; //!       
    TH1F* m_nSCTSpoiltHits; //!       
    TH1F* m_nSCTOutliers; //!       
    TH1F* m_nSCTHoles; //!   
    TH1F* m_nSCTDoubleHoles; //!        
    TH1F* m_nSCTDeadSensors; //!
    TH1F* m_nSiDeadSensors; //!

    TH1F* m_nTRTHits; //! 
    TH1F* m_nTRTOutliers; //!       
    TH1F* m_nTRTHoles; //!        
    TH1F* m_nTRTHTHits; //! 

    TH1F* m_chiSqPerDof; //!
    TH1F* m_nOutliers; //!
    TH1F* m_stdDevChi2OS; //!
    TH1F* m_eProbComb; //!
    TH1F* m_eProbHT; //!
    TH1F* m_eProbToT; //!
    TH1F* m_eProbBrem; //!

    TH1F* m_truthMatchProb; //!
    TH1F* m_matchingDR; //!
    TH1F* m_abseta; //!
    TH1F* m_abseta_dr001; //!
    TH1F* m_abseta_dr002; //!
    TH1F* m_abseta_dr003; //!
    TH1F* m_abseta_dr004; //!
    TH1F* m_abseta_dr005; //!
    TH1F* m_abseta_dr006; //!
    TH1F* m_abseta_dr007; //!
    TH1F* m_abseta_dr008; //!
    TH1F* m_abseta_dr009; //!
    
};

#endif //HistManager_TrackHists_H
