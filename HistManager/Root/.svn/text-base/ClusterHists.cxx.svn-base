/******************************************
 * Plot of tracks and tracking quantities
 *
 * G. Facini
 * Sep 10 10:03:25 CEST 2014
 *
 * Migrate into rel20. -- Mar  2 11:44:17 CET 2015 S. Tsuno
 *
 ******************************************/

#include <HistManager/ClusterHists.h>


ClusterHists::ClusterHists(TString name) {
   m_name = "ClusterHist_" + name;
   m_label = "Cluster "; // don't forget the space
}

ClusterHists::~ClusterHists() {}

void ClusterHists::BookHists() {

  std::cout << "Creating histograms for " << m_name << std::endl;

  /* layout */
  m_SiliconLayout_full_xy    = declare2D(m_name,"SiliconLayout_full_xy","x[mm]","y[mm]",200,-1100,1100,200,-1100,1100);
  m_SiliconLayout_full_zr    = declare2D(m_name,"SiliconLayout_full_zr","z[mm]","r[mm]",200,-3100,3100,200,   0,1100);
  m_SiliconLayout_quarter_xy = declare2D(m_name,"SiliconLayout_quarter_xy","x[mm]","y[mm]",200,0,1100,200,0,1100);
  m_SiliconLayout_quarter_zr = declare2D(m_name,"SiliconLayout_quarter_zr","z[mm]","r[mm]",200,0,3100,200,0,1100);

  m_PixelLayout_full_xy    = declare2D(m_name,"PixelLayout_full_xy","x[mm]","y[mm]",200,-350,350,200,-350,350);
  m_PixelLayout_full_zr    = declare2D(m_name,"PixelLayout_full_zr","z[mm]","r[mm]",200,-2000,2000,200,   0,350);
  m_PixelLayout_quarter_xy = declare2D(m_name,"PixelLayout_quarter_xy","x[mm]","y[mm]",200,0,350,200,0,350);
//  m_PixelLayout_quarter_zr = declare2D(m_name,"PixelLayout_quarter_zr","z[mm]","r[mm]",200,0,2000,200,0,350);
  m_PixelLayout_quarter_zr = declare2D(m_name,"PixelLayout_quarter_zr","z[mm]","r[mm]",800,0,200,200,30,50);

  /* positions */
  m_localX = declare1D(m_name, "localX", m_label + "local X [mm]",    120, -9., 9. );
  m_localY = declare1D(m_name, "localY", m_label + "local Y [mm]",    120, -31., 31. );
  m_localXError = declare1D(m_name, "localXError", m_label + "local X error [mm]",    60, 0., 5. );
  m_localYError = declare1D(m_name, "localYError", m_label + "local Y error [mm]",    60, 0., 20. );
  m_globalX = declare1D(m_name, "globalX", m_label + "global X [mm]",    150, -150., 150. );
  m_globalY = declare1D(m_name, "globalY", m_label + "global Y [mm]",    150, -150., 150. );
  m_globalZ = declare1D(m_name, "globalZ", m_label + "global Z [mm]",    100, -200., 200. );


  /* basic properties */
  m_layer   = declare1D(m_name, "layer",   m_label + "layer",     4,  -0.5, 3.5 );
  m_nPart   = declare1D(m_name, "nPart",   m_label + "N Particles",  10, -0.5, 9.5);
  m_nPriPart= declare1D(m_name, "nPriPart",m_label + "N Primary Particles",  10, -0.5, 9.5);
  m_size    = declare1D(m_name, "size",    m_label + "Size",      20, -0.5, 19.5);
  m_sizePhi = declare1D(m_name, "sizePhi", m_label + "Size #phi", 10, -0.5, 9.5);
  m_sizeZ   = declare1D(m_name, "sizeZ",   m_label + "Size z",    10, -0.5, 9.5);
  m_charge  = declare1D(m_name, "charge",  m_label + "charge [e]",120, 0., 240e3);
  m_ToT     = declare1D(m_name, "ToT",     m_label + "ToT [bc]",  120, 0., 240.);
  m_isFake  = declare1D(m_name, "isFake",  m_label + "Is Fake",   2, -0.5, 1.5);
  m_gangedPixel = declare1D(m_name, "gangedPixel", m_label + "Ganged Pixel",   2, -0.5, 1.5);
  m_isSplit     = declare1D(m_name, "isSplit",     m_label + "Is Split",   2, -0.5, 1.5);
  m_splitProb1  = declare1D(m_name, "splitProb1",  m_label + "Split Prob: 2 Trk Hypo",   100, -1.0, 1.0);
  m_splitProb2  = declare1D(m_name, "splitProb2",  m_label + "Split Prob: 3 Trk Hypo",   100, -1.0, 1.0);
  m_NN_sizeX = declare1D(m_name, "sizeX", m_label + "Size x", 10, -0.5, 9.5);
  m_NN_sizeY = declare1D(m_name, "sizeY", m_label + "Size y", 10, -0.5, 9.5);
  m_NN_phiBS = declare1D(m_name, "NN_phiBS", m_label + "NN phi BS", 120, 0.0, 0.40);
  m_NN_thetaBS = declare1D(m_name, "NN_thetaBS", m_label + "NN theta BS", 100, -1.0, 1.0);

  /* fun with 2D */
  m_size_VS_charge    = declare2D( m_name, "size_VS_charge",    m_label + "Size",      m_label + "charge [e]", 20, -0.5, 19.5, 60, 0., 240e3 );
  m_sizePhi_VS_charge = declare2D( m_name, "sizePhi_VS_charge", m_label + "Size #phi", m_label + "charge [e]", 10, -0.5, 9.5, 60, 0., 240e3 );
  m_sizeZ_VS_charge   = declare2D( m_name, "sizeZ_VS_charge",   m_label + "Size z",    m_label + "charge [e]", 10, -0.5, 9.5, 60, 0., 240e3 );
  m_size_VS_ToT       = declare2D( m_name, "size_VS_ToT",       m_label + "Size",      m_label + "ToT [bc]", 20, -0.5, 19.5, 60, 0., 240 );
  m_sizePhi_VS_ToT    = declare2D( m_name, "sizePhi_VS_ToT",    m_label + "Size #phi", m_label + "ToT [bc]", 10, -0.5, 9.5, 60, 0., 240 );
  m_sizeZ_VS_ToT      = declare2D( m_name, "sizeZ_VS_ToT",      m_label + "Size z",    m_label + "ToT [bc]", 10, -0.5, 9.5, 60, 0., 240 );


} // BookHists

