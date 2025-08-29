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
void ImpactofProc()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile* input_912 = new TFile("5-CutData/cut_FCC912.root", "READ");
	TFile* input_160 = new TFile("5-CutData/cut_FCC160.root", "READ");
	TFile* input_240 = new TFile("5-CutData/cut_FCC240.root", "READ");
	TFile* input_365 = new TFile("5-CutData/cut_FCC365.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F* hist_ThrPyth_al_912 = (TH1F*)input_912->Get("hist_ThrPyth");
	hist_ThrPyth_al_912->SetLineColor(kBlack); hist_ThrPyth_al_912->SetMarkerColor(kBlack); hist_ThrPyth_al_912->SetMarkerStyle(3); hist_ThrPyth_al_912->SetLineWidth(2); hist_ThrPyth_al_912->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_912 = (TH1F*)input_912->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_912->SetLineColor(kYellow+2); hist_ThrPyth_Zq_912->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_912->SetMarkerStyle(3); hist_ThrPyth_Zq_912->SetLineWidth(2); hist_ThrPyth_Zq_912->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_912 = (TH1F*)input_912->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_912->SetLineColor(kGreen+2); hist_ThrPyth_WW_912->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_912->SetMarkerStyle(3); hist_ThrPyth_WW_912->SetLineWidth(2); hist_ThrPyth_WW_912->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_912 = (TH1F*)input_912->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_912->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_912->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_912->SetMarkerStyle(3); hist_ThrPyth_ZZ_912->SetLineWidth(2); hist_ThrPyth_ZZ_912->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_912 = (TH1F*)input_912->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_912->SetLineColor(kRed+2); hist_ThrPyth_tt_912->SetMarkerColor(kRed+2); hist_ThrPyth_tt_912->SetMarkerStyle(3); hist_ThrPyth_tt_912->SetLineWidth(2); hist_ThrPyth_tt_912->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_912 = (TH1F*)input_912->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_912->SetLineColor(kBlue+2); hist_ThrPyth_HZ_912->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_912->SetMarkerStyle(53); hist_ThrPyth_HZ_912->SetLineWidth(2); hist_ThrPyth_HZ_912->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW_912 = (TH1F*)input_912->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW_912->SetLineColor(kRed+2); hist_ThrPyth_HW_912->SetMarkerColor(kRed+2); hist_ThrPyth_HW_912->SetMarkerStyle(53); hist_ThrPyth_HW_912->SetLineWidth(2); hist_ThrPyth_HW_912->SetMarkerSize(1);

	TH1F* hist_ThrPyth_al_160 = (TH1F*)input_160->Get("hist_ThrPyth");
	hist_ThrPyth_al_160->SetLineColor(kBlack); hist_ThrPyth_al_160->SetMarkerColor(kBlack); hist_ThrPyth_al_160->SetMarkerStyle(3); hist_ThrPyth_al_160->SetLineWidth(2); hist_ThrPyth_al_160->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_160 = (TH1F*)input_160->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_160->SetLineColor(kYellow+2); hist_ThrPyth_Zq_160->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_160->SetMarkerStyle(3); hist_ThrPyth_Zq_160->SetLineWidth(2); hist_ThrPyth_Zq_160->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_160 = (TH1F*)input_160->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_160->SetLineColor(kGreen+2); hist_ThrPyth_WW_160->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_160->SetMarkerStyle(3); hist_ThrPyth_WW_160->SetLineWidth(2); hist_ThrPyth_WW_160->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_160 = (TH1F*)input_160->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_160->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_160->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_160->SetMarkerStyle(3); hist_ThrPyth_ZZ_160->SetLineWidth(2); hist_ThrPyth_ZZ_160->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_160 = (TH1F*)input_160->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_160->SetLineColor(kRed+2); hist_ThrPyth_tt_160->SetMarkerColor(kRed+2); hist_ThrPyth_tt_160->SetMarkerStyle(3); hist_ThrPyth_tt_160->SetLineWidth(2); hist_ThrPyth_tt_160->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_160 = (TH1F*)input_160->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_160->SetLineColor(kBlue+2); hist_ThrPyth_HZ_160->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_160->SetMarkerStyle(53); hist_ThrPyth_HZ_160->SetLineWidth(2); hist_ThrPyth_HZ_160->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW_160 = (TH1F*)input_160->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW_160->SetLineColor(kRed+2); hist_ThrPyth_HW_160->SetMarkerColor(kRed+2); hist_ThrPyth_HW_160->SetMarkerStyle(53); hist_ThrPyth_HW_160->SetLineWidth(2); hist_ThrPyth_HW_160->SetMarkerSize(1);

	TH1F* hist_ThrPyth_al_240 = (TH1F*)input_240->Get("hist_ThrPyth");
	hist_ThrPyth_al_240->SetLineColor(kBlack); hist_ThrPyth_al_240->SetMarkerColor(kBlack); hist_ThrPyth_al_240->SetMarkerStyle(3); hist_ThrPyth_al_240->SetLineWidth(2); hist_ThrPyth_al_240->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_240 = (TH1F*)input_240->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_240->SetLineColor(kYellow+2); hist_ThrPyth_Zq_240->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_240->SetMarkerStyle(3); hist_ThrPyth_Zq_240->SetLineWidth(2); hist_ThrPyth_Zq_240->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_240 = (TH1F*)input_240->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_240->SetLineColor(kGreen+2); hist_ThrPyth_WW_240->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_240->SetMarkerStyle(3); hist_ThrPyth_WW_240->SetLineWidth(2); hist_ThrPyth_WW_240->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_240 = (TH1F*)input_240->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_240->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_240->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_240->SetMarkerStyle(3); hist_ThrPyth_ZZ_240->SetLineWidth(2); hist_ThrPyth_ZZ_240->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_240 = (TH1F*)input_240->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_240->SetLineColor(kRed+2); hist_ThrPyth_tt_240->SetMarkerColor(kRed+2); hist_ThrPyth_tt_240->SetMarkerStyle(3); hist_ThrPyth_tt_240->SetLineWidth(2); hist_ThrPyth_tt_240->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_240 = (TH1F*)input_240->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_240->SetLineColor(kBlue+2); hist_ThrPyth_HZ_240->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_240->SetMarkerStyle(53); hist_ThrPyth_HZ_240->SetLineWidth(2); hist_ThrPyth_HZ_240->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW_240 = (TH1F*)input_240->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW_240->SetLineColor(kRed+2); hist_ThrPyth_HW_240->SetMarkerColor(kRed+2); hist_ThrPyth_HW_240->SetMarkerStyle(53); hist_ThrPyth_HW_240->SetLineWidth(2); hist_ThrPyth_HW_240->SetMarkerSize(1);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F* hist_CprPyth_al_912 = (TH1F*)input_912->Get("hist_CprPyth");
	hist_CprPyth_al_912->SetLineColor(kBlack); hist_CprPyth_al_912->SetMarkerColor(kBlack); hist_CprPyth_al_912->SetMarkerStyle(3); hist_CprPyth_al_912->SetLineWidth(2); hist_CprPyth_al_912->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_912 = (TH1F*)input_912->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_912->SetLineColor(kYellow+2); hist_CprPyth_Zq_912->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_912->SetMarkerStyle(3); hist_CprPyth_Zq_912->SetLineWidth(2); hist_CprPyth_Zq_912->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_912 = (TH1F*)input_912->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_912->SetLineColor(kGreen+2); hist_CprPyth_WW_912->SetMarkerColor(kGreen+2); hist_CprPyth_WW_912->SetMarkerStyle(3); hist_CprPyth_WW_912->SetLineWidth(2); hist_CprPyth_WW_912->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_912 = (TH1F*)input_912->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_912->SetLineColor(kBlue+2); hist_CprPyth_ZZ_912->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_912->SetMarkerStyle(3); hist_CprPyth_ZZ_912->SetLineWidth(2); hist_CprPyth_ZZ_912->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_912 = (TH1F*)input_912->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_912->SetLineColor(kRed+2); hist_CprPyth_tt_912->SetMarkerColor(kRed+2); hist_CprPyth_tt_912->SetMarkerStyle(3); hist_CprPyth_tt_912->SetLineWidth(2); hist_CprPyth_tt_912->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_912 = (TH1F*)input_912->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_912->SetLineColor(kBlue+2); hist_CprPyth_HZ_912->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_912->SetMarkerStyle(53); hist_CprPyth_HZ_912->SetLineWidth(2); hist_CprPyth_HZ_912->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW_912 = (TH1F*)input_912->Get("hist_CprPyth_HW");
	hist_CprPyth_HW_912->SetLineColor(kRed+2); hist_CprPyth_HW_912->SetMarkerColor(kRed+2); hist_CprPyth_HW_912->SetMarkerStyle(53); hist_CprPyth_HW_912->SetLineWidth(2); hist_CprPyth_HW_912->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_160 = (TH1F*)input_160->Get("hist_CprPyth");
	hist_CprPyth_al_160->SetLineColor(kBlack); hist_CprPyth_al_160->SetMarkerColor(kBlack); hist_CprPyth_al_160->SetMarkerStyle(3); hist_CprPyth_al_160->SetLineWidth(2); hist_CprPyth_al_160->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_160 = (TH1F*)input_160->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_160->SetLineColor(kYellow+2); hist_CprPyth_Zq_160->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_160->SetMarkerStyle(3); hist_CprPyth_Zq_160->SetLineWidth(2); hist_CprPyth_Zq_160->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_160 = (TH1F*)input_160->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_160->SetLineColor(kGreen+2); hist_CprPyth_WW_160->SetMarkerColor(kGreen+2); hist_CprPyth_WW_160->SetMarkerStyle(3); hist_CprPyth_WW_160->SetLineWidth(2); hist_CprPyth_WW_160->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_160 = (TH1F*)input_160->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_160->SetLineColor(kBlue+2); hist_CprPyth_ZZ_160->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_160->SetMarkerStyle(3); hist_CprPyth_ZZ_160->SetLineWidth(2); hist_CprPyth_ZZ_160->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_160 = (TH1F*)input_160->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_160->SetLineColor(kRed+2); hist_CprPyth_tt_160->SetMarkerColor(kRed+2); hist_CprPyth_tt_160->SetMarkerStyle(3); hist_CprPyth_tt_160->SetLineWidth(2); hist_CprPyth_tt_160->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_160 = (TH1F*)input_160->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_160->SetLineColor(kBlue+2); hist_CprPyth_HZ_160->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_160->SetMarkerStyle(53); hist_CprPyth_HZ_160->SetLineWidth(2); hist_CprPyth_HZ_160->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW_160 = (TH1F*)input_160->Get("hist_CprPyth_HW");
	hist_CprPyth_HW_160->SetLineColor(kRed+2); hist_CprPyth_HW_160->SetMarkerColor(kRed+2); hist_CprPyth_HW_160->SetMarkerStyle(53); hist_CprPyth_HW_160->SetLineWidth(2); hist_CprPyth_HW_160->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_240 = (TH1F*)input_240->Get("hist_CprPyth");
	hist_CprPyth_al_240->SetLineColor(kBlack); hist_CprPyth_al_240->SetMarkerColor(kBlack); hist_CprPyth_al_240->SetMarkerStyle(3); hist_CprPyth_al_240->SetLineWidth(2); hist_CprPyth_al_240->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_240 = (TH1F*)input_240->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_240->SetLineColor(kYellow+2); hist_CprPyth_Zq_240->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_240->SetMarkerStyle(3); hist_CprPyth_Zq_240->SetLineWidth(2); hist_CprPyth_Zq_240->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_240 = (TH1F*)input_240->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_240->SetLineColor(kGreen+2); hist_CprPyth_WW_240->SetMarkerColor(kGreen+2); hist_CprPyth_WW_240->SetMarkerStyle(3); hist_CprPyth_WW_240->SetLineWidth(2); hist_CprPyth_WW_240->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_240 = (TH1F*)input_240->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_240->SetLineColor(kBlue+2); hist_CprPyth_ZZ_240->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_240->SetMarkerStyle(3); hist_CprPyth_ZZ_240->SetLineWidth(2); hist_CprPyth_ZZ_240->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_240 = (TH1F*)input_240->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_240->SetLineColor(kRed+2); hist_CprPyth_tt_240->SetMarkerColor(kRed+2); hist_CprPyth_tt_240->SetMarkerStyle(3); hist_CprPyth_tt_240->SetLineWidth(2); hist_CprPyth_tt_240->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_240 = (TH1F*)input_240->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_240->SetLineColor(kBlue+2); hist_CprPyth_HZ_240->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_240->SetMarkerStyle(53); hist_CprPyth_HZ_240->SetLineWidth(2); hist_CprPyth_HZ_240->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW_240 = (TH1F*)input_240->Get("hist_CprPyth_HW");
	hist_CprPyth_HW_240->SetLineColor(kRed+2); hist_CprPyth_HW_240->SetMarkerColor(kRed+2); hist_CprPyth_HW_240->SetMarkerStyle(53); hist_CprPyth_HW_240->SetLineWidth(2); hist_CprPyth_HW_240->SetMarkerSize(1);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F* hist_ThrPyth_al_365 = (TH1F*)input_365->Get("hist_ThrPyth");
	hist_ThrPyth_al_365->SetLineColor(kBlack); hist_ThrPyth_al_365->SetMarkerColor(kBlack); hist_ThrPyth_al_365->SetMarkerStyle(3); hist_ThrPyth_al_365->SetLineWidth(2); hist_ThrPyth_al_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_365 = (TH1F*)input_365->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_365->SetLineColor(kRed+2); hist_ThrPyth_Zq_365->SetMarkerColor(kRed+2); hist_ThrPyth_Zq_365->SetMarkerStyle(3); hist_ThrPyth_Zq_365->SetLineWidth(2); hist_ThrPyth_Zq_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_365 = (TH1F*)input_365->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_365->SetLineColor(kGreen+2); hist_ThrPyth_WW_365->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_365->SetMarkerStyle(3); hist_ThrPyth_WW_365->SetLineWidth(2); hist_ThrPyth_WW_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_365 = (TH1F*)input_365->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_365->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_365->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_365->SetMarkerStyle(3); hist_ThrPyth_ZZ_365->SetLineWidth(2); hist_ThrPyth_ZZ_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_365 = (TH1F*)input_365->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_365->SetLineColor(kYellow+2); hist_ThrPyth_tt_365->SetMarkerColor(kYellow+2); hist_ThrPyth_tt_365->SetMarkerStyle(3); hist_ThrPyth_tt_365->SetLineWidth(2); hist_ThrPyth_tt_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_365 = (TH1F*)input_365->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_365->SetLineColor(kMagenta+2); hist_ThrPyth_HZ_365->SetMarkerColor(kMagenta+2); hist_ThrPyth_HZ_365->SetMarkerStyle(53); hist_ThrPyth_HZ_365->SetLineWidth(2); hist_ThrPyth_HZ_365->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HW_365 = (TH1F*)input_365->Get("hist_ThrPyth_HW");
	hist_ThrPyth_HW_365->SetLineColor(kCyan+2); hist_ThrPyth_HW_365->SetMarkerColor(kCyan+2); hist_ThrPyth_HW_365->SetMarkerStyle(53); hist_ThrPyth_HW_365->SetLineWidth(2); hist_ThrPyth_HW_365->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_365 = (TH1F*)input_365->Get("hist_CprPyth");
	hist_CprPyth_al_365->SetLineColor(kBlack); hist_CprPyth_al_365->SetMarkerColor(kBlack); hist_CprPyth_al_365->SetMarkerStyle(3); hist_CprPyth_al_365->SetLineWidth(2); hist_CprPyth_al_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_365 = (TH1F*)input_365->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_365->SetLineColor(kRed+2); hist_CprPyth_Zq_365->SetMarkerColor(kRed+2); hist_CprPyth_Zq_365->SetMarkerStyle(3); hist_CprPyth_Zq_365->SetLineWidth(2); hist_CprPyth_Zq_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_365 = (TH1F*)input_365->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_365->SetLineColor(kGreen+2); hist_CprPyth_WW_365->SetMarkerColor(kGreen+2); hist_CprPyth_WW_365->SetMarkerStyle(3); hist_CprPyth_WW_365->SetLineWidth(2); hist_CprPyth_WW_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_365 = (TH1F*)input_365->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_365->SetLineColor(kBlue+2); hist_CprPyth_ZZ_365->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_365->SetMarkerStyle(3); hist_CprPyth_ZZ_365->SetLineWidth(2); hist_CprPyth_ZZ_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_365 = (TH1F*)input_365->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_365->SetLineColor(kYellow+2); hist_CprPyth_tt_365->SetMarkerColor(kYellow+2); hist_CprPyth_tt_365->SetMarkerStyle(3); hist_CprPyth_tt_365->SetLineWidth(2); hist_CprPyth_tt_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_365 = (TH1F*)input_365->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_365->SetLineColor(kMagenta+2); hist_CprPyth_HZ_365->SetMarkerColor(kMagenta+2); hist_CprPyth_HZ_365->SetMarkerStyle(53); hist_CprPyth_HZ_365->SetLineWidth(2); hist_CprPyth_HZ_365->SetMarkerSize(1);
	TH1F* hist_CprPyth_HW_365 = (TH1F*)input_365->Get("hist_CprPyth_HW");
	hist_CprPyth_HW_365->SetLineColor(kCyan+2); hist_CprPyth_HW_365->SetMarkerColor(kCyan+2); hist_CprPyth_HW_365->SetMarkerStyle(53); hist_CprPyth_HW_365->SetLineWidth(2); hist_CprPyth_HW_365->SetMarkerSize(1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_912->SetStats(kFALSE);
	hist_ThrPyth_WW_912->SetStats(kFALSE);
	hist_ThrPyth_ZZ_912->SetStats(kFALSE);
	hist_ThrPyth_tt_912->SetStats(kFALSE);
	hist_ThrPyth_HZ_912->SetStats(kFALSE);
	hist_ThrPyth_HW_912->SetStats(kFALSE);

	hist_ThrPyth_al_160->SetStats(kFALSE);
	hist_ThrPyth_WW_160->SetStats(kFALSE);
	hist_ThrPyth_ZZ_160->SetStats(kFALSE);
	hist_ThrPyth_tt_160->SetStats(kFALSE);
	hist_ThrPyth_HZ_160->SetStats(kFALSE);
	hist_ThrPyth_HW_160->SetStats(kFALSE);

	hist_ThrPyth_al_240->SetStats(kFALSE);
	hist_ThrPyth_WW_240->SetStats(kFALSE);
	hist_ThrPyth_ZZ_240->SetStats(kFALSE);
	hist_ThrPyth_tt_240->SetStats(kFALSE);
	hist_ThrPyth_HZ_240->SetStats(kFALSE);
	hist_ThrPyth_HW_240->SetStats(kFALSE);

	hist_ThrPyth_al_365->SetStats(kFALSE);
	hist_ThrPyth_WW_365->SetStats(kFALSE);
	hist_ThrPyth_ZZ_365->SetStats(kFALSE);
	hist_ThrPyth_tt_365->SetStats(kFALSE);
	hist_ThrPyth_HZ_365->SetStats(kFALSE);
	hist_ThrPyth_HW_365->SetStats(kFALSE);

	hist_CprPyth_al_912->SetStats(kFALSE);
	hist_CprPyth_WW_912->SetStats(kFALSE);
	hist_CprPyth_ZZ_912->SetStats(kFALSE);
	hist_CprPyth_tt_912->SetStats(kFALSE);
	hist_CprPyth_HZ_912->SetStats(kFALSE);
	hist_CprPyth_HW_912->SetStats(kFALSE);

	hist_CprPyth_al_160->SetStats(kFALSE);
	hist_CprPyth_WW_160->SetStats(kFALSE);
	hist_CprPyth_ZZ_160->SetStats(kFALSE);
	hist_CprPyth_tt_160->SetStats(kFALSE);
	hist_CprPyth_HZ_160->SetStats(kFALSE);
	hist_CprPyth_HW_160->SetStats(kFALSE);

	hist_CprPyth_al_240->SetStats(kFALSE);
	hist_CprPyth_WW_240->SetStats(kFALSE);
	hist_CprPyth_ZZ_240->SetStats(kFALSE);
	hist_CprPyth_tt_240->SetStats(kFALSE);
	hist_CprPyth_HZ_240->SetStats(kFALSE);
	hist_CprPyth_HW_240->SetStats(kFALSE);

	hist_CprPyth_al_365->SetStats(kFALSE);
	hist_CprPyth_WW_365->SetStats(kFALSE);
	hist_CprPyth_ZZ_365->SetStats(kFALSE);
	hist_CprPyth_tt_365->SetStats(kFALSE);
	hist_CprPyth_HZ_365->SetStats(kFALSE);
	hist_CprPyth_HW_365->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_912->SetTitle("");
	hist_ThrPyth_al_160->SetTitle("");
	hist_ThrPyth_al_240->SetTitle("");
	hist_ThrPyth_al_365->SetTitle("");

	hist_CprPyth_al_912->SetTitle("");
	hist_CprPyth_al_160->SetTitle("");
	hist_CprPyth_al_240->SetTitle("");
	hist_CprPyth_al_365->SetTitle("");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit text sizes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_912->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_al_912->GetYaxis()->SetLabelSize(0.04); hist_ThrPyth_al_912->GetYaxis()->SetTitleSize(0.04); hist_ThrPyth_al_912->GetXaxis()->SetTitleSize(0.04); 
	hist_ThrPyth_al_160->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_al_160->GetYaxis()->SetLabelSize(0.04); hist_ThrPyth_al_160->GetYaxis()->SetTitleSize(0.04); hist_ThrPyth_al_160->GetXaxis()->SetTitleSize(0.04); 
	hist_ThrPyth_al_240->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_al_240->GetYaxis()->SetLabelSize(0.04); hist_ThrPyth_al_240->GetYaxis()->SetTitleSize(0.04); hist_ThrPyth_al_240->GetXaxis()->SetTitleSize(0.04); 
	hist_ThrPyth_al_365->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_al_365->GetYaxis()->SetLabelSize(0.04); hist_ThrPyth_al_365->GetYaxis()->SetTitleSize(0.04); hist_ThrPyth_al_365->GetXaxis()->SetTitleSize(0.04); 

	hist_CprPyth_al_912->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_al_912->GetYaxis()->SetLabelSize(0.04); hist_CprPyth_al_912->GetYaxis()->SetTitleSize(0.04); hist_CprPyth_al_912->GetXaxis()->SetTitleSize(0.04); 
	hist_CprPyth_al_160->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_al_160->GetYaxis()->SetLabelSize(0.04); hist_CprPyth_al_160->GetYaxis()->SetTitleSize(0.04); hist_CprPyth_al_160->GetXaxis()->SetTitleSize(0.04); 
	hist_CprPyth_al_240->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_al_240->GetYaxis()->SetLabelSize(0.04); hist_CprPyth_al_240->GetYaxis()->SetTitleSize(0.04); hist_CprPyth_al_240->GetXaxis()->SetTitleSize(0.04); 
	hist_CprPyth_al_365->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_al_365->GetYaxis()->SetLabelSize(0.04); hist_CprPyth_al_365->GetYaxis()->SetTitleSize(0.04); hist_CprPyth_al_365->GetXaxis()->SetTitleSize(0.04); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create canvas
	TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 1600, 1400);

	// Add legend
	TLegend* lg2 = new TLegend(0.79, 0.70, 0.92, 0.95);
	lg2->AddEntry(hist_ThrPyth_al_365, "ee#rightarrowq#bar{q}", "L");
	lg2->AddEntry(hist_ThrPyth_Zq_365, "ee#rightarrow#gamma*/Z", "L");
	lg2->AddEntry(hist_ThrPyth_ZZ_365, "ee#rightarrowWW", "L");
	lg2->AddEntry(hist_ThrPyth_WW_365, "ee#rightarrowZZ", "L");
	lg2->AddEntry(hist_ThrPyth_tt_365, "ee#rightarrowt#bar{t}", "L");
	lg2->AddEntry(hist_ThrPyth_HZ_365, "ee#rightarrowZH", "L");
	lg2->AddEntry(hist_ThrPyth_HW_365, "ee#rightarrow#nu#bar{#nu}H", "L");
	lg2->SetTextSize(0.03);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv2->SetMargin(0, 0, 0, 0); 
	cv2->Divide(2,2);
	for (int i = 1; i <= 4; i++) {
		cv2->cd(i);
		gPad->SetTopMargin(0.017);
		gPad->SetBottomMargin(0.1);
		gPad->SetLeftMargin(0.15);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		gPad->SetLogy();
	}

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
	hist_ThrPyth_al_365->Draw("HIST");
	hist_ThrPyth_Zq_365->Draw("HIST SAME");
	hist_ThrPyth_WW_365->Draw("HIST SAME");
	hist_ThrPyth_ZZ_365->Draw("HIST SAME");
	hist_ThrPyth_tt_365->Draw("HIST SAME");
	hist_ThrPyth_HZ_365->Draw("HIST SAME");
	hist_ThrPyth_HW_365->Draw("HIST SAME");
	lg2->Draw("SAME");

	cv2->cd(3);
	hist_CprPyth_al_365->Draw("HIST");
	hist_CprPyth_Zq_365->Draw("HIST SAME");
	hist_CprPyth_WW_365->Draw("HIST SAME");
	hist_CprPyth_ZZ_365->Draw("HIST SAME");
	hist_CprPyth_tt_365->Draw("HIST SAME");
	hist_CprPyth_HZ_365->Draw("HIST SAME");
	hist_CprPyth_HW_365->Draw("HIST SAME");
	lg2->Draw("SAME");

	cv2->cd(4);
	hist_CprPyth_al_365->Draw("HIST");
	hist_CprPyth_Zq_365->Draw("HIST SAME");
	hist_CprPyth_WW_365->Draw("HIST SAME");
	hist_CprPyth_ZZ_365->Draw("HIST SAME");
	hist_CprPyth_tt_365->Draw("HIST SAME");
	hist_CprPyth_HZ_365->Draw("HIST SAME");
	hist_CprPyth_HW_365->Draw("HIST SAME");
	lg2->Draw("SAME");

	// Set limits
	hist_ThrPyth_al_365->GetYaxis()->SetRangeUser(1E0,1E5);
	hist_ThrPyth_al_365->GetXaxis()->SetRangeUser(0,0.4);
	hist_CprPyth_al_365->GetYaxis()->SetRangeUser(1E0,1E5);
	hist_CprPyth_al_365->GetXaxis()->SetRangeUser(0,1.0);	

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv2->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising by area under histogram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
// 	hist_ThrPyth_al_912->Scale(1.0/hist_ThrPyth_al_912->Integral("width"));
// 	hist_ThrPyth_Zq_912->Scale(1.0/hist_ThrPyth_Zq_912->Integral("width"));
// 	hist_ThrPyth_WW_912->Scale(1.0/hist_ThrPyth_WW_912->Integral("width"));
// 	hist_ThrPyth_ZZ_912->Scale(1.0/hist_ThrPyth_ZZ_912->Integral("width"));
// 	hist_ThrPyth_tt_912->Scale(1.0/hist_ThrPyth_tt_912->Integral("width"));
// 	hist_ThrPyth_HZ_912->Scale(1.0/hist_ThrPyth_HZ_912->Integral("width"));
// 	hist_ThrPyth_HW_912->Scale(1.0/hist_ThrPyth_HW_912->Integral("width"));

// 	hist_ThrPyth_al_160->Scale(1.0/hist_ThrPyth_al_160->Integral("width"));
// 	hist_ThrPyth_Zq_160->Scale(1.0/hist_ThrPyth_Zq_160->Integral("width"));
// 	hist_ThrPyth_WW_160->Scale(1.0/hist_ThrPyth_WW_160->Integral("width"));
// 	hist_ThrPyth_ZZ_160->Scale(1.0/hist_ThrPyth_ZZ_160->Integral("width"));
// 	hist_ThrPyth_tt_160->Scale(1.0/hist_ThrPyth_tt_160->Integral("width"));
// 	hist_ThrPyth_HZ_160->Scale(1.0/hist_ThrPyth_HZ_160->Integral("width"));
// 	hist_ThrPyth_HW_160->Scale(1.0/hist_ThrPyth_HW_160->Integral("width"));

// 	hist_ThrPyth_al_240->Scale(1.0/hist_ThrPyth_al_240->Integral("width"));
// 	hist_ThrPyth_Zq_240->Scale(1.0/hist_ThrPyth_Zq_240->Integral("width"));
// 	hist_ThrPyth_WW_240->Scale(1.0/hist_ThrPyth_WW_240->Integral("width"));
// 	hist_ThrPyth_ZZ_240->Scale(1.0/hist_ThrPyth_ZZ_240->Integral("width"));
// 	hist_ThrPyth_tt_240->Scale(1.0/hist_ThrPyth_tt_240->Integral("width"));
// 	hist_ThrPyth_HZ_240->Scale(1.0/hist_ThrPyth_HZ_240->Integral("width"));
// 	hist_ThrPyth_HW_240->Scale(1.0/hist_ThrPyth_HW_240->Integral("width"));

// 	hist_ThrPyth_al_365->Scale(1.0/hist_ThrPyth_al_365->Integral("width"));
// 	hist_ThrPyth_Zq_365->Scale(1.0/hist_ThrPyth_Zq_365->Integral("width"));
// 	hist_ThrPyth_WW_365->Scale(1.0/hist_ThrPyth_WW_365->Integral("width"));
// 	hist_ThrPyth_ZZ_365->Scale(1.0/hist_ThrPyth_ZZ_365->Integral("width"));
// 	hist_ThrPyth_tt_365->Scale(1.0/hist_ThrPyth_tt_365->Integral("width"));
// 	hist_ThrPyth_HZ_365->Scale(1.0/hist_ThrPyth_HZ_365->Integral("width"));
// 	hist_ThrPyth_HW_365->Scale(1.0/hist_ThrPyth_HW_365->Integral("width"));

// // /////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 	hist_CprPyth_al_912->Scale(1.0/hist_CprPyth_al_912->Integral("width"));
// 	hist_CprPyth_Zq_912->Scale(1.0/hist_CprPyth_Zq_912->Integral("width"));
// 	hist_CprPyth_WW_912->Scale(1.0/hist_CprPyth_WW_912->Integral("width"));
// 	hist_CprPyth_ZZ_912->Scale(1.0/hist_CprPyth_ZZ_912->Integral("width"));
// 	hist_CprPyth_tt_912->Scale(1.0/hist_CprPyth_tt_912->Integral("width"));
// 	hist_CprPyth_HZ_912->Scale(1.0/hist_CprPyth_HZ_912->Integral("width"));
// 	hist_CprPyth_HW_912->Scale(1.0/hist_CprPyth_HW_912->Integral("width"));

// 	hist_CprPyth_al_160->Scale(1.0/hist_CprPyth_al_160->Integral("width"));
// 	hist_CprPyth_Zq_160->Scale(1.0/hist_CprPyth_Zq_160->Integral("width"));
// 	hist_CprPyth_WW_160->Scale(1.0/hist_CprPyth_WW_160->Integral("width"));
// 	hist_CprPyth_ZZ_160->Scale(1.0/hist_CprPyth_ZZ_160->Integral("width"));
// 	hist_CprPyth_tt_160->Scale(1.0/hist_CprPyth_tt_160->Integral("width"));
// 	hist_CprPyth_HZ_160->Scale(1.0/hist_CprPyth_HZ_160->Integral("width"));
// 	hist_CprPyth_HW_160->Scale(1.0/hist_CprPyth_HW_160->Integral("width"));

// 	hist_CprPyth_al_240->Scale(1.0/hist_CprPyth_al_240->Integral("width"));
// 	hist_CprPyth_Zq_240->Scale(1.0/hist_CprPyth_Zq_240->Integral("width"));
// 	hist_CprPyth_WW_240->Scale(1.0/hist_CprPyth_WW_240->Integral("width"));
// 	hist_CprPyth_ZZ_240->Scale(1.0/hist_CprPyth_ZZ_240->Integral("width"));
// 	hist_CprPyth_tt_240->Scale(1.0/hist_CprPyth_tt_240->Integral("width"));
// 	hist_CprPyth_HZ_240->Scale(1.0/hist_CprPyth_HZ_240->Integral("width"));
// 	hist_CprPyth_HW_240->Scale(1.0/hist_CprPyth_HW_240->Integral("width"));

// 	hist_CprPyth_al_365->Scale(1.0/hist_CprPyth_al_365->Integral("width"));
// 	hist_CprPyth_Zq_365->Scale(1.0/hist_CprPyth_Zq_365->Integral("width"));
// 	hist_CprPyth_WW_365->Scale(1.0/hist_CprPyth_WW_365->Integral("width"));
// 	hist_CprPyth_ZZ_365->Scale(1.0/hist_CprPyth_ZZ_365->Integral("width"));
// 	hist_CprPyth_tt_365->Scale(1.0/hist_CprPyth_tt_365->Integral("width"));
// 	hist_CprPyth_HZ_365->Scale(1.0/hist_CprPyth_HZ_365->Integral("width"));
// 	hist_CprPyth_HW_365->Scale(1.0/hist_CprPyth_HW_365->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 	hist_ThrPyth_al_912->SetTitle("");
// 	hist_ThrPyth_al_160->SetTitle("");
// 	hist_ThrPyth_al_240->SetTitle("");
// 	hist_ThrPyth_al_365->SetTitle("");

// 	hist_CprPyth_al_912->SetTitle("");
// 	hist_CprPyth_al_160->SetTitle("");
// 	hist_CprPyth_al_240->SetTitle("");
// 	hist_CprPyth_al_365->SetTitle("");

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // Edit text sizes
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 	hist_ThrPyth_al_912->GetXaxis()->SetLabelSize(0.06); hist_ThrPyth_al_912->GetYaxis()->SetLabelSize(0.06); hist_ThrPyth_al_912->GetYaxis()->SetTitleSize(0.06); hist_ThrPyth_al_912->GetXaxis()->SetTitleSize(0.06); 
// 	hist_ThrPyth_al_160->GetXaxis()->SetLabelSize(0.06); hist_ThrPyth_al_160->GetYaxis()->SetLabelSize(0.06); hist_ThrPyth_al_160->GetYaxis()->SetTitleSize(0.06); hist_ThrPyth_al_160->GetXaxis()->SetTitleSize(0.06); 
// 	hist_ThrPyth_al_240->GetXaxis()->SetLabelSize(0.06); hist_ThrPyth_al_240->GetYaxis()->SetLabelSize(0.06); hist_ThrPyth_al_240->GetYaxis()->SetTitleSize(0.06); hist_ThrPyth_al_240->GetXaxis()->SetTitleSize(0.06); 
// 	hist_ThrPyth_al_365->GetXaxis()->SetLabelSize(0.06); hist_ThrPyth_al_365->GetYaxis()->SetLabelSize(0.06); hist_ThrPyth_al_365->GetYaxis()->SetTitleSize(0.06); hist_ThrPyth_al_365->GetXaxis()->SetTitleSize(0.06); 

// 	hist_CprPyth_al_912->GetXaxis()->SetLabelSize(0.06); hist_CprPyth_al_912->GetYaxis()->SetLabelSize(0.06); hist_CprPyth_al_912->GetYaxis()->SetTitleSize(0.06); hist_CprPyth_al_912->GetXaxis()->SetTitleSize(0.06); 
// 	hist_CprPyth_al_160->GetXaxis()->SetLabelSize(0.06); hist_CprPyth_al_160->GetYaxis()->SetLabelSize(0.06); hist_CprPyth_al_160->GetYaxis()->SetTitleSize(0.06); hist_CprPyth_al_160->GetXaxis()->SetTitleSize(0.06); 
// 	hist_CprPyth_al_240->GetXaxis()->SetLabelSize(0.06); hist_CprPyth_al_240->GetYaxis()->SetLabelSize(0.06); hist_CprPyth_al_240->GetYaxis()->SetTitleSize(0.06); hist_CprPyth_al_240->GetXaxis()->SetTitleSize(0.06); 
// 	hist_CprPyth_al_365->GetXaxis()->SetLabelSize(0.06); hist_CprPyth_al_365->GetYaxis()->SetLabelSize(0.06); hist_CprPyth_al_365->GetYaxis()->SetTitleSize(0.06); hist_CprPyth_al_365->GetXaxis()->SetTitleSize(0.06); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv1 = new TCanvas("cv1", "FCC-ee ISR Studies", 1000, 1400);

	// // Add legend
	// TLegend* lg1 = new TLegend(0.20, 0.20, 0.40, 0.36);
	// lg1->AddEntry(hist_ThrPyth_al_912, "ee#rightarrowq#bar{q}", "p");
	// lg1->AddEntry(hist_ThrPyth_Zq_912, "ee#rightarrow#gamma*/Z", "pl");
	// lg1->SetTextSize(0.06);

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv1->SetMargin(0, 0, 0, 0); 
	// cv1->Divide(2,4);
	// for (int i = 1; i <= 8; i++) {
	// 	cv1->cd(i);
	// 	gPad->SetTopMargin(0.025);
	// 	gPad->SetBottomMargin(0.14);
	// 	gPad->SetLeftMargin(0.15);
	// 	gPad->SetRightMargin(0.04);
	// 	gPad->SetTickx(); gPad->SetTicky();
	// 	gPad->SetLogy();
	// }

	// // Draw
	// cv1->cd(1);
	// hist_ThrPyth_al_912->Draw("HIST");
	// hist_ThrPyth_Zq_912->Draw("HIST SAME");
	// lg1->Draw("SAME");
	// cv1->cd(3);
	// hist_ThrPyth_al_160->Draw("HIST");
	// hist_ThrPyth_Zq_160->Draw("HIST SAME");
	// lg1->Draw("SAME");
	// cv1->cd(5);
	// hist_ThrPyth_al_240->Draw("HIST");
	// hist_ThrPyth_Zq_240->Draw("HIST SAME");
	// lg1->Draw("SAME");
	// cv1->cd(7);
	// hist_ThrPyth_al_365->Draw("HIST");
	// hist_ThrPyth_Zq_365->Draw("HIST SAME");
	// lg1->Draw("SAME");

	// cv1->cd(2);
	// hist_CprPyth_al_912->Draw("HIST");
	// hist_CprPyth_Zq_912->Draw("HIST SAME");
	// lg1->Draw("SAME");
	// cv1->cd(4);
	// hist_CprPyth_al_160->Draw("HIST");
	// hist_CprPyth_Zq_160->Draw("HIST SAME");
	// lg1->Draw("SAME");
	// cv1->cd(6);
	// hist_CprPyth_al_240->Draw("HIST");
	// hist_CprPyth_Zq_240->Draw("HIST SAME");
	// lg1->Draw("SAME");
	// cv1->cd(8);
	// hist_CprPyth_al_365->Draw("HIST");
	// hist_CprPyth_Zq_365->Draw("HIST SAME");
	// lg1->Draw("SAME");

	// // Set limits
	// hist_ThrPyth_al_912->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_ThrPyth_al_912->GetXaxis()->SetRangeUser(0,0.4);
	// hist_ThrPyth_al_160->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_ThrPyth_al_160->GetXaxis()->SetRangeUser(0,0.4);
	// hist_ThrPyth_al_240->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_ThrPyth_al_240->GetXaxis()->SetRangeUser(0,0.4);
	// hist_ThrPyth_al_365->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_ThrPyth_al_365->GetXaxis()->SetRangeUser(0,0.4);

	// hist_CprPyth_al_912->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_CprPyth_al_912->GetXaxis()->SetRangeUser(0,1.0);
	// hist_CprPyth_al_160->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_CprPyth_al_160->GetXaxis()->SetRangeUser(0,1.0);
	// hist_CprPyth_al_240->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_CprPyth_al_240->GetXaxis()->SetRangeUser(0,1.0);
	// hist_CprPyth_al_365->GetYaxis()->SetRangeUser(1E-4,1E2);
	// hist_CprPyth_al_365->GetXaxis()->SetRangeUser(0,1.0);	

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv1->Modified();

}