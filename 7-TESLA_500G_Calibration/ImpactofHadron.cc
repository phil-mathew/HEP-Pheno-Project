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

// Code
void ImpactofHadron()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_912_wiHadron = new TFile("5-CutData/cut_FCC912.root", "READ");
	TFile *input_160_wiHadron = new TFile("5-CutData/cut_FCC160.root", "READ");
	TFile *input_240_wiHadron = new TFile("5-CutData/cut_FCC240.root", "READ");
	TFile *input_365_wiHadron = new TFile("5-CutData/cut_FCC365.root", "READ");

	TFile *input_912_woHadron = new TFile("5-CutData/cut_FCC912_woHadron.root", "READ");
	TFile *input_160_woHadron = new TFile("5-CutData/cut_FCC160_woHadron.root", "READ");
	TFile *input_240_woHadron = new TFile("5-CutData/cut_FCC240_woHadron.root", "READ");
	TFile *input_365_woHadron = new TFile("5-CutData/cut_FCC365_woHadron.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defining histograms
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_912_wiHadron = (TH1F*)input_912_wiHadron->Get("hist_ThrPyth_Zq"); hist_ThrPyth_912_wiHadron->SetLineColor(kBlack); hist_ThrPyth_912_wiHadron->SetLineWidth(2);
	TH1F *hist_ThrPyth_912_woHadron = (TH1F*)input_912_woHadron->Get("hist_ThrPyth_Zq"); hist_ThrPyth_912_woHadron->SetLineColor(kBlue); hist_ThrPyth_912_woHadron->SetLineWidth(2);
	TH1F *hist_ThrPyth_160_wiHadron = (TH1F*)input_160_wiHadron->Get("hist_ThrPyth_Zq");
	TH1F *hist_ThrPyth_160_woHadron = (TH1F*)input_160_woHadron->Get("hist_ThrPyth_Zq");
	TH1F *hist_ThrPyth_240_wiHadron = (TH1F*)input_240_wiHadron->Get("hist_ThrPyth_Zq");
	TH1F *hist_ThrPyth_240_woHadron = (TH1F*)input_240_woHadron->Get("hist_ThrPyth_Zq");
	TH1F *hist_ThrPyth_365_wiHadron = (TH1F*)input_365_wiHadron->Get("hist_ThrPyth_Zq");
	TH1F *hist_ThrPyth_365_woHadron = (TH1F*)input_365_woHadron->Get("hist_ThrPyth_Zq");	

	TH1F *hist_CprPyth_912_wiHadron = (TH1F*)input_912_wiHadron->Get("hist_CprPyth_Zq");
	TH1F *hist_CprPyth_912_woHadron = (TH1F*)input_912_woHadron->Get("hist_CprPyth_Zq");
	TH1F *hist_CprPyth_160_wiHadron = (TH1F*)input_160_wiHadron->Get("hist_CprPyth_Zq");
	TH1F *hist_CprPyth_160_woHadron = (TH1F*)input_160_woHadron->Get("hist_CprPyth_Zq");
	TH1F *hist_CprPyth_240_wiHadron = (TH1F*)input_240_wiHadron->Get("hist_CprPyth_Zq");
	TH1F *hist_CprPyth_240_woHadron = (TH1F*)input_240_woHadron->Get("hist_CprPyth_Zq");
	TH1F *hist_CprPyth_365_wiHadron = (TH1F*)input_365_wiHadron->Get("hist_CprPyth_Zq");
	TH1F *hist_CprPyth_365_woHadron = (TH1F*)input_365_woHadron->Get("hist_CprPyth_Zq");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising by area under histogram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	hist_ThrPyth_912_wiHadron->Rebin(5);
	hist_ThrPyth_912_woHadron->Rebin(5);
	hist_ThrPyth_160_wiHadron->Rebin(5);
	hist_ThrPyth_160_woHadron->Rebin(5);
	hist_ThrPyth_240_wiHadron->Rebin(5);
	hist_ThrPyth_240_woHadron->Rebin(5);
	hist_ThrPyth_365_wiHadron->Rebin(5);
	hist_ThrPyth_365_woHadron->Rebin(5);

	hist_CprPyth_912_wiHadron->Rebin(5);
	hist_CprPyth_912_woHadron->Rebin(5);
	hist_CprPyth_160_wiHadron->Rebin(5);
	hist_CprPyth_160_woHadron->Rebin(5);
	hist_CprPyth_240_wiHadron->Rebin(5);
	hist_CprPyth_240_woHadron->Rebin(5);
	hist_CprPyth_365_wiHadron->Rebin(5);
	hist_CprPyth_365_woHadron->Rebin(5);
	
	hist_ThrPyth_912_wiHadron->Scale(1.0/hist_ThrPyth_912_wiHadron->Integral());
	hist_ThrPyth_912_woHadron->Scale(1.0/hist_ThrPyth_912_woHadron->Integral());
	hist_ThrPyth_160_wiHadron->Scale(1.0/hist_ThrPyth_160_wiHadron->Integral());
	hist_ThrPyth_160_woHadron->Scale(1.0/hist_ThrPyth_160_woHadron->Integral());
	hist_ThrPyth_240_wiHadron->Scale(1.0/hist_ThrPyth_240_wiHadron->Integral());
	hist_ThrPyth_240_woHadron->Scale(1.0/hist_ThrPyth_240_woHadron->Integral());
	hist_ThrPyth_365_wiHadron->Scale(1.0/hist_ThrPyth_365_wiHadron->Integral());
	hist_ThrPyth_365_woHadron->Scale(1.0/hist_ThrPyth_365_woHadron->Integral());

	hist_CprPyth_912_wiHadron->Scale(1.0/hist_CprPyth_912_wiHadron->Integral());
	hist_CprPyth_912_woHadron->Scale(1.0/hist_CprPyth_912_woHadron->Integral());
	hist_CprPyth_160_wiHadron->Scale(1.0/hist_CprPyth_160_wiHadron->Integral());
	hist_CprPyth_160_woHadron->Scale(1.0/hist_CprPyth_160_woHadron->Integral());
	hist_CprPyth_240_wiHadron->Scale(1.0/hist_CprPyth_240_wiHadron->Integral());
	hist_CprPyth_240_woHadron->Scale(1.0/hist_CprPyth_240_woHadron->Integral());
	hist_CprPyth_365_wiHadron->Scale(1.0/hist_CprPyth_365_wiHadron->Integral());
	hist_CprPyth_365_woHadron->Scale(1.0/hist_CprPyth_365_woHadron->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Compute hadronisation correction factor
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrCorr_912 = (TH1F*)hist_ThrPyth_912_wiHadron->Clone("hist_ThrCorr_912");
	hist_ThrCorr_912->SetLineColor(kYellow+2); hist_ThrCorr_912->SetMarkerColor(kYellow+2); hist_ThrCorr_912->SetMarkerStyle(kStar); hist_ThrCorr_912->SetLineStyle(1); hist_ThrCorr_912->SetLineWidth(2); hist_ThrCorr_912->SetMarkerSize(1);

	TH1F *hist_ThrCorr_160 = (TH1F*)hist_ThrPyth_160_wiHadron->Clone("hist_ThrCorr_160");
	hist_ThrCorr_160->SetLineColor(kBlue+2); hist_ThrCorr_160->SetMarkerColor(kBlue+2); hist_ThrCorr_160->SetMarkerStyle(kStar); hist_ThrCorr_160->SetLineStyle(7); hist_ThrCorr_160->SetLineWidth(2); hist_ThrCorr_160->SetMarkerSize(1);

	TH1F *hist_ThrCorr_240 = (TH1F*)hist_ThrPyth_240_wiHadron->Clone("hist_ThrCorr_240");
	hist_ThrCorr_240->SetLineColor(kRed+2); hist_ThrCorr_240->SetMarkerColor(kRed+2); hist_ThrCorr_240->SetMarkerStyle(kStar); hist_ThrCorr_240->SetLineStyle(5); hist_ThrCorr_240->SetLineWidth(2); hist_ThrCorr_240->SetMarkerSize(1);

	TH1F *hist_ThrCorr_365 = (TH1F*)hist_ThrPyth_365_wiHadron->Clone("hist_ThrCorr_365");
	hist_ThrCorr_365->SetLineColor(kGreen+2); hist_ThrCorr_365->SetMarkerColor(kGreen+2); hist_ThrCorr_365->SetMarkerStyle(kStar); hist_ThrCorr_365->SetLineStyle(9); hist_ThrCorr_365->SetLineWidth(2); hist_ThrCorr_365->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_CprCorr_912 = (TH1F*)hist_CprPyth_912_wiHadron->Clone("hist_CprCorr_912");
	hist_CprCorr_912->SetLineColor(kYellow+2); hist_CprCorr_912->SetMarkerColor(kYellow+2); hist_CprCorr_912->SetMarkerStyle(kStar); hist_CprCorr_912->SetLineStyle(1); hist_CprCorr_912->SetLineWidth(2); hist_CprCorr_912->SetMarkerSize(1);

	TH1F *hist_CprCorr_160 = (TH1F*)hist_CprPyth_160_wiHadron->Clone("hist_CprCorr_160");
	hist_CprCorr_160->SetLineColor(kBlue+2); hist_CprCorr_160->SetMarkerColor(kBlue+2); hist_CprCorr_160->SetMarkerStyle(kStar); hist_CprCorr_160->SetLineStyle(7); hist_CprCorr_160->SetLineWidth(2); hist_CprCorr_160->SetMarkerSize(1);

	TH1F *hist_CprCorr_240 = (TH1F*)hist_CprPyth_240_wiHadron->Clone("hist_CprCorr_240");
	hist_CprCorr_240->SetLineColor(kRed+2); hist_CprCorr_240->SetMarkerColor(kRed+2); hist_CprCorr_240->SetMarkerStyle(kStar); hist_CprCorr_240->SetLineStyle(5); hist_CprCorr_240->SetLineWidth(2); hist_CprCorr_240->SetMarkerSize(1);

	TH1F *hist_CprCorr_365 = (TH1F*)hist_CprPyth_365_wiHadron->Clone("hist_CprCorr_365");
	hist_CprCorr_365->SetLineColor(kGreen+2); hist_CprCorr_365->SetMarkerColor(kGreen+2); hist_CprCorr_365->SetMarkerStyle(kStar); hist_CprCorr_365->SetLineStyle(9); hist_CprCorr_365->SetLineWidth(2); hist_CprCorr_365->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrCorr_912->Divide(hist_ThrPyth_912_woHadron);
	hist_ThrCorr_160->Divide(hist_ThrPyth_160_woHadron);
	hist_ThrCorr_240->Divide(hist_ThrPyth_240_woHadron);
	hist_ThrCorr_365->Divide(hist_ThrPyth_365_woHadron);

	hist_CprCorr_912->Divide(hist_CprPyth_912_woHadron);
	hist_CprCorr_160->Divide(hist_CprPyth_160_woHadron);
	hist_CprCorr_240->Divide(hist_CprPyth_240_woHadron);
	hist_CprCorr_365->Divide(hist_CprPyth_365_woHadron);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrCorr_912->SetStats(kFALSE);
	hist_ThrCorr_160->SetStats(kFALSE);
	hist_ThrCorr_240->SetStats(kFALSE);
	hist_ThrCorr_365->SetStats(kFALSE);

	hist_CprCorr_912->SetStats(kFALSE);
	hist_CprCorr_160->SetStats(kFALSE);
	hist_CprCorr_240->SetStats(kFALSE);
	hist_CprCorr_365->SetStats(kFALSE);

	hist_ThrCorr_912->GetXaxis()->SetLabelSize(0.04); hist_ThrCorr_912->GetYaxis()->SetLabelSize(0.04); 
	hist_ThrCorr_912->GetXaxis()->SetTitleSize(0.04); hist_ThrCorr_912->GetYaxis()->SetTitleSize(0.04); 
	
	hist_CprCorr_912->GetXaxis()->SetLabelSize(0.04); hist_CprCorr_912->GetYaxis()->SetLabelSize(0.04); 
	hist_CprCorr_912->GetXaxis()->SetTitleSize(0.04); hist_CprCorr_912->GetYaxis()->SetTitleSize(0.04); 

	hist_ThrCorr_912->SetTitle(";(1-T);Hadronisation Correction (Hadron/Parton)");
	hist_CprCorr_912->SetTitle(";C;Hadronisation Correction (Hadron/Parton)");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg1 = new TLegend(0.42, 0.78, 0.66, 0.95);
	lg1->AddEntry(hist_ThrCorr_912, "#sqrt{s} = 91.2 GeV", "L");
	lg1->AddEntry(hist_ThrCorr_160, "#sqrt{s} = 160 GeV", "L");
	lg1->AddEntry(hist_ThrCorr_240, "#sqrt{s} = 240 GeV", "L");
	lg1->AddEntry(hist_ThrCorr_365, "#sqrt{s} = 365 GeV", "L");
	lg1->SetTextSize(0.03);

	// Create canvas
	TCanvas* cv = new TCanvas("cv", "FCC-ee Studies", 800, 1200);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");

	cv->Divide(1,2);
	for (int i = 1; i <= 2; i++) {
		cv->cd(i);
		gPad->SetTopMargin(0.015);
		gPad->SetBottomMargin(0.08);
		gPad->SetLeftMargin(0.11);
		gPad->SetRightMargin(0.02);
		gPad->SetTickx(); gPad->SetTicky();
	}

	hist_ThrCorr_912->GetXaxis()->CenterTitle(); hist_ThrCorr_912->GetYaxis()->CenterTitle();
	hist_CprCorr_912->GetXaxis()->CenterTitle(); hist_CprCorr_912->GetYaxis()->CenterTitle();

	// Draw
	cv->cd(1);
	hist_ThrCorr_912->Draw("HIST C");
	hist_ThrCorr_160->Draw("HIST C SAME");
	hist_ThrCorr_240->Draw("HIST C SAME");
	hist_ThrCorr_365->Draw("HIST C SAME");
	lg1->Draw("SAME");

	cv->cd(2);
	hist_CprCorr_912->Draw("HIST C");
	hist_CprCorr_160->Draw("HIST C SAME");
	hist_CprCorr_240->Draw("HIST C SAME");
	hist_CprCorr_365->Draw("HIST C SAME");
	lg1->Draw("SAME");

	// Set limits
	hist_ThrCorr_912->GetYaxis()->SetRangeUser(0,3.0);
	hist_ThrCorr_912->GetXaxis()->SetRangeUser(0,0.40);
	hist_CprCorr_912->GetYaxis()->SetRangeUser(0,3.0);
	hist_CprCorr_912->GetXaxis()->SetRangeUser(0,1.0);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv->Modified();

}