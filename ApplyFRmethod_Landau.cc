#include "TROOT.h"
#include "TFile.h"
#include "TMath.h"
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
#include <map>
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

double fitFunc_loosetau(float pt, float par0, float par1, float par2, float par3) {
    return par0 + par1*(TMath::Landau(pt,par2,par3,0));
}

double fitFunc_mediumtau(float pt, float par0, float par1, float par2, float par3) {
    return par0 + par1*(TMath::Landau(pt,par2,par3,0));
}

double fitFunc_ele(float pt, float par0, float par1, float par2, float par3) {
    return TMath::Min(0.10,par0 + par1*(TMath::Landau(pt,par2,par3,0)));
}

double fitFunc_mu(float pt, float par0, float par1, float par2, float par3) {
    return TMath::Min(0.15,par0 + par1*(TMath::Landau(pt,par2,par3,0)));
}

int main(int argc, char** argv) {
    bool isclosejet=true;
    float tes=0;
    std::string input = *(argv + 1);
    std::string output = *(argv + 2);

    float cat0_mmmt=0.0;
    float cat1_mmmt=0.0;
    float cat2_mmmt=0.0;

    float cat0_eemt=0.0;
    float cat1_eemt=0.0;
    float cat2_eemt=0.0;

    float cat0_mmet=0.0;
    float cat1_mmet=0.0;
    float cat2_mmet=0.0;

    float cat0_eeet=0.0;
    float cat1_eeet=0.0;
    float cat2_eeet=0.0;

    float cat0_mmtt=0.0;
    float cat1_mmtt=0.0;
    float cat2_mmtt=0.0;

    float cat0_eett=0.0;
    float cat1_eett=0.0;
    float cat2_eett=0.0;

    float cat0_mmem=0.0;
    float cat1_mmem=0.0;
    float cat2_mmem=0.0;

    float cat0_eeem=0.0;
    float cat1_eeem=0.0;
    float cat2_eeem=0.0;

    TFile *f_Double = new TFile(input.c_str());
    TTree *run_Tree = (TTree*) f_Double->Get("BG_Tree");

    TFile *f_FR = new TFile("FitValues_FR.root");
    TH2F *frvalues = (TH2F*) f_FR->Get("Fit_Value");

    int channel_,subchannel_;
    float pt_3_,pt_4_,w_,var_,closeJetPt_3_,closeJetPt_4_,decayMode_3_,decayMode_4_;
    bool isHigh_, isSR_;

    run_Tree->SetBranchAddress("channel_", &channel_);
    run_Tree->SetBranchAddress("subchannel_", &subchannel_);
    run_Tree->SetBranchAddress("pt_3_", &pt_3_);
    run_Tree->SetBranchAddress("pt_4_", &pt_4_);
    run_Tree->SetBranchAddress("closeJetPt_3_", &closeJetPt_3_);
    run_Tree->SetBranchAddress("closeJetPt_4_", &closeJetPt_4_);
    run_Tree->SetBranchAddress("w_", &w_);
    run_Tree->SetBranchAddress("var_", &var_);
    run_Tree->SetBranchAddress("isHigh_", &isHigh_);
    run_Tree->SetBranchAddress("isSR_", &isSR_);
    run_Tree->SetBranchAddress("decayMode_3_", &decayMode_3_);
    run_Tree->SetBranchAddress("decayMode_3_", &decayMode_4_);

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");

   //float bins0[] = {40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400,420,440};//
   //float bins1[] = {50,80,110,140,170,200,230,260,290,320,350,380,410};
   //float bins0[] = {14,18,22,26,30,34,38,42,46,50,54,58,62,66};
   //float bins1[] = {14,18,22,26,30,34,38,42,46,50,54,58,62,66};
   //float bins0[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140};
   //float bins1[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140};
   //float bins0[] = {19,24,29,34,39,44,49,54,59,64};
   //float bins1[] = {19,24,29,34,39,44,49,54,59,64};

   //float bins0[] = {-100,-80,-60,-40,-20,-10,0,10,20,40,60,80,100};
   //float bins1[] = {-100,-80,-60,-40,-20,-10,0,10,20,40,60,80,100};
   //float bins0[] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400};
   //float bins1[] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400};
   //float bins0[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,120,180};
   //float bins1[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,120,180};
   float binsh[] = {0,500};
   //float bins0[] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
   //float bins1[] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
   //float bins0[] = {0,20,40,60,80,100,120,140};
   //float bins1[] = {0,20,40,60,80,100,120,140};

   //float bins0[] = {0,20,40,60,80,100,120,140};
   //float bins1[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140};

   float bins0[] = {0,20,40,60,80,100,120,140,160,180,200};
   float bins1[] = {0,20,40,60,80,100,120,140,160,180,200};

   //float bins0[] = {0,0.4,0.8,1.2,1.6,2.0,2.4};
   //float bins1[] = {0,0.4,0.8,1.2,1.6,2.0,2.4};
   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;
   int  binnum1 = sizeof(bins1)/sizeof(Float_t) - 1;
   int  binnumh = sizeof(binsh)/sizeof(Float_t) - 1;

    TH1F *h_mmee=new TH1F ("h_mmee","h_mmee",binnum0,bins0);h_mmee->Sumw2();
    TH1F *h_mmem=new TH1F ("h_mmem","h_mmem",binnum1,bins1);h_mmem->Sumw2();
    TH1F *h_mmmm=new TH1F ("h_mmmm","h_mmmm",binnum0,bins0);h_mmmm->Sumw2();
    TH1F *h_mmet=new TH1F ("h_mmet","h_mmet",binnum1,bins1);h_mmet->Sumw2();
    TH1F *h_mmmt=new TH1F ("h_mmmt","h_mmmt",binnum1,bins1);h_mmmt->Sumw2();
    TH1F *h_mmtt=new TH1F ("h_mmtt","h_mmtt",binnum1,bins1);h_mmtt->Sumw2();
    TH1F *h_eeee=new TH1F ("h_eeee","h_eeee",binnum0,bins0);h_eeee->Sumw2();
    TH1F *h_eeem=new TH1F ("h_eeem","h_eeem",binnum1,bins1);h_eeem->Sumw2();
    TH1F *h_eemm=new TH1F ("h_eemm","h_eemm",binnum0,bins0);h_eemm->Sumw2();
    TH1F *h_eeet=new TH1F ("h_eeet","h_eeet",binnum1,bins1);h_eeet->Sumw2();
    TH1F *h_eemt=new TH1F ("h_eemt","h_eemt",binnum1,bins1);h_eemt->Sumw2();
    TH1F *h_eett=new TH1F ("h_eett","h_eett",binnum1,bins1);h_eett->Sumw2();

    TH1F *h_mmee_high=new TH1F ("h_mmee_high","h_mmee_high",binnumh,binsh);h_mmee_high->Sumw2();
    TH1F *h_mmem_high=new TH1F ("h_mmem_high","h_mmem_high",binnumh,binsh);h_mmem_high->Sumw2();
    TH1F *h_mmmm_high=new TH1F ("h_mmmm_high","h_mmmm_high",binnumh,binsh);h_mmmm_high->Sumw2();
    TH1F *h_mmet_high=new TH1F ("h_mmet_high","h_mmet_high",binnumh,binsh);h_mmet_high->Sumw2();
    TH1F *h_mmmt_high=new TH1F ("h_mmmt_high","h_mmmt_high",binnumh,binsh);h_mmmt_high->Sumw2();
    TH1F *h_mmtt_high=new TH1F ("h_mmtt_high","h_mmtt_high",binnumh,binsh);h_mmtt_high->Sumw2();
    TH1F *h_eeee_high=new TH1F ("h_eeee_high","h_eeee_high",binnumh,binsh);h_eeee_high->Sumw2();
    TH1F *h_eeem_high=new TH1F ("h_eeem_high","h_eeem_high",binnumh,binsh);h_eeem_high->Sumw2();
    TH1F *h_eemm_high=new TH1F ("h_eemm_high","h_eemm_high",binnumh,binsh);h_eemm_high->Sumw2();
    TH1F *h_eeet_high=new TH1F ("h_eeet_high","h_eeet_high",binnumh,binsh);h_eeet_high->Sumw2();
    TH1F *h_eemt_high=new TH1F ("h_eemt_high","h_eemt_high",binnumh,binsh);h_eemt_high->Sumw2();
    TH1F *h_eett_high=new TH1F ("h_eett_high","h_eett_high",binnumh,binsh);h_eett_high->Sumw2();

    ofstream myfile_mm;
    myfile_mm.open ("norm/Reducible_mm.txt");
    ofstream myfile_em;
    myfile_em.open ("norm/Reducible_em.txt");
    ofstream myfile_tt;
    myfile_tt.open ("norm/Reducible_tt.txt");
    ofstream myfile_et;
    myfile_et.open ("norm/Reducible_et.txt");
    ofstream myfile_mt;
    myfile_mt.open ("norm/Reducible_mt.txt");
    ofstream myfile_ee;
    myfile_ee.open ("norm/Reducible_ee.txt");

    Int_t nentries_wtn = (Int_t) run_Tree->GetEntries();
    int y = 0;
    for (Int_t i = 0; i < nentries_wtn; i++) {
        run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
	float f1=0; float f2=0;
	float varfr3_=pt_3_;
	float varfr4_=pt_4_;
	if (isclosejet && closeJetPt_3_>pt_3_){
	   varfr3_=closeJetPt_3_;
	}
        if (isclosejet && closeJetPt_4_>pt_4_){
           varfr4_=closeJetPt_4_;
	}

	if (channel_==7 or channel_==1){//H->EE
	   f2=fitFunc_ele(pt_3_,frvalues->GetBinContent(4,1),frvalues->GetBinContent(4,3),frvalues->GetBinContent(4,5),frvalues->GetBinContent(4,7));
           f1=fitFunc_ele(pt_4_,frvalues->GetBinContent(4,1),frvalues->GetBinContent(4,3),frvalues->GetBinContent(4,5),frvalues->GetBinContent(4,7));
	   if (subchannel_==0){
	      if (isSR_ && channel_==1) h_mmee->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isSR_ && channel_==7) h_eeee->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==1) h_mmee_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==7) h_eeee_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
	   }
           if (subchannel_==1){
              if (isSR_ && channel_==1) h_mmee->Fill(var_,w_*f1/(1-f1));
              if (isSR_ && channel_==7) h_eeee->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==1) h_mmee_high->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==7) h_eeee_high->Fill(var_,w_*f1/(1-f1));
	   }
           if (subchannel_==2){
              if (isSR_ && channel_==1) h_mmee->Fill(var_,w_*f2/(1-f2));
              if (isSR_ && channel_==7) h_eeee->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==1) h_mmee_high->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==7) h_eeee_high->Fill(var_,w_*f2/(1-f2));
	   }
	}

        if (channel_==8 or channel_==2){// H->EM
           f2=fitFunc_mu(pt_3_,frvalues->GetBinContent(6,1),frvalues->GetBinContent(6,3),frvalues->GetBinContent(6,5),frvalues->GetBinContent(6,7));
           f1=fitFunc_ele(pt_4_,frvalues->GetBinContent(4,1),frvalues->GetBinContent(4,3),frvalues->GetBinContent(4,5),frvalues->GetBinContent(4,7));
           if (subchannel_==0){
              if (isSR_ && channel_==2) h_mmem->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isSR_ && channel_==8) h_eeem->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==2) h_mmem_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==8) h_eeem_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isSR_ && channel_==2) cat0_mmem+=w_*(f1*f2)/((1-f1)*(1-f2));
              if (isSR_ && channel_==7) cat0_eeem+=w_*(f1*f2)/((1-f1)*(1-f2));
              //if (isSR_ && channel_==2 && (f1*f2)/((1-f1)*(1-f2))>1) cout<<(f1*f2)/((1-f1)*(1-f2))<<" "<<f1<<" "<<f2<<" "<<pt_4_<<" "<<pt_3_<<endl;
	   }
           if (subchannel_==1){
              if (isSR_ && channel_==2) h_mmem->Fill(var_,w_*f1/(1-f1));
              if (isSR_ && channel_==8) h_eeem->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==2) h_mmem_high->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==8) h_eeem_high->Fill(var_,w_*f1/(1-f1));
              if (isSR_ && channel_==2) cat1_mmem+=w_*(f1)/((1-f1));
              if (isSR_ && channel_==8) cat1_eeem+=w_*(f1)/((1-f1));
	   }
           if (subchannel_==2){
              if (isSR_ && channel_==2) h_mmem->Fill(var_,w_*f2/(1-f2));
              if (isSR_ && channel_==8) h_eeem->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==2) h_mmem_high->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==8) h_eeem_high->Fill(var_,w_*f2/(1-f2));
              if (isSR_ && channel_==2) cat2_mmem+=w_*(f2)/((1-f2));
              if (isSR_ && channel_==8) cat2_eeem+=w_*(f2)/((1-f2));
	   }
        }

        if (channel_==9 or channel_==3){ // H->ET
           f2=fitFunc_ele(pt_3_,frvalues->GetBinContent(4,1),frvalues->GetBinContent(4,3),frvalues->GetBinContent(4,5),frvalues->GetBinContent(4,7));
           f1=fitFunc_loosetau(varfr4_,frvalues->GetBinContent(18,1),frvalues->GetBinContent(18,3),frvalues->GetBinContent(18,5),frvalues->GetBinContent(18,7));
	   if (decayMode_4_==1) f1=fitFunc_loosetau(varfr4_,frvalues->GetBinContent(21,1),frvalues->GetBinContent(21,3),frvalues->GetBinContent(21,5),frvalues->GetBinContent(21,7));
           if (decayMode_4_==10) f1=fitFunc_loosetau(varfr4_,frvalues->GetBinContent(24,1),frvalues->GetBinContent(24,3),frvalues->GetBinContent(24,5),frvalues->GetBinContent(24,7));
           if (subchannel_==0){
              if (isSR_ && channel_==3) h_mmet->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isSR_ && channel_==9) h_eeet->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==3) h_mmet_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==9) h_eeet_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isSR_ && channel_==3) cat0_mmet+=w_*(f1*f2)/((1-f1)*(1-f2));
              if (isSR_ && channel_==9) cat0_eeet+=w_*(f1*f2)/((1-f1)*(1-f2));
	   }
           if (subchannel_==1){
              if (isSR_ && channel_==3) h_mmet->Fill(var_,w_*f1/(1-f1));
              if (isSR_ && channel_==9) h_eeet->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==3) h_mmet_high->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==9) h_eeet_high->Fill(var_,w_*f1/(1-f1));
              if (isSR_ && channel_==3) cat1_mmet+=w_*(f1)/((1-f1));
              if (isSR_ && channel_==9) cat1_eeet+=w_*(f1)/((1-f1));
	   }
           if (subchannel_==2){
              if (isSR_ && channel_==3) h_mmet->Fill(var_,w_*f2/(1-f2));
              if (isSR_ && channel_==9) h_eeet->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==3) h_mmet_high->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==9) h_eeet_high->Fill(var_,w_*f2/(1-f2));
              if (isSR_ && channel_==3) cat2_mmet+=w_*(f2)/((1-f2));
              if (isSR_ && channel_==9) cat2_eeet+=w_*(f2)/((1-f2));
	   }
        }

        if (channel_==10 or channel_==4){ // H->MM
           f2=fitFunc_mu(pt_3_,frvalues->GetBinContent(6,1),frvalues->GetBinContent(6,3),frvalues->GetBinContent(6,5),frvalues->GetBinContent(6,7));
           f1=fitFunc_mu(pt_4_,frvalues->GetBinContent(6,1),frvalues->GetBinContent(6,3),frvalues->GetBinContent(6,5),frvalues->GetBinContent(6,7));
           if (subchannel_==0){
              if (isSR_ && channel_==4) h_mmmm->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isSR_ && channel_==10) h_eemm->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==4) h_mmmm_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==10) h_eemm_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
	   }
           if (subchannel_==1){
              if (isSR_ && channel_==4) h_mmmm->Fill(var_,w_*f1/(1-f1));
              if (isSR_ && channel_==10) h_eemm->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==4) h_mmmm_high->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==10) h_eemm_high->Fill(var_,w_*f1/(1-f1));
	   }
           if (subchannel_==2){
              if (isSR_ && channel_==4) h_mmmm->Fill(var_,w_*f2/(1-f2));
              if (isSR_ && channel_==10) h_eemm->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==4) h_mmmm_high->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==10) h_eemm_high->Fill(var_,w_*f2/(1-f2));
	   }
        }

        if (channel_==11 or channel_==5){ // H->MT
           f2=fitFunc_mu(pt_3_,frvalues->GetBinContent(6,1),frvalues->GetBinContent(6,3),frvalues->GetBinContent(6,5),frvalues->GetBinContent(6,7));
           f1=fitFunc_loosetau(varfr4_,frvalues->GetBinContent(18,1),frvalues->GetBinContent(18,3),frvalues->GetBinContent(18,5),frvalues->GetBinContent(18,7));
           if (decayMode_4_==1) f1=fitFunc_loosetau(varfr4_,frvalues->GetBinContent(21,1),frvalues->GetBinContent(21,3),frvalues->GetBinContent(21,5),frvalues->GetBinContent(21,7));
           if (decayMode_4_==10) f1=fitFunc_loosetau(varfr4_,frvalues->GetBinContent(24,1),frvalues->GetBinContent(24,3),frvalues->GetBinContent(24,5),frvalues->GetBinContent(24,7));
           if (subchannel_==0){
              if (isSR_ && channel_==5) h_mmmt->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isSR_ && channel_==11) h_eemt->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==5) h_mmmt_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==11) h_eemt_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isSR_ && channel_==5) cat0_mmmt+=w_*(f1*f2)/((1-f1)*(1-f2));
              if (isSR_ && channel_==11) cat0_eemt+=w_*(f1*f2)/((1-f1)*(1-f2));
	   }
           if (subchannel_==1){
              if (isSR_ && channel_==5) h_mmmt->Fill(var_,w_*f1/(1-f1));
              if (isSR_ && channel_==11) h_eemt->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==5) h_mmmt_high->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==11) h_eemt_high->Fill(var_,w_*f1/(1-f1));
              if (isSR_ && channel_==5) cat1_mmmt+=w_*(f1)/((1-f1));
              if (isSR_ && channel_==11) cat1_eemt+=w_*(f1)/((1-f1));
	   }
           if (subchannel_==2){
              if (isSR_ && channel_==5) h_mmmt->Fill(var_,w_*f2/(1-f2));
              if (isSR_ && channel_==11) h_eemt->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==5) h_mmmt_high->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==11) h_eemt_high->Fill(var_,w_*f2/(1-f2));
              if (isSR_ && channel_==5) cat2_mmmt+=w_*(f2)/((1-f2));
              if (isSR_ && channel_==11) cat2_eemt+=w_*(f2)/((1-f2));
	   }
        }
        if (channel_==12 or channel_==6){ // H->TT
           f2=fitFunc_mediumtau(varfr3_,frvalues->GetBinContent(1,1),frvalues->GetBinContent(1,3),frvalues->GetBinContent(1,5),frvalues->GetBinContent(1,7));
           if (decayMode_3_==1) f2=fitFunc_mediumtau(varfr3_,frvalues->GetBinContent(1,1),frvalues->GetBinContent(1,3),frvalues->GetBinContent(1,5),frvalues->GetBinContent(1,7));
           if (decayMode_3_==10) f2=fitFunc_mediumtau(varfr3_,frvalues->GetBinContent(1,1),frvalues->GetBinContent(1,3),frvalues->GetBinContent(1,5),frvalues->GetBinContent(1,7));
           f1=fitFunc_mediumtau(varfr4_,frvalues->GetBinContent(1,1),frvalues->GetBinContent(1,3),frvalues->GetBinContent(1,5),frvalues->GetBinContent(1,7));
           if (decayMode_4_==1) f1=fitFunc_mediumtau(varfr4_,frvalues->GetBinContent(1,1),frvalues->GetBinContent(1,3),frvalues->GetBinContent(1,5),frvalues->GetBinContent(1,7));
           if (decayMode_4_==10) f1=fitFunc_mediumtau(varfr4_,frvalues->GetBinContent(1,1),frvalues->GetBinContent(1,3),frvalues->GetBinContent(1,5),frvalues->GetBinContent(1,7));
           if (subchannel_==0){
              if (isSR_ && channel_==6) h_mmtt->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isSR_ && channel_==12) h_eett->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==6) h_mmtt_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isHigh_ && channel_==12) h_eett_high->Fill(var_,-w_*(f1*f2)/((1-f1)*(1-f2)));
              if (isSR_ && channel_==6) cat0_mmtt+=w_*(f1*f2)/((1-f1)*(1-f2));
              if (isSR_ && channel_==12) cat0_eett+=w_*(f1*f2)/((1-f1)*(1-f2));
	   }
           if (subchannel_==1){
              if (isSR_ && channel_==6) h_mmtt->Fill(var_,w_*f1/(1-f1));
              if (isSR_ && channel_==12) h_eett->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==6) h_mmtt_high->Fill(var_,w_*f1/(1-f1));
              if (isHigh_ && channel_==12) h_eett_high->Fill(var_,w_*f1/(1-f1));
              if (isSR_ && channel_==6) cat1_mmtt+=w_*(f1)/((1-f1));
              if (isSR_ && channel_==12) cat1_eett+=w_*(f1)/((1-f1));
	   }
           if (subchannel_==2){
              if (isSR_ && channel_==6) h_mmtt->Fill(var_,w_*f2/(1-f2));
              if (isSR_ && channel_==12) h_eett->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==6) h_mmtt_high->Fill(var_,w_*f2/(1-f2));
              if (isHigh_ && channel_==12) h_eett_high->Fill(var_,w_*f2/(1-f2));
              if (isSR_ && channel_==6) cat2_mmtt+=w_*(f2)/((1-f2));
              if (isSR_ && channel_==12) cat2_eett+=w_*(f2)/((1-f2));
	   }
        }
    }

    myfile_ee<<h_mmee->Integral()<<endl;
    myfile_mm<<h_mmmm->Integral()<<endl;
    myfile_mt<<h_mmmt->Integral()<<endl;
    myfile_et<<h_mmet->Integral()<<endl;
    myfile_em<<h_mmem->Integral()<<endl;
    myfile_tt<<h_mmtt->Integral()<<endl;
    myfile_ee.close();
    myfile_tt.close();
    myfile_mt.close();
    myfile_et.close();
    myfile_em.close();
    myfile_mm.close();

