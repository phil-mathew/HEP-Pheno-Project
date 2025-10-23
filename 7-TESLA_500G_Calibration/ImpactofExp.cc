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
void ImpactofExp() {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_EXPDATA = TFile::Open("3-LEPdata/EXPDATA.root");

	TFile *input_912 = new TFile("5-CutData/cut_FCC912.root", "READ");
	TFile *input_161 = new TFile("5-CutData/cut_FCC161.root", "READ");
	TFile *input_183 = new TFile("5-CutData/cut_FCC183.root", "READ");
	TFile *input_200 = new TFile("5-CutData/cut_FCC200.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Importing raw TEXT data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F* hist_ThrExAL_912 = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_912_THR");
	TH1F* hist_ThrExAL_161 = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_161_THR");
	TH1F* hist_ThrExAL_183 = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_183_THR");
	TH1F* hist_ThrExAL_200 = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_200_THR");

	TH1F* hist_CprExAL_912 = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_912_CPR");
	TH1F* hist_CprExAL_161 = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_161_CPR");
	TH1F* hist_CprExAL_183 = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_183_CPR");
	TH1F* hist_CprExAL_200 = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_200_CPR");

	TH1F* hist_ThrExL3_912 = (TH1F*)input_EXPDATA->Get("hist_EXP_LL3_912_THR");
	TH1F* hist_ThrExL3_161 = (TH1F*)input_EXPDATA->Get("hist_EXP_LL3_161_THR");
	TH1F* hist_ThrExL3_183 = (TH1F*)input_EXPDATA->Get("hist_EXP_LL3_183_THR");
	TH1F* hist_ThrExL3_200 = (TH1F*)input_EXPDATA->Get("hist_EXP_LL3_200_THR");

	TH1F* hist_CprExL3_912 = (TH1F*)input_EXPDATA->Get("hist_EXP_LL3_912_CPR");
	TH1F* hist_CprExL3_161 = (TH1F*)input_EXPDATA->Get("hist_EXP_LL3_161_CPR");
	TH1F* hist_CprExL3_183 = (TH1F*)input_EXPDATA->Get("hist_EXP_LL3_183_CPR");
	TH1F* hist_CprExL3_200 = (TH1F*)input_EXPDATA->Get("hist_EXP_LL3_200_CPR");

	TH1F* hist_HjmExAL_912 = (TH1F*)input_EXPDATA->Get("hist_EXP_ALP_912_RHO");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F *hist_ThrPyth_912 = (TH1F*)input_912->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_912->SetLineColor(kBlack); hist_ThrPyth_912->SetMarkerColor(kBlack); hist_ThrPyth_912->SetMarkerStyle(26); hist_ThrPyth_912->SetLineWidth(2); hist_ThrPyth_912->SetMarkerSize(2);
	hist_ThrExL3_912->SetLineColor(kBlue); hist_ThrExL3_912->SetMarkerColor(kBlue); hist_ThrExL3_912->SetMarkerStyle(53); hist_ThrExL3_912->SetLineWidth(1); hist_ThrExL3_912->SetMarkerSize(1.5);
	hist_ThrExAL_912->SetLineColor(kRed+2); hist_ThrExAL_912->SetMarkerColor(kRed+2); hist_ThrExAL_912->SetMarkerStyle(53); hist_ThrExAL_912->SetLineWidth(1); hist_ThrExAL_912->SetMarkerSize(1.5);

	TH1F *hist_ThrPyth_161 = (TH1F*)input_161->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_161->SetLineColor(kBlack); hist_ThrPyth_161->SetMarkerColor(kBlack); hist_ThrPyth_161->SetMarkerStyle(26); hist_ThrPyth_161->SetLineWidth(2); hist_ThrPyth_161->SetMarkerSize(2);
	hist_ThrExL3_161->SetLineColor(kBlue); hist_ThrExL3_161->SetMarkerColor(kBlue); hist_ThrExL3_161->SetMarkerStyle(53); hist_ThrExL3_161->SetLineWidth(1); hist_ThrExL3_161->SetMarkerSize(1.5);
	hist_ThrExAL_161->SetLineColor(kRed+2); hist_ThrExAL_161->SetMarkerColor(kRed+2); hist_ThrExAL_161->SetMarkerStyle(53); hist_ThrExAL_161->SetLineWidth(1); hist_ThrExAL_161->SetMarkerSize(1.5);

	TH1F *hist_ThrPyth_183 = (TH1F*)input_183->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_183->SetLineColor(kBlack); hist_ThrPyth_183->SetMarkerColor(kBlack); hist_ThrPyth_183->SetMarkerStyle(26); hist_ThrPyth_183->SetLineWidth(2); hist_ThrPyth_183->SetMarkerSize(2);
	hist_ThrExL3_183->SetLineColor(kBlue); hist_ThrExL3_183->SetMarkerColor(kBlue); hist_ThrExL3_183->SetMarkerStyle(53); hist_ThrExL3_183->SetLineWidth(1); hist_ThrExL3_183->SetMarkerSize(1.5);
	hist_ThrExAL_183->SetLineColor(kRed+2); hist_ThrExAL_183->SetMarkerColor(kRed+2); hist_ThrExAL_183->SetMarkerStyle(53); hist_ThrExAL_183->SetLineWidth(1);	hist_ThrExAL_183->SetMarkerSize(1.5);

	TH1F *hist_ThrPyth_200 = (TH1F*)input_200->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_200->SetLineColor(kBlack); hist_ThrPyth_200->SetMarkerColor(kBlack); hist_ThrPyth_200->SetMarkerStyle(26); hist_ThrPyth_200->SetLineWidth(2); hist_ThrPyth_200->SetMarkerSize(2);
	hist_ThrExL3_200->SetLineColor(kBlue); hist_ThrExL3_200->SetMarkerColor(kBlue); hist_ThrExL3_200->SetMarkerStyle(53); hist_ThrExL3_200->SetLineWidth(1); hist_ThrExL3_200->SetMarkerSize(1.5);
	hist_ThrExAL_200->SetLineColor(kRed+2); hist_ThrExAL_200->SetMarkerColor(kRed+2); hist_ThrExAL_200->SetMarkerStyle(53); hist_ThrExAL_200->SetLineWidth(1);	hist_ThrExAL_200->SetMarkerSize(1.5);

	TH1F *hist_CprPyth_912 = (TH1F*)input_912->Get("hist_CprPyth_Zq");
	hist_CprPyth_912->SetLineColor(kBlack); hist_CprPyth_912->SetMarkerColor(kBlack); hist_CprPyth_912->SetMarkerStyle(26); hist_CprPyth_912->SetLineWidth(2); hist_CprPyth_912->SetMarkerSize(2);
	hist_CprExL3_912->SetLineColor(kBlue); hist_CprExL3_912->SetMarkerColor(kBlue); hist_CprExL3_912->SetMarkerStyle(53); hist_CprExL3_912->SetLineWidth(1); hist_CprExL3_912->SetMarkerSize(1.5);
	hist_CprExAL_912->SetLineColor(kRed+2); hist_CprExAL_912->SetMarkerColor(kRed+2); hist_CprExAL_912->SetMarkerStyle(53); hist_CprExAL_912->SetLineWidth(1); hist_CprExAL_912->SetMarkerSize(1.5);

	TH1F *hist_CprPyth_161 = (TH1F*)input_161->Get("hist_CprPyth_Zq");
	hist_CprPyth_161->SetLineColor(kBlack); hist_CprPyth_161->SetMarkerColor(kBlack); hist_CprPyth_161->SetMarkerStyle(26); hist_CprPyth_161->SetLineWidth(2); hist_CprPyth_161->SetMarkerSize(2);
	hist_CprExL3_161->SetLineColor(kBlue); hist_CprExL3_161->SetMarkerColor(kBlue); hist_CprExL3_161->SetMarkerStyle(53); hist_CprExL3_161->SetLineWidth(1); hist_CprExL3_161->SetMarkerSize(1.5);
	hist_CprExAL_161->SetLineColor(kRed+2); hist_CprExAL_161->SetMarkerColor(kRed+2); hist_CprExAL_161->SetMarkerStyle(53); hist_CprExAL_161->SetLineWidth(1); hist_CprExAL_161->SetMarkerSize(1.5);

	TH1F *hist_CprPyth_183 = (TH1F*)input_183->Get("hist_CprPyth_Zq");
	hist_CprPyth_183->SetLineColor(kBlack); hist_CprPyth_183->SetMarkerColor(kBlack); hist_CprPyth_183->SetMarkerStyle(26); hist_CprPyth_183->SetLineWidth(2); hist_CprPyth_183->SetMarkerSize(2);
	hist_CprExL3_183->SetLineColor(kBlue); hist_CprExL3_183->SetMarkerColor(kBlue); hist_CprExL3_183->SetMarkerStyle(53); hist_CprExL3_183->SetLineWidth(1); hist_CprExL3_183->SetMarkerSize(1.5);
	hist_CprExAL_183->SetLineColor(kRed+2); hist_CprExAL_183->SetMarkerColor(kRed+2); hist_CprExAL_183->SetMarkerStyle(53); hist_CprExAL_183->SetLineWidth(1);	hist_CprExAL_183->SetMarkerSize(1.5);

	TH1F *hist_CprPyth_200 = (TH1F*)input_200->Get("hist_CprPyth_Zq");
	hist_CprPyth_200->SetLineColor(kBlack); hist_CprPyth_200->SetMarkerColor(kBlack); hist_CprPyth_200->SetMarkerStyle(26); hist_CprPyth_200->SetLineWidth(2); hist_CprPyth_200->SetMarkerSize(2);
	hist_CprExL3_200->SetLineColor(kBlue); hist_CprExL3_200->SetMarkerColor(kBlue); hist_CprExL3_200->SetMarkerStyle(53); hist_CprExL3_200->SetLineWidth(1); hist_CprExL3_200->SetMarkerSize(1.5);
	hist_CprExAL_200->SetLineColor(kRed+2); hist_CprExAL_200->SetMarkerColor(kRed+2); hist_CprExAL_200->SetMarkerStyle(53); hist_CprExAL_200->SetLineWidth(1);	hist_CprExAL_200->SetMarkerSize(1.5);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising by area under histogram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	hist_ThrPyth_912->Scale(1.0/hist_ThrPyth_912->Integral("width"));
	hist_CprPyth_912->Scale(1.0/hist_CprPyth_912->Integral("width"));

	hist_ThrPyth_161->Scale(1.0/hist_ThrPyth_161->Integral("width"));
	hist_CprPyth_161->Scale(1.0/hist_CprPyth_161->Integral("width"));

	hist_ThrPyth_183->Scale(1.0/hist_ThrPyth_183->Integral("width"));
	hist_CprPyth_183->Scale(1.0/hist_CprPyth_183->Integral("width"));

	hist_ThrPyth_200->Scale(1.0/hist_ThrPyth_200->Integral("width"));
	hist_CprPyth_200->Scale(1.0/hist_CprPyth_200->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912->SetStats(kFALSE);
	hist_ThrExL3_912->SetStats(kFALSE);
	hist_ThrExAL_912->SetStats(kFALSE);

	hist_ThrPyth_161->SetStats(kFALSE);
	hist_ThrExL3_161->SetStats(kFALSE);
	hist_ThrExAL_161->SetStats(kFALSE);

	hist_ThrPyth_183->SetStats(kFALSE);
	hist_ThrExL3_183->SetStats(kFALSE);
	hist_ThrExAL_183->SetStats(kFALSE);

	hist_ThrPyth_200->SetStats(kFALSE);
	hist_ThrExL3_200->SetStats(kFALSE);
	hist_ThrExAL_200->SetStats(kFALSE);

	hist_CprPyth_912->SetStats(kFALSE);
	hist_CprExL3_912->SetStats(kFALSE);
	hist_CprExAL_912->SetStats(kFALSE);

	hist_CprPyth_161->SetStats(kFALSE);
	hist_CprExL3_161->SetStats(kFALSE);
	hist_CprExAL_161->SetStats(kFALSE);

	hist_CprPyth_183->SetStats(kFALSE);
	hist_CprExL3_183->SetStats(kFALSE);
	hist_CprExAL_183->SetStats(kFALSE);

	hist_CprPyth_200->SetStats(kFALSE);
	hist_CprExL3_200->SetStats(kFALSE);
	hist_CprExAL_200->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912->GetXaxis()->SetLabelSize(0.04);
	hist_ThrPyth_912->GetXaxis()->SetTitleSize(0.04);
	hist_ThrPyth_912->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_912->GetYaxis()->SetTitleSize(0.04);

	hist_ThrPyth_161->GetXaxis()->SetLabelSize(0.04);
	hist_ThrPyth_161->GetXaxis()->SetTitleSize(0.04);
	hist_ThrPyth_161->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_161->GetYaxis()->SetTitleSize(0.04);

	hist_ThrPyth_183->GetXaxis()->SetLabelSize(0.04);
	hist_ThrPyth_183->GetXaxis()->SetTitleSize(0.04);
	hist_ThrPyth_183->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_183->GetYaxis()->SetTitleSize(0.04);

	hist_ThrPyth_200->GetXaxis()->SetLabelSize(0.04);
	hist_ThrPyth_200->GetXaxis()->SetTitleSize(0.04);
	hist_ThrPyth_200->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_200->GetYaxis()->SetTitleSize(0.04);

	hist_CprPyth_912->GetXaxis()->SetLabelSize(0.04);
	hist_CprPyth_912->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_912->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_912->GetYaxis()->SetTitleSize(0.04);

	hist_CprPyth_161->GetXaxis()->SetLabelSize(0.04);
	hist_CprPyth_161->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_161->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_161->GetYaxis()->SetTitleSize(0.04);

	hist_CprPyth_183->GetXaxis()->SetLabelSize(0.04);
	hist_CprPyth_183->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_183->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_183->GetYaxis()->SetTitleSize(0.04);

	hist_CprPyth_200->GetXaxis()->SetLabelSize(0.04);
	hist_CprPyth_200->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_200->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_200->GetYaxis()->SetTitleSize(0.04);

	hist_ThrPyth_912->SetTitle("");
	hist_ThrPyth_161->SetTitle("");
	hist_ThrPyth_183->SetTitle("");
	hist_ThrPyth_200->SetTitle("");

	hist_CprPyth_912->SetTitle("");
	hist_CprPyth_161->SetTitle("");
	hist_CprPyth_183->SetTitle("");
	hist_CprPyth_200->SetTitle("");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv1 = new TCanvas("cv1", "FCC-ee ISR Studies", 850, 1600);

	// Add legend
	TLegend *lg = new TLegend(0.75, 0.80, 0.92, 0.95);
	lg->AddEntry(hist_ThrPyth_912, "PYTHIA", "L");
	lg->AddEntry(hist_ThrExAL_912, "ALEPH", "P");
	lg->AddEntry(hist_ThrExL3_912, "L3", "P");
	lg->SetTextSize(0.04);

	// Beautify
	// gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv1->SetMargin(0, 0, 0, 0); 
	cv1->Divide(1,2);
	for (int i = 1; i <= 2; i++) {
		cv1->cd(i);
		gPad->SetTopMargin(0.020);
		gPad->SetBottomMargin(0.1);
		gPad->SetLeftMargin(0.15);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		// gPad->SetGridx(); gPad->SetGridy();
		gPad->SetLogy();
	}

	hist_ThrExAL_200->SetBinError(hist_ThrExAL_200->FindBin(0.25), 9E-2);
	hist_ThrExAL_200->SetBinError(hist_ThrExAL_200->FindBin(0.30), 5E-2);
	
	hist_ThrExL3_161->SetBinError(hist_ThrExL3_161->FindBin(0.325), 2E-2); 
	hist_ThrExL3_183->SetBinError(hist_ThrExL3_183->FindBin(0.325), 9E-2);
	hist_ThrExL3_200->SetBinError(hist_ThrExL3_200->FindBin(0.325), 1E-1);

	hist_ThrExL3_200->SetBinError(hist_ThrExL3_200->FindBin(0.375), 1E-2); 

	hist_CprExL3_200->SetBinError(hist_CprExL3_200->FindBin(0.75), 1E-1);

	hist_CprExL3_161->SetBinError(hist_CprExL3_161->FindBin(0.80), 2E-2);
	hist_CprExL3_183->SetBinError(hist_CprExL3_183->FindBin(0.80), 3E-2);

	hist_CprExL3_161->SetBinError(hist_CprExL3_161->FindBin(0.85), 2E-3); 
	hist_CprExL3_183->SetBinError(hist_CprExL3_183->FindBin(0.85), 6E-2);

	hist_CprExAL_161->SetBinError(hist_CprExAL_161->FindBin(0.85), 1E-1); 
	hist_CprExAL_183->SetBinError(hist_CprExAL_183->FindBin(0.85), 5E-2);
	hist_CprExAL_200->SetBinError(hist_CprExAL_200->FindBin(0.85), 2E-2);

	hist_CprExL3_200->SetBinError(hist_CprExL3_200->FindBin(0.95), 4E-3); 

	// Draw
	cv1->cd(1);

	hist_ThrPyth_912->Draw("HIST");
	hist_ThrExL3_912->Draw("E1 SAME");
	hist_ThrExAL_912->Draw("E1 SAME");

	hist_ThrPyth_161->Scale(1E3);
	hist_ThrPyth_161->Draw("HIST SAME");
	hist_ThrExL3_161->Scale(1E3);
	hist_ThrExL3_161->Draw("E1 SAME");
	hist_ThrExAL_161->Scale(1E3);
	hist_ThrExAL_161->Draw("E1 SAME");
	
	hist_ThrPyth_183->Scale(1E6);
	hist_ThrPyth_183->Draw("HIST SAME");
	hist_ThrExL3_183->Scale(1E6);
	hist_ThrExL3_183->Draw("E1 SAME");
	hist_ThrExAL_183->Scale(1E6);
	hist_ThrExAL_183->Draw("E1 SAME");

	hist_ThrPyth_200->Scale(1E9);
	hist_ThrPyth_200->Draw("HIST SAME");
	hist_ThrExL3_200->Scale(1E9);
	hist_ThrExL3_200->Draw("E1 SAME");
	hist_ThrExAL_200->Scale(1E9);
	hist_ThrExAL_200->Draw("E1 SAME");

	lg->Draw("SAME");	

	cv1->cd(2);

	hist_CprPyth_912->Draw("HIST");
	hist_CprExL3_912->Draw("E1 SAME");
	hist_CprExAL_912->Draw("E1 SAME");

	hist_CprPyth_161->Scale(1E3);
	hist_CprPyth_161->Draw("HIST SAME");
	hist_CprExL3_161->Scale(1E3);
	hist_CprExL3_161->Draw("E1 SAME");
	hist_CprExAL_161->Scale(1E3);
	hist_CprExAL_161->Draw("E1 SAME");
	
	hist_CprPyth_183->Scale(1E6);
	hist_CprPyth_183->Draw("HIST SAME");
	hist_CprExL3_183->Scale(1E6);
	hist_CprExL3_183->Draw("E1 SAME");
	hist_CprExAL_183->Scale(1E6);
	hist_CprExAL_183->Draw("E1 SAME");

	hist_CprPyth_200->Scale(1E9);
	hist_CprPyth_200->Draw("HIST SAME");
	hist_CprExL3_200->Scale(1E9);
	hist_CprExL3_200->Draw("E1 SAME");
	hist_CprExAL_200->Scale(1E9);
	hist_CprExAL_200->Draw("E1 X0 SAME");

	lg->Draw("SAME");

	// Set limits
	hist_ThrPyth_912->GetYaxis()->SetRangeUser(1E-3,1E12);
	hist_ThrPyth_912->GetXaxis()->SetRangeUser(0,0.4);
	hist_CprPyth_912->GetYaxis()->SetRangeUser(1E-3,1E12);
	hist_CprPyth_912->GetXaxis()->SetRangeUser(0,1.0);	

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv1->Modified();

}