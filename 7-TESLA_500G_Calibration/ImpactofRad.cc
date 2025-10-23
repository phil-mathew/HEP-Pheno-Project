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
void ImpactofRad() {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// TFile* input_912_woISR = new TFile("5-CutData/cut_FCC912.root", "READ");
	// TFile* input_160_woISR = new TFile("5-CutData/cut_FCC160.root", "READ");
	// TFile* input_240_woISR = new TFile("5-CutData/cut_FCC240.root", "READ");
	// TFile* input_365_woISR = new TFile("5-CutData/cut_FCC365.root", "READ");

	TFile* input_912_wiISR = new TFile("5-CutData/cut_FCC912_ISR.root", "READ");
	TFile* input_160_wiISR = new TFile("5-CutData/cut_FCC160_ISR.root", "READ");
	TFile* input_240_wiISR = new TFile("5-CutData/cut_FCC240_ISR.root", "READ");
	TFile* input_365_wiISR = new TFile("5-CutData/cut_FCC365_ISR.root", "READ");

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
	hist_Esprime_365->SetLineColor(kBlack); hist_Esprime_365->SetMarkerColor(kBlack); hist_Esprime_365->SetMarkerStyle(21); hist_Esprime_365->SetLineWidth(2); hist_Esprime_365->SetMarkerSize(1);

	TH1F* hist_Esprime_Zq_912 = (TH1F*)input_912_wiISR->Get("hist_Esprime_Zq");
	hist_Esprime_Zq_912->SetLineColor(kYellow+2); hist_Esprime_Zq_912->SetMarkerColor(kYellow+2); hist_Esprime_Zq_912->SetMarkerStyle(3); hist_Esprime_Zq_912->SetLineStyle(1); hist_Esprime_Zq_912->SetLineWidth(2); hist_Esprime_Zq_912->SetMarkerSize(1);
	TH1F* hist_Esprime_WW_912 = (TH1F*)input_912_wiISR->Get("hist_Esprime_WW");
	hist_Esprime_WW_912->SetLineColor(kGreen+2); hist_Esprime_WW_912->SetMarkerColor(kGreen+2); hist_Esprime_WW_912->SetMarkerStyle(3); hist_Esprime_WW_912->SetLineStyle(2); hist_Esprime_WW_912->SetLineWidth(2); hist_Esprime_WW_912->SetMarkerSize(1);
	TH1F* hist_Esprime_ZZ_912 = (TH1F*)input_912_wiISR->Get("hist_Esprime_ZZ");
	hist_Esprime_ZZ_912->SetLineColor(kBlue+2); hist_Esprime_ZZ_912->SetMarkerColor(kBlue+2); hist_Esprime_ZZ_912->SetMarkerStyle(3); hist_Esprime_ZZ_912->SetLineStyle(2); hist_Esprime_ZZ_912->SetLineWidth(2); hist_Esprime_ZZ_912->SetMarkerSize(1);
	TH1F* hist_Esprime_tt_912 = (TH1F*)input_912_wiISR->Get("hist_Esprime_tt");
	hist_Esprime_tt_912->SetLineColor(kBlue+2); hist_Esprime_tt_912->SetMarkerColor(kBlue+2); hist_Esprime_tt_912->SetMarkerStyle(3); hist_Esprime_tt_912->SetLineStyle(1); hist_Esprime_tt_912->SetLineWidth(2); hist_Esprime_tt_912->SetMarkerSize(1);
	TH1F* hist_Esprime_HZ_912 = (TH1F*)input_912_wiISR->Get("hist_Esprime_HZ");
	hist_Esprime_HZ_912->SetLineColor(kGreen+2); hist_Esprime_HZ_912->SetMarkerColor(kGreen+2); hist_Esprime_HZ_912->SetMarkerStyle(53); hist_Esprime_HZ_912->SetLineStyle(1); hist_Esprime_HZ_912->SetLineWidth(2); hist_Esprime_HZ_912->SetMarkerSize(1);
	TH1F* hist_Esprime_HW_912 = (TH1F*)input_912_wiISR->Get("hist_Esprime_HW");
	hist_Esprime_HW_912->SetLineColor(kRed+2); hist_Esprime_HW_912->SetMarkerColor(kRed+2); hist_Esprime_HW_912->SetMarkerStyle(53); hist_Esprime_HW_912->SetLineStyle(1); hist_Esprime_HW_912->SetLineWidth(2); hist_Esprime_HW_912->SetMarkerSize(1);

	TH1F* hist_Esprime_Zq_160 = (TH1F*)input_160_wiISR->Get("hist_Esprime_Zq");
	hist_Esprime_Zq_160->SetLineColor(kYellow+2); hist_Esprime_Zq_160->SetMarkerColor(kYellow+2); hist_Esprime_Zq_160->SetMarkerStyle(3); hist_Esprime_Zq_160->SetLineStyle(1); hist_Esprime_Zq_160->SetLineWidth(2); hist_Esprime_Zq_160->SetMarkerSize(1);
	TH1F* hist_Esprime_WW_160 = (TH1F*)input_160_wiISR->Get("hist_Esprime_WW");
	hist_Esprime_WW_160->SetLineColor(kGreen+2); hist_Esprime_WW_160->SetMarkerColor(kGreen+2); hist_Esprime_WW_160->SetMarkerStyle(3); hist_Esprime_WW_160->SetLineStyle(2); hist_Esprime_WW_160->SetLineWidth(2); hist_Esprime_WW_160->SetMarkerSize(1);
	TH1F* hist_Esprime_ZZ_160 = (TH1F*)input_160_wiISR->Get("hist_Esprime_ZZ");
	hist_Esprime_ZZ_160->SetLineColor(kBlue+2); hist_Esprime_ZZ_160->SetMarkerColor(kBlue+2); hist_Esprime_ZZ_160->SetMarkerStyle(3); hist_Esprime_ZZ_160->SetLineStyle(2); hist_Esprime_ZZ_160->SetLineWidth(2); hist_Esprime_ZZ_160->SetMarkerSize(1);
	TH1F* hist_Esprime_tt_160 = (TH1F*)input_160_wiISR->Get("hist_Esprime_tt");
	hist_Esprime_tt_160->SetLineColor(kBlue+2); hist_Esprime_tt_160->SetMarkerColor(kBlue+2); hist_Esprime_tt_160->SetMarkerStyle(3); hist_Esprime_tt_160->SetLineStyle(1); hist_Esprime_tt_160->SetLineWidth(2); hist_Esprime_tt_160->SetMarkerSize(1);
	TH1F* hist_Esprime_HZ_160 = (TH1F*)input_160_wiISR->Get("hist_Esprime_HZ");
	hist_Esprime_HZ_160->SetLineColor(kGreen+2); hist_Esprime_HZ_160->SetMarkerColor(kGreen+2); hist_Esprime_HZ_160->SetMarkerStyle(53); hist_Esprime_HZ_160->SetLineStyle(1); hist_Esprime_HZ_160->SetLineWidth(2); hist_Esprime_HZ_160->SetMarkerSize(1);
	TH1F* hist_Esprime_HW_160 = (TH1F*)input_160_wiISR->Get("hist_Esprime_HW");
	hist_Esprime_HW_160->SetLineColor(kRed+2); hist_Esprime_HW_160->SetMarkerColor(kRed+2); hist_Esprime_HW_160->SetMarkerStyle(53); hist_Esprime_HW_160->SetLineStyle(1); hist_Esprime_HW_160->SetLineWidth(2); hist_Esprime_HW_160->SetMarkerSize(1);

	TH1F* hist_Esprime_Zq_240 = (TH1F*)input_240_wiISR->Get("hist_Esprime_Zq");
	hist_Esprime_Zq_240->SetLineColor(kYellow+2); hist_Esprime_Zq_240->SetMarkerColor(kYellow+2); hist_Esprime_Zq_240->SetMarkerStyle(3); hist_Esprime_Zq_240->SetLineStyle(1); hist_Esprime_Zq_240->SetLineWidth(2); hist_Esprime_Zq_240->SetMarkerSize(1);
	TH1F* hist_Esprime_WW_240 = (TH1F*)input_240_wiISR->Get("hist_Esprime_WW");
	hist_Esprime_WW_240->SetLineColor(kGreen+2); hist_Esprime_WW_240->SetMarkerColor(kGreen+2); hist_Esprime_WW_240->SetMarkerStyle(3); hist_Esprime_WW_240->SetLineStyle(2); hist_Esprime_WW_240->SetLineWidth(2); hist_Esprime_WW_240->SetMarkerSize(1);
	TH1F* hist_Esprime_ZZ_240 = (TH1F*)input_240_wiISR->Get("hist_Esprime_ZZ");
	hist_Esprime_ZZ_240->SetLineColor(kBlue+2); hist_Esprime_ZZ_240->SetMarkerColor(kBlue+2); hist_Esprime_ZZ_240->SetMarkerStyle(3); hist_Esprime_ZZ_240->SetLineStyle(2); hist_Esprime_ZZ_240->SetLineWidth(2); hist_Esprime_ZZ_240->SetMarkerSize(1);
	TH1F* hist_Esprime_tt_240 = (TH1F*)input_240_wiISR->Get("hist_Esprime_tt");
	hist_Esprime_tt_240->SetLineColor(kBlue+2); hist_Esprime_tt_240->SetMarkerColor(kBlue+2); hist_Esprime_tt_240->SetMarkerStyle(3); hist_Esprime_tt_240->SetLineStyle(1); hist_Esprime_tt_240->SetLineWidth(2); hist_Esprime_tt_240->SetMarkerSize(1);
	TH1F* hist_Esprime_HZ_240 = (TH1F*)input_240_wiISR->Get("hist_Esprime_HZ");
	hist_Esprime_HZ_240->SetLineColor(kGreen+2); hist_Esprime_HZ_240->SetMarkerColor(kGreen+2); hist_Esprime_HZ_240->SetMarkerStyle(53); hist_Esprime_HZ_240->SetLineStyle(1); hist_Esprime_HZ_240->SetLineWidth(2); hist_Esprime_HZ_240->SetMarkerSize(1);
	TH1F* hist_Esprime_HW_240 = (TH1F*)input_240_wiISR->Get("hist_Esprime_HW");
	hist_Esprime_HW_240->SetLineColor(kRed+2); hist_Esprime_HW_240->SetMarkerColor(kRed+2); hist_Esprime_HW_240->SetMarkerStyle(53); hist_Esprime_HW_240->SetLineStyle(1); hist_Esprime_HW_240->SetLineWidth(2); hist_Esprime_HW_240->SetMarkerSize(1);

	TH1F* hist_Esprime_Zq_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_Zq");
	hist_Esprime_Zq_365->SetLineColor(kRed+2); hist_Esprime_Zq_365->SetMarkerColor(kRed+1); hist_Esprime_Zq_365->SetMarkerStyle(21); hist_Esprime_Zq_365->SetLineStyle(1); hist_Esprime_Zq_365->SetLineWidth(2); hist_Esprime_Zq_365->SetMarkerSize(1);
	TH1F* hist_Esprime_WW_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_WW");
	hist_Esprime_WW_365->SetLineColor(kGreen+2); hist_Esprime_WW_365->SetMarkerColor(kGreen+1); hist_Esprime_WW_365->SetMarkerStyle(21); hist_Esprime_WW_365->SetLineStyle(1); hist_Esprime_WW_365->SetLineWidth(2); hist_Esprime_WW_365->SetMarkerSize(1);
	TH1F* hist_Esprime_ZZ_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_ZZ");
	hist_Esprime_ZZ_365->SetLineColor(kBlue+2); hist_Esprime_ZZ_365->SetMarkerColor(kBlue+1); hist_Esprime_ZZ_365->SetMarkerStyle(21); hist_Esprime_ZZ_365->SetLineStyle(1); hist_Esprime_ZZ_365->SetLineWidth(2); hist_Esprime_ZZ_365->SetMarkerSize(1);
	TH1F* hist_Esprime_tt_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_tt");
	hist_Esprime_tt_365->SetLineColor(kYellow+2); hist_Esprime_tt_365->SetMarkerColor(kYellow+1); hist_Esprime_tt_365->SetMarkerStyle(21); hist_Esprime_tt_365->SetLineStyle(1); hist_Esprime_tt_365->SetLineWidth(2); hist_Esprime_tt_365->SetMarkerSize(1);
	TH1F* hist_Esprime_HZ_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_HZ");
	hist_Esprime_HZ_365->SetLineColor(kMagenta+2); hist_Esprime_HZ_365->SetMarkerColor(kMagenta+1); hist_Esprime_HZ_365->SetMarkerStyle(21); hist_Esprime_HZ_365->SetLineStyle(1); hist_Esprime_HZ_365->SetLineWidth(2); hist_Esprime_HZ_365->SetMarkerSize(1);
	TH1F* hist_Esprime_HW_365 = (TH1F*)input_365_wiISR->Get("hist_Esprime_HW");
	hist_Esprime_HW_365->SetLineColor(kCyan+2); hist_Esprime_HW_365->SetMarkerColor(kCyan+1); hist_Esprime_HW_365->SetMarkerStyle(21); hist_Esprime_HW_365->SetLineStyle(1); hist_Esprime_HW_365->SetLineWidth(2); hist_Esprime_HW_365->SetMarkerSize(1);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_912_000 = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_000");
	hist_ThrPyth_912_000->SetLineColor(kBlack); hist_ThrPyth_912_000->SetMarkerColor(kBlack); hist_ThrPyth_912_000->SetMarkerStyle(kStar); hist_ThrPyth_912_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_912_100 = (TH1F*)input_912_wiISR->Get("hist_ThrPyth_100");
	hist_ThrPyth_912_100->SetLineColor(kRed+1); hist_ThrPyth_912_100->SetMarkerColor(kRed+1); hist_ThrPyth_912_100->SetMarkerStyle(kStar); hist_ThrPyth_912_100->SetLineWidth(2); 

	TH1F *hist_ThrPyth_160_000 = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_000");
	hist_ThrPyth_160_000->SetLineColor(kBlack); hist_ThrPyth_160_000->SetMarkerColor(kBlack); hist_ThrPyth_160_000->SetMarkerStyle(kStar); hist_ThrPyth_160_000->SetLineWidth(2); 	
	TH1F *hist_ThrPyth_160_100 = (TH1F*)input_160_wiISR->Get("hist_ThrPyth_100");
	hist_ThrPyth_160_100->SetLineColor(kRed+1); hist_ThrPyth_160_100->SetMarkerColor(kRed+1); hist_ThrPyth_160_100->SetMarkerStyle(kStar); hist_ThrPyth_160_100->SetLineWidth(2); 

	TH1F *hist_ThrPyth_240_000 = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_000");
	hist_ThrPyth_240_000->SetLineColor(kBlack); hist_ThrPyth_240_000->SetMarkerColor(kBlack); hist_ThrPyth_240_000->SetMarkerStyle(kStar); hist_ThrPyth_240_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_240_100 = (TH1F*)input_240_wiISR->Get("hist_ThrPyth_100");
	hist_ThrPyth_240_100->SetLineColor(kRed+1); hist_ThrPyth_240_100->SetMarkerColor(kRed+1); hist_ThrPyth_240_100->SetMarkerStyle(kStar); hist_ThrPyth_240_100->SetLineWidth(2); 

	TH1F *hist_ThrPyth_365_000 = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_000");
	hist_ThrPyth_365_000->SetLineColor(kBlack); hist_ThrPyth_365_000->SetMarkerColor(kBlack); hist_ThrPyth_365_000->SetMarkerStyle(kStar); hist_ThrPyth_365_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_365_100 = (TH1F*)input_365_wiISR->Get("hist_ThrPyth_100");
	hist_ThrPyth_365_100->SetLineColor(kRed+1); hist_ThrPyth_365_100->SetMarkerColor(kRed+1); hist_ThrPyth_365_100->SetMarkerStyle(kStar); hist_ThrPyth_365_100->SetLineWidth(2); 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_CprPyth_912_000 = (TH1F*)input_912_wiISR->Get("hist_CprPyth_000");
	hist_CprPyth_912_000->SetLineColor(kBlack); hist_CprPyth_912_000->SetMarkerColor(kBlack); hist_CprPyth_912_000->SetMarkerStyle(kStar); hist_CprPyth_912_000->SetLineWidth(2); 
	TH1F *hist_CprPyth_912_100 = (TH1F*)input_912_wiISR->Get("hist_CprPyth_100");
	hist_CprPyth_912_100->SetLineColor(kRed+1); hist_CprPyth_912_100->SetMarkerColor(kRed+1); hist_CprPyth_912_100->SetMarkerStyle(kStar); hist_CprPyth_912_100->SetLineWidth(2); 

	TH1F *hist_CprPyth_160_000 = (TH1F*)input_160_wiISR->Get("hist_CprPyth_000");
	hist_CprPyth_160_000->SetLineColor(kBlack); hist_CprPyth_160_000->SetMarkerColor(kBlack); hist_CprPyth_160_000->SetMarkerStyle(kStar); hist_CprPyth_160_000->SetLineWidth(2); 	
	TH1F *hist_CprPyth_160_100 = (TH1F*)input_160_wiISR->Get("hist_CprPyth_100");
	hist_CprPyth_160_100->SetLineColor(kRed+1); hist_CprPyth_160_100->SetMarkerColor(kRed+1); hist_CprPyth_160_100->SetMarkerStyle(kStar); hist_CprPyth_160_100->SetLineWidth(2); 

	TH1F *hist_CprPyth_240_000 = (TH1F*)input_240_wiISR->Get("hist_CprPyth_000");
	hist_CprPyth_240_000->SetLineColor(kBlack); hist_CprPyth_240_000->SetMarkerColor(kBlack); hist_CprPyth_240_000->SetMarkerStyle(kStar); hist_CprPyth_240_000->SetLineWidth(2); 
	TH1F *hist_CprPyth_240_100 = (TH1F*)input_240_wiISR->Get("hist_CprPyth_100");
	hist_CprPyth_240_100->SetLineColor(kRed+1); hist_CprPyth_240_100->SetMarkerColor(kRed+1); hist_CprPyth_240_100->SetMarkerStyle(kStar); hist_CprPyth_240_100->SetLineWidth(2); 

	TH1F *hist_CprPyth_365_000 = (TH1F*)input_365_wiISR->Get("hist_CprPyth_000");
	hist_CprPyth_365_000->SetLineColor(kBlack); hist_CprPyth_365_000->SetMarkerColor(kBlack); hist_CprPyth_365_000->SetMarkerStyle(kStar); hist_CprPyth_365_000->SetLineWidth(2); 
	TH1F *hist_CprPyth_365_100 = (TH1F*)input_365_wiISR->Get("hist_CprPyth_100");
	hist_CprPyth_365_100->SetLineColor(kRed+1); hist_CprPyth_365_100->SetMarkerColor(kRed+1); hist_CprPyth_365_100->SetMarkerStyle(kStar); hist_CprPyth_365_100->SetLineWidth(2); 	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_EgwiISR_912 = (TH1F*)input_912_wiISR->Get("hist_EgwiISR");
	hist_EgwiISR_912->SetLineColor(kBlack); hist_EgwiISR_912->SetMarkerColor(kBlack); hist_EgwiISR_912->SetMarkerStyle(kStar); hist_EgwiISR_912->SetLineWidth(2); 
	TH1F *hist_EgwoISR_912 = (TH1F*)input_912_wiISR->Get("hist_EgwoISR");
	hist_EgwoISR_912->SetLineColor(kRed+1); hist_EgwoISR_912->SetMarkerColor(kRed+1); hist_EgwoISR_912->SetMarkerStyle(kStar); hist_EgwoISR_912->SetLineWidth(2); 

	TH1F *hist_EgwiISR_160 = (TH1F*)input_160_wiISR->Get("hist_EgwiISR");
	hist_EgwiISR_160->SetLineColor(kBlack); hist_EgwiISR_160->SetMarkerColor(kBlack); hist_EgwiISR_160->SetMarkerStyle(kStar); hist_EgwiISR_160->SetLineWidth(2); 	
	TH1F *hist_EgwoISR_160 = (TH1F*)input_160_wiISR->Get("hist_EgwoISR");
	hist_EgwoISR_160->SetLineColor(kRed+1); hist_EgwoISR_160->SetMarkerColor(kRed+1); hist_EgwoISR_160->SetMarkerStyle(kStar); hist_EgwoISR_160->SetLineWidth(2); 

	TH1F *hist_EgwiISR_240 = (TH1F*)input_240_wiISR->Get("hist_EgwiISR");
	hist_EgwiISR_240->SetLineColor(kBlack); hist_EgwiISR_240->SetMarkerColor(kBlack); hist_EgwiISR_240->SetMarkerStyle(kStar); hist_EgwiISR_240->SetLineWidth(2); 
	TH1F *hist_EgwoISR_240 = (TH1F*)input_240_wiISR->Get("hist_EgwoISR");
	hist_EgwoISR_240->SetLineColor(kRed+1); hist_EgwoISR_240->SetMarkerColor(kRed+1); hist_EgwoISR_240->SetMarkerStyle(kStar); hist_EgwoISR_240->SetLineWidth(2); 

	TH1F *hist_EgwiISR_365 = (TH1F*)input_365_wiISR->Get("hist_EgwiISR");
	hist_EgwiISR_365->SetLineColor(kBlack); hist_EgwiISR_365->SetMarkerColor(kBlack); hist_EgwiISR_365->SetMarkerStyle(kStar); hist_EgwiISR_365->SetLineWidth(2); 
	TH1F *hist_EgwoISR_365 = (TH1F*)input_365_wiISR->Get("hist_EgwoISR");
	hist_EgwoISR_365->SetLineColor(kRed+1); hist_EgwoISR_365->SetMarkerColor(kRed+1); hist_EgwoISR_365->SetMarkerStyle(kStar); hist_EgwoISR_365->SetLineWidth(2); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising by area under histogram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	// hist_Esprime_912->Scale(1.0/hist_Esprime_912->Integral());
	// hist_Esprime_160->Scale(1.0/hist_Esprime_160->Integral());
	// hist_Esprime_240->Scale(1.0/hist_Esprime_240->Integral());
	// hist_Esprime_365->Scale(1.0/hist_Esprime_365->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912_100->Scale(1.0/hist_ThrPyth_912_100->Integral("width"));
	hist_ThrPyth_160_100->Scale(1.0/hist_ThrPyth_160_100->Integral("width"));
	hist_ThrPyth_240_100->Scale(1.0/hist_ThrPyth_240_100->Integral("width"));
	hist_ThrPyth_365_100->Scale(1.0/hist_ThrPyth_365_100->Integral("width"));

	hist_CprPyth_912_100->Scale(1.0/hist_CprPyth_912_100->Integral("width"));
	hist_CprPyth_160_100->Scale(1.0/hist_CprPyth_160_100->Integral("width"));
	hist_CprPyth_240_100->Scale(1.0/hist_CprPyth_240_100->Integral("width"));
	hist_CprPyth_365_100->Scale(1.0/hist_CprPyth_365_100->Integral("width"));

	hist_ThrPyth_912_000->Scale(1.0/hist_ThrPyth_912_000->Integral("width"));
	hist_ThrPyth_160_000->Scale(1.0/hist_ThrPyth_160_000->Integral("width"));
	hist_ThrPyth_240_000->Scale(1.0/hist_ThrPyth_240_000->Integral("width"));
	hist_ThrPyth_365_000->Scale(1.0/hist_ThrPyth_365_000->Integral("width"));

	hist_CprPyth_912_000->Scale(1.0/hist_CprPyth_912_000->Integral("width"));
	hist_CprPyth_160_000->Scale(1.0/hist_CprPyth_160_000->Integral("width"));
	hist_CprPyth_240_000->Scale(1.0/hist_CprPyth_240_000->Integral("width"));
	hist_CprPyth_365_000->Scale(1.0/hist_CprPyth_365_000->Integral("width"));

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

	hist_ThrPyth_912_000->SetStats(kFALSE);
	hist_ThrPyth_160_000->SetStats(kFALSE);
	hist_ThrPyth_240_000->SetStats(kFALSE);
	hist_ThrPyth_365_000->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_CprPyth_912_000->SetStats(kFALSE);
	hist_CprPyth_160_000->SetStats(kFALSE);
	hist_CprPyth_240_000->SetStats(kFALSE);
	hist_CprPyth_365_000->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_NumbISR_912->SetTitle("");
	hist_Esprime_912->SetTitle("");
	hist_Esprime_160->SetTitle("");
	hist_Esprime_240->SetTitle("");
	hist_Esprime_365->SetTitle("");

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
 
	hist_ThrPyth_912_000->GetXaxis()->SetLabelSize(0.07); hist_ThrPyth_912_000->GetYaxis()->SetLabelSize(0.07); hist_ThrPyth_912_000->GetYaxis()->SetTitleSize(0.08); hist_ThrPyth_912_000->GetXaxis()->SetTitleSize(0.08); 
	hist_ThrPyth_160_000->GetXaxis()->SetLabelSize(0.07); hist_ThrPyth_160_000->GetYaxis()->SetLabelSize(0.07); hist_ThrPyth_160_000->GetYaxis()->SetTitleSize(0.08); hist_ThrPyth_160_000->GetXaxis()->SetTitleSize(0.08); 
	hist_ThrPyth_240_000->GetXaxis()->SetLabelSize(0.07); hist_ThrPyth_240_000->GetYaxis()->SetLabelSize(0.07); hist_ThrPyth_240_000->GetYaxis()->SetTitleSize(0.08); hist_ThrPyth_240_000->GetXaxis()->SetTitleSize(0.08); 
	hist_ThrPyth_365_000->GetXaxis()->SetLabelSize(0.07); hist_ThrPyth_365_000->GetYaxis()->SetLabelSize(0.07); hist_ThrPyth_365_000->GetYaxis()->SetTitleSize(0.08); hist_ThrPyth_365_000->GetXaxis()->SetTitleSize(0.08); 

	hist_CprPyth_912_000->GetXaxis()->SetLabelSize(0.07); hist_CprPyth_912_000->GetYaxis()->SetLabelSize(0.07); hist_CprPyth_912_000->GetYaxis()->SetTitleSize(0.08); hist_CprPyth_912_000->GetXaxis()->SetTitleSize(0.08); 
	hist_CprPyth_160_000->GetXaxis()->SetLabelSize(0.07); hist_CprPyth_160_000->GetYaxis()->SetLabelSize(0.07); hist_CprPyth_160_000->GetYaxis()->SetTitleSize(0.08); hist_CprPyth_160_000->GetXaxis()->SetTitleSize(0.08); 
	hist_CprPyth_240_000->GetXaxis()->SetLabelSize(0.07); hist_CprPyth_240_000->GetYaxis()->SetLabelSize(0.07); hist_CprPyth_240_000->GetYaxis()->SetTitleSize(0.08); hist_CprPyth_240_000->GetXaxis()->SetTitleSize(0.08); 
	hist_CprPyth_365_000->GetXaxis()->SetLabelSize(0.07); hist_CprPyth_365_000->GetYaxis()->SetLabelSize(0.07); hist_CprPyth_365_000->GetYaxis()->SetTitleSize(0.08); hist_CprPyth_365_000->GetXaxis()->SetTitleSize(0.08); 
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// hist_ThrPyth_912_000->GetYaxis()->SetTitle("#");
	// hist_ThrPyth_160_000->GetYaxis()->SetTitle("#");
	// hist_ThrPyth_240_000->GetYaxis()->SetTitle("#");
	// hist_ThrPyth_365_000->GetYaxis()->SetTitle("#");

	// hist_CprPyth_912_000->GetYaxis()->SetTitle("#");
	// hist_CprPyth_160_000->GetYaxis()->SetTitle("#");
	// hist_CprPyth_240_000->GetYaxis()->SetTitle("#");
	// hist_CprPyth_365_000->GetYaxis()->SetTitle("#");

	// Create canvas
	TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 1000, 1300);

	// Add legend
	TLegend* lg2 = new TLegend(0.22, 0.20, 0.45, 0.40);
	lg2->AddEntry(hist_ThrPyth_912_000, "ee(#gamma)#rightarrow#gamma*/Z", "L");
	lg2->AddEntry(hist_ThrPyth_912_100, "ee#rightarrow#gamma*/Z", "L");
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
		gPad->SetTopMargin(0.04);
		gPad->SetBottomMargin(0.16);
		gPad->SetLeftMargin(0.18);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		gPad->SetLogy();
	}

	cv2->cd(1);
	hist_ThrPyth_912_000->Draw("HIST");
	hist_ThrPyth_912_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(3);
	hist_ThrPyth_160_000->Draw("HIST");
	hist_ThrPyth_160_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(5);
	hist_ThrPyth_240_000->Draw("HIST");
	hist_ThrPyth_240_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(7);
	hist_ThrPyth_365_000->Draw("HIST");
	hist_ThrPyth_365_100->Draw("HIST SAME");
	lg2->Draw("SAME");

	cv2->cd(2);
	hist_CprPyth_912_000->Draw("HIST");
	hist_CprPyth_912_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(4);
	hist_CprPyth_160_000->Draw("HIST");
	hist_CprPyth_160_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(6);
	hist_CprPyth_240_000->Draw("HIST");
	hist_CprPyth_240_100->Draw("HIST SAME");
	lg2->Draw("SAME");
	cv2->cd(8);
	hist_CprPyth_365_000->Draw("HIST");
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

	hist_Esprime_365->GetYaxis()->SetTitle("#");

	// Create canvas
	TCanvas* cv3 = new TCanvas("cv3", "FCC-ee ISR Studies", 1000, 800);

	// Add legend
	TLegend* lg3 = new TLegend(0.13, 0.65, 0.25, 0.95);
	lg3->AddEntry(hist_Esprime_365, "ee#rightarrowq#bar{q}", "P");
	lg3->AddEntry(hist_Esprime_Zq_365, "ee#rightarrow#gamma*/Z", "P");
	lg3->AddEntry(hist_Esprime_WW_365, "ee#rightarrowWW", "P");
	lg3->AddEntry(hist_Esprime_ZZ_365, "ee#rightarrowZZ", "P");
	lg3->AddEntry(hist_Esprime_tt_365, "ee#rightarrowt#bar{t}", "P");
	lg3->AddEntry(hist_Esprime_HZ_365, "ee#rightarrowZH", "P");
	lg3->AddEntry(hist_Esprime_HW_365, "ee#rightarrow#nu#bar{#nu}H", "P");
	lg3->SetTextSize(0.03);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv3->SetMargin(0, 0, 0, 0); 
	gPad->SetTopMargin(0.025);
	gPad->SetBottomMargin(0.10);
	gPad->SetLeftMargin(0.10);
	gPad->SetRightMargin(0.01);
	gPad->SetTickx(); gPad->SetTicky();
	gPad->SetLogy();

	hist_Esprime_365->SetFillStyle(3001); hist_Esprime_365->SetFillColor(kBlack); 
	hist_Esprime_Zq_365->SetFillStyle(3001); hist_Esprime_Zq_365->SetFillColor(kRed); 
	hist_Esprime_WW_365->SetFillStyle(3001); hist_Esprime_WW_365->SetFillColor(kGreen); 
	hist_Esprime_ZZ_365->SetFillStyle(3001); hist_Esprime_ZZ_365->SetFillColor(kBlue); 
	hist_Esprime_tt_365->SetFillStyle(3001); hist_Esprime_tt_365->SetFillColor(kYellow); 
	hist_Esprime_HZ_365->SetFillStyle(3001); hist_Esprime_HZ_365->SetFillColor(kMagenta+1); 
	hist_Esprime_HW_365->SetFillStyle(3001); hist_Esprime_HW_365->SetFillColor(kCyan+1); 

	hist_Esprime_365->Draw("HIST");
	hist_Esprime_Zq_365->Draw("HIST SAME");
	hist_Esprime_WW_365->Draw("HIST SAME");
	hist_Esprime_ZZ_365->Draw("HIST SAME");
	hist_Esprime_tt_365->Draw("HIST SAME");
	hist_Esprime_HZ_365->Draw("HIST SAME");
	hist_Esprime_HW_365->Draw("HIST SAME");
	lg3->Draw("SAME");

	// Set limits
	hist_Esprime_365->GetYaxis()->SetRangeUser(1E0,1E6);
	hist_Esprime_365->GetXaxis()->SetRangeUser(0,400);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv3->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// hist_EgwiISR_912->SetStats(kFALSE);
	// hist_EgwiISR_912->SetTitle("");
	// hist_EgwiISR_160->SetStats(kFALSE);
	// hist_EgwiISR_160->SetTitle("");
	// hist_EgwiISR_240->SetStats(kFALSE);
	// hist_EgwiISR_240->SetTitle("");
	// hist_EgwiISR_365->SetStats(kFALSE);
	// hist_EgwiISR_365->SetTitle("");

	// // Create canvas
	// TCanvas* cv4 = new TCanvas("cv4", "FCC-ee ISR Studies", 2000, 800);

	// // Add legend
	// TLegend* lg4 = new TLegend(0.60, 0.80, 0.90, 0.90);
	// lg4->AddEntry(hist_EgwiISR_912, "ISR", "L");
	// lg4->AddEntry(hist_EgwoISR_912, "non-ISR", "L");
	// lg4->SetTextSize(0.06);

	// // Beautify
	// gStyle->SetErrorX(0.000000001);
	// gStyle->SetLabelSize(0.05, "X");
	// gStyle->SetLabelSize(0.05, "Y");
	// gStyle->SetTitleSize(0.06, "X");
	// gStyle->SetTitleSize(0.06, "Y");
	// cv4->SetMargin(0, 0, 0, 0); 
	// cv4->Divide(4,1);
	// for (int i = 1; i <= 4; i++) {
	// 	cv4->cd(i);
	// 	gPad->SetTopMargin(0.04);
	// 	gPad->SetBottomMargin(0.16);
	// 	gPad->SetLeftMargin(0.18);
	// 	gPad->SetRightMargin(0.04);
	// 	gPad->SetTickx(); gPad->SetTicky();
	// 	gPad->SetLogy();
	// }

	// cv4->cd(1);
	// hist_EgwiISR_912->Draw("HIST");
	// hist_EgwoISR_912->Draw("HIST SAME");
	// lg4->Draw("SAME");
	// cv4->cd(2);
	// hist_EgwiISR_160->Draw("HIST");
	// hist_EgwoISR_160->Draw("HIST SAME");
	// lg4->Draw("SAME");
	// cv4->cd(3);
	// hist_EgwiISR_240->Draw("HIST");
	// hist_EgwoISR_240->Draw("HIST SAME");
	// lg4->Draw("SAME");
	// cv4->cd(4);
	// hist_EgwiISR_365->Draw("HIST");
	// hist_EgwoISR_365->Draw("HIST SAME");
	// lg4->Draw("SAME");

	// // Set limits
	// hist_EgwiISR_912->GetYaxis()->SetRangeUser(1E0,1E6);
	// hist_EgwiISR_912->GetXaxis()->SetRangeUser(0,50);
	// hist_EgwiISR_160->GetYaxis()->SetRangeUser(1E0,1E6);
	// hist_EgwiISR_160->GetXaxis()->SetRangeUser(0,100);
	// hist_EgwiISR_240->GetYaxis()->SetRangeUser(1E0,1E6);
	// hist_EgwiISR_240->GetXaxis()->SetRangeUser(0,150);
	// hist_EgwiISR_365->GetYaxis()->SetRangeUser(1E0,1E6);
	// hist_EgwiISR_365->GetXaxis()->SetRangeUser(0,200);

	// // Modify stat-box
	// gStyle->SetOptStat();
	// // Update canvas
	// cv4->Modified();

}