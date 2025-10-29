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

	TH1F *hist_nHadron_912_Zq = (TH1F*)input_912->Get("hist_nHadron_Zq");
	hist_nHadron_912_Zq->SetLineColor(kBlue+2); hist_nHadron_912_Zq->SetMarkerColor(kBlue+2); hist_nHadron_912_Zq->SetMarkerStyle(26); hist_nHadron_912_Zq->SetLineWidth(2); hist_nHadron_912_Zq->SetMarkerSize(2);
	TH1F *hist_nHadron_160_Zq = (TH1F*)input_160->Get("hist_nHadron_Zq");
	hist_nHadron_160_Zq->SetLineColor(kYellow+2); hist_nHadron_160_Zq->SetMarkerColor(kYellow+2); hist_nHadron_160_Zq->SetMarkerStyle(26); hist_nHadron_160_Zq->SetLineWidth(2); hist_nHadron_160_Zq->SetMarkerSize(2);
	TH1F *hist_nHadron_240_Zq = (TH1F*)input_240->Get("hist_nHadron_Zq");
	hist_nHadron_240_Zq->SetLineColor(kGreen+2); hist_nHadron_240_Zq->SetMarkerColor(kGreen+2); hist_nHadron_240_Zq->SetMarkerStyle(26); hist_nHadron_240_Zq->SetLineWidth(2); hist_nHadron_240_Zq->SetMarkerSize(2);

	TH1F* hist_nHadron_365_al = (TH1F*)input_365->Get("hist_nHadron");
	hist_nHadron_365_al->SetLineColor(kBlack); hist_nHadron_365_al->SetMarkerColor(kBlack); hist_nHadron_365_al->SetMarkerStyle(21); hist_nHadron_365_al->SetLineWidth(2); hist_nHadron_365_al->SetMarkerSize(1);
	TH1F* hist_nHadron_365_Zq = (TH1F*)input_365->Get("hist_nHadron_Zq");
	hist_nHadron_365_Zq->SetLineColor(kRed+2); hist_nHadron_365_Zq->SetMarkerColor(kRed+1); hist_nHadron_365_Zq->SetMarkerStyle(21); hist_nHadron_365_Zq->SetLineWidth(2); hist_nHadron_365_Zq->SetMarkerSize(1);
	TH1F* hist_nHadron_365_WW = (TH1F*)input_365->Get("hist_nHadron_WW");
	hist_nHadron_365_WW->SetLineColor(kGreen+2); hist_nHadron_365_WW->SetMarkerColor(kGreen+1); hist_nHadron_365_WW->SetMarkerStyle(21); hist_nHadron_365_WW->SetLineWidth(2); hist_nHadron_365_WW->SetMarkerSize(1);
	TH1F* hist_nHadron_365_ZZ = (TH1F*)input_365->Get("hist_nHadron_ZZ");
	hist_nHadron_365_ZZ->SetLineColor(kBlue+2); hist_nHadron_365_ZZ->SetMarkerColor(kBlue+1); hist_nHadron_365_ZZ->SetMarkerStyle(21); hist_nHadron_365_ZZ->SetLineWidth(2); hist_nHadron_365_ZZ->SetMarkerSize(1);
	TH1F* hist_nHadron_365_tt = (TH1F*)input_365->Get("hist_nHadron_tt");
	hist_nHadron_365_tt->SetLineColor(kYellow+2); hist_nHadron_365_tt->SetMarkerColor(kYellow+1); hist_nHadron_365_tt->SetMarkerStyle(21); hist_nHadron_365_tt->SetLineWidth(2); hist_nHadron_365_tt->SetMarkerSize(1);
	TH1F* hist_nHadron_365_HZ = (TH1F*)input_365->Get("hist_nHadron_HZ");
	hist_nHadron_365_HZ->SetLineColor(kMagenta+2); hist_nHadron_365_HZ->SetMarkerColor(kMagenta+1); hist_nHadron_365_HZ->SetMarkerStyle(21); hist_nHadron_365_HZ->SetLineWidth(2); hist_nHadron_365_HZ->SetMarkerSize(1);
	TH1F* hist_nHadron_365_HW = (TH1F*)input_365->Get("hist_nHadron_HW");
	hist_nHadron_365_HW->SetLineColor(kCyan+2); hist_nHadron_365_HW->SetMarkerColor(kCyan+1); hist_nHadron_365_HW->SetMarkerStyle(21); hist_nHadron_365_HW->SetLineWidth(2); hist_nHadron_365_HW->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_nHadron_912_Zq->SetStats(kFALSE);
	hist_nHadron_365_al->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv1 = new TCanvas("cv1", "FCC-ee ISR Studies", 800, 700);

	// // Add legend
	// TLegend *lg1 = new TLegend(0.77, 0.75, 0.95, 0.95);
	// lg1->AddEntry(hist_nHadron_912_Zq, "91.2 GeV", "PL");
	// lg1->AddEntry(hist_nHadron_160_Zq, "160 GeV", "PL");
	// lg1->AddEntry(hist_nHadron_240_Zq, "240 GeV", "PL");
	// lg1->AddEntry(hist_nHadron_365_Zq, "365 GeV", "PL");
	// lg1->SetTextSize(0.04);

	// // Beautify
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv1->SetMargin(0, 0, 0, 0); 
	// gPad->SetTopMargin(0.025);
	// gPad->SetBottomMargin(0.12);
	// gPad->SetLeftMargin(0.15);
	// gPad->SetRightMargin(0.02);
	// gPad->SetTickx(); gPad->SetTicky();
	// gPad->SetLogy();

	// // Beautify
	// hist_nHadron_912_Zq->GetXaxis()->SetLabelSize(0.05); hist_nHadron_912_Zq->GetXaxis()->SetTitleSize(0.05);
	// hist_nHadron_912_Zq->GetYaxis()->SetLabelSize(0.05); hist_nHadron_912_Zq->GetYaxis()->SetTitleSize(0.05);
	// hist_nHadron_912_Zq->SetTitle("");
	// hist_nHadron_912_Zq->GetYaxis()->SetTitle("P(N_{Ch})");

	// // Beautify
	// hist_nHadron_912_Zq->SetLineColor(kBlack); hist_nHadron_912_Zq->SetMarkerColor(kBlack); hist_nHadron_912_Zq->SetMarkerStyle(20); hist_nHadron_912_Zq->SetLineWidth(1); hist_nHadron_912_Zq->SetMarkerSize(1.2);
	// hist_nHadron_160_Zq->SetLineColor(kBlack); hist_nHadron_160_Zq->SetMarkerColor(kBlack); hist_nHadron_160_Zq->SetMarkerStyle(47); hist_nHadron_160_Zq->SetLineWidth(1); hist_nHadron_160_Zq->SetMarkerSize(1.2);
	// hist_nHadron_240_Zq->SetLineColor(kBlack); hist_nHadron_240_Zq->SetMarkerColor(kBlack); hist_nHadron_240_Zq->SetMarkerStyle(22); hist_nHadron_240_Zq->SetLineWidth(1); hist_nHadron_240_Zq->SetMarkerSize(1.2);
	// hist_nHadron_365_Zq->SetLineColor(kBlack); hist_nHadron_365_Zq->SetMarkerColor(kBlack); hist_nHadron_365_Zq->SetMarkerStyle(33); hist_nHadron_365_Zq->SetLineWidth(1); hist_nHadron_365_Zq->SetMarkerSize(1.5);

	// // Normalise
	// hist_nHadron_912_Zq->Scale(1.0/hist_nHadron_912_Zq->Integral());
	// hist_nHadron_160_Zq->Scale(1.0/hist_nHadron_160_Zq->Integral());
	// hist_nHadron_240_Zq->Scale(1.0/hist_nHadron_240_Zq->Integral());
	// hist_nHadron_365_Zq->Scale(1.0/hist_nHadron_365_Zq->Integral());

	// // hist_nHadron_912_Zq->Rebin(2);
	// // hist_nHadron_160_Zq->Rebin(2);
	// // hist_nHadron_240_Zq->Rebin(2);
	// // hist_nHadron_365_Zq->Rebin(2);

	// // Draw
	// hist_nHadron_912_Zq->Draw("P");
	// hist_nHadron_160_Zq->Draw("P SAME");
	// hist_nHadron_240_Zq->Draw("P SAME");
	// hist_nHadron_365_Zq->Draw("P SAME");
	// lg1->Draw("SAME");

	// // Set limits
	// hist_nHadron_912_Zq->GetYaxis()->SetRangeUser(1,2E-1);
	// hist_nHadron_912_Zq->GetXaxis()->SetRangeUser(0,90);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv1->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 800, 700);

	// // Add legend
	// TLegend* lg2 = new TLegend(0.75, 0.64, 0.92, 0.95);
	// lg2->AddEntry(hist_nHadron_365_al, "ee#rightarrowq#bar{q}", "P");
	// lg2->AddEntry(hist_nHadron_365_Zq, "ee#rightarrow#gamma/Z", "P");
	// lg2->AddEntry(hist_nHadron_365_ZZ, "ee#rightarrowZZ", "P");
	// lg2->AddEntry(hist_nHadron_365_WW, "ee#rightarrowWW", "P");
	// lg2->AddEntry(hist_nHadron_365_tt, "ee#rightarrowt#bar{t}", "P");
	// lg2->AddEntry(hist_nHadron_365_HZ, "ee#rightarrowZH", "P");
	// lg2->AddEntry(hist_nHadron_365_HW, "ee#rightarrow#nu#bar{#nu}H", "P");
	// lg2->SetTextSize(0.04);

	// // Beautify
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv2->SetMargin(0, 0, 0, 0); 
	// gPad->SetTopMargin(0.025);
	// gPad->SetBottomMargin(0.12);
	// gPad->SetLeftMargin(0.12);
	// gPad->SetRightMargin(0.04);
	// gPad->SetTickx(); gPad->SetTicky();
	// gPad->SetLogy();

	// // Beautify
	// hist_nHadron_365_al->GetXaxis()->SetLabelSize(0.05); hist_nHadron_365_al->GetXaxis()->SetTitleSize(0.05);
	// hist_nHadron_365_al->GetYaxis()->SetLabelSize(0.05); hist_nHadron_365_al->GetYaxis()->SetTitleSize(0.05);
	// hist_nHadron_365_al->SetTitle("");
	// hist_nHadron_365_al->GetYaxis()->SetTitle("#");

	// hist_nHadron_365_al->SetFillStyle(3001); hist_nHadron_365_al->SetFillColor(kBlack); 
	// hist_nHadron_365_Zq->SetFillStyle(3001); hist_nHadron_365_Zq->SetFillColor(kRed);
	// hist_nHadron_365_WW->SetFillStyle(3001); hist_nHadron_365_WW->SetFillColor(kGreen); 
	// hist_nHadron_365_ZZ->SetFillStyle(3001); hist_nHadron_365_ZZ->SetFillColor(kBlue); 
	// hist_nHadron_365_tt->SetFillStyle(3001); hist_nHadron_365_tt->SetFillColor(kYellow); 
	// hist_nHadron_365_HZ->SetFillStyle(3001); hist_nHadron_365_HZ->SetFillColor(kMagenta+1); 
	// hist_nHadron_365_HW->SetFillStyle(3001); hist_nHadron_365_HW->SetFillColor(kCyan+1); 

	// // Draw
	// hist_nHadron_365_al->Draw("HIST");
	// hist_nHadron_365_Zq->Draw("HIST SAME");
	// hist_nHadron_365_WW->Draw("HIST SAME");
	// hist_nHadron_365_ZZ->Draw("HIST SAME");
	// hist_nHadron_365_tt->Draw("HIST SAME");
	// hist_nHadron_365_HZ->Draw("HIST SAME");
	// hist_nHadron_365_HW->Draw("HIST SAME");

	// lg2->Draw("SAME");

	// // Set limits
	// hist_nHadron_365_al->GetYaxis()->SetRangeUser(2,1E6);
	// hist_nHadron_365_al->GetXaxis()->SetRangeUser(0,120);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv2->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Import aleph
	TDirectory *table_EXP_ALP_NCH = (TDirectory*)input_EXP_ALP->Get("Table 1");
	TGraphAsymmErrors* grph_nHadAvg_ExALP = (TGraphAsymmErrors*)table_EXP_ALP_NCH->Get("Graph1D_y1");
	grph_nHadAvg_ExALP->SetLineColor(kBlue+2); grph_nHadAvg_ExALP->SetMarkerColor(kBlue+2); grph_nHadAvg_ExALP->SetMarkerStyle(53); grph_nHadAvg_ExALP->SetLineWidth(2); grph_nHadAvg_ExALP->SetMarkerSize(1);
	
	// Import l3
	TDirectory *table_EXP_LL3_NCH = (TDirectory*)input_EXP_LL3->Get("Table 64");
	TGraphAsymmErrors* grph_nHadAvg_ExLL3 = (TGraphAsymmErrors*)table_EXP_LL3_NCH->Get("Graph1D_y1");
	grph_nHadAvg_ExLL3->SetLineColor(kRed+2); grph_nHadAvg_ExLL3->SetMarkerColor(kRed+2); grph_nHadAvg_ExLL3->SetMarkerStyle(53); grph_nHadAvg_ExLL3->SetLineWidth(2); grph_nHadAvg_ExLL3->SetMarkerSize(1);
	// Add z-pole 
	int ff = grph_nHadAvg_ExLL3->GetN();
	grph_nHadAvg_ExLL3->SetPoint(ff, 91.2, 20.46);
	grph_nHadAvg_ExLL3->SetPointError(ff, 0.0, 0.0, 0.11, 0.11);
	grph_nHadAvg_ExLL3->Sort();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// AMY graph
	double xbin_ZetaSta_ExAMY[8] = { 50.0, 52.0, 55.0, 56.0, 57.0, 60.0, 60.8, 61.4 };
	double ybin_ZetaSta_ExAMY[8] = { 16.24, 16.74, 16.82, 17.27, 17.49, 17.85, 17.66, 17.61 };
	double yerr_ZetaSta_ExAMY[8] = { 0.41, 0.19, 0.22, 0.16, 0.19, 0.23, 0.23, 0.21 };
	// Construct
	auto grph_ZetaSta_ExAMY = new TGraphErrors(8, xbin_ZetaSta_ExAMY, ybin_ZetaSta_ExAMY, nullptr, yerr_ZetaSta_ExAMY);
	grph_ZetaSta_ExAMY->SetLineColor(kGreen+2); grph_ZetaSta_ExAMY->SetMarkerColor(kGreen+2); grph_ZetaSta_ExAMY->SetMarkerStyle(53); grph_ZetaSta_ExAMY->SetLineWidth(2); grph_ZetaSta_ExAMY->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// TASSO graph
	double xbin_ZetaSta_ExTAS[4] = { 14.0, 22.0, 34.8, 43.6 };
	double ybin_ZetaSta_ExTAS[4] = { 9.3, 11.3, 13.59, 15.08 };
	double yerr_ZetaSta_ExTAS[4] = { 0.414366987, 0.466904701, 0.460434577, 0.47381431 };
	// Construct
	auto grph_ZetaSta_ExTAS = new TGraphErrors(4, xbin_ZetaSta_ExTAS, ybin_ZetaSta_ExTAS, nullptr, yerr_ZetaSta_ExTAS);
	grph_ZetaSta_ExTAS->SetLineColor(kYellow+2); grph_ZetaSta_ExTAS->SetMarkerColor(kYellow+2); grph_ZetaSta_ExTAS->SetMarkerStyle(53); grph_ZetaSta_ExTAS->SetLineWidth(2); grph_ZetaSta_ExTAS->SetMarkerSize(1);

	// FCC energy
	double xbin_nHadAvg_Pythi[4] = {91.2, 160.0, 240.0, 365.0};
	// Access pythia bins
	double ybin_nHadAvg_Pythi[4] = {hist_nHadron_912_Zq->GetMean(),	hist_nHadron_160_Zq->GetMean(),	hist_nHadron_240_Zq->GetMean(), hist_nHadron_365_Zq->GetMean() };
	// Access pythia errors
	double yerr_nHadAvg_Pythi[4] = { hist_nHadron_912_Zq->GetMeanError(), hist_nHadron_160_Zq->GetMeanError(), hist_nHadron_240_Zq->GetMeanError(), hist_nHadron_365_Zq->GetMeanError()	};
	// Construct pythia graph
	auto grph_nHadAvg_Pythi = new TGraphErrors(4, xbin_nHadAvg_Pythi, ybin_nHadAvg_Pythi, nullptr, yerr_nHadAvg_Pythi);
	grph_nHadAvg_Pythi->SetLineColor(kBlack); grph_nHadAvg_Pythi->SetMarkerColor(kBlack); grph_nHadAvg_Pythi->SetMarkerStyle(20); grph_nHadAvg_Pythi->SetLineWidth(2); grph_nHadAvg_Pythi->SetMarkerSize(1.5);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // --- Theoretical curve (3NLO) ---
    const int nPointsTh = 100;
    double xTh[nPointsTh], yTh[nPointsTh];

    // Model parameters
    const double Q0 = 0.25;           
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
		const double Ecm = 10.0 + i * (390.0/(nPointsTh-1)); // 10..400
		xTh[i] = Ecm;

		// y = ln(Q/Q0) with Q = sqrt(s) = Ecm
		const double y = std::log(Ecm / (2*Q0));
		// Guard very low y just in case
		if (y <= 1e-6) { yTh[i] = 0.0; continue; }

		yTh[i] = (1 / r0) * std::pow(y, -a1 * c * c) *
				std::exp( 2.0 * c * std::sqrt(y) + (c / std::sqrt(y)) * ( r1 + 2.0 * a2 * c * c + (beta1/(beta0*beta0)) * (std::log(2.0*y) + 2.0) ) + (c*c / y) * ( a3*c*c + 0.5*r1*r1 + r2 - a1*(beta1/(beta0*beta0)) * (std::log(2.0*y) + 1.0) ) );
	}

    // Construct theory curve
    auto grph_nHadAvg_QCD = new TGraph(nPointsTh, xTh, yTh);
    grph_nHadAvg_QCD->SetLineWidth(3); grph_nHadAvg_QCD->SetLineStyle(7);

    // Normalise theory to PYTHIA 
    const double th_at_Z = grph_nHadAvg_QCD->Eval(91.2);
    if (th_at_Z > 0) {
        const double scale = grph_nHadAvg_Pythi->GetY()[0] / th_at_Z;
        for (int i = 0; i < grph_nHadAvg_QCD->GetN(); ++i) grph_nHadAvg_QCD->GetY()[i] *= scale;            
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Create canvas
	TCanvas* cv4 = new TCanvas("cv4", "FCC-ee ISR Studies", 800, 600);

	// Add legend
	TLegend *lg4 = new TLegend(0.77, 0.18, 0.90, 0.50);
	lg4->AddEntry(grph_nHadAvg_Pythi, "PYTHIA", "P");
	lg4->AddEntry(grph_nHadAvg_ExALP, "ALEPH", "P");
	lg4->AddEntry(grph_nHadAvg_ExLL3, "L3", "P");
	lg4->AddEntry(grph_ZetaSta_ExAMY, "AMY", "P");
	lg4->AddEntry(grph_ZetaSta_ExTAS, "TASSO", "P");
	lg4->AddEntry(grph_nHadAvg_QCD, "3NLO", "L");
	lg4->SetTextSize(0.04);

	// Beautify
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv4->SetMargin(0, 0, 0, 0);
	gPad->SetTopMargin(0.025);
	gPad->SetBottomMargin(0.12);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.04);
	gPad->SetTickx(); gPad->SetTicky();

	// Beautify
	grph_nHadAvg_Pythi->GetXaxis()->SetLabelSize(0.05); grph_nHadAvg_Pythi->GetXaxis()->SetTitleSize(0.05);
	grph_nHadAvg_Pythi->GetYaxis()->SetLabelSize(0.05); grph_nHadAvg_Pythi->GetYaxis()->SetTitleSize(0.05);
	grph_nHadAvg_Pythi->SetTitle("");
	grph_nHadAvg_Pythi->GetYaxis()->SetTitle("<N_{ch}>");
	grph_nHadAvg_Pythi->GetXaxis()->SetTitle("#sqrt{s} (GeV)");

	// Draw
	grph_nHadAvg_Pythi->Draw("AP");
	grph_nHadAvg_ExALP->Draw("PE SAME");
	grph_nHadAvg_ExLL3->Draw("PE SAME");
	grph_ZetaSta_ExAMY->Draw("PE SAME");
	grph_ZetaSta_ExTAS->Draw("PE SAME");
	grph_nHadAvg_QCD->Draw("L SAME");
	lg4->Draw("SAME");

	// Set limits
	grph_nHadAvg_Pythi->GetYaxis()->SetRangeUser(0,40);
	grph_nHadAvg_Pythi->GetXaxis()->SetLimits(0, 400);

	// Update canvas
	cv4->Modified();

}