cout<<"written"<<endl;
    fout->cd();
    TDirectory *dir_mmee =fout->mkdir("mmee");
    dir_mmee->cd();
    h_mmee->SetName("Reducible");
    h_mmee->Write();
    h_mmee_high->SetName("Reducible_high_");
    h_mmee_high->Write();
    TDirectory *dir_mmem =fout->mkdir("mmem");
    dir_mmem->cd();
    h_mmem->SetName("Reducible");
    h_mmem->Write();
    h_mmem_high->SetName("Reducible_high_");
    h_mmem_high->Write();
    TDirectory *dir_mmet =fout->mkdir("mmet");
    dir_mmet->cd();
    h_mmet->SetName("Reducible");
    h_mmet->Write();
    h_mmet_high->SetName("Reducible_high_");
    h_mmet_high->Write();
    TDirectory *dir_mmmm =fout->mkdir("mmmm");
    dir_mmmm->cd();
    h_mmmm->SetName("Reducible");
    h_mmmm->Write();
    h_mmmm_high->SetName("Reducible_high_");
    h_mmmm_high->Write();
    TDirectory *dir_mmmt =fout->mkdir("mmmt");
    dir_mmmt->cd();
    h_mmmt->SetName("Reducible");
    h_mmmt->Write();
    h_mmmt_high->SetName("Reducible_high_");
    h_mmmt_high->Write();
    TDirectory *dir_mmtt =fout->mkdir("mmtt");
    dir_mmtt->cd();
    h_mmtt->SetName("Reducible");
    h_mmtt->Write();
    h_mmtt_high->SetName("Reducible_high_");
    h_mmtt_high->Write();
    TDirectory *dir_eeee =fout->mkdir("eeee");
    dir_eeee->cd();
    h_eeee->SetName("Reducible");
    h_eeee->Write();
    h_eeee_high->SetName("Reducible_high_");
    h_eeee_high->Write();
    TDirectory *dir_eeem =fout->mkdir("eeem");
    dir_eeem->cd();
    h_eeem->SetName("Reducible");
    h_eeem->Write();
    h_eeem_high->SetName("Reducible_high_");
    h_eeem_high->Write();
    TDirectory *dir_eeet =fout->mkdir("eeet");
    dir_eeet->cd();
    h_eeet->SetName("Reducible");
    h_eeet->Write();
    h_eeet_high->SetName("Reducible_high_");
    h_eeet_high->Write();
    TDirectory *dir_eemm =fout->mkdir("eemm");
    dir_eemm->cd();
    h_eemm->SetName("Reducible");
    h_eemm->Write();
    h_eemm_high->SetName("Reducible_high_");
    h_eemm_high->Write();
    TDirectory *dir_eemt =fout->mkdir("eemt");
    dir_eemt->cd();
    h_eemt->SetName("Reducible");
    h_eemt->Write();
    h_eemt_high->SetName("Reducible_high_");
    h_eemt_high->Write();
    TDirectory *dir_eett =fout->mkdir("eett");
    dir_eett->cd();
