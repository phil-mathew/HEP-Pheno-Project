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

// Code
void ImpactofXi() {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_EXPDATA = TFile::Open("3-LEPdata/EXPDATA.root");
	TFile *input_EXP_ALP = TFile::Open("3-LEPdata/EXP_ALP.root");
	TFile *input_EXP_LL3 = TFile::Open("3-LEPdata/EXP_LL3.root");
	TFile *input_EXP_TAS = TFile::Open("3-LEPdata/EXP_TAS.root");

	TFile *input_912 = new TFile("5-CutData/cut_FCC912.root", "READ");
	TFile *input_160 = new TFile("5-CutData/cut_FCC160.root", "READ");
	TFile *input_240 = new TFile("5-CutData/cut_FCC240.root", "READ");
	TFile *input_365 = new TFile("5-CutData/cut_FCC365.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F *hist_ZetaChg_912 = (TH1F*)input_912->Get("hist_ZetaChg");
	hist_ZetaChg_912->SetLineColor(kBlue+2); hist_ZetaChg_912->SetMarkerColor(kBlue+2); hist_ZetaChg_912->SetMarkerStyle(53); hist_ZetaChg_912->SetLineWidth(2); hist_ZetaChg_912->SetMarkerSize(1);
	TH1F *hist_ZetaChg_160 = (TH1F*)input_160->Get("hist_ZetaChg");
	hist_ZetaChg_160->SetLineColor(kRed+2); hist_ZetaChg_160->SetMarkerColor(kRed+2); hist_ZetaChg_160->SetMarkerStyle(53); hist_ZetaChg_160->SetLineWidth(2); hist_ZetaChg_160->SetMarkerSize(1);
	TH1F *hist_ZetaChg_240 = (TH1F*)input_240->Get("hist_ZetaChg");
	hist_ZetaChg_240->SetLineColor(kYellow+2); hist_ZetaChg_240->SetMarkerColor(kYellow+2); hist_ZetaChg_240->SetMarkerStyle(53); hist_ZetaChg_240->SetLineWidth(2); hist_ZetaChg_240->SetMarkerSize(1);
	TH1F *hist_ZetaChg_365 = (TH1F*)input_365->Get("hist_ZetaChg");
	hist_ZetaChg_365->SetLineColor(kGreen+2); hist_ZetaChg_365->SetMarkerColor(kGreen+2); hist_ZetaChg_365->SetMarkerStyle(53); hist_ZetaChg_365->SetLineWidth(2); hist_ZetaChg_365->SetMarkerSize(1);

	TH1F *hist_ZetaAll_912 = (TH1F*)input_912->Get("hist_ZetaAll");
	hist_ZetaAll_912->SetLineColor(kBlue+2); hist_ZetaAll_912->SetMarkerColor(kBlue+2); hist_ZetaAll_912->SetMarkerStyle(53); hist_ZetaAll_912->SetLineWidth(2); hist_ZetaAll_912->SetMarkerSize(1);
	TH1F *hist_ZetaAll_160 = (TH1F*)input_160->Get("hist_ZetaAll");
	hist_ZetaAll_160->SetLineColor(kRed+2); hist_ZetaAll_160->SetMarkerColor(kRed+2); hist_ZetaAll_160->SetMarkerStyle(53); hist_ZetaAll_160->SetLineWidth(2); hist_ZetaAll_160->SetMarkerSize(1);
	TH1F *hist_ZetaAll_240 = (TH1F*)input_240->Get("hist_ZetaAll");
	hist_ZetaAll_240->SetLineColor(kYellow+2); hist_ZetaAll_240->SetMarkerColor(kYellow+2); hist_ZetaAll_240->SetMarkerStyle(53); hist_ZetaAll_240->SetLineWidth(2); hist_ZetaAll_240->SetMarkerSize(1);
	TH1F *hist_ZetaAll_365 = (TH1F*)input_365->Get("hist_ZetaAll");
	hist_ZetaAll_365->SetLineColor(kGreen+2); hist_ZetaAll_365->SetMarkerColor(kGreen+2); hist_ZetaAll_365->SetMarkerStyle(53); hist_ZetaAll_365->SetLineWidth(2); hist_ZetaAll_365->SetMarkerSize(1);

	TDirectory *table_EXP_TAS = (TDirectory*)input_EXP_TAS->Get("Table 4");
	TGraphAsymmErrors* grph_ZetaChg_014 = (TGraphAsymmErrors*)table_EXP_TAS->Get("Graph1D_y1");
	TGraphAsymmErrors* grph_ZetaChg_022 = (TGraphAsymmErrors*)table_EXP_TAS->Get("Graph1D_y2");
	TGraphAsymmErrors* grph_ZetaChg_035 = (TGraphAsymmErrors*)table_EXP_TAS->Get("Graph1D_y3");
	TGraphAsymmErrors* grph_ZetaChg_044 = (TGraphAsymmErrors*)table_EXP_TAS->Get("Graph1D_y4");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << hist_ZetaChg_365->GetMean() << " " << hist_ZetaAll_365->GetMean() << " " << hist_ZetaAll_365->GetMean()/hist_ZetaChg_365->GetMean() << endl;
	cout << hist_ZetaChg_240->GetMean() << " " << hist_ZetaAll_240->GetMean() << " " << hist_ZetaAll_240->GetMean()/hist_ZetaChg_240->GetMean() << endl;
	cout << hist_ZetaChg_160->GetMean() << " " << hist_ZetaAll_160->GetMean() << " " << hist_ZetaAll_160->GetMean()/hist_ZetaChg_160->GetMean() << endl;
	cout << hist_ZetaChg_912->GetMean() << " " << hist_ZetaAll_912->GetMean() << " " << hist_ZetaAll_912->GetMean()/hist_ZetaChg_912->GetMean() << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ZetaChg_912->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fit ξ distributions for ξ*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ZetaChg_912->Scale(1.0/50,"width");
	hist_ZetaChg_160->Scale(1.0/50,"width");
	hist_ZetaChg_240->Scale(1.0/50,"width");
	hist_ZetaChg_365->Scale(1.0/50,"width");

	hist_ZetaAll_912->Scale(1.0/50,"width");
	hist_ZetaAll_160->Scale(1.0/50,"width");
	hist_ZetaAll_240->Scale(1.0/50,"width");
	hist_ZetaAll_365->Scale(1.0/50,"width");

	cout << hist_ZetaChg_365->GetMean() << " " << hist_ZetaAll_365->GetMean() << " " << hist_ZetaAll_365->GetMean()/hist_ZetaChg_365->GetMean() << endl;
	cout << hist_ZetaChg_240->GetMean() << " " << hist_ZetaAll_240->GetMean() << " " << hist_ZetaAll_240->GetMean()/hist_ZetaChg_240->GetMean() << endl;
	cout << hist_ZetaChg_160->GetMean() << " " << hist_ZetaAll_160->GetMean() << " " << hist_ZetaAll_160->GetMean()/hist_ZetaChg_160->GetMean() << endl;
	cout << hist_ZetaChg_912->GetMean() << " " << hist_ZetaAll_912->GetMean() << " " << hist_ZetaAll_912->GetMean()/hist_ZetaChg_912->GetMean() << endl;

	TF1 *hist_fitZeta_912 = new TF1("hist_fitZeta_912", "gaus", 2.6, 4.4);
	hist_fitZeta_912->SetLineColor(kBlue+3); hist_fitZeta_912->SetLineWidth(2); hist_fitZeta_912->SetLineStyle(7);
	hist_ZetaChg_912->Fit(hist_fitZeta_912, "RNQ MINOS");

	TF1 *hist_fitZeta_160 = new TF1("hist_fitZeta_160", "gaus", 3.0, 5.0);
	hist_fitZeta_160->SetLineColor(kRed+3); hist_fitZeta_160->SetLineWidth(2); hist_fitZeta_160->SetLineStyle(7);
	hist_ZetaChg_160->Fit(hist_fitZeta_160, "RNQ MINOS");

	TF1 *hist_fitZeta_240 = new TF1("hist_fitZeta_240", "gaus", 3.2, 5.6);
	hist_fitZeta_240->SetLineColor(kYellow+3); hist_fitZeta_240->SetLineWidth(2); hist_fitZeta_240->SetLineStyle(7);
	hist_ZetaChg_240->Fit(hist_fitZeta_240, "RNQ MINOS");

	TF1 *hist_fitZeta_365 = new TF1("hist_fitZeta_365", "gaus", 3.2, 6.2);
	hist_fitZeta_365->SetLineColor(kGreen+3); hist_fitZeta_365->SetLineWidth(2); hist_fitZeta_365->SetLineStyle(7);
	hist_ZetaChg_365->Fit(hist_fitZeta_365, "RNQ MINOS");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TF1 *hist_fitZeta_014 = new TF1("hist_fitZeta_014", "gaus", 1.0, 3.5);
	grph_ZetaChg_014->Fit(hist_fitZeta_014, "RNQ MINUIT");
	TF1 *hist_fitZeta_022 = new TF1("hist_fitZeta_022", "gaus", 1.0, 3.5);
	grph_ZetaChg_022->Fit(hist_fitZeta_022, "RNQ MINOS");
	TF1 *hist_fitZeta_035 = new TF1("hist_fitZeta_035", "gaus", 1.0, 3.5);
	grph_ZetaChg_035->Fit(hist_fitZeta_035, "RNQ MINOS");
	TF1 *hist_fitZeta_044 = new TF1("hist_fitZeta_044", "gaus", 1.0, 3.5);
	grph_ZetaChg_044->Fit(hist_fitZeta_044, "RNQ MINOS");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv3 = new TCanvas("cv3", "FCC-ee ISR Studies", 800, 600);

	// Add legend
	TLegend *lg3 = new TLegend(0.80, 0.75, 0.95, 0.95);
	lg3->AddEntry(hist_ZetaChg_912, "91.2 GeV", "P");
	lg3->AddEntry(hist_ZetaChg_160, "160 GeV", "P");
	lg3->AddEntry(hist_ZetaChg_240, "240 GeV", "P");
	lg3->AddEntry(hist_ZetaChg_365, "365 GeV", "P");
	lg3->SetTextSize(0.04);

	// Beautify
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv3->SetMargin(0, 0, 0, 0);
	gPad->SetTopMargin(0.025);
	gPad->SetBottomMargin(0.12);
	gPad->SetLeftMargin(0.12);
	gPad->SetRightMargin(0.02);
	gPad->SetTickx(); gPad->SetTicky();

	// Beautify
	hist_ZetaChg_912->GetXaxis()->SetLabelSize(0.05); hist_ZetaChg_912->GetXaxis()->SetTitleSize(0.05);
	hist_ZetaChg_912->GetYaxis()->SetLabelSize(0.05); hist_ZetaChg_912->GetYaxis()->SetTitleSize(0.05);
	hist_ZetaChg_912->SetTitle("");
	hist_ZetaChg_912->GetYaxis()->SetTitle("1/#sigma_{had} d#sigma_{ch}/d#xi");

	// Draw
	hist_ZetaChg_912->Draw("P");
	hist_ZetaChg_160->Draw("P SAME");
	hist_ZetaChg_240->Draw("P SAME");
	hist_ZetaChg_365->Draw("P SAME");
	hist_fitZeta_912->Draw("SAME");
	hist_fitZeta_160->Draw("SAME");
	hist_fitZeta_240->Draw("SAME");
	hist_fitZeta_365->Draw("SAME");
	lg3->Draw("SAME");

	// Set limits
	hist_ZetaChg_912->GetYaxis()->SetRangeUser(0,8);
	hist_ZetaChg_912->GetXaxis()->SetRangeUser(0,8);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv3->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv5 = new TCanvas("cv5", "FCC-ee ISR Studies", 800, 600);

	// Import aleph
	TDirectory *table_EXP_ALP_ZET = (TDirectory*)input_EXP_ALP->Get("Table 10");

	// Pythia graph
	double xbin_ZetaAvg_Pythi[4] = { 91.2, 160.0, 240.0, 365.0 };
	double ybin_ZetaAvg_Pythi[4] = { hist_fitZeta_912->GetParameter(1), hist_fitZeta_160->GetParameter(1), hist_fitZeta_240->GetParameter(1), hist_fitZeta_365->GetParameter(1)	};
	double yerr_ZetaAvg_Pythi[4] = { hist_fitZeta_912->GetParError(1), hist_fitZeta_160->GetParError(1), hist_fitZeta_240->GetParError(1), hist_fitZeta_365->GetParError(1) };
	// Construct
	auto grph_ZetaAvg_Pythi = new TGraphErrors(4, xbin_ZetaAvg_Pythi, ybin_ZetaAvg_Pythi, nullptr, yerr_ZetaAvg_Pythi);
	grph_ZetaAvg_Pythi->SetLineColor(kBlack); grph_ZetaAvg_Pythi->SetMarkerColor(kBlack); grph_ZetaAvg_Pythi->SetMarkerStyle(20); grph_ZetaAvg_Pythi->SetLineWidth(2); grph_ZetaAvg_Pythi->SetMarkerSize(1);

	// ALEPH graph
	double xbin_ZetaAvg_ExALP[9] = { 91.2, 133, 161, 172, 183, 189, 196, 200, 206};
	double ybin_ZetaAvg_ExALP[9] = { 3.66, 3.941, 4.05, 4.035, 4.116, 4.071, 4.137, 4.155, 4.127 };
	double yerr_ZetaAvg_ExALP[9] = { 0.01603122, 0.035, 0.041677332, 0.053310412, 0.031890437, 0.026400758, 0.031144823, 0.031144823, 0.028319605 };
	// Construct
	auto grph_ZetaAvg_ExALP = new TGraphErrors(9, xbin_ZetaAvg_ExALP, ybin_ZetaAvg_ExALP, nullptr, yerr_ZetaAvg_ExALP);
	grph_ZetaAvg_ExALP->SetLineColor(kBlue+2); grph_ZetaAvg_ExALP->SetMarkerColor(kBlue+2); grph_ZetaAvg_ExALP->SetMarkerStyle(53); grph_ZetaAvg_ExALP->SetLineWidth(2); grph_ZetaAvg_ExALP->SetMarkerSize(1);

	// L3 graph
	double xbin_ZetaAvg_ExLL3[10] = { 91.2, 130.1, 136.1, 161.3, 172.3, 182.8, 188.6, 194.4, 200.2, 206.2};
	double ybin_ZetaAvg_ExLL3[10] = { 3.74, 3.85, 3.96, 3.91, 4.06, 4.08, 4.06, 4.13, 4.17, 4.13 };
	double yerr_ZetaAvg_ExLL3[10] = { 0.02236068, 0.058309519, 0.070710678, 0.064031242, 0.070710678, 0.04472136, 0.031622777, 0.036055513, 0.04472136, 0.031622777 };
	// Construct
	auto grph_ZetaAvg_ExLL3 = new TGraphErrors(10, xbin_ZetaAvg_ExLL3, ybin_ZetaAvg_ExLL3, nullptr, yerr_ZetaAvg_ExLL3);
	grph_ZetaAvg_ExLL3->SetLineColor(kRed+2); grph_ZetaAvg_ExLL3->SetMarkerColor(kRed+2); grph_ZetaAvg_ExLL3->SetMarkerStyle(53); grph_ZetaAvg_ExLL3->SetLineWidth(2); grph_ZetaAvg_ExLL3->SetMarkerSize(1);

	// TASSO graph
	double xbin_ZetaAvg_ExTAS[4] = { 14.0, 22.0, 35.0, 44.0 };
	double ybin_ZetaAvg_ExTAS[4] = { hist_fitZeta_014->GetParameter(1), hist_fitZeta_022->GetParameter(1), hist_fitZeta_035->GetParameter(1), hist_fitZeta_044->GetParameter(1)	};
	double yerr_ZetaAvg_ExTAS[4] = { hist_fitZeta_014->GetParError(1), hist_fitZeta_022->GetParError(1), hist_fitZeta_035->GetParError(1), hist_fitZeta_044->GetParError(1) };
	// Construct
	auto grph_ZetaAvg_ExTAS = new TGraphErrors(4, xbin_ZetaAvg_ExTAS, ybin_ZetaAvg_ExTAS, nullptr, yerr_ZetaAvg_ExTAS);
	grph_ZetaAvg_ExTAS->SetLineColor(kYellow+2); grph_ZetaAvg_ExTAS->SetMarkerColor(kYellow+2); grph_ZetaAvg_ExTAS->SetMarkerStyle(53); grph_ZetaAvg_ExTAS->SetLineWidth(2); grph_ZetaAvg_ExTAS->SetMarkerSize(1);

	// QCD constants
	const double Nc = 3.0;
	const double nf = 5.0;
	const double Q0 = 0.25;
	const double a = 11.0*Nc/3.0 + 2.0*nf/(3.0*Nc*Nc);
	const double b = 11.0*Nc/3.0 - 2.0*nf/3.0;
	const double c = (a*a)/(16.0*Nc*b);

	// Compute points
	const int npts = 200;
	double E_theory[npts], Xi_theory[npts];

	for (int i=0; i<npts; ++i) {
		double Ecm = 10.0 + i*(400.0-10.0)/(npts-1);
		double y = log(Ecm / (2.0 * Q0));
		double XiStar = y * (0.5 + sqrt(c / y) - (c / y));
		E_theory[i] = Ecm;
		Xi_theory[i] = XiStar;
	}

	// Make theory graph
	TGraph* grph_ZetaAvg_QCD = new TGraph(npts, E_theory, Xi_theory);
	grph_ZetaAvg_QCD->SetLineStyle(2); grph_ZetaAvg_QCD->SetLineWidth(3);

	for (int i = 0; i < grph_ZetaAvg_QCD->GetN(); ++i) grph_ZetaAvg_QCD->GetY()[i] *= 0.98;

	// Normalise theory to PYTHIA 
	const double th_at_Z = grph_ZetaAvg_QCD->Eval(91.2);
	const double scale = grph_ZetaAvg_Pythi->GetY()[0] / th_at_Z;
	cout << scale << endl;
	for (int i = 0; i < grph_ZetaAvg_QCD->GetN(); ++i) grph_ZetaAvg_QCD->GetY()[i] *= scale;

	// Add legend
	TLegend *lg4 = new TLegend(0.77, 0.18, 0.90, 0.40);
	lg4->AddEntry(grph_ZetaAvg_Pythi, "PYTHIA", "P");
	lg4->AddEntry(grph_ZetaAvg_ExALP, "ALEPH", "P");
	lg4->AddEntry(grph_ZetaAvg_ExLL3, "L3", "P");
	lg4->AddEntry(grph_ZetaAvg_ExTAS, "TASSO", "P");
	lg4->AddEntry(grph_ZetaAvg_QCD, "MLLA", "L");
	lg4->SetTextSize(0.04);

	// Beautify
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv5->SetMargin(0, 0, 0, 0);
	gPad->SetTopMargin(0.025);
	gPad->SetBottomMargin(0.12);
	gPad->SetLeftMargin(0.14);
	gPad->SetRightMargin(0.05);
	gPad->SetTickx(); gPad->SetTicky();

	// Beautify
	grph_ZetaAvg_Pythi->GetXaxis()->SetLabelSize(0.05); grph_ZetaAvg_Pythi->GetXaxis()->SetTitleSize(0.05);
	grph_ZetaAvg_Pythi->GetYaxis()->SetLabelSize(0.05); grph_ZetaAvg_Pythi->GetYaxis()->SetTitleSize(0.05);
	grph_ZetaAvg_Pythi->SetTitle("");
	grph_ZetaAvg_Pythi->GetYaxis()->SetTitle("#xi*");
	grph_ZetaAvg_Pythi->GetXaxis()->SetTitle("#sqrt{s} (GeV)");

	// Draw
	grph_ZetaAvg_Pythi->Draw("AP");
	grph_ZetaAvg_ExALP->Draw("PE SAME");
	grph_ZetaAvg_ExLL3->Draw("PE SAME");
	grph_ZetaAvg_ExTAS->Draw("PE SAME");
	grph_ZetaAvg_QCD->Draw("L SAME");
	lg4->Draw("SAME");

	// Set limits
	grph_ZetaAvg_Pythi->GetYaxis()->SetRangeUser(2,5);
	grph_ZetaAvg_Pythi->GetXaxis()->SetLimits(0, 400);

	// Update canvas
	cv5->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Print results
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// cout << fixed << setprecision(4);

	// cout << "====== FITTING WITH THRUST ======" << endl;
	// cout << "√s \t χ²/ndf \t Xi* \t Error" << endl;
	// cout << "---------------------------------" << endl;
	// cout << "91.2 \t " << hist_fitZeta_912->GetChisquare()<<"/"<<hist_fitZeta_912->GetNDF() << "\t" << hist_fitZeta_912->GetParameter(1) << "\t" << hist_fitZeta_912->GetParError(0) << endl; 
	// cout << "160 \t " << hist_fitZeta_160->GetChisquare()<<"/"<<hist_fitZeta_160->GetNDF() << "\t" << hist_fitZeta_160->GetParameter(1) << "\t" << hist_fitZeta_160->GetParError(0) << endl;
	// cout << "240 \t " << hist_fitZeta_240->GetChisquare()<<"/"<<hist_fitZeta_240->GetNDF() << "\t" << hist_fitZeta_240->GetParameter(1) << "\t" << hist_fitZeta_240->GetParError(0) << endl;
	// cout << "365 \t " << hist_fitZeta_365->GetChisquare()<<"/"<<hist_fitZeta_365->GetNDF() << "\t" << hist_fitZeta_365->GetParameter(1) << "\t" << hist_fitZeta_365->GetParError(0) << endl;
	// cout << "=================================" << endl;

}