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
// QCD theory models
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Thrust [Bins, LO, NLO, NNLO]
std::vector<std::array<double,4>> Theory_THR = {
    {0.005, 25.7970, -495.7000, -9000.0000},
    {0.015, 18.2990,  216.6000, -3300.0000},
    {0.025, 15.4110,  280.9000,  1600.0000},
    {0.035, 13.5230,  292.0000,  4000.0000},
    {0.045, 12.1030,  287.7000,  4900.0000},
    {0.055, 10.9692,  277.2000,  5300.0000},
    {0.065, 10.0228,  263.8000,  5500.0000},
    {0.075,  9.2112,  250.5000,  5400.0000},
    {0.085,  8.5022,  237.1000,  5500.0000},
    {0.095,  7.8724,  224.4000,  5200.0000},
    {0.105,  7.3045,  211.3000,  5100.0000},
    {0.115,  6.7891,  199.3000,  4800.0000},
    {0.125,  6.3179,  187.8000,  4500.0000},
    {0.135,  5.8820,  176.8000,  4300.0000},
    {0.145,  5.4791,  166.6000,  4100.0000},
    {0.155,  5.1030,  157.2000,  3900.0000},
    {0.165,  4.7484,  147.5000,  3800.0000},
    {0.175,  4.4141,  139.3000,  3500.0000},
    {0.185,  4.0962,  130.6000,  3290.0000},
    {0.195,  3.7931,  123.1000,  3200.0000},
    {0.205,  3.5028,  115.3000,  2980.0000},
    {0.215,  3.2220,  108.1000,  2850.0000},
    {0.225,  2.9494,  101.1000,  2630.0000},
    {0.235,  2.6826,   94.7000,  2500.0000},
    {0.245,  2.4223,   88.2000,  2330.0000},
    {0.255,  2.1634,   82.1000,  2350.0000},
    {0.265,  1.9062,   75.4000,  2150.0000},
    {0.275,  1.6470,   69.4000,  1970.0000},
    {0.285,  1.3841,   63.0000,  1800.0000},
    {0.295,  1.1169,   56.4000,  1830.0000},
    {0.305,  0.8415,   48.8800,  1740.0000},
    {0.315,  0.5567,   41.3500,  1570.0000},
    {0.325,  0.2593,   33.5300,  1420.0000},
    {0.335,  0.1706,   21.0800,  1030.0000},
    {0.345,  0.0000,    8.5700,   296.0000},
    {0.355,  0.0000,    4.4740,   155.0000},
    {0.365,  0.0000,    2.4340,    53.0000},
    {0.375,  0.0000,    1.3010,    35.7000},
    {0.385,  0.0000,    0.6440,    10.9000},
    {0.395,  0.0000,    0.2818,     0.1800},
    {0.405,  0.0000,    5.12E-2,   -1.0E-3},
    {0.415,  0.0000,    1.45987E-5,-0.1950},
    {0.425,  0.0000,    4.66279E-5,-0.0090},
    {0.435,  0.0000,    0.0000,    -0.0010},
    {0.445,  0.0000,    0.0000,     0.0000}
};

