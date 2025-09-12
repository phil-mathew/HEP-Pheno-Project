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
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/JetDefinition.hh"
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
using namespace fastjet;
// Extras

// Code
int main(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create output Tfile
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define file
  	TFile *output = new TFile("4-GenData/gen_FCC500_ISR.root", "RECREATE");
	
	// Define tree
	TTree *tree = new TTree("tree_raw", "Raw Pythia data");

	// Intialise vecs
	vector<int> eveNum, eveSiz, eveCod, isrNum, parNum, parPdg, parChg, eveNjy;
	vector<float> eveSph, eveSax, eveThr, eveTax, eveSpr, isrMax, \
					eveCpr, eveHjm, eveBto, eveBwi, sigmaT, \
					eveYcu, eveY23, eveY34, \
					parEto, parEtt, parPmx, parPmy, parPmz;

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
	tree->Branch("eveYcu", "vector<float>", &eveYcu); 										// Event ycut
	tree->Branch("eveNjy", "vector<int>", &eveNjy);											// Event Njets(ycut)
	tree->Branch("eveY23", "vector<float>", &eveY23);										// Event y23
	tree->Branch("eveY34", "vector<float>", &eveY34);										// Event y34
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

	// Set # events
	int nEvent = 1E6;
	// Set centre mass
	float nEnerg = 500.0;

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

	// Define eve-vec
	event_fch.init();

	// Define jet grid
	const std::vector<double> YCUT_GRID = {
		1e-4, 1.5e-4, 2.2e-4, 3.2e-4, 4.6e-4,
		6.8e-4, 1e-3, 1.5e-3, 2.2e-3, 3.2e-3,
		4.6e-3, 6.8e-3, 1e-2, 2e-2, 5e-2
	};
	
	// Run through events
	for (int iEvent=0; iEvent<nEvent; iEvent++ ) {

		// Anti-crash
		if (!pythia.next()) continue;

		// Reset vars
		nCh=0; sigISR=0.0; sigmaE=0.0; nISR=0;

		// Reset event vectors
		event_fch.clear();
		eveNum.clear(); sigmaT.clear();
		eveSpr.clear(); eveThr.clear(); eveTax.clear(); eveSiz.clear();
		eveCpr.clear(); eveHjm.clear(); eveBto.clear(); eveBwi.clear();
		eveCod.clear(); eveSph.clear(); eveSax.clear();
		eveYcu.clear(); eveNjy.clear(); eveY23.clear(); eveY34.clear();
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
			eveCod.push_back(pythia.info.code());		// Add proc code
			sigmaT.push_back(pythia.info.sigmaGen());	// Add event sigma
			eveSiz.push_back(nCh);						// Add event size
			eveSpr.push_back(sigISR);					// Add ISR energy
		}

		// Store thrust data
		if (nCh!=0) if (thr.analyze(event_fch)) {
			

			////////////////////////// COMPUTING THRUST ///////////////////////////////////////////////////////
			eveThr.push_back(1.0-thr.thrust());			// Add event thrust
			eveTax.push_back(thr.eventAxis(1).pz());	// Add event thrθ
			
			////////////////////////// COMPUTING JET BROADENINGS //////////////////////////////////////////////
			// Get the thrust axis (as a 4-vector) from the thrust analysis
			Vec4 t4 = thr.eventAxis(1);

			// Convert thrust axis to a 3-vector (spatial part only)
			TVector3 nT(t4.px(), t4.py(), t4.pz());

			// If the thrust axis is zero (e.g. empty event), set broadenings to 0
			if (nT.Mag() == 0) { 
				eveBto.push_back(0.0); 
				eveBwi.push_back(0.0); 
			}

			// Otherwise, compute the jet broadenings
			else {
				// Normalize the thrust axis to unit length
				nT *= 1.0 / nT.Mag();

				double sumP = 0.0;             // sum of absolute momenta over all particles
				double sumPerp1 = 0.0;         // sum of transverse momenta in hemisphere 1
				double sumPerp2 = 0.0;         // sum of transverse momenta in hemisphere 2

				// Loop over all charged final-state particles in the event
				for (int i = 0; i < event_fch.size(); ++i) {
					// Momentum 3-vector of particle i
					TVector3 p(event_fch[i].px(), event_fch[i].py(), event_fch[i].pz());
					double pabs = p.Mag();
					if (pabs <= 0) continue;

					// Momentum component along thrust axis
					double ppar  = p.Dot(nT);

					// Transverse momentum magnitude: sqrt(|p|^2 - p_parallel^2)
					double pperp = std::sqrt(std::max(0.0, pabs*pabs - ppar*ppar));

					// Accumulate total |p| and transverse momenta in each hemisphere
					sumP += pabs;
					if (ppar >= 0) sumPerp1 += pperp;    // hemisphere 1 (forward)
					else           sumPerp2 += pperp;    // hemisphere 2 (backward)
				}

				// Broadening of hemisphere 1 and 2
				double B1 = (sumP > 0) ? (sumPerp1 / sumP) : 0.0;
				double B2 = (sumP > 0) ? (sumPerp2 / sumP) : 0.0;

				// Total broadening = average of the two hemispheres
				double BT = 0.5 * (B1 + B2);
				// Wide broadening = larger of the two hemispheres
				double BW = std::max(B1, B2);

				// Store results into your event tree vectors
				eveBto.push_back((float)BT);
				eveBwi.push_back((float)BW);
			}
		
			////////////////////////// COMPUTING HEAVY JET MASS ///////////////////////////////////////////////
			// Extract thrust axis components (already computed by thrust analysis)
			double nx = t4.px(), ny = t4.py(), nz = t4.pz();

			// Compute its magnitude
			double nmag = std::sqrt(nx*nx + ny*ny + nz*nz);

			if (nmag > 0) {
				// Normalize thrust axis to unit vector
				nx /= nmag; ny /= nmag; nz /= nmag;

				// Variables to accumulate 4-momentum sums in each hemisphere
				double E1=0, px1=0, py1=0, pz1=0;  // hemisphere 1
				double E2=0, px2=0, py2=0, pz2=0;  // hemisphere 2

				// Loop over all charged final-state particles
				for (int i = 0; i < event_fch.size(); ++i) {
					double px = event_fch[i].px();
					double py = event_fch[i].py();
					double pz = event_fch[i].pz();
					double E  = event_fch[i].e();

					// Momentum component along thrust axis
					double ppar = px*nx + py*ny + pz*nz;

					// Split particles into hemispheres based on sign of p_parallel
					if (ppar >= 0) {
						// Add 4-momentum to hemisphere 1
						E1  += E;  px1 += px;  py1 += py;  pz1 += pz;
					} else {
						// Add 4-momentum to hemisphere 2
						E2  += E;  px2 += px;  py2 += py;  pz2 += pz;
					}
				}

				// Compute invariant masses of each hemisphere: M^2 = E^2 - |p|^2
				double M1 = std::sqrt(std::max(0.0, E1*E1 - (px1*px1+py1*py1+pz1*pz1)));
				double M2 = std::sqrt(std::max(0.0, E2*E2 - (px2*px2+py2*py2+pz2*pz2)));

				// Heavy jet mass = max(M1, M2) normalized by √s
				double MH = std::max(M1, M2) / nEnerg;

				// Store in output vector
				eveHjm.push_back((float)MH);
			} 
			else {
				// If thrust axis is zero (empty event), store 0
				eveHjm.push_back(0.0f);
			}

		}

		////////////////////////// COMPUTING SPHERICITY ///////////////////////////////////////////////////////
		if (nCh!=0) if (sph.analyze(event_fch)) {
			eveSph.push_back(sph.sphericity());			// Add event spheric
			eveSax.push_back(sph.eventAxis(1).pz());	// Add event sphθ
		}

		////////////////////////// COMPUTING C-PARAMETER /////////////////////////////////////////////////////
		if (nCh != 0) {
			
			// Collect 4-momenta of all charged final-state particles into a vector
			vector<Vec4> particles;
			for (int i = 0; i < event_fch.size(); ++i) {
				particles.emplace_back(event_fch[i].p());
			}

			// Normalization factor (sum of |p|) and the 3×3 linearized momentum tensor
			double norm = 0.0;
			TMatrixD cMatrix(3,3);
			cMatrix.Zero();  // start all elements at 0

			// Build the linearized momentum tensor
			//    Θ_ij = (1 / Σ|p|) Σ_k (p_{k,i} p_{k,j} / |p_k|)
			for (const auto& p : particles) {
				TVector3 pi(p.px(), p.py(), p.pz());
				double p_abs = pi.Mag();
				if (p_abs > 0) {
					norm += p_abs;  // accumulate total |p|

					// Outer product of momentum direction, weighted by |p|
					for (int i = 0; i < 3; ++i) {
						for (int j = 0; j < 3; ++j) {
							cMatrix(i, j) += (pi[i] * pi[j]) / p_abs;
						}
					}
				}
			}

			// Only continue if we had any particles
			if (norm > 0) {
				// Normalize the tensor by total momentum sum
				cMatrix *= (1.0 / norm);

				// Diagonalize the matrix to get eigenvalues (λ1 ≥ λ2 ≥ λ3)
				TMatrixDEigen eig(cMatrix);
				TVectorD eigenVals = eig.GetEigenValuesRe();
				double lambda1 = eigenVals[0];
				double lambda2 = eigenVals[1];
				double lambda3 = eigenVals[2];

				// Compute the C-parameter:
				//   C = 3 * (λ1λ2 + λ2λ3 + λ3λ1)
				double C = 3.0 * (lambda1 * lambda2 + lambda2 * lambda3 + lambda3 * lambda1);

				// Store result for this event
				eveCpr.push_back(C);
			}

		}

		// ---------------- Durham jet algorithm analysis ----------------

		// Build a list of FastJet PseudoJet objects from the event's final particles
		std::vector<fastjet::PseudoJet> parts;
		parts.reserve(parNum.back());  // (optional) reserve memory for speed

		// Loop over all stored final particles
		for (size_t i = 0; i < parPdg.size(); ++i) {
			int pdg = parPdg[i];

			// Skip neutrinos (they are invisible in the detector)
			if (abs(pdg)==12 || abs(pdg)==14 || abs(pdg)==16) continue;

			// Create a FastJet PseudoJet from px,py,pz,E and add to list
			parts.emplace_back(parPmx[i], parPmy[i], parPmz[i], parEto[i]);
		}

		// Only run clustering if we actually have any visible particles
		if (!parts.empty()) {
			// Define the Durham (e⁺e⁻ kT) jet algorithm
			fastjet::JetDefinition jet_def(fastjet::ee_kt_algorithm);

			// Cluster all particles into jets using this algorithm
			fastjet::ClusterSequence cluster_seq(parts, jet_def);

			// --- Exclusive jet rates R_n(ycut) ---
			// For each resolution parameter ycut in your grid:
			//    - run exclusive clustering at that ycut
			//    - count how many jets the event is classified as
			for (double y : YCUT_GRID) {
				eveYcu.push_back((float)y);  // store the ycut value
				eveNjy.push_back(cluster_seq.exclusive_jets_ycut(y).size()); // store n_jets
			}

			// --- Jet transition scales ---
			// exclusive_ymerge(n-1) gives the y-value at which the event goes from n→(n-1) jets
			eveY23.push_back((float)cluster_seq.exclusive_ymerge(2)); // 3→2 transition
			eveY34.push_back((float)cluster_seq.exclusive_ymerge(3)); // 4→3 transition
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