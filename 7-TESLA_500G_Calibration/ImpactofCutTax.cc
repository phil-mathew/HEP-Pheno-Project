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

// Code
void ImpactofCutTax()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_912 = new TFile("5-CutData/cut_FCC912.root", "READ");
	TFile *input_160 = new TFile("5-CutData/cut_FCC160.root", "READ");
	TFile *input_240 = new TFile("5-CutData/cut_FCC240.root", "READ");
	TFile* input_365 = new TFile("5-CutData/cut_FCC365.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F* hist_TaxPyth_al_912 = (TH1F*)input_912->Get("hist_TaxPyth");
	hist_TaxPyth_al_912->SetLineColor(kBlack); hist_TaxPyth_al_912->SetMarkerColor(kBlack); hist_TaxPyth_al_912->SetMarkerStyle(3); hist_TaxPyth_al_912->SetLineWidth(2); hist_TaxPyth_al_912->SetMarkerSize(1);
	TH1F* hist_TaxPyth_Zq_912 = (TH1F*)input_912->Get("hist_TaxPyth_Zq");
	hist_TaxPyth_Zq_912->SetLineColor(kRed+2); hist_TaxPyth_Zq_912->SetMarkerColor(kRed+2); hist_TaxPyth_Zq_912->SetMarkerStyle(20); hist_TaxPyth_Zq_912->SetLineWidth(2); hist_TaxPyth_Zq_912->SetMarkerSize(1);
	TH1F* hist_TaxPyth_WW_912 = (TH1F*)input_912->Get("hist_TaxPyth_WW");
	hist_TaxPyth_WW_912->SetLineColor(kGreen+2); hist_TaxPyth_WW_912->SetMarkerColor(kGreen+2); hist_TaxPyth_WW_912->SetMarkerStyle(21); hist_TaxPyth_WW_912->SetLineWidth(2); hist_TaxPyth_WW_912->SetMarkerSize(1);
	TH1F* hist_TaxPyth_ZZ_912 = (TH1F*)input_912->Get("hist_TaxPyth_ZZ");
	hist_TaxPyth_ZZ_912->SetLineColor(kBlue+2); hist_TaxPyth_ZZ_912->SetMarkerColor(kBlue+2); hist_TaxPyth_ZZ_912->SetMarkerStyle(22); hist_TaxPyth_ZZ_912->SetLineWidth(2); hist_TaxPyth_ZZ_912->SetMarkerSize(1);
	TH1F* hist_TaxPyth_tt_912 = (TH1F*)input_912->Get("hist_TaxPyth_tt");
	hist_TaxPyth_tt_912->SetLineColor(kYellow+2); hist_TaxPyth_tt_912->SetMarkerColor(kYellow+2); hist_TaxPyth_tt_912->SetMarkerStyle(23); hist_TaxPyth_tt_912->SetLineWidth(2); hist_TaxPyth_tt_912->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HZ_912 = (TH1F*)input_912->Get("hist_TaxPyth_HZ");
	hist_TaxPyth_HZ_912->SetLineColor(kMagenta+2); hist_TaxPyth_HZ_912->SetMarkerColor(kMagenta+2); hist_TaxPyth_HZ_912->SetMarkerStyle(33); hist_TaxPyth_HZ_912->SetLineWidth(2); hist_TaxPyth_HZ_912->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HW_912 = (TH1F*)input_912->Get("hist_TaxPyth_HW");
	hist_TaxPyth_HW_912->SetLineColor(kCyan+2); hist_TaxPyth_HW_912->SetMarkerColor(kCyan+2); hist_TaxPyth_HW_912->SetMarkerStyle(47); hist_TaxPyth_HW_912->SetLineWidth(2); hist_TaxPyth_HW_912->SetMarkerSize(1);

	TH1F* hist_TaxPyth_al_160 = (TH1F*)input_160->Get("hist_TaxPyth");
	hist_TaxPyth_al_160->SetLineColor(kBlack); hist_TaxPyth_al_160->SetMarkerColor(kBlack); hist_TaxPyth_al_160->SetMarkerStyle(3); hist_TaxPyth_al_160->SetLineWidth(2); hist_TaxPyth_al_160->SetMarkerSize(1);
	TH1F* hist_TaxPyth_Zq_160 = (TH1F*)input_160->Get("hist_TaxPyth_Zq");
	hist_TaxPyth_Zq_160->SetLineColor(kRed+2); hist_TaxPyth_Zq_160->SetMarkerColor(kRed+2); hist_TaxPyth_Zq_160->SetMarkerStyle(20); hist_TaxPyth_Zq_160->SetLineWidth(2); hist_TaxPyth_Zq_160->SetMarkerSize(1);
	TH1F* hist_TaxPyth_WW_160 = (TH1F*)input_160->Get("hist_TaxPyth_WW");
	hist_TaxPyth_WW_160->SetLineColor(kGreen+2); hist_TaxPyth_WW_160->SetMarkerColor(kGreen+2); hist_TaxPyth_WW_160->SetMarkerStyle(21); hist_TaxPyth_WW_160->SetLineWidth(2); hist_TaxPyth_WW_160->SetMarkerSize(1);
	TH1F* hist_TaxPyth_ZZ_160 = (TH1F*)input_160->Get("hist_TaxPyth_ZZ");
	hist_TaxPyth_ZZ_160->SetLineColor(kBlue+2); hist_TaxPyth_ZZ_160->SetMarkerColor(kBlue+2); hist_TaxPyth_ZZ_160->SetMarkerStyle(22); hist_TaxPyth_ZZ_160->SetLineWidth(2); hist_TaxPyth_ZZ_160->SetMarkerSize(1);
	TH1F* hist_TaxPyth_tt_160 = (TH1F*)input_160->Get("hist_TaxPyth_tt");
	hist_TaxPyth_tt_160->SetLineColor(kYellow+2); hist_TaxPyth_tt_160->SetMarkerColor(kYellow+2); hist_TaxPyth_tt_160->SetMarkerStyle(23); hist_TaxPyth_tt_160->SetLineWidth(2); hist_TaxPyth_tt_160->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HZ_160 = (TH1F*)input_160->Get("hist_TaxPyth_HZ");
	hist_TaxPyth_HZ_160->SetLineColor(kMagenta+2); hist_TaxPyth_HZ_160->SetMarkerColor(kMagenta+2); hist_TaxPyth_HZ_160->SetMarkerStyle(33); hist_TaxPyth_HZ_160->SetLineWidth(2); hist_TaxPyth_HZ_160->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HW_160 = (TH1F*)input_160->Get("hist_TaxPyth_HW");
	hist_TaxPyth_HW_160->SetLineColor(kCyan+2); hist_TaxPyth_HW_160->SetMarkerColor(kCyan+2); hist_TaxPyth_HW_160->SetMarkerStyle(47); hist_TaxPyth_HW_160->SetLineWidth(2); hist_TaxPyth_HW_160->SetMarkerSize(1);

	TH1F* hist_TaxPyth_al_240 = (TH1F*)input_240->Get("hist_TaxPyth");
	hist_TaxPyth_al_240->SetLineColor(kBlack); hist_TaxPyth_al_240->SetMarkerColor(kBlack); hist_TaxPyth_al_240->SetMarkerStyle(3); hist_TaxPyth_al_240->SetLineWidth(2); hist_TaxPyth_al_240->SetMarkerSize(1);
	TH1F* hist_TaxPyth_Zq_240 = (TH1F*)input_240->Get("hist_TaxPyth_Zq");
	hist_TaxPyth_Zq_240->SetLineColor(kRed+2); hist_TaxPyth_Zq_240->SetMarkerColor(kRed+2); hist_TaxPyth_Zq_240->SetMarkerStyle(20); hist_TaxPyth_Zq_240->SetLineWidth(2); hist_TaxPyth_Zq_240->SetMarkerSize(1);
	TH1F* hist_TaxPyth_WW_240 = (TH1F*)input_240->Get("hist_TaxPyth_WW");
	hist_TaxPyth_WW_240->SetLineColor(kGreen+2); hist_TaxPyth_WW_240->SetMarkerColor(kGreen+2); hist_TaxPyth_WW_240->SetMarkerStyle(21); hist_TaxPyth_WW_240->SetLineWidth(2); hist_TaxPyth_WW_240->SetMarkerSize(1);
	TH1F* hist_TaxPyth_ZZ_240 = (TH1F*)input_240->Get("hist_TaxPyth_ZZ");
	hist_TaxPyth_ZZ_240->SetLineColor(kBlue+2); hist_TaxPyth_ZZ_240->SetMarkerColor(kBlue+2); hist_TaxPyth_ZZ_240->SetMarkerStyle(22); hist_TaxPyth_ZZ_240->SetLineWidth(2); hist_TaxPyth_ZZ_240->SetMarkerSize(1);
	TH1F* hist_TaxPyth_tt_240 = (TH1F*)input_240->Get("hist_TaxPyth_tt");
	hist_TaxPyth_tt_240->SetLineColor(kYellow+2); hist_TaxPyth_tt_240->SetMarkerColor(kYellow+2); hist_TaxPyth_tt_240->SetMarkerStyle(23); hist_TaxPyth_tt_240->SetLineWidth(2); hist_TaxPyth_tt_240->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HZ_240 = (TH1F*)input_240->Get("hist_TaxPyth_HZ");
	hist_TaxPyth_HZ_240->SetLineColor(kMagenta+2); hist_TaxPyth_HZ_240->SetMarkerColor(kMagenta+2); hist_TaxPyth_HZ_240->SetMarkerStyle(33); hist_TaxPyth_HZ_240->SetLineWidth(2); hist_TaxPyth_HZ_240->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HW_240 = (TH1F*)input_240->Get("hist_TaxPyth_HW");
	hist_TaxPyth_HW_240->SetLineColor(kCyan+2); hist_TaxPyth_HW_240->SetMarkerColor(kCyan+2); hist_TaxPyth_HW_240->SetMarkerStyle(47); hist_TaxPyth_HW_240->SetLineWidth(2); hist_TaxPyth_HW_240->SetMarkerSize(1);

	TH1F* hist_TaxPyth_al_365 = (TH1F*)input_365->Get("hist_TaxPyth");
	hist_TaxPyth_al_365->SetLineColor(kBlack); hist_TaxPyth_al_365->SetMarkerColor(kBlack); hist_TaxPyth_al_365->SetMarkerStyle(3); hist_TaxPyth_al_365->SetLineWidth(2); hist_TaxPyth_al_365->SetMarkerSize(1);
	TH1F* hist_TaxPyth_Zq_365 = (TH1F*)input_365->Get("hist_TaxPyth_Zq");
	hist_TaxPyth_Zq_365->SetLineColor(kRed+2); hist_TaxPyth_Zq_365->SetMarkerColor(kRed+2); hist_TaxPyth_Zq_365->SetMarkerStyle(20); hist_TaxPyth_Zq_365->SetLineWidth(2); hist_TaxPyth_Zq_365->SetMarkerSize(1);
	TH1F* hist_TaxPyth_WW_365 = (TH1F*)input_365->Get("hist_TaxPyth_WW");
	hist_TaxPyth_WW_365->SetLineColor(kGreen+2); hist_TaxPyth_WW_365->SetMarkerColor(kGreen+2); hist_TaxPyth_WW_365->SetMarkerStyle(21); hist_TaxPyth_WW_365->SetLineWidth(2); hist_TaxPyth_WW_365->SetMarkerSize(1);
	TH1F* hist_TaxPyth_ZZ_365 = (TH1F*)input_365->Get("hist_TaxPyth_ZZ");
	hist_TaxPyth_ZZ_365->SetLineColor(kBlue+2); hist_TaxPyth_ZZ_365->SetMarkerColor(kBlue+2); hist_TaxPyth_ZZ_365->SetMarkerStyle(22); hist_TaxPyth_ZZ_365->SetLineWidth(2); hist_TaxPyth_ZZ_365->SetMarkerSize(1);
	TH1F* hist_TaxPyth_tt_365 = (TH1F*)input_365->Get("hist_TaxPyth_tt");
	hist_TaxPyth_tt_365->SetLineColor(kYellow+2); hist_TaxPyth_tt_365->SetMarkerColor(kYellow+2); hist_TaxPyth_tt_365->SetMarkerStyle(23); hist_TaxPyth_tt_365->SetLineWidth(2); hist_TaxPyth_tt_365->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HZ_365 = (TH1F*)input_365->Get("hist_TaxPyth_HZ");
	hist_TaxPyth_HZ_365->SetLineColor(kMagenta+2); hist_TaxPyth_HZ_365->SetMarkerColor(kMagenta+2); hist_TaxPyth_HZ_365->SetMarkerStyle(33); hist_TaxPyth_HZ_365->SetLineWidth(2); hist_TaxPyth_HZ_365->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HW_365 = (TH1F*)input_365->Get("hist_TaxPyth_HW");
	hist_TaxPyth_HW_365->SetLineColor(kCyan+2); hist_TaxPyth_HW_365->SetMarkerColor(kCyan+2); hist_TaxPyth_HW_365->SetMarkerStyle(47); hist_TaxPyth_HW_365->SetLineWidth(2); hist_TaxPyth_HW_365->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_TaxPyth_al_912->SetStats(kFALSE);
	hist_TaxPyth_al_160->SetStats(kFALSE);
	hist_TaxPyth_al_240->SetStats(kFALSE);
	hist_TaxPyth_al_365->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit text sizes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_TaxPyth_al_912->GetXaxis()->SetLabelSize(0.06); hist_TaxPyth_al_912->GetYaxis()->SetLabelSize(0.06); hist_TaxPyth_al_912->GetYaxis()->SetTitleSize(0.06); hist_TaxPyth_al_912->GetXaxis()->SetTitleSize(0.06);
	hist_TaxPyth_al_160->GetXaxis()->SetLabelSize(0.06); hist_TaxPyth_al_160->GetYaxis()->SetLabelSize(0.06); hist_TaxPyth_al_160->GetYaxis()->SetTitleSize(0.06); hist_TaxPyth_al_160->GetXaxis()->SetTitleSize(0.06);
	hist_TaxPyth_al_240->GetXaxis()->SetLabelSize(0.06); hist_TaxPyth_al_240->GetYaxis()->SetLabelSize(0.06); hist_TaxPyth_al_240->GetYaxis()->SetTitleSize(0.06); hist_TaxPyth_al_240->GetXaxis()->SetTitleSize(0.06);
	hist_TaxPyth_al_365->GetXaxis()->SetLabelSize(0.06); hist_TaxPyth_al_365->GetYaxis()->SetLabelSize(0.06); hist_TaxPyth_al_365->GetYaxis()->SetTitleSize(0.06); hist_TaxPyth_al_365->GetXaxis()->SetTitleSize(0.06);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_TaxPyth_al_912->SetTitle("");
	hist_TaxPyth_al_160->SetTitle("");
	hist_TaxPyth_al_240->SetTitle("");
	hist_TaxPyth_al_365->SetTitle("");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw Plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv5 = new TCanvas("cv5", "FCC-ee ISR Studies", 800, 2100);

	// Add legend
	TLegend* lg5 = new TLegend(0.48, 0.64, 0.61, 0.95);
	lg5->AddEntry(hist_TaxPyth_al_365, "ee#rightarrowq#bar{q}", "PL");
	lg5->AddEntry(hist_TaxPyth_Zq_365, "ee#rightarrow#gamma/Z", "PL");
	lg5->AddEntry(hist_TaxPyth_ZZ_365, "ee#rightarrowZZ", "PL");
	lg5->AddEntry(hist_TaxPyth_WW_365, "ee#rightarrowWW", "PL");
	lg5->AddEntry(hist_TaxPyth_tt_365, "ee#rightarrowt#bar{t}", "PL");
	lg5->AddEntry(hist_TaxPyth_HZ_365, "ee#rightarrowZH", "PL");
	lg5->AddEntry(hist_TaxPyth_HW_365, "ee#rightarrow#nu#bar{#nu}H", "PL");
	lg5->SetTextSize(0.04);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv5->SetMargin(0, 0, 0, 0); 
	cv5->Divide(1,4);
	for (int i = 1; i <= 4; i++) {
		cv5->cd(i);
		gPad->SetTopMargin(0.03);
		gPad->SetBottomMargin(0.12);
		gPad->SetLeftMargin(0.14);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		gPad->SetLogy();
	}

	hist_TaxPyth_al_912->GetYaxis()->SetTitle("N_{events}");
	hist_TaxPyth_al_160->GetYaxis()->SetTitle("N_{events}");
	hist_TaxPyth_al_240->GetYaxis()->SetTitle("N_{events}");
	hist_TaxPyth_al_365->GetYaxis()->SetTitle("N_{events}");

	hist_TaxPyth_al_912->GetXaxis()->CenterTitle(); hist_TaxPyth_al_912->GetYaxis()->CenterTitle();
	hist_TaxPyth_al_160->GetXaxis()->CenterTitle(); hist_TaxPyth_al_160->GetYaxis()->CenterTitle();
	hist_TaxPyth_al_240->GetXaxis()->CenterTitle(); hist_TaxPyth_al_240->GetYaxis()->CenterTitle();
	hist_TaxPyth_al_365->GetXaxis()->CenterTitle(); hist_TaxPyth_al_365->GetYaxis()->CenterTitle();

	hist_TaxPyth_al_912->Rebin(2);
	hist_TaxPyth_Zq_912->Rebin(2);

	// Draw
	cv5->cd(4);
	hist_TaxPyth_al_912->Draw("HIST");
	hist_TaxPyth_Zq_912->Draw("HIST SAME");
	hist_TaxPyth_Zq_912->Draw("P SAME");
	lg5->Draw("SAME");

	hist_TaxPyth_al_160->Rebin(2);
	hist_TaxPyth_Zq_160->Rebin(2);
	hist_TaxPyth_WW_160->Rebin(2);
	hist_TaxPyth_ZZ_160->Rebin(2);

	cv5->cd(3);
	hist_TaxPyth_al_160->Draw("HIST");
	hist_TaxPyth_Zq_160->Draw("HIST SAME");
	hist_TaxPyth_Zq_160->Draw("P SAME");
	hist_TaxPyth_WW_160->Draw("HIST SAME");
	hist_TaxPyth_WW_160->Draw("P SAME");
	hist_TaxPyth_ZZ_160->Draw("HIST SAME");
	hist_TaxPyth_ZZ_160->Draw("P SAME");
	lg5->Draw("SAME");

	hist_TaxPyth_al_240->Rebin(2);
	hist_TaxPyth_Zq_240->Rebin(2);
	hist_TaxPyth_WW_240->Rebin(2);
	hist_TaxPyth_ZZ_240->Rebin(2);
	hist_TaxPyth_HZ_240->Rebin(2);
	hist_TaxPyth_HW_240->Rebin(2);

	cv5->cd(2);
	hist_TaxPyth_al_240->Draw("HIST");
	hist_TaxPyth_Zq_240->Draw("HIST SAME");
	hist_TaxPyth_Zq_240->Draw("P SAME");
	hist_TaxPyth_WW_240->Draw("HIST SAME");
	hist_TaxPyth_WW_240->Draw("P SAME");
	hist_TaxPyth_ZZ_240->Draw("HIST SAME");
	hist_TaxPyth_ZZ_240->Draw("P SAME");
	hist_TaxPyth_HZ_240->Draw("HIST SAME");
	hist_TaxPyth_HZ_240->Draw("P SAME");
	lg5->Draw("SAME");

	hist_TaxPyth_al_365->Rebin(2);
	hist_TaxPyth_Zq_365->Rebin(2);
	hist_TaxPyth_WW_365->Rebin(2);
	hist_TaxPyth_ZZ_365->Rebin(2);
	hist_TaxPyth_tt_365->Rebin(2);
	hist_TaxPyth_HZ_365->Rebin(2);
	hist_TaxPyth_HW_365->Rebin(2);

	cv5->cd(1);
	hist_TaxPyth_al_365->Draw("HIST");
	hist_TaxPyth_Zq_365->Draw("HIST SAME");
	hist_TaxPyth_Zq_365->Draw("P SAME");
	hist_TaxPyth_WW_365->Draw("HIST SAME");
	hist_TaxPyth_WW_365->Draw("P SAME");
	hist_TaxPyth_ZZ_365->Draw("HIST SAME");
	hist_TaxPyth_ZZ_365->Draw("P SAME");
	hist_TaxPyth_tt_365->Draw("HIST SAME");
	hist_TaxPyth_tt_365->Draw("P SAME");
	hist_TaxPyth_HZ_365->Draw("HIST SAME");
	hist_TaxPyth_HZ_365->Draw("P SAME");
	hist_TaxPyth_HW_365->Draw("HIST SAME");
	hist_TaxPyth_HW_365->Draw("P SAME");
	lg5->Draw("SAME");

	// Set limits
	hist_TaxPyth_al_912->GetYaxis()->SetRangeUser(1E2,1E7);
	hist_TaxPyth_al_912->GetXaxis()->SetRangeUser(-1,1);
	hist_TaxPyth_al_160->GetYaxis()->SetRangeUser(1E2,1E7);
	hist_TaxPyth_al_160->GetXaxis()->SetRangeUser(-1,1);
	hist_TaxPyth_al_240->GetYaxis()->SetRangeUser(1E2,1E7);
	hist_TaxPyth_al_240->GetXaxis()->SetRangeUser(-1,1);
	hist_TaxPyth_al_365->GetYaxis()->SetRangeUser(1E2,1E7);
	hist_TaxPyth_al_365->GetXaxis()->SetRangeUser(-1,1);
	
	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv5->Modified();

}