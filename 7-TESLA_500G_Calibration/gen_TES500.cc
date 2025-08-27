/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate collision events in Pythia
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
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
// LHAPDF
// #include "LHAPDF/LHAPDF.h"
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
#include "TMatrixD.h"
#include "TMatrixDEigen.h"
#include "TVectorD.h"
#include <algorithm>
#include <numeric>
// Header
using namespace Pythia8;
using namespace std;
using namespace fjcore;
// Extras

// Code
int main(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create output Tfile
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define file
  	TFile *output = new TFile("gen_FCC912_ISR.root", "RECREATE");
	
	// Define tree
	TTree *tree = new TTree("tree_raw", "Raw Pythia data");

	// Intialise vecs
	vector<int> eveNum, eveSiz, eveCod, isrNum, parNum, parPdg, parChg;
	vector<float> eveSph, eveSax, eveThr, eveTax, eveSpr, isrMax, \
					eveCpr, eveHjm, eveBto, eveBwi, sigmaT, parEto, \
					parEtt, parPmx, parPmy, parPmz;

	// Define branches
	tree->Branch("sigmaT", "vector<float>", &sigmaT);										// Total sigma
	tree->Branch("eveNum", "vector<int>", &eveNum);											// Event number
	tree->Branch("eveSiz", "vector<int>", &eveSiz);											// Event size
	tree->Branch("eveCod", "vector<int>", &eveCod);											// Event process
	tree->Branch("eveSpr", "vector<float>", &eveSpr);										// Event √s'
	tree->Branch("eveSph", "vector<float>", &eveSph);										// Event spheric
	tree->Branch("eveSax", "vector<float>", &eveSax);										// Event sphaxis
	tree->Branch("eveThr", "vector<float>", &eveThr);										// Event thrust
	tree->Branch("eveTax", "vector<float>", &eveTax);										// Event thraxis
	tree->Branch("eveCpr", "vector<float>", &eveCpr);  										// Event C-param
	tree->Branch("eveHjm", "vector<float>", &eveHjm);  										// Event rho
	tree->Branch("eveBto", "vector<float>", &eveBto);										// Event BTotal
	tree->Branch("eveBwi", "vector<float>", &eveBwi);										// Event Bwide
	tree->Branch("isrNum", "vector<int>", &isrNum);											// ISR γ number
	tree->Branch("isrMax", "vector<float>", &isrMax);										// ISR γ energy
	tree->Branch("parNum", "vector<int>", &parNum);											// Parts number
	tree->Branch("parPdg", "vector<int>", &parPdg);											// Parts pdg id
	tree->Branch("parChg", "vector<int>", &parChg);											// Parts charge
	tree->Branch("parEto", "vector<float>", &parEto);										// Parts energy
	tree->Branch("parEtt", "vector<float>", &parEtt);										// Parts energy
	tree->Branch("parPmx", "vector<float>", &parPmx);										// Parts mom-x
	tree->Branch("parPmy", "vector<float>", &parPmy);										// Parts mom-y
	tree->Branch("parPmz", "vector<float>", &parPmz);										// Parts mom-z

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define Pythia params
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define study object
	Pythia pythia;

	// Store masses
	float mZ = pythia.particleData.m0(23);													// Z0 mass
	float mW = pythia.particleData.m0(24);													// W+ mass

	// Set # of events
	int nEvent = 1E6;
	// Set centre mass
	float nEnerg = 91.2;

///////////////////////////////PHYSICS SWITCHES FOR TESLA 500 GeV ///////////////////////////////////////////
	
	// Define Beam params
	pythia.readString("Beams:idA = 11"); 													// beam energy
	pythia.readString("Beams:idB = -11"); 													// beam energy
	pythia.settings.parm("Beams:eCM", nEnerg);												// c-om energy
	// pythia.readString("PDF:lepton = off");													// ISR toggle
	
	// Hadronisation
	// pythia.readString("HadronLevel:Hadronize = off");
	// pythia.readString("HadronLevel:Decay = off");

	// Z processes
	pythia.readString("WeakZ0:gmZmode = 0");												// allow γ* or Z channels
	pythia.readString("WeakSingleBoson:ffbar2gmZ = on");									// (221) ee'->γ*/Z
	pythia.readString("WeakDoubleBoson:ffbar2gmZgmZ = on");									// (231) ee'->(γ*/Z)(γ*/Z)
	// Constrain decays
	pythia.readString("23:onMode = off");													// turn off Z production
	pythia.readString("23:onIfAny = 1 2 3 4 5 6");											// turn on Z iff duscbt
	
	// W processes
	pythia.readString("WeakDoubleBoson:ffbar2WW = on");										// (233) ee'->WW
	// Constrain decays
	pythia.readString("24:onMode = off");													// turn off W production
	pythia.readString("24:onIfAny = 1 2 3 4 5 6");											// turn on W iff duscbt
	
	// // Higgs processes
	pythia.readString("HiggsSM:ffbar2HZ = on");												// (904) ee'->H/Z
	pythia.readString("HiggsSM:ff2Hff(t:WW) = on");											// (907) ee'->WW->H
	// Constrain decays
	pythia.readString("25:onMode = off");													// turn off H production
	pythia.readString("25:onIfAny = 1 2 3 4 5 6");											// turn on H iff duscbt

	// Top processes
	pythia.readString("Top:ffbar2ttbar(s:gmZ) = on");										// (604) ee'->tt'

	// Suppress terminal text
	pythia.readString("Print:quiet = on");													// print nothing
	pythia.readString("Next:numberCount = 1000");											// print #events updates
	// pythia.readString("Next:numberShowEvent = 10");
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generate Pythia collisions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Initialise PYTHIA
	pythia.init();

	// Define analytics
	Thrust thr; Sphericity sph; Event event_fch;

	// Define vars
	float sigISR=0.0, sigmaE=0.0; int nCh=0, nISR=0;
	vector<float> isrEng;
	
	// Run through events
	for (int iEvent=0; iEvent<nEvent; iEvent++ ) {

		// Anti-crash
		if (!pythia.next()) continue;

		// Reset vars
		nCh=0; sigISR=0.0; sigmaE=0.0; nISR=0;

		// Reset event vectors
		event_fch.init(); event_fch.clear(); eveNum.clear(); sigmaT.clear();
		eveSpr.clear(); eveThr.clear(); eveTax.clear(); eveSiz.clear();
		eveCpr.clear(); eveHjm.clear(); eveBto.clear(); eveBwi.clear();
		eveCod.clear(); eveSph.clear(); eveSax.clear();
		// Reset ISR vectors
		isrNum.clear(); isrEng.clear(); isrMax.clear();
		// Reset part vectors
		parNum.clear(); parPdg.clear(); parChg.clear(); parEto.clear(); 
		parEtt.clear(); parPmx.clear(); parPmy.clear(); parPmz.clear();

		// Run through particles
		for (int jParts=0; jParts<pythia.event.size(); jParts++) {

			// Store particle info
			if (pythia.event[jParts].isFinal()) {
		
				sigmaE+=pythia.event[jParts].e();											// Sum final energies
				nCh++;																		// Count FC particles
				eveNum.push_back(iEvent);													// Add event number
				parNum.push_back(jParts);													// Add particle number
				parPdg.push_back(pythia.event[jParts].id());								// Add particle pdg id
				parChg.push_back(pythia.particleData.charge(pythia.event[jParts].id()));	// Add particle charge
				parEto.push_back(pythia.event[jParts].e());									// Add particle energy
				parEtt.push_back(pythia.event[jParts].eT());								// Add particle energy
				parPmx.push_back(pythia.event[jParts].px());								// Add particle mom-x
				parPmy.push_back(pythia.event[jParts].py());								// Add particle mom-y
				parPmz.push_back(pythia.event[jParts].pz());								// Add particle mom-z
				event_fch.append(pythia.event[jParts]);										// Update event vector

				// Search ISR photon
				if (pythia.event[jParts].id()==22 && pythia.event[jParts].status()==43) {
					
					// Store origins
					int idmom1 = pythia.event[jParts].mother1(); int idmom2 = pythia.event[jParts].mother2();
					int iddod1 = pythia.event[jParts].daughter1(); int iddod2 = pythia.event[jParts].daughter2();

					// Check mothers
					if ( (abs(pythia.event[idmom1].id())==11 || abs(pythia.event[idmom2].id())==11) ) {
						
						// Print isr info
						// cout << "ISR Photon at " << jParts << " with " << pythia.event[jParts].e() << endl;

						nISR++;																// Count isr photons
						isrEng.push_back(pythia.event[jParts].e()/nEnerg);					// Count event isr
						sigISR =+ pythia.event[jParts].e();									// 

					}
					
				}

			}
			
		}

		// Print ISR info
		if( nISR > 1 ) cout << nISR << " photons found in event " << iEvent << endl;
		// cout << *std::max_element(gammas.begin(),gammas.end()) << " GeV photon at √s' = " << sigISR << endl;

		// Store ISR info
		isrNum.push_back(nISR);
		if (!isrEng.empty()) isrMax.push_back(*std::max_element(isrEng.begin(),isrEng.end()));
		else isrMax.push_back(0.0);

		// Compute √s'
		sigISR = nEnerg*sqrt(1.0-(2.0*sigISR)/nEnerg);

		// Store event info
		if (nCh!=0) {
			eveCod.push_back(pythia.info.code());											// Add proc code
			sigmaT.push_back(pythia.info.sigmaGen());										// Add event sigma
			eveSiz.push_back(nCh);															// Add event size
			eveSpr.push_back(sigISR);														// Add ISR energy
		}

		// Store thrust data
		if (nCh!=0) if (thr.analyze(event_fch)) {
			eveThr.push_back(1.0-thr.thrust());												// Add event thrust
			eveTax.push_back(thr.eventAxis(1).pz());										// Add event thrθ
		}

		// Store spheric data
		if (nCh!=0) if (sph.analyze(event_fch)) {
			eveSph.push_back(sph.sphericity());												// Add event spheric
			eveSax.push_back(sph.eventAxis(1).pz());										// Add event sphθ
		}

		// Compute additional event shapes
		if (nCh != 0) {
			
			vector<Vec4> particles;
			for (int i = 0; i < event_fch.size(); ++i) {
				particles.emplace_back(event_fch[i].p());
			}

			// Compute C-parameter
			double norm = 0.0;
			TMatrixD cMatrix(3, 3);
			cMatrix.Zero();

			for (const auto& p : particles) {
				TVector3 pi(p.px(), p.py(), p.pz());
				double p_abs = pi.Mag();
				if (p_abs > 0) {
					norm += p_abs;
					for (int i = 0; i < 3; ++i) {
						for (int j = 0; j < 3; ++j) {
							cMatrix(i, j) += (pi[i] * pi[j]) / p_abs;
						}
					}
				}
			}

			if (norm > 0) {
				cMatrix *= (1.0 / norm);
				TMatrixDEigen eig(cMatrix);
				TVectorD eigenVals = eig.GetEigenValuesRe();
				double lambda1 = eigenVals[0];
				double lambda2 = eigenVals[1];
				double lambda3 = eigenVals[2];
				double C = 3.0 * (lambda1 * lambda2 + lambda2 * lambda3 + lambda3 * lambda1);
				eveCpr.push_back(C);
			}

		}

		// Populate
		tree->Fill();

	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cross-sections
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	pythia.stat();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File closures
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

			// // Heavy jet mass (hemisphere split along thrust axis)
			// if (thr.analyze(event_fch)) {
			// 	Vec4 thrustAxis = thr.eventAxis(1);
			// 	double m2_heavy = 0.0, m2_light = 0.0;
			// 	Vec4 h1, h2;
			// 	for (auto &p : particles) {
			// 		if (p.px()*thrustAxis.px() + p.py()*thrustAxis.py() + p.pz()*thrustAxis.pz() > 0)
			// 			h1 += p;
			// 		else
			// 			h2 += p;
			// 	}
			// 	double m1 = h1.mCalc(), m2 = h2.mCalc();
			// 	double mjmax = std::max(m1, m2);
			// 	eveHjm.push_back((mjmax * mjmax) / (nEnerg * nEnerg));
			// }

			// // Jet broadenings
			// if (thr.analyze(event_fch)) {
			// 	Vec4 thrustAxis = thr.eventAxis(1);
			// 	double BT = 0.0, BW = 0.0, B1 = 0.0, B2 = 0.0, normT = 0.0;
			// 	for (auto &p : particles) {
			// 		double pt = sqrt(p.px()*p.px() + p.py()*p.py() + p.pz()*p.pz());
			// 		normT += pt;

			// 		// project p onto thrust axis
			// 		double dot = p.px()*thrustAxis.px() + p.py()*thrustAxis.py() + p.pz()*thrustAxis.pz();
			// 		if (dot > 0)
			// 			B1 += pt * sqrt(1 - pow(dot / pt, 2));
			// 		else
			// 			B2 += pt * sqrt(1 - pow(dot / pt, 2));
			// 	}
			// 	BT = (B1 + B2) / (2.0 * normT);
			// 	BW = std::max(B1, B2) / normT;

			// 	eveBto.push_back(BT);
			// 	eveBwi.push_back(BW);
			// }