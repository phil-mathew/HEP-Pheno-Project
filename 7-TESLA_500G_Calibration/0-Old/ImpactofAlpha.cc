/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate plots in ROOT from TTree file produced by Pythia
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include <fstream>
#include <sstream>
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
#include "TGraphAsymmErrors.h"
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
using namespace std;

TGraphAsymmErrors* HistToGraph(const TH1* h, bool skipEmpty=false) {
    const int nb = h->GetNbinsX();
    auto g = new TGraphAsymmErrors();
    int p = 0;

    for (int i = 1; i <= nb; ++i) {
        const double xlow = h->GetXaxis()->GetBinLowEdge(i);
        const double xup  = h->GetXaxis()->GetBinUpEdge(i);
        const double x    = h->GetXaxis()->GetBinCenter(i);
        const double exl  = x - xlow;               // left x-error
        const double exh  = xup - x;                // right x-error

        const double y    = h->GetBinContent(i);
        const double ey   = h->GetBinError(i);      // symmetric y-error
        if (skipEmpty && y == 0 && ey == 0) continue;

        g->SetPoint(p, x, y);
        g->SetPointError(p, exl, exh, ey, ey);      // same up/down if symmetric
        ++p;
    }
    g->SetTitle(h->GetTitle());
    g->GetXaxis()->SetTitle(h->GetXaxis()->GetTitle());
    g->GetYaxis()->SetTitle(h->GetYaxis()->GetTitle());
    return g;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Theoretical model for Thrust
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// bin widths
vector<double> bins = { 0.005, 0.015, 0.025, 0.035, 0.045, 0.055, 0.065, 0.075, 0.085, 0.095, 0.105, 0.115, 0.125, 0.135, 0.145, 0.155, \
						0.165, 0.175, 0.185, 0.195, 0.205, 0.215, 0.225, 0.235, 0.245, 0.255, 0.265, 0.275, 0.285, 0.295, 0.305, 0.315, \
						0.325, 0.335, 0.345, 0.355, 0.365, 0.375, 0.385, 0.395, 0.405, 0.415, 0.425, 0.435, 0.445 };

// LO parameters A_T
vector<double> A_THR = {
2.58e+01, 1.83e+01, 1.54e+01, 1.35e+01, 1.21e+01, 1.10e+01, 1.00e+01, 9.21e+00, 8.50e+00, 7.87e+00,
7.30e+00, 6.79e+00, 6.32e+00, 5.88e+00, 5.48e+00, 5.10e+00, 4.75e+00, 4.41e+00, 4.10e+00, 3.79e+00,
3.50e+00, 3.22e+00, 2.95e+00, 2.68e+00, 2.42e+00, 2.16e+00, 1.91e+00, 1.65e+00, 1.38e+00, 1.12e+00,
8.42e-01, 5.57e-01, 2.59e-01, 1.71e-02, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
// NLO parameters B_T
vector<double> B_THR = {
-4.96e+02, 2.17e+02, 2.81e+02, 2.92e+02, 2.88e+02, 2.77e+02, 2.64e+02, 2.51e+02, 2.37e+02, 2.24e+02,
2.11e+02, 1.99e+02, 1.88e+02, 1.77e+02, 1.67e+02, 1.57e+02, 1.48e+02, 1.39e+02, 1.31e+02, 1.23e+02,
1.15e+02, 1.08e+02, 1.01e+02, 9.47e+01, 8.82e+01, 8.21e+01, 7.54e+01, 6.94e+01, 6.30e+01, 5.64e+01,
4.89e+01, 4.14e+01, 3.35e+01, 2.11e+01, 8.57e+00, 4.47e+00, 2.43e+00, 1.30e+00, 6.44e-01, 2.82e-01,
5.12e-02, 1.46e-05, 4.66e-05, 0
};
// NNLO parameters C_T
vector<double> C_THR = {
-9.00e+03, -3.30e+03, 1.60e+03, 4.00e+03, 4.90e+03, 5.30e+03, 5.50e+03, 5.40e+03, 5.50e+03, 5.20e+03,
5.10e+03, 4.80e+03, 4.50e+03, 4.30e+03, 4.10e+03, 3.90e+03, 3.80e+03, 3.50e+03, 3.29e+03, 3.20e+03,
2.98e+03, 2.85e+03, 2.63e+03, 2.50e+03, 2.33e+03, 2.35e+03, 2.15e+03, 1.97e+03, 1.80e+03, 1.83e+03,
1.74e+03, 1.57e+03, 1.42e+03, 1.03e+03, 2.96e+02, 1.55e+02, 5.30e+01, 3.57e+01, 1.09e+01, 1.80e-01,
-1.00e-03, -1.95e-01, -9.00e-03, -1.00e-03
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Theoretical model for CPR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// LO params A_C
vector<double> A_CPR = {
3.5327e+01, 2.7963e+01, 2.5124e+01, 2.2369e+01, 2.1887e+01, 2.0774e+01, 1.9831e+01, 1.9042e+01, 1.8340e+01, 1.7710e+01,
1.7152e+01, 1.6637e+01, 1.6145e+01, 1.5713e+01, 1.5312e+01, 1.4933e+01, 1.4572e+01, 1.4228e+01, 1.3915e+01, 1.3609e+01,
1.3321e+01, 1.3039e+01, 1.2779e+01, 1.2524e+01, 1.2281e+01, 1.2046e+01, 1.1823e+01, 1.1608e+01, 1.1392e+01, 1.1197e+01,
1.1002e+01, 1.0810e+01, 1.0627e+01, 1.0451e+01, 1.0273e+01, 1.0101e+01, 9.9461e+00, 9.7874e+00, 9.6281e+00, 9.4488e+00,
9.3321e+00, 9.1940e+00, 9.0491e+00, 8.9004e+00, 8.7791e+00, 8.6545e+00, 8.5181e+00, 8.3521e+00, 8.1526e+00, 8.1526e+00
};
// NLO params B_C
vector<double> B_CPR = {
-2.1510e+03, -4.7510e+02, -1.4510e+02, -1.3010e+02, -1.0910e+02, 1.7110e+02, 2.1500e+02, 2.4400e+02, 2.6700e+02, 2.8300e+02,
2.9610e+02, 3.0610e+02, 3.0600e+02, 3.1810e+02, 3.2000e+02, 3.2300e+02, 3.2400e+02, 3.2600e+02, 3.2420e+02, 3.2270e+02,
3.2190e+02, 3.2140e+02, 3.2080e+02, 3.1840e+02, 3.1760e+02, 3.1600e+02, 3.1390e+02, 3.0790e+02, 3.0780e+02, 3.0290e+02,
2.9900e+02, 2.9080e+02, 2.9640e+02, 2.9410e+02, 2.8970e+02, 2.8960e+02, 2.8430e+02, 2.8100e+02, 2.7520e+02, 2.7300e+02,
2.7110e+02, 2.6850e+02, 2.6360e+02, 2.6160e+02, 2.5800e+02, 2.5550e+02, 2.5180e+02, 2.4910e+02, 2.4650e+02, 2.4650e+02
};
// NNLO params C_C
vector<double> C_CPR = {
3.0640e+04, -3.0400e+04, -2.1500e+04, -1.4800e+04, -1.1200e+04, -7.6000e+03, -5.7000e+03, -2.7500e+03, -1.0600e+03, -7.5000e+02,
1.4000e+03, 1.6500e+03, 3.0000e+03, 3.1000e+03, 3.9000e+03, 4.1000e+03, 4.3000e+03, 4.8000e+03, 5.4000e+03, 5.9000e+03,
5.8000e+03, 5.5000e+03, 5.9000e+03, 6.2000e+03, 6.7000e+03, 6.4000e+03, 6.6000e+03, 6.6000e+03, 6.9000e+03, 6.8000e+03,
5.8000e+03, 5.8000e+03, 5.6000e+03, 5.8000e+03, 5.6000e+03, 5.4000e+03, 5.0000e+03, 4.8000e+03, 4.6000e+03, 4.3000e+03,
4.2000e+03, 4.1000e+03, 4.0000e+03, 3.9000e+03, 3.9000e+03, 3.8000e+03, 3.6000e+03, 3.5000e+03, 3.4000e+03, 3.4000e+03
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QCD Factors
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Nc = 3.0; double Nf = 5.0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Theory model
double THR_Order(double *x, double *par, const vector<double>& A, const vector<double>& B, const vector<double>& C, int order) {

	double tau = x[0]; 
	double alphaS = par[0]; 
	double asbar = alphaS / (2 * TMath::Pi());

	// Run through bins
	for (size_t i = 0; i < bins.size(); ++i) {
		
		// Check proximity
		if (fabs(tau - bins[i]) < 0.005) {

			// unbarred
			double At = 3*(Nc*Nc-1.0)/(4.0*Nc);
			double Bt = (Nc*Nc-1.0)/(8.0*Nc) * ( (243/4 - 44*1.202)*Nc + 3/(4*Nc) + (8*1.202 - 11)*Nf );

			// barred
			double AA = A[i];
			double BB = B[i] - At*A[i];
			double CC = C[i] - At*B[i] - (Bt-At*At)*A[i];

			// construct theory bin
			double val = 0;
			if (order == 1) val += asbar * AA;
			if (order == 2) val += asbar * AA + asbar * asbar * BB;
			if (order == 3) val += asbar * AA + asbar * asbar * BB + asbar * asbar * asbar * CC;

			// normalise to dO
			return val / bins[i];
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Theory model
double CPR_Order(double *x, double *par, const vector<double>& A, const vector<double>& B, const vector<double>& C, int order) {

	double tau = x[0]; 
	double alphaS = par[0]; 
	double asbar = alphaS / (2 * TMath::Pi());

	// Run through bins
	for (size_t i = 0; i < bins.size(); ++i) {
		
		// Check proximity
		if (fabs(tau - bins[i]) < 0.005) {

			// unbarred
			double At = 3*(Nc*Nc-1.0)/(4.0*Nc);
			double Bt = (Nc*Nc-1.0)/(8.0*Nc) * ( (243/4 - 44*1.202)*Nc + 3/(4*Nc) + (8*1.202 - 11)*Nf );

			// barred
			double AA = A[i];
			double BB = B[i] - At*A[i];
			double CC = C[i] - At*B[i] - (Bt-At*At)*A[i];

			// construct theory bin
			double val = 0;
			if (order == 1) val += asbar * AA;
			if (order == 2) val += asbar * AA + asbar * asbar * BB;
			if (order == 3) val += asbar * AA + asbar * asbar * BB + asbar * asbar * asbar * CC;

			// normalise to dO
			return val / bins[i];
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Wrapper LO
double THR_LOOO(double *x, double *par) {
    return THR_Order(x, par, A_THR, B_THR, C_THR, 1);
}
// Wrapper NLO
double THR_NLOO(double *x, double *par) {
    return THR_Order(x, par, A_THR, B_THR, C_THR, 2);
}
// Wrapper NNLO
double THR_NNLO(double *x, double *par) {
    return THR_Order(x, par, A_THR, B_THR, C_THR, 3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Wrapper LO
double CPR_LOOO(double *x, double *par) {
    return CPR_Order(x, par, A_CPR, B_CPR, C_CPR, 1);
}
// Wrapper NLO
double CPR_NLOO(double *x, double *par) {
    return CPR_Order(x, par, A_CPR, B_CPR, C_CPR, 2);
}
// Wrapper NNLO
double CPR_NNLO(double *x, double *par) {
    return CPR_Order(x, par, A_CPR, B_CPR, C_CPR, 3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Code
void ImpactofAlpha()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_912 = new TFile("5-CutData/cut_FCC912.root", "READ");
	TFile *input_160 = new TFile("5-CutData/cut_FCC160.root", "READ");
	TFile *input_240 = new TFile("5-CutData/cut_FCC240.root", "READ");
	TFile *input_365 = new TFile("5-CutData/cut_FCC365.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F *hist_ThrPyth_912 = (TH1F*)input_912->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_912->SetLineColor(kBlack); hist_ThrPyth_912->SetMarkerColor(kBlack); hist_ThrPyth_912->SetMarkerStyle(26); hist_ThrPyth_912->SetLineWidth(2); hist_ThrPyth_912->SetMarkerSize(2);
	TH1F *hist_ThrPyth_160 = (TH1F*)input_160->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_160->SetLineColor(kBlack); hist_ThrPyth_160->SetMarkerColor(kBlack); hist_ThrPyth_160->SetMarkerStyle(26); hist_ThrPyth_160->SetLineWidth(2); hist_ThrPyth_160->SetMarkerSize(2);
	TH1F *hist_ThrPyth_240 = (TH1F*)input_240->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_240->SetLineColor(kBlack); hist_ThrPyth_240->SetMarkerColor(kBlack); hist_ThrPyth_240->SetMarkerStyle(26); hist_ThrPyth_240->SetLineWidth(2); hist_ThrPyth_240->SetMarkerSize(2);
	TH1F *hist_ThrPyth_365 = (TH1F*)input_365->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_365->SetLineColor(kBlack); hist_ThrPyth_365->SetMarkerColor(kBlack); hist_ThrPyth_365->SetMarkerStyle(26); hist_ThrPyth_365->SetLineWidth(2); hist_ThrPyth_365->SetMarkerSize(2);

	TH1F *hist_CprPyth_912 = (TH1F*)input_912->Get("hist_CprPyth_TEO");
	hist_CprPyth_912->SetLineColor(kBlack); hist_CprPyth_912->SetMarkerColor(kBlack); hist_CprPyth_912->SetMarkerStyle(26); hist_CprPyth_912->SetLineWidth(2); hist_CprPyth_912->SetMarkerSize(2);
	TH1F *hist_CprPyth_160 = (TH1F*)input_160->Get("hist_CprPyth_TEO");
	hist_CprPyth_160->SetLineColor(kBlack); hist_CprPyth_160->SetMarkerColor(kBlack); hist_CprPyth_160->SetMarkerStyle(26); hist_CprPyth_160->SetLineWidth(2); hist_CprPyth_160->SetMarkerSize(2);
	TH1F *hist_CprPyth_240 = (TH1F*)input_240->Get("hist_CprPyth_TEO");
	hist_CprPyth_240->SetLineColor(kBlack); hist_CprPyth_240->SetMarkerColor(kBlack); hist_CprPyth_240->SetMarkerStyle(26); hist_CprPyth_240->SetLineWidth(2); hist_CprPyth_240->SetMarkerSize(2);
	TH1F *hist_CprPyth_365 = (TH1F*)input_365->Get("hist_CprPyth_TEO");
	hist_CprPyth_365->SetLineColor(kBlack); hist_CprPyth_365->SetMarkerColor(kBlack); hist_CprPyth_365->SetMarkerStyle(26); hist_CprPyth_365->SetLineWidth(2); hist_CprPyth_365->SetMarkerSize(2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading experimental data from TXT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Buffers
	double Par, Prb, ErrHi_Par, ErrLo_Par, ErrHi_Prb, ErrLo_Prb;
	vector<float> X, Y, ErrHi_X, ErrLo_X, ErrHi_Y, ErrLo_Y;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Flush vecs
	X.clear(), Y.clear(), ErrHi_X.clear(), ErrLo_X.clear(), ErrHi_Y.clear(), ErrLo_Y.clear();

	// Define histogram
	TH1F *hist_ThrExL3_912 = new TH1F("hist_ThrExL3_912", "", 500, 0, 0.4);
	hist_ThrExL3_912->SetTitle("Inverse Thrust");
	hist_ThrExL3_912->SetName("hist_ThrExL3_912");
	hist_ThrExL3_912->GetXaxis()->SetTitle("1-T");
	hist_ThrExL3_912->GetYaxis()->SetTitle("1/#sigma d#sigma/d(1-T)");
	hist_ThrExL3_912->SetLineColor(kYellow+2); hist_ThrExL3_912->SetMarkerColor(kYellow+2); hist_ThrExL3_912->SetMarkerStyle(27); hist_ThrExL3_912->SetLineWidth(2); hist_ThrExL3_912->SetMarkerSize(2);

	// Import data
	ifstream infile_01("3-LEPdata/EXP_ALP_912_THR_ASYMM.txt");

	// Sanity check
	if (!infile_01.is_open()) {
		std::cerr << "File not found!\n";
	}

	// Set reading order
	while ( infile_01 >> Par >> ErrHi_Par >> ErrLo_Par >> Prb >> ErrHi_Prb >> ErrLo_Prb ) {
		// Populate graph
		X.push_back(Par); Y.push_back(Prb);
		ErrHi_X.push_back(ErrHi_Par-Par); ErrLo_X.push_back(Par-ErrLo_Par);
		ErrHi_Y.push_back(ErrHi_Prb); ErrLo_Y.push_back(ErrLo_Prb);
		// Populate histogram
		hist_ThrExL3_912->SetBinContent(hist_ThrExL3_912->FindBin(Par), Prb);
		hist_ThrExL3_912->SetBinError(hist_ThrExL3_912->FindBin(Par), ErrHi_Prb+ErrLo_Prb);
	}
	// Close file
	infile_01.close();

	// Define graph
	TGraphAsymmErrors* grph_ThrExL3_912 = new TGraphAsymmErrors( X.size(), &X[0], &Y[0], &ErrHi_X[0], &ErrLo_X[0], &ErrHi_Y[0], &ErrLo_Y[0] );
	// Beautify
	grph_ThrExL3_912->SetTitle("Inverse Thrust");
	grph_ThrExL3_912->SetName("grph_ThrExL3_912");
	grph_ThrExL3_912->GetXaxis()->SetTitle("1-T");
	grph_ThrExL3_912->GetYaxis()->SetTitle("1/#sigma d#sigma/d(1-T)");
	grph_ThrExL3_912->SetLineColor(kBlack); grph_ThrExL3_912->SetMarkerColor(kBlack); grph_ThrExL3_912->SetLineWidth(2); grph_ThrExL3_912->SetMarkerSize(2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Flush vecs
	X.clear(), Y.clear(), ErrHi_X.clear(), ErrLo_X.clear(), ErrHi_Y.clear(), ErrLo_Y.clear();

	// Import data
	ifstream infile_02("3-LEPdata/EXP_ALP_912_CPR_ASYMM.txt");

	// Sanity check
	if (!infile_02.is_open()) {
		std::cerr << "File not found!\n";
	}

	// Set reading order
	while ( infile_02 >> Par >> ErrHi_Par >> ErrLo_Par >> Prb >> ErrHi_Prb >> ErrLo_Prb ) {
		// Populate axes
		X.push_back(Par); Y.push_back(Prb);
		// // Populate errors
		ErrHi_X.push_back(ErrHi_Par); ErrLo_X.push_back(ErrLo_Par);
		ErrHi_Y.push_back(ErrHi_Prb); ErrLo_Y.push_back(ErrLo_Prb);
	}
	// Close file
	infile_02.close();

	// Create TGraphAsymmErrors
	TGraphAsymmErrors* grph_CprExL3_912 = new TGraphAsymmErrors( X.size(), &X[0], &Y[0], &ErrHi_X[0], &ErrLo_X[0], &ErrHi_Y[0], &ErrLo_Y[0] );
	// Beautify
	grph_CprExL3_912->SetTitle("C-parameter");
	grph_CprExL3_912->SetName("grph_CprExL3_912");
	grph_CprExL3_912->GetXaxis()->SetTitle("C");
	grph_CprExL3_912->GetYaxis()->SetTitle("1/#sigma d#sigma/d(C)");
	grph_CprExL3_912->SetLineColor(kBlack); grph_CprExL3_912->SetMarkerColor(kBlack); grph_CprExL3_912->SetLineWidth(2); grph_CprExL3_912->SetMarkerSize(2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising by area under histogram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	hist_ThrPyth_912->Scale(1.0/hist_ThrPyth_912->Integral("width"));
	hist_CprPyth_912->Scale(1.0/hist_CprPyth_912->Integral("width"));

	hist_ThrPyth_160->Scale(1.0/hist_ThrPyth_160->Integral("width"));
	hist_CprPyth_160->Scale(1.0/hist_CprPyth_160->Integral("width"));

	hist_ThrPyth_240->Scale(1.0/hist_ThrPyth_240->Integral("width"));
	hist_CprPyth_240->Scale(1.0/hist_CprPyth_240->Integral("width"));

	hist_ThrPyth_365->Scale(1.0/hist_ThrPyth_365->Integral("width"));
	hist_CprPyth_365->Scale(1.0/hist_CprPyth_365->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912->SetStats(kFALSE);
	hist_ThrPyth_160->SetStats(kFALSE);
	hist_ThrPyth_240->SetStats(kFALSE);
	hist_ThrPyth_365->SetStats(kFALSE);

	hist_CprPyth_912->SetStats(kFALSE);
	hist_CprPyth_160->SetStats(kFALSE);
	hist_CprPyth_240->SetStats(kFALSE);
	hist_CprPyth_365->SetStats(kFALSE);
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fit PYTHIA to Theory
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float AlpFit_912_min = 0.09, AlpFit_912_max = 0.25, CprFit_912_min = 0.36, CprFit_912_max = 0.74;
	float AlpFit_160_min = 0.09, AlpFit_160_max = 0.25, CprFit_160_min = 0.36, CprFit_160_max = 0.74;
	float AlpFit_240_min = 0.09, AlpFit_240_max = 0.25, CprFit_240_min = 0.36, CprFit_240_max = 0.74;
	float AlpFit_365_min = 0.09, AlpFit_365_max = 0.25, CprFit_365_min = 0.36, CprFit_365_max = 0.74;

	TF1 *hist_fitThLO_912 = new TF1("hist_fitThLO_912", THR_LOOO, AlpFit_912_min, AlpFit_912_max, 1);
	hist_fitThLO_912->SetLineColor(kGreen+1); hist_fitThLO_912->SetMarkerColor(kGreen+1); hist_fitThLO_912->SetMarkerStyle(53); hist_fitThLO_912->SetLineWidth(2); hist_fitThLO_912->SetMarkerSize(1);	
	TF1 *hist_fitThNL_912 = new TF1("hist_fitThNL_912", THR_NLOO, AlpFit_912_min, AlpFit_912_max, 1);
	hist_fitThNL_912->SetLineColor(kRed+1); hist_fitThNL_912->SetMarkerColor(kRed+1); hist_fitThNL_912->SetMarkerStyle(53); hist_fitThNL_912->SetLineWidth(2); hist_fitThNL_912->SetMarkerSize(1);
	TF1 *hist_fitThNN_912 = new TF1("hist_fitThNN_912", THR_NNLO, AlpFit_912_min, AlpFit_912_max, 1);
	hist_fitThNN_912->SetLineColor(kBlue+1); hist_fitThNN_912->SetMarkerColor(kBlue+1); hist_fitThNN_912->SetMarkerStyle(53); hist_fitThNN_912->SetLineWidth(2); hist_fitThNN_912->SetMarkerSize(1);

	TF1 *hist_fitThLO_160 = new TF1("hist_fitThLO_160", THR_LOOO, AlpFit_160_min, AlpFit_160_max, 1);
	hist_fitThLO_160->SetLineColor(kGreen+1); hist_fitThLO_160->SetMarkerColor(kGreen+1); hist_fitThLO_160->SetMarkerStyle(53); hist_fitThLO_160->SetLineWidth(2); hist_fitThLO_160->SetMarkerSize(1);
	TF1 *hist_fitThNL_160 = new TF1("hist_fitThNL_160", THR_NLOO, AlpFit_160_min, AlpFit_160_max, 1);
	hist_fitThNL_160->SetLineColor(kRed+1); hist_fitThNL_160->SetMarkerColor(kRed+1); hist_fitThNL_160->SetMarkerStyle(53); hist_fitThNL_160->SetLineWidth(2); hist_fitThNL_160->SetMarkerSize(1);
	TF1 *hist_fitThNN_160 = new TF1("hist_fitThNN_160", THR_NNLO, AlpFit_160_min, AlpFit_160_max, 1);
	hist_fitThNN_160->SetLineColor(kBlue+1); hist_fitThNN_160->SetMarkerColor(kBlue+1); hist_fitThNN_160->SetMarkerStyle(53); hist_fitThNN_160->SetLineWidth(2); hist_fitThNN_160->SetMarkerSize(1);

	TF1 *hist_fitThLO_240 = new TF1("hist_fitThLO_240", THR_LOOO, AlpFit_240_min, AlpFit_240_max, 1);
	hist_fitThLO_240->SetLineColor(kGreen+1); hist_fitThLO_240->SetMarkerColor(kGreen+1); hist_fitThLO_240->SetMarkerStyle(53); hist_fitThLO_240->SetLineWidth(2); hist_fitThLO_240->SetMarkerSize(1);
	TF1 *hist_fitThNL_240 = new TF1("hist_fitThNL_240", THR_NLOO, AlpFit_240_min, AlpFit_240_max, 1);
	hist_fitThNL_240->SetLineColor(kRed+1); hist_fitThNL_240->SetMarkerColor(kRed+1); hist_fitThNL_240->SetMarkerStyle(53); hist_fitThNL_240->SetLineWidth(2); hist_fitThNL_240->SetMarkerSize(1);
	TF1 *hist_fitThNN_240 = new TF1("hist_fitThNN_240", THR_NNLO, AlpFit_240_min, AlpFit_240_max, 1);
	hist_fitThNN_240->SetLineColor(kBlue+1); hist_fitThNN_240->SetMarkerColor(kBlue+1); hist_fitThNN_240->SetMarkerStyle(53); hist_fitThNN_240->SetLineWidth(2); hist_fitThNN_240->SetMarkerSize(1);

	TF1 *hist_fitThLO_365 = new TF1("hist_fitThLO_365", THR_LOOO, AlpFit_365_min, AlpFit_365_max, 1);
	hist_fitThLO_365->SetLineColor(kGreen+1); hist_fitThLO_365->SetMarkerColor(kGreen+1); hist_fitThLO_365->SetMarkerStyle(53); hist_fitThLO_365->SetLineWidth(2); hist_fitThLO_365->SetMarkerSize(1);
	TF1 *hist_fitThNL_365 = new TF1("hist_fitThNL_365", THR_NLOO, AlpFit_365_min, AlpFit_365_max, 1);
	hist_fitThNL_365->SetLineColor(kRed+1); hist_fitThNL_365->SetMarkerColor(kRed+1); hist_fitThNL_365->SetMarkerStyle(53); hist_fitThNL_365->SetLineWidth(2); hist_fitThNL_365->SetMarkerSize(1);
	TF1 *hist_fitThNN_365 = new TF1("hist_fitThNN_365", THR_NNLO, AlpFit_365_min, AlpFit_365_max, 1);
	hist_fitThNN_365->SetLineColor(kBlue+1); hist_fitThNN_365->SetMarkerColor(kBlue+1); hist_fitThNN_365->SetMarkerStyle(53); hist_fitThNN_365->SetLineWidth(2); hist_fitThNN_365->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TF1 *hist_fitCpLO_912 = new TF1("hist_fitCpLO_912", CPR_LOOO, CprFit_912_min, CprFit_912_max, 1);
	hist_fitCpLO_912->SetLineColor(kGreen+1); hist_fitCpLO_912->SetMarkerColor(kGreen+1); hist_fitCpLO_912->SetMarkerStyle(53); hist_fitCpLO_912->SetLineWidth(2); hist_fitCpLO_912->SetMarkerSize(1);	
	TF1 *hist_fitCpNL_912 = new TF1("hist_fitCpNL_912", CPR_NLOO, CprFit_912_min, CprFit_912_max, 1);
	hist_fitCpNL_912->SetLineColor(kRed+1); hist_fitCpNL_912->SetMarkerColor(kRed+1); hist_fitCpNL_912->SetMarkerStyle(53); hist_fitCpNL_912->SetLineWidth(2); hist_fitCpNL_912->SetMarkerSize(1);
	TF1 *hist_fitCpNN_912 = new TF1("hist_fitCpNN_912", CPR_NNLO, CprFit_912_min, CprFit_912_max, 1);
	hist_fitCpNN_912->SetLineColor(kBlue+1); hist_fitCpNN_912->SetMarkerColor(kBlue+1); hist_fitCpNN_912->SetMarkerStyle(53); hist_fitCpNN_912->SetLineWidth(2); hist_fitCpNN_912->SetMarkerSize(1);

	TF1 *hist_fitCpLO_160 = new TF1("hist_fitCpLO_160", CPR_LOOO, CprFit_160_min, CprFit_160_max, 1);
	hist_fitCpLO_160->SetLineColor(kGreen+1); hist_fitCpLO_160->SetMarkerColor(kGreen+1); hist_fitCpLO_160->SetMarkerStyle(53); hist_fitCpLO_160->SetLineWidth(2); hist_fitCpLO_160->SetMarkerSize(1);
	TF1 *hist_fitCpNL_160 = new TF1("hist_fitCpNL_160", CPR_NLOO, CprFit_160_min, CprFit_160_max, 1);
	hist_fitCpNL_160->SetLineColor(kRed+1); hist_fitCpNL_160->SetMarkerColor(kRed+1); hist_fitCpNL_160->SetMarkerStyle(53); hist_fitCpNL_160->SetLineWidth(2); hist_fitCpNL_160->SetMarkerSize(1);
	TF1 *hist_fitCpNN_160 = new TF1("hist_fitCpNN_160", CPR_NNLO, CprFit_160_min, CprFit_160_max, 1);
	hist_fitCpNN_160->SetLineColor(kBlue+1); hist_fitCpNN_160->SetMarkerColor(kBlue+1); hist_fitCpNN_160->SetMarkerStyle(53); hist_fitCpNN_160->SetLineWidth(2); hist_fitCpNN_160->SetMarkerSize(1);

	TF1 *hist_fitCpLO_240 = new TF1("hist_fitCpLO_240", CPR_LOOO, CprFit_240_min, CprFit_240_max, 1);
	hist_fitCpLO_240->SetLineColor(kGreen+1); hist_fitCpLO_240->SetMarkerColor(kGreen+1); hist_fitCpLO_240->SetMarkerStyle(53); hist_fitCpLO_240->SetLineWidth(2); hist_fitCpLO_240->SetMarkerSize(1);
	TF1 *hist_fitCpNL_240 = new TF1("hist_fitCpNL_240", CPR_NLOO, CprFit_240_min, CprFit_240_max, 1);
	hist_fitCpNL_240->SetLineColor(kRed+1); hist_fitCpNL_240->SetMarkerColor(kRed+1); hist_fitCpNL_240->SetMarkerStyle(53); hist_fitCpNL_240->SetLineWidth(2); hist_fitCpNL_240->SetMarkerSize(1);
	TF1 *hist_fitCpNN_240 = new TF1("hist_fitCpNN_240", CPR_NNLO, CprFit_240_min, CprFit_240_max, 1);
	hist_fitCpNN_240->SetLineColor(kBlue+1); hist_fitCpNN_240->SetMarkerColor(kBlue+1); hist_fitCpNN_240->SetMarkerStyle(53); hist_fitCpNN_240->SetLineWidth(2); hist_fitCpNN_240->SetMarkerSize(1);

	TF1 *hist_fitCpLO_365 = new TF1("hist_fitCpLO_365", CPR_LOOO, CprFit_365_min, CprFit_365_max, 1);
	hist_fitCpLO_365->SetLineColor(kGreen+1); hist_fitCpLO_365->SetMarkerColor(kGreen+1); hist_fitCpLO_365->SetMarkerStyle(53); hist_fitCpLO_365->SetLineWidth(2); hist_fitCpLO_365->SetMarkerSize(1);
	TF1 *hist_fitCpNL_365 = new TF1("hist_fitCpNL_365", CPR_NLOO, CprFit_365_min, CprFit_365_max, 1);
	hist_fitCpNL_365->SetLineColor(kRed+1); hist_fitCpNL_365->SetMarkerColor(kRed+1); hist_fitCpNL_365->SetMarkerStyle(53); hist_fitCpNL_365->SetLineWidth(2); hist_fitCpNL_365->SetMarkerSize(1);
	TF1 *hist_fitCpNN_365 = new TF1("hist_fitCpNN_365", CPR_NNLO, CprFit_365_min, CprFit_365_max, 1);
	hist_fitCpNN_365->SetLineColor(kBlue+1); hist_fitCpNN_365->SetMarkerColor(kBlue+1); hist_fitCpNN_365->SetMarkerStyle(53); hist_fitCpNN_365->SetLineWidth(2); hist_fitCpNN_365->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	float guess = 0.1, guess_min = 0.01, guess_max = 1.0;

	hist_fitThLO_912->SetParameter(0, guess); hist_fitThLO_912->SetParLimits(0, guess_min, guess_max);
	hist_fitThNL_912->SetParameter(0, guess); hist_fitThNL_912->SetParLimits(0, guess_min, guess_max);
	hist_fitThNN_912->SetParameter(0, guess); hist_fitThNN_912->SetParLimits(0, guess_min, guess_max);
	hist_fitThLO_160->SetParameter(0, guess); hist_fitThLO_160->SetParLimits(0, guess_min, guess_max);
	hist_fitThNL_160->SetParameter(0, guess); hist_fitThNL_160->SetParLimits(0, guess_min, guess_max);
	hist_fitThNN_160->SetParameter(0, guess); hist_fitThNN_160->SetParLimits(0, guess_min, guess_max);
	hist_fitThLO_240->SetParameter(0, guess); hist_fitThLO_240->SetParLimits(0, guess_min, guess_max);
	hist_fitThNL_240->SetParameter(0, guess); hist_fitThNL_240->SetParLimits(0, guess_min, guess_max);
	hist_fitThNN_240->SetParameter(0, guess); hist_fitThNN_240->SetParLimits(0, guess_min, guess_max);
	hist_fitThLO_365->SetParameter(0, guess); hist_fitThLO_365->SetParLimits(0, guess_min, guess_max);
	hist_fitThNL_365->SetParameter(0, guess); hist_fitThNL_365->SetParLimits(0, guess_min, guess_max);
	hist_fitThNN_365->SetParameter(0, guess); hist_fitThNN_365->SetParLimits(0, guess_min, guess_max);
	
	hist_fitCpLO_912->SetParameter(0, guess); hist_fitCpLO_912->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNL_912->SetParameter(0, guess); hist_fitCpNL_912->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNN_912->SetParameter(0, guess); hist_fitCpNN_912->SetParLimits(0, guess_min, guess_max);
	hist_fitCpLO_160->SetParameter(0, guess); hist_fitCpLO_160->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNL_160->SetParameter(0, guess); hist_fitCpNL_160->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNN_160->SetParameter(0, guess); hist_fitCpNN_160->SetParLimits(0, guess_min, guess_max);
	hist_fitCpLO_240->SetParameter(0, guess); hist_fitCpLO_240->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNL_240->SetParameter(0, guess); hist_fitCpNL_240->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNN_240->SetParameter(0, guess); hist_fitCpNN_240->SetParLimits(0, guess_min, guess_max);
	hist_fitCpLO_365->SetParameter(0, guess); hist_fitCpLO_365->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNL_365->SetParameter(0, guess); hist_fitCpNL_365->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNN_365->SetParameter(0, guess); hist_fitCpNN_365->SetParLimits(0, guess_min, guess_max);
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// grph_ThrExL3_912->Fit(hist_fitThLO_912, "RNQ MINOS");
	// grph_ThrExL3_912->Fit(hist_fitThNL_912, "RNQ MINOS");
	// grph_ThrExL3_912->Fit(hist_fitThNN_912, "RNQ MINOS");
	// grph_CprExL3_912->Fit(hist_fitCpLO_912, "RNQ MINOS");
	// grph_CprExL3_912->Fit(hist_fitCpNL_912, "RNQ MINOS");
	// grph_CprExL3_912->Fit(hist_fitCpNN_912, "RNQ MINOS");

	// TGraphAsymmErrors* grph_ThrPyth_912 = HistToGraph(hist_ThrPyth_912, true);

	hist_ThrPyth_912->Fit(hist_fitThLO_912, "RNQ MINOS");
	hist_ThrPyth_912->Fit(hist_fitThNL_912, "RNQ MINOS");
	hist_ThrPyth_912->Fit(hist_fitThNN_912, "RNQ MINOS");
	hist_ThrPyth_160->Fit(hist_fitThLO_160, "RNQ MINOS");
	hist_ThrPyth_160->Fit(hist_fitThNL_160, "RNQ MINOS");
	hist_ThrPyth_160->Fit(hist_fitThNN_160, "RNQ MINOS");
	hist_ThrPyth_240->Fit(hist_fitThLO_240, "RNQ MINOS");
	hist_ThrPyth_240->Fit(hist_fitThNL_240, "RNQ MINOS");
	hist_ThrPyth_240->Fit(hist_fitThNN_240, "RNQ MINOS");
	hist_ThrPyth_365->Fit(hist_fitThLO_365, "RNQ MINOS");
	hist_ThrPyth_365->Fit(hist_fitThNL_365, "RNQ MINOS");
	hist_ThrPyth_365->Fit(hist_fitThNN_365, "RNQ MINOS");
	
	hist_CprPyth_912->Fit(hist_fitCpLO_912, "RNQ MINOS");
	hist_CprPyth_912->Fit(hist_fitCpNL_912, "RNQ MINOS");
	hist_CprPyth_912->Fit(hist_fitCpNN_912, "RNQ MINOS");
	hist_CprPyth_160->Fit(hist_fitCpLO_160, "RNQ MINOS");
	hist_CprPyth_160->Fit(hist_fitCpNL_160, "RNQ MINOS");
	hist_CprPyth_160->Fit(hist_fitCpNN_160, "RNQ MINOS");
	hist_CprPyth_240->Fit(hist_fitCpLO_240, "RNQ MINOS");
	hist_CprPyth_240->Fit(hist_fitCpNL_240, "RNQ MINOS");
	hist_CprPyth_240->Fit(hist_fitCpNN_240, "RNQ MINOS");
	hist_CprPyth_365->Fit(hist_fitCpLO_365, "RNQ MINOS");
	hist_CprPyth_365->Fit(hist_fitCpNL_365, "RNQ MINOS");
	hist_CprPyth_365->Fit(hist_fitCpNN_365, "RNQ MINOS");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	grph_ThrExL3_912->GetXaxis()->SetLabelSize(0.06);
	grph_ThrExL3_912->GetXaxis()->SetTitleSize(0.06);
	grph_ThrExL3_912->GetYaxis()->SetLabelSize(0.06);
	grph_ThrExL3_912->GetYaxis()->SetTitleSize(0.06);

	hist_ThrPyth_912->GetXaxis()->SetLabelSize(0.06);
	hist_ThrPyth_912->GetXaxis()->SetTitleSize(0.06);
	hist_ThrPyth_912->GetYaxis()->SetLabelSize(0.06);
	hist_ThrPyth_912->GetYaxis()->SetTitleSize(0.06);

	hist_ThrPyth_160->GetXaxis()->SetLabelSize(0.06);
	hist_ThrPyth_160->GetXaxis()->SetTitleSize(0.06);
	hist_ThrPyth_160->GetYaxis()->SetLabelSize(0.06);
	hist_ThrPyth_160->GetYaxis()->SetTitleSize(0.06);

	hist_ThrPyth_240->GetXaxis()->SetLabelSize(0.06);
	hist_ThrPyth_240->GetXaxis()->SetTitleSize(0.06);
	hist_ThrPyth_240->GetYaxis()->SetLabelSize(0.06);
	hist_ThrPyth_240->GetYaxis()->SetTitleSize(0.06);

	hist_ThrPyth_365->GetXaxis()->SetLabelSize(0.06);
	hist_ThrPyth_365->GetXaxis()->SetTitleSize(0.06);
	hist_ThrPyth_365->GetYaxis()->SetLabelSize(0.06);
	hist_ThrPyth_365->GetYaxis()->SetTitleSize(0.06);

	grph_CprExL3_912->GetXaxis()->SetLabelSize(0.06);
	grph_CprExL3_912->GetXaxis()->SetTitleSize(0.06);
	grph_CprExL3_912->GetYaxis()->SetLabelSize(0.06);
	grph_CprExL3_912->GetYaxis()->SetTitleSize(0.06);

	hist_CprPyth_912->GetXaxis()->SetLabelSize(0.06);
	hist_CprPyth_912->GetXaxis()->SetTitleSize(0.06);
	hist_CprPyth_912->GetYaxis()->SetLabelSize(0.06);
	hist_CprPyth_912->GetYaxis()->SetTitleSize(0.06);

	hist_CprPyth_160->GetXaxis()->SetLabelSize(0.06);
	hist_CprPyth_160->GetXaxis()->SetTitleSize(0.06);
	hist_CprPyth_160->GetYaxis()->SetLabelSize(0.06);
	hist_CprPyth_160->GetYaxis()->SetTitleSize(0.06);

	hist_CprPyth_240->GetXaxis()->SetLabelSize(0.06);
	hist_CprPyth_240->GetXaxis()->SetTitleSize(0.06);
	hist_CprPyth_240->GetYaxis()->SetLabelSize(0.06);
	hist_CprPyth_240->GetYaxis()->SetTitleSize(0.06);

	hist_CprPyth_365->GetXaxis()->SetLabelSize(0.06);
	hist_CprPyth_365->GetXaxis()->SetTitleSize(0.06);
	hist_CprPyth_365->GetYaxis()->SetLabelSize(0.06);
	hist_CprPyth_365->GetYaxis()->SetTitleSize(0.06);

	grph_ThrExL3_912->SetTitle("");
	grph_CprExL3_912->SetTitle("");
	hist_ThrPyth_912->SetTitle("");
	hist_ThrPyth_160->SetTitle("");
	hist_ThrPyth_240->SetTitle("");
	hist_ThrPyth_365->SetTitle("");

	hist_CprPyth_912->SetTitle("");
	hist_CprPyth_160->SetTitle("");
	hist_CprPyth_240->SetTitle("");
	hist_CprPyth_365->SetTitle("");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv1 = new TCanvas("cv1", "FCC-ee ISR Studies", 1400, 1400);

	// TLegend* lg = new TLegend(0.84, 0.69, 0.92, 0.93);
	// lg->AddEntry(hist_ThrPyth_912, "MC", "L");
	// lg->AddEntry(hist_fitThLO_912, "#it{O}(#alpha_{s}^{1})", "L");
	// lg->AddEntry(hist_fitThNL_912, "#it{O}(#alpha_{s}^{2})", "L");
	// lg->AddEntry(hist_fitThNN_912, "#it{O}(#alpha_{s}^{3})", "L");
	// lg->SetTextSize(0.05);	

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv1->SetMargin(0, 0, 0, 0); 
	// cv1->Divide(2,4);
	// for (int i = 1; i <= 8; i++) {
	// 	cv1->cd(i);
	// 	gPad->SetTopMargin(0.025);
	// 	gPad->SetBottomMargin(0.14);
	// 	gPad->SetLeftMargin(0.15);
	// 	gPad->SetRightMargin(0.04);
	// 	gPad->SetTickx(); gPad->SetTicky();
	// 	gPad->SetLogy();
	// }

	// cv1->cd(7);
	// hist_ThrPyth_912->Draw("HIST");
	// // hist_fitThLO_912->Draw("HIST SAME");
	// // hist_fitThNL_912->Draw("HIST SAME");
	// hist_fitThNN_912->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(5);
	// hist_ThrPyth_160->Draw("HIST");
	// // hist_fitThLO_160->Draw("HIST SAME");
	// // hist_fitThNL_160->Draw("HIST SAME");
	// hist_fitThNN_160->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(3);
	// hist_ThrPyth_240->Draw("HIST");
	// // hist_fitThLO_240->Draw("HIST SAME");
	// // hist_fitThNL_240->Draw("HIST SAME");
	// hist_fitThNN_240->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(1);
	// hist_ThrPyth_365->Draw("HIST");
	// // hist_fitThLO_365->Draw("HIST SAME");
	// // hist_fitThNL_365->Draw("HIST SAME");
	// hist_fitThNN_365->Draw("HIST SAME");
	// lg->Draw("SAME");

	// cv1->cd(8);
	// hist_CprPyth_912->Draw("HIST");
	// // hist_fitCpLO_912->Draw("HIST SAME");
	// // hist_fitCpNL_912->Draw("HIST SAME");
	// hist_fitCpNN_912->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(6);
	// hist_CprPyth_160->Draw("HIST");
	// // hist_fitCpLO_160->Draw("HIST SAME");
	// // hist_fitCpNL_160->Draw("HIST SAME");
	// hist_fitCpNN_160->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(4);
	// hist_CprPyth_240->Draw("HIST");
	// // hist_fitCpLO_240->Draw("HIST SAME");
	// // hist_fitCpNL_240->Draw("HIST SAME");
	// hist_fitCpNN_240->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(2);
	// hist_CprPyth_365->Draw("HIST");
	// // hist_fitCpLO_365->Draw("HIST SAME");
	// // hist_fitCpNL_365->Draw("HIST SAME");
	// hist_fitCpNN_365->Draw("HIST SAME");
	// lg->Draw("SAME");

	// // Set limits
	// hist_ThrPyth_912->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_ThrPyth_912->GetXaxis()->SetRangeUser(0,0.4);
	// hist_ThrPyth_160->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_ThrPyth_160->GetXaxis()->SetRangeUser(0,0.4);
	// hist_ThrPyth_240->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_ThrPyth_240->GetXaxis()->SetRangeUser(0,0.4);
	// hist_ThrPyth_365->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_ThrPyth_365->GetXaxis()->SetRangeUser(0,0.4);

	// hist_CprPyth_912->GetYaxis()->SetRangeUser(1E-3,1E1);
	// hist_CprPyth_912->GetXaxis()->SetRangeUser(0,1.0);
	// hist_CprPyth_160->GetYaxis()->SetRangeUser(1E-3,1E1);
	// hist_CprPyth_160->GetXaxis()->SetRangeUser(0,1.0);
	// hist_CprPyth_240->GetYaxis()->SetRangeUser(1E-3,1E1);
	// hist_CprPyth_240->GetXaxis()->SetRangeUser(0,1.0);
	// hist_CprPyth_365->GetYaxis()->SetRangeUser(1E-3,1E1);
	// hist_CprPyth_365->GetXaxis()->SetRangeUser(0,1.0);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv1->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 800, 600);

	TLegend* lg2 = new TLegend(0.84, 0.69, 0.92, 0.93);
	lg2->AddEntry(hist_ThrPyth_912, "PYTHIA", "P");
	lg2->AddEntry(hist_ThrExL3_912, "ALEPH", "P");
	lg2->SetTextSize(0.05);	

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv2->SetMargin(0, 0, 0, 0); 
	gPad->SetTopMargin(0.025);
	gPad->SetBottomMargin(0.14);
	gPad->SetLeftMargin(0.15);
	gPad->SetRightMargin(0.04);
	gPad->SetTickx(); gPad->SetTicky();
	// gPad->SetLogy();

	// Draw
	hist_ThrPyth_912->Draw("P");
	hist_ThrExL3_912->Draw("P SAME");
	lg2->Draw("SAME");

	// Set limits
	// hist_ThrPyth_912->GetYaxis()->SetRangeUser(1E-4,1E2);
	hist_ThrPyth_912->GetYaxis()->SetRangeUser(0,5);
	hist_ThrPyth_912->GetXaxis()->SetRangeUser(0.09,0.25);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv2->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Print results
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << fixed << setprecision(6);

	cout << "================= FITTING WITH THRUST ==============================================================" << endl;
	cout << "Order \t LO \t\t\t\t NLO \t\t\t\t NNLO" << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	cout << "√s \t χ²/ndf \t Alpha \t\t χ²/ndf \t Alpha \t\t χ²/ndf \t Alpha " << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	cout << "91.2 \t " << hist_fitThLO_912->GetChisquare()<<"/"<<hist_fitThLO_912->GetNDF() << "\t" << hist_fitThLO_912->GetParameter(0) << "\t" <<
						hist_fitThNL_912->GetChisquare()<<"/"<<hist_fitThLO_912->GetNDF() << "\t" << hist_fitThNL_912->GetParameter(0) << "\t" <<
						hist_fitThNN_912->GetChisquare()<<"/"<<hist_fitThLO_912->GetNDF() << "\t" << hist_fitThNN_912->GetParameter(0) << "\t" << endl;
	cout << "160 \t " << hist_fitThLO_160->GetChisquare()<<"/"<<hist_fitThLO_160->GetNDF() << "\t" << hist_fitThLO_160->GetParameter(0) << "\t" <<
						hist_fitThNL_160->GetChisquare()<<"/"<<hist_fitThNL_160->GetNDF() << "\t" << hist_fitThNL_160->GetParameter(0) << "\t" <<
						hist_fitThNN_160->GetChisquare()<<"/"<<hist_fitThNN_160->GetNDF() << "\t" << hist_fitThNN_160->GetParameter(0) << "\t" << endl;
	cout << "240 \t " << hist_fitThLO_240->GetChisquare()<<"/"<<hist_fitThLO_240->GetNDF() << "\t" << hist_fitThLO_240->GetParameter(0) << "\t" <<
						hist_fitThNL_240->GetChisquare()<<"/"<<hist_fitThNL_240->GetNDF() << "\t" << hist_fitThNL_240->GetParameter(0) << "\t" <<
						hist_fitThNN_240->GetChisquare()<<"/"<<hist_fitThNN_240->GetNDF() << "\t" << hist_fitThNN_240->GetParameter(0) << "\t" << endl;
	cout << "365 \t " << hist_fitThLO_365->GetChisquare()<<"/"<<hist_fitThLO_365->GetNDF() << "\t" << hist_fitThLO_365->GetParameter(0) << "\t" <<
						hist_fitThNL_365->GetChisquare()<<"/"<<hist_fitThNL_365->GetNDF() << "\t" << hist_fitThNL_365->GetParameter(0) << "\t" <<
						hist_fitThNN_365->GetChisquare()<<"/"<<hist_fitThNN_365->GetNDF() << "\t" << hist_fitThNN_365->GetParameter(0) << "\t" << endl;
	cout << "====================================================================================================" << endl;

	cout << "================= FITTING WITH CPARAM ==============================================================" << endl;
	cout << "Order \t LO \t\t\t\t NLO \t\t\t\t NNLO" << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	cout << "√s \t χ²/ndf \t Alpha \t\t χ²/ndf \t Alpha \t\t χ²/ndf \t Alpha " << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	cout << "91.2 \t " << hist_fitCpLO_912->GetChisquare()<<"/"<<hist_fitCpLO_912->GetNDF() << "\t" << hist_fitCpLO_912->GetParameter(0) << "\t" <<
						hist_fitCpNL_912->GetChisquare()<<"/"<<hist_fitCpNL_912->GetNDF() << "\t" << hist_fitCpNL_912->GetParameter(0) << "\t" <<
						hist_fitCpNN_912->GetChisquare()<<"/"<<hist_fitCpNN_912->GetNDF() << "\t" << hist_fitCpNN_912->GetParameter(0) << "\t" << endl;
	cout << "160 \t " << hist_fitCpLO_160->GetChisquare()<<"/"<<hist_fitCpLO_160->GetNDF() << "\t" << hist_fitCpLO_160->GetParameter(0) << "\t" <<
						hist_fitCpNL_160->GetChisquare()<<"/"<<hist_fitCpNL_160->GetNDF() << "\t" << hist_fitCpNL_160->GetParameter(0) << "\t" <<
						hist_fitCpNN_160->GetChisquare()<<"/"<<hist_fitCpNN_160->GetNDF() << "\t" << hist_fitCpNN_160->GetParameter(0) << "\t" << endl;
	cout << "240 \t " << hist_fitCpLO_240->GetChisquare()<<"/"<<hist_fitCpLO_240->GetNDF() << "\t" << hist_fitCpLO_240->GetParameter(0) << "\t" <<
						hist_fitCpNL_240->GetChisquare()<<"/"<<hist_fitCpNL_240->GetNDF() << "\t" << hist_fitCpNL_240->GetParameter(0) << "\t" <<
						hist_fitCpNN_240->GetChisquare()<<"/"<<hist_fitCpNN_240->GetNDF() << "\t" << hist_fitCpNN_240->GetParameter(0) << "\t" << endl;
	cout << "365 \t " << hist_fitCpLO_365->GetChisquare()<<"/"<<hist_fitCpLO_365->GetNDF() << "\t" << hist_fitCpLO_365->GetParameter(0) << "\t" <<
						hist_fitCpNL_365->GetChisquare()<<"/"<<hist_fitCpNL_365->GetNDF() << "\t" << hist_fitCpNL_365->GetParameter(0) << "\t" <<
						hist_fitCpNN_365->GetChisquare()<<"/"<<hist_fitCpNN_365->GetNDF() << "\t" << hist_fitCpNN_365->GetParameter(0) << "\t" << endl;
	cout << "====================================================================================================" << endl;

}