#include <TLatex.h>
#include <TGraph.h>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "HttStyles.h"

Double_t fitFunc_Exp3Par_tau(Double_t *x, Double_t *par) {
    /*if (x[0]>20 && x[0]<=27) return par[0] + par[1]*(TMath::Exp(par[2] * x[0])); 
    else if (x[0]>27) return par[3] + par[4]*(TMath::Exp(par[5] * x[0]));
    else return 0;*/
    return par[0] + par[1]*(TMath::Landau(x[0],par[2],par[3],0));
}

Double_t fitFunc_Exp3Par_mu(Double_t *x, Double_t *par) {
    /*if (x[0]>10 && x[0]<=17) return par[0] + par[1]*(TMath::Exp(par[2] * x[0]));
    else if (x[0]>17) return par[3] + par[4]*(TMath::Exp(par[5] * x[0]));
    else return 0;*/
    return par[0] + par[1]*(TMath::Landau(x[0],par[2],par[3],0));
}

Double_t fitFunc_Exp3Par_ele(Double_t *x, Double_t *par) {
    /*if (x[0]>10 && x[0]<=20) return par[0] + par[1]*(TMath::Exp(par[2] * x[0]));
    else if (x[0]>20) return par[3] + par[4]*(TMath::Exp(par[5] * x[0]));
    else return 0;*/
    return par[0] + par[1]*(TMath::Landau(x[0],par[2],par[3],0));
}

void M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, TH2F * hist2D_lep, Double_t fMin, Double_t fMax) {
    cout << "############################################################" << endl;
    cout << "\n\n    -->  " << num << "  over  " << denum << endl;
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    double ConstFR = Numerator->Integral(0, 100)*1.0 / Denumerator->Integral(0, 100);
    cout << "-------------------------------------------------" << endl;
    cout << " " << WP << " " << num.c_str() << " = " << Numerator->Integral(0, 100) << "/" << Denumerator->Integral(11, 400) << "  =  " << ConstFR << endl;
    cout << "-------------------------------------------------" << endl;
    TH1D *Num_rebin = (TH1D*) Numerator->Rebin(5);
    TH1D *Denum_rebin = (TH1D*) Denumerator->Rebin(5);

    TGraphAsymmErrors * TGraph_FR = new TGraphAsymmErrors(Num_rebin, Denum_rebin);


    int nPar = 4; // number of parameters in the fit
    TF1 * theFit = new TF1("theFit", fitFunc_Exp3Par_tau, fMin, fMax, nPar);

    theFit->SetParameter(0, -0.0);
    theFit->SetParameter(1, 0.5);
    theFit->SetParameter(2, 30.0);
    theFit->SetParameter(3, 5.00);

    if (type=="Exp3Par_ele"){
       theFit = new TF1("theFit", fitFunc_Exp3Par_ele, fMin, fMax, nPar);
       theFit->SetParameter(0, -0.0);
       theFit->SetParameter(1, 0.5);
       theFit->SetParameter(2, 30.0);
       theFit->SetParameter(3, 5.0);
    }
    if (type=="Exp3Par_mu"){
       theFit = new TF1("theFit", fitFunc_Exp3Par_mu, fMin, fMax, nPar);
       theFit->SetParameter(0, 0.0);
       theFit->SetParameter(1, 0.5);
       theFit->SetParameter(2, 30.0);
       theFit->SetParameter(3, 5.0);
    }

    float xAxisMax = 120;
    TGraph_FR->Fit("theFit", "R0");
    SetStyle();

    TCanvas* canvas = new TCanvas("canvas", "", 800, 800);
    //canvas->SetLogy();
    canvas->SetTitle("");
    //TGraph_FR->GetYaxis()->SetRangeUser(.001, 10);
    TGraph_FR->GetYaxis()->SetRangeUser(0, 0.18);
    if (num.find("tau_tt") < 140)
       TGraph_FR->GetYaxis()->SetRangeUser(0, 0.60);
    TGraph_FR->GetYaxis()->SetTitle("Misidentification rate");
    TGraph_FR->GetXaxis()->SetRangeUser(0, xAxisMax);
    TGraph_FR->GetXaxis()->SetTitle("p_{T} (GeV)");
    TGraph_FR->SetTitle("");
    TGraph_FR->SetLineColor(1);
    TGraph_FR->SetMarkerStyle(21);
    TGraph_FR->Draw("PAE");
    theFit->SetLineColor(2);
    theFit->SetLineWidth(2);
    theFit->Draw("SAME");
    std::string outNaming = "plots/fit" + num + ".pdf";
    std::string outNamingPng = "plots/fit" + num + ".png";

    TLatex t = TLatex();
    t.SetNDC();
    t.SetTextFont(62);
    t.SetTextAlign(12);
    t.SetTextSize(0.045);
    t.DrawLatex(0.2, .85, "CMS");
    t.DrawLatex(0.5, .95, "35.9 fb^{-1} (13 TeV)");
    TLatex t2 = TLatex();
    t2.SetNDC();
    t2.SetTextFont(52);
    t2.SetTextAlign(12);
    t2.SetTextSize(0.030);
    t2.DrawLatex(0.2, .80, "Preliminary");
    TLatex t3 = TLatex();
    t3.SetNDC();
    t3.SetTextFont(52);
    t3.SetTextAlign(12);
    t3.SetTextSize(0.040);
    std::string lepName;
    std::string region;
    if (num.find("mu_tight") < 140) lepName = "j #rightarrow #mu (tight)";
    else if (num.find("mu_loose") < 140) lepName = "j #rightarrow #mu (loose)";
    else if (num.find("ele_tight") < 140) lepName = "j #rightarrow e (tight)";
    else if (num.find("ele_loose") < 140) lepName = "j #rightarrow e (loose)";
    else if (num.find("tau_lt") < 140) lepName = "j #rightarrow #tau_{h} (loose)";
    else if (num.find("tau_tt") < 140) lepName = "j #rightarrow #tau_{h} (medium)";
    t3.DrawLatex(0.5, .85, lepName.c_str());
    t3.DrawLatex(0.5, .80, region.c_str());
    canvas->SaveAs(outNaming.c_str());
    canvas->SaveAs(outNamingPng.c_str());

    Double_t TauLegParameters[nPar];
    theFit->GetParameters(TauLegParameters);

    for (int i = 0; i < nPar; i++) {
	hist2D_lep->SetBinContent(WP, (2 * i + 1), TauLegParameters[i]);
        hist2D_lep->SetBinContent(WP, (2 * i + 2), theFit->GetParError(i));
    }
    hist2D_lep->SetBinContent(WP, 15, ConstFR); 

}

