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
void ImpactofMults()
{

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
	hist_nHadron_365_al->SetLineColor(kBlack); hist_nHadron_365_al->SetMarkerColor(kBlack); hist_nHadron_365_al->SetMarkerStyle(3); hist_nHadron_365_al->SetLineWidth(2); hist_nHadron_365_al->SetMarkerSize(1);
	TH1F* hist_nHadron_365_Zq = (TH1F*)input_365->Get("hist_nHadron_Zq");
	hist_nHadron_365_Zq->SetLineColor(kRed+2); hist_nHadron_365_Zq->SetMarkerColor(kRed+2); hist_nHadron_365_Zq->SetMarkerStyle(3); hist_nHadron_365_Zq->SetLineWidth(2); hist_nHadron_365_Zq->SetMarkerSize(1);
	TH1F* hist_nHadron_365_WW = (TH1F*)input_365->Get("hist_nHadron_WW");
	hist_nHadron_365_WW->SetLineColor(kGreen+2); hist_nHadron_365_WW->SetMarkerColor(kGreen+2); hist_nHadron_365_WW->SetMarkerStyle(3); hist_nHadron_365_WW->SetLineWidth(2); hist_nHadron_365_WW->SetMarkerSize(1);
	TH1F* hist_nHadron_365_ZZ = (TH1F*)input_365->Get("hist_nHadron_ZZ");
	hist_nHadron_365_ZZ->SetLineColor(kBlue+2); hist_nHadron_365_ZZ->SetMarkerColor(kBlue+2); hist_nHadron_365_ZZ->SetMarkerStyle(3); hist_nHadron_365_ZZ->SetLineWidth(2); hist_nHadron_365_ZZ->SetMarkerSize(1);
	TH1F* hist_nHadron_365_tt = (TH1F*)input_365->Get("hist_nHadron_tt");
	hist_nHadron_365_tt->SetLineColor(kYellow+2); hist_nHadron_365_tt->SetMarkerColor(kYellow+2); hist_nHadron_365_tt->SetMarkerStyle(3); hist_nHadron_365_tt->SetLineWidth(2); hist_nHadron_365_tt->SetMarkerSize(1);
	TH1F* hist_nHadron_365_HZ = (TH1F*)input_365->Get("hist_nHadron_HZ");
	hist_nHadron_365_HZ->SetLineColor(kMagenta+2); hist_nHadron_365_HZ->SetMarkerColor(kMagenta+2); hist_nHadron_365_HZ->SetMarkerStyle(53); hist_nHadron_365_HZ->SetLineWidth(2); hist_nHadron_365_HZ->SetMarkerSize(1);
	TH1F* hist_nHadron_365_HW = (TH1F*)input_365->Get("hist_nHadron_HW");
	hist_nHadron_365_HW->SetLineColor(kCyan+2); hist_nHadron_365_HW->SetMarkerColor(kCyan+2); hist_nHadron_365_HW->SetMarkerStyle(53); hist_nHadron_365_HW->SetLineWidth(2); hist_nHadron_365_HW->SetMarkerSize(1);

	TH1F *hist_ZetaInc_912 = (TH1F*)input_912->Get("hist_ZetaInc");
	hist_ZetaInc_912->SetLineColor(kBlue+2); hist_ZetaInc_912->SetMarkerColor(kBlue+2); hist_ZetaInc_912->SetMarkerStyle(26); hist_ZetaInc_912->SetLineWidth(2); hist_ZetaInc_912->SetMarkerSize(2);
	TH1F *hist_ZetaInc_160 = (TH1F*)input_160->Get("hist_ZetaInc");
	hist_ZetaInc_160->SetLineColor(kRed+2); hist_ZetaInc_160->SetMarkerColor(kRed+2); hist_ZetaInc_160->SetMarkerStyle(26); hist_ZetaInc_160->SetLineWidth(2); hist_ZetaInc_160->SetMarkerSize(2);
	TH1F *hist_ZetaInc_240 = (TH1F*)input_240->Get("hist_ZetaInc");
	hist_ZetaInc_240->SetLineColor(kYellow+2); hist_ZetaInc_240->SetMarkerColor(kYellow+2); hist_ZetaInc_240->SetMarkerStyle(26); hist_ZetaInc_240->SetLineWidth(2); hist_ZetaInc_240->SetMarkerSize(2);
	TH1F *hist_ZetaInc_365 = (TH1F*)input_365->Get("hist_ZetaInc");
	hist_ZetaInc_365->SetLineColor(kGreen+2); hist_ZetaInc_365->SetMarkerColor(kGreen+2); hist_ZetaInc_365->SetMarkerStyle(26); hist_ZetaInc_365->SetLineWidth(2); hist_ZetaInc_365->SetMarkerSize(2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting <NCH>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////		

	// hist_Zeta->GetBinCenter(hist_Zeta->GetMaximumBin())

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_nHadron_912_Zq->SetStats(kFALSE);
	hist_nHadron_365_al->SetStats(kFALSE);
	// hist_ZetaInc_912->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv1 = new TCanvas("cv1", "FCC-ee ISR Studies", 800, 700);

	// Add legend
	TLegend *lg1 = new TLegend(0.77, 0.75, 0.95, 0.95);
	lg1->AddEntry(hist_nHadron_912_Zq, "91.2 GeV", "PL");
	lg1->AddEntry(hist_nHadron_160_Zq, "160 GeV", "PL");
	lg1->AddEntry(hist_nHadron_240_Zq, "240 GeV", "PL");
	lg1->AddEntry(hist_nHadron_365_Zq, "365 GeV", "PL");
	lg1->SetTextSize(0.04);

	// Beautify
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv1->SetMargin(0, 0, 0, 0); 
	gPad->SetTopMargin(0.025);
	gPad->SetBottomMargin(0.12);
	gPad->SetLeftMargin(0.15);
	gPad->SetRightMargin(0.02);
	gPad->SetTickx(); gPad->SetTicky();
	gPad->SetLogy();

	// Beautify
	hist_nHadron_912_Zq->GetXaxis()->SetLabelSize(0.05); hist_nHadron_912_Zq->GetXaxis()->SetTitleSize(0.05);
	hist_nHadron_912_Zq->GetYaxis()->SetLabelSize(0.05); hist_nHadron_912_Zq->GetYaxis()->SetTitleSize(0.05);
	hist_nHadron_912_Zq->SetTitle("");
	hist_nHadron_912_Zq->GetYaxis()->SetTitle("P(N_{Ch})");

	// Beautify
	hist_nHadron_912_Zq->SetLineColor(kBlack); hist_nHadron_912_Zq->SetMarkerColor(kBlack); hist_nHadron_912_Zq->SetMarkerStyle(20); hist_nHadron_912_Zq->SetLineWidth(1); hist_nHadron_912_Zq->SetMarkerSize(1.2);
	hist_nHadron_160_Zq->SetLineColor(kBlack); hist_nHadron_160_Zq->SetMarkerColor(kBlack); hist_nHadron_160_Zq->SetMarkerStyle(47); hist_nHadron_160_Zq->SetLineWidth(1); hist_nHadron_160_Zq->SetMarkerSize(1.2);
	hist_nHadron_240_Zq->SetLineColor(kBlack); hist_nHadron_240_Zq->SetMarkerColor(kBlack); hist_nHadron_240_Zq->SetMarkerStyle(22); hist_nHadron_240_Zq->SetLineWidth(1); hist_nHadron_240_Zq->SetMarkerSize(1.2);
	hist_nHadron_365_Zq->SetLineColor(kBlack); hist_nHadron_365_Zq->SetMarkerColor(kBlack); hist_nHadron_365_Zq->SetMarkerStyle(33); hist_nHadron_365_Zq->SetLineWidth(1); hist_nHadron_365_Zq->SetMarkerSize(1.5);

	// Normalise
	hist_nHadron_912_Zq->Scale(1.0/hist_nHadron_912_Zq->Integral());
	hist_nHadron_160_Zq->Scale(1.0/hist_nHadron_160_Zq->Integral());
	hist_nHadron_240_Zq->Scale(1.0/hist_nHadron_240_Zq->Integral());
	hist_nHadron_365_Zq->Scale(1.0/hist_nHadron_365_Zq->Integral());

	hist_nHadron_912_Zq->Rebin(2);
	hist_nHadron_160_Zq->Rebin(2);
	hist_nHadron_240_Zq->Rebin(2);
	hist_nHadron_365_Zq->Rebin(2);
	// Draw
	hist_nHadron_912_Zq->Draw("HIST E");
	hist_nHadron_160_Zq->Draw("HIST E SAME");
	hist_nHadron_240_Zq->Draw("HIST E SAME");
	hist_nHadron_365_Zq->Draw("HIST E SAME");
	lg1->Draw("SAME");

	// Set limits
	hist_nHadron_912_Zq->GetYaxis()->SetRangeUser(1,2E-1);
	hist_nHadron_912_Zq->GetXaxis()->SetRangeUser(0,90);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv1->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 800, 700);

	// // Add legend
	// TLegend* lg2 = new TLegend(0.77, 0.64, 0.95, 0.95);
	// lg2->AddEntry(hist_nHadron_365_al, "ee#rightarrowq#bar{q}", "L");
	// lg2->AddEntry(hist_nHadron_365_Zq, "ee#rightarrow#gamma*/Z", "L");
	// lg2->AddEntry(hist_nHadron_365_ZZ, "ee#rightarrowWW", "L");
	// lg2->AddEntry(hist_nHadron_365_WW, "ee#rightarrowZZ", "L");
	// lg2->AddEntry(hist_nHadron_365_tt, "ee#rightarrowt#bar{t}", "L");
	// lg2->AddEntry(hist_nHadron_365_HZ, "ee#rightarrowZH", "L");
	// lg2->AddEntry(hist_nHadron_365_HW, "ee#rightarrow#nu#bar{#nu}H", "L");
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
	// gPad->SetRightMargin(0.02);
	// gPad->SetTickx(); gPad->SetTicky();
	// gPad->SetLogy();

	// // Beautify
	// hist_nHadron_365_al->GetXaxis()->SetLabelSize(0.05); hist_nHadron_365_al->GetXaxis()->SetTitleSize(0.05);
	// hist_nHadron_365_al->GetYaxis()->SetLabelSize(0.05); hist_nHadron_365_al->GetYaxis()->SetTitleSize(0.05);
	// hist_nHadron_365_al->SetTitle("");
	// hist_nHadron_365_al->GetYaxis()->SetTitle("#");

	// // Draw
	// hist_nHadron_365_al->Draw("HIST");
	// hist_nHadron_365_Zq->Draw("HIST SAME");
	// hist_nHadron_365_ZZ->Draw("HIST SAME");
	// hist_nHadron_365_WW->Draw("HIST SAME");
	// hist_nHadron_365_tt->Draw("HIST SAME");
	// hist_nHadron_365_HZ->Draw("HIST SAME");
	// hist_nHadron_365_HW->Draw("HIST SAME");

	// lg2->Draw("SAME");

	// // Set limits
	// hist_nHadron_365_al->GetYaxis()->SetRangeUser(1,2E5);
	// hist_nHadron_365_al->GetXaxis()->SetRangeUser(0,120);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv2->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv3 = new TCanvas("cv3", "FCC-ee ISR Studies", 800, 700);

	// // Add legend
	// TLegend *lg3 = new TLegend(0.77, 0.75, 0.95, 0.95);
	// lg3->AddEntry(hist_ZetaInc_912, "91.2 GeV", "L");
	// lg3->AddEntry(hist_ZetaInc_160, "160 GeV", "L");
	// lg3->AddEntry(hist_ZetaInc_240, "240 GeV", "L");
	// lg3->AddEntry(hist_ZetaInc_365, "365 GeV", "L");
	// lg3->SetTextSize(0.04);

	// // Beautify
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv3->SetMargin(0, 0, 0, 0);
	// gPad->SetTopMargin(0.025);
	// gPad->SetBottomMargin(0.12);
	// gPad->SetLeftMargin(0.12);
	// gPad->SetRightMargin(0.02);
	// gPad->SetTickx(); gPad->SetTicky();

	// // Beautify
	// hist_ZetaInc_912->GetXaxis()->SetLabelSize(0.05); hist_ZetaInc_912->GetXaxis()->SetTitleSize(0.05);
	// hist_ZetaInc_912->GetYaxis()->SetLabelSize(0.05); hist_ZetaInc_912->GetYaxis()->SetTitleSize(0.05);
	// hist_ZetaInc_912->SetTitle("");
	// hist_ZetaInc_912->GetYaxis()->SetTitle("#");

	// hist_ZetaInc_912->Scale(1.0/hist_ZetaInc_912->Integral());
	// hist_ZetaInc_160->Scale(1.0/hist_ZetaInc_160->Integral());
	// hist_ZetaInc_240->Scale(1.0/hist_ZetaInc_240->Integral());
	// hist_ZetaInc_365->Scale(1.0/hist_ZetaInc_365->Integral());

	// // Draw
	// hist_ZetaInc_912->Draw("HIST");
	// hist_ZetaInc_160->Draw("HIST");
	// hist_ZetaInc_240->Draw("HIST SAME");
	// hist_ZetaInc_365->Draw("HIST SAME");
	// lg3->Draw("SAME");

	// // Set limits
	// // hist_ZetaInc_912->GetYaxis()->SetRangeUser(0,8);
	// // hist_ZetaInc_912->GetXaxis()->SetRangeUser(0,8);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv3->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv4 = new TCanvas("cv4", "FCC-ee ISR Studies", 800, 700);

	// // Import aleph
	// TDirectory *table_EXP_ALP_NCH = (TDirectory*)input_EXP_ALP->Get("Table 1");
	// TGraphAsymmErrors* grph_nHadAvg_ExALP = (TGraphAsymmErrors*)table_EXP_ALP_NCH->Get("Graph1D_y1");
	// grph_nHadAvg_ExALP->SetLineColor(kBlue+2); grph_nHadAvg_ExALP->SetMarkerColor(kBlue+2); grph_nHadAvg_ExALP->SetMarkerStyle(53); grph_nHadAvg_ExALP->SetLineWidth(2); grph_nHadAvg_ExALP->SetMarkerSize(1);
	
	// // Import l3
	// TDirectory *table_EXP_LL3_NCH = (TDirectory*)input_EXP_LL3->Get("Table 64");
	// TGraphAsymmErrors* grph_nHadAvg_ExLL3 = (TGraphAsymmErrors*)table_EXP_LL3_NCH->Get("Graph1D_y1");
	// grph_nHadAvg_ExLL3->SetLineColor(kRed+2); grph_nHadAvg_ExLL3->SetMarkerColor(kRed+2); grph_nHadAvg_ExLL3->SetMarkerStyle(53); grph_nHadAvg_ExLL3->SetLineWidth(2); grph_nHadAvg_ExLL3->SetMarkerSize(1);

	// // FCC energy
	// double xbin_nHadAvg_Pythi[4] = {91.2, 160.0, 240.0, 365.0};

	// // Access pythia bins
	// double ybin_nHadAvg_Pythi[4] = {
	// hist_nHadron_912_Zq->GetMean(),
	// hist_nHadron_160_Zq->GetMean(),
	// hist_nHadron_240_Zq->GetMean(),
	// hist_nHadron_365_Zq->GetMean()
	// };

	// // Access pythia errors
	// double yerr_nHadAvg_Pythi[4] = {
	// hist_nHadron_912_Zq->GetMeanError(),
	// hist_nHadron_160_Zq->GetMeanError(),
	// hist_nHadron_240_Zq->GetMeanError(),
	// hist_nHadron_365_Zq->GetMeanError()
	// };

	// // Construct pythia graph
	// auto grph_nHadAvg_Pythi = new TGraphErrors(4, xbin_nHadAvg_Pythi, ybin_nHadAvg_Pythi, nullptr, yerr_nHadAvg_Pythi);
	// grph_nHadAvg_Pythi->SetLineColor(kBlack); grph_nHadAvg_Pythi->SetMarkerColor(kBlack); grph_nHadAvg_Pythi->SetMarkerStyle(20); grph_nHadAvg_Pythi->SetLineWidth(2); grph_nHadAvg_Pythi->SetMarkerSize(2);

	// // Add legend
	// TLegend *lg4 = new TLegend(0.16, 0.78, 0.32, 0.93);
	// lg4->AddEntry(grph_nHadAvg_Pythi, "PYTHIA", "PL");
	// lg4->AddEntry(grph_nHadAvg_ExALP, "ALEPH", "PL");
	// lg4->AddEntry(grph_nHadAvg_ExLL3, "L3", "PL");
	// lg4->SetTextSize(0.04);

	// // Beautify
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv4->SetMargin(0, 0, 0, 0);
	// gPad->SetTopMargin(0.025);
	// gPad->SetBottomMargin(0.12);
	// gPad->SetLeftMargin(0.12);
	// gPad->SetRightMargin(0.02);
	// gPad->SetTickx(); gPad->SetTicky();

	// // Beautify
	// grph_nHadAvg_Pythi->GetXaxis()->SetLabelSize(0.05); grph_nHadAvg_Pythi->GetXaxis()->SetTitleSize(0.05);
	// grph_nHadAvg_Pythi->GetYaxis()->SetLabelSize(0.05); grph_nHadAvg_Pythi->GetYaxis()->SetTitleSize(0.05);
	// grph_nHadAvg_Pythi->SetTitle("");
	// grph_nHadAvg_Pythi->GetYaxis()->SetTitle("<N_{CH}>");
	// grph_nHadAvg_Pythi->GetXaxis()->SetTitle("#sqrt{s}");

	// // Draw
	// grph_nHadAvg_Pythi->Draw("APL");
	// grph_nHadAvg_ExALP->Draw("PEL SAME");
	// grph_nHadAvg_ExLL3->Draw("PEL SAME");
	// lg4->Draw("SAME");

}