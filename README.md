Commit messages legend:
W: working
NW: not working - no clue
PW: not working - resolving

In this file:
U: possible update necessary


 --------------
|PLOTS AND CUTS|
 --------------


//////// TAGLI NEL FILLHIST ///////////

trkHist_all:		2000 < pt < 200000 [MeV]
truHist_all: 		2000 < pt < 200000 [MeV]

trkHist_reco:		mindRMatched < 0.1		
truHist_stable:       	truth->pt() - m_EnergyTarget < 0.1 [MeV]
			truth->pdgId() == m_idTarget
			
//////// TAGLI NEL FILL (HIST MANAGER) ///////////

Truth:
	ptGun: none
	eta:   none
	phi:   none

Track:
	pt: none
	ptGun: none
	ptnarrow: none
	eta: none 
	d0: none
	z0: none
	phi: none
	absetaGun: nSiHits > 10
	abseta: !!! Fills truthParticle->eta() !!!
	biasXXX: if(truthParticle)
	nSiHits: none
	nPixHits: none
	nSCTHits: none
	nSiFakeHits: if(isFake)
	...
	nSiTrueHits: if(!isFake)
	...
	eta_nSiHits: if (truthParticle)
	eta_nFakeSiHits: if (truthParticle && isFake)	
	...
	FakeGunVsEta: if (truthParticle)	
	fakeGun_bin: if (truthParticle)
	
Event:
	FakeVsEta: none - uses nFake_bin
	nFake_bin: none - filled by nFkBin[i]

EventInterface: 
	nFkBin[i]: truth link, isFake, interval eta, trkHist_all pt cuts
	           - filled by numFkBin in ITkStudy

/////// PLOTS (eff_all.cxx) ////////

Bias plots: ONLY FOR GUN - OKAY
     	    - requires only truthParticle link existence
	    - takes every track linked with truth, computes 
	      bias distribution for several eta intervals,
	      then computes RMS value of every distribution
	    - several plots are as a function of TRUTH eta
	           	    	 
Fake plots: OKAY
     	    fakeGun_average - TGraphErrors, points taken from mean 
     	                      of fakeGun_binXX distribution as a function 
			      of |eta|
	    fake_average - same as before but fake of every track, points
	    		   taken from mean of nFake_binXX in EventHist..
	    		   So, takes every fake track whose truth link
			   exists and whose pt is bounded as trkHist_all
	    - several plots are as a function of TRUTH eta

Efficiency: ONLY FOR GUN, SO OKAY
	    divide bin by bin ptGun/eta/phi distributions
U	    WARNING: if extended to all particles, TruthParticle pt/eta/phi
	             fill has to be restricted to charged particles.
Hits:       ONLY FOR GUN, SO OKAY
	    for every track, takes the number of total,pix or SCT hits
	    divided for fake and !fake tracks
U	    - should be ready for hits as a function of eta,
	      statistics problem for fakes
