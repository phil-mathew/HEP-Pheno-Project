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
void ImpactofExp()
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading ROOTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile *input_912 = new TFile("5-CutData/cut_FCC912.root", "READ");
	TFile *input_161 = new TFile("5-CutData/cut_FCC161.root", "READ");
	TFile *input_183 = new TFile("5-CutData/cut_FCC183.root", "READ");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Importing raw TEXT data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Buffers
	double Par; 
	double PrbTotal=0;
	double Prb, Err_Par, Err_Prb;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Read Histogram
	TH1F *hist_Thr1999 = new TH1F("hist_Thr1999", "Inverse Thrust (wo top)", 500, 0, 0.4);
	// Beautify
	hist_Thr1999->SetTitle("Inverse Thrust wo Top wo ISR");
	hist_Thr1999->SetName("hist_Thr1999");
	hist_Thr1999->GetXaxis()->SetTitle("1-T");
	hist_Thr1999->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_01("3-LEPdata/EXP_TES_500_THR_wot.txt");
	// Read through TXT
	while ( !infile_01.eof() ) {
		// Set reading order
		infile_01 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_Thr1999->SetBinContent(hist_Thr1999->FindBin(Par), Prb);
		// Populate error bar
		hist_Thr1999->SetBinError(hist_Thr1999->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_01.close();

	// // Read Histogram
	TH1F *hist_Thr199T = new TH1F("hist_Thr199T", "Inverse Thrust (wi top)", 500, 0, 0.4);
	// Beautify
	hist_Thr199T->SetTitle("Inverse Thrust wi Top wo ISR");
	hist_Thr199T->SetName("hist_Thr199T");
	hist_Thr199T->GetXaxis()->SetTitle("1-T");
	hist_Thr199T->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_02("3-LEPdata/EXP_TES_500_THR_wit.txt");
	// Read through TXT
	while ( !infile_02.eof() ) {
		// Set reading order
		infile_02 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_Thr199T->SetBinContent(hist_Thr199T->FindBin(Par), Prb);
		// Populate error bar
		hist_Thr199T->SetBinError(hist_Thr199T->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_02.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Read Histogram
	TH1F *hist_ThrExL3_912 = new TH1F("hist_ThrExL3_912", "Inverse Thrust", 500, 0, 0.4);
	// Beautify
	hist_ThrExL3_912->SetTitle("Inverse Thrust");
	hist_ThrExL3_912->SetName("hist_ThrExL3_912");
	hist_ThrExL3_912->GetXaxis()->SetTitle("1-T");
	hist_ThrExL3_912->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_03("3-LEPdata/EXP_LL3_912_THR.txt");
	// Read through TXT
	while ( !infile_03.eof() ) {
		// Set reading order
		infile_03 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_ThrExL3_912->SetBinContent(hist_ThrExL3_912->FindBin(Par), Prb);
		// Populate error bar
		hist_ThrExL3_912->SetBinError(hist_ThrExL3_912->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_03.close();

	// // Read Histogram
	TH1F *hist_ThrExAL_912 = new TH1F("hist_ThrExAL_912", "Inverse Thrust", 500, 0, 0.4);
	// Beautify
	hist_ThrExAL_912->SetTitle("Inverse Thrust");
	hist_ThrExAL_912->SetName("hist_ThrExAL_912");
	hist_ThrExAL_912->GetXaxis()->SetTitle("1-T");
	hist_ThrExAL_912->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_04("3-LEPdata/EXP_ALP_912_THR.txt");
	// Read through TXT
	while ( !infile_04.eof() ) {
		// Set reading order
		infile_04 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_ThrExAL_912->SetBinContent(hist_ThrExAL_912->FindBin(Par), Prb);
		// Populate error bar
		hist_ThrExAL_912->SetBinError(hist_ThrExAL_912->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_04.close();
	
	// // Read Histogram
	TH1F *hist_ThrExL3_161 = new TH1F("hist_ThrExL3_161", "Inverse Thrust", 500, 0, 0.4);
	// Beautify
	hist_ThrExL3_161->SetTitle("Inverse Thrust");
	hist_ThrExL3_161->SetName("hist_ThrExL3_161");
	hist_ThrExL3_161->GetXaxis()->SetTitle("1-T");
	hist_ThrExL3_161->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_05("3-LEPdata/EXP_LL3_161_THR.txt");
	// Read through TXT
	while ( !infile_05.eof() ) {
		// Set reading order
		infile_05 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_ThrExL3_161->SetBinContent(hist_ThrExL3_161->FindBin(Par), Prb);
		// Populate error bar
		hist_ThrExL3_161->SetBinError(hist_ThrExL3_161->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_05.close();

	// // Read Histogram
	TH1F *hist_ThrExAL_161 = new TH1F("hist_ThrExAL_161", "Inverse Thrust", 500, 0, 0.4);
	// Beautify
	hist_ThrExAL_161->SetTitle("Inverse Thrust");
	hist_ThrExAL_161->SetName("hist_ThrExAL_161");
	hist_ThrExAL_161->GetXaxis()->SetTitle("1-T");
	hist_ThrExAL_161->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_06("3-LEPdata/EXP_ALP_161_THR.txt");
	// Read through TXT
	while ( !infile_06.eof() ) {
		// Set reading order
		infile_06 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_ThrExAL_161->SetBinContent(hist_ThrExAL_161->FindBin(Par), Prb);
		// Populate error bar
		hist_ThrExAL_161->SetBinError(hist_ThrExAL_161->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_06.close();

	// // Read Histogram
	TH1F *hist_ThrExL3_183 = new TH1F("hist_ThrExL3_183", "Inverse Thrust", 500, 0, 0.4);
	// Beautify
	hist_ThrExL3_183->SetTitle("Inverse Thrust");
	hist_ThrExL3_183->SetName("hist_ThrExL3_183");
	hist_ThrExL3_183->GetXaxis()->SetTitle("1-T");
	hist_ThrExL3_183->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_07("3-LEPdata/EXP_LL3_183_THR.txt");
	// Read through TXT
	while ( !infile_07.eof() ) {
		// Set reading order
		infile_07 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_ThrExL3_183->SetBinContent(hist_ThrExL3_183->FindBin(Par), Prb);
		// Populate error bar
		hist_ThrExL3_183->SetBinError(hist_ThrExL3_183->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_07.close();

	// // Read Histogram
	TH1F *hist_ThrExAL_183 = new TH1F("hist_ThrExAL_183", "Inverse Thrust", 500, 0, 0.4);
	// Beautify
	hist_ThrExAL_183->SetTitle("Inverse Thrust");
	hist_ThrExAL_183->SetName("hist_ThrExAL_183");
	hist_ThrExAL_183->GetXaxis()->SetTitle("1-T");
	hist_ThrExAL_183->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_08("3-LEPdata/EXP_ALP_183_THR.txt");
	// Read through TXT
	while ( !infile_08.eof() ) {
		// Set reading order
		infile_08 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_ThrExAL_183->SetBinContent(hist_ThrExAL_183->FindBin(Par), Prb);
		// Populate error bar
		hist_ThrExAL_183->SetBinError(hist_ThrExAL_183->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_08.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// // Read Histogram
	TH1F *hist_CprExL3_912 = new TH1F("hist_CprExL3_912", "Inverse Cprust", 500, 0, 0.4);
	// Beautify
	hist_CprExL3_912->SetTitle("Inverse Cprust");
	hist_CprExL3_912->SetName("hist_CprExL3_912");
	hist_CprExL3_912->GetXaxis()->SetTitle("1-T");
	hist_CprExL3_912->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_09("3-LEPdata/EXP_LL3_912_Cpr.txt");
	// Read Cprough TXT
	while ( !infile_09.eof() ) {
		// Set reading order
		infile_09 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_CprExL3_912->SetBinContent(hist_CprExL3_912->FindBin(Par), Prb);
		// Populate error bar
		hist_CprExL3_912->SetBinError(hist_CprExL3_912->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_09.close();

	// // Read Histogram
	TH1F *hist_CprExAL_912 = new TH1F("hist_CprExAL_912", "Inverse Cprust", 500, 0, 0.4);
	// Beautify
	hist_CprExAL_912->SetTitle("Inverse Cprust");
	hist_CprExAL_912->SetName("hist_CprExAL_912");
	hist_CprExAL_912->GetXaxis()->SetTitle("1-T");
	hist_CprExAL_912->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_10("3-LEPdata/EXP_ALP_912_Cpr.txt");
	// Read Cprough TXT
	while ( !infile_10.eof() ) {
		// Set reading order
		infile_10 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_CprExAL_912->SetBinContent(hist_CprExAL_912->FindBin(Par), Prb);
		// Populate error bar
		hist_CprExAL_912->SetBinError(hist_CprExAL_912->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_10.close();
	
	// // Read Histogram
	TH1F *hist_CprExL3_161 = new TH1F("hist_CprExL3_161", "Inverse Cprust", 500, 0, 0.4);
	// Beautify
	hist_CprExL3_161->SetTitle("Inverse Cprust");
	hist_CprExL3_161->SetName("hist_CprExL3_161");
	hist_CprExL3_161->GetXaxis()->SetTitle("1-T");
	hist_CprExL3_161->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_11("3-LEPdata/EXP_LL3_161_Cpr.txt");
	// Read Cprough TXT
	while ( !infile_11.eof() ) {
		// Set reading order
		infile_11 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_CprExL3_161->SetBinContent(hist_CprExL3_161->FindBin(Par), Prb);
		// Populate error bar
		hist_CprExL3_161->SetBinError(hist_CprExL3_161->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_11.close();

	// // Read Histogram
	TH1F *hist_CprExAL_161 = new TH1F("hist_CprExAL_161", "Inverse Cprust", 500, 0, 0.4);
	// Beautify
	hist_CprExAL_161->SetTitle("Inverse Cprust");
	hist_CprExAL_161->SetName("hist_CprExAL_161");
	hist_CprExAL_161->GetXaxis()->SetTitle("1-T");
	hist_CprExAL_161->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_12("3-LEPdata/EXP_ALP_161_Cpr.txt");
	// Read Cprough TXT
	while ( !infile_12.eof() ) {
		// Set reading order
		infile_12 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_CprExAL_161->SetBinContent(hist_CprExAL_161->FindBin(Par), Prb);
		// Populate error bar
		hist_CprExAL_161->SetBinError(hist_CprExAL_161->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_12.close();

	// // Read Histogram
	TH1F *hist_CprExL3_183 = new TH1F("hist_CprExL3_183", "Inverse Cprust", 500, 0, 0.4);
	// Beautify
	hist_CprExL3_183->SetTitle("Inverse Cprust");
	hist_CprExL3_183->SetName("hist_CprExL3_183");
	hist_CprExL3_183->GetXaxis()->SetTitle("1-T");
	hist_CprExL3_183->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_13("3-LEPdata/EXP_LL3_183_Cpr.txt");
	// Read Cprough TXT
	while ( !infile_13.eof() ) {
		// Set reading order
		infile_13 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_CprExL3_183->SetBinContent(hist_CprExL3_183->FindBin(Par), Prb);
		// Populate error bar
		hist_CprExL3_183->SetBinError(hist_CprExL3_183->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_13.close();

	// // Read Histogram
	TH1F *hist_CprExAL_183 = new TH1F("hist_CprExAL_183", "Inverse Cprust", 500, 0, 0.4);
	// Beautify
	hist_CprExAL_183->SetTitle("Inverse Cprust");
	hist_CprExAL_183->SetName("hist_CprExAL_183");
	hist_CprExAL_183->GetXaxis()->SetTitle("1-T");
	hist_CprExAL_183->GetYaxis()->SetTitle("P(1-T)");
	// Import data
	ifstream infile_14("3-LEPdata/EXP_ALP_183_Cpr.txt");
	// Read Cprough TXT
	while ( !infile_14.eof() ) {
		// Set reading order
		infile_14 >> Par >> Prb >> Err_Par >> Err_Prb;
		// Populate histogram
		hist_CprExAL_183->SetBinContent(hist_CprExAL_183->FindBin(Par), Prb);
		// Populate error bar
		hist_CprExAL_183->SetBinError(hist_CprExAL_183->FindBin(Par), Err_Prb);
	}
	// Close file
	infile_14.close();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reading Pythia histograms from ROOT files
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	// TH1F *hist_ThrPy99 = (TH1F*)input_500->Get("hist_ThrPy99_Zq");
	// hist_ThrPy99->SetLineColor(kYellow+2); hist_ThrPy99->SetMarkerColor(kYellow+2); hist_ThrPy99->SetMarkerStyle(kOpenTriangleUp); hist_ThrPy99->SetLineWidth(2);
	// hist_Thr1999->SetLineColor(kBlack); hist_Thr1999->SetMarkerColor(kBlack); hist_Thr1999->SetMarkerStyle(kOpenTriangleUp); hist_Thr1999->SetLineWidth(2); 

	// TH1F *hist_ThrPy9T = (TH1F*)input_500->Get("hist_ThrPy99_Zt");
	// hist_ThrPy9T->SetLineColor(kYellow+2); hist_ThrPy9T->SetMarkerColor(kYellow+2); hist_ThrPy9T->SetMarkerStyle(kOpenTriangleUp); hist_ThrPy9T->SetLineWidth(2); 
	// hist_Thr199T->SetLineColor(kBlack); hist_Thr199T->SetMarkerColor(kBlack); hist_Thr199T->SetMarkerStyle(kOpenTriangleUp); hist_Thr199T->SetLineWidth(2); 

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

	TH1F *hist_CprPyth_912 = (TH1F*)input_912->Get("hist_CprPyth");
	hist_CprPyth_912->SetLineColor(kBlack); hist_CprPyth_912->SetMarkerColor(kBlack); hist_CprPyth_912->SetMarkerStyle(26); hist_CprPyth_912->SetLineWidth(2); hist_CprPyth_912->SetMarkerSize(2);
	hist_CprExL3_912->SetLineColor(kBlue); hist_CprExL3_912->SetMarkerColor(kBlue); hist_CprExL3_912->SetMarkerStyle(53); hist_CprExL3_912->SetLineWidth(1); hist_CprExL3_912->SetMarkerSize(1.5);
	hist_CprExAL_912->SetLineColor(kRed+2); hist_CprExAL_912->SetMarkerColor(kRed+2); hist_CprExAL_912->SetMarkerStyle(53); hist_CprExAL_912->SetLineWidth(1); hist_CprExAL_912->SetMarkerSize(1.5);

	TH1F *hist_CprPyth_161 = (TH1F*)input_161->Get("hist_CprPyth");
	hist_CprPyth_161->SetLineColor(kBlack); hist_CprPyth_161->SetMarkerColor(kBlack); hist_CprPyth_161->SetMarkerStyle(26); hist_CprPyth_161->SetLineWidth(2); hist_CprPyth_161->SetMarkerSize(2);
	hist_CprExL3_161->SetLineColor(kBlue); hist_CprExL3_161->SetMarkerColor(kBlue); hist_CprExL3_161->SetMarkerStyle(53); hist_CprExL3_161->SetLineWidth(1); hist_CprExL3_161->SetMarkerSize(1.5);
	hist_CprExAL_161->SetLineColor(kRed+2); hist_CprExAL_161->SetMarkerColor(kRed+2); hist_CprExAL_161->SetMarkerStyle(53); hist_CprExAL_161->SetLineWidth(1); hist_CprExAL_161->SetMarkerSize(1.5);

	TH1F *hist_CprPyth_183 = (TH1F*)input_183->Get("hist_CprPyth");
	hist_CprPyth_183->SetLineColor(kBlack); hist_CprPyth_183->SetMarkerColor(kBlack); hist_CprPyth_183->SetMarkerStyle(26); hist_CprPyth_183->SetLineWidth(2); hist_CprPyth_183->SetMarkerSize(2);
	hist_CprExL3_183->SetLineColor(kBlue); hist_CprExL3_183->SetMarkerColor(kBlue); hist_CprExL3_183->SetMarkerStyle(53); hist_CprExL3_183->SetLineWidth(1); hist_CprExL3_183->SetMarkerSize(1.5);
	hist_CprExAL_183->SetLineColor(kRed+2); hist_CprExAL_183->SetMarkerColor(kRed+2); hist_CprExAL_183->SetMarkerStyle(53); hist_CprExAL_183->SetLineWidth(1);	hist_CprExAL_183->SetMarkerSize(1.5);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalising by area under histogram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	cout << "--------------------------------------------" << endl;
	cout << "hist_ThrPyth_912->Integral(width) = " << hist_ThrPyth_912->Integral("width") << endl;
	cout << "hist_ThrPyth_912->Integral() = " << hist_ThrPyth_912->Integral() << endl;
	cout << "--------------------------------------------" << endl;
	cout << "hist_ThrPyth_161->Integral(width) = " << hist_ThrPyth_161->Integral("width") << endl;
	cout << "hist_ThrPyth_161->Integral() = " << hist_ThrPyth_161->Integral() << endl;
	cout << "--------------------------------------------" << endl;
	cout << "hist_ThrPyth_183->Integral(width) = " << hist_ThrPyth_183->Integral("width") << endl;
	cout << "hist_ThrPyth_183->Integral() = " << hist_ThrPyth_183->Integral() << endl;
	cout << "--------------------------------------------" << endl;

	hist_ThrPyth_912->Scale(1.0/hist_ThrPyth_912->Integral("width"));
	hist_CprPyth_912->Scale(1.0/hist_CprPyth_912->Integral("width"));

	hist_ThrPyth_161->Scale(1.0/hist_ThrPyth_161->Integral("width"));
	hist_CprPyth_161->Scale(1.0/hist_CprPyth_161->Integral("width"));

	hist_ThrPyth_183->Scale(1.0/hist_ThrPyth_183->Integral("width"));
	hist_CprPyth_183->Scale(1.0/hist_CprPyth_183->Integral("width"));

	// hist_ThrExL3_912->Scale(1.0/hist_ThrExL3_912->Integral());
	// hist_ThrExAL_912->Scale(1.0/hist_ThrExAL_912->Integral());

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

	hist_CprPyth_912->SetStats(kFALSE);
	hist_CprExL3_912->SetStats(kFALSE);
	hist_CprExAL_912->SetStats(kFALSE);

	hist_CprPyth_161->SetStats(kFALSE);
	hist_CprExL3_161->SetStats(kFALSE);
	hist_CprExAL_161->SetStats(kFALSE);

	hist_CprPyth_183->SetStats(kFALSE);
	hist_CprExL3_183->SetStats(kFALSE);
	hist_CprExAL_183->SetStats(kFALSE);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hist_ThrPyth_912->SetTitle("Inverse Thrust at 91.2 GeV");
	hist_ThrPyth_161->SetTitle("Inverse Thrust at 161 GeV");
	hist_ThrPyth_183->SetTitle("Inverse Thrust at 183 GeV");

	hist_CprPyth_912->SetTitle("C-parameter at 91.2 GeV");
	hist_CprPyth_161->SetTitle("C-parameter at 161 GeV");
	hist_CprPyth_183->SetTitle("C-parameter at 183 GeV");

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

	hist_ThrPyth_912->SetTitle("");
	hist_ThrPyth_161->SetTitle("");
	hist_ThrPyth_183->SetTitle("");

	hist_CprPyth_912->SetTitle("");
	hist_CprPyth_161->SetTitle("");
	hist_CprPyth_183->SetTitle("");

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
	gStyle->SetErrorX(0.000000001);
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv1->SetMargin(0, 0, 0, 0); 
	cv1->Divide(1,2);
	for (int i = 1; i <= 2; i++) {
		cv1->cd(i);
		gPad->SetTopMargin(0.015);
		gPad->SetBottomMargin(0.1);
		gPad->SetLeftMargin(0.15);
		gPad->SetRightMargin(0.04);
		gPad->SetTickx(); gPad->SetTicky();
		// gPad->SetGridx(); gPad->SetGridy();
		gPad->SetLogy();
	}

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

	lg->Draw("SAME");

	// Set limits
	hist_ThrPyth_912->GetYaxis()->SetRangeUser(1E-3,1E2);
	hist_ThrPyth_912->GetXaxis()->SetRangeUser(0,0.4);
	hist_CprPyth_912->GetYaxis()->SetRangeUser(1E-3,1E9);
	hist_CprPyth_912->GetXaxis()->SetRangeUser(0,0.4);	

	// Modify stat-box
	gStyle->SetOptStat();
	// Update canvas
	cv1->Modified();

}