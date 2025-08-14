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
void ImpactofRad()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile* input_912_woISR = new TFile("cut_FCC912.root", "READ");
	TFile* input_160_woISR = new TFile("cut_FCC160.root", "READ");
	TFile* input_240_woISR = new TFile("cut_FCC240.root", "READ");
	TFile* input_365_woISR = new TFile("cut_FCC365.root", "READ");

	TFile* input_912_wiISR = new TFile("cut_FCC912_ISR.root", "READ");
	TFile* input_160_wiISR = new TFile("cut_FCC160_ISR.root", "READ");
	TFile* input_240_wiISR = new TFile("cut_FCC240_ISR.root", "READ");
	TFile* input_365_wiISR = new TFile("cut_FCC365_ISR.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	TH1F *hist_NumbISR_912 = (TH1F*)input_912_wiISR->Get("hist_NumbISR");
	hist_NumbISR_912->SetLineColor(kRed+2); hist_NumbISR_912->SetMarkerColor(kRed+2); hist_NumbISR_912->SetMarkerStyle(53); hist_NumbISR_912->SetLineWidth(2);
	TH1F *hist_NumbISR_160 = (TH1F*)input_160_wiISR->Get("hist_NumbISR");
	hist_NumbISR_160->SetLineColor(kGreen+2); hist_NumbISR_160->SetMarkerColor(kGreen+2); hist_NumbISR_160->SetMarkerStyle(53); hist_NumbISR_160->SetLineWidth(2);
	TH1F *hist_NumbISR_240 = (TH1F*)input_240_wiISR->Get("hist_NumbISR");
	hist_NumbISR_240->SetLineColor(kYellow+2); hist_NumbISR_240->SetMarkerColor(kYellow+2); hist_NumbISR_240->SetMarkerStyle(53); hist_NumbISR_240->SetLineWidth(2);
	TH1F *hist_NumbISR_365 = (TH1F*)input_365_wiISR->Get("hist_NumbISR");
	hist_NumbISR_365->SetLineColor(kBlue+2); hist_NumbISR_365->SetMarkerColor(kBlue+2); hist_NumbISR_365->SetMarkerStyle(53); hist_NumbISR_365->SetLineWidth(2);

	TH1F *hist_Esprime_912 = (TH1F*)input_912_wiISR->Get("hist_Esprime_al");
	hist_Esprime_912->SetLineColor(kRed+2); hist_Esprime_912->SetMarkerColor(kRed+2); hist_Esprime_912->SetMarkerStyle(53); hist_Esprime_912->SetLineWidth(3);
	TH1F *hist_Esprime_160 = (TH1F*)input_160_wiISR->Get("hist_Esprime_al");
	hist_Esprime_160->SetLineColor(kGreen+2); hist_Esprime_160->SetMarkerColor(kGreen+2); hist_Esprime_160->SetMarkerStyle(53); hist_Esprime_160->SetLineWidth(3);
	TH1F *hist_Esprime_240 = (TH1F*)input_240_wiISR->Get("hist_Esprime_al");
	hist_Esprime_240->SetLineColor(kYellow+2); hist_Esprime_240->SetMarkerColor(kYellow+2); hist_Esprime_240->SetMarkerStyle(53); hist_Esprime_240->SetLineWidth(3);
	TH1F *hist_Esprime_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_al");
	hist_Esprime_365->SetLineColor(kBlack); hist_Esprime_365->SetMarkerColor(kBlue+2); hist_Esprime_365->SetMarkerStyle(53); hist_Esprime_365->SetLineWidth(2); hist_Esprime_365->SetMarkerSize(1);

	TH1F* hist_Esprime_Zq_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_Zq");
	hist_Esprime_Zq_365->SetLineColor(kYellow+2); hist_Esprime_Zq_365->SetMarkerColor(kYellow+2); hist_Esprime_Zq_365->SetMarkerStyle(3); hist_Esprime_Zq_365->SetLineStyle(1); hist_Esprime_Zq_365->SetLineWidth(2); hist_Esprime_Zq_365->SetMarkerSize(1);
	TH1F* hist_Esprime_WW_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_WW");
	hist_Esprime_WW_365->SetLineColor(kGreen+2); hist_Esprime_WW_365->SetMarkerColor(kGreen+2); hist_Esprime_WW_365->SetMarkerStyle(3); hist_Esprime_WW_365->SetLineStyle(1); hist_Esprime_WW_365->SetLineWidth(2); hist_Esprime_WW_365->SetMarkerSize(1);
	TH1F* hist_Esprime_ZZ_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_ZZ");
	hist_Esprime_ZZ_365->SetLineColor(kBlue+2); hist_Esprime_ZZ_365->SetMarkerColor(kBlue+2); hist_Esprime_ZZ_365->SetMarkerStyle(3); hist_Esprime_ZZ_365->SetLineStyle(1); hist_Esprime_ZZ_365->SetLineWidth(2); hist_Esprime_ZZ_365->SetMarkerSize(1);
	TH1F* hist_Esprime_tt_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_tt");
	hist_Esprime_tt_365->SetLineColor(kRed+2); hist_Esprime_tt_365->SetMarkerColor(kRed+2); hist_Esprime_tt_365->SetMarkerStyle(3); hist_Esprime_tt_365->SetLineStyle(1); hist_Esprime_tt_365->SetLineWidth(2); hist_Esprime_tt_365->SetMarkerSize(1);
	TH1F* hist_Esprime_HZ_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_HZ");
	hist_Esprime_HZ_365->SetLineColor(kGreen+2); hist_Esprime_HZ_365->SetMarkerColor(kGreen+2); hist_Esprime_HZ_365->SetMarkerStyle(53); hist_Esprime_HZ_365->SetLineStyle(2); hist_Esprime_HZ_365->SetLineWidth(2); hist_Esprime_HZ_365->SetMarkerSize(1);
	TH1F* hist_Esprime_hW_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_hW");
	hist_Esprime_hW_365->SetLineColor(kRed+2); hist_Esprime_hW_365->SetMarkerColor(kRed+2); hist_Esprime_hW_365->SetMarkerStyle(53); hist_Esprime_hW_365->SetLineStyle(2); hist_Esprime_hW_365->SetLineWidth(2); hist_Esprime_hW_365->SetMarkerSize(1);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F* hist_ThrPyth_al_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_ThrPyth");
	hist_ThrPyth_al_912_wiISR->SetLineColor(kBlack); hist_ThrPyth_al_912_wiISR->SetMarkerColor(kBlack); hist_ThrPyth_al_912_wiISR->SetMarkerStyle(3); hist_ThrPyth_al_912_wiISR->SetLineWidth(2); hist_ThrPyth_al_912_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_912_wiISR->SetLineColor(kYellow+2); hist_ThrPyth_Zq_912_wiISR->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_912_wiISR->SetMarkerStyle(3); hist_ThrPyth_Zq_912_wiISR->SetLineWidth(2); hist_ThrPyth_Zq_912_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_912_wiISR->SetLineColor(kGreen+2); hist_ThrPyth_WW_912_wiISR->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_912_wiISR->SetMarkerStyle(3); hist_ThrPyth_WW_912_wiISR->SetLineWidth(2); hist_ThrPyth_WW_912_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_912_wiISR->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_912_wiISR->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_912_wiISR->SetMarkerStyle(3); hist_ThrPyth_ZZ_912_wiISR->SetLineWidth(2); hist_ThrPyth_ZZ_912_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_912_wiISR->SetLineColor(kRed+2); hist_ThrPyth_tt_912_wiISR->SetMarkerColor(kRed+2); hist_ThrPyth_tt_912_wiISR->SetMarkerStyle(3); hist_ThrPyth_tt_912_wiISR->SetLineWidth(2); hist_ThrPyth_tt_912_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_912_wiISR->SetLineColor(kBlue+2); hist_ThrPyth_HZ_912_wiISR->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_912_wiISR->SetMarkerStyle(53); hist_ThrPyth_HZ_912_wiISR->SetLineWidth(2); hist_ThrPyth_HZ_912_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_hW_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_hW");
	hist_ThrPyth_hW_912_wiISR->SetLineColor(kRed+2); hist_ThrPyth_hW_912_wiISR->SetMarkerColor(kRed+2); hist_ThrPyth_hW_912_wiISR->SetMarkerStyle(53); hist_ThrPyth_hW_912_wiISR->SetLineWidth(2); hist_ThrPyth_hW_912_wiISR->SetMarkerSize(1);

	TH1F* hist_ThrPyth_al_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_ThrPyth");
	hist_ThrPyth_al_160_wiISR->SetLineColor(kBlack); hist_ThrPyth_al_160_wiISR->SetMarkerColor(kBlack); hist_ThrPyth_al_160_wiISR->SetMarkerStyle(3); hist_ThrPyth_al_160_wiISR->SetLineWidth(2); hist_ThrPyth_al_160_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_160_wiISR->SetLineColor(kYellow+2); hist_ThrPyth_Zq_160_wiISR->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_160_wiISR->SetMarkerStyle(3); hist_ThrPyth_Zq_160_wiISR->SetLineWidth(2); hist_ThrPyth_Zq_160_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_160_wiISR->SetLineColor(kGreen+2); hist_ThrPyth_WW_160_wiISR->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_160_wiISR->SetMarkerStyle(3); hist_ThrPyth_WW_160_wiISR->SetLineWidth(2); hist_ThrPyth_WW_160_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_160_wiISR->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_160_wiISR->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_160_wiISR->SetMarkerStyle(3); hist_ThrPyth_ZZ_160_wiISR->SetLineWidth(2); hist_ThrPyth_ZZ_160_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_160_wiISR->SetLineColor(kRed+2); hist_ThrPyth_tt_160_wiISR->SetMarkerColor(kRed+2); hist_ThrPyth_tt_160_wiISR->SetMarkerStyle(3); hist_ThrPyth_tt_160_wiISR->SetLineWidth(2); hist_ThrPyth_tt_160_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_160_wiISR->SetLineColor(kBlue+2); hist_ThrPyth_HZ_160_wiISR->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_160_wiISR->SetMarkerStyle(53); hist_ThrPyth_HZ_160_wiISR->SetLineWidth(2); hist_ThrPyth_HZ_160_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_hW_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_hW");
	hist_ThrPyth_hW_160_wiISR->SetLineColor(kRed+2); hist_ThrPyth_hW_160_wiISR->SetMarkerColor(kRed+2); hist_ThrPyth_hW_160_wiISR->SetMarkerStyle(53); hist_ThrPyth_hW_160_wiISR->SetLineWidth(2); hist_ThrPyth_hW_160_wiISR->SetMarkerSize(1);

	TH1F* hist_ThrPyth_al_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_ThrPyth");
	hist_ThrPyth_al_240_wiISR->SetLineColor(kBlack); hist_ThrPyth_al_240_wiISR->SetMarkerColor(kBlack); hist_ThrPyth_al_240_wiISR->SetMarkerStyle(3); hist_ThrPyth_al_240_wiISR->SetLineWidth(2); hist_ThrPyth_al_240_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_240_wiISR->SetLineColor(kYellow+2); hist_ThrPyth_Zq_240_wiISR->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_240_wiISR->SetMarkerStyle(3); hist_ThrPyth_Zq_240_wiISR->SetLineWidth(2); hist_ThrPyth_Zq_240_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_240_wiISR->SetLineColor(kGreen+2); hist_ThrPyth_WW_240_wiISR->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_240_wiISR->SetMarkerStyle(3); hist_ThrPyth_WW_240_wiISR->SetLineWidth(2); hist_ThrPyth_WW_240_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_240_wiISR->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_240_wiISR->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_240_wiISR->SetMarkerStyle(3); hist_ThrPyth_ZZ_240_wiISR->SetLineWidth(2); hist_ThrPyth_ZZ_240_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_240_wiISR->SetLineColor(kRed+2); hist_ThrPyth_tt_240_wiISR->SetMarkerColor(kRed+2); hist_ThrPyth_tt_240_wiISR->SetMarkerStyle(3); hist_ThrPyth_tt_240_wiISR->SetLineWidth(2); hist_ThrPyth_tt_240_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_240_wiISR->SetLineColor(kBlue+2); hist_ThrPyth_HZ_240_wiISR->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_240_wiISR->SetMarkerStyle(53); hist_ThrPyth_HZ_240_wiISR->SetLineWidth(2); hist_ThrPyth_HZ_240_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_hW_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_hW");
	hist_ThrPyth_hW_240_wiISR->SetLineColor(kRed+2); hist_ThrPyth_hW_240_wiISR->SetMarkerColor(kRed+2); hist_ThrPyth_hW_240_wiISR->SetMarkerStyle(53); hist_ThrPyth_hW_240_wiISR->SetLineWidth(2); hist_ThrPyth_hW_240_wiISR->SetMarkerSize(1);

	TH1F* hist_ThrPyth_al_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_ThrPyth");
	hist_ThrPyth_al_365_wiISR->SetLineColor(kBlack); hist_ThrPyth_al_365_wiISR->SetMarkerColor(kBlack); hist_ThrPyth_al_365_wiISR->SetMarkerStyle(3); hist_ThrPyth_al_365_wiISR->SetLineWidth(2); hist_ThrPyth_al_365_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_365_wiISR->SetLineColor(kYellow+2); hist_ThrPyth_Zq_365_wiISR->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_365_wiISR->SetMarkerStyle(3); hist_ThrPyth_Zq_365_wiISR->SetLineWidth(2); hist_ThrPyth_Zq_365_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_365_wiISR->SetLineColor(kGreen+2); hist_ThrPyth_WW_365_wiISR->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_365_wiISR->SetMarkerStyle(3); hist_ThrPyth_WW_365_wiISR->SetLineWidth(2); hist_ThrPyth_WW_365_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_365_wiISR->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_365_wiISR->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_365_wiISR->SetMarkerStyle(3); hist_ThrPyth_ZZ_365_wiISR->SetLineWidth(2); hist_ThrPyth_ZZ_365_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_365_wiISR->SetLineColor(kRed+2); hist_ThrPyth_tt_365_wiISR->SetMarkerColor(kRed+2); hist_ThrPyth_tt_365_wiISR->SetMarkerStyle(3); hist_ThrPyth_tt_365_wiISR->SetLineWidth(2); hist_ThrPyth_tt_365_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_365_wiISR->SetLineColor(kBlue+2); hist_ThrPyth_HZ_365_wiISR->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_365_wiISR->SetMarkerStyle(53); hist_ThrPyth_HZ_365_wiISR->SetLineStyle(2); hist_ThrPyth_HZ_365_wiISR->SetLineWidth(2); hist_ThrPyth_HZ_365_wiISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_hW_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_hW");
	hist_ThrPyth_hW_365_wiISR->SetLineColor(kRed+2); hist_ThrPyth_hW_365_wiISR->SetMarkerColor(kRed+2); hist_ThrPyth_hW_365_wiISR->SetMarkerStyle(53); hist_ThrPyth_hW_365_wiISR->SetLineStyle(2); hist_ThrPyth_hW_365_wiISR->SetLineWidth(2); hist_ThrPyth_hW_365_wiISR->SetMarkerSize(1);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F* hist_CprPyth_al_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_CprPyth");
	hist_CprPyth_al_912_wiISR->SetLineColor(kBlack); hist_CprPyth_al_912_wiISR->SetMarkerColor(kBlack); hist_CprPyth_al_912_wiISR->SetMarkerStyle(3); hist_CprPyth_al_912_wiISR->SetLineWidth(2); hist_CprPyth_al_912_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_912_wiISR->SetLineColor(kYellow+2); hist_CprPyth_Zq_912_wiISR->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_912_wiISR->SetMarkerStyle(3); hist_CprPyth_Zq_912_wiISR->SetLineWidth(2); hist_CprPyth_Zq_912_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_912_wiISR->SetLineColor(kGreen+2); hist_CprPyth_WW_912_wiISR->SetMarkerColor(kGreen+2); hist_CprPyth_WW_912_wiISR->SetMarkerStyle(3); hist_CprPyth_WW_912_wiISR->SetLineWidth(2); hist_CprPyth_WW_912_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_912_wiISR->SetLineColor(kBlue+2); hist_CprPyth_ZZ_912_wiISR->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_912_wiISR->SetMarkerStyle(3); hist_CprPyth_ZZ_912_wiISR->SetLineWidth(2); hist_CprPyth_ZZ_912_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_912_wiISR->SetLineColor(kRed+2); hist_CprPyth_tt_912_wiISR->SetMarkerColor(kRed+2); hist_CprPyth_tt_912_wiISR->SetMarkerStyle(3); hist_CprPyth_tt_912_wiISR->SetLineWidth(2); hist_CprPyth_tt_912_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_912_wiISR->SetLineColor(kBlue+2); hist_CprPyth_HZ_912_wiISR->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_912_wiISR->SetMarkerStyle(53); hist_CprPyth_HZ_912_wiISR->SetLineWidth(2); hist_CprPyth_HZ_912_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_hW_912_wiISR = (TH1F*)input_912_wiISR->Get("hist_CprPyth_hW");
	hist_CprPyth_hW_912_wiISR->SetLineColor(kRed+2); hist_CprPyth_hW_912_wiISR->SetMarkerColor(kRed+2); hist_CprPyth_hW_912_wiISR->SetMarkerStyle(53); hist_CprPyth_hW_912_wiISR->SetLineWidth(2); hist_CprPyth_hW_912_wiISR->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_CprPyth");
	hist_CprPyth_al_160_wiISR->SetLineColor(kBlack); hist_CprPyth_al_160_wiISR->SetMarkerColor(kBlack); hist_CprPyth_al_160_wiISR->SetMarkerStyle(3); hist_CprPyth_al_160_wiISR->SetLineWidth(2); hist_CprPyth_al_160_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_160_wiISR->SetLineColor(kYellow+2); hist_CprPyth_Zq_160_wiISR->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_160_wiISR->SetMarkerStyle(3); hist_CprPyth_Zq_160_wiISR->SetLineWidth(2); hist_CprPyth_Zq_160_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_160_wiISR->SetLineColor(kGreen+2); hist_CprPyth_WW_160_wiISR->SetMarkerColor(kGreen+2); hist_CprPyth_WW_160_wiISR->SetMarkerStyle(3); hist_CprPyth_WW_160_wiISR->SetLineWidth(2); hist_CprPyth_WW_160_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_160_wiISR->SetLineColor(kBlue+2); hist_CprPyth_ZZ_160_wiISR->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_160_wiISR->SetMarkerStyle(3); hist_CprPyth_ZZ_160_wiISR->SetLineWidth(2); hist_CprPyth_ZZ_160_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_160_wiISR->SetLineColor(kRed+2); hist_CprPyth_tt_160_wiISR->SetMarkerColor(kRed+2); hist_CprPyth_tt_160_wiISR->SetMarkerStyle(3); hist_CprPyth_tt_160_wiISR->SetLineWidth(2); hist_CprPyth_tt_160_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_160_wiISR->SetLineColor(kBlue+2); hist_CprPyth_HZ_160_wiISR->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_160_wiISR->SetMarkerStyle(53); hist_CprPyth_HZ_160_wiISR->SetLineWidth(2); hist_CprPyth_HZ_160_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_hW_160_wiISR = (TH1F*)input_160_wiISR->Get("hist_CprPyth_hW");
	hist_CprPyth_hW_160_wiISR->SetLineColor(kRed+2); hist_CprPyth_hW_160_wiISR->SetMarkerColor(kRed+2); hist_CprPyth_hW_160_wiISR->SetMarkerStyle(53); hist_CprPyth_hW_160_wiISR->SetLineWidth(2); hist_CprPyth_hW_160_wiISR->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_CprPyth");
	hist_CprPyth_al_240_wiISR->SetLineColor(kBlack); hist_CprPyth_al_240_wiISR->SetMarkerColor(kBlack); hist_CprPyth_al_240_wiISR->SetMarkerStyle(3); hist_CprPyth_al_240_wiISR->SetLineWidth(2); hist_CprPyth_al_240_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_240_wiISR->SetLineColor(kYellow+2); hist_CprPyth_Zq_240_wiISR->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_240_wiISR->SetMarkerStyle(3); hist_CprPyth_Zq_240_wiISR->SetLineWidth(2); hist_CprPyth_Zq_240_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_240_wiISR->SetLineColor(kGreen+2); hist_CprPyth_WW_240_wiISR->SetMarkerColor(kGreen+2); hist_CprPyth_WW_240_wiISR->SetMarkerStyle(3); hist_CprPyth_WW_240_wiISR->SetLineWidth(2); hist_CprPyth_WW_240_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_240_wiISR->SetLineColor(kBlue+2); hist_CprPyth_ZZ_240_wiISR->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_240_wiISR->SetMarkerStyle(3); hist_CprPyth_ZZ_240_wiISR->SetLineWidth(2); hist_CprPyth_ZZ_240_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_240_wiISR->SetLineColor(kRed+2); hist_CprPyth_tt_240_wiISR->SetMarkerColor(kRed+2); hist_CprPyth_tt_240_wiISR->SetMarkerStyle(3); hist_CprPyth_tt_240_wiISR->SetLineWidth(2); hist_CprPyth_tt_240_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_240_wiISR->SetLineColor(kBlue+2); hist_CprPyth_HZ_240_wiISR->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_240_wiISR->SetMarkerStyle(53); hist_CprPyth_HZ_240_wiISR->SetLineWidth(2); hist_CprPyth_HZ_240_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_hW_240_wiISR = (TH1F*)input_240_wiISR->Get("hist_CprPyth_hW");
	hist_CprPyth_hW_240_wiISR->SetLineColor(kRed+2); hist_CprPyth_hW_240_wiISR->SetMarkerColor(kRed+2); hist_CprPyth_hW_240_wiISR->SetMarkerStyle(53); hist_CprPyth_hW_240_wiISR->SetLineWidth(2); hist_CprPyth_hW_240_wiISR->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_CprPyth");
	hist_CprPyth_al_365_wiISR->SetLineColor(kBlack); hist_CprPyth_al_365_wiISR->SetMarkerColor(kBlack); hist_CprPyth_al_365_wiISR->SetMarkerStyle(3); hist_CprPyth_al_365_wiISR->SetLineWidth(2); hist_CprPyth_al_365_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_365_wiISR->SetLineColor(kYellow+2); hist_CprPyth_Zq_365_wiISR->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_365_wiISR->SetMarkerStyle(3); hist_CprPyth_Zq_365_wiISR->SetLineWidth(2); hist_CprPyth_Zq_365_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_365_wiISR->SetLineColor(kGreen+2); hist_CprPyth_WW_365_wiISR->SetMarkerColor(kGreen+2); hist_CprPyth_WW_365_wiISR->SetMarkerStyle(3); hist_CprPyth_WW_365_wiISR->SetLineWidth(2); hist_CprPyth_WW_365_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_365_wiISR->SetLineColor(kBlue+2); hist_CprPyth_ZZ_365_wiISR->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_365_wiISR->SetMarkerStyle(3); hist_CprPyth_ZZ_365_wiISR->SetLineWidth(2); hist_CprPyth_ZZ_365_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_365_wiISR->SetLineColor(kRed+2); hist_CprPyth_tt_365_wiISR->SetMarkerColor(kRed+2); hist_CprPyth_tt_365_wiISR->SetMarkerStyle(3); hist_CprPyth_tt_365_wiISR->SetLineWidth(2); hist_CprPyth_tt_365_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_365_wiISR->SetLineColor(kBlue+2); hist_CprPyth_HZ_365_wiISR->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_365_wiISR->SetMarkerStyle(53); hist_CprPyth_HZ_365_wiISR->SetLineStyle(2); hist_CprPyth_HZ_365_wiISR->SetLineWidth(2); hist_CprPyth_HZ_365_wiISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_hW_365_wiISR = (TH1F*)input_365_wiISR->Get("hist_CprPyth_hW");
	hist_CprPyth_hW_365_wiISR->SetLineColor(kRed+2); hist_CprPyth_hW_365_wiISR->SetMarkerColor(kRed+2); hist_CprPyth_hW_365_wiISR->SetMarkerStyle(53); hist_CprPyth_hW_365_wiISR->SetLineStyle(2); hist_CprPyth_hW_365_wiISR->SetLineWidth(2); hist_CprPyth_hW_365_wiISR->SetMarkerSize(1);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F* hist_ThrPyth_al_912_woISR = (TH1F*)input_912_woISR->Get("hist_ThrPyth");
	hist_ThrPyth_al_912_woISR->SetLineColor(kBlack); hist_ThrPyth_al_912_woISR->SetMarkerColor(kBlack); hist_ThrPyth_al_912_woISR->SetMarkerStyle(3); hist_ThrPyth_al_912_woISR->SetLineWidth(2); hist_ThrPyth_al_912_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_912_woISR = (TH1F*)input_912_woISR->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_912_woISR->SetLineColor(kYellow+2); hist_ThrPyth_Zq_912_woISR->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_912_woISR->SetMarkerStyle(3); hist_ThrPyth_Zq_912_woISR->SetLineWidth(2); hist_ThrPyth_Zq_912_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_912_woISR = (TH1F*)input_912_woISR->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_912_woISR->SetLineColor(kGreen+2); hist_ThrPyth_WW_912_woISR->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_912_woISR->SetMarkerStyle(3); hist_ThrPyth_WW_912_woISR->SetLineWidth(2); hist_ThrPyth_WW_912_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_912_woISR = (TH1F*)input_912_woISR->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_912_woISR->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_912_woISR->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_912_woISR->SetMarkerStyle(3); hist_ThrPyth_ZZ_912_woISR->SetLineWidth(2); hist_ThrPyth_ZZ_912_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_912_woISR = (TH1F*)input_912_woISR->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_912_woISR->SetLineColor(kRed+2); hist_ThrPyth_tt_912_woISR->SetMarkerColor(kRed+2); hist_ThrPyth_tt_912_woISR->SetMarkerStyle(3); hist_ThrPyth_tt_912_woISR->SetLineWidth(2); hist_ThrPyth_tt_912_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_912_woISR = (TH1F*)input_912_woISR->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_912_woISR->SetLineColor(kBlue+2); hist_ThrPyth_HZ_912_woISR->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_912_woISR->SetMarkerStyle(53); hist_ThrPyth_HZ_912_woISR->SetLineWidth(2); hist_ThrPyth_HZ_912_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_hW_912_woISR = (TH1F*)input_912_woISR->Get("hist_ThrPyth_hW");
	hist_ThrPyth_hW_912_woISR->SetLineColor(kRed+2); hist_ThrPyth_hW_912_woISR->SetMarkerColor(kRed+2); hist_ThrPyth_hW_912_woISR->SetMarkerStyle(53); hist_ThrPyth_hW_912_woISR->SetLineWidth(2); hist_ThrPyth_hW_912_woISR->SetMarkerSize(1);

	TH1F* hist_ThrPyth_al_160_woISR = (TH1F*)input_160_woISR->Get("hist_ThrPyth");
	hist_ThrPyth_al_160_woISR->SetLineColor(kBlack); hist_ThrPyth_al_160_woISR->SetMarkerColor(kBlack); hist_ThrPyth_al_160_woISR->SetMarkerStyle(3); hist_ThrPyth_al_160_woISR->SetLineWidth(2); hist_ThrPyth_al_160_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_160_woISR = (TH1F*)input_160_woISR->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_160_woISR->SetLineColor(kYellow+2); hist_ThrPyth_Zq_160_woISR->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_160_woISR->SetMarkerStyle(3); hist_ThrPyth_Zq_160_woISR->SetLineWidth(2); hist_ThrPyth_Zq_160_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_160_woISR = (TH1F*)input_160_woISR->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_160_woISR->SetLineColor(kGreen+2); hist_ThrPyth_WW_160_woISR->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_160_woISR->SetMarkerStyle(3); hist_ThrPyth_WW_160_woISR->SetLineWidth(2); hist_ThrPyth_WW_160_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_160_woISR = (TH1F*)input_160_woISR->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_160_woISR->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_160_woISR->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_160_woISR->SetMarkerStyle(3); hist_ThrPyth_ZZ_160_woISR->SetLineWidth(2); hist_ThrPyth_ZZ_160_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_160_woISR = (TH1F*)input_160_woISR->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_160_woISR->SetLineColor(kRed+2); hist_ThrPyth_tt_160_woISR->SetMarkerColor(kRed+2); hist_ThrPyth_tt_160_woISR->SetMarkerStyle(3); hist_ThrPyth_tt_160_woISR->SetLineWidth(2); hist_ThrPyth_tt_160_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_160_woISR = (TH1F*)input_160_woISR->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_160_woISR->SetLineColor(kBlue+2); hist_ThrPyth_HZ_160_woISR->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_160_woISR->SetMarkerStyle(53); hist_ThrPyth_HZ_160_woISR->SetLineWidth(2); hist_ThrPyth_HZ_160_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_hW_160_woISR = (TH1F*)input_160_woISR->Get("hist_ThrPyth_hW");
	hist_ThrPyth_hW_160_woISR->SetLineColor(kRed+2); hist_ThrPyth_hW_160_woISR->SetMarkerColor(kRed+2); hist_ThrPyth_hW_160_woISR->SetMarkerStyle(53); hist_ThrPyth_hW_160_woISR->SetLineWidth(2); hist_ThrPyth_hW_160_woISR->SetMarkerSize(1);

	TH1F* hist_ThrPyth_al_240_woISR = (TH1F*)input_240_woISR->Get("hist_ThrPyth");
	hist_ThrPyth_al_240_woISR->SetLineColor(kBlack); hist_ThrPyth_al_240_woISR->SetMarkerColor(kBlack); hist_ThrPyth_al_240_woISR->SetMarkerStyle(3); hist_ThrPyth_al_240_woISR->SetLineWidth(2); hist_ThrPyth_al_240_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_240_woISR = (TH1F*)input_240_woISR->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_240_woISR->SetLineColor(kYellow+2); hist_ThrPyth_Zq_240_woISR->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_240_woISR->SetMarkerStyle(3); hist_ThrPyth_Zq_240_woISR->SetLineWidth(2); hist_ThrPyth_Zq_240_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_240_woISR = (TH1F*)input_240_woISR->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_240_woISR->SetLineColor(kGreen+2); hist_ThrPyth_WW_240_woISR->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_240_woISR->SetMarkerStyle(3); hist_ThrPyth_WW_240_woISR->SetLineWidth(2); hist_ThrPyth_WW_240_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_240_woISR = (TH1F*)input_240_woISR->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_240_woISR->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_240_woISR->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_240_woISR->SetMarkerStyle(3); hist_ThrPyth_ZZ_240_woISR->SetLineWidth(2); hist_ThrPyth_ZZ_240_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_240_woISR = (TH1F*)input_240_woISR->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_240_woISR->SetLineColor(kRed+2); hist_ThrPyth_tt_240_woISR->SetMarkerColor(kRed+2); hist_ThrPyth_tt_240_woISR->SetMarkerStyle(3); hist_ThrPyth_tt_240_woISR->SetLineWidth(2); hist_ThrPyth_tt_240_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_240_woISR = (TH1F*)input_240_woISR->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_240_woISR->SetLineColor(kBlue+2); hist_ThrPyth_HZ_240_woISR->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_240_woISR->SetMarkerStyle(53); hist_ThrPyth_HZ_240_woISR->SetLineWidth(2); hist_ThrPyth_HZ_240_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_hW_240_woISR = (TH1F*)input_240_woISR->Get("hist_ThrPyth_hW");
	hist_ThrPyth_hW_240_woISR->SetLineColor(kRed+2); hist_ThrPyth_hW_240_woISR->SetMarkerColor(kRed+2); hist_ThrPyth_hW_240_woISR->SetMarkerStyle(53); hist_ThrPyth_hW_240_woISR->SetLineWidth(2); hist_ThrPyth_hW_240_woISR->SetMarkerSize(1);

	TH1F* hist_ThrPyth_al_365_woISR = (TH1F*)input_365_woISR->Get("hist_ThrPyth");
	hist_ThrPyth_al_365_woISR->SetLineColor(kBlack); hist_ThrPyth_al_365_woISR->SetMarkerColor(kBlack); hist_ThrPyth_al_365_woISR->SetMarkerStyle(3); hist_ThrPyth_al_365_woISR->SetLineWidth(2); hist_ThrPyth_al_365_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_Zq_365_woISR = (TH1F*)input_365_woISR->Get("hist_ThrPyth_Zq");
	hist_ThrPyth_Zq_365_woISR->SetLineColor(kYellow+2); hist_ThrPyth_Zq_365_woISR->SetMarkerColor(kYellow+2); hist_ThrPyth_Zq_365_woISR->SetMarkerStyle(3); hist_ThrPyth_Zq_365_woISR->SetLineWidth(2); hist_ThrPyth_Zq_365_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_WW_365_woISR = (TH1F*)input_365_woISR->Get("hist_ThrPyth_WW");
	hist_ThrPyth_WW_365_woISR->SetLineColor(kGreen+2); hist_ThrPyth_WW_365_woISR->SetMarkerColor(kGreen+2); hist_ThrPyth_WW_365_woISR->SetMarkerStyle(3); hist_ThrPyth_WW_365_woISR->SetLineWidth(2); hist_ThrPyth_WW_365_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_ZZ_365_woISR = (TH1F*)input_365_woISR->Get("hist_ThrPyth_ZZ");
	hist_ThrPyth_ZZ_365_woISR->SetLineColor(kBlue+2); hist_ThrPyth_ZZ_365_woISR->SetMarkerColor(kBlue+2); hist_ThrPyth_ZZ_365_woISR->SetMarkerStyle(3); hist_ThrPyth_ZZ_365_woISR->SetLineWidth(2); hist_ThrPyth_ZZ_365_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_tt_365_woISR = (TH1F*)input_365_woISR->Get("hist_ThrPyth_tt");
	hist_ThrPyth_tt_365_woISR->SetLineColor(kRed+2); hist_ThrPyth_tt_365_woISR->SetMarkerColor(kRed+2); hist_ThrPyth_tt_365_woISR->SetMarkerStyle(3); hist_ThrPyth_tt_365_woISR->SetLineWidth(2); hist_ThrPyth_tt_365_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_HZ_365_woISR = (TH1F*)input_365_woISR->Get("hist_ThrPyth_HZ");
	hist_ThrPyth_HZ_365_woISR->SetLineColor(kBlue+2); hist_ThrPyth_HZ_365_woISR->SetMarkerColor(kBlue+2); hist_ThrPyth_HZ_365_woISR->SetMarkerStyle(53); hist_ThrPyth_HZ_365_woISR->SetLineStyle(2); hist_ThrPyth_HZ_365_woISR->SetLineWidth(2); hist_ThrPyth_HZ_365_woISR->SetMarkerSize(1);
	TH1F* hist_ThrPyth_hW_365_woISR = (TH1F*)input_365_woISR->Get("hist_ThrPyth_hW");
	hist_ThrPyth_hW_365_woISR->SetLineColor(kRed+2); hist_ThrPyth_hW_365_woISR->SetMarkerColor(kRed+2); hist_ThrPyth_hW_365_woISR->SetMarkerStyle(53); hist_ThrPyth_hW_365_woISR->SetLineStyle(2); hist_ThrPyth_hW_365_woISR->SetLineWidth(2); hist_ThrPyth_hW_365_woISR->SetMarkerSize(1);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F* hist_CprPyth_al_912_woISR = (TH1F*)input_912_woISR->Get("hist_CprPyth");
	hist_CprPyth_al_912_woISR->SetLineColor(kBlack); hist_CprPyth_al_912_woISR->SetMarkerColor(kBlack); hist_CprPyth_al_912_woISR->SetMarkerStyle(3); hist_CprPyth_al_912_woISR->SetLineWidth(2); hist_CprPyth_al_912_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_912_woISR = (TH1F*)input_912_woISR->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_912_woISR->SetLineColor(kYellow+2); hist_CprPyth_Zq_912_woISR->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_912_woISR->SetMarkerStyle(3); hist_CprPyth_Zq_912_woISR->SetLineWidth(2); hist_CprPyth_Zq_912_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_912_woISR = (TH1F*)input_912_woISR->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_912_woISR->SetLineColor(kGreen+2); hist_CprPyth_WW_912_woISR->SetMarkerColor(kGreen+2); hist_CprPyth_WW_912_woISR->SetMarkerStyle(3); hist_CprPyth_WW_912_woISR->SetLineWidth(2); hist_CprPyth_WW_912_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_912_woISR = (TH1F*)input_912_woISR->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_912_woISR->SetLineColor(kBlue+2); hist_CprPyth_ZZ_912_woISR->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_912_woISR->SetMarkerStyle(3); hist_CprPyth_ZZ_912_woISR->SetLineWidth(2); hist_CprPyth_ZZ_912_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_912_woISR = (TH1F*)input_912_woISR->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_912_woISR->SetLineColor(kRed+2); hist_CprPyth_tt_912_woISR->SetMarkerColor(kRed+2); hist_CprPyth_tt_912_woISR->SetMarkerStyle(3); hist_CprPyth_tt_912_woISR->SetLineWidth(2); hist_CprPyth_tt_912_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_912_woISR = (TH1F*)input_912_woISR->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_912_woISR->SetLineColor(kBlue+2); hist_CprPyth_HZ_912_woISR->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_912_woISR->SetMarkerStyle(53); hist_CprPyth_HZ_912_woISR->SetLineWidth(2); hist_CprPyth_HZ_912_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_hW_912_woISR = (TH1F*)input_912_woISR->Get("hist_CprPyth_hW");
	hist_CprPyth_hW_912_woISR->SetLineColor(kRed+2); hist_CprPyth_hW_912_woISR->SetMarkerColor(kRed+2); hist_CprPyth_hW_912_woISR->SetMarkerStyle(53); hist_CprPyth_hW_912_woISR->SetLineWidth(2); hist_CprPyth_hW_912_woISR->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_160_woISR = (TH1F*)input_160_woISR->Get("hist_CprPyth");
	hist_CprPyth_al_160_woISR->SetLineColor(kBlack); hist_CprPyth_al_160_woISR->SetMarkerColor(kBlack); hist_CprPyth_al_160_woISR->SetMarkerStyle(3); hist_CprPyth_al_160_woISR->SetLineWidth(2); hist_CprPyth_al_160_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_160_woISR = (TH1F*)input_160_woISR->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_160_woISR->SetLineColor(kYellow+2); hist_CprPyth_Zq_160_woISR->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_160_woISR->SetMarkerStyle(3); hist_CprPyth_Zq_160_woISR->SetLineWidth(2); hist_CprPyth_Zq_160_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_160_woISR = (TH1F*)input_160_woISR->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_160_woISR->SetLineColor(kGreen+2); hist_CprPyth_WW_160_woISR->SetMarkerColor(kGreen+2); hist_CprPyth_WW_160_woISR->SetMarkerStyle(3); hist_CprPyth_WW_160_woISR->SetLineWidth(2); hist_CprPyth_WW_160_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_160_woISR = (TH1F*)input_160_woISR->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_160_woISR->SetLineColor(kBlue+2); hist_CprPyth_ZZ_160_woISR->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_160_woISR->SetMarkerStyle(3); hist_CprPyth_ZZ_160_woISR->SetLineWidth(2); hist_CprPyth_ZZ_160_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_160_woISR = (TH1F*)input_160_woISR->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_160_woISR->SetLineColor(kRed+2); hist_CprPyth_tt_160_woISR->SetMarkerColor(kRed+2); hist_CprPyth_tt_160_woISR->SetMarkerStyle(3); hist_CprPyth_tt_160_woISR->SetLineWidth(2); hist_CprPyth_tt_160_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_160_woISR = (TH1F*)input_160_woISR->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_160_woISR->SetLineColor(kBlue+2); hist_CprPyth_HZ_160_woISR->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_160_woISR->SetMarkerStyle(53); hist_CprPyth_HZ_160_woISR->SetLineWidth(2); hist_CprPyth_HZ_160_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_hW_160_woISR = (TH1F*)input_160_woISR->Get("hist_CprPyth_hW");
	hist_CprPyth_hW_160_woISR->SetLineColor(kRed+2); hist_CprPyth_hW_160_woISR->SetMarkerColor(kRed+2); hist_CprPyth_hW_160_woISR->SetMarkerStyle(53); hist_CprPyth_hW_160_woISR->SetLineWidth(2); hist_CprPyth_hW_160_woISR->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_240_woISR = (TH1F*)input_240_woISR->Get("hist_CprPyth");
	hist_CprPyth_al_240_woISR->SetLineColor(kBlack); hist_CprPyth_al_240_woISR->SetMarkerColor(kBlack); hist_CprPyth_al_240_woISR->SetMarkerStyle(3); hist_CprPyth_al_240_woISR->SetLineWidth(2); hist_CprPyth_al_240_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_240_woISR = (TH1F*)input_240_woISR->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_240_woISR->SetLineColor(kYellow+2); hist_CprPyth_Zq_240_woISR->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_240_woISR->SetMarkerStyle(3); hist_CprPyth_Zq_240_woISR->SetLineWidth(2); hist_CprPyth_Zq_240_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_240_woISR = (TH1F*)input_240_woISR->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_240_woISR->SetLineColor(kGreen+2); hist_CprPyth_WW_240_woISR->SetMarkerColor(kGreen+2); hist_CprPyth_WW_240_woISR->SetMarkerStyle(3); hist_CprPyth_WW_240_woISR->SetLineWidth(2); hist_CprPyth_WW_240_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_240_woISR = (TH1F*)input_240_woISR->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_240_woISR->SetLineColor(kBlue+2); hist_CprPyth_ZZ_240_woISR->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_240_woISR->SetMarkerStyle(3); hist_CprPyth_ZZ_240_woISR->SetLineWidth(2); hist_CprPyth_ZZ_240_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_240_woISR = (TH1F*)input_240_woISR->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_240_woISR->SetLineColor(kRed+2); hist_CprPyth_tt_240_woISR->SetMarkerColor(kRed+2); hist_CprPyth_tt_240_woISR->SetMarkerStyle(3); hist_CprPyth_tt_240_woISR->SetLineWidth(2); hist_CprPyth_tt_240_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_240_woISR = (TH1F*)input_240_woISR->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_240_woISR->SetLineColor(kBlue+2); hist_CprPyth_HZ_240_woISR->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_240_woISR->SetMarkerStyle(53); hist_CprPyth_HZ_240_woISR->SetLineWidth(2); hist_CprPyth_HZ_240_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_hW_240_woISR = (TH1F*)input_240_woISR->Get("hist_CprPyth_hW");
	hist_CprPyth_hW_240_woISR->SetLineColor(kRed+2); hist_CprPyth_hW_240_woISR->SetMarkerColor(kRed+2); hist_CprPyth_hW_240_woISR->SetMarkerStyle(53); hist_CprPyth_hW_240_woISR->SetLineWidth(2); hist_CprPyth_hW_240_woISR->SetMarkerSize(1);

	TH1F* hist_CprPyth_al_365_woISR = (TH1F*)input_365_woISR->Get("hist_CprPyth");
	hist_CprPyth_al_365_woISR->SetLineColor(kBlack); hist_CprPyth_al_365_woISR->SetMarkerColor(kBlack); hist_CprPyth_al_365_woISR->SetMarkerStyle(3); hist_CprPyth_al_365_woISR->SetLineWidth(2); hist_CprPyth_al_365_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_Zq_365_woISR = (TH1F*)input_365_woISR->Get("hist_CprPyth_Zq");
	hist_CprPyth_Zq_365_woISR->SetLineColor(kYellow+2); hist_CprPyth_Zq_365_woISR->SetMarkerColor(kYellow+2); hist_CprPyth_Zq_365_woISR->SetMarkerStyle(3); hist_CprPyth_Zq_365_woISR->SetLineWidth(2); hist_CprPyth_Zq_365_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_WW_365_woISR = (TH1F*)input_365_woISR->Get("hist_CprPyth_WW");
	hist_CprPyth_WW_365_woISR->SetLineColor(kGreen+2); hist_CprPyth_WW_365_woISR->SetMarkerColor(kGreen+2); hist_CprPyth_WW_365_woISR->SetMarkerStyle(3); hist_CprPyth_WW_365_woISR->SetLineWidth(2); hist_CprPyth_WW_365_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_ZZ_365_woISR = (TH1F*)input_365_woISR->Get("hist_CprPyth_ZZ");
	hist_CprPyth_ZZ_365_woISR->SetLineColor(kBlue+2); hist_CprPyth_ZZ_365_woISR->SetMarkerColor(kBlue+2); hist_CprPyth_ZZ_365_woISR->SetMarkerStyle(3); hist_CprPyth_ZZ_365_woISR->SetLineWidth(2); hist_CprPyth_ZZ_365_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_tt_365_woISR = (TH1F*)input_365_woISR->Get("hist_CprPyth_tt");
	hist_CprPyth_tt_365_woISR->SetLineColor(kRed+2); hist_CprPyth_tt_365_woISR->SetMarkerColor(kRed+2); hist_CprPyth_tt_365_woISR->SetMarkerStyle(3); hist_CprPyth_tt_365_woISR->SetLineWidth(2); hist_CprPyth_tt_365_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_HZ_365_woISR = (TH1F*)input_365_woISR->Get("hist_CprPyth_HZ");
	hist_CprPyth_HZ_365_woISR->SetLineColor(kBlue+2); hist_CprPyth_HZ_365_woISR->SetMarkerColor(kBlue+2); hist_CprPyth_HZ_365_woISR->SetMarkerStyle(53); hist_CprPyth_HZ_365_woISR->SetLineStyle(2); hist_CprPyth_HZ_365_woISR->SetLineWidth(2); hist_CprPyth_HZ_365_woISR->SetMarkerSize(1);
	TH1F* hist_CprPyth_hW_365_woISR = (TH1F*)input_365_woISR->Get("hist_CprPyth_hW");
	hist_CprPyth_hW_365_woISR->SetLineColor(kRed+2); hist_CprPyth_hW_365_woISR->SetMarkerColor(kRed+2); hist_CprPyth_hW_365_woISR->SetMarkerStyle(53); hist_CprPyth_hW_365_woISR->SetLineStyle(2); hist_CprPyth_hW_365_woISR->SetLineWidth(2); hist_CprPyth_hW_365_woISR->SetMarkerSize(1);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_912_000 = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_000");
	hist_ThrPyth_912_000->SetLineColor(kRed+2); hist_ThrPyth_912_000->SetMarkerColor(kRed+2); hist_ThrPyth_912_000->SetMarkerStyle(kStar); hist_ThrPyth_912_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_912_085 = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_085");
	hist_ThrPyth_912_085->SetLineColor(kGreen+2); hist_ThrPyth_912_085->SetMarkerColor(kGreen+2); hist_ThrPyth_912_085->SetMarkerStyle(kStar); hist_ThrPyth_912_085->SetLineWidth(2); 
	TH1F *hist_ThrPyth_912_095 = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_095");
	hist_ThrPyth_912_095->SetLineColor(kYellow+2); hist_ThrPyth_912_095->SetMarkerColor(kYellow+2); hist_ThrPyth_912_095->SetMarkerStyle(kStar); hist_ThrPyth_912_095->SetLineWidth(2); 
	TH1F *hist_ThrPyth_912_100 = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_100");
	hist_ThrPyth_912_100->SetLineColor(kBlue+2); hist_ThrPyth_912_100->SetMarkerColor(kBlue+2); hist_ThrPyth_912_100->SetMarkerStyle(kStar); hist_ThrPyth_912_100->SetLineWidth(2); 

	TH1F *hist_ThrPyth_160_000 = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_000");
	hist_ThrPyth_160_000->SetLineColor(kRed+2); hist_ThrPyth_160_000->SetMarkerColor(kRed+2); hist_ThrPyth_160_000->SetMarkerStyle(kStar); hist_ThrPyth_160_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_160_085 = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_085");
	hist_ThrPyth_160_085->SetLineColor(kGreen+2); hist_ThrPyth_160_085->SetMarkerColor(kGreen+2); hist_ThrPyth_160_085->SetMarkerStyle(kStar); hist_ThrPyth_160_085->SetLineWidth(2); 
	TH1F *hist_ThrPyth_160_095 = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_095");
	hist_ThrPyth_160_095->SetLineColor(kYellow+2); hist_ThrPyth_160_095->SetMarkerColor(kYellow+2); hist_ThrPyth_160_095->SetMarkerStyle(kStar); hist_ThrPyth_160_095->SetLineWidth(2); 
	TH1F *hist_ThrPyth_160_100 = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_100");
	hist_ThrPyth_160_100->SetLineColor(kBlue+2); hist_ThrPyth_160_100->SetMarkerColor(kBlue+2); hist_ThrPyth_160_100->SetMarkerStyle(kStar); hist_ThrPyth_160_100->SetLineWidth(2); 

	TH1F *hist_ThrPyth_240_000 = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_000");
	hist_ThrPyth_240_000->SetLineColor(kRed+2); hist_ThrPyth_240_000->SetMarkerColor(kRed+2); hist_ThrPyth_240_000->SetMarkerStyle(kStar); hist_ThrPyth_240_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_240_085 = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_085");
	hist_ThrPyth_240_085->SetLineColor(kGreen+2); hist_ThrPyth_240_085->SetMarkerColor(kGreen+2); hist_ThrPyth_240_085->SetMarkerStyle(kStar); hist_ThrPyth_240_085->SetLineWidth(2); 
	TH1F *hist_ThrPyth_240_095 = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_095");
	hist_ThrPyth_240_095->SetLineColor(kYellow+2); hist_ThrPyth_240_095->SetMarkerColor(kYellow+2); hist_ThrPyth_240_095->SetMarkerStyle(kStar); hist_ThrPyth_240_095->SetLineWidth(2); 
	TH1F *hist_ThrPyth_240_100 = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_100");
	hist_ThrPyth_240_100->SetLineColor(kBlue+2); hist_ThrPyth_240_100->SetMarkerColor(kBlue+2); hist_ThrPyth_240_100->SetMarkerStyle(kStar); hist_ThrPyth_240_100->SetLineWidth(2); 

	TH1F *hist_ThrPyth_365_000 = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_000");
	hist_ThrPyth_365_000->SetLineColor(kRed+2); hist_ThrPyth_365_000->SetMarkerColor(kRed+2); hist_ThrPyth_365_000->SetMarkerStyle(kStar); hist_ThrPyth_365_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_365_085 = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_085");
	hist_ThrPyth_365_085->SetLineColor(kGreen+2); hist_ThrPyth_365_085->SetMarkerColor(kGreen+2); hist_ThrPyth_365_085->SetMarkerStyle(kStar); hist_ThrPyth_365_085->SetLineWidth(2); 
	TH1F *hist_ThrPyth_365_095 = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_095");
	hist_ThrPyth_365_095->SetLineColor(kYellow+2); hist_ThrPyth_365_095->SetMarkerColor(kYellow+2); hist_ThrPyth_365_095->SetMarkerStyle(kStar); hist_ThrPyth_365_095->SetLineWidth(2); 
	TH1F *hist_ThrPyth_365_100 = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_100");
	hist_ThrPyth_365_100->SetLineColor(kBlue+2); hist_ThrPyth_365_100->SetMarkerColor(kBlue+2); hist_ThrPyth_365_100->SetMarkerStyle(kStar); hist_ThrPyth_365_100->SetLineWidth(2); 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_CprPyth_912_000 = (TH1F*)input_912_wiISR->Get("hist_CprPyth_000");
	hist_CprPyth_912_000->SetLineColor(kRed+2); hist_CprPyth_912_000->SetMarkerColor(kRed+2); hist_CprPyth_912_000->SetMarkerStyle(kStar); hist_CprPyth_912_000->SetLineWidth(2); 
	TH1F *hist_CprPyth_912_085 = (TH1F*)input_912_wiISR->Get("hist_CprPyth_085");
	hist_CprPyth_912_085->SetLineColor(kGreen+2); hist_CprPyth_912_085->SetMarkerColor(kGreen+2); hist_CprPyth_912_085->SetMarkerStyle(kStar); hist_CprPyth_912_085->SetLineWidth(2); 
	TH1F *hist_CprPyth_912_095 = (TH1F*)input_912_wiISR->Get("hist_CprPyth_095");
	hist_CprPyth_912_095->SetLineColor(kYellow+2); hist_CprPyth_912_095->SetMarkerColor(kYellow+2); hist_CprPyth_912_095->SetMarkerStyle(kStar); hist_CprPyth_912_095->SetLineWidth(2); 
	TH1F *hist_CprPyth_912_100 = (TH1F*)input_912_wiISR->Get("hist_CprPyth_100");
	hist_CprPyth_912_100->SetLineColor(kBlue+2); hist_CprPyth_912_100->SetMarkerColor(kBlue+2); hist_CprPyth_912_100->SetMarkerStyle(kStar); hist_CprPyth_912_100->SetLineWidth(2); 

	TH1F *hist_CprPyth_160_000 = (TH1F*)input_160_wiISR->Get("hist_CprPyth_000");
	hist_CprPyth_160_000->SetLineColor(kRed+2); hist_CprPyth_160_000->SetMarkerColor(kRed+2); hist_CprPyth_160_000->SetMarkerStyle(kStar); hist_CprPyth_160_000->SetLineWidth(2); 
	TH1F *hist_CprPyth_160_085 = (TH1F*)input_160_wiISR->Get("hist_CprPyth_085");
	hist_CprPyth_160_085->SetLineColor(kGreen+2); hist_CprPyth_160_085->SetMarkerColor(kGreen+2); hist_CprPyth_160_085->SetMarkerStyle(kStar); hist_CprPyth_160_085->SetLineWidth(2); 
	TH1F *hist_CprPyth_160_095 = (TH1F*)input_160_wiISR->Get("hist_CprPyth_095");
	hist_CprPyth_160_095->SetLineColor(kYellow+2); hist_CprPyth_160_095->SetMarkerColor(kYellow+2); hist_CprPyth_160_095->SetMarkerStyle(kStar); hist_CprPyth_160_095->SetLineWidth(2); 
	TH1F *hist_CprPyth_160_100 = (TH1F*)input_160_wiISR->Get("hist_CprPyth_100");
	hist_CprPyth_160_100->SetLineColor(kBlue+2); hist_CprPyth_160_100->SetMarkerColor(kBlue+2); hist_CprPyth_160_100->SetMarkerStyle(kStar); hist_CprPyth_160_100->SetLineWidth(2); 

	TH1F *hist_CprPyth_240_000 = (TH1F*)input_240_wiISR->Get("hist_CprPyth_000");
	hist_CprPyth_240_000->SetLineColor(kRed+2); hist_CprPyth_240_000->SetMarkerColor(kRed+2); hist_CprPyth_240_000->SetMarkerStyle(kStar); hist_CprPyth_240_000->SetLineWidth(2); 
	TH1F *hist_CprPyth_240_085 = (TH1F*)input_240_wiISR->Get("hist_CprPyth_085");
	hist_CprPyth_240_085->SetLineColor(kGreen+2); hist_CprPyth_240_085->SetMarkerColor(kGreen+2); hist_CprPyth_240_085->SetMarkerStyle(kStar); hist_CprPyth_240_085->SetLineWidth(2); 
	TH1F *hist_CprPyth_240_095 = (TH1F*)input_240_wiISR->Get("hist_CprPyth_095");
	hist_CprPyth_240_095->SetLineColor(kYellow+2); hist_CprPyth_240_095->SetMarkerColor(kYellow+2); hist_CprPyth_240_095->SetMarkerStyle(kStar); hist_CprPyth_240_095->SetLineWidth(2); 
	TH1F *hist_CprPyth_240_100 = (TH1F*)input_240_wiISR->Get("hist_CprPyth_100");
	hist_CprPyth_240_100->SetLineColor(kBlue+2); hist_CprPyth_240_100->SetMarkerColor(kBlue+2); hist_CprPyth_240_100->SetMarkerStyle(kStar); hist_CprPyth_240_100->SetLineWidth(2); 

	TH1F *hist_CprPyth_365_000 = (TH1F*)input_365_wiISR->Get("hist_CprPyth_000");
	hist_CprPyth_365_000->SetLineColor(kRed+2); hist_CprPyth_365_000->SetMarkerColor(kRed+2); hist_CprPyth_365_000->SetMarkerStyle(kStar); hist_CprPyth_365_000->SetLineWidth(2); 
	TH1F *hist_CprPyth_365_085 = (TH1F*)input_365_wiISR->Get("hist_CprPyth_085");
	hist_CprPyth_365_085->SetLineColor(kGreen+2); hist_CprPyth_365_085->SetMarkerColor(kGreen+2); hist_CprPyth_365_085->SetMarkerStyle(kStar); hist_CprPyth_365_085->SetLineWidth(2); 
	TH1F *hist_CprPyth_365_095 = (TH1F*)input_365_wiISR->Get("hist_CprPyth_095");
	hist_CprPyth_365_095->SetLineColor(kYellow+2); hist_CprPyth_365_095->SetMarkerColor(kYellow+2); hist_CprPyth_365_095->SetMarkerStyle(kStar); hist_CprPyth_365_095->SetLineWidth(2); 
	TH1F *hist_CprPyth_365_100 = (TH1F*)input_365_wiISR->Get("hist_CprPyth_100");
	hist_CprPyth_365_100->SetLineColor(kBlue+2); hist_CprPyth_365_100->SetMarkerColor(kBlue+2); hist_CprPyth_365_100->SetMarkerStyle(kStar); hist_CprPyth_365_100->SetLineWidth(2); 	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising by area under histogram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	// hist_Esprime_912->Scale(1.0/hist_Esprime_912->Integral());
	// hist_Esprime_160->Scale(1.0/hist_Esprime_160->Integral());
	// hist_Esprime_240->Scale(1.0/hist_Esprime_240->Integral());
	// hist_Esprime_365->Scale(1.0/hist_Esprime_365->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_912_wiISR->Scale(1.0/hist_ThrPyth_al_912_wiISR->Integral("width"));
	hist_ThrPyth_Zq_912_wiISR->Scale(1.0/hist_ThrPyth_Zq_912_wiISR->Integral("width"));
	hist_ThrPyth_WW_912_wiISR->Scale(1.0/hist_ThrPyth_WW_912_wiISR->Integral("width"));
	hist_ThrPyth_ZZ_912_wiISR->Scale(1.0/hist_ThrPyth_ZZ_912_wiISR->Integral("width"));
	hist_ThrPyth_tt_912_wiISR->Scale(1.0/hist_ThrPyth_tt_912_wiISR->Integral("width"));
	hist_ThrPyth_HZ_912_wiISR->Scale(1.0/hist_ThrPyth_HZ_912_wiISR->Integral("width"));
	hist_ThrPyth_hW_912_wiISR->Scale(1.0/hist_ThrPyth_hW_912_wiISR->Integral("width"));

	hist_ThrPyth_al_160_wiISR->Scale(1.0/hist_ThrPyth_al_160_wiISR->Integral("width"));
	hist_ThrPyth_Zq_160_wiISR->Scale(1.0/hist_ThrPyth_Zq_160_wiISR->Integral("width"));
	hist_ThrPyth_WW_160_wiISR->Scale(1.0/hist_ThrPyth_WW_160_wiISR->Integral("width"));
	hist_ThrPyth_ZZ_160_wiISR->Scale(1.0/hist_ThrPyth_ZZ_160_wiISR->Integral("width"));
	hist_ThrPyth_tt_160_wiISR->Scale(1.0/hist_ThrPyth_tt_160_wiISR->Integral("width"));
	hist_ThrPyth_HZ_160_wiISR->Scale(1.0/hist_ThrPyth_HZ_160_wiISR->Integral("width"));
	hist_ThrPyth_hW_160_wiISR->Scale(1.0/hist_ThrPyth_hW_160_wiISR->Integral("width"));

	hist_ThrPyth_al_240_wiISR->Scale(1.0/hist_ThrPyth_al_240_wiISR->Integral("width"));
	hist_ThrPyth_Zq_240_wiISR->Scale(1.0/hist_ThrPyth_Zq_240_wiISR->Integral("width"));
	hist_ThrPyth_WW_240_wiISR->Scale(1.0/hist_ThrPyth_WW_240_wiISR->Integral("width"));
	hist_ThrPyth_ZZ_240_wiISR->Scale(1.0/hist_ThrPyth_ZZ_240_wiISR->Integral("width"));
	hist_ThrPyth_tt_240_wiISR->Scale(1.0/hist_ThrPyth_tt_240_wiISR->Integral("width"));
	hist_ThrPyth_HZ_240_wiISR->Scale(1.0/hist_ThrPyth_HZ_240_wiISR->Integral("width"));
	hist_ThrPyth_hW_240_wiISR->Scale(1.0/hist_ThrPyth_hW_240_wiISR->Integral("width"));

	hist_ThrPyth_al_365_wiISR->Scale(1.0/hist_ThrPyth_al_365_wiISR->Integral("width"));
	hist_ThrPyth_Zq_365_wiISR->Scale(1.0/hist_ThrPyth_Zq_365_wiISR->Integral("width"));
	hist_ThrPyth_WW_365_wiISR->Scale(1.0/hist_ThrPyth_WW_365_wiISR->Integral("width"));
	hist_ThrPyth_ZZ_365_wiISR->Scale(1.0/hist_ThrPyth_ZZ_365_wiISR->Integral("width"));
	hist_ThrPyth_tt_365_wiISR->Scale(1.0/hist_ThrPyth_tt_365_wiISR->Integral("width"));
	hist_ThrPyth_HZ_365_wiISR->Scale(1.0/hist_ThrPyth_HZ_365_wiISR->Integral("width"));
	hist_ThrPyth_hW_365_wiISR->Scale(1.0/hist_ThrPyth_hW_365_wiISR->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_CprPyth_al_912_wiISR->Scale(1.0/hist_CprPyth_al_912_wiISR->Integral("width"));
	hist_CprPyth_Zq_912_wiISR->Scale(1.0/hist_CprPyth_Zq_912_wiISR->Integral("width"));
	hist_CprPyth_WW_912_wiISR->Scale(1.0/hist_CprPyth_WW_912_wiISR->Integral("width"));
	hist_CprPyth_ZZ_912_wiISR->Scale(1.0/hist_CprPyth_ZZ_912_wiISR->Integral("width"));
	hist_CprPyth_tt_912_wiISR->Scale(1.0/hist_CprPyth_tt_912_wiISR->Integral("width"));
	hist_CprPyth_HZ_912_wiISR->Scale(1.0/hist_CprPyth_HZ_912_wiISR->Integral("width"));
	hist_CprPyth_hW_912_wiISR->Scale(1.0/hist_CprPyth_hW_912_wiISR->Integral("width"));

	hist_CprPyth_al_160_wiISR->Scale(1.0/hist_CprPyth_al_160_wiISR->Integral("width"));
	hist_CprPyth_Zq_160_wiISR->Scale(1.0/hist_CprPyth_Zq_160_wiISR->Integral("width"));
	hist_CprPyth_WW_160_wiISR->Scale(1.0/hist_CprPyth_WW_160_wiISR->Integral("width"));
	hist_CprPyth_ZZ_160_wiISR->Scale(1.0/hist_CprPyth_ZZ_160_wiISR->Integral("width"));
	hist_CprPyth_tt_160_wiISR->Scale(1.0/hist_CprPyth_tt_160_wiISR->Integral("width"));
	hist_CprPyth_HZ_160_wiISR->Scale(1.0/hist_CprPyth_HZ_160_wiISR->Integral("width"));
	hist_CprPyth_hW_160_wiISR->Scale(1.0/hist_CprPyth_hW_160_wiISR->Integral("width"));

	hist_CprPyth_al_240_wiISR->Scale(1.0/hist_CprPyth_al_240_wiISR->Integral("width"));
	hist_CprPyth_Zq_240_wiISR->Scale(1.0/hist_CprPyth_Zq_240_wiISR->Integral("width"));
	hist_CprPyth_WW_240_wiISR->Scale(1.0/hist_CprPyth_WW_240_wiISR->Integral("width"));
	hist_CprPyth_ZZ_240_wiISR->Scale(1.0/hist_CprPyth_ZZ_240_wiISR->Integral("width"));
	hist_CprPyth_tt_240_wiISR->Scale(1.0/hist_CprPyth_tt_240_wiISR->Integral("width"));
	hist_CprPyth_HZ_240_wiISR->Scale(1.0/hist_CprPyth_HZ_240_wiISR->Integral("width"));
	hist_CprPyth_hW_240_wiISR->Scale(1.0/hist_CprPyth_hW_240_wiISR->Integral("width"));

	hist_CprPyth_al_365_wiISR->Scale(1.0/hist_CprPyth_al_365_wiISR->Integral("width"));
	hist_CprPyth_Zq_365_wiISR->Scale(1.0/hist_CprPyth_Zq_365_wiISR->Integral("width"));
	hist_CprPyth_WW_365_wiISR->Scale(1.0/hist_CprPyth_WW_365_wiISR->Integral("width"));
	hist_CprPyth_ZZ_365_wiISR->Scale(1.0/hist_CprPyth_ZZ_365_wiISR->Integral("width"));
	hist_CprPyth_tt_365_wiISR->Scale(1.0/hist_CprPyth_tt_365_wiISR->Integral("width"));
	hist_CprPyth_HZ_365_wiISR->Scale(1.0/hist_CprPyth_HZ_365_wiISR->Integral("width"));
	hist_CprPyth_hW_365_wiISR->Scale(1.0/hist_CprPyth_hW_365_wiISR->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_912_woISR->Scale(1.0/hist_ThrPyth_al_912_woISR->Integral("width"));
	hist_ThrPyth_Zq_912_woISR->Scale(1.0/hist_ThrPyth_Zq_912_woISR->Integral("width"));
	hist_ThrPyth_WW_912_woISR->Scale(1.0/hist_ThrPyth_WW_912_woISR->Integral("width"));
	hist_ThrPyth_ZZ_912_woISR->Scale(1.0/hist_ThrPyth_ZZ_912_woISR->Integral("width"));
	hist_ThrPyth_tt_912_woISR->Scale(1.0/hist_ThrPyth_tt_912_woISR->Integral("width"));
	hist_ThrPyth_HZ_912_woISR->Scale(1.0/hist_ThrPyth_HZ_912_woISR->Integral("width"));
	hist_ThrPyth_hW_912_woISR->Scale(1.0/hist_ThrPyth_hW_912_woISR->Integral("width"));

	hist_ThrPyth_al_160_woISR->Scale(1.0/hist_ThrPyth_al_160_woISR->Integral("width"));
	hist_ThrPyth_Zq_160_woISR->Scale(1.0/hist_ThrPyth_Zq_160_woISR->Integral("width"));
	hist_ThrPyth_WW_160_woISR->Scale(1.0/hist_ThrPyth_WW_160_woISR->Integral("width"));
	hist_ThrPyth_ZZ_160_woISR->Scale(1.0/hist_ThrPyth_ZZ_160_woISR->Integral("width"));
	hist_ThrPyth_tt_160_woISR->Scale(1.0/hist_ThrPyth_tt_160_woISR->Integral("width"));
	hist_ThrPyth_HZ_160_woISR->Scale(1.0/hist_ThrPyth_HZ_160_woISR->Integral("width"));
	hist_ThrPyth_hW_160_woISR->Scale(1.0/hist_ThrPyth_hW_160_woISR->Integral("width"));

	hist_ThrPyth_al_240_woISR->Scale(1.0/hist_ThrPyth_al_240_woISR->Integral("width"));
	hist_ThrPyth_Zq_240_woISR->Scale(1.0/hist_ThrPyth_Zq_240_woISR->Integral("width"));
	hist_ThrPyth_WW_240_woISR->Scale(1.0/hist_ThrPyth_WW_240_woISR->Integral("width"));
	hist_ThrPyth_ZZ_240_woISR->Scale(1.0/hist_ThrPyth_ZZ_240_woISR->Integral("width"));
	hist_ThrPyth_tt_240_woISR->Scale(1.0/hist_ThrPyth_tt_240_woISR->Integral("width"));
	hist_ThrPyth_HZ_240_woISR->Scale(1.0/hist_ThrPyth_HZ_240_woISR->Integral("width"));
	hist_ThrPyth_hW_240_woISR->Scale(1.0/hist_ThrPyth_hW_240_woISR->Integral("width"));

	hist_ThrPyth_al_365_woISR->Scale(1.0/hist_ThrPyth_al_365_woISR->Integral("width"));
	hist_ThrPyth_Zq_365_woISR->Scale(1.0/hist_ThrPyth_Zq_365_woISR->Integral("width"));
	hist_ThrPyth_WW_365_woISR->Scale(1.0/hist_ThrPyth_WW_365_woISR->Integral("width"));
	hist_ThrPyth_ZZ_365_woISR->Scale(1.0/hist_ThrPyth_ZZ_365_woISR->Integral("width"));
	hist_ThrPyth_tt_365_woISR->Scale(1.0/hist_ThrPyth_tt_365_woISR->Integral("width"));
	hist_ThrPyth_HZ_365_woISR->Scale(1.0/hist_ThrPyth_HZ_365_woISR->Integral("width"));
	hist_ThrPyth_hW_365_woISR->Scale(1.0/hist_ThrPyth_hW_365_woISR->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_CprPyth_al_912_woISR->Scale(1.0/hist_CprPyth_al_912_woISR->Integral("width"));
	hist_CprPyth_Zq_912_woISR->Scale(1.0/hist_CprPyth_Zq_912_woISR->Integral("width"));
	hist_CprPyth_WW_912_woISR->Scale(1.0/hist_CprPyth_WW_912_woISR->Integral("width"));
	hist_CprPyth_ZZ_912_woISR->Scale(1.0/hist_CprPyth_ZZ_912_woISR->Integral("width"));
	hist_CprPyth_tt_912_woISR->Scale(1.0/hist_CprPyth_tt_912_woISR->Integral("width"));
	hist_CprPyth_HZ_912_woISR->Scale(1.0/hist_CprPyth_HZ_912_woISR->Integral("width"));
	hist_CprPyth_hW_912_woISR->Scale(1.0/hist_CprPyth_hW_912_woISR->Integral("width"));

	hist_CprPyth_al_160_woISR->Scale(1.0/hist_CprPyth_al_160_woISR->Integral("width"));
	hist_CprPyth_Zq_160_woISR->Scale(1.0/hist_CprPyth_Zq_160_woISR->Integral("width"));
	hist_CprPyth_WW_160_woISR->Scale(1.0/hist_CprPyth_WW_160_woISR->Integral("width"));
	hist_CprPyth_ZZ_160_woISR->Scale(1.0/hist_CprPyth_ZZ_160_woISR->Integral("width"));
	hist_CprPyth_tt_160_woISR->Scale(1.0/hist_CprPyth_tt_160_woISR->Integral("width"));
	hist_CprPyth_HZ_160_woISR->Scale(1.0/hist_CprPyth_HZ_160_woISR->Integral("width"));
	hist_CprPyth_hW_160_woISR->Scale(1.0/hist_CprPyth_hW_160_woISR->Integral("width"));

	hist_CprPyth_al_240_woISR->Scale(1.0/hist_CprPyth_al_240_woISR->Integral("width"));
	hist_CprPyth_Zq_240_woISR->Scale(1.0/hist_CprPyth_Zq_240_woISR->Integral("width"));
	hist_CprPyth_WW_240_woISR->Scale(1.0/hist_CprPyth_WW_240_woISR->Integral("width"));
	hist_CprPyth_ZZ_240_woISR->Scale(1.0/hist_CprPyth_ZZ_240_woISR->Integral("width"));
	hist_CprPyth_tt_240_woISR->Scale(1.0/hist_CprPyth_tt_240_woISR->Integral("width"));
	hist_CprPyth_HZ_240_woISR->Scale(1.0/hist_CprPyth_HZ_240_woISR->Integral("width"));
	hist_CprPyth_hW_240_woISR->Scale(1.0/hist_CprPyth_hW_240_woISR->Integral("width"));

	hist_CprPyth_al_365_woISR->Scale(1.0/hist_CprPyth_al_365_woISR->Integral("width"));
	hist_CprPyth_Zq_365_woISR->Scale(1.0/hist_CprPyth_Zq_365_woISR->Integral("width"));
	hist_CprPyth_WW_365_woISR->Scale(1.0/hist_CprPyth_WW_365_woISR->Integral("width"));
	hist_CprPyth_ZZ_365_woISR->Scale(1.0/hist_CprPyth_ZZ_365_woISR->Integral("width"));
	hist_CprPyth_tt_365_woISR->Scale(1.0/hist_CprPyth_tt_365_woISR->Integral("width"));
	hist_CprPyth_HZ_365_woISR->Scale(1.0/hist_CprPyth_HZ_365_woISR->Integral("width"));
	hist_CprPyth_hW_365_woISR->Scale(1.0/hist_CprPyth_hW_365_woISR->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912_000->Scale(1.0/hist_ThrPyth_912_000->Integral("width"));
	hist_ThrPyth_912_085->Scale(1.0/hist_ThrPyth_912_085->Integral("width"));
	hist_ThrPyth_912_095->Scale(1.0/hist_ThrPyth_912_095->Integral("width"));
	hist_ThrPyth_912_100->Scale(1.0/hist_ThrPyth_912_100->Integral("width"));

	hist_ThrPyth_160_000->Scale(1.0/hist_ThrPyth_160_000->Integral("width"));
	hist_ThrPyth_160_085->Scale(1.0/hist_ThrPyth_160_085->Integral("width"));
	hist_ThrPyth_160_095->Scale(1.0/hist_ThrPyth_160_095->Integral("width"));
	hist_ThrPyth_160_100->Scale(1.0/hist_ThrPyth_160_100->Integral("width"));

	hist_ThrPyth_240_000->Scale(1.0/hist_ThrPyth_240_000->Integral("width"));
	hist_ThrPyth_240_085->Scale(1.0/hist_ThrPyth_240_085->Integral("width"));
	hist_ThrPyth_240_095->Scale(1.0/hist_ThrPyth_240_095->Integral("width"));
	hist_ThrPyth_240_100->Scale(1.0/hist_ThrPyth_240_100->Integral("width"));

	hist_ThrPyth_365_000->Scale(1.0/hist_ThrPyth_365_000->Integral("width"));
	hist_ThrPyth_365_085->Scale(1.0/hist_ThrPyth_365_085->Integral("width"));
	hist_ThrPyth_365_095->Scale(1.0/hist_ThrPyth_365_095->Integral("width"));
	hist_ThrPyth_365_100->Scale(1.0/hist_ThrPyth_365_100->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_CprPyth_912_000->Scale(1.0/hist_CprPyth_912_000->Integral("width"));
	hist_CprPyth_912_085->Scale(1.0/hist_CprPyth_912_085->Integral("width"));
	hist_CprPyth_912_095->Scale(1.0/hist_CprPyth_912_095->Integral("width"));
	hist_CprPyth_912_100->Scale(1.0/hist_CprPyth_912_100->Integral("width"));

	hist_CprPyth_160_000->Scale(1.0/hist_CprPyth_160_000->Integral("width"));
	hist_CprPyth_160_085->Scale(1.0/hist_CprPyth_160_085->Integral("width"));
	hist_CprPyth_160_095->Scale(1.0/hist_CprPyth_160_095->Integral("width"));
	hist_CprPyth_160_100->Scale(1.0/hist_CprPyth_160_100->Integral("width"));

	hist_CprPyth_240_000->Scale(1.0/hist_CprPyth_240_000->Integral("width"));
	hist_CprPyth_240_085->Scale(1.0/hist_CprPyth_240_085->Integral("width"));
	hist_CprPyth_240_095->Scale(1.0/hist_CprPyth_240_095->Integral("width"));
	hist_CprPyth_240_100->Scale(1.0/hist_CprPyth_240_100->Integral("width"));

	hist_CprPyth_365_000->Scale(1.0/hist_CprPyth_365_000->Integral("width"));
	hist_CprPyth_365_085->Scale(1.0/hist_CprPyth_365_085->Integral("width"));
	hist_CprPyth_365_095->Scale(1.0/hist_CprPyth_365_095->Integral("width"));
	hist_CprPyth_365_100->Scale(1.0/hist_CprPyth_365_100->Integral("width"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_NumbISR_912->SetStats(kFALSE);
	hist_NumbISR_160->SetStats(kFALSE);
	hist_NumbISR_240->SetStats(kFALSE);
	hist_NumbISR_365->SetStats(kFALSE);

	hist_Esprime_912->SetStats(kFALSE);
	hist_Esprime_160->SetStats(kFALSE);
	hist_Esprime_240->SetStats(kFALSE);
	hist_Esprime_365->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_912_wiISR->SetStats(kFALSE);
	hist_ThrPyth_Zq_912_wiISR->SetStats(kFALSE);
	hist_ThrPyth_WW_912_wiISR->SetStats(kFALSE);
	hist_ThrPyth_ZZ_912_wiISR->SetStats(kFALSE);
	hist_ThrPyth_tt_912_wiISR->SetStats(kFALSE);
	hist_ThrPyth_HZ_912_wiISR->SetStats(kFALSE);
	hist_ThrPyth_hW_912_wiISR->SetStats(kFALSE);

	hist_ThrPyth_al_160_wiISR->SetStats(kFALSE);
	hist_ThrPyth_Zq_160_wiISR->SetStats(kFALSE);
	hist_ThrPyth_WW_160_wiISR->SetStats(kFALSE);
	hist_ThrPyth_ZZ_160_wiISR->SetStats(kFALSE);
	hist_ThrPyth_tt_160_wiISR->SetStats(kFALSE);
	hist_ThrPyth_HZ_160_wiISR->SetStats(kFALSE);
	hist_ThrPyth_hW_160_wiISR->SetStats(kFALSE);

	hist_ThrPyth_al_240_wiISR->SetStats(kFALSE);
	hist_ThrPyth_Zq_240_wiISR->SetStats(kFALSE);
	hist_ThrPyth_WW_240_wiISR->SetStats(kFALSE);
	hist_ThrPyth_ZZ_240_wiISR->SetStats(kFALSE);
	hist_ThrPyth_tt_240_wiISR->SetStats(kFALSE);
	hist_ThrPyth_HZ_240_wiISR->SetStats(kFALSE);
	hist_ThrPyth_hW_240_wiISR->SetStats(kFALSE);

	hist_ThrPyth_al_365_wiISR->SetStats(kFALSE);
	hist_ThrPyth_Zq_365_wiISR->SetStats(kFALSE);
	hist_ThrPyth_WW_365_wiISR->SetStats(kFALSE);
	hist_ThrPyth_ZZ_365_wiISR->SetStats(kFALSE);
	hist_ThrPyth_tt_365_wiISR->SetStats(kFALSE);
	hist_ThrPyth_HZ_365_wiISR->SetStats(kFALSE);
	hist_ThrPyth_hW_365_wiISR->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_CprPyth_al_912_wiISR->SetStats(kFALSE);
	hist_CprPyth_Zq_912_wiISR->SetStats(kFALSE);
	hist_CprPyth_WW_912_wiISR->SetStats(kFALSE);
	hist_CprPyth_ZZ_912_wiISR->SetStats(kFALSE);
	hist_CprPyth_tt_912_wiISR->SetStats(kFALSE);
	hist_CprPyth_HZ_912_wiISR->SetStats(kFALSE);
	hist_CprPyth_hW_912_wiISR->SetStats(kFALSE);

	hist_CprPyth_al_160_wiISR->SetStats(kFALSE);
	hist_CprPyth_Zq_160_wiISR->SetStats(kFALSE);
	hist_CprPyth_WW_160_wiISR->SetStats(kFALSE);
	hist_CprPyth_ZZ_160_wiISR->SetStats(kFALSE);
	hist_CprPyth_tt_160_wiISR->SetStats(kFALSE);
	hist_CprPyth_HZ_160_wiISR->SetStats(kFALSE);
	hist_CprPyth_hW_160_wiISR->SetStats(kFALSE);

	hist_CprPyth_al_240_wiISR->SetStats(kFALSE);
	hist_CprPyth_Zq_240_wiISR->SetStats(kFALSE);
	hist_CprPyth_WW_240_wiISR->SetStats(kFALSE);
	hist_CprPyth_ZZ_240_wiISR->SetStats(kFALSE);
	hist_CprPyth_tt_240_wiISR->SetStats(kFALSE);
	hist_CprPyth_HZ_240_wiISR->SetStats(kFALSE);
	hist_CprPyth_hW_240_wiISR->SetStats(kFALSE);

	hist_CprPyth_al_365_wiISR->SetStats(kFALSE);
	hist_CprPyth_Zq_365_wiISR->SetStats(kFALSE);
	hist_CprPyth_WW_365_wiISR->SetStats(kFALSE);
	hist_CprPyth_ZZ_365_wiISR->SetStats(kFALSE);
	hist_CprPyth_tt_365_wiISR->SetStats(kFALSE);
	hist_CprPyth_HZ_365_wiISR->SetStats(kFALSE);
	hist_CprPyth_hW_365_wiISR->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_al_912_woISR->SetStats(kFALSE);
	hist_ThrPyth_Zq_912_woISR->SetStats(kFALSE);
	hist_ThrPyth_WW_912_woISR->SetStats(kFALSE);
	hist_ThrPyth_ZZ_912_woISR->SetStats(kFALSE);
	hist_ThrPyth_tt_912_woISR->SetStats(kFALSE);
	hist_ThrPyth_HZ_912_woISR->SetStats(kFALSE);
	hist_ThrPyth_hW_912_woISR->SetStats(kFALSE);

	hist_ThrPyth_al_160_woISR->SetStats(kFALSE);
	hist_ThrPyth_Zq_160_woISR->SetStats(kFALSE);
	hist_ThrPyth_WW_160_woISR->SetStats(kFALSE);
	hist_ThrPyth_ZZ_160_woISR->SetStats(kFALSE);
	hist_ThrPyth_tt_160_woISR->SetStats(kFALSE);
	hist_ThrPyth_HZ_160_woISR->SetStats(kFALSE);
	hist_ThrPyth_hW_160_woISR->SetStats(kFALSE);

	hist_ThrPyth_al_240_woISR->SetStats(kFALSE);
	hist_ThrPyth_Zq_240_woISR->SetStats(kFALSE);
	hist_ThrPyth_WW_240_woISR->SetStats(kFALSE);
	hist_ThrPyth_ZZ_240_woISR->SetStats(kFALSE);
	hist_ThrPyth_tt_240_woISR->SetStats(kFALSE);
	hist_ThrPyth_HZ_240_woISR->SetStats(kFALSE);
	hist_ThrPyth_hW_240_woISR->SetStats(kFALSE);

	hist_ThrPyth_al_365_woISR->SetStats(kFALSE);
	hist_ThrPyth_Zq_365_woISR->SetStats(kFALSE);
	hist_ThrPyth_WW_365_woISR->SetStats(kFALSE);
	hist_ThrPyth_ZZ_365_woISR->SetStats(kFALSE);
	hist_ThrPyth_tt_365_woISR->SetStats(kFALSE);
	hist_ThrPyth_HZ_365_woISR->SetStats(kFALSE);
	hist_ThrPyth_hW_365_woISR->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_CprPyth_al_912_woISR->SetStats(kFALSE);
	hist_CprPyth_Zq_912_woISR->SetStats(kFALSE);
	hist_CprPyth_WW_912_woISR->SetStats(kFALSE);
	hist_CprPyth_ZZ_912_woISR->SetStats(kFALSE);
	hist_CprPyth_tt_912_woISR->SetStats(kFALSE);
	hist_CprPyth_HZ_912_woISR->SetStats(kFALSE);
	hist_CprPyth_hW_912_woISR->SetStats(kFALSE);

	hist_CprPyth_al_160_woISR->SetStats(kFALSE);
	hist_CprPyth_Zq_160_woISR->SetStats(kFALSE);
	hist_CprPyth_WW_160_woISR->SetStats(kFALSE);
	hist_CprPyth_ZZ_160_woISR->SetStats(kFALSE);
	hist_CprPyth_tt_160_woISR->SetStats(kFALSE);
	hist_CprPyth_HZ_160_woISR->SetStats(kFALSE);
	hist_CprPyth_hW_160_woISR->SetStats(kFALSE);

	hist_CprPyth_al_240_woISR->SetStats(kFALSE);
	hist_CprPyth_Zq_240_woISR->SetStats(kFALSE);
	hist_CprPyth_WW_240_woISR->SetStats(kFALSE);
	hist_CprPyth_ZZ_240_woISR->SetStats(kFALSE);
	hist_CprPyth_tt_240_woISR->SetStats(kFALSE);
	hist_CprPyth_HZ_240_woISR->SetStats(kFALSE);
	hist_CprPyth_hW_240_woISR->SetStats(kFALSE);

	hist_CprPyth_al_365_woISR->SetStats(kFALSE);
	hist_CprPyth_Zq_365_woISR->SetStats(kFALSE);
	hist_CprPyth_WW_365_woISR->SetStats(kFALSE);
	hist_CprPyth_ZZ_365_woISR->SetStats(kFALSE);
	hist_CprPyth_tt_365_woISR->SetStats(kFALSE);
	hist_CprPyth_HZ_365_woISR->SetStats(kFALSE);
	hist_CprPyth_hW_365_woISR->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912_000->SetStats(kFALSE);
	hist_ThrPyth_912_085->SetStats(kFALSE);
	hist_ThrPyth_912_095->SetStats(kFALSE);
	hist_ThrPyth_912_100->SetStats(kFALSE);

	hist_ThrPyth_160_000->SetStats(kFALSE);
	hist_ThrPyth_160_085->SetStats(kFALSE);
	hist_ThrPyth_160_095->SetStats(kFALSE);
	hist_ThrPyth_160_100->SetStats(kFALSE);

	hist_ThrPyth_240_000->SetStats(kFALSE);
	hist_ThrPyth_240_085->SetStats(kFALSE);
	hist_ThrPyth_240_095->SetStats(kFALSE);
	hist_ThrPyth_240_100->SetStats(kFALSE);

	hist_ThrPyth_365_000->SetStats(kFALSE);
	hist_ThrPyth_365_085->SetStats(kFALSE);
	hist_ThrPyth_365_095->SetStats(kFALSE);
	hist_ThrPyth_365_100->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_CprPyth_912_000->SetStats(kFALSE);
	hist_CprPyth_912_085->SetStats(kFALSE);
	hist_CprPyth_912_095->SetStats(kFALSE);
	hist_CprPyth_912_100->SetStats(kFALSE);

	hist_CprPyth_160_000->SetStats(kFALSE);
	hist_CprPyth_160_085->SetStats(kFALSE);
	hist_CprPyth_160_095->SetStats(kFALSE);
	hist_CprPyth_160_100->SetStats(kFALSE);

	hist_CprPyth_240_000->SetStats(kFALSE);
	hist_CprPyth_240_085->SetStats(kFALSE);
	hist_CprPyth_240_095->SetStats(kFALSE);
	hist_CprPyth_240_100->SetStats(kFALSE);

	hist_CprPyth_365_000->SetStats(kFALSE);
	hist_CprPyth_365_085->SetStats(kFALSE);
	hist_CprPyth_365_095->SetStats(kFALSE);
	hist_CprPyth_365_100->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_NumbISR_912->SetTitle("");
	hist_Esprime_912->SetTitle("");
	hist_Esprime_365->SetTitle("");

	hist_ThrPyth_Zq_912_woISR->SetTitle("");
	hist_ThrPyth_Zq_160_woISR->SetTitle("");
	hist_ThrPyth_Zq_240_woISR->SetTitle("");
	hist_ThrPyth_Zq_365_woISR->SetTitle("");

	hist_CprPyth_Zq_912_woISR->SetTitle("");
	hist_CprPyth_Zq_160_woISR->SetTitle("");
	hist_CprPyth_Zq_240_woISR->SetTitle("");
	hist_CprPyth_Zq_365_woISR->SetTitle("");

	hist_ThrPyth_912_000->SetTitle("");
	hist_ThrPyth_160_000->SetTitle("");
	hist_ThrPyth_240_000->SetTitle("");
	hist_ThrPyth_365_000->SetTitle("");
	hist_CprPyth_912_000->SetTitle("");
	hist_CprPyth_160_000->SetTitle("");
	hist_CprPyth_240_000->SetTitle("");
	hist_CprPyth_365_000->SetTitle("");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit text sizes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_NumbISR_912->GetXaxis()->SetLabelSize(0.04);hist_NumbISR_912->GetYaxis()->SetLabelSize(0.04); hist_NumbISR_912->GetYaxis()->SetTitleSize(0.04); hist_NumbISR_912->GetXaxis()->SetTitleSize(0.04);
	hist_Esprime_912->GetXaxis()->SetLabelSize(0.04); hist_Esprime_912->GetYaxis()->SetLabelSize(0.04); hist_Esprime_912->GetYaxis()->SetTitleSize(0.04); hist_Esprime_912->GetXaxis()->SetTitleSize(0.04);
	hist_Esprime_365->GetXaxis()->SetLabelSize(0.04); hist_Esprime_365->GetYaxis()->SetLabelSize(0.04); hist_Esprime_365->GetYaxis()->SetTitleSize(0.04); hist_Esprime_365->GetXaxis()->SetTitleSize(0.04);

	hist_ThrPyth_Zq_912_woISR->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_Zq_912_woISR->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_Zq_160_woISR->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_Zq_160_woISR->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_Zq_240_woISR->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_Zq_240_woISR->GetYaxis()->SetLabelSize(0.04);
	hist_ThrPyth_Zq_365_woISR->GetXaxis()->SetLabelSize(0.04); hist_ThrPyth_Zq_365_woISR->GetYaxis()->SetLabelSize(0.04);

	hist_CprPyth_Zq_912_woISR->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_Zq_912_woISR->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_Zq_160_woISR->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_Zq_160_woISR->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_Zq_240_woISR->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_Zq_240_woISR->GetYaxis()->SetLabelSize(0.04);
	hist_CprPyth_Zq_365_woISR->GetXaxis()->SetLabelSize(0.04); hist_CprPyth_Zq_365_woISR->GetYaxis()->SetLabelSize(0.04);
 
	hist_ThrPyth_912_000->GetXaxis()->SetLabelSize(0.06); hist_ThrPyth_912_000->GetYaxis()->SetLabelSize(0.06); hist_ThrPyth_912_000->GetYaxis()->SetTitleSize(0.06); hist_ThrPyth_912_000->GetXaxis()->SetTitleSize(0.06); 
	hist_ThrPyth_160_000->GetXaxis()->SetLabelSize(0.06); hist_ThrPyth_160_000->GetYaxis()->SetLabelSize(0.06); hist_ThrPyth_160_000->GetYaxis()->SetTitleSize(0.06); hist_ThrPyth_160_000->GetXaxis()->SetTitleSize(0.06); 
	hist_ThrPyth_240_000->GetXaxis()->SetLabelSize(0.06); hist_ThrPyth_240_000->GetYaxis()->SetLabelSize(0.06); hist_ThrPyth_240_000->GetYaxis()->SetTitleSize(0.06); hist_ThrPyth_240_000->GetXaxis()->SetTitleSize(0.06); 
	hist_ThrPyth_365_000->GetXaxis()->SetLabelSize(0.06); hist_ThrPyth_365_000->GetYaxis()->SetLabelSize(0.06); hist_ThrPyth_365_000->GetYaxis()->SetTitleSize(0.06); hist_ThrPyth_365_000->GetXaxis()->SetTitleSize(0.06); 

	hist_CprPyth_912_000->GetXaxis()->SetLabelSize(0.06); hist_CprPyth_912_000->GetYaxis()->SetLabelSize(0.06); hist_CprPyth_912_000->GetYaxis()->SetTitleSize(0.06); hist_CprPyth_912_000->GetXaxis()->SetTitleSize(0.06); 
	hist_CprPyth_160_000->GetXaxis()->SetLabelSize(0.06); hist_CprPyth_160_000->GetYaxis()->SetLabelSize(0.06); hist_CprPyth_160_000->GetYaxis()->SetTitleSize(0.06); hist_CprPyth_160_000->GetXaxis()->SetTitleSize(0.06); 
	hist_CprPyth_240_000->GetXaxis()->SetLabelSize(0.06); hist_CprPyth_240_000->GetYaxis()->SetLabelSize(0.06); hist_CprPyth_240_000->GetYaxis()->SetTitleSize(0.06); hist_CprPyth_240_000->GetXaxis()->SetTitleSize(0.06); 
	hist_CprPyth_365_000->GetXaxis()->SetLabelSize(0.06); hist_CprPyth_365_000->GetYaxis()->SetLabelSize(0.06); hist_CprPyth_365_000->GetYaxis()->SetTitleSize(0.06); hist_CprPyth_365_000->GetXaxis()->SetTitleSize(0.06); 
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv1 = new TCanvas("cv1", "FCC-ee ISR Studies", 1000, 800);

	// // Add legend
	// TLegend* lg1 = new TLegend(0.76, 0.75, 0.96, 0.94);
	// lg1->AddEntry(hist_Esprime_912, "#sqrt{s} = 91.2 GeV", "p");
	// lg1->AddEntry(hist_Esprime_160, "#sqrt{s} = 160 GeV", "p");
	// lg1->AddEntry(hist_Esprime_240, "#sqrt{s} = 240 GeV", "p");
	// lg1->AddEntry(hist_Esprime_365, "#sqrt{s} = 500 GeV", "p");
	// lg1->SetTextSize(0.03);

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv1->SetMargin(0, 0, 0, 0); 
	// gPad->SetTopMargin(0.025);
	// gPad->SetBottomMargin(0.10);
	// gPad->SetLeftMargin(0.10);
	// gPad->SetRightMargin(0.01);
	// gPad->SetTickx(); gPad->SetTicky();
	// gPad->SetLogy();


	// hist_Esprime_912->Draw("P");
	// hist_Esprime_160->Draw("P SAME");
	// hist_Esprime_240->Draw("P SAME");
	// hist_Esprime_365->Draw("P SAME");
	// lg1->Draw("SAME");

	// // Set limits
	// hist_Esprime_912->GetYaxis()->SetRangeUser(1E0,1E6);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv1->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912_000->SetLineColor(kBlack); 
	hist_ThrPyth_160_000->SetLineColor(kBlack);
	hist_ThrPyth_240_000->SetLineColor(kBlack);
	hist_ThrPyth_365_000->SetLineColor(kBlack);
	
	hist_CprPyth_912_000->SetLineColor(kBlack);
	hist_CprPyth_160_000->SetLineColor(kBlack);
	hist_CprPyth_240_000->SetLineColor(kBlack);
	hist_CprPyth_365_000->SetLineColor(kBlack);

	hist_ThrPyth_912_100->SetLineColor(kRed+1);
	hist_ThrPyth_160_100->SetLineColor(kRed+1);
	hist_ThrPyth_240_100->SetLineColor(kRed+1);
	hist_ThrPyth_365_100->SetLineColor(kRed+1);
	
	hist_CprPyth_912_100->SetLineColor(kRed+1);
	hist_CprPyth_160_100->SetLineColor(kRed+1);
	hist_CprPyth_240_100->SetLineColor(kRed+1);
	hist_CprPyth_365_100->SetLineColor(kRed+1);

	// Create canvas
	TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 800, 1000);

	// Add legend
	TLegend* lg2 = new TLegend(0.20, 0.20, 0.37, 0.45);
	lg2->AddEntry(hist_ThrPyth_912_000, "No cut", "L");
	lg2->AddEntry(hist_ThrPyth_912_085, "LEP cut", "L");
	// lg2->AddEntry(hist_ThrPyth_912_095, "0.95 cut", "L");
	lg2->AddEntry(hist_ThrPyth_912_100, "Full cut", "L");
	lg2->SetTextSize(0.06);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv2->SetMargin(0, 0, 0, 0); 
	cv2->Divide(2,4);
	for (int i = 1; i <= 8; i++) {
		cv2->cd(i);
		gPad->SetTopMargin(0.025);
		gPad->SetBottomMargin(0.14);
		gPad->SetLeftMargin(0.15);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		gPad->SetLogy();
	}

	cv2->cd(1);
	hist_ThrPyth_912_000->Draw("HIST");
	hist_ThrPyth_912_085->Draw("HIST SAME");
	hist_ThrPyth_912_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(3);
	hist_ThrPyth_160_000->Draw("HIST");
	hist_ThrPyth_160_085->Draw("HIST SAME");
	hist_ThrPyth_160_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(5);
	hist_ThrPyth_240_000->Draw("HIST");
	hist_ThrPyth_240_085->Draw("HIST SAME");
	hist_ThrPyth_240_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(7);
	hist_ThrPyth_365_000->Draw("HIST");
	hist_ThrPyth_365_085->Draw("HIST SAME");
	hist_ThrPyth_365_100->Draw("HIST SAME");
	lg2->Draw("SAME");

	cv2->cd(2);
	hist_CprPyth_912_000->Draw("HIST");
	hist_CprPyth_912_085->Draw("HIST SAME");
	hist_CprPyth_912_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(4);
	hist_CprPyth_160_000->Draw("HIST");
	hist_CprPyth_160_085->Draw("HIST SAME");
	hist_CprPyth_160_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(6);
	hist_CprPyth_240_000->Draw("HIST");
	hist_CprPyth_240_085->Draw("HIST SAME");
	hist_CprPyth_240_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(8);
	hist_CprPyth_365_000->Draw("HIST");
	hist_CprPyth_365_085->Draw("HIST SAME");
	hist_CprPyth_365_100->Draw("HIST SAME");
	lg2->Draw("SAME");

	// Set limits
	hist_ThrPyth_912_000->GetYaxis()->SetRangeUser(1E-4,1E2);
	hist_ThrPyth_912_000->GetXaxis()->SetRangeUser(0,0.4);
	hist_ThrPyth_160_000->GetYaxis()->SetRangeUser(1E-4,1E2);
	hist_ThrPyth_160_000->GetXaxis()->SetRangeUser(0,0.4);
	hist_ThrPyth_240_000->GetYaxis()->SetRangeUser(1E-4,1E2);
	hist_ThrPyth_240_000->GetXaxis()->SetRangeUser(0,0.4);
	hist_ThrPyth_365_000->GetYaxis()->SetRangeUser(1E-4,1E2);
	hist_ThrPyth_365_000->GetXaxis()->SetRangeUser(0,0.4);

	hist_CprPyth_912_000->GetYaxis()->SetRangeUser(1E-4,1E2);
	hist_CprPyth_912_000->GetXaxis()->SetRangeUser(0,1.0);
	hist_CprPyth_160_000->GetYaxis()->SetRangeUser(1E-4,1E2);
	hist_CprPyth_160_000->GetXaxis()->SetRangeUser(0,1.0);
	hist_CprPyth_240_000->GetYaxis()->SetRangeUser(1E-4,1E2);
	hist_CprPyth_240_000->GetXaxis()->SetRangeUser(0,1.0);
	hist_CprPyth_365_000->GetYaxis()->SetRangeUser(1E-4,1E2);
	hist_CprPyth_365_000->GetXaxis()->SetRangeUser(0,1.0);	

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv2->Modified();	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Create canvas
	// TCanvas* cv3 = new TCanvas("cv3", "FCC-ee ISR Studies", 1000, 800);

	// // Add legend
	// TLegend* lg3 = new TLegend(0.13, 0.65, 0.28, 0.95);
	// lg3->AddEntry(hist_Esprime_365, "ee#rightarrowq#bar{q}", "L");
	// lg3->AddEntry(hist_Esprime_Zq_365, "ee#rightarrow#gamma*/Z", "L");
	// lg3->AddEntry(hist_Esprime_WW_365, "ee#rightarrowWW", "L");
	// lg3->AddEntry(hist_Esprime_ZZ_365, "ee#rightarrowZZ", "L");
	// lg3->AddEntry(hist_Esprime_tt_365, "ee#rightarrowt#bar{t}", "L");
	// lg3->AddEntry(hist_Esprime_HZ_365, "ee#rightarrowZH", "L");
	// lg3->AddEntry(hist_Esprime_hW_365, "ee#rightarrow#nu_{e}#bar{#nu_{e}}H", "L");
	// lg3->SetTextSize(0.03);

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv3->SetMargin(0, 0, 0, 0); 
	// gPad->SetTopMargin(0.025);
	// gPad->SetBottomMargin(0.10);
	// gPad->SetLeftMargin(0.10);
	// gPad->SetRightMargin(0.01);
	// gPad->SetTickx(); gPad->SetTicky();
	// gPad->SetLogy();

	// hist_Esprime_365->Draw("HIST");
	// hist_Esprime_Zq_365->Draw("HIST SAME");
	// hist_Esprime_WW_365->Draw("HIST SAME");
	// hist_Esprime_ZZ_365->Draw("HIST SAME");
	// hist_Esprime_tt_365->Draw("HIST SAME");
	// hist_Esprime_HZ_365->Draw("HIST SAME");
	// hist_Esprime_hW_365->Draw("HIST SAME");
	// lg3->Draw("SAME");

	// // Set limits
	// hist_Esprime_365->GetYaxis()->SetRangeUser(1E0,1E6);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv3->Modified();

}