cout<<h_eett->Integral()<<endl;
    h_eett->SetName("Reducible");
    h_eett->Write();
    h_eett_high->SetName("Reducible_high_");
    h_eett_high->Write();
    fout->Close();
cout<<"fin"<<endl;
cout<<"mmmt: "<<cat0_mmmt<<" "<<cat1_mmmt<<" "<<cat2_mmmt<<endl;
cout<<"eemt: "<<cat0_eemt<<" "<<cat1_eemt<<" "<<cat2_eemt<<endl;
cout<<"mmem: "<<cat0_mmem<<" "<<cat1_mmem<<" "<<cat2_mmem<<endl;
cout<<"eeem: "<<cat0_eeem<<" "<<cat1_eeem<<" "<<cat2_eeem<<endl;
cout<<"mmet: "<<cat0_mmet<<" "<<cat1_mmet<<" "<<cat2_mmet<<endl;
cout<<"eeet: "<<cat0_eeet<<" "<<cat1_eeet<<" "<<cat2_eeet<<endl;
cout<<"mmtt: "<<cat0_mmtt<<" "<<cat1_mmtt<<" "<<cat2_mmtt<<endl;
cout<<"eett: "<<cat0_eett<<" "<<cat1_eett<<" "<<cat2_eett<<endl;
}

