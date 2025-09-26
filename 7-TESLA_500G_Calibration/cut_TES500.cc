/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to perform cuts on generated events and cluster particles with FastJet3
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include <fstream>
#include <sstream>
// Pythia
#include "Pythia8/Pythia.h"
#include "Pythia8/Basics.h"
#include "Pythia8/Event.h"
// Fastjet
#include "fastjet/ClusterSequence.hh"
// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
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
#include "TEllipse.h"
#include "TText.h"
#include "TPolyLine3D.h"
#include <TVectorF.h>
// Header
using namespace Pythia8;
using namespace std;
using namespace fastjet;

TH1F* ComputeKNOScaling(TH1F* inputHist, const std::string& outputName) {
    // Axes params
	double histNch = inputHist->GetMean();
    double histMax = inputHist->GetXaxis()->GetXmax()/histNch;
    double histMin = inputHist->GetXaxis()->GetXmin()/histNch;
    double histBin = inputHist->GetBinWidth(10)/histNch;
    int numBin = static_cast<int>(ceil(histMax/histBin));
    // KNO histogram
    TH1F* knoHist = new TH1F(outputName.c_str(), "KNO Charged Multiplicity", numBin, 0, histMax);
	// Beautify
    knoHist->GetXaxis()->SetTitle("N_{CH}/<N_{CH}>");
    knoHist->GetYaxis()->SetTitle("P(N_{CH}) x <N_{CH}>");
    // Fill histogram
    for (int bin = 1; bin <= inputHist->GetNbinsX(); ++bin) {
        double nCh = inputHist->GetXaxis()->GetBinCenter(bin);
        double binContent = inputHist->GetBinContent(bin);
        double scaledNch = nCh / histNch;
        double scaledCon = inputHist->GetBinContent(bin)*histNch;
        double scaledErr = inputHist->GetBinError(bin)*histNch;
        knoHist->Fill(scaledNch, scaledCon);
        knoHist->SetBinError(knoHist->FindBin(scaledNch), scaledErr);
    }

    return knoHist;
}

