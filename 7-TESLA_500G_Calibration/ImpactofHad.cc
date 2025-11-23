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

	TFile *input = new TFile("5-CutData/cut_FCC912.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F* hist_ThrPyth_al = (TH1F*)input->Get("hist_ThrPyth");
	hist_ThrPyth_al->SetLineColor(kBlack); hist_ThrPyth_al->SetMarkerColor(kBlack); hist_ThrPyth_al->SetMarkerStyle(21); hist_ThrPyth_al->SetLineWidth(3); hist_ThrPyth_al->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq = (TH1F*)input->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq->SetLineColor(kRed+2); hist_ThrPyth_Zq->SetMarkerColor(kRed+1); hist_ThrPyth_Zq->SetMarkerStyle(21); hist_ThrPyth_Zq->SetLineWidth(3); hist_ThrPyth_Zq->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW = (TH1F*)input->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW->SetLineColor(kGreen+2); hist_ThrPyth_WW->SetMarkerColor(kGreen+1); hist_ThrPyth_WW->SetMarkerStyle(21); hist_ThrPyth_WW->SetLineWidth(3); hist_ThrPyth_WW->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ = (TH1F*)input->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ->SetLineColor(kBlue+2); hist_ThrPyth_ZZ->SetMarkerColor(kBlue+1); hist_ThrPyth_ZZ->SetMarkerStyle(21); hist_ThrPyth_ZZ->SetLineWidth(3); hist_ThrPyth_ZZ->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt = (TH1F*)input->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt->SetLineColor(kYellow+2); hist_ThrPyth_tt->SetMarkerColor(kYellow+1); hist_ThrPyth_tt->SetMarkerStyle(21); hist_ThrPyth_tt->SetLineWidth(3); hist_ThrPyth_tt->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ = (TH1F*)input->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ->SetLineColor(kMagenta+2); hist_ThrPyth_HZ->SetMarkerColor(kMagenta+1); hist_ThrPyth_HZ->SetMarkerStyle(21); hist_ThrPyth_HZ->SetLineWidth(3); hist_ThrPyth_HZ->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW = (TH1F*)input->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW->SetLineColor(kCyan+2); hist_ThrPyth_HW->SetMarkerColor(kCyan+1); hist_ThrPyth_HW->SetMarkerStyle(21); hist_ThrPyth_HW->SetLineWidth(3); hist_ThrPyth_HW->SetMarkerSize(1);

	TH1F* hist_CprPyth_al = (TH1F*)input->Get("hist_CprPyth");
	hist_CprPyth_al->SetLineColor(kBlack); hist_CprPyth_al->SetMarkerColor(kBlack); hist_CprPyth_al->SetMarkerStyle(21); hist_CprPyth_al->SetLineWidth(3); hist_CprPyth_al->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq = (TH1F*)input->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq->SetLineColor(kRed+2); hist_CprPyth_Zq->SetMarkerColor(kRed+1); hist_CprPyth_Zq->SetMarkerStyle(21); hist_CprPyth_Zq->SetLineWidth(3); hist_CprPyth_Zq->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW = (TH1F*)input->Get("hist_CprPyth_WW");
	hist_CprPyth_WW->SetLineColor(kGreen+2); hist_CprPyth_WW->SetMarkerColor(kGreen+1); hist_CprPyth_WW->SetMarkerStyle(21); hist_CprPyth_WW->SetLineWidth(3); hist_CprPyth_WW->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ = (TH1F*)input->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ->SetLineColor(kBlue+2); hist_CprPyth_ZZ->SetMarkerColor(kBlue+1); hist_CprPyth_ZZ->SetMarkerStyle(21); hist_CprPyth_ZZ->SetLineWidth(3); hist_CprPyth_ZZ->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt = (TH1F*)input->Get("hist_CprPyth_tt");
	hist_CprPyth_tt->SetLineColor(kYellow+2); hist_CprPyth_tt->SetMarkerColor(kYellow+1); hist_CprPyth_tt->SetMarkerStyle(21); hist_CprPyth_tt->SetLineWidth(3); hist_CprPyth_tt->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ = (TH1F*)input->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ->SetLineColor(kMagenta+2); hist_CprPyth_HZ->SetMarkerColor(kMagenta+1); hist_CprPyth_HZ->SetMarkerStyle(21); hist_CprPyth_HZ->SetLineWidth(3); hist_CprPyth_HZ->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW = (TH1F*)input->Get("hist_CprPyth_HW");
	hist_CprPyth_HW->SetLineColor(kCyan+2); hist_CprPyth_HW->SetMarkerColor(kCyan+1); hist_CprPyth_HW->SetMarkerStyle(21); hist_CprPyth_HW->SetLineWidth(3); hist_CprPyth_HW->SetMarkerSize(1);

	TH1F* hist_nHadChg_al = (TH1F*)input->Get("hist_nHadChg");
	hist_nHadChg_al->SetLineColor(kBlack); hist_nHadChg_al->SetMarkerColor(kBlack); hist_nHadChg_al->SetMarkerStyle(21); hist_nHadChg_al->SetLineWidth(3); hist_nHadChg_al->SetMarkerSize(1);
	TH1F* hist_nHadChg_Zq = (TH1F*)input->Get("hist_nHadChg_Zq");
	hist_nHadChg_Zq->SetLineColor(kRed+2); hist_nHadChg_Zq->SetMarkerColor(kRed+1); hist_nHadChg_Zq->SetMarkerStyle(21); hist_nHadChg_Zq->SetLineWidth(3); hist_nHadChg_Zq->SetMarkerSize(1);
	TH1F* hist_nHadChg_WW = (TH1F*)input->Get("hist_nHadChg_WW");
	hist_nHadChg_WW->SetLineColor(kGreen+2); hist_nHadChg_WW->SetMarkerColor(kGreen+1); hist_nHadChg_WW->SetMarkerStyle(21); hist_nHadChg_WW->SetLineWidth(3); hist_nHadChg_WW->SetMarkerSize(1);
	TH1F* hist_nHadChg_ZZ = (TH1F*)input->Get("hist_nHadChg_ZZ");
	hist_nHadChg_ZZ->SetLineColor(kBlue+2); hist_nHadChg_ZZ->SetMarkerColor(kBlue+1); hist_nHadChg_ZZ->SetMarkerStyle(21); hist_nHadChg_ZZ->SetLineWidth(3); hist_nHadChg_ZZ->SetMarkerSize(1);
	TH1F* hist_nHadChg_tt = (TH1F*)input->Get("hist_nHadChg_tt");
	hist_nHadChg_tt->SetLineColor(kYellow+2); hist_nHadChg_tt->SetMarkerColor(kYellow+1); hist_nHadChg_tt->SetMarkerStyle(21); hist_nHadChg_tt->SetLineWidth(3); hist_nHadChg_tt->SetMarkerSize(1);
	TH1F* hist_nHadChg_HZ = (TH1F*)input->Get("hist_nHadChg_HZ");
	hist_nHadChg_HZ->SetLineColor(kMagenta+2); hist_nHadChg_HZ->SetMarkerColor(kMagenta+1); hist_nHadChg_HZ->SetMarkerStyle(21); hist_nHadChg_HZ->SetLineWidth(3); hist_nHadChg_HZ->SetMarkerSize(1);
	TH1F* hist_nHadChg_HW = (TH1F*)input->Get("hist_nHadChg_HW");
	hist_nHadChg_HW->SetLineColor(kCyan+2); hist_nHadChg_HW->SetMarkerColor(kCyan+1); hist_nHadChg_HW->SetMarkerStyle(21); hist_nHadChg_HW->SetLineWidth(3); hist_nHadChg_HW->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al->SetStats(kFALSE);
	hist_ThrPyth_WW->SetStats(kFALSE);
	hist_ThrPyth_ZZ->SetStats(kFALSE);
	hist_ThrPyth_tt->SetStats(kFALSE);
	hist_ThrPyth_HZ->SetStats(kFALSE);
	hist_ThrPyth_HW->SetStats(kFALSE);
	hist_CprPyth_al->SetStats(kFALSE);
	hist_CprPyth_WW->SetStats(kFALSE);
	hist_CprPyth_ZZ->SetStats(kFALSE);
	hist_CprPyth_tt->SetStats(kFALSE);
	hist_CprPyth_HZ->SetStats(kFALSE);
	hist_CprPyth_HW->SetStats(kFALSE);
	hist_nHadChg_al->SetStats(kFALSE);
	hist_nHadChg_WW->SetStats(kFALSE);
	hist_nHadChg_ZZ->SetStats(kFALSE);
	hist_nHadChg_tt->SetStats(kFALSE);
	hist_nHadChg_HZ->SetStats(kFALSE);
	hist_nHadChg_HW->SetStats(kFALSE);

	hist_ThrPyth_Zq->SetStats(kFALSE);
	hist_CprPyth_Zq->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al->SetTitle("");
	hist_CprPyth_al->SetTitle("");
	hist_nHadChg_al->SetTitle("");

	hist_ThrPyth_Zq->SetTitle("");
	hist_CprPyth_Zq->SetTitle("");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit text sizes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_al->GetYaxis()->SetLabelSize(0.04); hist_ThrPyth_al->GetYaxis()->SetTitleSize(0.04); hist_ThrPyth_al->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_al->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_al->GetYaxis()->SetLabelSize(0.04); hist_CprPyth_al->GetYaxis()->SetTitleSize(0.04); hist_CprPyth_al->GetXaxis()->SetTitleSize(0.04); 
	hist_nHadChg_al->GetXaxis()->SetLabelSize(0.04); hist_nHadChg_al->GetYaxis()->SetLabelSize(0.04); hist_nHadChg_al->GetYaxis()->SetTitleSize(0.04); hist_nHadChg_al->GetXaxis()->SetTitleSize(0.04);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw Plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 800, 2100);

	// Add legend
	TLegend* lg2 = new TLegend(0.78, 0.70, 0.92, 0.95);
	lg2->AddEntry(hist_ThrPyth_al, "ee#rightarrowq#bar{q}", "P");
	lg2->AddEntry(hist_ThrPyth_Zq, "ee#rightarrow#gamma/Z", "P");
	lg2->AddEntry(hist_ThrPyth_ZZ, "ee#rightarrowZZ", "P");
	lg2->AddEntry(hist_ThrPyth_WW, "ee#rightarrowWW", "P");
	lg2->AddEntry(hist_ThrPyth_tt, "ee#rightarrowt#bar{t}", "P");
	lg2->AddEntry(hist_ThrPyth_HZ, "ee#rightarrowZH", "P");
	lg2->AddEntry(hist_ThrPyth_HW, "ee#rightarrow#nu#bar{#nu}H", "P");
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

	hist_ThrPyth_al->GetXaxis()->CenterTitle(); hist_ThrPyth_al->GetYaxis()->CenterTitle();
	hist_CprPyth_al->GetXaxis()->CenterTitle(); hist_CprPyth_al->GetYaxis()->CenterTitle();
	hist_nHadChg_al->GetXaxis()->CenterTitle(); hist_nHadChg_al->GetYaxis()->CenterTitle();

	hist_ThrPyth_al->GetYaxis()->SetTitle("N_{events}");
	hist_CprPyth_al->GetYaxis()->SetTitle("N_{events}");
	hist_nHadChg_al->GetYaxis()->SetTitle("N_{events}");

	hist_ThrPyth_al->SetFillStyle(3001); hist_ThrPyth_al->SetFillColor(kBlack); 
	hist_ThrPyth_Zq->SetFillStyle(3001); hist_ThrPyth_Zq->SetFillColor(kRed); 
	hist_ThrPyth_WW->SetFillStyle(3001); hist_ThrPyth_WW->SetFillColor(kGreen); 
	hist_ThrPyth_ZZ->SetFillStyle(3001); hist_ThrPyth_ZZ->SetFillColor(kBlue); 
	hist_ThrPyth_tt->SetFillStyle(3001); hist_ThrPyth_tt->SetFillColor(kYellow); 
	hist_ThrPyth_HZ->SetFillStyle(3001); hist_ThrPyth_HZ->SetFillColor(kMagenta+1); 
	hist_ThrPyth_HW->SetFillStyle(3001); hist_ThrPyth_HW->SetFillColor(kCyan+1); 

	hist_CprPyth_al->SetFillStyle(3001); hist_CprPyth_al->SetFillColor(kBlack); 
	hist_CprPyth_Zq->SetFillStyle(3001); hist_CprPyth_Zq->SetFillColor(kRed); 
	hist_CprPyth_WW->SetFillStyle(3001); hist_CprPyth_WW->SetFillColor(kGreen); 
	hist_CprPyth_ZZ->SetFillStyle(3001); hist_CprPyth_ZZ->SetFillColor(kBlue); 
	hist_CprPyth_tt->SetFillStyle(3001); hist_CprPyth_tt->SetFillColor(kYellow); 
	hist_CprPyth_HZ->SetFillStyle(3001); hist_CprPyth_HZ->SetFillColor(kMagenta+1); 
	hist_CprPyth_HW->SetFillStyle(3001); hist_CprPyth_HW->SetFillColor(kCyan+1);

	hist_nHadChg_al->SetFillStyle(3001); hist_nHadChg_al->SetFillColor(kBlack); 
	hist_nHadChg_Zq->SetFillStyle(3001); hist_nHadChg_Zq->SetFillColor(kRed); 
	hist_nHadChg_WW->SetFillStyle(3001); hist_nHadChg_WW->SetFillColor(kGreen); 
	hist_nHadChg_ZZ->SetFillStyle(3001); hist_nHadChg_ZZ->SetFillColor(kBlue); 
	hist_nHadChg_tt->SetFillStyle(3001); hist_nHadChg_tt->SetFillColor(kYellow); 
	hist_nHadChg_HZ->SetFillStyle(3001); hist_nHadChg_HZ->SetFillColor(kMagenta+1); 
	hist_nHadChg_HW->SetFillStyle(3001); hist_nHadChg_HW->SetFillColor(kCyan+1); 

	hist_ThrPyth_al->Rebin(2);
	hist_ThrPyth_Zq->Rebin(2);
	hist_ThrPyth_WW->Rebin(2);
	hist_ThrPyth_ZZ->Rebin(2);
	hist_ThrPyth_tt->Rebin(2);
	hist_ThrPyth_HZ->Rebin(2);
	hist_ThrPyth_HW->Rebin(2);

	hist_CprPyth_al->Rebin(2);
	hist_CprPyth_Zq->Rebin(2);
	hist_CprPyth_WW->Rebin(2);
	hist_CprPyth_ZZ->Rebin(2);
	hist_CprPyth_tt->Rebin(2);
	hist_CprPyth_HZ->Rebin(2);
	hist_CprPyth_HW->Rebin(2);

	// Draw
	cv2->cd(1);
	hist_ThrPyth_al->Draw("HIST");
	hist_ThrPyth_Zq->Draw("HIST SAME");
	hist_ThrPyth_WW->Draw("HIST SAME");
	hist_ThrPyth_ZZ->Draw("HIST SAME");
	hist_ThrPyth_tt->Draw("HIST SAME");
	hist_ThrPyth_HZ->Draw("HIST SAME");
	hist_ThrPyth_HW->Draw("HIST SAME");
	lg2->Draw("SAME");

	cv2->cd(2);
	hist_CprPyth_al->Draw("HIST");
	hist_CprPyth_Zq->Draw("HIST SAME");
	hist_CprPyth_WW->Draw("HIST SAME");
	hist_CprPyth_ZZ->Draw("HIST SAME");
	hist_CprPyth_tt->Draw("HIST SAME");
	hist_CprPyth_HZ->Draw("HIST SAME");
	hist_CprPyth_HW->Draw("HIST SAME");
	lg2->Draw("SAME");

	cv2->cd(3);
	hist_nHadChg_al->Draw("HIST");
	hist_nHadChg_Zq->Draw("HIST SAME");
	hist_nHadChg_WW->Draw("HIST SAME");
	hist_nHadChg_ZZ->Draw("HIST SAME");
	hist_nHadChg_tt->Draw("HIST SAME");
	hist_nHadChg_HZ->Draw("HIST SAME");
	hist_nHadChg_HW->Draw("HIST SAME");
	lg2->Draw("SAME");

	// Set limits
	hist_ThrPyth_al->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_ThrPyth_al->GetXaxis()->SetRangeUser(0,0.45);
	hist_CprPyth_al->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_CprPyth_al->GetXaxis()->SetRangeUser(0,1.0);	
	hist_nHadChg_al->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_nHadChg_al->GetXaxis()->SetRangeUser(0,120);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv2->Modified();
	
}