void Measure_FR_Landau() {

    TFile *FR_File = new TFile("FitValues_FR.root", "RECREATE");

    TH2F * Fit_Value = new TH2F("Fit_Value", "Fit_Value", 20, 0, 20, 20, 0, 20);

    /*M_FR(1, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_tau_tt_Num", "FR_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(2, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_tau_lt_Num", "FR_tau_lt_Den", Fit_Value, 20, 120);
    M_FR(4, "Exp3Par_ele", "files_nominal/data_obs.root", "FR_ele_tight_Num", "FR_ele_Den", Fit_Value, 10, 120);
    M_FR(6, "Exp3Par_mu", "files_nominal/data_obs.root", "FR_mu_tight_Num", "FR_mu_Den", Fit_Value, 10, 120);*/

    M_FR(1, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_tau_tt_Num", "FR_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(2, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_tau_lt_Num", "FR_tau_lt_Den", Fit_Value, 20, 120);
    M_FR(4, "Exp3Par_ele", "files_nominal/data_obs.root", "FR_ele_tight_Num", "FR_ele_Den", Fit_Value, 10, 120);
    M_FR(6, "Exp3Par_mu", "files_nominal/data_obs.root", "FR_mu_tight_Num", "FR_mu_Den", Fit_Value, 10, 120);

    M_FR(10, "Exp3Par_ele", "files_nominal/data_obs.root", "FR_B_ele_tight_Num", "FR_B_ele_Den", Fit_Value, 10, 120);
    M_FR(11, "Exp3Par_ele", "files_nominal/data_obs.root", "FR_E_ele_tight_Num", "FR_E_ele_Den", Fit_Value, 10, 120);
    M_FR(12, "Exp3Par_mu", "files_nominal/data_obs.root", "FR_B_mu_tight_Num", "FR_B_mu_Den", Fit_Value, 10, 120);
    M_FR(13, "Exp3Par_mu", "files_nominal/data_obs.root", "FR_E_mu_tight_Num", "FR_E_mu_Den", Fit_Value, 10, 120);
    M_FR(14, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_B_tau_tt_Num", "FR_B_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(15, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_E_tau_tt_Num", "FR_E_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(16, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_DM0_B_tau_tt_Num", "FR_DM0_B_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(17, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_DM0_E_tau_tt_Num", "FR_DM0_E_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(18, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_DM0_tau_tt_Num", "FR_DM0_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(19, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_DM1_B_tau_tt_Num", "FR_DM1_B_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(20, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_DM1_E_tau_tt_Num", "FR_DM1_E_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(21, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_DM1_tau_tt_Num", "FR_DM1_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(22, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_DM10_B_tau_tt_Num", "FR_DM10_B_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(23, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_DM10_E_tau_tt_Num", "FR_DM10_E_tau_tt_Den", Fit_Value, 20, 120);
    M_FR(24, "Exp3Par_tau", "files_nominal/data_obs.root", "FR_DM10_tau_tt_Num", "FR_DM10_tau_tt_Den", Fit_Value, 20, 120);

    FR_File->Write();
    FR_File->Close();
}