void ClusterHists::FillHists(const xAOD::TrackMeasurementValidation* prd, float weight) const {

  /* layout */
  double rrr = sqrt(prd->globalX()*prd->globalX()+prd->globalY()*prd->globalY());
  if (rrr<380.0) {
    m_SiliconLayout_full_zr    -> Fill(prd->globalZ(),rrr);
    m_SiliconLayout_quarter_zr -> Fill(prd->globalZ(),rrr);
    m_PixelLayout_full_zr      -> Fill(prd->globalZ(),rrr);
    m_PixelLayout_quarter_zr   -> Fill(prd->globalZ(),rrr);
    if (fabs(prd->globalZ())<750.0) {
      m_SiliconLayout_full_xy    -> Fill(prd->globalX(),prd->globalY());
      m_SiliconLayout_quarter_xy -> Fill(prd->globalX(),prd->globalY());
      m_PixelLayout_full_xy      -> Fill(prd->globalX(),prd->globalY());
      m_PixelLayout_quarter_xy   -> Fill(prd->globalX(),prd->globalY());
    }
  }
  if (rrr>380.0) {
    m_SiliconLayout_full_zr    -> Fill(prd->globalZ(),rrr);
    m_SiliconLayout_quarter_zr -> Fill(prd->globalZ(),rrr);
    if (fabs(prd->globalZ())<1350.0) {
      m_SiliconLayout_full_xy    -> Fill(prd->globalX(),prd->globalY());
      m_SiliconLayout_quarter_xy -> Fill(prd->globalX(),prd->globalY());
    }
  }

  /* positions */
  m_localX -> Fill(prd->localX(),weight);
  m_localY -> Fill(prd->localY(),weight);
  m_localXError -> Fill(prd->localXError(),weight);
  m_localYError -> Fill(prd->localYError(),weight);
  m_globalX -> Fill(prd->globalX(),weight);
  m_globalY -> Fill(prd->globalY(),weight);
  m_globalZ -> Fill(prd->globalZ(),weight);

  /* basic properties */
  m_layer -> Fill(prd->auxdata<int>("layer"),weight);
  if (prd->isAvailable<int>("nParticles")) {
    m_nPart    -> Fill(prd->auxdata<int>("nParticles"),weight);
    m_nPriPart -> Fill(prd->auxdata<int>("nPrimaryParticles"),weight);
  }

  // only store for pixel
  if (rrr<380.0) {
    m_size    -> Fill(prd->auxdata<int>("size"),weight);
    m_sizePhi -> Fill(prd->auxdata<int>("sizePhi"),weight);
    m_sizeZ   -> Fill(prd->auxdata<int>("sizeZ"),weight);
    m_charge  -> Fill(prd->auxdata<float>("charge"),weight);
    m_ToT     -> Fill(prd->auxdata<int>("ToT"),weight);
    m_isFake  -> Fill(prd->auxdata<char>("isFake"),weight);
    m_gangedPixel -> Fill(prd->auxdata<char>("gangedPixel"),weight);
    m_isSplit     -> Fill(prd->auxdata<int>("isSplit"),weight);
    m_splitProb1  -> Fill(prd->auxdata<float>("splitProbability1"),weight);
    m_splitProb2  -> Fill(prd->auxdata<float>("splitProbability2"),weight);
    //  m_NN_sizeX    -> Fill( prd->auxdata< int >( "NN_sizeX" ) );
    //  m_NN_sizeY    -> Fill( prd->auxdata< int >( "NN_sizeY" ) );
    //  m_NN_phiBS    -> Fill( prd->auxdata< float >( "NN_phiBS" ) );
    //  m_NN_thetaBS  -> Fill( prd->auxdata< float >( "NN_thetaBS" ) );

    /* fun with 2D */
    m_size_VS_charge    -> Fill(prd->auxdata<int>("size"),    prd->auxdata<float>("charge"),weight);
    m_sizePhi_VS_charge -> Fill(prd->auxdata<int>("sizePhi"), prd->auxdata<float>("charge"),weight);
    m_sizeZ_VS_charge   -> Fill(prd->auxdata<int>("sizeZ"),   prd->auxdata<float>("charge"),weight);
    m_size_VS_ToT       -> Fill(prd->auxdata<int>("size"),    prd->auxdata<int>("ToT"),weight);
    m_sizePhi_VS_ToT    -> Fill(prd->auxdata<int>("sizePhi"), prd->auxdata<int>("ToT"),weight);
    m_sizeZ_VS_ToT      -> Fill(prd->auxdata<int>("sizeZ"),   prd->auxdata<int>("ToT"),weight);
  }

} // FillHists

