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
void ImpactofError() {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw Plots
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	gStyle->SetCanvasPreferGL(true);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// L3 axes
	double xbin_ExLL3[16] = { 41.4, 55.3, 65.4, 75.7, 82.3, 85.1, 91.2, 130.1, 136.1, 161.3, 172.3, 182.8, 188.6, 194.4, 200.2, 206.2 };
	double yerr_ExLL3[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	// L3 graphs
	double ybin_ErorThr_ExLL3[16] = { 0.0124/0.1500*100, 0.0127/0.1310*100, 0.0104/0.1458*100, 0.0101/0.1290*100, 0.0094/0.1224*100, 0.0093/0.1184*100, 0.0076/0.1233*100, 0.0056/0.1139*100, 
									0.0060/0.1166*100, 0.0050/0.1018*100, 0.0064/0.1109*100, 0.0054/0.1132*100, 0.0057/0.1168*100, 0.0056/0.1168*100, 0.0059/0.1178*100, 0.0057/0.1173*100 };
	double ybin_ErorRho_ExLL3[16] = { 0.0102, 0.0064, 0.0065, 0.0062, 0.0075, 0.0059, 0.0052, 0.0038, 0.0037, 0.0034, 0.0033, 0.0038, 0.0033, 0.0039, 0.0034, 0.0034 };
	double ybin_ErorBto_ExLL3[16] = { 0.0119, 0.0099, 0.0106, 0.0097, 0.0095, 0.0095, 0.0080, 0.0064, 0.0064, 0.0067, 0.0061, 0.0060, 0.0067, 0.0065, 0.0062, 0.0065 };
	double ybin_ErorBwi_ExLL3[16] = { 0.0091, 0.0088, 0.0086, 0.0084, 0.0087, 0.0091, 0.0052, 0.0088, 0.0078, 0.0068, 0.0065, 0.0071, 0.0078, 0.0062, 0.0062, 0.0062 };
	double ybin_ErorCpr_ExLL3[16] = { 0.0102/0.1371*100, 0.0118/0.1197*100, 0.0108/0.1258*100, 0.0094/0.1143*100, 0.0091/0.1153*100, 0.0089/0.1115*100, 0.0076/0.1170*100, 0.0066/0.1151*100,
									0.0076/0.1089*100, 0.0057/0.1043*100, 0.0057/0.1121*100, 0.0054/0.1081*100, 0.0055/0.1118*100, 0.0056/0.1130*100, 0.0057/0.1147*100, 0.0053/0.1130*100 };
	// Construct
	auto grph_ErorThr_ExLL3 = new TGraphErrors(16, xbin_ExLL3, ybin_ErorThr_ExLL3, nullptr, yerr_ExLL3);
	grph_ErorThr_ExLL3->SetLineColor(kRed+2); grph_ErorThr_ExLL3->SetMarkerColor(kRed+2); grph_ErorThr_ExLL3->SetMarkerStyle(53); grph_ErorThr_ExLL3->SetLineWidth(2);
	auto grph_ErorRho_ExLL3 = new TGraphErrors(16, xbin_ExLL3, ybin_ErorRho_ExLL3, nullptr, yerr_ExLL3);
	grph_ErorRho_ExLL3->SetLineColor(kBlue+2); grph_ErorRho_ExLL3->SetMarkerColor(kBlue+2); grph_ErorRho_ExLL3->SetMarkerStyle(53); grph_ErorRho_ExLL3->SetLineWidth(2);
	auto grph_ErorBto_ExLL3 = new TGraphErrors(16, xbin_ExLL3, ybin_ErorBto_ExLL3, nullptr, yerr_ExLL3);
	grph_ErorBto_ExLL3->SetLineColor(kYellow+2); grph_ErorBto_ExLL3->SetMarkerColor(kYellow+2); grph_ErorBto_ExLL3->SetMarkerStyle(53); grph_ErorBto_ExLL3->SetLineWidth(2);
	auto grph_ErorBwi_ExLL3 = new TGraphErrors(16, xbin_ExLL3, ybin_ErorBwi_ExLL3, nullptr, yerr_ExLL3);
	grph_ErorBwi_ExLL3->SetLineColor(kGreen+2); grph_ErorBwi_ExLL3->SetMarkerColor(kGreen+2); grph_ErorBwi_ExLL3->SetMarkerStyle(53); grph_ErorBwi_ExLL3->SetLineWidth(2);
	auto grph_ErorCpr_ExLL3 = new TGraphErrors(16, xbin_ExLL3, ybin_ErorCpr_ExLL3, nullptr, yerr_ExLL3);
	grph_ErorCpr_ExLL3->SetLineColor(kMagenta+1); grph_ErorCpr_ExLL3->SetMarkerColor(kMagenta+1); grph_ErorCpr_ExLL3->SetMarkerStyle(53); grph_ErorCpr_ExLL3->SetLineWidth(2);

	// Create canvas
	TCanvas* cv4 = new TCanvas("cv4", "FCC-ee ISR Studies", 800, 800); 
	
	// Add legend
	TLegend *lg4 = new TLegend(0.75, 0.75, 0.92, 0.93);
	lg4->AddEntry(grph_ErorThr_ExLL3, "(1-T)", "L");
	// lg4->AddEntry(grph_ErorRho_ExLL3, "L3:#rho_{H}", "L");
	// lg4->AddEntry(grph_ErorBto_ExLL3, "L3:B_{T}", "L");
	// lg4->AddEntry(grph_ErorBwi_ExLL3, "L3:B_{W}", "L");
	lg4->AddEntry(grph_ErorCpr_ExLL3, "C", "L");
	lg4->SetTextSize(0.04);
	
	// Beautify
	gStyle->SetLabelSize(0.05, "X");
	gStyle->SetLabelSize(0.05, "Y");
	gStyle->SetTitleSize(0.06, "X");
	gStyle->SetTitleSize(0.06, "Y");
	cv4->SetMargin(0, 0, 0, 0);
	gPad->SetTopMargin(0.025);
	gPad->SetBottomMargin(0.08);
	gPad->SetLeftMargin(0.15);
	gPad->SetRightMargin(0.04);
	gPad->SetTickx(); gPad->SetTicky();

	// Beautify
	grph_ErorThr_ExLL3->GetXaxis()->CenterTitle(); grph_ErorThr_ExLL3->GetYaxis()->CenterTitle();
	grph_ErorThr_ExLL3->GetXaxis()->SetLabelSize(0.04); grph_ErorThr_ExLL3->GetXaxis()->SetTitleSize(0.04);
	grph_ErorThr_ExLL3->GetYaxis()->SetLabelSize(0.04); grph_ErorThr_ExLL3->GetYaxis()->SetTitleSize(0.04);
	grph_ErorThr_ExLL3->SetTitle("");
	grph_ErorThr_ExLL3->GetYaxis()->SetTitle("systematic error (%)");
	grph_ErorThr_ExLL3->GetXaxis()->SetTitle("#sqrt{s} (GeV)");

	// // Draw
	grph_ErorThr_ExLL3->Draw("APL");
	// grph_ErorRho_ExLL3->Draw("PL");
	// grph_ErorBto_ExLL3->Draw("PL");
	// grph_ErorBwi_ExLL3->Draw("PL");
	grph_ErorCpr_ExLL3->Draw("PL");
	lg4->Draw("SAME");

	// Set limits
	grph_ErorThr_ExLL3->GetYaxis()->SetRangeUser(0,20);
	grph_ErorThr_ExLL3->GetXaxis()->SetLimits(30, 400);

	// Update canvas
	cv4->Modified();

}