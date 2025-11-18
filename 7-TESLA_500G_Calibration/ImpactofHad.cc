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
void ImpactofHad() {

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

	TH1F* hist_ThrPyth_al_365 = (TH1F*)input_365->Get("hist_ThrPyth");
	hist_ThrPyth_al_365->SetLineColor(kBlack); hist_ThrPyth_al_365->SetMarkerColor(kBlack); hist_ThrPyth_al_365->SetMarkerStyle(21); hist_ThrPyth_al_365->SetLineWidth(3); hist_ThrPyth_al_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_365 = (TH1F*)input_365->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_365->SetLineColor(kRed+2); hist_ThrPyth_Zq_365->SetMarkerColor(kRed+1); hist_ThrPyth_Zq_365->SetMarkerStyle(21); hist_ThrPyth_Zq_365->SetLineWidth(3); hist_ThrPyth_Zq_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_365 = (TH1F*)input_365->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_365->SetLineColor(kGreen+2); hist_ThrPyth_WW_365->SetMarkerColor(kGreen+1); hist_ThrPyth_WW_365->SetMarkerStyle(21); hist_ThrPyth_WW_365->SetLineWidth(3); hist_ThrPyth_WW_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_365 = (TH1F*)input_365->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_365->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_365->SetMarkerColor(kBlue+1); hist_ThrPyth_ZZ_365->SetMarkerStyle(21); hist_ThrPyth_ZZ_365->SetLineWidth(3); hist_ThrPyth_ZZ_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_365 = (TH1F*)input_365->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_365->SetLineColor(kYellow+2); hist_ThrPyth_tt_365->SetMarkerColor(kYellow+1); hist_ThrPyth_tt_365->SetMarkerStyle(21); hist_ThrPyth_tt_365->SetLineWidth(3); hist_ThrPyth_tt_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_365 = (TH1F*)input_365->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_365->SetLineColor(kMagenta+2); hist_ThrPyth_HZ_365->SetMarkerColor(kMagenta+1); hist_ThrPyth_HZ_365->SetMarkerStyle(21); hist_ThrPyth_HZ_365->SetLineWidth(3); hist_ThrPyth_HZ_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW_365 = (TH1F*)input_365->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW_365->SetLineColor(kCyan+2); hist_ThrPyth_HW_365->SetMarkerColor(kCyan+1); hist_ThrPyth_HW_365->SetMarkerStyle(21); hist_ThrPyth_HW_365->SetLineWidth(3); hist_ThrPyth_HW_365->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_365 = (TH1F*)input_365->Get("hist_CprPyth");
	hist_CprPyth_al_365->SetLineColor(kBlack); hist_CprPyth_al_365->SetMarkerColor(kBlack); hist_CprPyth_al_365->SetMarkerStyle(21); hist_CprPyth_al_365->SetLineWidth(3); hist_CprPyth_al_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_365 = (TH1F*)input_365->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_365->SetLineColor(kRed+2); hist_CprPyth_Zq_365->SetMarkerColor(kRed+1); hist_CprPyth_Zq_365->SetMarkerStyle(21); hist_CprPyth_Zq_365->SetLineWidth(3); hist_CprPyth_Zq_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_365 = (TH1F*)input_365->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_365->SetLineColor(kGreen+2); hist_CprPyth_WW_365->SetMarkerColor(kGreen+1); hist_CprPyth_WW_365->SetMarkerStyle(21); hist_CprPyth_WW_365->SetLineWidth(3); hist_CprPyth_WW_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_365 = (TH1F*)input_365->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_365->SetLineColor(kBlue+2); hist_CprPyth_ZZ_365->SetMarkerColor(kBlue+1); hist_CprPyth_ZZ_365->SetMarkerStyle(21); hist_CprPyth_ZZ_365->SetLineWidth(3); hist_CprPyth_ZZ_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_365 = (TH1F*)input_365->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_365->SetLineColor(kYellow+2); hist_CprPyth_tt_365->SetMarkerColor(kYellow+1); hist_CprPyth_tt_365->SetMarkerStyle(21); hist_CprPyth_tt_365->SetLineWidth(3); hist_CprPyth_tt_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_365 = (TH1F*)input_365->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_365->SetLineColor(kMagenta+2); hist_CprPyth_HZ_365->SetMarkerColor(kMagenta+1); hist_CprPyth_HZ_365->SetMarkerStyle(21); hist_CprPyth_HZ_365->SetLineWidth(3); hist_CprPyth_HZ_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW_365 = (TH1F*)input_365->Get("hist_CprPyth_HW");
	hist_CprPyth_HW_365->SetLineColor(kCyan+2); hist_CprPyth_HW_365->SetMarkerColor(kCyan+1); hist_CprPyth_HW_365->SetMarkerStyle(21); hist_CprPyth_HW_365->SetLineWidth(3); hist_CprPyth_HW_365->SetMarkerSize(1);

	TH1F* hist_nHadChg_al_365 = (TH1F*)input_365->Get("hist_nHadChg");
	hist_nHadChg_al_365->SetLineColor(kBlack); hist_nHadChg_al_365->SetMarkerColor(kBlack); hist_nHadChg_al_365->SetMarkerStyle(21); hist_nHadChg_al_365->SetLineWidth(3); hist_nHadChg_al_365->SetMarkerSize(1);
	TH1F* hist_nHadChg_Zq_365 = (TH1F*)input_365->Get("hist_nHadChg_Zq");
	hist_nHadChg_Zq_365->SetLineColor(kRed+2); hist_nHadChg_Zq_365->SetMarkerColor(kRed+1); hist_nHadChg_Zq_365->SetMarkerStyle(21); hist_nHadChg_Zq_365->SetLineWidth(3); hist_nHadChg_Zq_365->SetMarkerSize(1);
	TH1F* hist_nHadChg_WW_365 = (TH1F*)input_365->Get("hist_nHadChg_WW");
	hist_nHadChg_WW_365->SetLineColor(kGreen+2); hist_nHadChg_WW_365->SetMarkerColor(kGreen+1); hist_nHadChg_WW_365->SetMarkerStyle(21); hist_nHadChg_WW_365->SetLineWidth(3); hist_nHadChg_WW_365->SetMarkerSize(1);
	TH1F* hist_nHadChg_ZZ_365 = (TH1F*)input_365->Get("hist_nHadChg_ZZ");
	hist_nHadChg_ZZ_365->SetLineColor(kBlue+2); hist_nHadChg_ZZ_365->SetMarkerColor(kBlue+1); hist_nHadChg_ZZ_365->SetMarkerStyle(21); hist_nHadChg_ZZ_365->SetLineWidth(3); hist_nHadChg_ZZ_365->SetMarkerSize(1);
	TH1F* hist_nHadChg_tt_365 = (TH1F*)input_365->Get("hist_nHadChg_tt");
	hist_nHadChg_tt_365->SetLineColor(kYellow+2); hist_nHadChg_tt_365->SetMarkerColor(kYellow+1); hist_nHadChg_tt_365->SetMarkerStyle(21); hist_nHadChg_tt_365->SetLineWidth(3); hist_nHadChg_tt_365->SetMarkerSize(1);
	TH1F* hist_nHadChg_HZ_365 = (TH1F*)input_365->Get("hist_nHadChg_HZ");
	hist_nHadChg_HZ_365->SetLineColor(kMagenta+2); hist_nHadChg_HZ_365->SetMarkerColor(kMagenta+1); hist_nHadChg_HZ_365->SetMarkerStyle(21); hist_nHadChg_HZ_365->SetLineWidth(3); hist_nHadChg_HZ_365->SetMarkerSize(1);
	TH1F* hist_nHadChg_HW_365 = (TH1F*)input_365->Get("hist_nHadChg_HW");
	hist_nHadChg_HW_365->SetLineColor(kCyan+2); hist_nHadChg_HW_365->SetMarkerColor(kCyan+1); hist_nHadChg_HW_365->SetMarkerStyle(21); hist_nHadChg_HW_365->SetLineWidth(3); hist_nHadChg_HW_365->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_365->SetStats(kFALSE);
	hist_ThrPyth_WW_365->SetStats(kFALSE);
	hist_ThrPyth_ZZ_365->SetStats(kFALSE);
	hist_ThrPyth_tt_365->SetStats(kFALSE);
	hist_ThrPyth_HZ_365->SetStats(kFALSE);
	hist_ThrPyth_HW_365->SetStats(kFALSE);
	hist_CprPyth_al_365->SetStats(kFALSE);
	hist_CprPyth_WW_365->SetStats(kFALSE);
	hist_CprPyth_ZZ_365->SetStats(kFALSE);
	hist_CprPyth_tt_365->SetStats(kFALSE);
	hist_CprPyth_HZ_365->SetStats(kFALSE);
	hist_CprPyth_HW_365->SetStats(kFALSE);
	hist_nHadChg_al_365->SetStats(kFALSE);
	hist_nHadChg_WW_365->SetStats(kFALSE);
	hist_nHadChg_ZZ_365->SetStats(kFALSE);
	hist_nHadChg_tt_365->SetStats(kFALSE);
	hist_nHadChg_HZ_365->SetStats(kFALSE);
	hist_nHadChg_HW_365->SetStats(kFALSE);

	hist_ThrPyth_Zq_365->SetStats(kFALSE);
	hist_CprPyth_Zq_365->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_365->SetTitle("");
	hist_CprPyth_al_365->SetTitle("");
	hist_nHadChg_al_365->SetTitle("");

	hist_ThrPyth_Zq_365->SetTitle("");
	hist_CprPyth_Zq_365->SetTitle("");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit text sizes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_365->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_al_365->GetYaxis()->SetLabelSize(0.04); hist_ThrPyth_al_365->GetYaxis()->SetTitleSize(0.04); hist_ThrPyth_al_365->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_al_365->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_al_365->GetYaxis()->SetLabelSize(0.04); hist_CprPyth_al_365->GetYaxis()->SetTitleSize(0.04); hist_CprPyth_al_365->GetXaxis()->SetTitleSize(0.04); 
	hist_nHadChg_al_365->GetXaxis()->SetLabelSize(0.04); hist_nHadChg_al_365->GetYaxis()->SetLabelSize(0.04); hist_nHadChg_al_365->GetYaxis()->SetTitleSize(0.04); hist_nHadChg_al_365->GetXaxis()->SetTitleSize(0.04);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw Plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 800, 2100);

	// Add legend
	TLegend* lg2 = new TLegend(0.78, 0.70, 0.92, 0.95);
	lg2->AddEntry(hist_ThrPyth_al_365, "ee#rightarrowq#bar{q}", "P");
	lg2->AddEntry(hist_ThrPyth_Zq_365, "ee#rightarrow#gamma/Z", "P");
	lg2->AddEntry(hist_ThrPyth_ZZ_365, "ee#rightarrowZZ", "P");
	lg2->AddEntry(hist_ThrPyth_WW_365, "ee#rightarrowWW", "P");
	lg2->AddEntry(hist_ThrPyth_tt_365, "ee#rightarrowt#bar{t}", "P");
	lg2->AddEntry(hist_ThrPyth_HZ_365, "ee#rightarrowZH", "P");
	lg2->AddEntry(hist_ThrPyth_HW_365, "ee#rightarrow#nu#bar{#nu}H", "P");
	lg2->SetTextSize(0.03);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv2->SetMargin(0, 0, 0, 0); 
	cv2->Divide(1,3);
	for (int i = 1; i <= 3; i++) {
		cv2->cd(i);
		gPad->SetTopMargin(0.017);
		gPad->SetBottomMargin(0.1);
		gPad->SetLeftMargin(0.10);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		gPad->SetLogy();
	}

	hist_ThrPyth_al_365->GetYaxis()->SetTitle("N_{events}");
	hist_CprPyth_al_365->GetYaxis()->SetTitle("N_{events}");
	hist_nHadChg_al_365->GetYaxis()->SetTitle("N_{events}");

	hist_ThrPyth_al_365->SetFillStyle(3001); hist_ThrPyth_al_365->SetFillColor(kBlack); 
	hist_ThrPyth_Zq_365->SetFillStyle(3001); hist_ThrPyth_Zq_365->SetFillColor(kRed); 
	hist_ThrPyth_WW_365->SetFillStyle(3001); hist_ThrPyth_WW_365->SetFillColor(kGreen); 
	hist_ThrPyth_ZZ_365->SetFillStyle(3001); hist_ThrPyth_ZZ_365->SetFillColor(kBlue); 
	hist_ThrPyth_tt_365->SetFillStyle(3001); hist_ThrPyth_tt_365->SetFillColor(kYellow); 
	hist_ThrPyth_HZ_365->SetFillStyle(3001); hist_ThrPyth_HZ_365->SetFillColor(kMagenta+1); 
	hist_ThrPyth_HW_365->SetFillStyle(3001); hist_ThrPyth_HW_365->SetFillColor(kCyan+1); 

	hist_CprPyth_al_365->SetFillStyle(3001); hist_CprPyth_al_365->SetFillColor(kBlack); 
	hist_CprPyth_Zq_365->SetFillStyle(3001); hist_CprPyth_Zq_365->SetFillColor(kRed); 
	hist_CprPyth_WW_365->SetFillStyle(3001); hist_CprPyth_WW_365->SetFillColor(kGreen); 
	hist_CprPyth_ZZ_365->SetFillStyle(3001); hist_CprPyth_ZZ_365->SetFillColor(kBlue); 
	hist_CprPyth_tt_365->SetFillStyle(3001); hist_CprPyth_tt_365->SetFillColor(kYellow); 
	hist_CprPyth_HZ_365->SetFillStyle(3001); hist_CprPyth_HZ_365->SetFillColor(kMagenta+1); 
	hist_CprPyth_HW_365->SetFillStyle(3001); hist_CprPyth_HW_365->SetFillColor(kCyan+1);

	hist_nHadChg_al_365->SetFillStyle(3001); hist_nHadChg_al_365->SetFillColor(kBlack); 
	hist_nHadChg_Zq_365->SetFillStyle(3001); hist_nHadChg_Zq_365->SetFillColor(kRed); 
	hist_nHadChg_WW_365->SetFillStyle(3001); hist_nHadChg_WW_365->SetFillColor(kGreen); 
	hist_nHadChg_ZZ_365->SetFillStyle(3001); hist_nHadChg_ZZ_365->SetFillColor(kBlue); 
	hist_nHadChg_tt_365->SetFillStyle(3001); hist_nHadChg_tt_365->SetFillColor(kYellow); 
	hist_nHadChg_HZ_365->SetFillStyle(3001); hist_nHadChg_HZ_365->SetFillColor(kMagenta+1); 
	hist_nHadChg_HW_365->SetFillStyle(3001); hist_nHadChg_HW_365->SetFillColor(kCyan+1); 

	// Draw
	cv2->cd(1);
	hist_ThrPyth_al_365->Draw("HIST");
	hist_ThrPyth_Zq_365->Draw("HIST SAME");
	hist_ThrPyth_WW_365->Draw("HIST SAME");
	hist_ThrPyth_ZZ_365->Draw("HIST SAME");
	hist_ThrPyth_tt_365->Draw("HIST SAME");
	hist_ThrPyth_HZ_365->Draw("HIST SAME");
	hist_ThrPyth_HW_365->Draw("HIST SAME");
	lg2->Draw("SAME");

	cv2->cd(2);
	hist_CprPyth_al_365->Draw("HIST");
	hist_CprPyth_Zq_365->Draw("HIST SAME");
	hist_CprPyth_WW_365->Draw("HIST SAME");
	hist_CprPyth_ZZ_365->Draw("HIST SAME");
	hist_CprPyth_tt_365->Draw("HIST SAME");
	hist_CprPyth_HZ_365->Draw("HIST SAME");
	hist_CprPyth_HW_365->Draw("HIST SAME");
	lg2->Draw("SAME");

	cv2->cd(3);
	hist_nHadChg_al_365->Draw("HIST");
	hist_nHadChg_Zq_365->Draw("HIST SAME");
	hist_nHadChg_WW_365->Draw("HIST SAME");
	hist_nHadChg_ZZ_365->Draw("HIST SAME");
	hist_nHadChg_tt_365->Draw("HIST SAME");
	hist_nHadChg_HZ_365->Draw("HIST SAME");
	hist_nHadChg_HW_365->Draw("HIST SAME");
	lg2->Draw("SAME");

	// Set limits
	hist_ThrPyth_al_365->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_ThrPyth_al_365->GetXaxis()->SetRangeUser(0,0.45);
	hist_CprPyth_al_365->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_CprPyth_al_365->GetXaxis()->SetRangeUser(0,1.0);	
	hist_nHadChg_al_365->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_nHadChg_al_365->GetXaxis()->SetRangeUser(0,120);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv2->Modified();
	
}