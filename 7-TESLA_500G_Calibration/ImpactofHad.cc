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
	hist_ThrPyth_al->SetLineColor(kBlack); hist_ThrPyth_al->SetMarkerColor(kBlack); hist_ThrPyth_al->SetMarkerStyle(21); hist_ThrPyth_al->SetLineWidth(1); hist_ThrPyth_al->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq = (TH1F*)input->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq->SetLineColor(kRed+2); hist_ThrPyth_Zq->SetMarkerColor(kRed+1); hist_ThrPyth_Zq->SetMarkerStyle(21); hist_ThrPyth_Zq->SetLineWidth(1); hist_ThrPyth_Zq->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW = (TH1F*)input->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW->SetLineColor(kGreen+2); hist_ThrPyth_WW->SetMarkerColor(kGreen+1); hist_ThrPyth_WW->SetMarkerStyle(21); hist_ThrPyth_WW->SetLineWidth(1); hist_ThrPyth_WW->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ = (TH1F*)input->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ->SetLineColor(kBlue+2); hist_ThrPyth_ZZ->SetMarkerColor(kBlue+1); hist_ThrPyth_ZZ->SetMarkerStyle(21); hist_ThrPyth_ZZ->SetLineWidth(1); hist_ThrPyth_ZZ->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt = (TH1F*)input->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt->SetLineColor(kYellow+2); hist_ThrPyth_tt->SetMarkerColor(kYellow+1); hist_ThrPyth_tt->SetMarkerStyle(21); hist_ThrPyth_tt->SetLineWidth(1); hist_ThrPyth_tt->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ = (TH1F*)input->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ->SetLineColor(kMagenta+2); hist_ThrPyth_HZ->SetMarkerColor(kMagenta+1); hist_ThrPyth_HZ->SetMarkerStyle(21); hist_ThrPyth_HZ->SetLineWidth(1); hist_ThrPyth_HZ->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW = (TH1F*)input->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW->SetLineColor(kCyan+2); hist_ThrPyth_HW->SetMarkerColor(kCyan+1); hist_ThrPyth_HW->SetMarkerStyle(21); hist_ThrPyth_HW->SetLineWidth(1); hist_ThrPyth_HW->SetMarkerSize(1);

	TH1F* hist_CprPyth_al = (TH1F*)input->Get("hist_CprPyth");
	hist_CprPyth_al->SetLineColor(kBlack); hist_CprPyth_al->SetMarkerColor(kBlack); hist_CprPyth_al->SetMarkerStyle(21); hist_CprPyth_al->SetLineWidth(1); hist_CprPyth_al->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq = (TH1F*)input->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq->SetLineColor(kRed+2); hist_CprPyth_Zq->SetMarkerColor(kRed+1); hist_CprPyth_Zq->SetMarkerStyle(21); hist_CprPyth_Zq->SetLineWidth(1); hist_CprPyth_Zq->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW = (TH1F*)input->Get("hist_CprPyth_WW");
	hist_CprPyth_WW->SetLineColor(kGreen+2); hist_CprPyth_WW->SetMarkerColor(kGreen+1); hist_CprPyth_WW->SetMarkerStyle(21); hist_CprPyth_WW->SetLineWidth(1); hist_CprPyth_WW->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ = (TH1F*)input->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ->SetLineColor(kBlue+2); hist_CprPyth_ZZ->SetMarkerColor(kBlue+1); hist_CprPyth_ZZ->SetMarkerStyle(21); hist_CprPyth_ZZ->SetLineWidth(1); hist_CprPyth_ZZ->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt = (TH1F*)input->Get("hist_CprPyth_tt");
	hist_CprPyth_tt->SetLineColor(kYellow+2); hist_CprPyth_tt->SetMarkerColor(kYellow+1); hist_CprPyth_tt->SetMarkerStyle(21); hist_CprPyth_tt->SetLineWidth(1); hist_CprPyth_tt->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ = (TH1F*)input->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ->SetLineColor(kMagenta+2); hist_CprPyth_HZ->SetMarkerColor(kMagenta+1); hist_CprPyth_HZ->SetMarkerStyle(21); hist_CprPyth_HZ->SetLineWidth(1); hist_CprPyth_HZ->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW = (TH1F*)input->Get("hist_CprPyth_HW");
	hist_CprPyth_HW->SetLineColor(kCyan+2); hist_CprPyth_HW->SetMarkerColor(kCyan+1); hist_CprPyth_HW->SetMarkerStyle(21); hist_CprPyth_HW->SetLineWidth(1); hist_CprPyth_HW->SetMarkerSize(1);

	TH1F* hist_nHadChg_al = (TH1F*)input->Get("hist_nHadChg");
	hist_nHadChg_al->SetLineColor(kBlack); hist_nHadChg_al->SetMarkerColor(kBlack); hist_nHadChg_al->SetMarkerStyle(21); hist_nHadChg_al->SetLineWidth(1); hist_nHadChg_al->SetMarkerSize(1);
	TH1F* hist_nHadChg_Zq = (TH1F*)input->Get("hist_nHadChg_Zq");
	hist_nHadChg_Zq->SetLineColor(kRed+2); hist_nHadChg_Zq->SetMarkerColor(kRed+1); hist_nHadChg_Zq->SetMarkerStyle(21); hist_nHadChg_Zq->SetLineWidth(1); hist_nHadChg_Zq->SetMarkerSize(1);
	TH1F* hist_nHadChg_WW = (TH1F*)input->Get("hist_nHadChg_WW");
	hist_nHadChg_WW->SetLineColor(kGreen+2); hist_nHadChg_WW->SetMarkerColor(kGreen+1); hist_nHadChg_WW->SetMarkerStyle(21); hist_nHadChg_WW->SetLineWidth(1); hist_nHadChg_WW->SetMarkerSize(1);
	TH1F* hist_nHadChg_ZZ = (TH1F*)input->Get("hist_nHadChg_ZZ");
	hist_nHadChg_ZZ->SetLineColor(kBlue+2); hist_nHadChg_ZZ->SetMarkerColor(kBlue+1); hist_nHadChg_ZZ->SetMarkerStyle(21); hist_nHadChg_ZZ->SetLineWidth(1); hist_nHadChg_ZZ->SetMarkerSize(1);
	TH1F* hist_nHadChg_tt = (TH1F*)input->Get("hist_nHadChg_tt");
	hist_nHadChg_tt->SetLineColor(kYellow+2); hist_nHadChg_tt->SetMarkerColor(kYellow+1); hist_nHadChg_tt->SetMarkerStyle(21); hist_nHadChg_tt->SetLineWidth(1); hist_nHadChg_tt->SetMarkerSize(1);
	TH1F* hist_nHadChg_HZ = (TH1F*)input->Get("hist_nHadChg_HZ");
	hist_nHadChg_HZ->SetLineColor(kMagenta+2); hist_nHadChg_HZ->SetMarkerColor(kMagenta+1); hist_nHadChg_HZ->SetMarkerStyle(21); hist_nHadChg_HZ->SetLineWidth(1); hist_nHadChg_HZ->SetMarkerSize(1);
	TH1F* hist_nHadChg_HW = (TH1F*)input->Get("hist_nHadChg_HW");
	hist_nHadChg_HW->SetLineColor(kCyan+2); hist_nHadChg_HW->SetMarkerColor(kCyan+1); hist_nHadChg_HW->SetMarkerStyle(21); hist_nHadChg_HW->SetLineWidth(1); hist_nHadChg_HW->SetMarkerSize(1);

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
	TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 800, 2090);

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
	auto h1 = (TH1F*)hist_ThrPyth_al->Clone("h1");
	h1->SetFillColor(kWhite);
	h1->SetFillStyle(3005);
	h1->Draw("HIST SAME");

	hist_ThrPyth_Zq->SetFillColor(10);
	hist_ThrPyth_Zq->SetFillStyle(1001);
	hist_ThrPyth_Zq->Draw("HIST SAME");
	auto h2 = (TH1F*)hist_ThrPyth_Zq->Clone("h2");
	h2->SetFillColor(kRed+1);
	h2->SetFillStyle(3344);
	h2->Draw("HIST SAME");

	hist_ThrPyth_WW->SetFillColor(10);
	hist_ThrPyth_WW->SetFillStyle(1001);
	hist_ThrPyth_WW->Draw("HIST SAME");
	auto h3 = (TH1F*)hist_ThrPyth_WW->Clone("h3");
	h3->SetFillColor(kGreen+2);
	h3->SetFillStyle(3305);
	h3->Draw("HIST SAME");

	hist_ThrPyth_ZZ->SetFillColor(10);
	hist_ThrPyth_ZZ->SetFillStyle(1001);
	hist_ThrPyth_ZZ->Draw("HIST SAME");
	auto h4 = (TH1F*)hist_ThrPyth_ZZ->Clone("h4");
	h4->SetFillColor(kBlue+2);
	h4->SetFillStyle(3395);
	h4->Draw("HIST SAME");

	hist_ThrPyth_tt->SetFillColor(10);
	hist_ThrPyth_tt->SetFillStyle(1001);
	hist_ThrPyth_tt->Draw("HIST SAME");
	auto h5 = (TH1F*)hist_ThrPyth_tt->Clone("h5");
	h5->SetFillColor(kYellow+2);
	h5->SetFillStyle(3345);
	h5->Draw("HIST SAME");

	hist_ThrPyth_HZ->SetFillColor(10);
	hist_ThrPyth_HZ->SetFillStyle(1001);
	hist_ThrPyth_HZ->Draw("HIST SAME");
	auto h6 = (TH1F*)hist_ThrPyth_HZ->Clone("h6");
	h6->SetFillColor(kMagenta+1);
	h6->SetFillStyle(3354);
	h6->Draw("HIST SAME");

	hist_ThrPyth_HW->SetFillColor(10);
	hist_ThrPyth_HW->SetFillStyle(1001);
	hist_ThrPyth_HW->Draw("HIST SAME");
	auto h7 = (TH1F*)hist_ThrPyth_HW->Clone("h7");
	h7->SetFillColor(kCyan+2);
	h7->SetFillStyle(3409);
	h7->Draw("HIST SAME");

	hist_ThrPyth_al->Draw("HIST SAME");

	// Add legend
	TLegend* lg2 = new TLegend(0.80, 0.70, 0.93, 0.95);
	lg2->AddEntry(h1, "ee#rightarrowq#bar{q}", "F");
	lg2->AddEntry(h2, "ee#rightarrow#gamma*/Z", "F");
	lg2->AddEntry(h3, "ee#rightarrowWW", "F");
	lg2->AddEntry(h4, "ee#rightarrowZZ", "F");
	lg2->AddEntry(h5, "ee#rightarrowt#bar{t}", "F");
	lg2->AddEntry(h6, "ee#rightarrowZH", "F");
	lg2->AddEntry(h7, "ee#rightarrow#nu#bar{#nu}H", "F");
	lg2->SetTextSize(0.03);
	lg2->Draw("SAME");
	gPad->RedrawAxis();

	cv2->cd(2);
	hist_CprPyth_al->Draw("HIST");
	auto h11 = (TH1F*)hist_CprPyth_al->Clone("h11");
	h11->SetFillColor(kWhite);
	h11->SetFillStyle(3005);
	h11->Draw("HIST SAME");

	hist_CprPyth_Zq->SetFillColor(10);
	hist_CprPyth_Zq->SetFillStyle(1001);
	hist_CprPyth_Zq->Draw("HIST SAME");
	auto h21 = (TH1F*)hist_CprPyth_Zq->Clone("h21");
	h21->SetFillColor(kRed+1);
	h21->SetFillStyle(3344);
	h21->Draw("HIST SAME");

	hist_CprPyth_WW->SetFillColor(10);
	hist_CprPyth_WW->SetFillStyle(1001);
	hist_CprPyth_WW->Draw("HIST SAME");
	auto h31 = (TH1F*)hist_CprPyth_WW->Clone("h31");
	h31->SetFillColor(kGreen+2);
	h31->SetFillStyle(3305);
	h31->Draw("HIST SAME");

	hist_CprPyth_ZZ->SetFillColor(10);
	hist_CprPyth_ZZ->SetFillStyle(1001);
	hist_CprPyth_ZZ->Draw("HIST SAME");
	auto h41 = (TH1F*)hist_CprPyth_ZZ->Clone("h41");
	h41->SetFillColor(kBlue+2);
	h41->SetFillStyle(3395);
	h41->Draw("HIST SAME");

	hist_CprPyth_tt->SetFillColor(10);
	hist_CprPyth_tt->SetFillStyle(1001);
	hist_CprPyth_tt->Draw("HIST SAME");
	auto h51 = (TH1F*)hist_CprPyth_tt->Clone("h51");
	h51->SetFillColor(kYellow+2);
	h51->SetFillStyle(3345);
	h51->Draw("HIST SAME");

	hist_CprPyth_HZ->SetFillColor(10);
	hist_CprPyth_HZ->SetFillStyle(1001);
	hist_CprPyth_HZ->Draw("HIST SAME");
	auto h61 = (TH1F*)hist_CprPyth_HZ->Clone("h61");
	h61->SetFillColor(kMagenta+1);
	h61->SetFillStyle(3354);
	h61->Draw("HIST SAME");

	hist_CprPyth_HW->SetFillColor(10);
	hist_CprPyth_HW->SetFillStyle(1001);
	hist_CprPyth_HW->Draw("HIST SAME");
	auto h71 = (TH1F*)hist_CprPyth_HW->Clone("h71");
	h71->SetFillColor(kCyan+2);
	h71->SetFillStyle(3409);
	h71->Draw("HIST SAME");

	hist_CprPyth_al->Draw("HIST SAME");

	lg2->Draw("SAME");
	gPad->RedrawAxis();

	cv2->cd(3);
	hist_nHadChg_al->Draw("HIST");
	auto h12 = (TH1F*)hist_nHadChg_al->Clone("h12");
	h12->SetFillColor(kWhite);
	h12->SetFillStyle(3005);
	h12->Draw("HIST SAME");

	hist_nHadChg_Zq->SetFillColor(10);
	hist_nHadChg_Zq->SetFillStyle(1001);
	hist_nHadChg_Zq->Draw("HIST SAME");
	auto h22 = (TH1F*)hist_nHadChg_Zq->Clone("h22");
	h22->SetFillColor(kRed+1);
	h22->SetFillStyle(3344);
	h22->Draw("HIST SAME");

	hist_nHadChg_WW->SetFillColor(10);
	hist_nHadChg_WW->SetFillStyle(1001);
	hist_nHadChg_WW->Draw("HIST SAME");
	auto h32 = (TH1F*)hist_nHadChg_WW->Clone("h32");
	h32->SetFillColor(kGreen+2);
	h32->SetFillStyle(3305);
	h32->Draw("HIST SAME");

	hist_nHadChg_ZZ->SetFillColor(10);
	hist_nHadChg_ZZ->SetFillStyle(1001);
	hist_nHadChg_ZZ->Draw("HIST SAME");
	auto h42 = (TH1F*)hist_nHadChg_ZZ->Clone("h42");
	h42->SetFillColor(kBlue+2);
	h42->SetFillStyle(3395);
	h42->Draw("HIST SAME");

	hist_nHadChg_tt->SetFillColor(10);
	hist_nHadChg_tt->SetFillStyle(1001);
	hist_nHadChg_tt->Draw("HIST SAME");
	auto h52 = (TH1F*)hist_nHadChg_tt->Clone("h52");
	h52->SetFillColor(kYellow+2);
	h52->SetFillStyle(3345);
	h52->Draw("HIST SAME");

	hist_nHadChg_HZ->SetFillColor(10);
	hist_nHadChg_HZ->SetFillStyle(1001);
	hist_nHadChg_HZ->Draw("HIST SAME");
	auto h62 = (TH1F*)hist_nHadChg_HZ->Clone("h62");
	h62->SetFillColor(kMagenta+1);
	h62->SetFillStyle(3354);
	h62->Draw("HIST SAME");

	hist_nHadChg_HW->SetFillColor(10);
	hist_nHadChg_HW->SetFillStyle(1001);
	hist_nHadChg_HW->Draw("HIST SAME");
	auto h72 = (TH1F*)hist_nHadChg_HW->Clone("h72");
	h72->SetFillColor(kCyan+2);
	h72->SetFillStyle(3409);
	h72->Draw("HIST SAME");

	hist_nHadChg_al->Draw("HIST SAME");

	lg2->Draw("SAME");
	gPad->RedrawAxis();

	// Set limits
	hist_ThrPyth_al->GetYaxis()->SetRangeUser(1E0,1E7);
	hist_ThrPyth_al->GetXaxis()->SetRangeUser(0,0.45);
	hist_CprPyth_al->GetYaxis()->SetRangeUser(1E0,1E7);
	hist_CprPyth_al->GetXaxis()->SetRangeUser(0,1.0);	
	hist_nHadChg_al->GetYaxis()->SetRangeUser(1E0,1E7);
	hist_nHadChg_al->GetXaxis()->SetRangeUser(0,120);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv2->Modified();
	
	
}