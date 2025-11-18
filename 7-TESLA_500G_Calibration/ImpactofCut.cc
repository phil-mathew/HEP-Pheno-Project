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
void ImpactofCut()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile* input_365_woCut = new TFile("5-CutData/cut_FCC365.root", "READ");
	TFile* input_365_wiCut = new TFile("5-CutData/cut_FCC365_wiCut.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F* hist_ThrPyth_al_365_woCut = (TH1F*)input_365_woCut->Get("hist_ThrPyth");
	hist_ThrPyth_al_365_woCut->SetLineColor(kBlack); hist_ThrPyth_al_365_woCut->SetMarkerColor(kBlack); hist_ThrPyth_al_365_woCut->SetMarkerStyle(3); hist_ThrPyth_al_365_woCut->SetLineWidth(2); hist_ThrPyth_al_365_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_365_woCut = (TH1F*)input_365_woCut->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_365_woCut->SetLineColor(kRed+2); hist_ThrPyth_Zq_365_woCut->SetMarkerColor(kRed+2); hist_ThrPyth_Zq_365_woCut->SetMarkerStyle(3); hist_ThrPyth_Zq_365_woCut->SetLineWidth(2); hist_ThrPyth_Zq_365_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_365_woCut = (TH1F*)input_365_woCut->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_365_woCut->SetLineColor(kGreen+2); hist_ThrPyth_WW_365_woCut->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_365_woCut->SetMarkerStyle(3); hist_ThrPyth_WW_365_woCut->SetLineWidth(2); hist_ThrPyth_WW_365_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_365_woCut = (TH1F*)input_365_woCut->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_365_woCut->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_365_woCut->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_365_woCut->SetMarkerStyle(3); hist_ThrPyth_ZZ_365_woCut->SetLineWidth(2); hist_ThrPyth_ZZ_365_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_365_woCut = (TH1F*)input_365_woCut->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_365_woCut->SetLineColor(kYellow+2); hist_ThrPyth_tt_365_woCut->SetMarkerColor(kYellow+2); hist_ThrPyth_tt_365_woCut->SetMarkerStyle(3); hist_ThrPyth_tt_365_woCut->SetLineWidth(2); hist_ThrPyth_tt_365_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_365_woCut = (TH1F*)input_365_woCut->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_365_woCut->SetLineColor(kMagenta+2); hist_ThrPyth_HZ_365_woCut->SetMarkerColor(kMagenta+2); hist_ThrPyth_HZ_365_woCut->SetMarkerStyle(53); hist_ThrPyth_HZ_365_woCut->SetLineWidth(2); hist_ThrPyth_HZ_365_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW_365_woCut = (TH1F*)input_365_woCut->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW_365_woCut->SetLineColor(kCyan+2); hist_ThrPyth_HW_365_woCut->SetMarkerColor(kCyan+2); hist_ThrPyth_HW_365_woCut->SetMarkerStyle(53); hist_ThrPyth_HW_365_woCut->SetLineWidth(2); hist_ThrPyth_HW_365_woCut->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_365_woCut = (TH1F*)input_365_woCut->Get("hist_CprPyth");
	hist_CprPyth_al_365_woCut->SetLineColor(kBlack); hist_CprPyth_al_365_woCut->SetMarkerColor(kBlack); hist_CprPyth_al_365_woCut->SetMarkerStyle(3); hist_CprPyth_al_365_woCut->SetLineWidth(2); hist_CprPyth_al_365_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_365_woCut = (TH1F*)input_365_woCut->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_365_woCut->SetLineColor(kRed+2); hist_CprPyth_Zq_365_woCut->SetMarkerColor(kRed+2); hist_CprPyth_Zq_365_woCut->SetMarkerStyle(3); hist_CprPyth_Zq_365_woCut->SetLineWidth(2); hist_CprPyth_Zq_365_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_365_woCut = (TH1F*)input_365_woCut->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_365_woCut->SetLineColor(kGreen+2); hist_CprPyth_WW_365_woCut->SetMarkerColor(kGreen+2); hist_CprPyth_WW_365_woCut->SetMarkerStyle(3); hist_CprPyth_WW_365_woCut->SetLineWidth(2); hist_CprPyth_WW_365_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_365_woCut = (TH1F*)input_365_woCut->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_365_woCut->SetLineColor(kBlue+2); hist_CprPyth_ZZ_365_woCut->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_365_woCut->SetMarkerStyle(3); hist_CprPyth_ZZ_365_woCut->SetLineWidth(2); hist_CprPyth_ZZ_365_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_365_woCut = (TH1F*)input_365_woCut->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_365_woCut->SetLineColor(kYellow+2); hist_CprPyth_tt_365_woCut->SetMarkerColor(kYellow+2); hist_CprPyth_tt_365_woCut->SetMarkerStyle(3); hist_CprPyth_tt_365_woCut->SetLineWidth(2); hist_CprPyth_tt_365_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_365_woCut = (TH1F*)input_365_woCut->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_365_woCut->SetLineColor(kMagenta+2); hist_CprPyth_HZ_365_woCut->SetMarkerColor(kMagenta+2); hist_CprPyth_HZ_365_woCut->SetMarkerStyle(53); hist_CprPyth_HZ_365_woCut->SetLineWidth(2); hist_CprPyth_HZ_365_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW_365_woCut = (TH1F*)input_365_woCut->Get("hist_CprPyth_HW");
	hist_CprPyth_HW_365_woCut->SetLineColor(kCyan+2); hist_CprPyth_HW_365_woCut->SetMarkerColor(kCyan+2); hist_CprPyth_HW_365_woCut->SetMarkerStyle(53); hist_CprPyth_HW_365_woCut->SetLineWidth(2); hist_CprPyth_HW_365_woCut->SetMarkerSize(1);

	TH1F* hist_TaxPyth_al_365_woCut = (TH1F*)input_365_woCut->Get("hist_TaxPyth");
	hist_TaxPyth_al_365_woCut->SetLineColor(kBlack); hist_TaxPyth_al_365_woCut->SetMarkerColor(kBlack); hist_TaxPyth_al_365_woCut->SetMarkerStyle(3); hist_TaxPyth_al_365_woCut->SetLineWidth(2); hist_TaxPyth_al_365_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_Zq_365_woCut = (TH1F*)input_365_woCut->Get("hist_TaxPyth_Zq");
	hist_TaxPyth_Zq_365_woCut->SetLineColor(kRed+2); hist_TaxPyth_Zq_365_woCut->SetMarkerColor(kRed+2); hist_TaxPyth_Zq_365_woCut->SetMarkerStyle(3); hist_TaxPyth_Zq_365_woCut->SetLineWidth(2); hist_TaxPyth_Zq_365_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_WW_365_woCut = (TH1F*)input_365_woCut->Get("hist_TaxPyth_WW");
	hist_TaxPyth_WW_365_woCut->SetLineColor(kGreen+2); hist_TaxPyth_WW_365_woCut->SetMarkerColor(kGreen+2); hist_TaxPyth_WW_365_woCut->SetMarkerStyle(3); hist_TaxPyth_WW_365_woCut->SetLineWidth(2); hist_TaxPyth_WW_365_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_ZZ_365_woCut = (TH1F*)input_365_woCut->Get("hist_TaxPyth_ZZ");
	hist_TaxPyth_ZZ_365_woCut->SetLineColor(kBlue+2); hist_TaxPyth_ZZ_365_woCut->SetMarkerColor(kBlue+2); hist_TaxPyth_ZZ_365_woCut->SetMarkerStyle(3); hist_TaxPyth_ZZ_365_woCut->SetLineWidth(2); hist_TaxPyth_ZZ_365_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_tt_365_woCut = (TH1F*)input_365_woCut->Get("hist_TaxPyth_tt");
	hist_TaxPyth_tt_365_woCut->SetLineColor(kYellow+2); hist_TaxPyth_tt_365_woCut->SetMarkerColor(kYellow+2); hist_TaxPyth_tt_365_woCut->SetMarkerStyle(3); hist_TaxPyth_tt_365_woCut->SetLineWidth(2); hist_TaxPyth_tt_365_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HZ_365_woCut = (TH1F*)input_365_woCut->Get("hist_TaxPyth_HZ");
	hist_TaxPyth_HZ_365_woCut->SetLineColor(kMagenta+2); hist_TaxPyth_HZ_365_woCut->SetMarkerColor(kMagenta+2); hist_TaxPyth_HZ_365_woCut->SetMarkerStyle(53); hist_TaxPyth_HZ_365_woCut->SetLineWidth(2); hist_TaxPyth_HZ_365_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HW_365_woCut = (TH1F*)input_365_woCut->Get("hist_TaxPyth_HW");
	hist_TaxPyth_HW_365_woCut->SetLineColor(kCyan+2); hist_TaxPyth_HW_365_woCut->SetMarkerColor(kCyan+2); hist_TaxPyth_HW_365_woCut->SetMarkerStyle(53); hist_TaxPyth_HW_365_woCut->SetLineWidth(2); hist_TaxPyth_HW_365_woCut->SetMarkerSize(1);

	TH1F* hist_SaxPyth_al_365_woCut = (TH1F*)input_365_woCut->Get("hist_SaxPyth");
	hist_SaxPyth_al_365_woCut->SetLineColor(kBlack); hist_SaxPyth_al_365_woCut->SetMarkerColor(kBlack); hist_SaxPyth_al_365_woCut->SetMarkerStyle(3); hist_SaxPyth_al_365_woCut->SetLineWidth(2); hist_SaxPyth_al_365_woCut->SetMarkerSize(1);
	TH1F* hist_SaxPyth_Zq_365_woCut = (TH1F*)input_365_woCut->Get("hist_SaxPyth_Zq");
	hist_SaxPyth_Zq_365_woCut->SetLineColor(kRed+2); hist_SaxPyth_Zq_365_woCut->SetMarkerColor(kRed+2); hist_SaxPyth_Zq_365_woCut->SetMarkerStyle(3); hist_SaxPyth_Zq_365_woCut->SetLineWidth(2); hist_SaxPyth_Zq_365_woCut->SetMarkerSize(1);
	TH1F* hist_SaxPyth_WW_365_woCut = (TH1F*)input_365_woCut->Get("hist_SaxPyth_WW");
	hist_SaxPyth_WW_365_woCut->SetLineColor(kGreen+2); hist_SaxPyth_WW_365_woCut->SetMarkerColor(kGreen+2); hist_SaxPyth_WW_365_woCut->SetMarkerStyle(3); hist_SaxPyth_WW_365_woCut->SetLineWidth(2); hist_SaxPyth_WW_365_woCut->SetMarkerSize(1);
	TH1F* hist_SaxPyth_ZZ_365_woCut = (TH1F*)input_365_woCut->Get("hist_SaxPyth_ZZ");
	hist_SaxPyth_ZZ_365_woCut->SetLineColor(kBlue+2); hist_SaxPyth_ZZ_365_woCut->SetMarkerColor(kBlue+2); hist_SaxPyth_ZZ_365_woCut->SetMarkerStyle(3); hist_SaxPyth_ZZ_365_woCut->SetLineWidth(2); hist_SaxPyth_ZZ_365_woCut->SetMarkerSize(1);
	TH1F* hist_SaxPyth_tt_365_woCut = (TH1F*)input_365_woCut->Get("hist_SaxPyth_tt");
	hist_SaxPyth_tt_365_woCut->SetLineColor(kYellow+2); hist_SaxPyth_tt_365_woCut->SetMarkerColor(kYellow+2); hist_SaxPyth_tt_365_woCut->SetMarkerStyle(3); hist_SaxPyth_tt_365_woCut->SetLineWidth(2); hist_SaxPyth_tt_365_woCut->SetMarkerSize(1);
	TH1F* hist_SaxPyth_HZ_365_woCut = (TH1F*)input_365_woCut->Get("hist_SaxPyth_HZ");
	hist_SaxPyth_HZ_365_woCut->SetLineColor(kMagenta+2); hist_SaxPyth_HZ_365_woCut->SetMarkerColor(kMagenta+2); hist_SaxPyth_HZ_365_woCut->SetMarkerStyle(53); hist_SaxPyth_HZ_365_woCut->SetLineWidth(2); hist_SaxPyth_HZ_365_woCut->SetMarkerSize(1);
	TH1F* hist_SaxPyth_HW_365_woCut = (TH1F*)input_365_woCut->Get("hist_SaxPyth_HW");
	hist_SaxPyth_HW_365_woCut->SetLineColor(kCyan+2); hist_SaxPyth_HW_365_woCut->SetMarkerColor(kCyan+2); hist_SaxPyth_HW_365_woCut->SetMarkerStyle(53); hist_SaxPyth_HW_365_woCut->SetLineWidth(2); hist_SaxPyth_HW_365_woCut->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F* hist_ThrPyth_al_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_ThrPyth");
	hist_ThrPyth_al_365_wiCut->SetLineColor(kBlack); hist_ThrPyth_al_365_wiCut->SetMarkerColor(kBlack); hist_ThrPyth_al_365_wiCut->SetMarkerStyle(3); hist_ThrPyth_al_365_wiCut->SetLineWidth(2); hist_ThrPyth_al_365_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_365_wiCut->SetLineColor(kRed+2); hist_ThrPyth_Zq_365_wiCut->SetMarkerColor(kRed+2); hist_ThrPyth_Zq_365_wiCut->SetMarkerStyle(3); hist_ThrPyth_Zq_365_wiCut->SetLineWidth(2); hist_ThrPyth_Zq_365_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_365_wiCut->SetLineColor(kGreen+2); hist_ThrPyth_WW_365_wiCut->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_365_wiCut->SetMarkerStyle(3); hist_ThrPyth_WW_365_wiCut->SetLineWidth(2); hist_ThrPyth_WW_365_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_365_wiCut->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_365_wiCut->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_365_wiCut->SetMarkerStyle(3); hist_ThrPyth_ZZ_365_wiCut->SetLineWidth(2); hist_ThrPyth_ZZ_365_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_365_wiCut->SetLineColor(kYellow+2); hist_ThrPyth_tt_365_wiCut->SetMarkerColor(kYellow+2); hist_ThrPyth_tt_365_wiCut->SetMarkerStyle(3); hist_ThrPyth_tt_365_wiCut->SetLineWidth(2); hist_ThrPyth_tt_365_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_365_wiCut->SetLineColor(kMagenta+2); hist_ThrPyth_HZ_365_wiCut->SetMarkerColor(kMagenta+2); hist_ThrPyth_HZ_365_wiCut->SetMarkerStyle(53); hist_ThrPyth_HZ_365_wiCut->SetLineWidth(2); hist_ThrPyth_HZ_365_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW_365_wiCut->SetLineColor(kCyan+2); hist_ThrPyth_HW_365_wiCut->SetMarkerColor(kCyan+2); hist_ThrPyth_HW_365_wiCut->SetMarkerStyle(53); hist_ThrPyth_HW_365_wiCut->SetLineWidth(2); hist_ThrPyth_HW_365_wiCut->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_CprPyth");
	hist_CprPyth_al_365_wiCut->SetLineColor(kBlack); hist_CprPyth_al_365_wiCut->SetMarkerColor(kBlack); hist_CprPyth_al_365_wiCut->SetMarkerStyle(3); hist_CprPyth_al_365_wiCut->SetLineWidth(2); hist_CprPyth_al_365_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_365_wiCut->SetLineColor(kRed+2); hist_CprPyth_Zq_365_wiCut->SetMarkerColor(kRed+2); hist_CprPyth_Zq_365_wiCut->SetMarkerStyle(3); hist_CprPyth_Zq_365_wiCut->SetLineWidth(2); hist_CprPyth_Zq_365_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_365_wiCut->SetLineColor(kGreen+2); hist_CprPyth_WW_365_wiCut->SetMarkerColor(kGreen+2); hist_CprPyth_WW_365_wiCut->SetMarkerStyle(3); hist_CprPyth_WW_365_wiCut->SetLineWidth(2); hist_CprPyth_WW_365_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_365_wiCut->SetLineColor(kBlue+2); hist_CprPyth_ZZ_365_wiCut->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_365_wiCut->SetMarkerStyle(3); hist_CprPyth_ZZ_365_wiCut->SetLineWidth(2); hist_CprPyth_ZZ_365_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_365_wiCut->SetLineColor(kYellow+2); hist_CprPyth_tt_365_wiCut->SetMarkerColor(kYellow+2); hist_CprPyth_tt_365_wiCut->SetMarkerStyle(3); hist_CprPyth_tt_365_wiCut->SetLineWidth(2); hist_CprPyth_tt_365_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_365_wiCut->SetLineColor(kMagenta+2); hist_CprPyth_HZ_365_wiCut->SetMarkerColor(kMagenta+2); hist_CprPyth_HZ_365_wiCut->SetMarkerStyle(53); hist_CprPyth_HZ_365_wiCut->SetLineWidth(2); hist_CprPyth_HZ_365_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW_365_wiCut = (TH1F*)input_365_wiCut->Get("hist_CprPyth_HW");
	hist_CprPyth_HW_365_wiCut->SetLineColor(kCyan+2); hist_CprPyth_HW_365_wiCut->SetMarkerColor(kCyan+2); hist_CprPyth_HW_365_wiCut->SetMarkerStyle(53); hist_CprPyth_HW_365_wiCut->SetLineWidth(2); hist_CprPyth_HW_365_wiCut->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_Zq_365_woCut->SetStats(kFALSE);
	hist_CprPyth_Zq_365_woCut->SetStats(kFALSE);
	hist_TaxPyth_al_365_woCut->SetStats(kFALSE);
	hist_SaxPyth_al_365_woCut->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit text sizes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_Zq_365_woCut->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_Zq_365_woCut->GetYaxis()->SetLabelSize(0.04); hist_ThrPyth_Zq_365_woCut->GetYaxis()->SetTitleSize(0.04); hist_ThrPyth_Zq_365_woCut->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_Zq_365_woCut->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_Zq_365_woCut->GetYaxis()->SetLabelSize(0.04); hist_CprPyth_Zq_365_woCut->GetYaxis()->SetTitleSize(0.04); hist_CprPyth_Zq_365_woCut->GetXaxis()->SetTitleSize(0.04); 
	hist_TaxPyth_Zq_365_woCut->GetXaxis()->SetLabelSize(0.04); hist_TaxPyth_Zq_365_woCut->GetYaxis()->SetLabelSize(0.04); hist_TaxPyth_Zq_365_woCut->GetYaxis()->SetTitleSize(0.04); hist_TaxPyth_Zq_365_woCut->GetXaxis()->SetTitleSize(0.04);
	hist_SaxPyth_Zq_365_woCut->GetXaxis()->SetLabelSize(0.04); hist_SaxPyth_Zq_365_woCut->GetYaxis()->SetLabelSize(0.04); hist_SaxPyth_Zq_365_woCut->GetYaxis()->SetTitleSize(0.04); hist_SaxPyth_Zq_365_woCut->GetXaxis()->SetTitleSize(0.04); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_Zq_365_woCut->SetTitle("");
	hist_CprPyth_Zq_365_woCut->SetTitle("");
	hist_TaxPyth_al_365_woCut->SetTitle("");
	hist_SaxPyth_al_365_woCut->SetTitle("");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw Plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 1600, 800);

	// Add legend
	TLegend* lg2 = new TLegend(0.77, 0.83, 0.92, 0.95);
	lg2->AddEntry(hist_ThrPyth_al_365_woCut, "ee#rightarrowq#bar{q}", "L");
	lg2->AddEntry(hist_ThrPyth_ZZ_365_woCut, "ee#rightarrowWW", "L");
	lg2->AddEntry(hist_ThrPyth_WW_365_woCut, "ee#rightarrowZZ", "L");
	lg2->SetTextSize(0.03);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv2->SetMargin(0, 0, 0, 0); 
	cv2->Divide(2,1);
	for (int i = 1; i <= 2; i++) {
		cv2->cd(i);
		gPad->SetTopMargin(0.017);
		gPad->SetBottomMargin(0.1);
		gPad->SetLeftMargin(0.15);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		gPad->SetLogy();
	}

	hist_ThrPyth_Zq_365_wiCut->SetLineStyle(7);
	hist_ThrPyth_WW_365_wiCut->SetLineStyle(7);
	hist_ThrPyth_ZZ_365_wiCut->SetLineStyle(7);
	hist_CprPyth_Zq_365_wiCut->SetLineStyle(7);
	hist_CprPyth_WW_365_wiCut->SetLineStyle(7);
	hist_CprPyth_ZZ_365_wiCut->SetLineStyle(7);

	hist_ThrPyth_Zq_365_woCut->GetYaxis()->SetTitle("N_{events}");
	hist_CprPyth_Zq_365_woCut->GetYaxis()->SetTitle("N_{events}");

	hist_ThrPyth_Zq_365_woCut->GetXaxis()->CenterTitle(); hist_ThrPyth_Zq_365_woCut->GetYaxis()->CenterTitle();
	hist_CprPyth_Zq_365_woCut->GetXaxis()->CenterTitle(); hist_CprPyth_Zq_365_woCut->GetYaxis()->CenterTitle();

	double scale_Thr = hist_ThrPyth_Zq_365_wiCut->GetBinContent(hist_ThrPyth_Zq_365_wiCut->GetMaximumBin())/hist_ThrPyth_Zq_365_woCut->GetBinContent(hist_ThrPyth_Zq_365_woCut->GetMaximumBin());
	hist_ThrPyth_WW_365_wiCut->Scale(1/scale_Thr); hist_ThrPyth_ZZ_365_wiCut->Scale(1/scale_Thr); hist_ThrPyth_Zq_365_wiCut->Scale(1/scale_Thr);

	double scale_Cpr = hist_CprPyth_Zq_365_wiCut->GetBinContent(hist_CprPyth_Zq_365_wiCut->GetMaximumBin())/hist_CprPyth_Zq_365_woCut->GetBinContent(hist_CprPyth_Zq_365_woCut->GetMaximumBin());
	hist_CprPyth_WW_365_wiCut->Scale(1/scale_Cpr); hist_CprPyth_ZZ_365_wiCut->Scale(1/scale_Cpr); hist_CprPyth_Zq_365_wiCut->Scale(1/scale_Cpr);

	cout << 1/scale_Thr << " " << 1/scale_Cpr << endl;
	
	// Draw
	cv2->cd(1);
	hist_ThrPyth_Zq_365_woCut->Draw("HIST");
	hist_ThrPyth_WW_365_woCut->Draw("HIST SAME");
	hist_ThrPyth_ZZ_365_woCut->Draw("HIST SAME");
	// hist_ThrPyth_Zq_365_wiCut->Draw("HIST C SAME");
	hist_ThrPyth_WW_365_wiCut->Draw("HIST SAME");
	hist_ThrPyth_ZZ_365_wiCut->Draw("HIST SAME");
	lg2->Draw("SAME");

	cv2->cd(2);
	hist_CprPyth_Zq_365_woCut->Draw("HIST");
	hist_CprPyth_WW_365_woCut->Draw("HIST SAME");
	hist_CprPyth_ZZ_365_woCut->Draw("HIST SAME");
	// hist_CprPyth_Zq_365_wiCut->Draw("HIST SAME");
	hist_CprPyth_WW_365_wiCut->Draw("HIST SAME");
	hist_CprPyth_ZZ_365_wiCut->Draw("HIST SAME");
	lg2->Draw("SAME");

	// Set limits
	hist_ThrPyth_Zq_365_woCut->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_ThrPyth_Zq_365_woCut->GetXaxis()->SetRangeUser(0,0.45);
	hist_CprPyth_Zq_365_woCut->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_CprPyth_Zq_365_woCut->GetXaxis()->SetRangeUser(0,1.0);	

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv2->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv3 = new TCanvas("cv3", "FCC-ee ISR Studies", 1400, 800);

	// Add legend
	TLegend* lg3 = new TLegend(0.75, 0.70, 0.92, 0.95);
	lg3->AddEntry(hist_TaxPyth_al_365_woCut, "ee#rightarrowq#bar{q}", "L");
	lg3->AddEntry(hist_TaxPyth_Zq_365_woCut, "ee#rightarrow#gamma/Z", "L");
	lg3->AddEntry(hist_TaxPyth_ZZ_365_woCut, "ee#rightarrowZZ", "L");
	lg3->AddEntry(hist_TaxPyth_WW_365_woCut, "ee#rightarrowWW", "L");
	lg3->AddEntry(hist_TaxPyth_tt_365_woCut, "ee#rightarrowt#bar{t}", "L");
	lg3->AddEntry(hist_TaxPyth_HZ_365_woCut, "ee#rightarrowZH", "L");
	lg3->AddEntry(hist_TaxPyth_HW_365_woCut, "ee#rightarrow#nu#bar{#nu}H", "L");
	lg3->SetTextSize(0.03);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv3->SetMargin(0, 0, 0, 0); 
	cv3->Divide(2,1);
	for (int i = 1; i <= 3; i++) {
		cv3->cd(i);
		gPad->SetTopMargin(0.017);
		gPad->SetBottomMargin(0.1);
		gPad->SetLeftMargin(0.10);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		gPad->SetLogy();
	}

	// Draw
	cv3->cd(1);
	hist_TaxPyth_al_365_woCut->Draw("HIST");
	hist_TaxPyth_Zq_365_woCut->Draw("HIST SAME");
	hist_TaxPyth_WW_365_woCut->Draw("HIST SAME");
	hist_TaxPyth_ZZ_365_woCut->Draw("HIST SAME");
	hist_TaxPyth_tt_365_woCut->Draw("HIST SAME");
	hist_TaxPyth_HZ_365_woCut->Draw("HIST SAME");
	hist_TaxPyth_HW_365_woCut->Draw("HIST SAME");
	lg3->Draw("SAME");

	cv3->cd(2);
	hist_SaxPyth_al_365_woCut->Draw("HIST");
	hist_SaxPyth_Zq_365_woCut->Draw("HIST SAME");
	hist_SaxPyth_WW_365_woCut->Draw("HIST SAME");
	hist_SaxPyth_ZZ_365_woCut->Draw("HIST SAME");
	hist_SaxPyth_tt_365_woCut->Draw("HIST SAME");
	hist_SaxPyth_HZ_365_woCut->Draw("HIST SAME");
	hist_SaxPyth_HW_365_woCut->Draw("HIST SAME");
	lg3->Draw("SAME");

	// Set limits
	hist_TaxPyth_al_365_woCut->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_TaxPyth_al_365_woCut->GetXaxis()->SetRangeUser(-1,1);
	hist_SaxPyth_al_365_woCut->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_SaxPyth_al_365_woCut->GetXaxis()->SetRangeUser(-1,1);	
	
	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv3->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}