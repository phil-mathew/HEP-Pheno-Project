/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate plots in ROOT from TTree file produced by PyAlla
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

// 3-loop QCD running coupling αs(Q) with fixed nf=5 (MSbar scheme)
static inline double alpha3L_Lambda(double Q, double Lambda) {
    const double nf = 5.0;
    const double b0 = 11.0 - 2.0/3.0*nf;
    const double b1 = 102.0 - 38.0/3.0*nf;
    const double b2 = 2857.0/2.0 - 5033.0/18.0*nf + 325.0/54.0*nf*nf;

    const double L = std::log((Q*Q)/(Lambda*Lambda));
    const double lnL = std::log(L);

    const double pref = 4.0 * M_PI / (b0 * L);
    const double corr1 = (b1 / (b0*b0)) * (lnL / L);
    const double corr2 = ((b1*b1)*((lnL*lnL) - lnL - 1.0) + b0*b2) / (std::pow(b0,4) * L*L);

    return pref * (1.0 - corr1 + corr2);
}

// Invert αs(Q0) → Λ at 3-loop (nf=5). αs increases with Λ.
static inline double Lambda_from_alpha3L(double Q0, double as_Q0) {
    double lo = 0.01, hi = 1.0;           // GeV, safe bracket for Λ^(5)
    for (int it = 0; it < 100; ++it) {
        double mid   = 0.5 * (lo + hi);
        double a_mid = alpha3L_Lambda(Q0, mid);
        if (a_mid > as_Q0) hi = mid;      // reduce Λ to reduce αs
        else               lo = mid;      // increase Λ to increase αs
    }
    return 0.5 * (lo + hi);
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
void ImpactofAlpha() {
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1::SetDefaultSumw2(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading roots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_EXPDATA = TFile::Open("3-LEPdata/EXPDATA.root");
	TFile *input_EXP_ALP = TFile::Open("3-LEPdata/EXP_ALP.root");
	TFile *input_EXP_LL3 = TFile::Open("3-LEPdata/EXP_LL3.root");

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
	hist_ThrPyth_912_wiHadron->SetLineColor(kBlack); hist_ThrPyth_912_wiHadron->SetMarkerColor(kBlack); hist_ThrPyth_912_wiHadron->SetMarkerStyle(20); hist_ThrPyth_912_wiHadron->SetLineWidth(2); hist_ThrPyth_912_wiHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_160_wiHadron = (TH1F*)input_160_wiHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_160_wiHadron->SetLineColor(kBlack); hist_ThrPyth_160_wiHadron->SetMarkerColor(kBlack); hist_ThrPyth_160_wiHadron->SetMarkerStyle(20); hist_ThrPyth_160_wiHadron->SetLineWidth(2); hist_ThrPyth_160_wiHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_240_wiHadron = (TH1F*)input_240_wiHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_240_wiHadron->SetLineColor(kBlack); hist_ThrPyth_240_wiHadron->SetMarkerColor(kBlack); hist_ThrPyth_240_wiHadron->SetMarkerStyle(20); hist_ThrPyth_240_wiHadron->SetLineWidth(2); hist_ThrPyth_240_wiHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_365_wiHadron = (TH1F*)input_365_wiHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_365_wiHadron->SetLineColor(kBlack); hist_ThrPyth_365_wiHadron->SetMarkerColor(kBlack); hist_ThrPyth_365_wiHadron->SetMarkerStyle(20); hist_ThrPyth_365_wiHadron->SetLineWidth(2); hist_ThrPyth_365_wiHadron->SetMarkerSize(1);

	TH1F *hist_CprPyth_912_wiHadron = (TH1F*)input_912_wiHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_912_wiHadron->SetLineColor(kBlack); hist_CprPyth_912_wiHadron->SetMarkerColor(kBlack); hist_CprPyth_912_wiHadron->SetMarkerStyle(20); hist_CprPyth_912_wiHadron->SetLineWidth(2); hist_CprPyth_912_wiHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_160_wiHadron = (TH1F*)input_160_wiHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_160_wiHadron->SetLineColor(kBlack); hist_CprPyth_160_wiHadron->SetMarkerColor(kBlack); hist_CprPyth_160_wiHadron->SetMarkerStyle(20); hist_CprPyth_160_wiHadron->SetLineWidth(2); hist_CprPyth_160_wiHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_240_wiHadron = (TH1F*)input_240_wiHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_240_wiHadron->SetLineColor(kBlack); hist_CprPyth_240_wiHadron->SetMarkerColor(kBlack); hist_CprPyth_240_wiHadron->SetMarkerStyle(20); hist_CprPyth_240_wiHadron->SetLineWidth(2); hist_CprPyth_240_wiHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_365_wiHadron = (TH1F*)input_365_wiHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_365_wiHadron->SetLineColor(kBlack); hist_CprPyth_365_wiHadron->SetMarkerColor(kBlack); hist_CprPyth_365_wiHadron->SetMarkerStyle(20); hist_CprPyth_365_wiHadron->SetLineWidth(2); hist_CprPyth_365_wiHadron->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_912_woHadron = (TH1F*)input_912_woHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_912_woHadron->SetLineColor(kBlack); hist_ThrPyth_912_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_912_woHadron->SetMarkerStyle(20); hist_ThrPyth_912_woHadron->SetLineWidth(2); hist_ThrPyth_912_woHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_160_woHadron = (TH1F*)input_160_woHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_160_woHadron->SetLineColor(kBlack); hist_ThrPyth_160_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_160_woHadron->SetMarkerStyle(20); hist_ThrPyth_160_woHadron->SetLineWidth(2); hist_ThrPyth_160_woHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_240_woHadron = (TH1F*)input_240_woHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_240_woHadron->SetLineColor(kBlack); hist_ThrPyth_240_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_240_woHadron->SetMarkerStyle(20); hist_ThrPyth_240_woHadron->SetLineWidth(2); hist_ThrPyth_240_woHadron->SetMarkerSize(1);
	TH1F *hist_ThrPyth_365_woHadron = (TH1F*)input_365_woHadron->Get("hist_ThrPyth_TEO");
	hist_ThrPyth_365_woHadron->SetLineColor(kBlack); hist_ThrPyth_365_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_365_woHadron->SetMarkerStyle(20); hist_ThrPyth_365_woHadron->SetLineWidth(2); hist_ThrPyth_365_woHadron->SetMarkerSize(1);

	TH1F *hist_CprPyth_912_woHadron = (TH1F*)input_912_woHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_912_woHadron->SetLineColor(kBlack); hist_CprPyth_912_woHadron->SetMarkerColor(kBlack); hist_CprPyth_912_woHadron->SetMarkerStyle(20); hist_CprPyth_912_woHadron->SetLineWidth(2); hist_CprPyth_912_woHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_160_woHadron = (TH1F*)input_160_woHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_160_woHadron->SetLineColor(kBlack); hist_CprPyth_160_woHadron->SetMarkerColor(kBlack); hist_CprPyth_160_woHadron->SetMarkerStyle(20); hist_CprPyth_160_woHadron->SetLineWidth(2); hist_CprPyth_160_woHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_240_woHadron = (TH1F*)input_240_woHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_240_woHadron->SetLineColor(kBlack); hist_CprPyth_240_woHadron->SetMarkerColor(kBlack); hist_CprPyth_240_woHadron->SetMarkerStyle(20); hist_CprPyth_240_woHadron->SetLineWidth(2); hist_CprPyth_240_woHadron->SetMarkerSize(1);
	TH1F *hist_CprPyth_365_woHadron = (TH1F*)input_365_woHadron->Get("hist_CprPyth_TEO");
	hist_CprPyth_365_woHadron->SetLineColor(kBlack); hist_CprPyth_365_woHadron->SetMarkerColor(kBlack); hist_CprPyth_365_woHadron->SetMarkerStyle(20); hist_CprPyth_365_woHadron->SetLineWidth(2); hist_CprPyth_365_woHadron->SetMarkerSize(1);

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

	TF1 *fits_fitThNN_912 = new TF1("fits_fitThNN_912", THR_NNLO, 0.15, 0.25, 1);
	fits_fitThNN_912->SetLineColor(kBlue+1); fits_fitThNN_912->SetMarkerColor(kBlue+1); fits_fitThNN_912->SetMarkerStyle(53); fits_fitThNN_912->SetLineWidth(2); fits_fitThNN_912->SetMarkerSize(1);
	TF1 *fits_fitThNN_160 = new TF1("fits_fitThNN_160", THR_NNLO, 0.08, 0.20, 1);
	fits_fitThNN_160->SetLineColor(kBlue+1); fits_fitThNN_160->SetMarkerColor(kBlue+1); fits_fitThNN_160->SetMarkerStyle(53); fits_fitThNN_160->SetLineWidth(2); fits_fitThNN_160->SetMarkerSize(1);
	TF1 *fits_fitThNN_240 = new TF1("fits_fitThNN_240", THR_NNLO, 0.05, 0.20, 1);
	fits_fitThNN_240->SetLineColor(kBlue+1); fits_fitThNN_240->SetMarkerColor(kBlue+1); fits_fitThNN_240->SetMarkerStyle(53); fits_fitThNN_240->SetLineWidth(2); fits_fitThNN_240->SetMarkerSize(1);
	TF1 *fits_fitThNN_365 = new TF1("fits_fitThNN_365", THR_NNLO, 0.05, 0.20, 1);
	fits_fitThNN_365->SetLineColor(kBlue+1); fits_fitThNN_365->SetMarkerColor(kBlue+1); fits_fitThNN_365->SetMarkerStyle(53); fits_fitThNN_365->SetLineWidth(2); fits_fitThNN_365->SetMarkerSize(1);

	TF1 *fits_fitCpNN_912 = new TF1("fits_fitCpNN_912", CPR_NNLO, 0.45, 0.60, 1);
	fits_fitCpNN_912->SetLineColor(kBlue+1); fits_fitCpNN_912->SetMarkerColor(kBlue+1); fits_fitCpNN_912->SetMarkerStyle(53); fits_fitCpNN_912->SetLineWidth(2); fits_fitCpNN_912->SetMarkerSize(1);
	TF1 *fits_fitCpNN_160 = new TF1("fits_fitCpNN_160", CPR_NNLO, 0.25, 0.75, 1);
	fits_fitCpNN_160->SetLineColor(kBlue+1); fits_fitCpNN_160->SetMarkerColor(kBlue+1); fits_fitCpNN_160->SetMarkerStyle(53); fits_fitCpNN_160->SetLineWidth(2); fits_fitCpNN_160->SetMarkerSize(1);
	TF1 *fits_fitCpNN_240 = new TF1("fits_fitCpNN_240", CPR_NNLO, 0.22, 0.60, 1);
	fits_fitCpNN_240->SetLineColor(kBlue+1); fits_fitCpNN_240->SetMarkerColor(kBlue+1); fits_fitCpNN_240->SetMarkerStyle(53); fits_fitCpNN_240->SetLineWidth(2); fits_fitCpNN_240->SetMarkerSize(1);
	TF1 *fits_fitCpNN_365 = new TF1("fits_fitCpNN_365", CPR_NNLO, 0.22, 0.60, 1);
	fits_fitCpNN_365->SetLineColor(kBlue+1); fits_fitCpNN_365->SetMarkerColor(kBlue+1); fits_fitCpNN_365->SetMarkerStyle(53); fits_fitCpNN_365->SetLineWidth(2); fits_fitCpNN_365->SetMarkerSize(1);

	TF1 *fits_fitThNN_91X = new TF1("fits_fitThNN_91X", THR_NNLO, 0.15, 0.25, 1);
	fits_fitThNN_91X->SetLineColor(kRed+2); fits_fitThNN_91X->SetMarkerColor(kRed+2); fits_fitThNN_91X->SetMarkerStyle(53); fits_fitThNN_91X->SetLineWidth(2); fits_fitThNN_91X->SetMarkerSize(1);
	TF1 *fits_fitCpNN_91X = new TF1("fits_fitCpNN_91X", CPR_NNLO, 0.65, 0.74, 1);
	fits_fitCpNN_91X->SetLineColor(kRed+2); fits_fitCpNN_91X->SetMarkerColor(kRed+2); fits_fitCpNN_91X->SetMarkerStyle(53); fits_fitCpNN_91X->SetLineWidth(2); fits_fitCpNN_91X->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	float guess = 0.1, guess_min = 0.01, guess_max = 1.0;

	// fits_fitThNN_912->SetParameter(0, 0.1275); fits_fitThNN_912->SetParLimits(0, guess_min, guess_max);
	// fits_fitThNN_91X->SetParameter(0, 0.1275); fits_fitThNN_91X->SetParLimits(0, guess_min, guess_max);

	// fits_fitThNN_160->SetParameter(0, 0.1172); fits_fitThNN_160->SetParLimits(0, guess_min, guess_max);
	// fits_fitThNN_240->SetParameter(0, 0.1084); fits_fitThNN_240->SetParLimits(0, guess_min, guess_max);
	// fits_fitThNN_365->SetParameter(0, 0.1084); fits_fitThNN_365->SetParLimits(0, guess_min, guess_max);
	
	// fits_fitCpNN_912->SetParameter(0, 0.1273); fits_fitCpNN_912->SetParLimits(0, guess_min, guess_max);
	// fits_fitCpNN_91X->SetParameter(0, 0.1273); fits_fitCpNN_91X->SetParLimits(0, guess_min, guess_max);

	// fits_fitCpNN_160->SetParameter(0, 0.1190); fits_fitCpNN_160->SetParLimits(0, guess_min, guess_max);
	// fits_fitCpNN_240->SetParameter(0, 0.1076); fits_fitCpNN_240->SetParLimits(0, guess_min, guess_max);
	// fits_fitCpNN_365->SetParameter(0, 0.1076); fits_fitCpNN_365->SetParLimits(0, guess_min, guess_max);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912_woHadron->Fit(fits_fitThNN_912, "RNQ MINOS");
	hist_ThrPyth_160_woHadron->Fit(fits_fitThNN_160, "RNQ MINOS");
	hist_ThrPyth_240_woHadron->Fit(fits_fitThNN_240, "RNQ MINOS");
	hist_ThrPyth_365_woHadron->Fit(fits_fitThNN_365, "RNQ MINOS");
	
	hist_CprPyth_912_woHadron->Fit(fits_fitCpNN_912, "RNQ MINOS");
	hist_CprPyth_160_woHadron->Fit(fits_fitCpNN_160, "RNQ MINOS");
	hist_CprPyth_240_woHadron->Fit(fits_fitCpNN_240, "RNQ MINOS");
	hist_CprPyth_365_woHadron->Fit(fits_fitCpNN_365, "RNQ MINOS");

	hist_ThrALPH_912_wiHadron->Fit(fits_fitThNN_91X, "RNQ MINOS");
	hist_CprALPH_912_wiHadron->Fit(fits_fitCpNN_91X, "RNQ MINOS");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	grph_ThrALPH_912_wiHadron->SetTitle("");
	grph_CprALPH_912_wiHadron->SetTitle("");
	hist_ThrPyth_912_woHadron->SetTitle("");
	hist_ThrPyth_160_woHadron->SetTitle("");
	hist_ThrPyth_240_woHadron->SetTitle("");
	hist_ThrPyth_365_woHadron->SetTitle("");

	hist_CprPyth_912_woHadron->SetTitle("");
	hist_CprPyth_160_woHadron->SetTitle("");
	hist_CprPyth_240_woHadron->SetTitle("");
	hist_CprPyth_365_woHadron->SetTitle("");

	hist_ThrPyth_912_woHadron->SetStats(kFALSE);
	hist_ThrPyth_160_woHadron->SetStats(kFALSE);
	hist_ThrPyth_240_woHadron->SetStats(kFALSE);
	hist_ThrPyth_365_woHadron->SetStats(kFALSE);

	hist_CprPyth_912_woHadron->SetStats(kFALSE);
	hist_CprPyth_160_woHadron->SetStats(kFALSE);
	hist_CprPyth_240_woHadron->SetStats(kFALSE);
	hist_CprPyth_365_woHadron->SetStats(kFALSE);
	
	hist_ThrPyth_912_wiHadron->SetStats(kFALSE);
	hist_ThrPyth_160_wiHadron->SetStats(kFALSE);
	hist_ThrPyth_240_wiHadron->SetStats(kFALSE);
	hist_ThrPyth_365_wiHadron->SetStats(kFALSE);

	hist_CprPyth_912_wiHadron->SetStats(kFALSE);
	hist_CprPyth_160_wiHadron->SetStats(kFALSE);
	hist_CprPyth_240_wiHadron->SetStats(kFALSE);
	hist_CprPyth_365_wiHadron->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_fitThNN_912 = new TH1F("hist_fitThNN_912", " ", fits_fitThNN_912->GetNpx(), fits_fitThNN_912->GetXmin(), fits_fitThNN_912->GetXmax());
	for (int b = 1; b <= hist_fitThNN_912->GetNbinsX(); b++) hist_fitThNN_912->SetBinContent(b, fits_fitThNN_912->Eval(hist_fitThNN_912->GetBinCenter(b)));
	hist_fitThNN_912->SetLineColor(kRed+1); hist_fitThNN_912->SetMarkerColor(kBlack); hist_fitThNN_912->SetMarkerStyle(20); hist_fitThNN_912->SetLineWidth(3); hist_fitThNN_912->SetMarkerSize(1);

	TH1F *hist_fitThNN_160 = new TH1F("hist_fitThNN_160", " ", fits_fitThNN_160->GetNpx(), fits_fitThNN_160->GetXmin(), fits_fitThNN_160->GetXmax());
	for (int b = 1; b <= hist_fitThNN_160->GetNbinsX(); b++) hist_fitThNN_160->SetBinContent(b, fits_fitThNN_160->Eval(hist_fitThNN_160->GetBinCenter(b)));
	hist_fitThNN_160->SetLineColor(kRed+1); hist_fitThNN_160->SetMarkerColor(kBlack); hist_fitThNN_160->SetMarkerStyle(20); hist_fitThNN_160->SetLineWidth(3); hist_fitThNN_160->SetMarkerSize(1);

	TH1F *hist_fitThNN_240 = new TH1F("hist_fitThNN_240", " ", fits_fitThNN_240->GetNpx(), fits_fitThNN_240->GetXmin(), fits_fitThNN_240->GetXmax());
	for (int b = 1; b <= hist_fitThNN_240->GetNbinsX(); b++) hist_fitThNN_240->SetBinContent(b, fits_fitThNN_240->Eval(hist_fitThNN_240->GetBinCenter(b)));
	hist_fitThNN_240->SetLineColor(kRed+1); hist_fitThNN_240->SetMarkerColor(kBlack); hist_fitThNN_240->SetMarkerStyle(20); hist_fitThNN_240->SetLineWidth(3); hist_fitThNN_240->SetMarkerSize(1);

	TH1F *hist_fitThNN_365 = new TH1F("hist_fitThNN_365", " ", fits_fitThNN_365->GetNpx(), fits_fitThNN_365->GetXmin(), fits_fitThNN_365->GetXmax());
	for (int b = 1; b <= hist_fitThNN_365->GetNbinsX(); b++) hist_fitThNN_365->SetBinContent(b, fits_fitThNN_365->Eval(hist_fitThNN_365->GetBinCenter(b)));
	hist_fitThNN_365->SetLineColor(kRed+1); hist_fitThNN_365->SetMarkerColor(kBlack); hist_fitThNN_365->SetMarkerStyle(20); hist_fitThNN_365->SetLineWidth(3); hist_fitThNN_365->SetMarkerSize(1);	

	TH1F *hist_fitCpNN_912 = new TH1F("hist_fitCpNN_912", " ", fits_fitCpNN_912->GetNpx(), fits_fitCpNN_912->GetXmin(), fits_fitCpNN_912->GetXmax());
	for (int b = 1; b <= hist_fitCpNN_912->GetNbinsX(); b++) hist_fitCpNN_912->SetBinContent(b, fits_fitCpNN_912->Eval(hist_fitCpNN_912->GetBinCenter(b)));
	hist_fitCpNN_912->SetLineColor(kRed+1); hist_fitCpNN_912->SetMarkerColor(kBlack); hist_fitCpNN_912->SetMarkerStyle(20); hist_fitCpNN_912->SetLineWidth(3); hist_fitCpNN_912->SetMarkerSize(1);

	TH1F *hist_fitCpNN_160 = new TH1F("hist_fitCpNN_160", " ", fits_fitCpNN_160->GetNpx(), fits_fitCpNN_160->GetXmin(), fits_fitCpNN_160->GetXmax());
	for (int b = 1; b <= hist_fitCpNN_160->GetNbinsX(); b++) hist_fitCpNN_160->SetBinContent(b, fits_fitCpNN_160->Eval(hist_fitCpNN_160->GetBinCenter(b)));
	hist_fitCpNN_160->SetLineColor(kRed+1); hist_fitCpNN_160->SetMarkerColor(kBlack); hist_fitCpNN_160->SetMarkerStyle(20); hist_fitCpNN_160->SetLineWidth(3); hist_fitCpNN_160->SetMarkerSize(1);

	TH1F *hist_fitCpNN_240 = new TH1F("hist_fitCpNN_240", " ", fits_fitCpNN_240->GetNpx(), fits_fitCpNN_240->GetXmin(), fits_fitCpNN_240->GetXmax());
	for (int b = 1; b <= hist_fitCpNN_240->GetNbinsX(); b++) hist_fitCpNN_240->SetBinContent(b, fits_fitCpNN_240->Eval(hist_fitCpNN_240->GetBinCenter(b)));
	hist_fitCpNN_240->SetLineColor(kRed+1); hist_fitCpNN_240->SetMarkerColor(kBlack); hist_fitCpNN_240->SetMarkerStyle(20); hist_fitCpNN_240->SetLineWidth(3); hist_fitCpNN_240->SetMarkerSize(1);

	TH1F *hist_fitCpNN_365 = new TH1F("hist_fitCpNN_365", " ", fits_fitCpNN_365->GetNpx(), fits_fitCpNN_365->GetXmin(), fits_fitCpNN_365->GetXmax());
	for (int b = 1; b <= hist_fitCpNN_365->GetNbinsX(); b++) hist_fitCpNN_365->SetBinContent(b, fits_fitCpNN_365->Eval(hist_fitCpNN_365->GetBinCenter(b)));
	hist_fitCpNN_365->SetLineColor(kRed+1); hist_fitCpNN_365->SetMarkerColor(kBlack); hist_fitCpNN_365->SetMarkerStyle(20); hist_fitCpNN_365->SetLineWidth(3); hist_fitCpNN_365->SetMarkerSize(1);	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv5 = new TCanvas("cv5", "FCC-ee ISR Studies", 900, 900);

	TLegend* lg5 = new TLegend(0.73, 0.82, 0.92, 0.93);
	lg5->AddEntry(hist_ThrPyth_912_woHadron, "PYTHIA", "P");
	lg5->AddEntry(hist_fitThNN_912, "NNLO", "L");
	lg5->SetTextSize(0.04);	

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv5->SetMargin(0, 0, 0, 0); 
	cv5->Divide(1,2);
	for (int i = 1; i <= 2; i++) {
		cv5->cd(i);
		gPad->SetTopMargin(0.025);
		gPad->SetBottomMargin(0.07);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		gPad->SetLogy();
	}

	hist_ThrPyth_912_woHadron->SetLineColor(kBlack); hist_ThrPyth_912_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_912_woHadron->SetMarkerStyle(kStar); hist_ThrPyth_912_woHadron->SetLineWidth(2); hist_ThrPyth_912_woHadron->SetMarkerSize(2);
	hist_ThrPyth_160_woHadron->SetLineColor(kBlack); hist_ThrPyth_160_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_160_woHadron->SetMarkerStyle(kStar); hist_ThrPyth_160_woHadron->SetLineWidth(2); hist_ThrPyth_160_woHadron->SetMarkerSize(2);
	hist_ThrPyth_240_woHadron->SetLineColor(kBlack); hist_ThrPyth_240_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_240_woHadron->SetMarkerStyle(kStar); hist_ThrPyth_240_woHadron->SetLineWidth(2); hist_ThrPyth_240_woHadron->SetMarkerSize(2);
	hist_ThrPyth_365_woHadron->SetLineColor(kBlack); hist_ThrPyth_365_woHadron->SetMarkerColor(kBlack); hist_ThrPyth_365_woHadron->SetMarkerStyle(kStar); hist_ThrPyth_365_woHadron->SetLineWidth(2); hist_ThrPyth_365_woHadron->SetMarkerSize(2);

	hist_CprPyth_912_woHadron->SetLineColor(kBlack); hist_CprPyth_912_woHadron->SetMarkerColor(kBlack); hist_CprPyth_912_woHadron->SetMarkerStyle(kStar); hist_CprPyth_912_woHadron->SetLineWidth(2); hist_CprPyth_912_woHadron->SetMarkerSize(1.5);
	hist_CprPyth_160_woHadron->SetLineColor(kBlack); hist_CprPyth_160_woHadron->SetMarkerColor(kBlack); hist_CprPyth_160_woHadron->SetMarkerStyle(kStar); hist_CprPyth_160_woHadron->SetLineWidth(2); hist_CprPyth_160_woHadron->SetMarkerSize(1.5);
	hist_CprPyth_240_woHadron->SetLineColor(kBlack); hist_CprPyth_240_woHadron->SetMarkerColor(kBlack); hist_CprPyth_240_woHadron->SetMarkerStyle(kStar); hist_CprPyth_240_woHadron->SetLineWidth(2); hist_CprPyth_240_woHadron->SetMarkerSize(1.5);
	hist_CprPyth_365_woHadron->SetLineColor(kBlack); hist_CprPyth_365_woHadron->SetMarkerColor(kBlack); hist_CprPyth_365_woHadron->SetMarkerStyle(kStar); hist_CprPyth_365_woHadron->SetLineWidth(2); hist_CprPyth_365_woHadron->SetMarkerSize(1.5);

	hist_ThrPyth_912_woHadron->GetXaxis()->CenterTitle(); hist_ThrPyth_912_woHadron->GetYaxis()->CenterTitle();
	hist_CprPyth_912_woHadron->GetXaxis()->CenterTitle(); hist_CprPyth_912_woHadron->GetYaxis()->CenterTitle();

	// Draw
	cv5->cd(1);

	hist_ThrPyth_912_woHadron->Draw("P");
	hist_fitThNN_912->Draw("HIST C SAME");
	
	hist_ThrPyth_160_woHadron->Scale(1E3);
	hist_ThrPyth_160_woHadron->Draw("P SAME");
	hist_fitThNN_160->Scale(1E3);
	hist_fitThNN_160->Draw("HIST C SAME");

	hist_ThrPyth_240_woHadron->Scale(1E6);
	hist_ThrPyth_240_woHadron->Draw("P SAME");
	hist_fitThNN_240->Scale(1E6);
	hist_fitThNN_240->Draw("HIST C SAME");

	hist_ThrPyth_365_woHadron->Scale(1E9);
	hist_ThrPyth_365_woHadron->Draw("P SAME");
	hist_fitThNN_365->Scale(1E9);
	hist_fitThNN_365->Draw("HIST C SAME");

	lg5->Draw("SAME");	

	cv5->cd(2);

	hist_CprPyth_912_woHadron->Draw("P");
	hist_fitCpNN_912->Draw("HIST C SAME");

	hist_CprPyth_160_woHadron->Scale(1E3);
	hist_CprPyth_160_woHadron->Draw("P SAME");
	hist_fitCpNN_160->Scale(1E3);
	hist_fitCpNN_160->Draw("HIST C SAME");

	hist_CprPyth_240_woHadron->Scale(1E6);
	hist_CprPyth_240_woHadron->Draw("P SAME");
	hist_fitCpNN_240->Scale(1E6);
	hist_fitCpNN_240->Draw("HIST C SAME");

	hist_CprPyth_365_woHadron->Scale(1E9);
	hist_CprPyth_365_woHadron->Draw("P SAME");
	hist_fitCpNN_365->Scale(1E9);
	hist_fitCpNN_365->Draw("HIST C SAME");

	lg5->Draw("SAME");	

	// Set limits
	hist_ThrPyth_912_woHadron->GetYaxis()->SetRangeUser(1E-3,1E12);
	hist_ThrPyth_912_woHadron->GetXaxis()->SetRangeUser(0,0.39);
	hist_CprPyth_912_woHadron->GetYaxis()->SetRangeUser(1E-3,1E12);
	hist_CprPyth_912_woHadron->GetXaxis()->SetRangeUser(0,0.90);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv5->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Import aleph
	TDirectory *table_EXP_ALP = (TDirectory*)input_EXP_ALP->Get("Table 52");
	TGraphAsymmErrors* grph_AlphaSS_ExALP = (TGraphAsymmErrors*)table_EXP_ALP->Get("Graph1D_y1");
	grph_AlphaSS_ExALP->SetLineColor(kBlue+2); grph_AlphaSS_ExALP->SetMarkerColor(kBlue+2); grph_AlphaSS_ExALP->SetMarkerStyle(53); grph_AlphaSS_ExALP->SetLineWidth(2); grph_AlphaSS_ExALP->SetMarkerSize(1.5); grph_AlphaSS_ExALP->SetFillColorAlpha(kBlue, 0.1);

	// L3 graph
	double xbin_AlphaSS_ExLL3[16] = { 41.4, 55.3, 65.4, 75.7, 82.3, 85.1, 91.2, 130.1, 136.1, 161.3, 172.3, 182.8, 188.6, 194.4, 200, 206.2 };
	double ybin_AlphaSS_ExLL3[16] = { 0.1418, 0.1260, 0.1331, 0.1204, 0.1184, 0.1152, 0.1210, 0.1138, 0.1121, 0.1051, 0.1099, 0.1096, 0.1122, 0.1123, 0.1138, 0.1132 };
	double yerr_AlphaSS_ExLL3[16] = { 0.011814821, 0.011638299, 0.010180864, 0.010230347, 0.009896464, 0.010293202, 0.006824222, 0.006787488, 0.007315053, 0.007477968, 0.007912016, 0.005521775, 0.005337602, 0.005647123, 0.005728001, 0.005497272 };
	// Construct
	auto grph_AlphaSS_ExLL3 = new TGraphErrors(16, xbin_AlphaSS_ExLL3, ybin_AlphaSS_ExLL3, nullptr, yerr_AlphaSS_ExLL3);
	grph_AlphaSS_ExLL3->SetLineColor(kRed+2); grph_AlphaSS_ExLL3->SetMarkerColor(kRed+2); grph_AlphaSS_ExLL3->SetMarkerStyle(53); grph_AlphaSS_ExLL3->SetLineWidth(2); grph_AlphaSS_ExLL3->SetMarkerSize(1.5); grph_AlphaSS_ExLL3->SetFillColorAlpha(kRed, 0.1);

	// Dissertori graph
	double xbin_AlphaSS_Disse[8] = { 91.2, 133.0, 161.0, 172.0, 183.0, 189.0, 200.0, 206.0 };
	double ybin_AlphaSS_Disse[8] = { 0.1239, 0.1270, 0.1313, 0.1192, 0.1226, 0.1234, 0.1200, 0.1202 };
	double yerr_AlphaSS_Disse[8] = { 0.0037, 0.0048, 0.0060, 0.0070, 0.0041, 0.0036, 0.0036, 0.0034 };
	// Construct
	auto grph_AlphaSS_Disse = new TGraphErrors(8, xbin_AlphaSS_Disse, ybin_AlphaSS_Disse, nullptr, yerr_AlphaSS_Disse);
	grph_AlphaSS_Disse->SetLineColor(kRed+2); grph_AlphaSS_Disse->SetMarkerColor(kRed+2); grph_AlphaSS_Disse->SetMarkerStyle(53); grph_AlphaSS_Disse->SetLineWidth(2); grph_AlphaSS_Disse->SetMarkerSize(1.5); grph_AlphaSS_Disse->SetFillColorAlpha(kRed, 0.1);

	// FCC energy
	double xbin_AlphaSS_PyAll[4] = {91.2, 160.0, 240.0, 365.0};

	// Access pythia bins
	double ybin_AlphaSS_PyAll[4] = {
	(fits_fitThNN_912->GetParameter(0)+fits_fitCpNN_912->GetParameter(0))/2,
	(fits_fitThNN_160->GetParameter(0)+fits_fitCpNN_160->GetParameter(0))/2,
	(fits_fitThNN_240->GetParameter(0)+fits_fitCpNN_240->GetParameter(0))/2,
	(fits_fitThNN_365->GetParameter(0)+fits_fitCpNN_365->GetParameter(0))/2
	};

	// Access pythia errors
	double yerr_AlphaSS_PyAll[4] = {
	fits_fitThNN_912->GetParError(0),
	fits_fitThNN_160->GetParError(0),
	fits_fitThNN_240->GetParError(0),
	fits_fitThNN_365->GetParError(0)
	};

	// Access pythia bins
	double ybin_AlphaSS_PyThr[4] = {
	fits_fitThNN_912->GetParameter(0),
	fits_fitThNN_160->GetParameter(0),
	fits_fitThNN_240->GetParameter(0),
	fits_fitThNN_365->GetParameter(0)
	};

	// Access pythia bins
	double ybin_AlphaSS_PyCpr[4] = {
	fits_fitCpNN_912->GetParameter(0),
	fits_fitCpNN_160->GetParameter(0),
	fits_fitCpNN_240->GetParameter(0),
	fits_fitCpNN_365->GetParameter(0)
	};

	// Access pythia errors
	double yerr_AlphaSS_PyThr[4] = {
	fits_fitThNN_912->GetParError(0),
	fits_fitThNN_160->GetParError(0),
	fits_fitThNN_240->GetParError(0),
	fits_fitThNN_365->GetParError(0)
	};

	// Construct pythia graph
	auto grph_AlphaSS_PyAll = new TGraphAsymmErrors(4, xbin_AlphaSS_PyAll, ybin_AlphaSS_PyAll, nullptr, yerr_AlphaSS_PyAll);
	grph_AlphaSS_PyAll->SetLineColor(kBlack); grph_AlphaSS_PyAll->SetMarkerColor(kBlack); grph_AlphaSS_PyAll->SetMarkerStyle(20); grph_AlphaSS_PyAll->SetLineWidth(2); grph_AlphaSS_PyAll->SetMarkerSize(1.5);
	auto grph_AlphaSS_PyThr = new TGraphAsymmErrors(4, xbin_AlphaSS_PyAll, ybin_AlphaSS_PyThr, nullptr, yerr_AlphaSS_PyThr);
	grph_AlphaSS_PyThr->SetLineColor(kRed+2); grph_AlphaSS_PyThr->SetMarkerColor(kRed+2); grph_AlphaSS_PyThr->SetMarkerStyle(53); grph_AlphaSS_PyThr->SetLineWidth(2); grph_AlphaSS_PyThr->SetMarkerSize(2);
	auto grph_AlphaSS_PyCpr = new TGraphAsymmErrors(4, xbin_AlphaSS_PyAll, ybin_AlphaSS_PyCpr, nullptr, yerr_AlphaSS_PyThr);
	grph_AlphaSS_PyCpr->SetLineColor(kBlue+2); grph_AlphaSS_PyCpr->SetMarkerColor(kBlue+2); grph_AlphaSS_PyCpr->SetMarkerStyle(53); grph_AlphaSS_PyCpr->SetLineWidth(2); grph_AlphaSS_PyCpr->SetMarkerSize(2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Construct the 3-loop QCD running curve and uncertainty band (Λ₅ = 0.247 ± 0.014 GeV)
	const double Lam_c  = 0.247;										// Central Λ₅ value in GeV
	const double Lam_lo = 0.247 - 0.014;								// Lower Λ₅ bound (−1σ)
	const double Lam_hi = 0.247 + 0.014;								// Upper Λ₅ bound (+1σ)

	const int Npts = 300;												// Number of sampling points
	double Qx[Npts], asC[Npts], asUp[Npts], asDn[Npts];					// Arrays for √s and αs values

	// Compute 3-loop αs(Q)
	for (int i = 0; i < Npts; i++) {
		double Q = 20.0 + i * (400.0) / (Npts - 1);  // √s range: 40–400 GeV
		Qx[i]  = Q;
		asC[i] = alpha3L_Lambda(Q, Lam_c);           // Central prediction
		// Λ envelope
		double a_hi = alpha3L_Lambda(Q, Lam_lo);     // Smaller Λ → larger αs
		double a_lo = alpha3L_Lambda(Q, Lam_hi);     // Larger Λ → smaller αs
		asUp[i] = a_hi;
		asDn[i] = a_lo;
	}

	// Define central curve
	TGraph *gRun3L = new TGraph(Npts, Qx, asC);
	gRun3L->SetLineColor(kGray + 3);
	// gRun3L->SetLineStyle(7);
	gRun3L->SetLineWidth(1);

	// Construct uncertainty band
	TGraph *gBand3L = new TGraph(2 * Npts);
	for (int i = 0; i < Npts; i++) {
		gBand3L->SetPoint(i, Qx[i], asUp[i]);                			// Upper edge
		gBand3L->SetPoint(2 * Npts - 1 - i, Qx[i], asDn[i]);			// Lower edge (reversed)
	}
	gBand3L->SetFillColorAlpha(kBlue, 0.20);
	gBand3L->SetLineColor(0);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// === PYTHIA-based 3-loop QCD running (αs(mZ) = 0.1283 ± 0.014) ===
	const double asMZ_pythia = 0.1283;
	const double asMZ_unc = 0.000001;
	const double mZ_val = 91.1876;

	double Lambda_pyt_c  = Lambda_from_alpha3L(mZ_val, asMZ_pythia);
	double Lambda_pyt_lo = Lambda_from_alpha3L(mZ_val, asMZ_pythia - asMZ_unc);
	double Lambda_pyt_hi = Lambda_from_alpha3L(mZ_val, asMZ_pythia + asMZ_unc);

	const int NptsPY = 300;
	double Qpy[NptsPY], asPytC[NptsPY], asPytLo[NptsPY], asPytHi[NptsPY];

	for (int i = 0; i < NptsPY; i++) {
		double Qval = 20.0 + i * (400.0) / (NptsPY - 1);
		Qpy[i]     = Qval;
		asPytC[i]  = alpha3L_Lambda(Qval, Lambda_pyt_c);
		// Λ envelope
		asPytLo[i] = alpha3L_Lambda(Qval, Lambda_pyt_lo);
		asPytHi[i] = alpha3L_Lambda(Qval, Lambda_pyt_hi);
	}

	TGraph* gRunPY = new TGraph(NptsPY, Qpy, asPytC);
	gRunPY->SetLineColor(kYellow+2);
	// gRunPY->SetLineStyle(7);
	gRunPY->SetLineWidth(1);

	// Ensure ordering and no crossings
	for (int i = 0; i < NptsPY; ++i) {
		if (asPytLo[i] > asPytHi[i]) std::swap(asPytLo[i], asPytHi[i]);
	}

	// Draw band and central curve
	TGraph* gBandPY = new TGraph(2*NptsPY);
	for (int i = 0; i < NptsPY; ++i)
		gBandPY->SetPoint(i, Qpy[i], asPytHi[i]);
	for (int i = 0; i < NptsPY; ++i)
		gBandPY->SetPoint(NptsPY + i, Qpy[NptsPY-1-i], asPytLo[NptsPY-1-i]);
	gBandPY->SetFillColorAlpha(kCyan, 0.3);
	gBandPY->SetLineColor(0);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv4 = new TCanvas("cv4", "FCC-ee ISR Studies", 800, 1200);

	// // Add legend
	// TLegend *lg4 = new TLegend(0.73, 0.83, 0.92, 0.93);
	// lg4->AddEntry(grph_AlphaSS_PyAll, "PYTHIA", "P");
	// // lg4->AddEntry(grph_AlphaSS_PyThr, "PYTHIA (1-T)", "L");
	// // lg4->AddEntry(grph_AlphaSS_PyCpr, "PYTHIA (C)", "L");
	// lg4->AddEntry(grph_AlphaSS_ExALP, "ALEPH", "P");
	// lg4->AddEntry(grph_AlphaSS_ExLL3, "L3", "P");
	// // lg4->AddEntry(gRun3L, "3-loop QCD", "L");
	// lg4->SetTextSize(0.04);

	// // Beautify
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv4->SetMargin(0, 0, 0, 0);
	// gPad->SetTopMargin(0.025);
	// gPad->SetBottomMargin(0.08);
	// gPad->SetLeftMargin(0.15);
	// gPad->SetRightMargin(0.04);
	// gPad->SetTickx(); gPad->SetTicky();

	// // Beautify
	// grph_AlphaSS_PyAll->GetXaxis()->CenterTitle(); grph_AlphaSS_PyAll->GetYaxis()->CenterTitle();
	// grph_AlphaSS_PyAll->GetXaxis()->SetLabelSize(0.04); grph_AlphaSS_PyAll->GetXaxis()->SetTitleSize(0.04);
	// grph_AlphaSS_PyAll->GetYaxis()->SetLabelSize(0.04); grph_AlphaSS_PyAll->GetYaxis()->SetTitleSize(0.04);
	// grph_AlphaSS_PyAll->SetTitle("");
	// grph_AlphaSS_PyAll->GetYaxis()->SetTitle("#alpha_{S}(#sqrt{s})");
	// grph_AlphaSS_PyAll->GetXaxis()->SetTitle("#sqrt{s} (GeV)");

	// // // Draw
	// grph_AlphaSS_PyAll->Draw("APE");
	// // grph_AlphaSS_PyThr->Draw("PEL SAME");
	// // grph_AlphaSS_PyCpr->Draw("PEL SAME");
	// grph_AlphaSS_ExALP->Draw("PE SAME");
	// grph_AlphaSS_ExLL3->Draw("PE SAME");
	// // grph_AlphaSS_Disse->Draw("PEL SAME");
	// gBand3L->Draw("F SAME");
	// gRun3L->Draw("L SAME");
	// // gBandPY->Draw("F SAME");
	// // gRunPY->Draw("L SAME");
	// lg4->Draw("SAME");

	// // Set limits
	// grph_AlphaSS_PyAll->GetYaxis()->SetRangeUser(0.09,0.16);
	// grph_AlphaSS_PyAll->GetXaxis()->SetLimits(30, 400);

	// // Update canvas
	// cv4->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Print results
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << fixed << setprecision(4);

	cout << "====== FITTING WITH THRUST ======" << endl;
	cout << "√s \t χ²/ndf \t Alpha \t Error" << endl;
	cout << "---------------------------------" << endl;
	// cout << "ALEPH \t " << fits_fitThNN_91X->GetChisquare()<<"/"<<fits_fitThNN_91X->GetNDF() << "\t" << fits_fitThNN_91X->GetParameter(0) << endl; 
	cout << "91.2 \t " << fits_fitThNN_912->GetChisquare()<<"/"<<fits_fitThNN_912->GetNDF() << "\t" << fits_fitThNN_912->GetParameter(0) << "\t" << fits_fitThNN_912->GetParError(0) << endl; 
	cout << "160 \t " << fits_fitThNN_160->GetChisquare()<<"/"<<fits_fitThNN_160->GetNDF() << "\t" << fits_fitThNN_160->GetParameter(0) << "\t" << fits_fitThNN_160->GetParError(0) << endl;
	cout << "240 \t " << fits_fitThNN_240->GetChisquare()<<"/"<<fits_fitThNN_240->GetNDF() << "\t" << fits_fitThNN_240->GetParameter(0) << "\t" << fits_fitThNN_240->GetParError(0) << endl;
	cout << "365 \t " << fits_fitThNN_365->GetChisquare()<<"/"<<fits_fitThNN_365->GetNDF() << "\t" << fits_fitThNN_365->GetParameter(0) << "\t" << fits_fitThNN_365->GetParError(0) << endl;
	cout << "=================================" << endl;

	cout << "====== FITTING WITH CPARAM ======" << endl;
	cout << "√s \t χ²/ndf \t Alpha \t Error" << endl;
	cout << "---------------------------------" << endl;
	// cout << "ALEPH \t " << fits_fitCpNN_91X->GetChisquare()<<"/"<<fits_fitCpNN_91X->GetNDF() << "\t" << fits_fitCpNN_91X->GetParameter(0) << endl;
	cout << "91.2 \t " << fits_fitCpNN_912->GetChisquare()<<"/"<<fits_fitCpNN_912->GetNDF() << "\t" << fits_fitCpNN_912->GetParameter(0) << "\t" << fits_fitCpNN_912->GetParError(0) << endl;
	cout << "160 \t " << fits_fitCpNN_160->GetChisquare()<<"/"<<fits_fitCpNN_160->GetNDF() << "\t" << fits_fitCpNN_160->GetParameter(0) << "\t" << fits_fitCpNN_160->GetParError(0) << endl;
	cout << "240 \t " << fits_fitCpNN_240->GetChisquare()<<"/"<<fits_fitCpNN_240->GetNDF() << "\t" << fits_fitCpNN_240->GetParameter(0) << "\t" << fits_fitCpNN_240->GetParError(0) << endl;
	cout << "365 \t " << fits_fitCpNN_365->GetChisquare()<<"/"<<fits_fitCpNN_365->GetNDF() << "\t" << fits_fitCpNN_365->GetParameter(0) << "\t" << fits_fitCpNN_365->GetParError(0) << endl;
	cout << "=================================" << endl;

	cout << "====== FINAL ======" << endl;
	cout << "√s \t Alpha " << endl;
	cout << "-------------------" << endl;
	cout << "91.2 \t " << (fits_fitThNN_912->GetParameter(0)+fits_fitCpNN_912->GetParameter(0))/2 << endl;
	cout << "160 \t " << (fits_fitThNN_160->GetParameter(0)+fits_fitCpNN_160->GetParameter(0))/2 << "\t" << endl;
	cout << "240 \t " << (fits_fitThNN_240->GetParameter(0)+fits_fitCpNN_240->GetParameter(0))/2 << "\t" << endl;
	cout << "365 \t " << (fits_fitThNN_365->GetParameter(0)+fits_fitCpNN_365->GetParameter(0))/2 << "\t" << endl;
	cout << "===================" << endl;

}