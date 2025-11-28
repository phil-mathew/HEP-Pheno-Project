/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to generate plots in ROOT from TTree file produced by Pythia
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include <fstream>
#include <sstream>
// ROOT
#include "TFile.h"
#include "TH1F.h"
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

struct Mult3NLOCoeffs {
    double r1, r2, r3;
    double a1, a2, a3;
};

Mult3NLOCoeffs coeffs_for_nf(int nf) {
    // From your table (screenshot): rows for nf=3,4,5
    // r_i and a_i values
    if (nf == 3) return {0.185, 0.426, 0.189, 0.280, -0.379, 0.209};
    if (nf == 4) return {0.191, 0.468, 0.080, 0.297, -0.339, 0.162};
    // default to nf = 5
    return {0.198, 0.510, -0.041, 0.314, -0.301, 0.112};
}


// Code
void ImpactofMults() {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_EXPDATA = TFile::Open("3-LEPdata/EXPDATA.root");
	TFile *input_EXP_ALP = TFile::Open("3-LEPdata/EXP_ALP.root");
	TFile *input_EXP_LL3 = TFile::Open("3-LEPdata/EXP_LL3.root");

	TFile *input_912 = new TFile("5-CutData/cut_FCC912.root", "READ");
	TFile *input_160 = new TFile("5-CutData/cut_FCC160.root", "READ");
	TFile *input_240 = new TFile("5-CutData/cut_FCC240.root", "READ");
	TFile *input_365 = new TFile("5-CutData/cut_FCC365.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F *hist_nHadChg_912_Zq = (TH1F*)input_912->Get("hist_nHadChg_Zq");
	hist_nHadChg_912_Zq->SetLineColor(kBlue+2); hist_nHadChg_912_Zq->SetMarkerColor(kBlue+2); hist_nHadChg_912_Zq->SetMarkerStyle(26); hist_nHadChg_912_Zq->SetLineWidth(1); hist_nHadChg_912_Zq->SetMarkerSize(2);
	TH1F *hist_nHadChg_160_Zq = (TH1F*)input_160->Get("hist_nHadChg_Zq");
	hist_nHadChg_160_Zq->SetLineColor(kYellow+2); hist_nHadChg_160_Zq->SetMarkerColor(kYellow+2); hist_nHadChg_160_Zq->SetMarkerStyle(26); hist_nHadChg_160_Zq->SetLineWidth(1); hist_nHadChg_160_Zq->SetMarkerSize(2);
	TH1F *hist_nHadChg_240_Zq = (TH1F*)input_240->Get("hist_nHadChg_Zq");
	hist_nHadChg_240_Zq->SetLineColor(kGreen+2); hist_nHadChg_240_Zq->SetMarkerColor(kGreen+2); hist_nHadChg_240_Zq->SetMarkerStyle(26); hist_nHadChg_240_Zq->SetLineWidth(1); hist_nHadChg_240_Zq->SetMarkerSize(2);

	TH1F* hist_nHadChg_365_al = (TH1F*)input_365->Get("hist_nHadChg");
	hist_nHadChg_365_al->SetLineColor(kBlack); hist_nHadChg_365_al->SetMarkerColor(kBlack); hist_nHadChg_365_al->SetMarkerStyle(21); hist_nHadChg_365_al->SetLineWidth(1); hist_nHadChg_365_al->SetMarkerSize(1);
	TH1F* hist_nHadChg_365_Zq = (TH1F*)input_365->Get("hist_nHadChg_Zq");
	hist_nHadChg_365_Zq->SetLineColor(kRed+2); hist_nHadChg_365_Zq->SetMarkerColor(kRed+1); hist_nHadChg_365_Zq->SetMarkerStyle(21); hist_nHadChg_365_Zq->SetLineWidth(1); hist_nHadChg_365_Zq->SetMarkerSize(1);
	TH1F* hist_nHadChg_365_WW = (TH1F*)input_365->Get("hist_nHadChg_WW");
	hist_nHadChg_365_WW->SetLineColor(kGreen+2); hist_nHadChg_365_WW->SetMarkerColor(kGreen+1); hist_nHadChg_365_WW->SetMarkerStyle(21); hist_nHadChg_365_WW->SetLineWidth(1); hist_nHadChg_365_WW->SetMarkerSize(1);
	TH1F* hist_nHadChg_365_ZZ = (TH1F*)input_365->Get("hist_nHadChg_ZZ");
	hist_nHadChg_365_ZZ->SetLineColor(kBlue+2); hist_nHadChg_365_ZZ->SetMarkerColor(kBlue+1); hist_nHadChg_365_ZZ->SetMarkerStyle(21); hist_nHadChg_365_ZZ->SetLineWidth(1); hist_nHadChg_365_ZZ->SetMarkerSize(1);
	TH1F* hist_nHadChg_365_tt = (TH1F*)input_365->Get("hist_nHadChg_tt");
	hist_nHadChg_365_tt->SetLineColor(kYellow+2); hist_nHadChg_365_tt->SetMarkerColor(kYellow+1); hist_nHadChg_365_tt->SetMarkerStyle(21); hist_nHadChg_365_tt->SetLineWidth(1); hist_nHadChg_365_tt->SetMarkerSize(1);
	TH1F* hist_nHadChg_365_HZ = (TH1F*)input_365->Get("hist_nHadChg_HZ");
	hist_nHadChg_365_HZ->SetLineColor(kMagenta+2); hist_nHadChg_365_HZ->SetMarkerColor(kMagenta+1); hist_nHadChg_365_HZ->SetMarkerStyle(21); hist_nHadChg_365_HZ->SetLineWidth(1); hist_nHadChg_365_HZ->SetMarkerSize(1);
	TH1F* hist_nHadChg_365_HW = (TH1F*)input_365->Get("hist_nHadChg_HW");
	hist_nHadChg_365_HW->SetLineColor(kCyan+2); hist_nHadChg_365_HW->SetMarkerColor(kCyan+1); hist_nHadChg_365_HW->SetMarkerStyle(21); hist_nHadChg_365_HW->SetLineWidth(1); hist_nHadChg_365_HW->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_nHadAll_912_Zq = (TH1F*)input_912->Get("hist_nHadAll_Zq");
	hist_nHadAll_912_Zq->SetLineColor(kBlue+2); hist_nHadAll_912_Zq->SetMarkerColor(kBlue+2); hist_nHadAll_912_Zq->SetMarkerStyle(26); hist_nHadAll_912_Zq->SetLineWidth(1); hist_nHadAll_912_Zq->SetMarkerSize(2);
	TH1F *hist_nHadAll_160_Zq = (TH1F*)input_160->Get("hist_nHadAll_Zq");
	hist_nHadAll_160_Zq->SetLineColor(kYellow+2); hist_nHadAll_160_Zq->SetMarkerColor(kYellow+2); hist_nHadAll_160_Zq->SetMarkerStyle(26); hist_nHadAll_160_Zq->SetLineWidth(1); hist_nHadAll_160_Zq->SetMarkerSize(2);
	TH1F *hist_nHadAll_240_Zq = (TH1F*)input_240->Get("hist_nHadAll_Zq");
	hist_nHadAll_240_Zq->SetLineColor(kGreen+2); hist_nHadAll_240_Zq->SetMarkerColor(kGreen+2); hist_nHadAll_240_Zq->SetMarkerStyle(26); hist_nHadAll_240_Zq->SetLineWidth(1); hist_nHadAll_240_Zq->SetMarkerSize(2);

	TH1F* hist_nHadAll_365_al = (TH1F*)input_365->Get("hist_nHadAll");
	hist_nHadAll_365_al->SetLineColor(kBlack); hist_nHadAll_365_al->SetMarkerColor(kBlack); hist_nHadAll_365_al->SetMarkerStyle(21); hist_nHadAll_365_al->SetLineWidth(1); hist_nHadAll_365_al->SetMarkerSize(1);
	TH1F* hist_nHadAll_365_Zq = (TH1F*)input_365->Get("hist_nHadAll_Zq");
	hist_nHadAll_365_Zq->SetLineColor(kRed+2); hist_nHadAll_365_Zq->SetMarkerColor(kRed+1); hist_nHadAll_365_Zq->SetMarkerStyle(21); hist_nHadAll_365_Zq->SetLineWidth(1); hist_nHadAll_365_Zq->SetMarkerSize(1);
	TH1F* hist_nHadAll_365_WW = (TH1F*)input_365->Get("hist_nHadAll_WW");
	hist_nHadAll_365_WW->SetLineColor(kGreen+2); hist_nHadAll_365_WW->SetMarkerColor(kGreen+1); hist_nHadAll_365_WW->SetMarkerStyle(21); hist_nHadAll_365_WW->SetLineWidth(1); hist_nHadAll_365_WW->SetMarkerSize(1);
	TH1F* hist_nHadAll_365_ZZ = (TH1F*)input_365->Get("hist_nHadAll_ZZ");
	hist_nHadAll_365_ZZ->SetLineColor(kBlue+2); hist_nHadAll_365_ZZ->SetMarkerColor(kBlue+1); hist_nHadAll_365_ZZ->SetMarkerStyle(21); hist_nHadAll_365_ZZ->SetLineWidth(1); hist_nHadAll_365_ZZ->SetMarkerSize(1);
	TH1F* hist_nHadAll_365_tt = (TH1F*)input_365->Get("hist_nHadAll_tt");
	hist_nHadAll_365_tt->SetLineColor(kYellow+2); hist_nHadAll_365_tt->SetMarkerColor(kYellow+1); hist_nHadAll_365_tt->SetMarkerStyle(21); hist_nHadAll_365_tt->SetLineWidth(1); hist_nHadAll_365_tt->SetMarkerSize(1);
	TH1F* hist_nHadAll_365_HZ = (TH1F*)input_365->Get("hist_nHadAll_HZ");
	hist_nHadAll_365_HZ->SetLineColor(kMagenta+2); hist_nHadAll_365_HZ->SetMarkerColor(kMagenta+1); hist_nHadAll_365_HZ->SetMarkerStyle(21); hist_nHadAll_365_HZ->SetLineWidth(1); hist_nHadAll_365_HZ->SetMarkerSize(1);
	TH1F* hist_nHadAll_365_HW = (TH1F*)input_365->Get("hist_nHadAll_HW");
	hist_nHadAll_365_HW->SetLineColor(kCyan+2); hist_nHadAll_365_HW->SetMarkerColor(kCyan+1); hist_nHadAll_365_HW->SetMarkerStyle(21); hist_nHadAll_365_HW->SetLineWidth(1); hist_nHadAll_365_HW->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_nHadChg_912_Zq->SetStats(kFALSE);
	hist_nHadChg_365_al->SetStats(kFALSE);
	hist_nHadAll_365_al->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Import aleph
	TDirectory *table_EXP_ALP_NCH = (TDirectory*)input_EXP_ALP->Get("Table 1");
	TGraphAsymmErrors* grph_nHadAvg_ExALP = (TGraphAsymmErrors*)table_EXP_ALP_NCH->Get("Graph1D_y1");
	grph_nHadAvg_ExALP->SetLineColor(kBlue+2); grph_nHadAvg_ExALP->SetMarkerColor(kBlue+2); grph_nHadAvg_ExALP->SetMarkerStyle(54); grph_nHadAvg_ExALP->SetLineWidth(2); grph_nHadAvg_ExALP->SetMarkerSize(1.5);
	
	// Import l3
	TDirectory *table_EXP_LL3_NCH = (TDirectory*)input_EXP_LL3->Get("Table 64");
	TGraphAsymmErrors* grph_nHadAvg_ExLL3 = (TGraphAsymmErrors*)table_EXP_LL3_NCH->Get("Graph1D_y1");
	grph_nHadAvg_ExLL3->SetLineColor(kRed+2); grph_nHadAvg_ExLL3->SetMarkerColor(kRed+2); grph_nHadAvg_ExLL3->SetMarkerStyle(53); grph_nHadAvg_ExLL3->SetLineWidth(2); grph_nHadAvg_ExLL3->SetMarkerSize(1.5);
	// Add z-pole 
	int ff = grph_nHadAvg_ExLL3->GetN();
	grph_nHadAvg_ExLL3->SetPoint(ff, 91.2, 20.46);
	grph_nHadAvg_ExLL3->SetPointError(ff, 0.0, 0.0, 0.11, 0.11);
	grph_nHadAvg_ExLL3->Sort();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// AMY graph
	double xbin_nHadAvg_ExAMY[8] = { 50.0, 52.0, 55.0, 56.0, 57.0, 60.0, 60.8, 61.4 };
	double ybin_nHadAvg_ExAMY[8] = { 16.24, 16.74, 16.82, 17.27, 17.49, 17.85, 17.66, 17.61 };
	double yerr_nHadAvg_ExAMY[8] = { 0.41, 0.19, 0.22, 0.16, 0.19, 0.23, 0.23, 0.21 };
	// Construct
	auto grph_nHadAvg_ExAMY = new TGraphErrors(8, xbin_nHadAvg_ExAMY, ybin_nHadAvg_ExAMY, nullptr, yerr_nHadAvg_ExAMY);
	grph_nHadAvg_ExAMY->SetLineColor(kGreen+3); grph_nHadAvg_ExAMY->SetMarkerColor(kGreen+3); grph_nHadAvg_ExAMY->SetMarkerStyle(59); grph_nHadAvg_ExAMY->SetLineWidth(2); grph_nHadAvg_ExAMY->SetMarkerSize(2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// TASSO graph
	double xbin_nHadAvg_ExTAS[4] = { 14.0, 22.0, 34.8, 43.6 };
	double ybin_nHadAvg_ExTAS[4] = { 9.3, 11.3, 13.59, 15.08 };
	double yerr_nHadAvg_ExTAS[4] = { 0.414366987, 0.466904701, 0.460434577, 0.47381431 };
	// Construct
	auto grph_nHadAvg_ExTAS = new TGraphErrors(4, xbin_nHadAvg_ExTAS, ybin_nHadAvg_ExTAS, nullptr, yerr_nHadAvg_ExTAS);
	grph_nHadAvg_ExTAS->SetLineColor(kYellow+2); grph_nHadAvg_ExTAS->SetMarkerColor(kYellow+2); grph_nHadAvg_ExTAS->SetMarkerStyle(55); grph_nHadAvg_ExTAS->SetLineWidth(2); grph_nHadAvg_ExTAS->SetMarkerSize(1.5);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// FCC energy
	double xbin_nHadAvg_Pythi[4] = {91.2, 160.0, 240.0, 365.0};
	// Access pythia bins
	double ybin_nHadAvg_Pythi[4] = {hist_nHadChg_912_Zq->GetMean(),	hist_nHadChg_160_Zq->GetMean(),	hist_nHadChg_240_Zq->GetMean(), hist_nHadChg_365_Zq->GetMean() };
	// Access pythia errors
	double yerr_nHadAvg_Pythi[4] = { hist_nHadChg_912_Zq->GetMeanError(), hist_nHadChg_160_Zq->GetMeanError(), hist_nHadChg_240_Zq->GetMeanError(), hist_nHadChg_365_Zq->GetMeanError()	};
	// Construct pythia graph
	auto grph_nHadAvg_Pythi = new TGraphErrors(4, xbin_nHadAvg_Pythi, ybin_nHadAvg_Pythi, nullptr, yerr_nHadAvg_Pythi);
	grph_nHadAvg_Pythi->SetLineColor(kBlack); grph_nHadAvg_Pythi->SetMarkerColor(kBlack); grph_nHadAvg_Pythi->SetMarkerStyle(20); grph_nHadAvg_Pythi->SetLineWidth(2); grph_nHadAvg_Pythi->SetMarkerSize(1.5);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Theory curve sampling
    const int nPointsTh = 100;
    double xTh[nPointsTh], yTh[nPointsTh];

	// Model parameters
	const double Q0 = 0.202;
	const int    Nf = 5;
	const double Nc = 3.0;
	const double CA = 3.0;
	const double CF = (Nc*Nc - 1.0)/(2.0*Nc);
	const double r0 = CA/CF;
	const double beta0 = 11.0 - (2.0/3.0)*Nf;
	const double beta1 = 102.0 - (38.0/3.0)*Nf;
	const double c = std::sqrt(4.0 * Nc / beta0);

    // Coefficients from Dremlin table
    const auto Cn = coeffs_for_nf(Nf);
    const double r1 = Cn.r1, r2 = Cn.r2, r3 = Cn.r3;
    const double a1 = Cn.a1, a2 = Cn.a2, a3 = Cn.a3;

	// Build the curve vs sqrt(s) from 10 to 400 GeV
	for (int i = 0; i < nPointsTh; ++i) {
		const double Ecm = 10.0 + i * (390.0/(nPointsTh-1));
		xTh[i] = Ecm;

		// y = ln(Q/Q0) with Q = sqrt(s) = Ecm
		const double y = std::log(Ecm / (2*Q0));
		// Guard very low y just in case
		if (y <= 1e-6) { yTh[i] = 0.0; continue; }

		yTh[i] = (1 / r0) * std::pow(y, -a1 * c * c) * std::exp( 2.0 * c * std::sqrt(y) + (c / std::sqrt(y)) * ( r1 + 2.0 * a2 * c * c + (beta1/(beta0*beta0)) * (std::log(2.0*y) + 2.0) ) + (c*c / y) * ( a3*c*c + 0.5*r1*r1 + r2 - a1*(beta1/(beta0*beta0)) * (std::log(2.0*y) + 1.0) ) );
	}
	
    // Construct theory curve
    auto grph_nHadAvg_QCD = new TGraph(nPointsTh, xTh, yTh);

	cout << "K (Charged/Total) : " << hist_nHadChg_912_Zq->GetMean()/hist_nHadAll_912_Zq->GetMean() << endl;
	cout << "K (Charged/Total) : " << hist_nHadChg_160_Zq->GetMean()/hist_nHadAll_160_Zq->GetMean() << endl;
	cout << "K (Charged/Total) : " << hist_nHadChg_240_Zq->GetMean()/hist_nHadAll_240_Zq->GetMean() << endl;
	cout << "K (Charged/Total) : " << hist_nHadChg_365_Zq->GetMean()/hist_nHadAll_365_Zq->GetMean() << endl;

	// Neutral correction
	for (int i = 0; i < grph_nHadAvg_QCD->GetN(); ++i) grph_nHadAvg_QCD->GetY()[i] *= hist_nHadChg_365_Zq->GetMean()/hist_nHadAll_365_Zq->GetMean();

	cout << "K (Pythia/Theory) : " << grph_nHadAvg_Pythi->GetY()[0] / grph_nHadAvg_QCD->Eval(91.2) << endl;

	// LPHD correction
	const double th_at_Z = grph_nHadAvg_QCD->Eval(91.2);
	const double scale = grph_nHadAvg_Pythi->GetY()[0] / th_at_Z;
	for (int i = 0; i < grph_nHadAvg_QCD->GetN(); ++i) grph_nHadAvg_QCD->GetY()[i] *= scale;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Lambda_QCD uncertainty band: vary Q0 = 202 ± 31 MeV
	const double Q0_central = 0.202;
	const double Q0_low  = 0.171; // 202 - 31 MeV
	const double Q0_high = 0.233; // 202 + 31 MeV

	double yLow[nPointsTh], yHigh[nPointsTh];

	for (int i = 0; i < nPointsTh; ++i) {
		const double Ecm = xTh[i];
		auto multPred = [&](double Q0val) {
			double y = std::log(Ecm / (2*Q0val));
			if (y <= 1e-6) return 0.0;
			return (1 / r0) * std::pow(y, -a1 * c * c) *
				std::exp(2.0 * c * std::sqrt(y) +
							(c / std::sqrt(y)) * ( r1 + 2.0 * a2 * c * c + (beta1/(beta0*beta0)) * (std::log(2.0*y) + 2.0) ) +
							(c*c / y) * ( a3*c*c + 0.5*r1*r1 + r2 - a1*(beta1/(beta0*beta0)) * (std::log(2.0*y) + 1.0) ));
		};
		yLow[i]  = multPred(Q0_high); // smaller Λ → smaller y → higher multiplicity
		yHigh[i] = multPred(Q0_low);  // larger Λ → larger y → lower multiplicity
	}

	// Apply same neutral + LPHD scaling to the bounds
	for (int i = 0; i < nPointsTh; ++i) {
		yLow[i]  *= hist_nHadChg_365_Zq->GetMean()/hist_nHadAll_365_Zq->GetMean() * scale;
		yHigh[i] *= hist_nHadChg_365_Zq->GetMean()/hist_nHadAll_365_Zq->GetMean() * scale;
	}

	// Build band graph
	TGraph* grph_nHadAvg_QCD_low  = new TGraph(nPointsTh, xTh, yLow);
	TGraph* grph_nHadAvg_QCD_high = new TGraph(nPointsTh, xTh, yHigh);

	auto grph_band = new TGraph(2*nPointsTh);
	for (int i = 0; i < nPointsTh; ++i) {
		grph_band->SetPoint(i, xTh[i], yLow[i]);
		grph_band->SetPoint(nPointsTh + i, xTh[nPointsTh - 1 - i], yHigh[nPointsTh - 1 - i]);
	}

	// Style and draw band
	grph_band->SetFillColorAlpha(kBlack, 0.1);
	// grph_band->SetLineColor(0);
	// grph_nHadAvg_QCD->SetLineColor(kBlack);
	grph_nHadAvg_QCD->SetLineWidth(2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Create canvas
	TCanvas* cv4 = new TCanvas("cv4", "FCC-ee ISR Studies", 800, 850);

	// Add legend
	TLegend *lg4 = new TLegend(0.70, 0.15, 0.90, 0.43);
	lg4->AddEntry(grph_nHadAvg_Pythi, "PYTHIA", "P");
	lg4->AddEntry(grph_nHadAvg_ExALP, "ALEPH", "P");
	lg4->AddEntry(grph_nHadAvg_ExLL3, "L3", "P");
	lg4->AddEntry(grph_nHadAvg_ExAMY, "AMY", "P");
	lg4->AddEntry(grph_nHadAvg_ExTAS, "TASSO", "P");
	lg4->AddEntry(grph_nHadAvg_QCD, "3NLO", "L");
	lg4->SetTextSize(0.04);

	// Beautify
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv4->SetMargin(0, 0, 0, 0);
	gPad->SetTopMargin(0.025);
	gPad->SetBottomMargin(0.09);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.05);
	gPad->SetTickx(); gPad->SetTicky();

	// Beautify
	grph_nHadAvg_Pythi->GetXaxis()->CenterTitle(); grph_nHadAvg_Pythi->GetYaxis()->CenterTitle();
	grph_nHadAvg_Pythi->GetXaxis()->SetLabelSize(0.04); grph_nHadAvg_Pythi->GetXaxis()->SetTitleSize(0.04);
	grph_nHadAvg_Pythi->GetYaxis()->SetLabelSize(0.04); grph_nHadAvg_Pythi->GetYaxis()->SetTitleSize(0.04);
	grph_nHadAvg_Pythi->SetTitle("");
	grph_nHadAvg_Pythi->GetYaxis()->SetTitle("<N_{ch}>");
	grph_nHadAvg_Pythi->GetXaxis()->SetTitle("#sqrt{s} (GeV)");

	// Draw
	grph_nHadAvg_Pythi->Draw("AP");
	grph_nHadAvg_QCD->Draw("L SAME");
	grph_band->Draw("F SAME");
	grph_nHadAvg_Pythi->Draw("P SAME");
	grph_nHadAvg_ExALP->Draw("PE SAME");
	grph_nHadAvg_ExLL3->Draw("PE SAME");
	grph_nHadAvg_ExAMY->Draw("PE SAME");
	grph_nHadAvg_ExTAS->Draw("PE SAME");
	lg4->Draw("SAME");

	// Set limits
	grph_nHadAvg_Pythi->GetYaxis()->SetRangeUser(0,40);
	grph_nHadAvg_Pythi->GetXaxis()->SetLimits(0, 400);

	// Update canvas
	cv4->Modified();

}