// C-parameter [Bins, LO, NLO, NNLO]
std::vector<std::array<double,4>> Theory_CPR = {
    {0.005, 35.3270, -2151.0000, 30600.0000},
    {0.015, 27.9630,  -475.1000, -30400.0000},
    {0.025, 25.1240,  -145.1000, -21500.0000},
    {0.035, 23.2690,    13.0000, -14800.0000},
    {0.045, 21.8870,   109.1000, -11200.0000},
    {0.055, 20.7740,   171.0000,  -7600.0000},
    {0.065, 19.8310,   215.0000,  -5300.0000},
    {0.075, 19.0420,   244.0000,  -2700.0000},
    {0.085, 18.3400,   267.0000,  -1500.0000},
    {0.095, 17.7100,   283.0000,   -750.0000},
    {0.105, 17.1520,   295.0000,   1600.0000},
    {0.115, 16.6370,   306.0000,   1400.0000},
    {0.125, 16.1540,   310.0000,   1700.0000},
    {0.135, 15.7130,   318.0000,   3300.0000},
    {0.145, 15.3120,   321.0000,   3600.0000},
    {0.155, 14.9330,   323.0000,   4300.0000},
    {0.165, 14.5720,   324.0000,   4200.0000},
    {0.175, 14.2280,   326.0000,   4800.0000},
    {0.185, 13.9150,   324.1000,   5400.0000},
    {0.195, 13.6090,   322.7000,   4400.0000},
    {0.205, 13.3210,   324.2000,   5500.0000},
    {0.215, 13.0390,   321.4000,   5800.0000},
    {0.225, 12.7790,   320.8000,   5900.0000},
    {0.235, 12.5240,   318.4000,   6200.0000},
    {0.245, 12.2810,   317.9000,   6700.0000},
    {0.255, 12.0460,   315.6000,   6300.0000},
    {0.265, 11.8230,   311.3000,   6200.0000},
    {0.275, 11.6080,   307.9000,   6600.0000},
    {0.285, 11.3920,   307.8000,   5900.0000},
    {0.295, 11.1970,   302.9000,   6800.0000},
    {0.305, 11.0000,   300.8000,   6500.0000},
    {0.315, 10.8120,   298.0000,   6800.0000},
    {0.325, 10.6270,   296.4000,   6500.0000},
    {0.335, 10.4510,   290.8000,   6300.0000},
    {0.345, 10.2730,   289.7000,   6100.0000},
    {0.355, 10.1100,   285.6000,   6200.0000},
    {0.365,  9.9460,   284.3000,   6400.0000},
    {0.375,  9.7870,   280.4000,   7000.0000},
    {0.385,  9.6280,   275.2000,   6500.0000},
    {0.395,  9.4840,   273.2000,   6100.0000},
    {0.405,  9.3321,   271.1000,   6200.0000},
    {0.415,  9.1900,   268.5000,   7000.0000},
    {0.425,  9.0490,   263.6000,   5800.0000},
    {0.435,  8.9140,   261.6000,   6100.0000},
    {0.445,  8.7791,   258.0000,   6200.0000},
    {0.455,  8.6450,   255.5000,   6000.0000},
    {0.465,  8.5180,   251.8000,   6500.0000},
    {0.475,  8.3920,   249.1000,   5600.0000},
    {0.485,  8.2690,   246.5000,   5900.0000},
    {0.495,  8.1520,   241.5000,   5800.0000},
    {0.505,  8.0330,   241.7000,   5800.0000},
    {0.515,  7.9180,   237.6000,   5500.0000},
    {0.525,  7.8040,   232.6000,   6100.0000},
    {0.535,  7.6910,   231.2000,   5000.0000},
    {0.545,  7.5890,   228.5000,   5500.0000},
    {0.555,  7.4760,   224.7000,   5700.0000},
    {0.565,  7.3770,   224.7000,   5700.0000},
    {0.575,  7.2710,   219.0000,   5600.0000},
    {0.585,  7.1720,   218.0000,   5400.0000},
    {0.595,  7.0730,   214.3000,   5200.0000},
    {0.605,  6.9760,   210.5000,   4900.0000},
    {0.615,  6.8800,   208.4000,   5200.0000},
    {0.625,  6.7880,   204.6000,   4600.0000},
    {0.635,  6.6920,   202.5000,   5100.0000},
    {0.645,  6.6000,   200.9000,   5100.0000},
    {0.655,  6.5150,   197.7000,   4400.0000},
    {0.665,  6.4260,   194.7000,   5000.0000},
    {0.675,  6.3370,   192.4000,   4700.0000},
    {0.685,  6.2530,   189.2000,   5100.0000},
    {0.695,  6.1710,   187.7000,   4500.0000},
    {0.705,  6.0874,   184.0000,   4300.0000},
    {0.715,  6.0103,   182.6000,   3900.0000},
    {0.725,  5.9266,   180.0000,   4400.0000},
    {0.735,  5.8474,   177.5000,   4300.0000},
    {0.745,  5.7695,   174.5000,   3200.0000},
    {0.755,  0.0000,   601.1000,  12700.0000},
    {0.765,  0.0000,   277.1000,  13800.0000},
    {0.775,  0.0000,   190.5000,   9990.0000},
    {0.785,  0.0000,   142.4600,   7600.0000},
    {0.795,  0.0000,   111.2400,   6170.0000},
    {0.805,  0.0000,    88.9500,   4650.0000},
    {0.815,  0.0000,    72.2800,   3490.0000},
    {0.825,  0.0000,    59.1300,   3020.0000},
    {0.835,  0.0000,    48.7600,   1930.0000},
    {0.845,  0.0000,    40.3700,   1930.0000},
    {0.855,  0.0000,    33.3600,    820.0000},
    {0.865,  0.0000,    27.5400,   1260.0000},
    {0.875,  0.0000,    22.7000,    940.0000},
    {0.885,  0.0000,    18.5600,    680.0000},
    {0.895,  0.0000,    15.0600,    590.0000},
    {0.905,  0.0000,    12.1200,    457.0000},
    {0.915,  0.0000,     9.5870,    350.0000},
    {0.925,  0.0000,     7.4580,    219.0000},
    {0.935,  0.0000,     5.6450,     10.0000},
    {0.945,  0.0000,     4.1250,    101.9000},
    {0.955,  0.0000,     2.8750,     25.9000},
    {0.965,  0.0000,     1.8350,     22.6000},
    {0.975,  0.0000,     1.0080,      3.9000},
    {0.985,  0.0000,     0.3990,     -0.4886},
    {0.995,  0.0000,     0.0188,     -0.1443}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fit functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double Nc = 3.0; double Nf = 5.0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double THR_NNLO(double *x, double *par) {
   
	double tau   = x[0];
    double alphaS = par[0];
    double asbar  = alphaS / (2 * TMath::Pi());

    // unbarred
    double At = 3.0*(Nc*Nc-1.0)/(4.0*Nc);
    double Bt = (Nc*Nc-1.0)/(8.0*Nc) * ( (243.0/4.0 - 44.0*1.202)*Nc + 3.0/(4.0*Nc) + (8.0*1.202 - 11.0)*Nf );

	// Run through bins
    for (const auto &row : Theory_THR) {
        
		// bin vector
		double bin = row[0];
        
		// Check proximity
		if (std::fabs(tau - bin) < 0.005) {

			// extract
			double A = row[1], B = row[2], C = row[3];
			
			// barred
            double AA = A;
            double BB = B - At*A;
            double CC = C - At*B - (Bt - At*At)*A;

			// construct
            double val = asbar*AA + asbar*asbar*BB + asbar*asbar*asbar*CC;

			// normalise
			return val / bin;
        }
    }
    return 0.0;
}

double CPR_NNLO(double *x, double *par) {
   
	double tau   = x[0];
    double alphaS = par[0];
    double asbar  = alphaS / (2 * TMath::Pi());

    // unbarred
    double At = 3.0*(Nc*Nc-1.0)/(4.0*Nc);
    double Bt = (Nc*Nc-1.0)/(8.0*Nc) * ( (243.0/4.0 - 44.0*1.202)*Nc + 3.0/(4.0*Nc) + (8.0*1.202 - 11.0)*Nf );

	// Run through bins
    for (const auto &row : Theory_CPR) {
        
		// bin vector
		double bin = row[0];
        
		// Check proximity
		if (std::fabs(tau - bin) < 0.005) {

			// extract
			double A = row[1], B = row[2], C = row[3];
			
			// barred
            double AA = A;
            double BB = B - At*A;
            double CC = C - At*B - (Bt - At*At)*A;

			// construct
            double val = asbar*AA + asbar*asbar*BB + asbar*asbar*asbar*CC;

			// normalise
			return val / bin;
        }
    }
    return 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Code
void ImpactofAlpha()
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1::SetDefaultSumw2(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading roots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_EXPDATA = TFile::Open("3-LEPdata/EXPDATA.root");

	TFile *input_912_wiHadron = new TFile("5-CutData/cut_FCC912.root", "READ");
	TFile *input_160_wiHadron = new TFile("5-CutData/cut_FCC160.root", "READ");
	TFile *input_240_wiHadron = new TFile("5-CutData/cut_FCC240.root", "READ");
	TFile *input_365_wiHadron = new TFile("5-CutData/cut_FCC365.root", "READ");

	TFile *input_912_woHadron = new TFile("5-CutData/cut_FCC912_woHadron.root", "READ");
	TFile *input_160_woHadron = new TFile("5-CutData/cut_FCC160_woHadron.root", "READ");
	TFile *input_240_woHadron = new TFile("5-CutData/cut_FCC240_woHadron.root", "READ");
	TFile *input_365_woHadron = new TFile("5-CutData/cut_FCC365_woHadron.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TGraphAsymmErrors* grph_ThrALPH_912_wiHadron = (TGraphAsymmErrors*)input_EXPDATA->Get("grph_EXP_ALP_912_THR");
	TGraphAsymmErrors* grph_CprALPH_912_wiHadron = (TGraphAsymmErrors*)input_EXPDATA->Get("grph_EXP_ALP_912_CPR");

	TH1F* hist_ThrALPH_912_wiHadron = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_912_THR");
	TH1F* hist_CprALPH_912_wiHadron = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_912_CPR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_912_wiHadron = (TH1F*)input_912_wiHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_912_wiHadron->SetLineColor(kBlack); hist_ThrPyth_912_wiHadron->SetMarkerColor(kBlack); hist_ThrPyth_912_wiHadron->SetMarkerStyle(26); hist_ThrPyth_912_wiHadron->SetLineWidth(2); hist_ThrPyth_912_wiHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_160_wiHadron = (TH1F*)input_160_wiHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_160_wiHadron->SetLineColor(kBlack); hist_ThrPyth_160_wiHadron->SetMarkerColor(kBlack); hist_ThrPyth_160_wiHadron->SetMarkerStyle(26); hist_ThrPyth_160_wiHadron->SetLineWidth(2); hist_ThrPyth_160_wiHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_240_wiHadron = (TH1F*)input_240_wiHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_240_wiHadron->SetLineColor(kBlack); hist_ThrPyth_240_wiHadron->SetMarkerColor(kBlack); hist_ThrPyth_240_wiHadron->SetMarkerStyle(26); hist_ThrPyth_240_wiHadron->SetLineWidth(2); hist_ThrPyth_240_wiHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_365_wiHadron = (TH1F*)input_365_wiHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_365_wiHadron->SetLineColor(kBlack); hist_ThrPyth_365_wiHadron->SetMarkerColor(kBlack); hist_ThrPyth_365_wiHadron->SetMarkerStyle(26); hist_ThrPyth_365_wiHadron->SetLineWidth(2); hist_ThrPyth_365_wiHadron->SetMarkerSize(1);

	TH1F *hist_CprPyth_912_wiHadron = (TH1F*)input_912_wiHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_912_wiHadron->SetLineColor(kBlack); hist_CprPyth_912_wiHadron->SetMarkerColor(kBlack); hist_CprPyth_912_wiHadron->SetMarkerStyle(26); hist_CprPyth_912_wiHadron->SetLineWidth(2); hist_CprPyth_912_wiHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_160_wiHadron = (TH1F*)input_160_wiHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_160_wiHadron->SetLineColor(kBlack); hist_CprPyth_160_wiHadron->SetMarkerColor(kBlack); hist_CprPyth_160_wiHadron->SetMarkerStyle(26); hist_CprPyth_160_wiHadron->SetLineWidth(2); hist_CprPyth_160_wiHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_240_wiHadron = (TH1F*)input_240_wiHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_240_wiHadron->SetLineColor(kBlack); hist_CprPyth_240_wiHadron->SetMarkerColor(kBlack); hist_CprPyth_240_wiHadron->SetMarkerStyle(26); hist_CprPyth_240_wiHadron->SetLineWidth(2); hist_CprPyth_240_wiHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_365_wiHadron = (TH1F*)input_365_wiHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_365_wiHadron->SetLineColor(kBlack); hist_CprPyth_365_wiHadron->SetMarkerColor(kBlack); hist_CprPyth_365_wiHadron->SetMarkerStyle(26); hist_CprPyth_365_wiHadron->SetLineWidth(2); hist_CprPyth_365_wiHadron->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_912_woHadron = (TH1F*)input_912_woHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_912_woHadron->SetLineColor(kBlack); hist_ThrPyth_912_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_912_woHadron->SetMarkerStyle(26); hist_ThrPyth_912_woHadron->SetLineWidth(2); hist_ThrPyth_912_woHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_160_woHadron = (TH1F*)input_160_woHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_160_woHadron->SetLineColor(kBlack); hist_ThrPyth_160_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_160_woHadron->SetMarkerStyle(26); hist_ThrPyth_160_woHadron->SetLineWidth(2); hist_ThrPyth_160_woHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_240_woHadron = (TH1F*)input_240_woHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_240_woHadron->SetLineColor(kBlack); hist_ThrPyth_240_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_240_woHadron->SetMarkerStyle(26); hist_ThrPyth_240_woHadron->SetLineWidth(2); hist_ThrPyth_240_woHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_365_woHadron = (TH1F*)input_365_woHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_365_woHadron->SetLineColor(kBlack); hist_ThrPyth_365_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_365_woHadron->SetMarkerStyle(26); hist_ThrPyth_365_woHadron->SetLineWidth(2); hist_ThrPyth_365_woHadron->SetMarkerSize(1);

	TH1F *hist_CprPyth_912_woHadron = (TH1F*)input_912_woHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_912_woHadron->SetLineColor(kBlack); hist_CprPyth_912_woHadron->SetMarkerColor(kBlack); hist_CprPyth_912_woHadron->SetMarkerStyle(26); hist_CprPyth_912_woHadron->SetLineWidth(2); hist_CprPyth_912_woHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_160_woHadron = (TH1F*)input_160_woHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_160_woHadron->SetLineColor(kBlack); hist_CprPyth_160_woHadron->SetMarkerColor(kBlack); hist_CprPyth_160_woHadron->SetMarkerStyle(26); hist_CprPyth_160_woHadron->SetLineWidth(2); hist_CprPyth_160_woHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_240_woHadron = (TH1F*)input_240_woHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_240_woHadron->SetLineColor(kBlack); hist_CprPyth_240_woHadron->SetMarkerColor(kBlack); hist_CprPyth_240_woHadron->SetMarkerStyle(26); hist_CprPyth_240_woHadron->SetLineWidth(2); hist_CprPyth_240_woHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_365_woHadron = (TH1F*)input_365_woHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_365_woHadron->SetLineColor(kBlack); hist_CprPyth_365_woHadron->SetMarkerColor(kBlack); hist_CprPyth_365_woHadron->SetMarkerStyle(26); hist_CprPyth_365_woHadron->SetLineWidth(2); hist_CprPyth_365_woHadron->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising to (1/N)(dN/dO)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	hist_ThrPyth_912_woHadron->Scale(1.0/hist_ThrPyth_912_woHadron->Integral("width"));
	hist_ThrPyth_160_woHadron->Scale(1.0/hist_ThrPyth_160_woHadron->Integral("width"));
	hist_ThrPyth_240_woHadron->Scale(1.0/hist_ThrPyth_240_woHadron->Integral("width"));
	hist_ThrPyth_365_woHadron->Scale(1.0/hist_ThrPyth_365_woHadron->Integral("width"));

	hist_CprPyth_912_woHadron->Scale(1.0/hist_CprPyth_912_woHadron->Integral("width"));
	hist_CprPyth_160_woHadron->Scale(1.0/hist_CprPyth_160_woHadron->Integral("width"));
	hist_CprPyth_240_woHadron->Scale(1.0/hist_CprPyth_240_woHadron->Integral("width"));
	hist_CprPyth_365_woHadron->Scale(1.0/hist_CprPyth_365_woHadron->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912_wiHadron->Scale(1.0/hist_ThrPyth_912_wiHadron->Integral("width"));	
	hist_ThrPyth_160_wiHadron->Scale(1.0/hist_ThrPyth_160_wiHadron->Integral("width"));
	hist_ThrPyth_240_wiHadron->Scale(1.0/hist_ThrPyth_240_wiHadron->Integral("width"));
	hist_ThrPyth_365_wiHadron->Scale(1.0/hist_ThrPyth_365_wiHadron->Integral("width"));

	hist_CprPyth_912_wiHadron->Scale(1.0/hist_CprPyth_912_wiHadron->Integral("width"));
	hist_CprPyth_160_wiHadron->Scale(1.0/hist_CprPyth_160_wiHadron->Integral("width"));
	hist_CprPyth_240_wiHadron->Scale(1.0/hist_CprPyth_240_wiHadron->Integral("width"));
	hist_CprPyth_365_wiHadron->Scale(1.0/hist_CprPyth_365_wiHadron->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TGraphAsymmErrors* grph_ThrPyth_912_wiHadron = HistToGraph(hist_ThrPyth_912_wiHadron, true);

	TGraphAsymmErrors* grph_ThrPyth_912_woHadron = HistToGraph(hist_ThrPyth_912_woHadron, true);

	TGraphAsymmErrors* grph_CprPyth_912_woHadron = HistToGraph(hist_CprPyth_912_woHadron, true);
	grph_CprPyth_912_woHadron->SetLineColor(kBlack); grph_CprPyth_912_woHadron->SetMarkerColor(kBlack); grph_CprPyth_912_woHadron->SetLineWidth(2); grph_CprPyth_912_woHadron->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hadronic correction factors
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Read histos binned to exp data
	TH1F *hist_ThrPyth_912_wiHadron_Correction = (TH1F*)input_912_wiHadron->Get("hist_ThrPyth_EXP");
	TH1F *hist_ThrPyth_912_woHadron_Correction = (TH1F*)input_912_woHadron->Get("hist_ThrPyth_EXP");
	TH1F *hist_CprPyth_912_wiHadron_Correction = (TH1F*)input_912_wiHadron->Get("hist_CprPyth_EXP");
	TH1F *hist_CprPyth_912_woHadron_Correction = (TH1F*)input_912_woHadron->Get("hist_CprPyth_EXP");

	// Normalise
	hist_ThrPyth_912_wiHadron_Correction->Scale(1.0/hist_ThrPyth_912_wiHadron_Correction->Integral("width"));
	hist_ThrPyth_912_woHadron_Correction->Scale(1.0/hist_ThrPyth_912_woHadron_Correction->Integral("width"));
	hist_CprPyth_912_wiHadron_Correction->Scale(1.0/hist_CprPyth_912_wiHadron_Correction->Integral("width"));
	hist_CprPyth_912_woHadron_Correction->Scale(1.0/hist_CprPyth_912_woHadron_Correction->Integral("width"));

	// Compute corrections
	TH1F *hist_ThrCorr_912 = (TH1F*)hist_ThrPyth_912_woHadron_Correction->Clone("hist_ThrCorr_912");
	hist_ThrCorr_912->Divide(hist_ThrPyth_912_wiHadron_Correction);
	TH1F *hist_CprCorr_912 = (TH1F*)hist_CprPyth_912_woHadron_Correction->Clone("hist_ThrCorr_912");
	hist_CprCorr_912->Divide(hist_CprPyth_912_wiHadron_Correction);

	// Apply corrections
	TH1F *hist_ThrALPH_912_woHadron = (TH1F*)hist_ThrALPH_912_wiHadron->Clone("hist_ThrALPH_912_woHadron");
	
	TH1D* hist_ThrCorr_912_rebinned = (TH1D*)hist_ThrALPH_912_woHadron->Clone("hist_ThrCorr_912_rebinned");
	hist_ThrCorr_912_rebinned->Reset();

	for (int i = 1; i <= hist_ThrCorr_912_rebinned->GetNbinsX(); ++i) {
		double x = hist_ThrCorr_912_rebinned->GetXaxis()->GetBinCenter(i);
		int bin = hist_ThrCorr_912->FindBin(x);
		hist_ThrCorr_912_rebinned->SetBinContent(i, hist_ThrCorr_912->GetBinContent(bin));
		hist_ThrCorr_912_rebinned->SetBinError(i, hist_ThrCorr_912->GetBinError(bin));
	}
	
	hist_ThrALPH_912_woHadron->Multiply(hist_ThrCorr_912_rebinned);
	hist_ThrALPH_912_woHadron->SetLineColor(kBlack); hist_ThrALPH_912_woHadron->SetMarkerColor(kBlack); hist_ThrALPH_912_woHadron->SetMarkerStyle(27); hist_ThrALPH_912_woHadron->SetLineWidth(2); hist_ThrALPH_912_woHadron->SetMarkerSize(1);

	TGraphAsymmErrors* grph_ThrALPH_912_woHadron = HistToGraph(hist_ThrALPH_912_woHadron, true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fit PYTHIA to Theory
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float AlpFit_912_min = 0.09, AlpFit_912_max = 0.25, CprFit_912_min = 0.36, CprFit_912_max = 0.74;
	float AlpFit_160_min = 0.09, AlpFit_160_max = 0.25, CprFit_160_min = 0.36, CprFit_160_max = 0.74;
	float AlpFit_240_min = 0.09, AlpFit_240_max = 0.25, CprFit_240_min = 0.36, CprFit_240_max = 0.74;
	float AlpFit_365_min = 0.09, AlpFit_365_max = 0.25, CprFit_365_min = 0.36, CprFit_365_max = 0.74;

	TF1 *hist_fitThNN_912 = new TF1("hist_fitThNN_912", THR_NNLO, 0.09, 0.25, 1);
	hist_fitThNN_912->SetLineColor(kBlue+1); hist_fitThNN_912->SetMarkerColor(kBlue+1); hist_fitThNN_912->SetMarkerStyle(53); hist_fitThNN_912->SetLineWidth(2); hist_fitThNN_912->SetMarkerSize(1);
	TF1 *hist_fitThNN_91X = new TF1("hist_fitThNN_91X", THR_NNLO, AlpFit_912_min, AlpFit_912_max, 1);
	hist_fitThNN_91X->SetLineColor(kRed+2); hist_fitThNN_91X->SetMarkerColor(kRed+2); hist_fitThNN_91X->SetMarkerStyle(53); hist_fitThNN_91X->SetLineWidth(2); hist_fitThNN_91X->SetMarkerSize(1);

	TF1 *hist_fitThNN_160 = new TF1("hist_fitThNN_160", THR_NNLO, AlpFit_160_min, AlpFit_160_max, 1);
	hist_fitThNN_160->SetLineColor(kBlue+1); hist_fitThNN_160->SetMarkerColor(kBlue+1); hist_fitThNN_160->SetMarkerStyle(53); hist_fitThNN_160->SetLineWidth(2); hist_fitThNN_160->SetMarkerSize(1);
	TF1 *hist_fitThNN_240 = new TF1("hist_fitThNN_240", THR_NNLO, AlpFit_240_min, AlpFit_240_max, 1);
	hist_fitThNN_240->SetLineColor(kBlue+1); hist_fitThNN_240->SetMarkerColor(kBlue+1); hist_fitThNN_240->SetMarkerStyle(53); hist_fitThNN_240->SetLineWidth(2); hist_fitThNN_240->SetMarkerSize(1);
	TF1 *hist_fitThNN_365 = new TF1("hist_fitThNN_365", THR_NNLO, AlpFit_365_min, AlpFit_365_max, 1);
	hist_fitThNN_365->SetLineColor(kBlue+1); hist_fitThNN_365->SetMarkerColor(kBlue+1); hist_fitThNN_365->SetMarkerStyle(53); hist_fitThNN_365->SetLineWidth(2); hist_fitThNN_365->SetMarkerSize(1);

	TF1 *hist_fitCpNN_912 = new TF1("hist_fitCpNN_912", CPR_NNLO, CprFit_912_min, CprFit_912_max, 1);
	hist_fitCpNN_912->SetLineColor(kBlue+1); hist_fitCpNN_912->SetMarkerColor(kBlue+1); hist_fitCpNN_912->SetMarkerStyle(53); hist_fitCpNN_912->SetLineWidth(2); hist_fitCpNN_912->SetMarkerSize(1);
	TF1 *hist_fitCpNN_91X = new TF1("hist_fitCpNN_91X", CPR_NNLO, CprFit_912_min, CprFit_912_max, 1);
	hist_fitCpNN_91X->SetLineColor(kRed+2); hist_fitCpNN_91X->SetMarkerColor(kRed+2); hist_fitCpNN_91X->SetMarkerStyle(53); hist_fitCpNN_91X->SetLineWidth(2); hist_fitCpNN_91X->SetMarkerSize(1);

	TF1 *hist_fitCpNN_160 = new TF1("hist_fitCpNN_160", CPR_NNLO, CprFit_160_min, CprFit_160_max, 1);
	hist_fitCpNN_160->SetLineColor(kBlue+1); hist_fitCpNN_160->SetMarkerColor(kBlue+1); hist_fitCpNN_160->SetMarkerStyle(53); hist_fitCpNN_160->SetLineWidth(2); hist_fitCpNN_160->SetMarkerSize(1);
	TF1 *hist_fitCpNN_240 = new TF1("hist_fitCpNN_240", CPR_NNLO, CprFit_240_min, CprFit_240_max, 1);
	hist_fitCpNN_240->SetLineColor(kBlue+1); hist_fitCpNN_240->SetMarkerColor(kBlue+1); hist_fitCpNN_240->SetMarkerStyle(53); hist_fitCpNN_240->SetLineWidth(2); hist_fitCpNN_240->SetMarkerSize(1);
	TF1 *hist_fitCpNN_365 = new TF1("hist_fitCpNN_365", CPR_NNLO, CprFit_365_min, CprFit_365_max, 1);
	hist_fitCpNN_365->SetLineColor(kBlue+1); hist_fitCpNN_365->SetMarkerColor(kBlue+1); hist_fitCpNN_365->SetMarkerStyle(53); hist_fitCpNN_365->SetLineWidth(2); hist_fitCpNN_365->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	float guess = 0.1, guess_min = 0.01, guess_max = 1.0;

	hist_fitThNN_912->SetParameter(0, guess); hist_fitThNN_912->SetParLimits(0, guess_min, guess_max);
	hist_fitThNN_91X->SetParameter(0, guess); hist_fitThNN_91X->SetParLimits(0, guess_min, guess_max);

	hist_fitThNN_160->SetParameter(0, guess); hist_fitThNN_160->SetParLimits(0, guess_min, guess_max);
	hist_fitThNN_240->SetParameter(0, guess); hist_fitThNN_240->SetParLimits(0, guess_min, guess_max);
	hist_fitThNN_365->SetParameter(0, guess); hist_fitThNN_365->SetParLimits(0, guess_min, guess_max);
	
	hist_fitCpNN_912->SetParameter(0, guess); hist_fitCpNN_912->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNN_91X->SetParameter(0, guess); hist_fitCpNN_91X->SetParLimits(0, guess_min, guess_max);

	hist_fitCpNN_160->SetParameter(0, guess); hist_fitCpNN_160->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNN_240->SetParameter(0, guess); hist_fitCpNN_240->SetParLimits(0, guess_min, guess_max);
	hist_fitCpNN_365->SetParameter(0, guess); hist_fitCpNN_365->SetParLimits(0, guess_min, guess_max);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912_woHadron->Fit(hist_fitThNN_912, "RNQ MINOS");
	hist_ThrALPH_912_wiHadron->Fit(hist_fitThNN_91X, "RNQ MINOS");

	hist_ThrPyth_160_woHadron->Fit(hist_fitThNN_160, "RNQ MINOS");
	hist_ThrPyth_240_woHadron->Fit(hist_fitThNN_240, "RNQ MINOS");
	hist_ThrPyth_365_woHadron->Fit(hist_fitThNN_365, "RNQ MINOS");
	
	hist_CprPyth_912_woHadron->Fit(hist_fitCpNN_912, "RNQ MINOS");
	hist_CprALPH_912_wiHadron->Fit(hist_fitCpNN_91X, "RNQ MINOS");

	hist_CprPyth_160_woHadron->Fit(hist_fitCpNN_160, "RNQ MINOS");
	hist_CprPyth_240_woHadron->Fit(hist_fitCpNN_240, "RNQ MINOS");
	hist_CprPyth_365_woHadron->Fit(hist_fitCpNN_365, "RNQ MINOS");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// grph_ThrALPH_912_wiHadron->GetXaxis()->SetLabelSize(0.06);
	// grph_ThrALPH_912_wiHadron->GetXaxis()->SetTitleSize(0.06);
	// grph_ThrALPH_912_wiHadron->GetYaxis()->SetLabelSize(0.06);
	// grph_ThrALPH_912_wiHadron->GetYaxis()->SetTitleSize(0.06);

	// hist_ThrPyth_912->GetXaxis()->SetLabelSize(0.06);
	// hist_ThrPyth_912->GetXaxis()->SetTitleSize(0.06);
	// hist_ThrPyth_912->GetYaxis()->SetLabelSize(0.06);
	// hist_ThrPyth_912->GetYaxis()->SetTitleSize(0.06);

	// hist_ThrPyth_160->GetXaxis()->SetLabelSize(0.06);
	// hist_ThrPyth_160->GetXaxis()->SetTitleSize(0.06);
	// hist_ThrPyth_160->GetYaxis()->SetLabelSize(0.06);
	// hist_ThrPyth_160->GetYaxis()->SetTitleSize(0.06);

	// hist_ThrPyth_240->GetXaxis()->SetLabelSize(0.06);
	// hist_ThrPyth_240->GetXaxis()->SetTitleSize(0.06);
	// hist_ThrPyth_240->GetYaxis()->SetLabelSize(0.06);
	// hist_ThrPyth_240->GetYaxis()->SetTitleSize(0.06);

	// hist_ThrPyth_365->GetXaxis()->SetLabelSize(0.06);
	// hist_ThrPyth_365->GetXaxis()->SetTitleSize(0.06);
	// hist_ThrPyth_365->GetYaxis()->SetLabelSize(0.06);
	// hist_ThrPyth_365->GetYaxis()->SetTitleSize(0.06);

	// grph_CprALPH_912_wiHadron->GetXaxis()->SetLabelSize(0.06);
	// grph_CprALPH_912_wiHadron->GetXaxis()->SetTitleSize(0.06);
	// grph_CprALPH_912_wiHadron->GetYaxis()->SetLabelSize(0.06);
	// grph_CprALPH_912_wiHadron->GetYaxis()->SetTitleSize(0.06);

	// hist_CprPyth_912->GetXaxis()->SetLabelSize(0.06);
	// hist_CprPyth_912->GetXaxis()->SetTitleSize(0.06);
	// hist_CprPyth_912->GetYaxis()->SetLabelSize(0.06);
	// hist_CprPyth_912->GetYaxis()->SetTitleSize(0.06);

	// hist_CprPyth_160->GetXaxis()->SetLabelSize(0.06);
	// hist_CprPyth_160->GetXaxis()->SetTitleSize(0.06);
	// hist_CprPyth_160->GetYaxis()->SetLabelSize(0.06);
	// hist_CprPyth_160->GetYaxis()->SetTitleSize(0.06);

	// hist_CprPyth_240->GetXaxis()->SetLabelSize(0.06);
	// hist_CprPyth_240->GetXaxis()->SetTitleSize(0.06);
	// hist_CprPyth_240->GetYaxis()->SetLabelSize(0.06);
	// hist_CprPyth_240->GetYaxis()->SetTitleSize(0.06);

	// hist_CprPyth_365->GetXaxis()->SetLabelSize(0.06);
	// hist_CprPyth_365->GetXaxis()->SetTitleSize(0.06);
	// hist_CprPyth_365->GetYaxis()->SetLabelSize(0.06);
	// hist_CprPyth_365->GetYaxis()->SetTitleSize(0.06);

	// grph_ThrALPH_912_wiHadron->SetTitle("");
	// grph_CprALPH_912_wiHadron->SetTitle("");
	// hist_ThrPyth_912->SetTitle("");
	// hist_ThrPyth_160->SetTitle("");
	// hist_ThrPyth_240->SetTitle("");
	// hist_ThrPyth_365->SetTitle("");

	// hist_CprPyth_912->SetTitle("");
	// hist_CprPyth_160->SetTitle("");
	// hist_CprPyth_240->SetTitle("");
	// hist_CprPyth_365->SetTitle("");

	// hist_ThrPyth_912_woHadron->SetStats(kFALSE);
	// hist_ThrPyth_160_woHadron->SetStats(kFALSE);
	// hist_ThrPyth_240_woHadron->SetStats(kFALSE);
	// hist_ThrPyth_365_woHadron->SetStats(kFALSE);

	// hist_CprPyth_912_woHadron->SetStats(kFALSE);
	// hist_CprPyth_160_woHadron->SetStats(kFALSE);
	// hist_CprPyth_240_woHadron->SetStats(kFALSE);
	// hist_CprPyth_365_woHadron->SetStats(kFALSE);
	
	// hist_ThrPyth_912_wiHadron->SetStats(kFALSE);
	// hist_ThrPyth_160_wiHadron->SetStats(kFALSE);
	// hist_ThrPyth_240_wiHadron->SetStats(kFALSE);
	// hist_ThrPyth_365_wiHadron->SetStats(kFALSE);

	// hist_CprPyth_912_wiHadron->SetStats(kFALSE);
	// hist_CprPyth_160_wiHadron->SetStats(kFALSE);
	// hist_CprPyth_240_wiHadron->SetStats(kFALSE);
	// hist_CprPyth_365_wiHadron->SetStats(kFALSE);

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
	// hist_fitThNN_912->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(5);
	// hist_ThrPyth_160->Draw("HIST");
	// hist_fitThNN_160->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(3);
	// hist_ThrPyth_240->Draw("HIST");
	// hist_fitThNN_240->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(1);
	// hist_ThrPyth_365->Draw("HIST");
	// hist_fitThNN_365->Draw("HIST SAME");
	// lg->Draw("SAME");

	// cv1->cd(8);
	// hist_CprPyth_912->Draw("HIST");
	// hist_fitCpNN_912->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(6);
	// hist_CprPyth_160->Draw("HIST");
	// hist_fitCpNN_160->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(4);
	// hist_CprPyth_240->Draw("HIST");
	// hist_fitCpNN_240->Draw("HIST SAME");
	// lg->Draw("SAME");
	// cv1->cd(2);
	// hist_CprPyth_365->Draw("HIST");
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

	// // Create canvas
	// TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 2000, 1200);

	// TLegend* lg2 = new TLegend(0.54, 0.69, 0.92, 0.93);
	// // lg2->AddEntry(grph_ThrALPH_912_wiHadron, "ALEPH data", "PL");
	// // lg2->AddEntry(hist_fitThNN_91X, "ALEPH fits", "PL");
	// // lg2->AddEntry(grph_ThrPyth_912_woHadron, "PYTHIA data", "PL");
	// // lg2->AddEntry(hist_fitThNN_912, "PYTHIA fits", "PL");
	// lg2->AddEntry(hist_ThrALPH_912_wiHadron, "ALEPH-hadron", "PL");
	// lg2->AddEntry(hist_ThrALPH_912_woHadron, "ALEPH-parton", "PL");
	// lg2->AddEntry(hist_ThrPyth_912_wiHadron, "PYTHIA-hadron", "PL");
	// lg2->AddEntry(hist_ThrPyth_912_woHadron, "PYTHIA-parton", "PL");
	// lg2->SetTextSize(0.05);

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv2->SetMargin(0, 0, 0, 0); 
	// cv2->Divide(4,2);
	// for (int i = 1; i <= 8; i++) {
	// 	cv2->cd(i);
	// 	gPad->SetTopMargin(0.015);
	// 	gPad->SetBottomMargin(0.1);
	// 	gPad->SetLeftMargin(0.15);
	// 	gPad->SetRightMargin(0.04);
	// 	gPad->SetTickx(); gPad->SetTicky();
	// 	// gPad->SetGridx(); gPad->SetGridy();
	// 	// gPad->SetLogy();
	// }

	// hist_ThrALPH_912_wiHadron->SetLineColor(kRed+2); hist_ThrALPH_912_wiHadron->SetMarkerColor(kRed+2); hist_ThrALPH_912_wiHadron->SetLineWidth(2); hist_ThrALPH_912_wiHadron->SetMarkerStyle(26); hist_ThrALPH_912_wiHadron->SetMarkerSize(1);
	// hist_ThrALPH_912_woHadron->SetLineColor(kBlack); hist_ThrALPH_912_woHadron->SetMarkerColor(kBlack); hist_ThrALPH_912_woHadron->SetLineWidth(2); hist_ThrALPH_912_woHadron->SetMarkerStyle(26); hist_ThrALPH_912_woHadron->SetMarkerSize(1);
	// hist_ThrPyth_912_wiHadron->SetLineColor(kGreen+2); hist_ThrPyth_912_wiHadron->SetMarkerColor(kGreen+2); hist_ThrPyth_912_wiHadron->SetLineWidth(2); hist_ThrPyth_912_wiHadron->SetMarkerStyle(26); hist_ThrPyth_912_wiHadron->SetMarkerSize(1);
	// hist_ThrPyth_912_woHadron->SetLineColor(kYellow+2); hist_ThrPyth_912_woHadron->SetMarkerColor(kYellow+2); hist_ThrPyth_912_woHadron->SetLineWidth(2); hist_ThrPyth_912_woHadron->SetMarkerStyle(26); hist_ThrPyth_912_woHadron->SetMarkerSize(1);

	// // Draw
	// cv2->cd(1);
	// hist_ThrALPH_912_wiHadron->Draw("HIST");
	// hist_ThrALPH_912_woHadron->Draw("HIST SAME");
	// hist_ThrPyth_912_wiHadron->Draw("HIST SAME");
	// hist_ThrPyth_912_woHadron->Draw("HIST SAME");
	// lg2->Draw("SAME");
	// cv2->cd(2);
	// hist_fitThNN_91X->Draw();	
	// hist_fitThNN_912->Draw("SAME");
	// cv2->cd(3);
	// grph_ThrALPH_912_wiHadron->Draw();	
	// hist_fitThNN_91X->Draw("SAME");
	// cv2->cd(4);
	// grph_ThrPyth_912_woHadron->Draw();
	// hist_fitThNN_912->Draw("SAME");

	// Draw
	// cv2->cd(5);
	// grph_CprALPH_912_wiHadron->Draw();
	// grph_CprPyth_912_woHadron->Draw("SAME");
	// lg2->Draw("SAME");
	// cv2->cd(6);
	// hist_fitCpNN_91X->Draw();	
	// hist_fitCpNN_912->Draw("SAME");
	// cv2->cd(7);
	// grph_CprALPH_912_wiHadron->Draw();	
	// hist_fitCpNN_91X->Draw("SAME");
	// cv2->cd(8);
	// grph_CprPyth_912_woHadron->Draw();
	// hist_fitCpNN_912->Draw("SAME");

	// Set limits
	// hist_ThrALPH_912_wiHadron->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_ThrALPH_912_wiHadron->GetYaxis()->SetRangeUser(0,4);
	// hist_ThrALPH_912_wiHadron->GetXaxis()->SetRangeUser(0.09,0.25);

	// grph_ThrPyth_912_woHadron->GetYaxis()->SetRangeUser(1E-4,1E2);
	// grph_ThrPyth_912_woHadron->GetYaxis()->SetRangeUser(0,4);
	// grph_ThrPyth_912_woHadron->GetXaxis()->SetRangeUser(0.09,0.25);
	// hist_fitThNN_91X->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_fitThNN_91X->GetYaxis()->SetRangeUser(0,4);
	// hist_fitThNN_91X->GetXaxis()->SetRangeUser(0.09,0.25);
	// hist_fitThNN_912->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_fitThNN_912->GetYaxis()->SetRangeUser(0,4);
	// hist_fitThNN_912->GetXaxis()->SetRangeUser(0.09,0.25);

	// grph_CprALPH_912_wiHadron->GetYaxis()->SetRangeUser(1E-4,1E2);
	// grph_CprALPH_912_wiHadron->GetYaxis()->SetRangeUser(0,1.2);
	// grph_CprALPH_912_wiHadron->GetXaxis()->SetRangeUser(0.36,0.74);
	// grph_CprPyth_912_woHadron->GetYaxis()->SetRangeUser(1E-4,1E2);
	// grph_CprPyth_912_woHadron->GetYaxis()->SetRangeUser(0,1.2);
	// grph_CprPyth_912_woHadron->GetXaxis()->SetRangeUser(0.36,0.74);
	// hist_fitCpNN_91X->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_fitCpNN_91X->GetYaxis()->SetRangeUser(0,1.2);
	// hist_fitCpNN_91X->GetXaxis()->SetRangeUser(0.36,0.74);
	// hist_fitCpNN_912->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_fitCpNN_912->GetYaxis()->SetRangeUser(0,1.2);
	// hist_fitCpNN_912->GetXaxis()->SetRangeUser(0.36,0.74);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv2->Modified();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Print results
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << fixed << setprecision(4);

	cout << "====== FITTING WITH THRUST ======" << endl;
	cout << "√s \t χ²/ndf \t Alpha \t Fit range" << endl;
	cout << "---------------------------------" << endl;
	cout << "ALEPH \t " << hist_fitThNN_91X->GetChisquare()<<"/"<<hist_fitThNN_91X->GetNDF() << "\t" << hist_fitThNN_91X->GetParameter(0) << "\t" << AlpFit_912_min << "-" << AlpFit_912_max << endl;
	cout << "91.2 \t " << hist_fitThNN_912->GetChisquare()<<"/"<<hist_fitThNN_912->GetNDF() << "\t" << hist_fitThNN_912->GetParameter(0) << "\t" << AlpFit_912_min << "-" << AlpFit_912_max << endl;
	cout << "160 \t " << hist_fitThNN_160->GetChisquare()<<"/"<<hist_fitThNN_160->GetNDF() << "\t" << hist_fitThNN_160->GetParameter(0) << "\t" << AlpFit_160_min << "-" << AlpFit_160_max << endl;
	cout << "240 \t " << hist_fitThNN_240->GetChisquare()<<"/"<<hist_fitThNN_240->GetNDF() << "\t" << hist_fitThNN_240->GetParameter(0) << "\t" << AlpFit_240_min << "-" << AlpFit_240_max << endl;
	cout << "365 \t " << hist_fitThNN_365->GetChisquare()<<"/"<<hist_fitThNN_365->GetNDF() << "\t" << hist_fitThNN_365->GetParameter(0) << "\t" << AlpFit_365_min << "-" << AlpFit_365_max << endl;
	cout << "=================================" << endl;

	cout << "====== FITTING WITH CPARAM ======" << endl;
	cout << "√s \t χ²/ndf \t Alpha \t Fit range" << endl;
	cout << "---------------------------------" << endl;
	cout << "ALEPH \t " << hist_fitCpNN_91X->GetChisquare()<<"/"<<hist_fitCpNN_91X->GetNDF() << "\t" << hist_fitCpNN_91X->GetParameter(0) << "\t" << CprFit_912_min << "-" << CprFit_912_max << endl;
	cout << "91.2 \t " << hist_fitCpNN_912->GetChisquare()<<"/"<<hist_fitCpNN_912->GetNDF() << "\t" << hist_fitCpNN_912->GetParameter(0) << "\t" << CprFit_912_min << "-" << CprFit_912_max << endl;
	cout << "160 \t " << hist_fitCpNN_160->GetChisquare()<<"/"<<hist_fitCpNN_160->GetNDF() << "\t" << hist_fitCpNN_160->GetParameter(0) << "\t" << CprFit_160_min << "-" << CprFit_160_max << endl;
	cout << "240 \t " << hist_fitCpNN_240->GetChisquare()<<"/"<<hist_fitCpNN_240->GetNDF() << "\t" << hist_fitCpNN_240->GetParameter(0) << "\t" << CprFit_240_min << "-" << CprFit_240_max << endl;
	cout << "365 \t " << hist_fitCpNN_365->GetChisquare()<<"/"<<hist_fitCpNN_365->GetNDF() << "\t" << hist_fitCpNN_365->GetParameter(0) << "\t" << CprFit_365_min << "-" << CprFit_365_max << endl;
	cout << "=================================" << endl;

}