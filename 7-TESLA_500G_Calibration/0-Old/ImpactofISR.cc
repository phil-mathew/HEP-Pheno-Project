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
// Header
using namespace std;

// Code
void ImpactofISR() {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_912 = new TFile("cut_FCC912.root", "READ");
	TFile *input_160 = new TFile("cut_FCC160.root", "READ");
	TFile *input_180 = new TFile("cut_FCC180.root", "READ");
	TFile *input_240 = new TFile("cut_FCC240.root", "READ");
	TFile *input_365 = new TFile("cut_FCC365.root", "READ");
	TFile *input_500 = new TFile("cut_FCC500.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Impact of centre-of-mass on ISR photons and ISR energy
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_NumbISR_912 = (TH1F*)input_912->Get("hist_NumbISR");
	hist_NumbISR_912->SetLineColor(kRed+2); hist_NumbISR_912->SetMarkerColor(kRed+2); hist_NumbISR_912->SetMarkerStyle(kStar); hist_NumbISR_912->SetLineWidth(2); hist_NumbISR_912->SetStats(kFALSE);
	TH1F *hist_NumbISR_160 = (TH1F*)input_160->Get("hist_NumbISR");
	hist_NumbISR_160->SetLineColor(kGreen+2); hist_NumbISR_160->SetMarkerColor(kGreen+2); hist_NumbISR_160->SetMarkerStyle(kStar); hist_NumbISR_160->SetLineWidth(2); hist_NumbISR_160->SetStats(kFALSE);
	TH1F *hist_NumbISR_240 = (TH1F*)input_240->Get("hist_NumbISR");
	hist_NumbISR_240->SetLineColor(kYellow+2); hist_NumbISR_240->SetMarkerColor(kYellow+2); hist_NumbISR_240->SetMarkerStyle(kStar); hist_NumbISR_240->SetLineWidth(2); hist_NumbISR_240->SetStats(kFALSE);
	TH1F *hist_NumbISR_365 = (TH1F*)input_365->Get("hist_NumbISR");
	hist_NumbISR_365->SetLineColor(kBlue+2); hist_NumbISR_365->SetMarkerColor(kBlue+2); hist_NumbISR_365->SetMarkerStyle(kStar); hist_NumbISR_365->SetLineWidth(2); hist_NumbISR_365->SetStats(kFALSE);

	TH1F *hist_EmaxISR_912 = (TH1F*)input_912->Get("hist_EmaxISR");
	hist_EmaxISR_912->SetLineColor(kRed+2); hist_EmaxISR_912->SetMarkerColor(kRed+2); hist_EmaxISR_912->SetMarkerStyle(kStar); hist_EmaxISR_912->SetLineWidth(3); hist_EmaxISR_912->SetStats(kFALSE);
	TH1F *hist_EmaxISR_160 = (TH1F*)input_160->Get("hist_EmaxISR");
	hist_EmaxISR_160->SetLineColor(kGreen+2); hist_EmaxISR_160->SetMarkerColor(kGreen+2); hist_EmaxISR_160->SetMarkerStyle(kStar); hist_EmaxISR_160->SetLineWidth(3); hist_EmaxISR_160->SetStats(kFALSE);
	TH1F *hist_EmaxISR_240 = (TH1F*)input_240->Get("hist_EmaxISR");
	hist_EmaxISR_240->SetLineColor(kYellow+2); hist_EmaxISR_240->SetMarkerColor(kYellow+2); hist_EmaxISR_240->SetMarkerStyle(kStar); hist_EmaxISR_240->SetLineWidth(3); hist_EmaxISR_240->SetStats(kFALSE);
	TH1F *hist_EmaxISR_365 = (TH1F*)input_365->Get("hist_EmaxISR");
	hist_EmaxISR_365->SetLineColor(kBlue+2); hist_EmaxISR_365->SetMarkerColor(kBlue+2); hist_EmaxISR_365->SetMarkerStyle(kStar); hist_EmaxISR_365->SetLineWidth(3); hist_EmaxISR_365->SetStats(kFALSE);

	TH1F *hist_Esprime_912 = (TH1F*)input_912->Get("hist_Esprime_al");
	hist_Esprime_912->SetLineColor(kRed+2); hist_Esprime_912->SetMarkerColor(kRed+2); hist_Esprime_912->SetMarkerStyle(kStar); hist_Esprime_912->SetLineWidth(3); hist_Esprime_912->SetStats(kFALSE);
	TH1F *hist_Esprime_160 = (TH1F*)input_160->Get("hist_Esprime_al");
	hist_Esprime_160->SetLineColor(kGreen+2); hist_Esprime_160->SetMarkerColor(kGreen+2); hist_Esprime_160->SetMarkerStyle(kStar); hist_Esprime_160->SetLineWidth(3); hist_Esprime_160->SetStats(kFALSE);
	TH1F *hist_Esprime_240 = (TH1F*)input_240->Get("hist_Esprime_al");
	hist_Esprime_240->SetLineColor(kYellow+2); hist_Esprime_240->SetMarkerColor(kYellow+2); hist_Esprime_240->SetMarkerStyle(kStar); hist_Esprime_240->SetLineWidth(3); hist_Esprime_240->SetStats(kFALSE);
	TH1F *hist_Esprime_365 = (TH1F*)input_365->Get("hist_Esprime_al");
	hist_Esprime_365->SetLineColor(kBlue+2); hist_Esprime_365->SetMarkerColor(kBlue+2); hist_Esprime_365->SetMarkerStyle(kStar); hist_Esprime_365->SetLineWidth(3); hist_Esprime_365->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalisation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// hist_EmaxISR_912->Scale(1.0/hist_EmaxISR_912->Integral());
	// hist_EmaxISR_160->Scale(1.0/hist_EmaxISR_160->Integral());
	// hist_EmaxISR_240->Scale(1.0/hist_EmaxISR_240->Integral());
	// hist_EmaxISR_365->Scale(1.0/hist_EmaxISR_365->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// hist_Esprime_LEP->GetXaxis()->SetTitle("#sqrt{s} /#sqrt{s'}");
	// hist_Esprime_LEP->GetYaxis()->SetTitle("P(#sqrt{s} /#sqrt{s'})");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg1 = new TLegend(0.64, 0.65, 0.87, 0.87);
	lg1->AddEntry(hist_EmaxISR_912, "#sqrt{s} = 91.2 GeV", "p");
	lg1->AddEntry(hist_EmaxISR_160, "#sqrt{s} = 160 GeV", "p");
	lg1->AddEntry(hist_EmaxISR_240, "#sqrt{s} = 240 GeV", "p");
	lg1->AddEntry(hist_EmaxISR_365, "#sqrt{s} = 500 GeV", "p");
	lg1->SetTextSize(0.03);
	
	// Create canvas
	TCanvas* cv1 = new TCanvas("cv1", "FCC-ee ISR Studies", 1200, 1000);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	cv1->Divide(2,2);
	cv1->cd(1)->SetLeftMargin(0.15);
	cv1->cd(1)->SetLogy();
	cv1->cd(1)->SetTickx(); cv1->cd(1)->SetTicky();
	cv1->cd(1)->SetGridx(); cv1->cd(1)->SetGridy();
	cv1->cd(2)->SetLeftMargin(0.15);
	cv1->cd(2)->SetLogy();
	cv1->cd(2)->SetTickx(); cv1->cd(2)->SetTicky();
	cv1->cd(2)->SetGridx(); cv1->cd(2)->SetGridy();
	cv1->cd(3)->SetLeftMargin(0.15);
	cv1->cd(3)->SetLogy();
	cv1->cd(3)->SetTickx(); cv1->cd(3)->SetTicky();
	cv1->cd(3)->SetGridx(); cv1->cd(3)->SetGridy();
	cv1->cd(4)->SetLeftMargin(0.15);
	cv1->cd(4)->SetLogy();
	cv1->cd(4)->SetTickx(); cv1->cd(4)->SetTicky();
	cv1->cd(4)->SetGridx(); cv1->cd(4)->SetGridy();

	// Draw
	cv1->cd(2);
	hist_EmaxISR_912->Draw("P");
	hist_EmaxISR_160->Draw("P SAME");
	hist_EmaxISR_240->Draw("P SAME");
	hist_EmaxISR_365->Draw("P SAME");
	lg1->Draw("SAME");

	cv1->cd(3);
	hist_NumbISR_912->Draw("");
	hist_NumbISR_160->Draw("SAME");
	hist_NumbISR_240->Draw("SAME");
	hist_NumbISR_365->Draw("SAME");
	lg1->Draw("SAME");

	cv1->cd(4);
	hist_Esprime_912->Draw("P");
	hist_Esprime_160->Draw("P SAME");
	hist_Esprime_240->Draw("P SAME");
	hist_Esprime_365->Draw("P SAME");
	lg1->Draw("SAME");

	// Set limits
	hist_EmaxISR_912->GetYaxis()->SetRangeUser(1E-1,1E8);
	hist_NumbISR_912->GetYaxis()->SetRangeUser(1E4,1E7);
	hist_Esprime_912->GetYaxis()->SetRangeUser(1E-1,1E7);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv1->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Impact of ISR Cuts on Thrust/Nch
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_ThrPyth_912_000 = (TH1F*)input_912->Get("hist_ThrPyth_000");
	hist_ThrPyth_912_000->SetLineColor(kRed+2); hist_ThrPyth_912_000->SetMarkerColor(kRed+2); hist_ThrPyth_912_000->SetMarkerStyle(kStar); hist_ThrPyth_912_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_912_060 = (TH1F*)input_912->Get("hist_ThrPyth_060");
	hist_ThrPyth_912_060->SetLineColor(kGreen+2); hist_ThrPyth_912_060->SetMarkerColor(kGreen+2); hist_ThrPyth_912_060->SetMarkerStyle(kStar); hist_ThrPyth_912_060->SetLineWidth(2); 
	TH1F *hist_ThrPyth_912_085 = (TH1F*)input_912->Get("hist_ThrPyth_085");
	hist_ThrPyth_912_085->SetLineColor(kYellow+2); hist_ThrPyth_912_085->SetMarkerColor(kYellow+2); hist_ThrPyth_912_085->SetMarkerStyle(kStar); hist_ThrPyth_912_085->SetLineWidth(2); 
	TH1F *hist_ThrPyth_912_100 = (TH1F*)input_912->Get("hist_ThrPyth_100");
	hist_ThrPyth_912_100->SetLineColor(kBlue+2); hist_ThrPyth_912_100->SetMarkerColor(kBlue+2); hist_ThrPyth_912_100->SetMarkerStyle(kStar); hist_ThrPyth_912_100->SetLineWidth(2); 

	TH1F *hist_nHadron_912_000 = (TH1F*)input_912->Get("KNOO_nHadron_000");
	hist_nHadron_912_000->SetLineColor(kRed+2); hist_nHadron_912_000->SetMarkerColor(kRed+2); hist_nHadron_912_000->SetMarkerStyle(kStar); hist_nHadron_912_000->SetLineWidth(2); 
	TH1F *hist_nHadron_912_060 = (TH1F*)input_912->Get("KNOO_nHadron_060");
	hist_nHadron_912_060->SetLineColor(kGreen+2); hist_nHadron_912_060->SetMarkerColor(kGreen+2); hist_nHadron_912_060->SetMarkerStyle(kStar); hist_nHadron_912_060->SetLineWidth(2); 
	TH1F *hist_nHadron_912_085 = (TH1F*)input_912->Get("KNOO_nHadron_085");
	hist_nHadron_912_085->SetLineColor(kYellow+2); hist_nHadron_912_085->SetMarkerColor(kYellow+2); hist_nHadron_912_085->SetMarkerStyle(kStar); hist_nHadron_912_085->SetLineWidth(2); 
	TH1F *hist_nHadron_912_100 = (TH1F*)input_912->Get("KNOO_nHadron_100");
	hist_nHadron_912_100->SetLineColor(kBlue+2); hist_nHadron_912_100->SetMarkerColor(kBlue+2); hist_nHadron_912_100->SetMarkerStyle(kStar); hist_nHadron_912_100->SetLineWidth(2); 

	TH1F *hist_ThrPyth_160_000 = (TH1F*)input_160->Get("hist_ThrPyth_000");
	hist_ThrPyth_160_000->SetLineColor(kRed+2); hist_ThrPyth_160_000->SetMarkerColor(kRed+2); hist_ThrPyth_160_000->SetMarkerStyle(kStar); hist_ThrPyth_160_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_160_060 = (TH1F*)input_160->Get("hist_ThrPyth_060");
	hist_ThrPyth_160_060->SetLineColor(kGreen+2); hist_ThrPyth_160_060->SetMarkerColor(kGreen+2); hist_ThrPyth_160_060->SetMarkerStyle(kStar); hist_ThrPyth_160_060->SetLineWidth(2); 
	TH1F *hist_ThrPyth_160_085 = (TH1F*)input_160->Get("hist_ThrPyth_085");
	hist_ThrPyth_160_085->SetLineColor(kYellow+2); hist_ThrPyth_160_085->SetMarkerColor(kYellow+2); hist_ThrPyth_160_085->SetMarkerStyle(kStar); hist_ThrPyth_160_085->SetLineWidth(2); 
	TH1F *hist_ThrPyth_160_100 = (TH1F*)input_160->Get("hist_ThrPyth_100");
	hist_ThrPyth_160_100->SetLineColor(kBlue+2); hist_ThrPyth_160_100->SetMarkerColor(kBlue+2); hist_ThrPyth_160_100->SetMarkerStyle(kStar); hist_ThrPyth_160_100->SetLineWidth(2); 

	TH1F *hist_nHadron_160_000 = (TH1F*)input_160->Get("KNOO_nHadron_000");
	hist_nHadron_160_000->SetLineColor(kRed+2); hist_nHadron_160_000->SetMarkerColor(kRed+2); hist_nHadron_160_000->SetMarkerStyle(kStar); hist_nHadron_160_000->SetLineWidth(2); 
	TH1F *hist_nHadron_160_060 = (TH1F*)input_160->Get("KNOO_nHadron_060");
	hist_nHadron_160_060->SetLineColor(kGreen+2); hist_nHadron_160_060->SetMarkerColor(kGreen+2); hist_nHadron_160_060->SetMarkerStyle(kStar); hist_nHadron_160_060->SetLineWidth(2); 
	TH1F *hist_nHadron_160_085 = (TH1F*)input_160->Get("KNOO_nHadron_085");
	hist_nHadron_160_085->SetLineColor(kYellow+2); hist_nHadron_160_085->SetMarkerColor(kYellow+2); hist_nHadron_160_085->SetMarkerStyle(kStar); hist_nHadron_160_085->SetLineWidth(2); 
	TH1F *hist_nHadron_160_100 = (TH1F*)input_160->Get("KNOO_nHadron_100");
	hist_nHadron_160_100->SetLineColor(kBlue+2); hist_nHadron_160_100->SetMarkerColor(kBlue+2); hist_nHadron_160_100->SetMarkerStyle(kStar); hist_nHadron_160_100->SetLineWidth(2); 

	TH1F *hist_ThrPyth_180_000 = (TH1F*)input_180->Get("hist_ThrPyth_000");
	hist_ThrPyth_180_000->SetLineColor(kRed+2); hist_ThrPyth_180_000->SetMarkerColor(kRed+2); hist_ThrPyth_180_000->SetMarkerStyle(kStar); hist_ThrPyth_180_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_180_060 = (TH1F*)input_180->Get("hist_ThrPyth_060");
	hist_ThrPyth_180_060->SetLineColor(kGreen+2); hist_ThrPyth_180_060->SetMarkerColor(kGreen+2); hist_ThrPyth_180_060->SetMarkerStyle(kStar); hist_ThrPyth_180_060->SetLineWidth(2); 
	TH1F *hist_ThrPyth_180_085 = (TH1F*)input_180->Get("hist_ThrPyth_085");
	hist_ThrPyth_180_085->SetLineColor(kYellow+2); hist_ThrPyth_180_085->SetMarkerColor(kYellow+2); hist_ThrPyth_180_085->SetMarkerStyle(kStar); hist_ThrPyth_180_085->SetLineWidth(2); 
	TH1F *hist_ThrPyth_180_100 = (TH1F*)input_180->Get("hist_ThrPyth_100");
	hist_ThrPyth_180_100->SetLineColor(kBlue+2); hist_ThrPyth_180_100->SetMarkerColor(kBlue+2); hist_ThrPyth_180_100->SetMarkerStyle(kStar); hist_ThrPyth_180_100->SetLineWidth(2); 

	TH1F *hist_nHadron_180_000 = (TH1F*)input_180->Get("KNOO_nHadron_000");
	hist_nHadron_180_000->SetLineColor(kRed+2); hist_nHadron_180_000->SetMarkerColor(kRed+2); hist_nHadron_180_000->SetMarkerStyle(kStar); hist_nHadron_180_000->SetLineWidth(2); 
	TH1F *hist_nHadron_180_060 = (TH1F*)input_180->Get("KNOO_nHadron_060");
	hist_nHadron_180_060->SetLineColor(kGreen+2); hist_nHadron_180_060->SetMarkerColor(kGreen+2); hist_nHadron_180_060->SetMarkerStyle(kStar); hist_nHadron_180_060->SetLineWidth(2); 
	TH1F *hist_nHadron_180_085 = (TH1F*)input_180->Get("KNOO_nHadron_085");
	hist_nHadron_180_085->SetLineColor(kYellow+2); hist_nHadron_180_085->SetMarkerColor(kYellow+2); hist_nHadron_180_085->SetMarkerStyle(kStar); hist_nHadron_180_085->SetLineWidth(2); 
	TH1F *hist_nHadron_180_100 = (TH1F*)input_180->Get("KNOO_nHadron_100");
	hist_nHadron_180_100->SetLineColor(kBlue+2); hist_nHadron_180_100->SetMarkerColor(kBlue+2); hist_nHadron_180_100->SetMarkerStyle(kStar); hist_nHadron_180_100->SetLineWidth(2); 

	TH1F *hist_ThrPyth_240_000 = (TH1F*)input_240->Get("hist_ThrPyth_000");
	hist_ThrPyth_240_000->SetLineColor(kRed+2); hist_ThrPyth_240_000->SetMarkerColor(kRed+2); hist_ThrPyth_240_000->SetMarkerStyle(kStar); hist_ThrPyth_240_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_240_060 = (TH1F*)input_240->Get("hist_ThrPyth_060");
	hist_ThrPyth_240_060->SetLineColor(kGreen+2); hist_ThrPyth_240_060->SetMarkerColor(kGreen+2); hist_ThrPyth_240_060->SetMarkerStyle(kStar); hist_ThrPyth_240_060->SetLineWidth(2); 
	TH1F *hist_ThrPyth_240_085 = (TH1F*)input_240->Get("hist_ThrPyth_085");
	hist_ThrPyth_240_085->SetLineColor(kYellow+2); hist_ThrPyth_240_085->SetMarkerColor(kYellow+2); hist_ThrPyth_240_085->SetMarkerStyle(kStar); hist_ThrPyth_240_085->SetLineWidth(2); 
	TH1F *hist_ThrPyth_240_100 = (TH1F*)input_240->Get("hist_ThrPyth_100");
	hist_ThrPyth_240_100->SetLineColor(kBlue+2); hist_ThrPyth_240_100->SetMarkerColor(kBlue+2); hist_ThrPyth_240_100->SetMarkerStyle(kStar); hist_ThrPyth_240_100->SetLineWidth(2); 

	TH1F *hist_nHadron_240_000 = (TH1F*)input_240->Get("KNOO_nHadron_000");
	hist_nHadron_240_000->SetLineColor(kRed+2); hist_nHadron_240_000->SetMarkerColor(kRed+2); hist_nHadron_240_000->SetMarkerStyle(kStar); hist_nHadron_240_000->SetLineWidth(2); 
	TH1F *hist_nHadron_240_060 = (TH1F*)input_240->Get("KNOO_nHadron_060");
	hist_nHadron_240_060->SetLineColor(kGreen+2); hist_nHadron_240_060->SetMarkerColor(kGreen+2); hist_nHadron_240_060->SetMarkerStyle(kStar); hist_nHadron_240_060->SetLineWidth(2); 
	TH1F *hist_nHadron_240_085 = (TH1F*)input_240->Get("KNOO_nHadron_085");
	hist_nHadron_240_085->SetLineColor(kYellow+2); hist_nHadron_240_085->SetMarkerColor(kYellow+2); hist_nHadron_240_085->SetMarkerStyle(kStar); hist_nHadron_240_085->SetLineWidth(2); 
	TH1F *hist_nHadron_240_100 = (TH1F*)input_240->Get("KNOO_nHadron_100");
	hist_nHadron_240_100->SetLineColor(kBlue+2); hist_nHadron_240_100->SetMarkerColor(kBlue+2); hist_nHadron_240_100->SetMarkerStyle(kStar); hist_nHadron_240_100->SetLineWidth(2); 

	TH1F *hist_ThrPyth_365_000 = (TH1F*)input_365->Get("hist_ThrPyth_000");
	hist_ThrPyth_365_000->SetLineColor(kRed+2); hist_ThrPyth_365_000->SetMarkerColor(kRed+2); hist_ThrPyth_365_000->SetMarkerStyle(kStar); hist_ThrPyth_365_000->SetLineWidth(2); 
	TH1F *hist_ThrPyth_365_060 = (TH1F*)input_365->Get("hist_ThrPyth_060");
	hist_ThrPyth_365_060->SetLineColor(kGreen+2); hist_ThrPyth_365_060->SetMarkerColor(kGreen+2); hist_ThrPyth_365_060->SetMarkerStyle(kStar); hist_ThrPyth_365_060->SetLineWidth(2); 
	TH1F *hist_ThrPyth_365_085 = (TH1F*)input_365->Get("hist_ThrPyth_085");
	hist_ThrPyth_365_085->SetLineColor(kYellow+2); hist_ThrPyth_365_085->SetMarkerColor(kYellow+2); hist_ThrPyth_365_085->SetMarkerStyle(kStar); hist_ThrPyth_365_085->SetLineWidth(2); 
	TH1F *hist_ThrPyth_365_100 = (TH1F*)input_365->Get("hist_ThrPyth_100");
	hist_ThrPyth_365_100->SetLineColor(kBlue+2); hist_ThrPyth_365_100->SetMarkerColor(kBlue+2); hist_ThrPyth_365_100->SetMarkerStyle(kStar); hist_ThrPyth_365_100->SetLineWidth(2); 

	TH1F *hist_nHadron_365_000 = (TH1F*)input_365->Get("KNOO_nHadron_000");
	hist_nHadron_365_000->SetLineColor(kRed+2); hist_nHadron_365_000->SetMarkerColor(kRed+2); hist_nHadron_365_000->SetMarkerStyle(kStar); hist_nHadron_365_000->SetLineWidth(2); 
	TH1F *hist_nHadron_365_060 = (TH1F*)input_365->Get("KNOO_nHadron_060");
	hist_nHadron_365_060->SetLineColor(kGreen+2); hist_nHadron_365_060->SetMarkerColor(kGreen+2); hist_nHadron_365_060->SetMarkerStyle(kStar); hist_nHadron_365_060->SetLineWidth(2); 
	TH1F *hist_nHadron_365_085 = (TH1F*)input_365->Get("KNOO_nHadron_085");
	hist_nHadron_365_085->SetLineColor(kYellow+2); hist_nHadron_365_085->SetMarkerColor(kYellow+2); hist_nHadron_365_085->SetMarkerStyle(kStar); hist_nHadron_365_085->SetLineWidth(2); 
	TH1F *hist_nHadron_365_100 = (TH1F*)input_365->Get("KNOO_nHadron_100");
	hist_nHadron_365_100->SetLineColor(kBlue+2); hist_nHadron_365_100->SetMarkerColor(kBlue+2); hist_nHadron_365_100->SetMarkerStyle(kStar); hist_nHadron_365_100->SetLineWidth(2); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Disable histogram stats
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912_000->SetStats(kFALSE);
	hist_ThrPyth_912_060->SetStats(kFALSE);
	hist_ThrPyth_912_085->SetStats(kFALSE);
	hist_ThrPyth_912_100->SetStats(kFALSE);
	hist_nHadron_912_000->SetStats(kFALSE);
	hist_nHadron_912_060->SetStats(kFALSE);
	hist_nHadron_912_085->SetStats(kFALSE);
	hist_nHadron_912_100->SetStats(kFALSE);
	hist_ThrPyth_160_000->SetStats(kFALSE);
	hist_ThrPyth_160_060->SetStats(kFALSE);
	hist_ThrPyth_160_085->SetStats(kFALSE);
	hist_ThrPyth_160_100->SetStats(kFALSE);
	hist_nHadron_160_000->SetStats(kFALSE);
	hist_nHadron_160_060->SetStats(kFALSE);
	hist_nHadron_160_085->SetStats(kFALSE);
	hist_nHadron_160_100->SetStats(kFALSE);
	hist_ThrPyth_180_000->SetStats(kFALSE);
	hist_ThrPyth_180_060->SetStats(kFALSE);
	hist_ThrPyth_180_085->SetStats(kFALSE);
	hist_ThrPyth_180_100->SetStats(kFALSE);
	hist_nHadron_180_000->SetStats(kFALSE);
	hist_nHadron_180_060->SetStats(kFALSE);
	hist_nHadron_180_085->SetStats(kFALSE);
	hist_nHadron_180_100->SetStats(kFALSE);
	hist_ThrPyth_240_000->SetStats(kFALSE);
	hist_ThrPyth_240_060->SetStats(kFALSE);
	hist_ThrPyth_240_085->SetStats(kFALSE);
	hist_ThrPyth_240_100->SetStats(kFALSE);
	hist_nHadron_240_000->SetStats(kFALSE);
	hist_nHadron_240_060->SetStats(kFALSE);
	hist_nHadron_240_085->SetStats(kFALSE);
	hist_nHadron_240_100->SetStats(kFALSE);
	hist_ThrPyth_365_000->SetStats(kFALSE);
	hist_ThrPyth_365_060->SetStats(kFALSE);
	hist_ThrPyth_365_085->SetStats(kFALSE);
	hist_ThrPyth_365_100->SetStats(kFALSE);
	hist_nHadron_365_000->SetStats(kFALSE);
	hist_nHadron_365_060->SetStats(kFALSE);
	hist_nHadron_365_085->SetStats(kFALSE);
	hist_nHadron_365_100->SetStats(kFALSE);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalisation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912_000->Scale(1.0/hist_ThrPyth_912_000->Integral());
	hist_ThrPyth_912_060->Scale(1.0/hist_ThrPyth_912_060->Integral());
	hist_ThrPyth_912_085->Scale(1.0/hist_ThrPyth_912_085->Integral());
	hist_ThrPyth_912_100->Scale(1.0/hist_ThrPyth_912_100->Integral());

	hist_nHadron_912_000->Scale(1.0/hist_nHadron_912_000->Integral());
	hist_nHadron_912_060->Scale(1.0/hist_nHadron_912_060->Integral());
	hist_nHadron_912_085->Scale(1.0/hist_nHadron_912_085->Integral());
	hist_nHadron_912_100->Scale(1.0/hist_nHadron_912_100->Integral());

	hist_ThrPyth_160_000->Scale(1.0/hist_ThrPyth_160_000->Integral());
	hist_ThrPyth_160_060->Scale(1.0/hist_ThrPyth_160_060->Integral());
	hist_ThrPyth_160_085->Scale(1.0/hist_ThrPyth_160_085->Integral());
	hist_ThrPyth_160_100->Scale(1.0/hist_ThrPyth_160_100->Integral());

	hist_nHadron_160_000->Scale(1.0/hist_nHadron_160_000->Integral());
	hist_nHadron_160_060->Scale(1.0/hist_nHadron_160_060->Integral());
	hist_nHadron_160_085->Scale(1.0/hist_nHadron_160_085->Integral());
	hist_nHadron_160_100->Scale(1.0/hist_nHadron_160_100->Integral());

	hist_ThrPyth_180_000->Scale(1.0/hist_ThrPyth_180_000->Integral());
	hist_ThrPyth_180_060->Scale(1.0/hist_ThrPyth_180_060->Integral());
	hist_ThrPyth_180_085->Scale(1.0/hist_ThrPyth_180_085->Integral());
	hist_ThrPyth_180_100->Scale(1.0/hist_ThrPyth_180_100->Integral());

	hist_nHadron_180_000->Scale(1.0/hist_nHadron_180_000->Integral());
	hist_nHadron_180_060->Scale(1.0/hist_nHadron_180_060->Integral());
	hist_nHadron_180_085->Scale(1.0/hist_nHadron_180_085->Integral());
	hist_nHadron_180_100->Scale(1.0/hist_nHadron_180_100->Integral());

	hist_ThrPyth_240_000->Scale(1.0/hist_ThrPyth_240_000->Integral());
	hist_ThrPyth_240_060->Scale(1.0/hist_ThrPyth_240_060->Integral());
	hist_ThrPyth_240_085->Scale(1.0/hist_ThrPyth_240_085->Integral());
	hist_ThrPyth_240_100->Scale(1.0/hist_ThrPyth_240_100->Integral());

	hist_nHadron_240_000->Scale(1.0/hist_nHadron_240_000->Integral());
	hist_nHadron_240_060->Scale(1.0/hist_nHadron_240_060->Integral());
	hist_nHadron_240_085->Scale(1.0/hist_nHadron_240_085->Integral());
	hist_nHadron_240_100->Scale(1.0/hist_nHadron_240_100->Integral());
	
	hist_ThrPyth_365_000->Scale(1.0/hist_ThrPyth_365_000->Integral());
	hist_ThrPyth_365_060->Scale(1.0/hist_ThrPyth_365_060->Integral());
	hist_ThrPyth_365_085->Scale(1.0/hist_ThrPyth_365_085->Integral());
	hist_ThrPyth_365_100->Scale(1.0/hist_ThrPyth_365_100->Integral());

	hist_nHadron_365_000->Scale(1.0/hist_nHadron_365_000->Integral());
	hist_nHadron_365_060->Scale(1.0/hist_nHadron_365_060->Integral());
	hist_nHadron_365_085->Scale(1.0/hist_nHadron_365_085->Integral());
	hist_nHadron_365_100->Scale(1.0/hist_nHadron_365_100->Integral());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Edit titles
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// hist_ThrPyth_365_000->GetXaxis()->SetTitle("#sqrt{s} /#sqrt{s'}");
	// hist_ThrPyth_365_000->GetYaxis()->SetTitle("P(#sqrt{s} /#sqrt{s'})");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Add legend
	TLegend *lg2 = new TLegend(0.64, 0.65, 0.87, 0.87);
	lg2->AddEntry(hist_ThrPyth_365_000, "0.00#sqrt{s'} cut", "p");
	lg2->AddEntry(hist_ThrPyth_365_060, "0.65#sqrt{s'} cut", "p");
	lg2->AddEntry(hist_ThrPyth_365_085, "0.85#sqrt{s'} cut", "p");
	lg2->AddEntry(hist_ThrPyth_365_100, "1.00#sqrt{s'} cut", "p");
	lg2->SetTextSize(0.03);
	
	// Create canvas
	TCanvas* cv2 = new TCanvas("cv2", "FCC-ee ISR Studies", 1600, 800);

	// Beautify
	gStyle->SetErrorX(0.000000001);
	cv2->Divide(4,2);
	cv2->cd(1)->SetLeftMargin(0.15);
	cv2->cd(1)->SetLogy();
	cv2->cd(1)->SetTickx(); cv2->cd(1)->SetTicky();
	cv2->cd(1)->SetGridx(); cv2->cd(1)->SetGridy();
	cv2->cd(2)->SetLeftMargin(0.15);
	cv2->cd(2)->SetLogy();
	cv2->cd(2)->SetTickx(); cv2->cd(2)->SetTicky();
	cv2->cd(2)->SetGridx(); cv2->cd(2)->SetGridy();
	cv2->cd(3)->SetLeftMargin(0.15);
	cv2->cd(3)->SetLogy();
	cv2->cd(3)->SetTickx(); cv2->cd(3)->SetTicky();
	cv2->cd(3)->SetGridx(); cv2->cd(3)->SetGridy();
	cv2->cd(4)->SetLeftMargin(0.15);
	cv2->cd(4)->SetLogy();
	cv2->cd(4)->SetTickx(); cv2->cd(4)->SetTicky();
	cv2->cd(4)->SetGridx(); cv2->cd(4)->SetGridy();
	cv2->cd(5)->SetLeftMargin(0.15);
	cv2->cd(5)->SetLogy();
	cv2->cd(5)->SetTickx(); cv2->cd(5)->SetTicky();
	cv2->cd(5)->SetGridx(); cv2->cd(5)->SetGridy();
	cv2->cd(6)->SetLeftMargin(0.15);
	cv2->cd(6)->SetLogy();
	cv2->cd(6)->SetTickx(); cv2->cd(6)->SetTicky();
	cv2->cd(6)->SetGridx(); cv2->cd(6)->SetGridy();
	cv2->cd(7)->SetLeftMargin(0.15);
	cv2->cd(7)->SetLogy();
	cv2->cd(7)->SetTickx(); cv2->cd(7)->SetTicky();
	cv2->cd(7)->SetGridx(); cv2->cd(7)->SetGridy();
	cv2->cd(8)->SetLeftMargin(0.15);
	cv2->cd(8)->SetLogy();
	cv2->cd(8)->SetTickx(); cv2->cd(8)->SetTicky();
	cv2->cd(8)->SetGridx(); cv2->cd(8)->SetGridy();
	
	// Draw
	cv2->cd(1);
	hist_ThrPyth_912_000->Draw("P");
	hist_ThrPyth_912_060->Draw("P SAME");
	hist_ThrPyth_912_085->Draw("P SAME");
	hist_ThrPyth_912_100->Draw("P SAME");
	lg2->Draw("SAME");
	cv2->cd(2);
	hist_ThrPyth_160_000->Draw("P");
	hist_ThrPyth_160_060->Draw("P SAME");
	hist_ThrPyth_160_085->Draw("P SAME");
	hist_ThrPyth_160_100->Draw("P SAME");
	lg2->Draw("SAME");
	cv2->cd(3);
	hist_ThrPyth_240_000->Draw("P");
	hist_ThrPyth_240_060->Draw("P SAME");
	hist_ThrPyth_240_085->Draw("P SAME");
	hist_ThrPyth_240_100->Draw("P SAME");
	lg2->Draw("SAME");
	cv2->cd(4);
	hist_ThrPyth_365_000->Draw("P");
	hist_ThrPyth_365_060->Draw("P SAME");
	hist_ThrPyth_365_085->Draw("P SAME");
	hist_ThrPyth_365_100->Draw("P SAME");
	lg2->Draw("SAME");

	cv2->cd(5);
	hist_nHadron_912_000->Draw("P");
	hist_nHadron_912_060->Draw("P SAME");
	hist_nHadron_912_085->Draw("P SAME");
	hist_nHadron_912_100->Draw("P SAME");
	lg2->Draw("SAME");
	cv2->cd(6);
	hist_nHadron_160_000->Draw("P");
	hist_nHadron_160_060->Draw("P SAME");
	hist_nHadron_160_085->Draw("P SAME");
	hist_nHadron_160_100->Draw("P SAME");
	lg2->Draw("SAME");
	cv2->cd(7);
	hist_nHadron_240_000->Draw("P");
	hist_nHadron_240_060->Draw("P SAME");
	hist_nHadron_240_085->Draw("P SAME");
	hist_nHadron_240_100->Draw("P SAME");
	lg2->Draw("SAME");
	cv2->cd(8);
	hist_nHadron_365_000->Draw("P");
	hist_nHadron_365_060->Draw("P SAME");
	hist_nHadron_365_085->Draw("P SAME");
	hist_nHadron_365_100->Draw("P SAME");
	lg2->Draw("SAME");

	// Set limits
	hist_ThrPyth_365_000->GetYaxis()->SetRangeUser(1E-5,1E0);
	hist_nHadron_365_000->GetYaxis()->SetRangeUser(1E-7,1E0);
	hist_ThrPyth_240_000->GetYaxis()->SetRangeUser(1E-5,1E0);
	hist_nHadron_240_000->GetYaxis()->SetRangeUser(1E-7,1E0);
	hist_ThrPyth_160_000->GetYaxis()->SetRangeUser(1E-5,1E0);
	hist_nHadron_160_000->GetYaxis()->SetRangeUser(1E-7,1E0);
	hist_ThrPyth_912_000->GetYaxis()->SetRangeUser(1E-5,1E0);
	hist_nHadron_912_000->GetYaxis()->SetRangeUser(1E-7,1E0);

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv2->Modified();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plotting Running of <1-T>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1F *hist_RunThrust = new TH1F("hist_Esprime_hZ", "Reduced energy after ISR", 200, -1, 366);
	hist_RunThrust->Fill(hist_ThrPyth_912_100->GetMean());
	hist_RunThrust->Fill(hist_ThrPyth_160_100->GetMean());
	hist_RunThrust->Fill(hist_ThrPyth_180_100->GetMean());
	hist_RunThrust->Fill(hist_ThrPyth_240_100->GetMean());
	hist_RunThrust->Fill(hist_ThrPyth_365_100->GetMean());

}