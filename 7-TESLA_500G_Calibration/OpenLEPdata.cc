/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Code to read in HEP-data files and recompile into a single ROOT file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Plugins
#include <iostream>
#include <fstream>
#include <sstream>
// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
// Header
using namespace std;

// Function to produce (1-T)
TH1D* InvertThrust(const TH1* h) {
    int nb = h->GetNbinsX();
    std::vector<double> edges(nb+1);
    for (int i=0; i<=nb; ++i)
        edges[i] = 1.0 - h->GetXaxis()->GetBinUpEdge(nb - i);
    TH1D* out = new TH1D(Form("%s_1mT",h->GetName()),"(1-T)",nb,edges.data());
    for (int i=1,j=nb; i<=nb; ++i,--j) {
        out->SetBinContent(i, h->GetBinContent(j));
        out->SetBinError(i,   h->GetBinError(j));
    }
    return out;
}

void OpenLEPdata() {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TH1::SetDefaultSumw2(true);
	double x, y;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access root
	TFile *input_EXP_ALP = TFile::Open("3-LEPdata/EXP_ALP.root");
	TFile *input_EXP_LL3 = TFile::Open("3-LEPdata/EXP_LL3.root");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_ALP_912_THR = (TDirectory*)input_EXP_ALP->Get("Table 54");

	// Access hist
	TH1F *hist_xx_00 = (TH1F*)table_EXP_ALP_912_THR->Get("Hist1D_y1");
	TH1F *hist_e1_00 = (TH1F*)table_EXP_ALP_912_THR->Get("Hist1D_y1_e1");
	TH1F *hist_e2_00 = (TH1F*)table_EXP_ALP_912_THR->Get("Hist1D_y1_e2");
	TH1F *hist_e3_00 = (TH1F*)table_EXP_ALP_912_THR->Get("Hist1D_y1_e3");
	// Populate hist
	for (int i = 1; i <= hist_xx_00->GetNbinsX(); ++i)
		hist_xx_00->SetBinError(i, std::sqrt(hist_e1_00->GetBinContent(i)*hist_e1_00->GetBinContent(i) + hist_e2_00->GetBinContent(i)*hist_e2_00->GetBinContent(i) + hist_e3_00->GetBinContent(i)*hist_e3_00->GetBinContent(i) ) );
	// Invert hist
	TH1D* hist_EXP_ALP_912_THR = InvertThrust(hist_xx_00);

	// Access grph
	TGraphAsymmErrors* grph_EXP_ALP_912_THR = (TGraphAsymmErrors*)table_EXP_ALP_912_THR->Get("Graph1D_y1");
	// Invert
	for (int i = 0; i < grph_EXP_ALP_912_THR->GetN(); ++i) {
		// Access T
		grph_EXP_ALP_912_THR->GetPoint(i, x, y);
		// Access errors
		double exl = grph_EXP_ALP_912_THR->GetErrorXlow(i);
		double exh = grph_EXP_ALP_912_THR->GetErrorXhigh(i);
		double eyl = grph_EXP_ALP_912_THR->GetErrorYlow(i);
		double eyh = grph_EXP_ALP_912_THR->GetErrorYhigh(i);
		// Overwrite
		grph_EXP_ALP_912_THR->SetPoint(i, 1.0 - x, y);
		grph_EXP_ALP_912_THR->SetPointError(i, exl, exh, eyl, eyh);
	}
	// Rename
	grph_EXP_ALP_912_THR->SetName("grph_EXP_ALP_912_THR");
	hist_EXP_ALP_912_THR->SetName("hist_EXP_ALP_912_THR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_ALP_161_THR = (TDirectory*)input_EXP_ALP->Get("Table 56");

	// Access hist
	TH1F *hist_xx_01 = (TH1F*)table_EXP_ALP_161_THR->Get("Hist1D_y1");
	TH1F *hist_e1_01 = (TH1F*)table_EXP_ALP_161_THR->Get("Hist1D_y1_e1");
	TH1F *hist_e2_01 = (TH1F*)table_EXP_ALP_161_THR->Get("Hist1D_y1_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_01->GetNbinsX(); ++i)
		hist_xx_01->SetBinError(i, std::sqrt(hist_e1_01->GetBinContent(i)*hist_e1_01->GetBinContent(i) + hist_e2_01->GetBinContent(i)*hist_e2_01->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_ALP_161_THR = (TH1F*)hist_xx_01->Clone("hist_EXP_ALP_161_THR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_ALP_161_THR = (TGraphAsymmErrors*)table_EXP_ALP_161_THR->Get("Graph1D_y1");
	// Rename
	grph_EXP_ALP_161_THR->SetName("grph_EXP_ALP_161_THR");
	hist_EXP_ALP_161_THR->SetName("hist_EXP_ALP_161_THR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_ALP_183_THR = (TDirectory*)input_EXP_ALP->Get("Table 58");

	// Access hist
	TH1F *hist_xx_02 = (TH1F*)table_EXP_ALP_183_THR->Get("Hist1D_y1");
	TH1F *hist_e1_02 = (TH1F*)table_EXP_ALP_183_THR->Get("Hist1D_y1_e1");
	TH1F *hist_e2_02 = (TH1F*)table_EXP_ALP_183_THR->Get("Hist1D_y1_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_02->GetNbinsX(); ++i)
		hist_xx_02->SetBinError(i, std::sqrt(hist_e1_02->GetBinContent(i)*hist_e1_02->GetBinContent(i) + hist_e2_02->GetBinContent(i)*hist_e2_02->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_ALP_183_THR = (TH1F*)hist_xx_02->Clone("hist_EXP_ALP_183_THR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_ALP_183_THR = (TGraphAsymmErrors*)table_EXP_ALP_183_THR->Get("Graph1D_y1");
	// Rename
	grph_EXP_ALP_183_THR->SetName("grph_EXP_ALP_183_THR");
	hist_EXP_ALP_183_THR->SetName("hist_EXP_ALP_183_THR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_ALP_200_THR = (TDirectory*)input_EXP_ALP->Get("Table 60");

	// Access hist
	TH1F *hist_xx_03 = (TH1F*)table_EXP_ALP_200_THR->Get("Hist1D_y1");
	TH1F *hist_e1_03 = (TH1F*)table_EXP_ALP_200_THR->Get("Hist1D_y1_e1");
	TH1F *hist_e2_03 = (TH1F*)table_EXP_ALP_200_THR->Get("Hist1D_y1_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_03->GetNbinsX(); ++i)
		hist_xx_03->SetBinError(i, std::sqrt(hist_e1_03->GetBinContent(i)*hist_e1_03->GetBinContent(i) + hist_e2_03->GetBinContent(i)*hist_e2_03->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_ALP_200_THR = (TH1F*)hist_xx_03->Clone("hist_EXP_ALP_200_THR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_ALP_200_THR = (TGraphAsymmErrors*)table_EXP_ALP_200_THR->Get("Graph1D_y1");
	// Rename
	grph_EXP_ALP_200_THR->SetName("grph_EXP_ALP_200_THR");
	hist_EXP_ALP_200_THR->SetName("hist_EXP_ALP_200_THR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_ALP_912_CPR = (TDirectory*)input_EXP_ALP->Get("Table 86");

	// Access hist
	TH1F *hist_xx_04 = (TH1F*)table_EXP_ALP_912_CPR->Get("Hist1D_y1");
	TH1F *hist_e1_04 = (TH1F*)table_EXP_ALP_912_CPR->Get("Hist1D_y1_e1");
	TH1F *hist_e2_04 = (TH1F*)table_EXP_ALP_912_CPR->Get("Hist1D_y1_e2");
	TH1F *hist_e3_04 = (TH1F*)table_EXP_ALP_912_CPR->Get("Hist1D_y1_e3");
	// Populate hist
	for (int i = 1; i <= hist_xx_04->GetNbinsX(); ++i)
		hist_xx_04->SetBinError(i, std::sqrt(hist_e1_04->GetBinContent(i)*hist_e1_04->GetBinContent(i) + hist_e2_04->GetBinContent(i)*hist_e2_04->GetBinContent(i) + hist_e3_04->GetBinContent(i)*hist_e3_04->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_ALP_912_CPR = (TH1F*)hist_xx_04->Clone("hist_EXP_ALP_912_CPR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_ALP_912_CPR = (TGraphAsymmErrors*)table_EXP_ALP_912_CPR->Get("Graph1D_y1");
	// Rename
	grph_EXP_ALP_912_CPR->SetName("grph_EXP_ALP_912_CPR");
	hist_EXP_ALP_912_CPR->SetName("hist_EXP_ALP_912_CPR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_ALP_161_CPR = (TDirectory*)input_EXP_ALP->Get("Table 88");

	// Access hist
	TH1F *hist_xx_05 = (TH1F*)table_EXP_ALP_161_CPR->Get("Hist1D_y1");
	TH1F *hist_e1_05 = (TH1F*)table_EXP_ALP_161_CPR->Get("Hist1D_y1_e1");
	TH1F *hist_e2_05 = (TH1F*)table_EXP_ALP_161_CPR->Get("Hist1D_y1_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_05->GetNbinsX(); ++i)
		hist_xx_05->SetBinError(i, std::sqrt(hist_e1_05->GetBinContent(i)*hist_e1_05->GetBinContent(i) + hist_e2_05->GetBinContent(i)*hist_e2_05->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_ALP_161_CPR = (TH1F*)hist_xx_05->Clone("hist_EXP_ALP_161_CPR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_ALP_161_CPR = (TGraphAsymmErrors*)table_EXP_ALP_161_CPR->Get("Graph1D_y1");
	// Rename
	grph_EXP_ALP_161_CPR->SetName("grph_EXP_ALP_161_CPR");
	hist_EXP_ALP_161_CPR->SetName("hist_EXP_ALP_161_CPR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_ALP_183_CPR = (TDirectory*)input_EXP_ALP->Get("Table 90");

	// Access hist
	TH1F *hist_xx_06 = (TH1F*)table_EXP_ALP_183_CPR->Get("Hist1D_y1");
	TH1F *hist_e1_06 = (TH1F*)table_EXP_ALP_183_CPR->Get("Hist1D_y1_e1");
	TH1F *hist_e2_06 = (TH1F*)table_EXP_ALP_183_CPR->Get("Hist1D_y1_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_06->GetNbinsX(); ++i)
		hist_xx_06->SetBinError(i, std::sqrt(hist_e1_06->GetBinContent(i)*hist_e1_06->GetBinContent(i) + hist_e2_06->GetBinContent(i)*hist_e2_06->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_ALP_183_CPR = (TH1F*)hist_xx_06->Clone("hist_EXP_ALP_183_CPR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_ALP_183_CPR = (TGraphAsymmErrors*)table_EXP_ALP_183_CPR->Get("Graph1D_y1");
	// Rename
	grph_EXP_ALP_183_CPR->SetName("grph_EXP_ALP_183_CPR");
	hist_EXP_ALP_183_CPR->SetName("hist_EXP_ALP_183_CPR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_ALP_200_CPR = (TDirectory*)input_EXP_ALP->Get("Table 92");

	// Access hist
	TH1F *hist_xx_07 = (TH1F*)table_EXP_ALP_200_CPR->Get("Hist1D_y1");
	TH1F *hist_e1_07 = (TH1F*)table_EXP_ALP_200_CPR->Get("Hist1D_y1_e1");
	TH1F *hist_e2_07 = (TH1F*)table_EXP_ALP_200_CPR->Get("Hist1D_y1_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_07->GetNbinsX(); ++i)
		hist_xx_07->SetBinError(i, std::sqrt(hist_e1_07->GetBinContent(i)*hist_e1_07->GetBinContent(i) + hist_e2_07->GetBinContent(i)*hist_e2_07->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_ALP_200_CPR = (TH1F*)hist_xx_07->Clone("hist_EXP_ALP_200_CPR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_ALP_200_CPR = (TGraphAsymmErrors*)table_EXP_ALP_200_CPR->Get("Graph1D_y1");
	// Rename
	grph_EXP_ALP_200_CPR->SetName("grph_EXP_ALP_200_CPR");
	hist_EXP_ALP_200_CPR->SetName("hist_EXP_ALP_200_CPR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_LL3_912_THR = (TDirectory*)input_EXP_LL3->Get("Table 47");

	// Access hist
	TH1F *hist_xx_08 = (TH1F*)table_EXP_LL3_912_THR->Get("Hist1D_y2");
	TH1F *hist_e1_08 = (TH1F*)table_EXP_LL3_912_THR->Get("Hist1D_y2_e1");
	TH1F *hist_e2_08 = (TH1F*)table_EXP_LL3_912_THR->Get("Hist1D_y2_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_08->GetNbinsX(); ++i)
		hist_xx_08->SetBinError(i, std::sqrt(hist_e1_08->GetBinContent(i)*hist_e1_08->GetBinContent(i) + hist_e2_08->GetBinContent(i)*hist_e2_08->GetBinContent(i)) );
	// Invert hist
	TH1D* hist_EXP_LL3_912_THR = InvertThrust(hist_xx_08);

	// Access grph
	TGraphAsymmErrors* grph_EXP_LL3_912_THR = (TGraphAsymmErrors*)table_EXP_LL3_912_THR->Get("Graph1D_y2");
	// Invert
	for (int i = 0; i < grph_EXP_LL3_912_THR->GetN(); ++i) {
		// Access T
		grph_EXP_LL3_912_THR->GetPoint(i, x, y);
		// Access errors
		double exl = grph_EXP_LL3_912_THR->GetErrorXlow(i);
		double exh = grph_EXP_LL3_912_THR->GetErrorXhigh(i);
		double eyl = grph_EXP_LL3_912_THR->GetErrorYlow(i);
		double eyh = grph_EXP_LL3_912_THR->GetErrorYhigh(i);
		// Overwrite
		grph_EXP_LL3_912_THR->SetPoint(i, 1.0 - x, y);
		grph_EXP_LL3_912_THR->SetPointError(i, exl, exh, eyl, eyh);
	}
	// Rename
	grph_EXP_LL3_912_THR->SetName("grph_EXP_LL3_912_THR");
	hist_EXP_LL3_912_THR->SetName("hist_EXP_LL3_912_THR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_LL3_161_THR = (TDirectory*)input_EXP_LL3->Get("Table 23");

	// Access hist
	TH1F *hist_xx_09 = (TH1F*)table_EXP_LL3_161_THR->Get("Hist1D_y3");
	TH1F *hist_e1_09 = (TH1F*)table_EXP_LL3_161_THR->Get("Hist1D_y3_e1");
	TH1F *hist_e2_09 = (TH1F*)table_EXP_LL3_161_THR->Get("Hist1D_y3_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_09->GetNbinsX(); ++i)
		hist_xx_09->SetBinError(i, std::sqrt(hist_e1_09->GetBinContent(i)*hist_e1_09->GetBinContent(i) + hist_e2_09->GetBinContent(i)*hist_e2_09->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_LL3_161_THR = (TH1F*)hist_xx_09->Clone("hist_EXP_LL3_161_THR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_LL3_161_THR = (TGraphAsymmErrors*)table_EXP_LL3_161_THR->Get("Graph1D_y3");
	// Rename
	grph_EXP_LL3_161_THR->SetName("grph_EXP_LL3_161_THR");
	hist_EXP_LL3_161_THR->SetName("hist_EXP_LL3_161_THR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_LL3_183_THR = (TDirectory*)input_EXP_LL3->Get("Table 24");

	// Access hist
	TH1F *hist_xx_10 = (TH1F*)table_EXP_LL3_183_THR->Get("Hist1D_y2");
	TH1F *hist_e1_10 = (TH1F*)table_EXP_LL3_183_THR->Get("Hist1D_y2_e1");
	TH1F *hist_e2_10 = (TH1F*)table_EXP_LL3_183_THR->Get("Hist1D_y2_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_10->GetNbinsX(); ++i)
		hist_xx_10->SetBinError(i, std::sqrt(hist_e1_10->GetBinContent(i)*hist_e1_10->GetBinContent(i) + hist_e2_10->GetBinContent(i)*hist_e2_10->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_LL3_183_THR = (TH1F*)hist_xx_10->Clone("hist_EXP_LL3_183_THR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_LL3_183_THR = (TGraphAsymmErrors*)table_EXP_LL3_183_THR->Get("Graph1D_y2");
	// Rename
	grph_EXP_LL3_183_THR->SetName("grph_EXP_LL3_183_THR");
	hist_EXP_LL3_183_THR->SetName("hist_EXP_LL3_183_THR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_LL3_200_THR = (TDirectory*)input_EXP_LL3->Get("Table 25");

	// Access hist
	TH1F *hist_xx_11 = (TH1F*)table_EXP_LL3_200_THR->Get("Hist1D_y2");
	TH1F *hist_e1_11 = (TH1F*)table_EXP_LL3_200_THR->Get("Hist1D_y2_e1");
	TH1F *hist_e2_11 = (TH1F*)table_EXP_LL3_200_THR->Get("Hist1D_y2_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_11->GetNbinsX(); ++i)
		hist_xx_11->SetBinError(i, std::sqrt(hist_e1_11->GetBinContent(i)*hist_e1_11->GetBinContent(i) + hist_e2_11->GetBinContent(i)*hist_e2_11->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_LL3_200_THR = (TH1F*)hist_xx_11->Clone("hist_EXP_LL3_200_THR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_LL3_200_THR = (TGraphAsymmErrors*)table_EXP_LL3_200_THR->Get("Graph1D_y2");
	// Rename
	grph_EXP_LL3_200_THR->SetName("grph_EXP_LL3_200_THR");
	hist_EXP_LL3_200_THR->SetName("hist_EXP_LL3_200_THR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_LL3_912_CPR = (TDirectory*)input_EXP_LL3->Get("Table 51");

	// Access hist
	TH1F *hist_xx_12 = (TH1F*)table_EXP_LL3_912_CPR->Get("Hist1D_y2");
	TH1F *hist_e1_12 = (TH1F*)table_EXP_LL3_912_CPR->Get("Hist1D_y2_e1");
	TH1F *hist_e2_12 = (TH1F*)table_EXP_LL3_912_CPR->Get("Hist1D_y2_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_12->GetNbinsX(); ++i)
		hist_xx_12->SetBinError(i, std::sqrt(hist_e1_12->GetBinContent(i)*hist_e1_12->GetBinContent(i) + hist_e2_12->GetBinContent(i)*hist_e2_12->GetBinContent(i)) );
	// Clone hist
	TH1F *hist_EXP_LL3_912_CPR = (TH1F*)hist_xx_12->Clone("hist_EXP_LL3_912_CPR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_LL3_912_CPR = (TGraphAsymmErrors*)table_EXP_LL3_912_CPR->Get("Graph1D_y2");
	// Rename
	grph_EXP_LL3_912_CPR->SetName("grph_EXP_LL3_912_CPR");
	hist_EXP_LL3_912_CPR->SetName("hist_EXP_LL3_912_CPR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_LL3_161_CPR = (TDirectory*)input_EXP_LL3->Get("Table 41");

	// Access hist
	TH1F *hist_xx_13 = (TH1F*)table_EXP_LL3_161_CPR->Get("Hist1D_y3");
	TH1F *hist_e1_13 = (TH1F*)table_EXP_LL3_161_CPR->Get("Hist1D_y3_e1");
	TH1F *hist_e2_13 = (TH1F*)table_EXP_LL3_161_CPR->Get("Hist1D_y3_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_13->GetNbinsX(); ++i)
		hist_xx_13->SetBinError(i, std::sqrt(hist_e1_13->GetBinContent(i)*hist_e1_13->GetBinContent(i) + hist_e2_13->GetBinContent(i)*hist_e2_13->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_LL3_161_CPR = (TH1F*)hist_xx_13->Clone("hist_EXP_LL3_161_CPR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_LL3_161_CPR = (TGraphAsymmErrors*)table_EXP_LL3_161_CPR->Get("Graph1D_y3");
	// Rename
	grph_EXP_LL3_161_CPR->SetName("grph_EXP_LL3_161_CPR");
	hist_EXP_LL3_161_CPR->SetName("hist_EXP_LL3_161_CPR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_LL3_183_CPR = (TDirectory*)input_EXP_LL3->Get("Table 42");
	
	// Access hist
	TH1F *hist_xx_14 = (TH1F*)table_EXP_LL3_183_CPR->Get("Hist1D_y2");
	TH1F *hist_e1_14 = (TH1F*)table_EXP_LL3_183_CPR->Get("Hist1D_y2_e1");
	TH1F *hist_e2_14 = (TH1F*)table_EXP_LL3_183_CPR->Get("Hist1D_y2_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_14->GetNbinsX(); ++i)
		hist_xx_14->SetBinError(i, std::sqrt(hist_e1_14->GetBinContent(i)*hist_e1_14->GetBinContent(i) + hist_e2_14->GetBinContent(i)*hist_e2_14->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_LL3_183_CPR = (TH1F*)hist_xx_14->Clone("hist_EXP_LL3_183_CPR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_LL3_183_CPR = (TGraphAsymmErrors*)table_EXP_LL3_183_CPR->Get("Graph1D_y2");
	// Rename
	grph_EXP_LL3_183_CPR->SetName("grph_EXP_LL3_183_CPR");
	hist_EXP_LL3_183_CPR->SetName("hist_EXP_LL3_183_CPR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_LL3_200_CPR = (TDirectory*)input_EXP_LL3->Get("Table 43");

	// Access hist
	TH1F *hist_xx_15 = (TH1F*)table_EXP_LL3_200_CPR->Get("Hist1D_y2");
	TH1F *hist_e1_15 = (TH1F*)table_EXP_LL3_200_CPR->Get("Hist1D_y2_e1");
	TH1F *hist_e2_15 = (TH1F*)table_EXP_LL3_200_CPR->Get("Hist1D_y2_e2");
	// Populate hist
	for (int i = 1; i <= hist_xx_15->GetNbinsX(); ++i)
		hist_xx_15->SetBinError(i, std::sqrt(hist_e1_15->GetBinContent(i)*hist_e1_15->GetBinContent(i) + hist_e2_15->GetBinContent(i)*hist_e2_15->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_LL3_200_CPR = (TH1F*)hist_xx_15->Clone("hist_EXP_LL3_200_CPR");

	// Access grph
	TGraphAsymmErrors* grph_EXP_LL3_200_CPR = (TGraphAsymmErrors*)table_EXP_LL3_200_CPR->Get("Graph1D_y2");
	// Rename
	grph_EXP_LL3_200_CPR->SetName("grph_EXP_LL3_200_CPR");
	hist_EXP_LL3_200_CPR->SetName("hist_EXP_LL3_200_CPR");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Access table
	TDirectory *table_EXP_ALP_912_RHO = (TDirectory*)input_EXP_ALP->Get("Table 62");

	// Access hist
	TH1F *hist_xx_16 = (TH1F*)table_EXP_ALP_912_RHO->Get("Hist1D_y1");
	TH1F *hist_e1_16 = (TH1F*)table_EXP_ALP_912_RHO->Get("Hist1D_y1_e1");
	TH1F *hist_e2_16 = (TH1F*)table_EXP_ALP_912_RHO->Get("Hist1D_y1_e2");
	TH1F *hist_e3_16 = (TH1F*)table_EXP_ALP_912_RHO->Get("Hist1D_y1_e3");
	// Populate hist
	for (int i = 1; i <= hist_xx_16->GetNbinsX(); ++i)
		hist_xx_16->SetBinError(i, std::sqrt(hist_e1_16->GetBinContent(i)*hist_e1_16->GetBinContent(i) + hist_e2_16->GetBinContent(i)*hist_e2_16->GetBinContent(i) + hist_e3_16->GetBinContent(i)*hist_e3_16->GetBinContent(i) ) );
	// Clone hist
	TH1F *hist_EXP_ALP_912_RHO = (TH1F*)hist_xx_16->Clone("hist_EXP_ALP_912_RHO");

	// Access grph
	TGraphAsymmErrors* grph_EXP_ALP_912_RHO = (TGraphAsymmErrors*)table_EXP_ALP_912_RHO->Get("Graph1D_y1");
	// Rename
	grph_EXP_ALP_912_RHO->SetName("grph_EXP_ALP_912_RHO");
	hist_EXP_ALP_912_RHO->SetName("hist_EXP_ALP_912_RHO");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Define output
	TFile *output = new TFile("3-LEPdata/EXPDATA.root", "RECREATE");

	output->cd();
	grph_EXP_ALP_912_THR->Write(); hist_EXP_ALP_912_THR->Write();
	grph_EXP_ALP_161_THR->Write(); hist_EXP_ALP_161_THR->Write();
	grph_EXP_ALP_183_THR->Write(); hist_EXP_ALP_183_THR->Write();
	grph_EXP_ALP_200_THR->Write(); hist_EXP_ALP_200_THR->Write();
	grph_EXP_ALP_912_CPR->Write(); hist_EXP_ALP_912_CPR->Write();
	grph_EXP_ALP_161_CPR->Write(); hist_EXP_ALP_161_CPR->Write();
	grph_EXP_ALP_183_CPR->Write(); hist_EXP_ALP_183_CPR->Write();
	grph_EXP_ALP_200_CPR->Write(); hist_EXP_ALP_200_CPR->Write();
	
	grph_EXP_LL3_912_THR->Write(); hist_EXP_LL3_912_THR->Write();
	grph_EXP_LL3_161_THR->Write(); hist_EXP_LL3_161_THR->Write();
	grph_EXP_LL3_183_THR->Write(); hist_EXP_LL3_183_THR->Write();
	grph_EXP_LL3_200_THR->Write(); hist_EXP_LL3_200_THR->Write();
	grph_EXP_LL3_912_CPR->Write(); hist_EXP_LL3_912_CPR->Write();
	grph_EXP_LL3_161_CPR->Write(); hist_EXP_LL3_161_CPR->Write();
	grph_EXP_LL3_183_CPR->Write(); hist_EXP_LL3_183_CPR->Write();
	grph_EXP_LL3_200_CPR->Write(); hist_EXP_LL3_200_CPR->Write();
	
	grph_EXP_ALP_912_RHO->Write(); hist_EXP_ALP_912_RHO->Write();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	output->Close(); delete output;
	
	TFile *input_EXPDATA = TFile::Open("3-LEPdata/EXPDATA.root");
	new TBrowser;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

}