// Import data, perform cuts, store data
void applyCuts( const std::string& inputFileName, const std::string& outputFileName, float nEnerg ) {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create file, Read TTree data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	// Read ROOT
	TFile *input = new TFile(inputFileName.c_str(), "READ");
	// Read TTree
	TTree *itree = (TTree*)input->Get("tree_raw");

	// Define file
	TFile *output = new TFile(outputFileName.c_str(), "RECREATE");
	// Define tree
	TTree *otree = new TTree("tree_cut", "Cut Pythia data");

	// Intialise vecs
	vector<int> *eveNum=nullptr, *eveSiz=nullptr, *eveCod=nullptr, *parNum=nullptr, *parPdg=nullptr, \
	 *parChg=nullptr, *isrNum=nullptr, *eveNjy=nullptr;
	vector<float> *eveThr=nullptr, *eveTax=nullptr, *eveSph=nullptr, *eveSax=nullptr, *eveSpr=nullptr, \
	 *sigmaT=nullptr, *parEto=nullptr, *parEtt=nullptr, *parPmx=nullptr, *parPmy=nullptr, *parPmz=nullptr, \
	 *eveYcu=nullptr, *eveY23=nullptr, *eveY34=nullptr, \
	 *isrMax=nullptr, *eveCpr=nullptr, *eveHjm=nullptr, *eveBto=nullptr, *eveBwi=nullptr;

	// Set branches
	itree->SetBranchAddress("sigmaT", &sigmaT);											// Total sigma
	itree->SetBranchAddress("eveNum", &eveNum);											// Event number
	itree->SetBranchAddress("eveSiz", &eveSiz);											// Event size
	itree->SetBranchAddress("eveCod", &eveCod);											// Event process
	itree->SetBranchAddress("eveSpr", &eveSpr);											// Event √s'
	itree->SetBranchAddress("eveSph", &eveSph);											// Event spheric
	itree->SetBranchAddress("eveSax", &eveSax);											// Event sphaxis
	itree->SetBranchAddress("eveThr", &eveThr);											// Event thrust
	itree->SetBranchAddress("eveTax", &eveTax);											// Event thraxis
	itree->SetBranchAddress("eveCpr", &eveCpr);  										// Event C-param
	itree->SetBranchAddress("eveHjm", &eveHjm);  										// Event rho
	itree->SetBranchAddress("eveBto", &eveBto);											// Event BTotal
	itree->SetBranchAddress("eveBwi", &eveBwi);											// Event Bwide
	itree->SetBranchAddress("eveYcu", &eveYcu); 										// Event ycut
	itree->SetBranchAddress("eveNjy", &eveNjy);											// Event Njets(ycut)
	itree->SetBranchAddress("eveY23", &eveY23);											// Event y23
	itree->SetBranchAddress("eveY34", &eveY34);											// Event y34
	itree->SetBranchAddress("isrNum", &isrNum);											// ISR γ number
	itree->SetBranchAddress("isrMax", &isrMax);											// ISR γ energy
	itree->SetBranchAddress("parNum", &parNum);											// Parts number
	itree->SetBranchAddress("parPdg", &parPdg);											// Parts pdg id
	itree->SetBranchAddress("parChg", &parChg);											// Parts charge
	itree->SetBranchAddress("parEto", &parEto);											// Parts energy
	itree->SetBranchAddress("parEtt", &parEtt);											// Parts energy
	itree->SetBranchAddress("parPmx", &parPmx);											// Parts mom-x
	itree->SetBranchAddress("parPmy", &parPmy);											// Parts mom-y
	itree->SetBranchAddress("parPmz", &parPmz);											// Parts mom-z

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Define histograms, Add branches
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_Esprime_al = new TH1F("hist_Esprime_al", "Reduced energy after ISR", 200, -1, 366);
	hist_Esprime_al->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_al->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_al", &hist_Esprime_al, "hist_Esprime_al");

	TH1F *hist_Esprime_HZ = new TH1F("hist_Esprime_HZ", "Reduced energy after ISR", 166, 200, 366);
	hist_Esprime_HZ->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_HZ->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_HZ", &hist_Esprime_HZ, "hist_Esprime_HZ");

	TH1F *hist_Esprime_HW = new TH1F("hist_Esprime_HW", "Reduced energy after ISR", 66, 300, 366);
	hist_Esprime_HW->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_HW->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_HW", &hist_Esprime_HW, "hist_Esprime_HW");

	TH1F *hist_Esprime_Zq = new TH1F("hist_Esprime_Zq", "Reduced energy after ISR", 200, -1, 366);
	hist_Esprime_Zq->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_Zq->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_Zq", &hist_Esprime_Zq, "hist_Esprime_Zq");
	
	TH1F *hist_Esprime_tt = new TH1F("hist_Esprime_tt", "Reduced energy after ISR", 36, 330, 366);
	hist_Esprime_tt->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_tt->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_tt", &hist_Esprime_tt, "hist_Esprime_tt");

	TH1F *hist_Esprime_WW = new TH1F("hist_Esprime_WW", "Reduced energy after ISR", 266, 100, 366);
	hist_Esprime_WW->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_WW->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_WW", &hist_Esprime_WW, "hist_Esprime_WW");

	TH1F *hist_Esprime_ZZ = new TH1F("hist_Esprime_ZZ", "Reduced energy after ISR", 266, 100, 366);
	hist_Esprime_ZZ->GetXaxis()->SetTitle("#sqrt{s'}");
	hist_Esprime_ZZ->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_Esprime_ZZ", &hist_Esprime_ZZ, "hist_Esprime_ZZ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_nHadron = new TH1F("hist_nHadron", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron", &hist_nHadron, "hist_nHadron");

	TH1F *hist_nHadron_HZ = new TH1F("hist_nHadron_HZ", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_HZ->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_HZ->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_HZ", &hist_nHadron_HZ, "hist_nHadron_HZ");

	TH1F *hist_nHadron_HW = new TH1F("hist_nHadron_HW", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_HW->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_HW->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_HW", &hist_nHadron_HW, "hist_nHadron_HW");

	TH1F *hist_nHadron_Zq = new TH1F("hist_nHadron_Zq", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_Zq->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_Zq->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_Zq", &hist_nHadron_Zq, "hist_nHadron_Zq");

	TH1F *hist_nHadron_ZZ = new TH1F("hist_nHadron_ZZ", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_ZZ->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_ZZ->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_ZZ", &hist_nHadron_ZZ, "hist_nHadron_ZZ");

	TH1F *hist_nHadron_WW = new TH1F("hist_nHadron_WW", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_WW->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_WW->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_WW", &hist_nHadron_WW, "hist_nHadron_WW");

	TH1F *hist_nHadron_tt = new TH1F("hist_nHadron_tt", "Charged Hadron Multiplicity", 60, 1, 121);
	hist_nHadron_tt->GetXaxis()->SetTitle("N_{CH}");
	hist_nHadron_tt->GetYaxis()->SetTitle("P(N_{CH})");
	otree->Branch("hist_nHadron_tt", &hist_nHadron_tt, "hist_nHadron_tt");
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth = new TH1F("hist_ThrPyth", "Inverse Thrust", 200, 0, 1.0);
	hist_ThrPyth->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth", &hist_ThrPyth, "hist_ThrPyth");

	TH1F *hist_ThrPyth_HZ = new TH1F("hist_ThrPyth_HZ", "Inverse Thrust", 200, 0, 1.0);
	hist_ThrPyth_HZ->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_HZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_HZ", &hist_ThrPyth_HZ, "hist_ThrPyth_HZ");

	TH1F *hist_ThrPyth_HW = new TH1F("hist_ThrPyth_HW", "Inverse Thrust", 200, 0, 1.0);
	hist_ThrPyth_HW->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_HW->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_HW", &hist_ThrPyth_HW, "hist_ThrPyth_HW");

	TH1F *hist_ThrPyth_Zq = new TH1F("hist_ThrPyth_Zq", "Inverse Thrust", 200, 0, 1.0);
	hist_ThrPyth_Zq->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_Zq->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_Zq", &hist_ThrPyth_Zq, "hist_ThrPyth_Zq");

	TH1F *hist_ThrPyth_tt = new TH1F("hist_ThrPyth_tt", "Inverse Thrust", 200, 0, 1.0);
	hist_ThrPyth_tt->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_tt->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_tt", &hist_ThrPyth_tt, "hist_ThrPyth_tt");

	TH1F *hist_ThrPyth_WW = new TH1F("hist_ThrPyth_WW", "Inverse Thrust", 200, 0, 1.0);
	hist_ThrPyth_WW->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_WW->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_WW", &hist_ThrPyth_WW, "hist_ThrPyth_WW");

	TH1F *hist_ThrPyth_ZZ = new TH1F("hist_ThrPyth_ZZ", "Inverse Thrust", 200, 0, 1.0);
	hist_ThrPyth_ZZ->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_ZZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_ZZ", &hist_ThrPyth_ZZ, "hist_ThrPyth_ZZ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_CprPyth = new TH1F("hist_CprPyth", "C-Parameter", 200, 0, 1.0);
	hist_CprPyth->GetXaxis()->SetTitle("C");
	hist_CprPyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth", &hist_CprPyth, "hist_CprPyth");

	TH1F *hist_CprPyth_HZ = new TH1F("hist_CprPyth_HZ", "C-parameter", 200, 0, 1.0);
	hist_CprPyth_HZ->GetXaxis()->SetTitle("C");
	hist_CprPyth_HZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_HZ", &hist_CprPyth_HZ, "hist_CprPyth_HZ");

	TH1F *hist_CprPyth_HW = new TH1F("hist_CprPyth_HW", "C-parameter", 200, 0, 1.0);
	hist_CprPyth_HW->GetXaxis()->SetTitle("C");
	hist_CprPyth_HW->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_HW", &hist_CprPyth_HW, "hist_CprPyth_HW");

	TH1F *hist_CprPyth_Zq = new TH1F("hist_CprPyth_Zq", "C-parameter", 200, 0, 1.0);
	hist_CprPyth_Zq->GetXaxis()->SetTitle("C");
	hist_CprPyth_Zq->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_Zq", &hist_CprPyth_Zq, "hist_CprPyth_Zq");

	TH1F *hist_CprPyth_tt = new TH1F("hist_CprPyth_tt", "C-parameter", 200, 0, 1.0);
	hist_CprPyth_tt->GetXaxis()->SetTitle("C");
	hist_CprPyth_tt->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_tt", &hist_CprPyth_tt, "hist_CprPyth_tt");

	TH1F *hist_CprPyth_WW = new TH1F("hist_CprPyth_WW", "C-parameter", 200, 0, 1.0);
	hist_CprPyth_WW->GetXaxis()->SetTitle("C");
	hist_CprPyth_WW->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_WW", &hist_CprPyth_WW, "hist_CprPyth_WW");

	TH1F *hist_CprPyth_ZZ = new TH1F("hist_CprPyth_ZZ", "C-parameter", 200, 0, 1.0);
	hist_CprPyth_ZZ->GetXaxis()->SetTitle("C");
	hist_CprPyth_ZZ->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_ZZ", &hist_CprPyth_ZZ, "hist_CprPyth_ZZ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	float xbin[] = { 
		0.000, 0.010, 0.020, 0.030, 0.040, 0.050, 0.060, 0.070, 0.080, 0.090,
		0.100, 0.110, 0.120, 0.130, 0.140, 0.150, 0.160, 0.170, 0.180, 0.190,
		0.200, 0.210, 0.220, 0.230, 0.240, 0.250, 0.260, 0.270, 0.280, 0.290,
		0.300, 0.310, 0.320, 0.330, 0.340, 0.350, 0.360, 0.370, 0.380, 0.390,
		0.400, 0.410, 0.420, 0.430, 0.440
	};

	TH1F *hist_ThrPyth_TEO = new TH1F("hist_ThrPyth_TEO", "Inverse Thrust", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_ThrPyth_TEO->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_TEO->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_TEO", &hist_ThrPyth_TEO, "hist_ThrPyth_TEO");

	TH1F *hist_CprPyth_TEO = new TH1F("hist_CprPyth_TEO", "C-Parameter", (sizeof(xbin)/sizeof(xbin[0])-1), xbin);
	hist_CprPyth_TEO->GetXaxis()->SetTitle("C");
	hist_CprPyth_TEO->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_TEO", &hist_CprPyth_TEO, "hist_CprPyth_TEO");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_HjmPyth = new TH1F("hist_HjmPyth", "Heavy jet mass", 100, 0, 1.0);
	hist_HjmPyth->GetXaxis()->SetTitle("C");
	hist_HjmPyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(M_{H})");
	otree->Branch("hist_HjmPyth", &hist_HjmPyth, "hist_HjmPyth");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_BtoPyth = new TH1F("hist_BtoPyth", "Total jet broadening", 100, 0, 1.0);
	hist_BtoPyth->GetXaxis()->SetTitle("B_{T}");
	hist_BtoPyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(B_{T})");
	otree->Branch("hist_BtoPyth", &hist_BtoPyth, "hist_BtoPyth");

	TH1F *hist_BwiPyth = new TH1F("hist_BwiPyth", "Wide jet broadening", 100, 0, 1.0);
	hist_BwiPyth->GetXaxis()->SetTitle("B_{W}");
	hist_BwiPyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(B_{W})");
	otree->Branch("hist_BwiPyth", &hist_BwiPyth, "hist_BwiPyth");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_Y23Pyth = new TH1F("hist_Y23Pyth", "Differential 2-jet rate", 100, 0, 1.0);
	hist_Y23Pyth->GetXaxis()->SetTitle("y_{23}");
	hist_Y23Pyth->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(y_{23})");
	otree->Branch("hist_Y23Pyth", &hist_Y23Pyth, "hist_Y23Pyth");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_TaxPyth = new TH1F("hist_TaxPyth", "Thrust axis", 100, -1., 1.);
	hist_TaxPyth->GetXaxis()->SetTitle("cosΘ_{Thrust}");
	hist_TaxPyth->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_TaxPyth", &hist_TaxPyth, "hist_TaxPyth");

	TH1F *hist_SphPyth = new TH1F("hist_SphPyth", "Sphericity", 100, 0, 1.0);
	hist_SphPyth->GetXaxis()->SetTitle("S");
	hist_SphPyth->GetYaxis()->SetTitle("P(S)");
	otree->Branch("hist_SphPyth", &hist_SphPyth, "hist_SphPyth");

	TH1F *hist_SaxPyth = new TH1F("hist_SaxPyth", "Thrust axis", 100, -1., 1.);
	hist_SaxPyth->GetXaxis()->SetTitle("cosΘ_{Sphericity}");
	hist_SaxPyth->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_SaxPyth", &hist_SaxPyth, "hist_SaxPyth");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_ISR = new TH1F("hist_ThrPyth_ISR", "Inverse Thrust", 200, 0, 1.0);
	hist_ThrPyth_ISR->GetXaxis()->SetTitle("(1-T)");
	hist_ThrPyth_ISR->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(1-T)");
	otree->Branch("hist_ThrPyth_ISR", &hist_ThrPyth_ISR, "hist_ThrPyth_ISR");

	TH1F *hist_CprPyth_ISR = new TH1F("hist_CprPyth_ISR", "C-Parameter", 200, 0, 1.0);
	hist_CprPyth_ISR->GetXaxis()->SetTitle("C");
	hist_CprPyth_ISR->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma/d(C)");
	otree->Branch("hist_CprPyth_ISR", &hist_CprPyth_ISR, "hist_CprPyth_ISR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_NumbISR = new TH1F("hist_NumbISR", "Number of ISR photons", 2, 0, 2);
	hist_NumbISR->GetXaxis()->SetTitle("#E_{#gamma}");
	hist_NumbISR->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_NumbISR", &hist_NumbISR, "hist_NumbISR");

	TH1F *hist_EmaxISR = new TH1F("hist_EmaxISR", "Energy of max ISR photons", 100, 0, 0.6);
	hist_EmaxISR->GetXaxis()->SetTitle("E_{#gamma}/#sqrt{s}");
	hist_EmaxISR->GetYaxis()->SetTitle("#events");
	otree->Branch("hist_EmaxISR", &hist_EmaxISR, "hist_EmaxISR");
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Perform cuts, Populate histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define vars
	int nCh=0, \
		nRad_wi_al=0, nRad_wi_Zq=0, nRad_wi_ZZ=0, nRad_wi_WW=0, nRad_wi_tt=0, nRad_wi_HZ=0, nRad_wi_HW=0, \
		nRad_wo_al=0, nRad_wo_Zq=0, nRad_wo_ZZ=0, nRad_wo_WW=0, nRad_wo_tt=0, nRad_wo_HZ=0, nRad_wo_HW=0;
	float Pmx, Pmy, Pmz, Eto, Ett, Thr, Tax, Sph, Sax, Spr, Hjm, Bto, Bwi;
	
	// Run through events
	for(int iEvent = 0; iEvent < itree->GetEntries(); iEvent++ ) {
		
		itree->GetEntry(iEvent);	// Access		
		nCh=0;						// Reset

		// Run through particles
		for(int jParts = 0; jParts < (*eveSiz)[0]; jParts++) {
	
			// Multiplicity
			if ((*parChg)[jParts]!=0) nCh++;
			
		}

		////////////////////////// COMPUTING EVENT SHAPES VARS //////////////////////////////////////////////

		// Sanity √s' check
		if ((*eveSpr)[0] >= nEnerg*0.00){
			
			hist_Esprime_al->Fill((*eveSpr)[0]);
			hist_CprPyth->Fill((*eveCpr)[0]);
			hist_ThrPyth->Fill((*eveThr)[0]);
			hist_TaxPyth->Fill((*eveTax)[0]);
			hist_SphPyth->Fill((*eveSph)[0]);
			hist_SaxPyth->Fill((*eveSax)[0]);
			hist_nHadron->Fill(nCh);
			hist_HjmPyth->Fill((*eveHjm)[0]);
			hist_BtoPyth->Fill((*eveBto)[0]);
			hist_BwiPyth->Fill((*eveBwi)[0]);
			hist_Y23Pyth->Fill((*eveY23)[0]);
			hist_NumbISR->Fill((*isrNum)[0]);
			hist_EmaxISR->Fill((*isrMax)[0]);

			// Process cuts
			if ((*eveCod)[0] == 221) {
				hist_Esprime_Zq->Fill((*eveSpr)[0]);
				hist_nHadron_Zq->Fill(nCh);

				hist_CprPyth_Zq->Fill((*eveCpr)[0]);
				hist_ThrPyth_Zq->Fill((*eveThr)[0]); 

				hist_ThrPyth_TEO->Fill((*eveThr)[0]);
				hist_CprPyth_TEO->Fill((*eveCpr)[0]);
			}
			if ((*eveCod)[0] == 231) {
				hist_Esprime_ZZ->Fill((*eveSpr)[0]);
				hist_nHadron_ZZ->Fill(nCh);

				hist_CprPyth_ZZ->Fill((*eveCpr)[0]);
				hist_ThrPyth_ZZ->Fill((*eveThr)[0]); 
			}
			if ((*eveCod)[0] == 233) {
				hist_Esprime_WW->Fill((*eveSpr)[0]);
				hist_nHadron_WW->Fill(nCh);

				hist_CprPyth_WW->Fill((*eveCpr)[0]);
				hist_ThrPyth_WW->Fill((*eveThr)[0]); 
			}
			if ((*eveCod)[0] == 604) {
				hist_Esprime_tt->Fill((*eveSpr)[0]);
				hist_nHadron_tt->Fill(nCh);

				hist_CprPyth_tt->Fill((*eveCpr)[0]);
				hist_ThrPyth_tt->Fill((*eveThr)[0]); 
			}
			if ((*eveCod)[0] == 904) {
				hist_Esprime_HZ->Fill((*eveSpr)[0]);
				hist_nHadron_HZ->Fill(nCh);
				hist_ThrPyth_HZ->Fill((*eveThr)[0]);
				hist_CprPyth_HZ->Fill((*eveCpr)[0]);
			}
			if ((*eveCod)[0] == 907) {
				hist_Esprime_HW->Fill((*eveSpr)[0]);
				hist_nHadron_HW->Fill(nCh);
				hist_ThrPyth_HW->Fill((*eveThr)[0]);
				hist_CprPyth_HW->Fill((*eveCpr)[0]);
			}

		}
		
		// √s' cut
		if ((*eveSpr)[0] == nEnerg) {
			nRad_wo_al++;
			if ((*eveCod)[0] == 221) {
				nRad_wo_Zq++;
				hist_ThrPyth_ISR->Fill((*eveThr)[0]);
				hist_CprPyth_ISR->Fill((*eveCpr)[0]);
			}
			if ((*eveCod)[0] == 231) nRad_wo_ZZ++;
			if ((*eveCod)[0] == 233) nRad_wo_WW++;
			if ((*eveCod)[0] == 604) nRad_wo_tt++;
			if ((*eveCod)[0] == 904) nRad_wo_HZ++;
			if ((*eveCod)[0] == 907) nRad_wo_HW++;
		}
		else {
			nRad_wi_al++;
			if ((*eveCod)[0] == 221) nRad_wi_Zq++;
			if ((*eveCod)[0] == 231) nRad_wi_ZZ++;
			if ((*eveCod)[0] == 233) nRad_wi_WW++;
			if ((*eveCod)[0] == 604) nRad_wi_tt++;
			if ((*eveCod)[0] == 904) nRad_wi_HZ++;
			if ((*eveCod)[0] == 907) nRad_wi_HW++;
		}
		
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Print info
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "----------------------------------------" << endl;
	cout << "Non-radiative:Radiative:Summed at " << nEnerg << " GeV " << endl;
	cout << "----------------------------------------" << endl;
	cout << "al = " << nRad_wo_al << " : " << nRad_wi_al << " : " << nRad_wo_al+nRad_wi_al << endl;
	cout << "gZ = " << nRad_wo_Zq << " : " << nRad_wi_Zq << " : " << nRad_wo_Zq+nRad_wi_Zq << endl;
	cout << "ZZ = " << nRad_wo_ZZ << " : " << nRad_wi_ZZ << " : " << nRad_wo_ZZ+nRad_wi_ZZ << endl;
	cout << "WW = " << nRad_wo_WW << " : " << nRad_wi_WW << " : " << nRad_wo_WW+nRad_wi_WW << endl;
	cout << "tt = " << nRad_wo_tt << " : " << nRad_wi_tt << " : " << nRad_wo_tt+nRad_wi_tt << endl;
	cout << "HZ = " << nRad_wo_HZ << " : " << nRad_wi_HZ << " : " << nRad_wo_HZ+nRad_wi_HZ << endl;
	cout << "HW = " << nRad_wo_HW << " : " << nRad_wi_HW << " : " << nRad_wo_HW+nRad_wi_HW << endl;
	cout << "----------------------------------------" << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KNO scaling
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F* KNOO_nHadron = ComputeKNOScaling(hist_nHadron, "KNOO_nHadron");
	TH1F* KNOO_nHadron_Zq = ComputeKNOScaling(hist_nHadron_Zq, "KNOO_nHadron_Zq");
	TH1F* KNOO_nHadron_ZZ = ComputeKNOScaling(hist_nHadron_ZZ, "KNOO_nHadron_ZZ");
	TH1F* KNOO_nHadron_WW = ComputeKNOScaling(hist_nHadron_WW, "KNOO_nHadron_WW");
	TH1F* KNOO_nHadron_tt = ComputeKNOScaling(hist_nHadron_tt, "KNOO_nHadron_tt");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File closures
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	output->Write();
	output->Close();
	input->Close();
	delete output;
	delete input;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

// Code
int main() {

	// Extraction
	applyCuts("4-GenData/gen_FCC912.root", "5-CutData/cut_FCC912.root", 91.20);
	// applyCuts("4-GenData/gen_FCC160.root", "5-CutData/cut_FCC160.root", 160.0);
	// applyCuts("4-GenData/gen_FCC240.root", "5-CutData/cut_FCC240.root", 240.0);
	// applyCuts("4-GenData/gen_FCC365.root", "5-CutData/cut_FCC365.root", 365.0);
	
	// Hadronic cuts
	// applyCuts("4-GenData/gen_FCC365.root", "5-CutData/cut_FCC365_wiCut.root", 365.0);

	// ISR
	// applyCuts("4-GenData/gen_FCC500_ISR.root", "5-CutData/cut_FCC500_ISR.root", 500.0);
	// applyCuts("4-GenData/gen_FCC365_ISR.root", "5-CutData/cut_FCC365_ISR.root", 365.0);
	// applyCuts("4-GenData/gen_FCC240_ISR.root", "5-CutData/cut_FCC240_ISR.root", 240.0);
	// applyCuts("4-GenData/gen_FCC160_ISR.root", "5-CutData/cut_FCC160_ISR.root", 160.0);
	// applyCuts("4-GenData/gen_FCC912_ISR.root", "5-CutData/cut_FCC912_ISR.root", 91.20);

	// // Calibration
	// applyCuts("4-GenData/gen_FCC183.root", "5-CutData/cut_FCC183.root", 183.0);
	// applyCuts("4-GenData/gen_FCC161.root", "5-CutData/cut_FCC161.root", 161.0);
	// applyCuts("4-GenData/gen_FCC912.root", "5-CutData/cut_FCC912.root", 91.20);

	// Hadronisation
	// applyCuts("4-GenData/gen_FCC912_woHadron.root", "5-CutData/cut_FCC912_woHadron.root", 91.20);
	// applyCuts("4-GenData/gen_FCC160_woHadron.root", "5-CutData/cut_FCC160_woHadron.root", 160.0);
	// applyCuts("4-GenData/gen_FCC240_woHadron.root", "5-CutData/cut_FCC240_woHadron.root", 240.0);
	// applyCuts("4-GenData/gen_FCC365_woHadron.root", "5-CutData/cut_FCC365_woHadron.root", 365.0);

	// Old	
	// applyCuts("gen_LEP912_wiR.root", "cut_LEP912_wiR.root", 91.0);
	// applyCuts("gen_TES50t_wiR.root", "cut_TES50t_wiR.root", 500.0);
	// applyCuts("gen_TES50t_noR.root", "cut_TES50t_noR.root", 500.0);
	// applyCuts("gen_TES50t_noR_noH.root", "cut_TES50t_noR_noH.root", 500.0);
	// applyCuts("gen_TES500_noR.root", "cut_TES500_noR.root", 500.0);

	// Terminate
	return 0;

}