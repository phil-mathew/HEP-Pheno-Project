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

	TFile *input_912_woCut = new TFile("5-CutData/cut_FCC912.root", "READ");
	TFile *input_160_woCut = new TFile("5-CutData/cut_FCC160.root", "READ");
	TFile *input_240_woCut = new TFile("5-CutData/cut_FCC240.root", "READ");
	TFile* input_365_woCut = new TFile("5-CutData/cut_FCC365.root", "READ");
	TFile* input_240_wiCut = new TFile("5-CutData/cut_FCC240_wiCut_Tax.root", "READ");
	TFile* input_365_wiCut = new TFile("5-CutData/cut_FCC365_wiCut_Tax.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F* hist_ThrPyth_al_240_woCut = (TH1F*)input_240_woCut->Get("hist_ThrPyth");
	hist_ThrPyth_al_240_woCut->SetLineColor(kBlack); hist_ThrPyth_al_240_woCut->SetMarkerColor(kBlack); hist_ThrPyth_al_240_woCut->SetMarkerStyle(3); hist_ThrPyth_al_240_woCut->SetLineWidth(2); hist_ThrPyth_al_240_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_240_woCut = (TH1F*)input_240_woCut->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_240_woCut->SetLineColor(kRed+2); hist_ThrPyth_Zq_240_woCut->SetMarkerColor(kRed+2); hist_ThrPyth_Zq_240_woCut->SetMarkerStyle(3); hist_ThrPyth_Zq_240_woCut->SetLineWidth(2); hist_ThrPyth_Zq_240_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_240_woCut = (TH1F*)input_240_woCut->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_240_woCut->SetLineColor(kGreen+2); hist_ThrPyth_WW_240_woCut->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_240_woCut->SetMarkerStyle(3); hist_ThrPyth_WW_240_woCut->SetLineWidth(2); hist_ThrPyth_WW_240_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_240_woCut = (TH1F*)input_240_woCut->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_240_woCut->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_240_woCut->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_240_woCut->SetMarkerStyle(3); hist_ThrPyth_ZZ_240_woCut->SetLineWidth(2); hist_ThrPyth_ZZ_240_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_240_woCut = (TH1F*)input_240_woCut->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_240_woCut->SetLineColor(kYellow+2); hist_ThrPyth_tt_240_woCut->SetMarkerColor(kYellow+2); hist_ThrPyth_tt_240_woCut->SetMarkerStyle(3); hist_ThrPyth_tt_240_woCut->SetLineWidth(2); hist_ThrPyth_tt_240_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_240_woCut = (TH1F*)input_240_woCut->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_240_woCut->SetLineColor(kMagenta+2); hist_ThrPyth_HZ_240_woCut->SetMarkerColor(kMagenta+2); hist_ThrPyth_HZ_240_woCut->SetMarkerStyle(53); hist_ThrPyth_HZ_240_woCut->SetLineWidth(2); hist_ThrPyth_HZ_240_woCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW_240_woCut = (TH1F*)input_240_woCut->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW_240_woCut->SetLineColor(kCyan+2); hist_ThrPyth_HW_240_woCut->SetMarkerColor(kCyan+2); hist_ThrPyth_HW_240_woCut->SetMarkerStyle(53); hist_ThrPyth_HW_240_woCut->SetLineWidth(2); hist_ThrPyth_HW_240_woCut->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_240_woCut = (TH1F*)input_240_woCut->Get("hist_CprPyth");
	hist_CprPyth_al_240_woCut->SetLineColor(kBlack); hist_CprPyth_al_240_woCut->SetMarkerColor(kBlack); hist_CprPyth_al_240_woCut->SetMarkerStyle(3); hist_CprPyth_al_240_woCut->SetLineWidth(2); hist_CprPyth_al_240_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_240_woCut = (TH1F*)input_240_woCut->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_240_woCut->SetLineColor(kRed+2); hist_CprPyth_Zq_240_woCut->SetMarkerColor(kRed+2); hist_CprPyth_Zq_240_woCut->SetMarkerStyle(3); hist_CprPyth_Zq_240_woCut->SetLineWidth(2); hist_CprPyth_Zq_240_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_240_woCut = (TH1F*)input_240_woCut->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_240_woCut->SetLineColor(kGreen+2); hist_CprPyth_WW_240_woCut->SetMarkerColor(kGreen+2); hist_CprPyth_WW_240_woCut->SetMarkerStyle(3); hist_CprPyth_WW_240_woCut->SetLineWidth(2); hist_CprPyth_WW_240_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_240_woCut = (TH1F*)input_240_woCut->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_240_woCut->SetLineColor(kBlue+2); hist_CprPyth_ZZ_240_woCut->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_240_woCut->SetMarkerStyle(3); hist_CprPyth_ZZ_240_woCut->SetLineWidth(2); hist_CprPyth_ZZ_240_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_240_woCut = (TH1F*)input_240_woCut->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_240_woCut->SetLineColor(kYellow+2); hist_CprPyth_tt_240_woCut->SetMarkerColor(kYellow+2); hist_CprPyth_tt_240_woCut->SetMarkerStyle(3); hist_CprPyth_tt_240_woCut->SetLineWidth(2); hist_CprPyth_tt_240_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_240_woCut = (TH1F*)input_240_woCut->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_240_woCut->SetLineColor(kMagenta+2); hist_CprPyth_HZ_240_woCut->SetMarkerColor(kMagenta+2); hist_CprPyth_HZ_240_woCut->SetMarkerStyle(53); hist_CprPyth_HZ_240_woCut->SetLineWidth(2); hist_CprPyth_HZ_240_woCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW_240_woCut = (TH1F*)input_240_woCut->Get("hist_CprPyth_HW");
	hist_CprPyth_HW_240_woCut->SetLineColor(kCyan+2); hist_CprPyth_HW_240_woCut->SetMarkerColor(kCyan+2); hist_CprPyth_HW_240_woCut->SetMarkerStyle(53); hist_CprPyth_HW_240_woCut->SetLineWidth(2); hist_CprPyth_HW_240_woCut->SetMarkerSize(1);

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F* hist_TaxPyth_al_912_woCut = (TH1F*)input_912_woCut->Get("hist_TaxPyth");
	hist_TaxPyth_al_912_woCut->SetLineColor(kBlack); hist_TaxPyth_al_912_woCut->SetMarkerColor(kBlack); hist_TaxPyth_al_912_woCut->SetMarkerStyle(3); hist_TaxPyth_al_912_woCut->SetLineWidth(2); hist_TaxPyth_al_912_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_Zq_912_woCut = (TH1F*)input_912_woCut->Get("hist_TaxPyth_Zq");
	hist_TaxPyth_Zq_912_woCut->SetLineColor(kRed+2); hist_TaxPyth_Zq_912_woCut->SetMarkerColor(kRed+2); hist_TaxPyth_Zq_912_woCut->SetMarkerStyle(3); hist_TaxPyth_Zq_912_woCut->SetLineWidth(2); hist_TaxPyth_Zq_912_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_WW_912_woCut = (TH1F*)input_912_woCut->Get("hist_TaxPyth_WW");
	hist_TaxPyth_WW_912_woCut->SetLineColor(kGreen+2); hist_TaxPyth_WW_912_woCut->SetMarkerColor(kGreen+2); hist_TaxPyth_WW_912_woCut->SetMarkerStyle(3); hist_TaxPyth_WW_912_woCut->SetLineWidth(2); hist_TaxPyth_WW_912_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_ZZ_912_woCut = (TH1F*)input_912_woCut->Get("hist_TaxPyth_ZZ");
	hist_TaxPyth_ZZ_912_woCut->SetLineColor(kBlue+2); hist_TaxPyth_ZZ_912_woCut->SetMarkerColor(kBlue+2); hist_TaxPyth_ZZ_912_woCut->SetMarkerStyle(3); hist_TaxPyth_ZZ_912_woCut->SetLineWidth(2); hist_TaxPyth_ZZ_912_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_tt_912_woCut = (TH1F*)input_912_woCut->Get("hist_TaxPyth_tt");
	hist_TaxPyth_tt_912_woCut->SetLineColor(kYellow+2); hist_TaxPyth_tt_912_woCut->SetMarkerColor(kYellow+2); hist_TaxPyth_tt_912_woCut->SetMarkerStyle(3); hist_TaxPyth_tt_912_woCut->SetLineWidth(2); hist_TaxPyth_tt_912_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HZ_912_woCut = (TH1F*)input_912_woCut->Get("hist_TaxPyth_HZ");
	hist_TaxPyth_HZ_912_woCut->SetLineColor(kMagenta+2); hist_TaxPyth_HZ_912_woCut->SetMarkerColor(kMagenta+2); hist_TaxPyth_HZ_912_woCut->SetMarkerStyle(53); hist_TaxPyth_HZ_912_woCut->SetLineWidth(2); hist_TaxPyth_HZ_912_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HW_912_woCut = (TH1F*)input_912_woCut->Get("hist_TaxPyth_HW");
	hist_TaxPyth_HW_912_woCut->SetLineColor(kCyan+2); hist_TaxPyth_HW_912_woCut->SetMarkerColor(kCyan+2); hist_TaxPyth_HW_912_woCut->SetMarkerStyle(53); hist_TaxPyth_HW_912_woCut->SetLineWidth(2); hist_TaxPyth_HW_912_woCut->SetMarkerSize(1);

	TH1F* hist_TaxPyth_al_160_woCut = (TH1F*)input_160_woCut->Get("hist_TaxPyth");
	hist_TaxPyth_al_160_woCut->SetLineColor(kBlack); hist_TaxPyth_al_160_woCut->SetMarkerColor(kBlack); hist_TaxPyth_al_160_woCut->SetMarkerStyle(3); hist_TaxPyth_al_160_woCut->SetLineWidth(2); hist_TaxPyth_al_160_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_Zq_160_woCut = (TH1F*)input_160_woCut->Get("hist_TaxPyth_Zq");
	hist_TaxPyth_Zq_160_woCut->SetLineColor(kRed+2); hist_TaxPyth_Zq_160_woCut->SetMarkerColor(kRed+2); hist_TaxPyth_Zq_160_woCut->SetMarkerStyle(3); hist_TaxPyth_Zq_160_woCut->SetLineWidth(2); hist_TaxPyth_Zq_160_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_WW_160_woCut = (TH1F*)input_160_woCut->Get("hist_TaxPyth_WW");
	hist_TaxPyth_WW_160_woCut->SetLineColor(kGreen+2); hist_TaxPyth_WW_160_woCut->SetMarkerColor(kGreen+2); hist_TaxPyth_WW_160_woCut->SetMarkerStyle(3); hist_TaxPyth_WW_160_woCut->SetLineWidth(2); hist_TaxPyth_WW_160_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_ZZ_160_woCut = (TH1F*)input_160_woCut->Get("hist_TaxPyth_ZZ");
	hist_TaxPyth_ZZ_160_woCut->SetLineColor(kBlue+2); hist_TaxPyth_ZZ_160_woCut->SetMarkerColor(kBlue+2); hist_TaxPyth_ZZ_160_woCut->SetMarkerStyle(3); hist_TaxPyth_ZZ_160_woCut->SetLineWidth(2); hist_TaxPyth_ZZ_160_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_tt_160_woCut = (TH1F*)input_160_woCut->Get("hist_TaxPyth_tt");
	hist_TaxPyth_tt_160_woCut->SetLineColor(kYellow+2); hist_TaxPyth_tt_160_woCut->SetMarkerColor(kYellow+2); hist_TaxPyth_tt_160_woCut->SetMarkerStyle(3); hist_TaxPyth_tt_160_woCut->SetLineWidth(2); hist_TaxPyth_tt_160_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HZ_160_woCut = (TH1F*)input_160_woCut->Get("hist_TaxPyth_HZ");
	hist_TaxPyth_HZ_160_woCut->SetLineColor(kMagenta+2); hist_TaxPyth_HZ_160_woCut->SetMarkerColor(kMagenta+2); hist_TaxPyth_HZ_160_woCut->SetMarkerStyle(53); hist_TaxPyth_HZ_160_woCut->SetLineWidth(2); hist_TaxPyth_HZ_160_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HW_160_woCut = (TH1F*)input_160_woCut->Get("hist_TaxPyth_HW");
	hist_TaxPyth_HW_160_woCut->SetLineColor(kCyan+2); hist_TaxPyth_HW_160_woCut->SetMarkerColor(kCyan+2); hist_TaxPyth_HW_160_woCut->SetMarkerStyle(53); hist_TaxPyth_HW_160_woCut->SetLineWidth(2); hist_TaxPyth_HW_160_woCut->SetMarkerSize(1);

	TH1F* hist_TaxPyth_al_240_woCut = (TH1F*)input_240_woCut->Get("hist_TaxPyth");
	hist_TaxPyth_al_240_woCut->SetLineColor(kBlack); hist_TaxPyth_al_240_woCut->SetMarkerColor(kBlack); hist_TaxPyth_al_240_woCut->SetMarkerStyle(3); hist_TaxPyth_al_240_woCut->SetLineWidth(2); hist_TaxPyth_al_240_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_Zq_240_woCut = (TH1F*)input_240_woCut->Get("hist_TaxPyth_Zq");
	hist_TaxPyth_Zq_240_woCut->SetLineColor(kRed+2); hist_TaxPyth_Zq_240_woCut->SetMarkerColor(kRed+2); hist_TaxPyth_Zq_240_woCut->SetMarkerStyle(3); hist_TaxPyth_Zq_240_woCut->SetLineWidth(2); hist_TaxPyth_Zq_240_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_WW_240_woCut = (TH1F*)input_240_woCut->Get("hist_TaxPyth_WW");
	hist_TaxPyth_WW_240_woCut->SetLineColor(kGreen+2); hist_TaxPyth_WW_240_woCut->SetMarkerColor(kGreen+2); hist_TaxPyth_WW_240_woCut->SetMarkerStyle(3); hist_TaxPyth_WW_240_woCut->SetLineWidth(2); hist_TaxPyth_WW_240_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_ZZ_240_woCut = (TH1F*)input_240_woCut->Get("hist_TaxPyth_ZZ");
	hist_TaxPyth_ZZ_240_woCut->SetLineColor(kBlue+2); hist_TaxPyth_ZZ_240_woCut->SetMarkerColor(kBlue+2); hist_TaxPyth_ZZ_240_woCut->SetMarkerStyle(3); hist_TaxPyth_ZZ_240_woCut->SetLineWidth(2); hist_TaxPyth_ZZ_240_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_tt_240_woCut = (TH1F*)input_240_woCut->Get("hist_TaxPyth_tt");
	hist_TaxPyth_tt_240_woCut->SetLineColor(kYellow+2); hist_TaxPyth_tt_240_woCut->SetMarkerColor(kYellow+2); hist_TaxPyth_tt_240_woCut->SetMarkerStyle(3); hist_TaxPyth_tt_240_woCut->SetLineWidth(2); hist_TaxPyth_tt_240_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HZ_240_woCut = (TH1F*)input_240_woCut->Get("hist_TaxPyth_HZ");
	hist_TaxPyth_HZ_240_woCut->SetLineColor(kMagenta+2); hist_TaxPyth_HZ_240_woCut->SetMarkerColor(kMagenta+2); hist_TaxPyth_HZ_240_woCut->SetMarkerStyle(53); hist_TaxPyth_HZ_240_woCut->SetLineWidth(2); hist_TaxPyth_HZ_240_woCut->SetMarkerSize(1);
	TH1F* hist_TaxPyth_HW_240_woCut = (TH1F*)input_240_woCut->Get("hist_TaxPyth_HW");
	hist_TaxPyth_HW_240_woCut->SetLineColor(kCyan+2); hist_TaxPyth_HW_240_woCut->SetMarkerColor(kCyan+2); hist_TaxPyth_HW_240_woCut->SetMarkerStyle(53); hist_TaxPyth_HW_240_woCut->SetLineWidth(2); hist_TaxPyth_HW_240_woCut->SetMarkerSize(1);

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F* hist_ThrPyth_al_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_ThrPyth");
	hist_ThrPyth_al_240_wiCut->SetLineColor(kBlack); hist_ThrPyth_al_240_wiCut->SetMarkerColor(kBlack); hist_ThrPyth_al_240_wiCut->SetMarkerStyle(3); hist_ThrPyth_al_240_wiCut->SetLineWidth(2); hist_ThrPyth_al_240_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_240_wiCut->SetLineColor(kRed+2); hist_ThrPyth_Zq_240_wiCut->SetMarkerColor(kRed+2); hist_ThrPyth_Zq_240_wiCut->SetMarkerStyle(3); hist_ThrPyth_Zq_240_wiCut->SetLineWidth(2); hist_ThrPyth_Zq_240_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_240_wiCut->SetLineColor(kGreen+2); hist_ThrPyth_WW_240_wiCut->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_240_wiCut->SetMarkerStyle(3); hist_ThrPyth_WW_240_wiCut->SetLineWidth(2); hist_ThrPyth_WW_240_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_240_wiCut->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_240_wiCut->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_240_wiCut->SetMarkerStyle(3); hist_ThrPyth_ZZ_240_wiCut->SetLineWidth(2); hist_ThrPyth_ZZ_240_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_240_wiCut->SetLineColor(kYellow+2); hist_ThrPyth_tt_240_wiCut->SetMarkerColor(kYellow+2); hist_ThrPyth_tt_240_wiCut->SetMarkerStyle(3); hist_ThrPyth_tt_240_wiCut->SetLineWidth(2); hist_ThrPyth_tt_240_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_240_wiCut->SetLineColor(kMagenta+2); hist_ThrPyth_HZ_240_wiCut->SetMarkerColor(kMagenta+2); hist_ThrPyth_HZ_240_wiCut->SetMarkerStyle(53); hist_ThrPyth_HZ_240_wiCut->SetLineWidth(2); hist_ThrPyth_HZ_240_wiCut->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW_240_wiCut->SetLineColor(kCyan+2); hist_ThrPyth_HW_240_wiCut->SetMarkerColor(kCyan+2); hist_ThrPyth_HW_240_wiCut->SetMarkerStyle(53); hist_ThrPyth_HW_240_wiCut->SetLineWidth(2); hist_ThrPyth_HW_240_wiCut->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_CprPyth");
	hist_CprPyth_al_240_wiCut->SetLineColor(kBlack); hist_CprPyth_al_240_wiCut->SetMarkerColor(kBlack); hist_CprPyth_al_240_wiCut->SetMarkerStyle(3); hist_CprPyth_al_240_wiCut->SetLineWidth(2); hist_CprPyth_al_240_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_240_wiCut->SetLineColor(kRed+2); hist_CprPyth_Zq_240_wiCut->SetMarkerColor(kRed+2); hist_CprPyth_Zq_240_wiCut->SetMarkerStyle(3); hist_CprPyth_Zq_240_wiCut->SetLineWidth(2); hist_CprPyth_Zq_240_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_240_wiCut->SetLineColor(kGreen+2); hist_CprPyth_WW_240_wiCut->SetMarkerColor(kGreen+2); hist_CprPyth_WW_240_wiCut->SetMarkerStyle(3); hist_CprPyth_WW_240_wiCut->SetLineWidth(2); hist_CprPyth_WW_240_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_240_wiCut->SetLineColor(kBlue+2); hist_CprPyth_ZZ_240_wiCut->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_240_wiCut->SetMarkerStyle(3); hist_CprPyth_ZZ_240_wiCut->SetLineWidth(2); hist_CprPyth_ZZ_240_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_240_wiCut->SetLineColor(kYellow+2); hist_CprPyth_tt_240_wiCut->SetMarkerColor(kYellow+2); hist_CprPyth_tt_240_wiCut->SetMarkerStyle(3); hist_CprPyth_tt_240_wiCut->SetLineWidth(2); hist_CprPyth_tt_240_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_240_wiCut->SetLineColor(kMagenta+2); hist_CprPyth_HZ_240_wiCut->SetMarkerColor(kMagenta+2); hist_CprPyth_HZ_240_wiCut->SetMarkerStyle(53); hist_CprPyth_HZ_240_wiCut->SetLineWidth(2); hist_CprPyth_HZ_240_wiCut->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW_240_wiCut = (TH1F*)input_240_wiCut->Get("hist_CprPyth_HW");
	hist_CprPyth_HW_240_wiCut->SetLineColor(kCyan+2); hist_CprPyth_HW_240_wiCut->SetMarkerColor(kCyan+2); hist_CprPyth_HW_240_wiCut->SetMarkerStyle(53); hist_CprPyth_HW_240_wiCut->SetLineWidth(2); hist_CprPyth_HW_240_wiCut->SetMarkerSize(1);

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

	hist_ThrPyth_al_240_woCut->SetStats(kFALSE);
	hist_CprPyth_al_240_woCut->SetStats(kFALSE);
	hist_ThrPyth_al_365_woCut->SetStats(kFALSE);
	hist_CprPyth_al_365_woCut->SetStats(kFALSE);

	hist_TaxPyth_al_912_woCut->SetStats(kFALSE);
	hist_TaxPyth_al_160_woCut->SetStats(kFALSE);
	hist_TaxPyth_al_240_woCut->SetStats(kFALSE);
	hist_TaxPyth_al_365_woCut->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit text sizes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_240_woCut->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_al_240_woCut->GetYaxis()->SetLabelSize(0.04); hist_ThrPyth_al_240_woCut->GetYaxis()->SetTitleSize(0.04); hist_ThrPyth_al_240_woCut->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_al_240_woCut->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_al_240_woCut->GetYaxis()->SetLabelSize(0.04); hist_CprPyth_al_240_woCut->GetYaxis()->SetTitleSize(0.04); hist_CprPyth_al_240_woCut->GetXaxis()->SetTitleSize(0.04); 
	hist_ThrPyth_al_365_woCut->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_al_365_woCut->GetYaxis()->SetLabelSize(0.04); hist_ThrPyth_al_365_woCut->GetYaxis()->SetTitleSize(0.04); hist_ThrPyth_al_365_woCut->GetXaxis()->SetTitleSize(0.04);
	hist_CprPyth_al_365_woCut->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_al_365_woCut->GetYaxis()->SetLabelSize(0.04); hist_CprPyth_al_365_woCut->GetYaxis()->SetTitleSize(0.04); hist_CprPyth_al_365_woCut->GetXaxis()->SetTitleSize(0.04); 

	hist_TaxPyth_al_912_woCut->GetXaxis()->SetLabelSize(0.04); hist_TaxPyth_al_912_woCut->GetYaxis()->SetLabelSize(0.04); hist_TaxPyth_al_912_woCut->GetYaxis()->SetTitleSize(0.04); hist_TaxPyth_al_912_woCut->GetXaxis()->SetTitleSize(0.04);
	hist_TaxPyth_al_160_woCut->GetXaxis()->SetLabelSize(0.04); hist_TaxPyth_al_160_woCut->GetYaxis()->SetLabelSize(0.04); hist_TaxPyth_al_160_woCut->GetYaxis()->SetTitleSize(0.04); hist_TaxPyth_al_160_woCut->GetXaxis()->SetTitleSize(0.04);
	hist_TaxPyth_al_240_woCut->GetXaxis()->SetLabelSize(0.04); hist_TaxPyth_al_240_woCut->GetYaxis()->SetLabelSize(0.04); hist_TaxPyth_al_240_woCut->GetYaxis()->SetTitleSize(0.04); hist_TaxPyth_al_240_woCut->GetXaxis()->SetTitleSize(0.04);
	hist_TaxPyth_al_365_woCut->GetXaxis()->SetLabelSize(0.04); hist_TaxPyth_al_365_woCut->GetYaxis()->SetLabelSize(0.04); hist_TaxPyth_al_365_woCut->GetYaxis()->SetTitleSize(0.04); hist_TaxPyth_al_365_woCut->GetXaxis()->SetTitleSize(0.04);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_240_woCut->SetTitle("");
	hist_CprPyth_al_240_woCut->SetTitle("");
	hist_ThrPyth_al_365_woCut->SetTitle("");
	hist_CprPyth_al_365_woCut->SetTitle("");

	hist_TaxPyth_al_912_woCut->SetTitle("");
	hist_TaxPyth_al_160_woCut->SetTitle("");
	hist_TaxPyth_al_240_woCut->SetTitle("");
	hist_TaxPyth_al_365_woCut->SetTitle("");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw Plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv5 = new TCanvas("cv5", "FCC-ee ISR Studies", 2000, 900);

	// // Add legend
	// TLegend* lg5 = new TLegend(0.75, 0.70, 0.92, 0.95);
	// lg5->AddEntry(hist_TaxPyth_al_365_woCut, "ee#rightarrowq#bar{q}", "L");
	// lg5->AddEntry(hist_TaxPyth_Zq_365_woCut, "ee#rightarrow#gamma/Z", "L");
	// lg5->AddEntry(hist_TaxPyth_ZZ_365_woCut, "ee#rightarrowZZ", "L");
	// lg5->AddEntry(hist_TaxPyth_WW_365_woCut, "ee#rightarrowWW", "L");
	// lg5->AddEntry(hist_TaxPyth_tt_365_woCut, "ee#rightarrowt#bar{t}", "L");
	// lg5->AddEntry(hist_TaxPyth_HZ_365_woCut, "ee#rightarrowZH", "L");
	// lg5->AddEntry(hist_TaxPyth_HW_365_woCut, "ee#rightarrow#nu#bar{#nu}H", "L");
	// lg5->SetTextSize(0.03);

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv5->SetMargin(0, 0, 0, 0); 
	// cv5->Divide(4,1);
	// for (int i = 1; i <= 4; i++) {
	// 	cv5->cd(i);
	// 	gPad->SetTopMargin(0.017);
	// 	gPad->SetBottomMargin(0.1);
	// 	gPad->SetLeftMargin(0.10);
	// 	gPad->SetRightMargin(0.04);
	// 	gPad->SetTickx(); gPad->SetTicky();
	// 	gPad->SetLogy();
	// }

	// // Draw
	// cv5->cd(1);
	// hist_TaxPyth_al_912_woCut->Draw("HIST");
	// hist_TaxPyth_Zq_912_woCut->Draw("HIST SAME");
	// hist_TaxPyth_WW_912_woCut->Draw("HIST SAME");
	// hist_TaxPyth_ZZ_912_woCut->Draw("HIST SAME");
	// hist_TaxPyth_tt_912_woCut->Draw("HIST SAME");
	// hist_TaxPyth_HZ_912_woCut->Draw("HIST SAME");
	// hist_TaxPyth_HW_912_woCut->Draw("HIST SAME");
	// lg5->Draw("SAME");

	// cv5->cd(2);
	// hist_TaxPyth_al_160_woCut->Draw("HIST");
	// hist_TaxPyth_Zq_160_woCut->Draw("HIST SAME");
	// hist_TaxPyth_WW_160_woCut->Draw("HIST SAME");
	// hist_TaxPyth_ZZ_160_woCut->Draw("HIST SAME");
	// hist_TaxPyth_tt_160_woCut->Draw("HIST SAME");
	// hist_TaxPyth_HZ_160_woCut->Draw("HIST SAME");
	// hist_TaxPyth_HW_160_woCut->Draw("HIST SAME");
	// lg5->Draw("SAME");

	// cv5->cd(3);
	// hist_TaxPyth_al_240_woCut->Draw("HIST");
	// hist_TaxPyth_Zq_240_woCut->Draw("HIST SAME");
	// hist_TaxPyth_WW_240_woCut->Draw("HIST SAME");
	// hist_TaxPyth_ZZ_240_woCut->Draw("HIST SAME");
	// hist_TaxPyth_tt_240_woCut->Draw("HIST SAME");
	// hist_TaxPyth_HZ_240_woCut->Draw("HIST SAME");
	// hist_TaxPyth_HW_240_woCut->Draw("HIST SAME");
	// lg5->Draw("SAME");

	// cv5->cd(4);
	// hist_TaxPyth_al_365_woCut->Draw("HIST");
	// hist_TaxPyth_Zq_365_woCut->Draw("HIST SAME");
	// hist_TaxPyth_WW_365_woCut->Draw("HIST SAME");
	// hist_TaxPyth_ZZ_365_woCut->Draw("HIST SAME");
	// hist_TaxPyth_tt_365_woCut->Draw("HIST SAME");
	// hist_TaxPyth_HZ_365_woCut->Draw("HIST SAME");
	// hist_TaxPyth_HW_365_woCut->Draw("HIST SAME");
	// lg5->Draw("SAME");

	// // Set limits
	// hist_TaxPyth_al_912_woCut->GetYaxis()->SetRangeUser(1E0,1E6);
	// hist_TaxPyth_al_912_woCut->GetXaxis()->SetRangeUser(-1,1);
	// hist_TaxPyth_al_160_woCut->GetYaxis()->SetRangeUser(1E0,1E6);
	// hist_TaxPyth_al_160_woCut->GetXaxis()->SetRangeUser(-1,1);
	// hist_TaxPyth_al_240_woCut->GetYaxis()->SetRangeUser(1E0,1E6);
	// hist_TaxPyth_al_240_woCut->GetXaxis()->SetRangeUser(-1,1);
	// hist_TaxPyth_al_365_woCut->GetYaxis()->SetRangeUser(1E0,1E6);
	// hist_TaxPyth_al_365_woCut->GetXaxis()->SetRangeUser(-1,1);
	
	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv5->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv1 = new TCanvas("cv1", "FCC-ee ISR Studies", 1600, 800);

	// Add legend
	TLegend* lg1 = new TLegend(0.77, 0.75, 0.92, 0.95);
	lg1->AddEntry(hist_ThrPyth_al_240_woCut, "ee#rightarrowq#bar{q}", "L");
	lg1->AddEntry(hist_ThrPyth_ZZ_240_woCut, "ee#rightarrowWW", "L");
	lg1->AddEntry(hist_ThrPyth_WW_240_woCut, "ee#rightarrowZZ", "L");
	lg1->AddEntry(hist_ThrPyth_tt_240_woCut, "ee#rightarrowt#bar{t}", "L");
	lg1->AddEntry(hist_ThrPyth_HZ_240_woCut, "ee#rightarrowZH", "L");
	lg1->AddEntry(hist_ThrPyth_HW_240_woCut, "ee#rightarrow#nu#bar{#nu}H", "L");
	lg1->SetTextSize(0.03);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv1->SetMargin(0, 0, 0, 0); 
	cv1->Divide(2,1);
	for (int i = 1; i <= 2; i++) {
		cv1->cd(i);
		gPad->SetTopMargin(0.017);
		gPad->SetBottomMargin(0.1);
		gPad->SetLeftMargin(0.15);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		gPad->SetLogy();
	}

	hist_ThrPyth_al_240_wiCut->SetLineStyle(7);
	hist_ThrPyth_Zq_240_wiCut->SetLineStyle(7);
	hist_ThrPyth_WW_240_wiCut->SetLineStyle(7);
	hist_ThrPyth_ZZ_240_wiCut->SetLineStyle(7);
	hist_ThrPyth_tt_240_wiCut->SetLineStyle(7);
	hist_ThrPyth_HZ_240_wiCut->SetLineStyle(7);
	hist_ThrPyth_HW_240_wiCut->SetLineStyle(7);

	hist_CprPyth_al_240_wiCut->SetLineStyle(7);
	hist_CprPyth_Zq_240_wiCut->SetLineStyle(7);
	hist_CprPyth_WW_240_wiCut->SetLineStyle(7);
	hist_CprPyth_ZZ_240_wiCut->SetLineStyle(7);
	hist_CprPyth_tt_240_wiCut->SetLineStyle(7);
	hist_CprPyth_HZ_240_wiCut->SetLineStyle(7);
	hist_CprPyth_HW_240_wiCut->SetLineStyle(7);

	hist_ThrPyth_Zq_240_woCut->GetYaxis()->SetTitle("N_{events}");
	hist_CprPyth_Zq_240_woCut->GetYaxis()->SetTitle("N_{events}");

	hist_ThrPyth_Zq_240_woCut->GetXaxis()->CenterTitle(); hist_ThrPyth_Zq_240_woCut->GetYaxis()->CenterTitle();
	hist_CprPyth_Zq_240_woCut->GetXaxis()->CenterTitle(); hist_CprPyth_Zq_240_woCut->GetYaxis()->CenterTitle();
	
	// Draw
	cv1->cd(1);
	hist_ThrPyth_al_240_woCut->Draw("HIST");
	hist_ThrPyth_Zq_240_woCut->Draw("HIST SAME");
	hist_ThrPyth_WW_240_woCut->Draw("HIST SAME");
	hist_ThrPyth_ZZ_240_woCut->Draw("HIST SAME");
	hist_ThrPyth_tt_240_woCut->Draw("HIST SAME");
	hist_ThrPyth_HZ_240_woCut->Draw("HIST SAME");
	hist_ThrPyth_HW_240_woCut->Draw("HIST SAME");
	hist_ThrPyth_al_240_wiCut->Draw("HIST SAME");
	hist_ThrPyth_Zq_240_wiCut->Draw("HIST SAME");
	hist_ThrPyth_WW_240_wiCut->Draw("HIST SAME");
	hist_ThrPyth_ZZ_240_wiCut->Draw("HIST SAME");
	hist_ThrPyth_tt_240_wiCut->Draw("HIST SAME");
	hist_ThrPyth_HZ_240_wiCut->Draw("HIST SAME");
	hist_ThrPyth_HW_240_wiCut->Draw("HIST SAME");
	lg1->Draw("SAME");

	cv1->cd(2);
	hist_CprPyth_al_240_woCut->Draw("HIST");
	hist_CprPyth_Zq_240_woCut->Draw("HIST SAME");
	hist_CprPyth_WW_240_woCut->Draw("HIST SAME");
	hist_CprPyth_ZZ_240_woCut->Draw("HIST SAME");
	hist_CprPyth_tt_240_woCut->Draw("HIST SAME");
	hist_CprPyth_HZ_240_woCut->Draw("HIST SAME");
	hist_CprPyth_HW_240_woCut->Draw("HIST SAME");
	hist_CprPyth_al_240_wiCut->Draw("HIST SAME");
	hist_CprPyth_Zq_240_wiCut->Draw("HIST SAME");
	hist_CprPyth_WW_240_wiCut->Draw("HIST SAME");
	hist_CprPyth_ZZ_240_wiCut->Draw("HIST SAME");
	hist_CprPyth_tt_240_wiCut->Draw("HIST SAME");
	hist_CprPyth_HZ_240_wiCut->Draw("HIST SAME");
	hist_CprPyth_HW_240_wiCut->Draw("HIST SAME");
	// lg1->Draw("SAME");

	// Set limits
	hist_ThrPyth_Zq_240_woCut->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_ThrPyth_Zq_240_woCut->GetXaxis()->SetRangeUser(0,0.45);
	hist_CprPyth_Zq_240_woCut->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_CprPyth_Zq_240_woCut->GetXaxis()->SetRangeUser(0,1.0);	

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv1->Modified();

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 1600, 800);

	// Add legend
	TLegend* lg2 = new TLegend(0.77, 0.75, 0.92, 0.95);
	lg2->AddEntry(hist_ThrPyth_al_365_woCut, "ee#rightarrowq#bar{q}", "L");
	lg2->AddEntry(hist_ThrPyth_ZZ_365_woCut, "ee#rightarrowWW", "L");
	lg2->AddEntry(hist_ThrPyth_WW_365_woCut, "ee#rightarrowZZ", "L");
	lg2->AddEntry(hist_ThrPyth_tt_365_woCut, "ee#rightarrowt#bar{t}", "L");
	lg2->AddEntry(hist_ThrPyth_HZ_365_woCut, "ee#rightarrowZH", "L");
	lg2->AddEntry(hist_ThrPyth_HW_365_woCut, "ee#rightarrow#nu#bar{#nu}H", "L");
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

	hist_ThrPyth_al_365_wiCut->SetLineStyle(7);
	hist_ThrPyth_Zq_365_wiCut->SetLineStyle(7);
	hist_ThrPyth_WW_365_wiCut->SetLineStyle(7);
	hist_ThrPyth_ZZ_365_wiCut->SetLineStyle(7);
	hist_ThrPyth_tt_365_wiCut->SetLineStyle(7);
	hist_ThrPyth_HZ_365_wiCut->SetLineStyle(7);
	hist_ThrPyth_HW_365_wiCut->SetLineStyle(7);

	hist_CprPyth_al_365_wiCut->SetLineStyle(7);
	hist_CprPyth_Zq_365_wiCut->SetLineStyle(7);
	hist_CprPyth_WW_365_wiCut->SetLineStyle(7);
	hist_CprPyth_ZZ_365_wiCut->SetLineStyle(7);
	hist_CprPyth_tt_365_wiCut->SetLineStyle(7);
	hist_CprPyth_HZ_365_wiCut->SetLineStyle(7);
	hist_CprPyth_HW_365_wiCut->SetLineStyle(7);

	hist_ThrPyth_Zq_365_woCut->GetYaxis()->SetTitle("N_{events}");
	hist_CprPyth_Zq_365_woCut->GetYaxis()->SetTitle("N_{events}");

	hist_ThrPyth_Zq_365_woCut->GetXaxis()->CenterTitle(); hist_ThrPyth_Zq_365_woCut->GetYaxis()->CenterTitle();
	hist_CprPyth_Zq_365_woCut->GetXaxis()->CenterTitle(); hist_CprPyth_Zq_365_woCut->GetYaxis()->CenterTitle();
	
	// Draw
	cv2->cd(1);
	hist_ThrPyth_al_365_woCut->Draw("HIST");
	hist_ThrPyth_Zq_365_woCut->Draw("HIST SAME");
	hist_ThrPyth_WW_365_woCut->Draw("HIST SAME");
	hist_ThrPyth_ZZ_365_woCut->Draw("HIST SAME");
	hist_ThrPyth_tt_365_woCut->Draw("HIST SAME");
	hist_ThrPyth_HZ_365_woCut->Draw("HIST SAME");
	hist_ThrPyth_HW_365_woCut->Draw("HIST SAME");
	hist_ThrPyth_al_365_wiCut->Draw("HIST SAME");
	hist_ThrPyth_Zq_365_wiCut->Draw("HIST SAME");
	hist_ThrPyth_WW_365_wiCut->Draw("HIST SAME");
	hist_ThrPyth_ZZ_365_wiCut->Draw("HIST SAME");
	hist_ThrPyth_tt_365_wiCut->Draw("HIST SAME");
	hist_ThrPyth_HZ_365_wiCut->Draw("HIST SAME");
	hist_ThrPyth_HW_365_wiCut->Draw("HIST SAME");
	lg2->Draw("SAME");

	cv2->cd(2);
	hist_CprPyth_al_365_woCut->Draw("HIST");
	hist_CprPyth_Zq_365_woCut->Draw("HIST SAME");
	hist_CprPyth_WW_365_woCut->Draw("HIST SAME");
	hist_CprPyth_ZZ_365_woCut->Draw("HIST SAME");
	hist_CprPyth_tt_365_woCut->Draw("HIST SAME");
	hist_CprPyth_HZ_365_woCut->Draw("HIST SAME");
	hist_CprPyth_HW_365_woCut->Draw("HIST SAME");
	hist_CprPyth_al_365_wiCut->Draw("HIST SAME");
	hist_CprPyth_Zq_365_wiCut->Draw("HIST SAME");
	hist_CprPyth_WW_365_wiCut->Draw("HIST SAME");
	hist_CprPyth_ZZ_365_wiCut->Draw("HIST SAME");
	hist_CprPyth_tt_365_wiCut->Draw("HIST SAME");
	hist_CprPyth_HZ_365_wiCut->Draw("HIST SAME");
	hist_CprPyth_HW_365_wiCut->Draw("HIST SAME");
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

}