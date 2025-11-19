/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate collision events in Pythia and cluster particles with FastJet3
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include <fstream>
#include <sstream>
// Pythia
#include "Pythia8/Pythia.h"
#include "Pythia8/Basics.h"
// Fastjet
#include "fjcore.hh"
// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "TPaveStats.h"
#include "TList.h"
#include "TLorentzVector.h"
// Header
using namespace Pythia8;
using namespace std;
using namespace fjcore;
// Extras

// Code
int main(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create output TTree file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define file
  	TFile *output = new TFile("gen_TES500.root", "recreate");
	// Anti-crash
	if (!output->IsOpen()) {
		cerr << "Error opening output file!" << endl;
		return 1;
	}
	
	// Define tree
	TTree *tree = new TTree("tree", "tree");

	// Intialise tree branch vars
	int eveNum, eveSiz, parNum, parPdg;
	double parMas, parPmx, parPmy, parPmz, parPmt, parEta, parPhi;

	// Define particle branches
	tree->Branch("eveNum", &eveNum, "eveNum/I");
	tree->Branch("eveSiz", &eveSiz, "eveSiz/I");
	tree->Branch("parNum", &parNum, "parNum/I");
	tree->Branch("parPdg", &parPdg, "parPdg/I");
	tree->Branch("parMas", &parMas, "parMas/D");
	tree->Branch("parPmx", &parPmx, "parPmx/D");
	tree->Branch("parPmy", &parPmy, "parPmy/D");
	tree->Branch("parPmz", &parPmz, "parPmz/D");
	tree->Branch("parPmt", &parPmt, "parPmt/D");
	tree->Branch("parEta", &parEta, "parEta/D");
	tree->Branch("parPhi", &parPhi, "parPhi/D");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Histograms, Add branches
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1D *hist_nChPyth = new TH1D("hist_nChPyth", "Charged Hadron Multiplicity distributions", 50, 0, 100);
	tree->Branch("hist_nChPyth", &hist_nChPyth, "hist_nChPyth");

	TH1D *hist_nJetsCh = new TH1D("hist_nJetsCh", "Hadronic Jet Multiplicity distributions", 100, 0, 5);
	tree->Branch("hist_nJetsCh", &hist_nJetsCh, "hist_nJetsCh");

	TH1D *hist_nJetsFr = new TH1D("hist_nJetsFr", "Hadronic Jet Constituent multiplicity distributions", 30, 0, 30);
	tree->Branch("hist_nJetsFr", &hist_nJetsFr, "hist_nJetsFr");

	TH1D *hist_nParton = new TH1D("hist_nParton", "Intermediate Parton Multiplicity distributions", 25, 0, 100);
	tree->Branch("hist_nParton", &hist_nParton, "hist_nParton");

	TH1D *hist_nPQuark = new TH1D("hist_nPQuark", "Intermediate Quark Multiplicity distributions", 100, 0, 100);
	tree->Branch("hist_nPQuark", &hist_nPQuark, "hist_nPQuark");

	TH1D *hist_nPGluon = new TH1D("hist_nPGluon", "Intermediate Gluon Multiplicity distributions", 25, 0, 100);
	tree->Branch("hist_nPGluon", &hist_nPGluon, "hist_nPGluon");

	TH1D *hist_Spheric = new TH1D("hist_Spheric", "Sphericity distributions", 100, 0., 1.);
	tree->Branch("hist_Spheric", &hist_Spheric, "hist_Spheric");

	TH1D *hist_Aplanar = new TH1D("hist_Aplanar", "Aplanarity distributions", 100, 0., 1.);
	tree->Branch("hist_Aplanar", &hist_Aplanar, "hist_Aplanar");

	TH1D *hist_Lineric = new TH1D("hist_Lineric", "Linearised Sphericity distributions", 100, 0., 1.);
	tree->Branch("hist_Lineric", &hist_Lineric, "hist_Lineric");

	float xbin[] = {0.00E+00,1.00E-02,2.00E-02,3.00E-02,4.00E-02,5.00E-02,7.00E-02,9.00E-02,1.20E-01,1.50E-01,2.20E-01,3.00E-01,4.00E-01};
	TH1D *hist_ThrustP = new TH1D("hist_ThrustP", "Thrust distributions", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	tree->Branch("hist_ThrustP", &hist_ThrustP, "hist_ThrustP");

	TH1D *hist_ThMajor = new TH1D("hist_ThMajor", "Thrust Major distributions", 100, 0., 1.);
	tree->Branch("hist_ThMajor", &hist_ThMajor, "hist_ThMajor");

	TH1D *hist_ThMinor = new TH1D("hist_ThMinor", "Thrust Minor distributions", 100, 0., 1.);
	tree->Branch("hist_ThMinor", &hist_ThMinor, "hist_ThMinor");

	TH1D *hist_Oblatey = new TH1D("hist_Oblatey", "Oblateness distributions", 100, 0., 1.);
	tree->Branch("hist_Oblatey", &hist_Oblatey, "hist_Oblatey");

	TH1D *hist_sphAxis = new TH1D("hist_sphAxis", "Sphericity axis distributions", 100, -1., 1.);
	tree->Branch("hist_sphAxis", &hist_sphAxis, "hist_sphAxis");

	TH1D *hist_linAxis = new TH1D("hist_linAxis", "Linearity axis distributions", 100, -1., 1.);
	tree->Branch("hist_linAxis", &hist_linAxis, "hist_linAxis");

	TH1D *hist_thrAxis = new TH1D("hist_thrAxis", "Thrust axis distributions", 100, -1., 1.);
	tree->Branch("hist_thrAxis", &hist_thrAxis, "hist_thrAxis");

	TH1D *hist_nChLund = new TH1D("hist_nChLund", "Lund Jet multiplicity", 40, -0.5, 39.5);
	tree->Branch("hist_nChLund", &hist_nChLund, "hist_nChLund");

	TH1D *hist_nChJade = new TH1D("hist_nChJade", "Jade jet multiplicity", 40, -0.5, 39.5);
	tree->Branch("hist_nChJade", &hist_nChJade, "hist_nChJade");

	TH1D *hist_nChDurh = new TH1D("hist_nChDurh", "Durham jet multiplicity", 40, -0.5, 39.5);
	tree->Branch("hist_nChDurh", &hist_nChDurh, "hist_nChDurh");

	TH1D *hist_difLund = new TH1D("hist_difLund", "Lund e_i - e_{i+1}", 100, -5.,45.);
	tree->Branch("hist_difLund", &hist_difLund, "hist_difLund");

	TH1D *hist_difJade = new TH1D("hist_difJade", "Jade e_i - e_{i+1}", 100, -5.,45.);
	tree->Branch("hist_difJade", &hist_difJade, "hist_difJade");

	TH1D *hist_difDurh = new TH1D("hist_difDurh", "Durham e_i - e_{i+1}", 100, -5.,45.);
	tree->Branch("hist_difDurh", &hist_difDurh, "hist_difDurh");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Pythia params
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Set # of events
	int nEvent = 1e4;

	// Store masses
	double mZ = pythia.particleData.m0(23);						// Z0 mass
	double mW = pythia.particleData.m0(24);						// W+ mass

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// QCD processes
	pythia.readString("HardQCD:all = off");						// master switch

	// Electroweak boson processes
	pythia.readString("WeakZ0:gmZmode = 0");					// allow γ* or Z channels
	// pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gm));	// ee'->qq'
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");		// ee'->γ*/Z
	// pythia.readString("WeakSingleBoson:ffbar2W = on");		// ee'->W
	pythia.readString("WeakDoubleBoson:ffbar2gmZgmZ = on");		// ee'->γ*γ*ZZ
	pythia.readString("WeakDoubleBoson:ffbar2ZW = off");		// ee'->ZW
	pythia.readString("WeakDoubleBoson:ffbar2WW = on");			// ee'->WW
	// Boson decays
	pythia.readString("23:onMode = off");						// turn off Z production
	pythia.readString("23:onIfAny = 1 2 3 4 5 6");				// turn on Z iff (duscbt)
	pythia.readString("24:onMode = off");						// turn off W production
	pythia.readString("24:onIfAny = 1 2 3 4 5 6 15");			// turn on W iff (duscbt and τν)

	// Electroweak photon-parton processes
	pythia.readString("PhotonParton:ggm2qqbar = off");			// gγ->qq' (uds)
	pythia.readString("PhotonParton:ggm2ccbar = off");			// gγ->cc'
	pythia.readString("PhotonParton:ggm2bbbar = off");			// gγ->bb'
	pythia.readString("PhotonParton:qgm2qg = off");				// gγ->qq'
	pythia.readString("PhotonParton:qgm2qgm = off");			// gγ->qq'

	// Top processes
	pythia.readString("Top:ffbar2ttbar(s:gmZ) = on");			// ee'->tt'

	// Photon processes
	pythia.readString("PhotonCollision:all = off");
	pythia.readString("PhotonCollision:gmgm2qqbar = off");		// γγ->qq'
	pythia.readString("PhotonCollision:gmgm2ccbar = off");		// γγ->cc'
	pythia.readString("PhotonCollision:gmgm2bbbar = off");		// γγ->bb'
	pythia.readString("PhotonCollision:gmgm2ee = off");			// γγ->ee'
	pythia.readString("PhotonCollision:gmgm2mumu = off");		// γγ->μμ'
	pythia.readString("PhotonCollision:gmgm2tautau = off");		// γγ->ττ'

	// ISR processes
	pythia.readString("TimeShower:QEDshowerByL = on");			// ee->γee
	pythia.readString("TimeShower:QEDshowerByQ = off");			// qq->γqq
	pythia.readString("SpaceShower:QEDshowerByL = on");			// ee->γee
	pythia.readString("SpaceShower:QEDshowerByQ = off");		// qq->γqq

	// Define Beam params
	pythia.readString("Beams:idA = 11"); 						// Beam A energy
	pythia.readString("Beams:idB = -11"); 						// Beam B energy
	pythia.settings.parm("Beams:eCM", 500);						// Set centre-of-mass
	pythia.readString("PDF:lepton = off");						// Disable substructure

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Define physics
	// pythia.readString("HardQCD:all = off"); 						// master switch
	// pythia.readString("WeakSingleBoson:ffbar2gmZ = on");			// ee->gamma*/Z/W->ff
	// pythia.readString("23:onMode = off");							// turn off Z production
	// pythia.readString("23:onIfAny = 1 2 3 4 5");					// turn on Z iff (duscb)

	// // Define Beam params
	// pythia.readString("Beams:idA = 11"); 							// Beam A energy
	// pythia.readString("Beams:idB = -11"); 							// Beam B energy
	// pythia.settings.parm("Beams:eCM", mZ);							// Set centre-of-mass
	// pythia.readString("PDF:lepton = off");							// Disable substructure

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Suppress terminal text
	pythia.readString("Next:numberCount = 1000");
	pythia.readString("Next:numberShowProcess = 0");
	pythia.readString("Init:showMultipartonInteractions = off");
	pythia.readString("Init:showChangedSettings = off");
	pythia.readString("Init:showChangedParticleData = off");
	pythia.readString("Next:numberCount = 0");
	pythia.readString("Next:numberShowInfo = 0");
	pythia.readString("Next:numberShowEvent = 0");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generate Pythia collisions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();

	// Anti-crash
	if (!pythia.init()) return 1;

	// Define analyses
	Sphericity sph;
	Sphericity lin(1.);
	Thrust thr;
	ClusterJet lund("Lund");
	ClusterJet jade("Jade");
	ClusterJet durham("Durham");

	// Counters
	double sigmaTotal = 0.0;

	// Run through events
	for(int iEvent = 0; iEvent < nEvent; iEvent++ ) {

		// Anti-crash
		if(!pythia.next()) continue;
		
		// Print event#
		// cout << "\tEvent#" << iEvent << endl;
		
		// Counters
		int nCh = 0;		// Charged Hadron Multiplicity
		int nJc = 0;		// Jet multiplicity
		int nJf = 0;		// Jet fraction
		int nCp = 0;		// Intermediate parton
		int nCq = 0;		// Intermediate quarks
		int nCg = 0;		// Intermediate gluons

		// FJ event vector
		vector<PseudoJet> particles;

		// Run through particles
		for(int j = 0; j < pythia.event.size(); j++) {
			
			// Hadron check
			if(pythia.event[j].isFinal() && pythia.event[j].isCharged() && pythia.event[j].isHadron()) {
				
				////////////////////////// STORING PARTICLE PARAMETERS //////////////////////////
				eveNum = iEvent;														// Store event number
				eveSiz = pythia.event.size();											// Store event size
				parNum = j;																// Store particle number
				parPdg = pythia.event[j].id();											// Store particle pdg id
				parMas = pythia.event[j].m();											// Store particle mass
				parPmx = pythia.event[j].px();											// Store particle momentum-x
				parPmy = pythia.event[j].py();											// Store particle momentum-y
				parPmz = pythia.event[j].pz();											// Store particle momentum-z
				parPmt = pythia.event[j].pT();											// Store particle momentum-t
				parEta = pythia.event[j].eta();											// Store particle rapidity
				parPhi = pythia.event[j].phi();											// Store particle azimuthal

				////////////////////////// COUNTING HADRONIC NCH CURVE //////////////////////////
				nCh++;																	// Update counter

				////////////////////////// STORING FASTJETS PARAMETERS //////////////////////////
				PseudoJet particle(parPmx, parPmy, parPmz, parMas);						// FJ particle vector
				particle.set_user_index(parPdg);										// Store particle pdg
				particles.push_back(particle);											// Add particle to event

				////////////////////////// CLUSTERING AND PRINTING JET //////////////////////////
				double R = 0.4;															// Jet radius
				double ptmin = 5.0;														// Lower pT
				JetDefinition jet_def(antikt_algorithm, R);								// Create jet definition
				ClusterSequence cs(particles, jet_def);									// Run clustering
				vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets(ptmin));		// Sort/store results
				nJc = jets.size();														// Jet multiplicity
		
				// Run through jets
				for (int i = 0; i < jets.size(); i++) {				
					nJf = jets[i].constituents().size();								// Store jet fraction					
					int n_constituents = jets[i].constituents().size();					// Count jet particles					
					vector<PseudoJet> constituents = jets[i].constituents();			// Define constituents vector
					// Run through jet constituents
					for (int j = 0; j < constituents.size(); j++)
						PseudoJet constituent = jets[i].constituents()[j];				// Define constituent vector
				}
			}
		}

		// Hadron check
		if (nCh != 0) {

			////////////////////////// COMPUTING EVENT SHAPES VARS //////////////////////////
			// Populate histogram
			if (sph.analyze( pythia.event )) {
				hist_Spheric->Fill( sph.sphericity() );				// Sphericity = (sum_i p_i^a p_i^b)/(sum_i p_i^2)
				hist_sphAxis->Fill( sph.eventAxis(1).pz() );		// Cosθ
				hist_Aplanar->Fill( sph.aplanarity() );				// Aplanarity
			}
			// Populate histogram
			if (lin.analyze( pythia.event )) {
				hist_Lineric->Fill( lin.sphericity() );				// Linear.Sph = (sum_i p_i^a p_i^b p_i^{r-2})/(sum_i p_i^r)
				hist_linAxis->Fill( lin.eventAxis(1).pz() );		// Cosθ
			}
			// Populate histogram
			if (thr.analyze( pythia.event )) {
				hist_ThrustP->Fill( 1.0 - thr.thrust() );			// Thrust
				hist_thrAxis->Fill( thr.eventAxis(1).pz() );		// Cosθ
				hist_ThMajor->Fill( thr.tMajor() );					// Tmajor  
				hist_ThMinor->Fill( thr.tMinor() );					// Tminor
				hist_Oblatey->Fill( thr.oblateness() );				// Oblateness
				}

			// Populate histogram
			if (lund.analyze( pythia.event, 0.01, 0.)) {
				hist_nChLund->Fill( lund.size() );
				for (int k = 0; k < lund.size() - 1; ++k)
				hist_difLund->Fill( lund.p(k).e() - lund.p(k+1).e() );
			}

			if (jade.analyze( pythia.event, 0.01, 0.)) {
				hist_nChJade->Fill( jade.size() );
				for (int k = 0; k < jade.size() - 1; ++k)
				hist_difJade->Fill( jade.p(k).e() - jade.p(k+1).e() );
			}
			
			if (durham.analyze( pythia.event, 0.01, 0.)) {
				hist_nChDurh->Fill( durham.size() );
				for (int k = 0; k < durham.size() - 1; ++k)
				hist_difDurh->Fill( durham.p(k).e() - durham.p(k+1).e() );
			}
		}

		////////////////////////// POPULATING HISTOS WITH DATA //////////////////////////
		hist_nChPyth->Fill( nCh );
		hist_nJetsCh->Fill( nJc );
		hist_nJetsFr->Fill( nJf );
		hist_nParton->Fill( nCp );
		hist_nPQuark->Fill( nCq );
		hist_nPGluon->Fill( nCg );

		////////////////////////// FILLING DATA TO TREEBRANCHES //////////////////////////
		tree->Fill();

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cross-section checks
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	pythia.stat();
	// cout << "Total weighted sum:\t" << pythia.info.weightSum() << endl;					// total events 
	// cout << "Total crosssection:\t" << pythia.info.sigmaGen() << endl;					// total σ 
	// cout << pythia.info.nameProc(221) << "\t" << pythia.info.sigmaGen(221) << endl;		// ee'->γ*/Z
	// cout << pythia.info.nameProc(222) << "\t" << pythia.info.sigmaGen(222) << endl;		// ee'->W
	// cout << pythia.info.nameProc(231) << "\t" << pythia.info.sigmaGen(231) << endl;		// ee'->γ*Zγ*Z
	// cout << pythia.info.nameProc(232) << "\t" << pythia.info.sigmaGen(232) << endl;		// ee'->ZW
	// cout << pythia.info.nameProc(233) << "\t" << pythia.info.sigmaGen(233) << endl;		// ee'->WW
	// cout << pythia.info.nameProc(604) << "\t" << pythia.info.sigmaGen(604) << endl;		// ee'->tt'

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File closures
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Write file
	output->Write();
	output->Close();
	delete output;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Terminate
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

// // Search ISR photon
// if (pythia.event[jParts].isFinal() && pythia.event[jParts].id()==22 && pythia.event[jParts].e()>5) {
	
// 	// Run through particles to compare
// 	for(int isrcount=0; isrcount<pythia.event.size(); isrcount++) {

// 		// Check energy of compared particle
// 		if (pythia.event[isrcount].isFinal() && pythia.event[isrcount].e()>0.250) {

// 			// Neglect itself
// 			if ( isrcount==jParts ) continue;

// 			// Compute ΔR
// 			float deltaEta = pythia.event[isrcount].eta()-pythia.event[jParts].eta();
// 			float deltaPhi = pythia.event[isrcount].phi()-pythia.event[jParts].phi();
// 			float deltaR = sqrt( deltaEta*deltaEta + deltaPhi*deltaPhi ) * 180/M_PI;
			
// 			// cout << pythia.event[jParts].e() << "\t" << pythia.event[isrcount].e() << "\t" << deltaR << endl;
			
// 			// Check isolated
// 			if ( deltaR<15.0 ) {
// 				isrcheck = false;
// 				break;
// 			}
			
// 		}
// 	}

// 	// ISR photon found!
// 	if (isrcheck==true) {
// 		// cout << "ISR photon found at: " << jParts << endl;
// 		sigISR+=pythia.event[jParts].e();
// 	}

// }	