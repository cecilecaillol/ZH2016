#include "tr_Tree.h"
#include <iostream>
#include <fstream>
#include "LumiReweightingStandAlone.h"
#include "ScaleFactor.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"

int main(int argc, char** argv) {

    float tes=0;
    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);
    std::string name = *(argv + 4);

    float tes=0;
    if (argc > 1) {
        tes = atof(argv[5]);
    }

    TFile *fout = TFile::Open(output.c_str(), "RECREATE");

    using namespace std;

    myMap1 = new std::map<std::string, TH1F*>();
    myMap2 = new map<string, TH2F*>();
    TFile *f_Double = new TFile(input.c_str());
    TTree *run_Tree = (TTree*) f_Double->Get("RLE_tree");
    TH1F* nbevt = (TH1F*) f_Double->Get("nevents");
    float ngen = nbevt->GetBinContent(1);
    ngen=ngen/8;

    TFile *fVVL = new TFile("file_vvloose.root","r");
    TGraph *DBoldDMwLTEff95 = (TGraph*) fVVL->Get("DBoldDMwLTEff95");
    TFormula* mvaOutput_normalization_DBoldDMwLT = (TFormula*) fVVL->Get("mvaOutput_normalization_DBoldDMwLT");

    reweight::LumiReWeighting* LumiWeights_12;
    LumiWeights_12 = new reweight::LumiReWeighting("MC_Moriond17_PU25ns_V1.root", "Data_Pileup_2016_271036-284044_80bins.root", "pileup", "pileup");

    TFile fw("htt_scalefactors_v16_3.root");
    RooWorkspace *w = (RooWorkspace*)fw.Get("w");
    fw.Close();

    float xs=1.0; float weight=1.0; float luminosity=35870.0;
    if (sample=="DY"){ xs=5765.2; weight=luminosity*xs/ngen;}
    else if (sample=="data_obs"){weight=1.0;}
    else if (sample=="ZZ4L") {xs=1.256; weight=luminosity*xs/ngen;}
    else if (sample=="GGZZ2e2mu") {xs=2*0.00319; weight=luminosity*xs/ngen;}
    else if (sample=="GGZZ2mu2tau") {xs=2*0.00319; weight=luminosity*xs/ngen;}
    else if (sample=="GGZZ2e2tau") {xs=2*0.00319; weight=luminosity*xs/ngen;}
    else if (sample=="GGZZ4mu") {xs=2*0.00159; weight=luminosity*xs/ngen;}
    else if (sample=="GGZZ4tau") {xs=2*0.00159; weight=luminosity*xs/ngen;}
    else if (sample=="GGZZ4e") {xs=2*0.00159; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3L") {xs=4.43; weight=luminosity*xs/ngen;}
    else if (sample=="WWZ") {xs=0.165; weight=luminosity*xs/ngen;}
    else if (sample=="WZZ") {xs=0.0557; weight=luminosity*xs/ngen;}
    else if (sample=="ZZZ") {xs=0.0140; weight=luminosity*xs/ngen;}
    else if (sample=="ttZ") {xs=0.606; weight=luminosity*xs/ngen;}
    else if (sample=="ZH120") {xs=0.9939*0.0698; weight=luminosity*xs/ngen;}
    else if (sample=="ZH125") {xs=0.8839*0.0627; weight=luminosity*xs/ngen;}
    else if (sample=="ZH130") {xs=0.7899*0.0541; weight=luminosity*xs/ngen;}
    else if (sample=="ZHWW125") {xs=0.8839*0.2137*0.3258*0.3258; weight=luminosity*xs/ngen;}
    else if (sample=="ZH110") {xs=1.309*0.0791; weight=luminosity*xs/ngen;}
    else if (sample=="ZH140") {xs=0.6514*0.0360; weight=luminosity*xs/ngen;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(5);

    run_Tree->SetBranchAddress("channel", &channel);
    run_Tree->SetBranchAddress("run", &run);
    run_Tree->SetBranchAddress("lumi", &lumi);
    run_Tree->SetBranchAddress("evt", &evt);
    run_Tree->SetBranchAddress("met", &met);
    run_Tree->SetBranchAddress("metphi", &metphi);
    run_Tree->SetBranchAddress("mvaMet", &mvaMet);
    run_Tree->SetBranchAddress("mvaMetPhi", &mvaMetPhi);
    run_Tree->SetBranchAddress("mvametcov00", &mvametcov00);
    run_Tree->SetBranchAddress("mvametcov01", &mvametcov01);
    run_Tree->SetBranchAddress("mvametcov10", &mvametcov10);
    run_Tree->SetBranchAddress("mvametcov11", &mvametcov11);
    run_Tree->SetBranchAddress("njets", &njets);
    run_Tree->SetBranchAddress("nbtag", &nbtag);
    run_Tree->SetBranchAddress("npv", &npv);
    run_Tree->SetBranchAddress("NUP", &NUP);
    run_Tree->SetBranchAddress("npu", &npu);
    run_Tree->SetBranchAddress("gen_weight", &gen_weight);
    run_Tree->SetBranchAddress("m_pair1", &m_pair1);
    run_Tree->SetBranchAddress("m_pair2", &m_pair2);
    run_Tree->SetBranchAddress("m_four", &m_four);
    run_Tree->SetBranchAddress("closeJetPt_3", &closeJetPt_3);
    run_Tree->SetBranchAddress("closeJetPt_4", &closeJetPt_4);
    run_Tree->SetBranchAddress("passDoubleMu", &passDoubleMu);
    run_Tree->SetBranchAddress("passDoubleEle", &passDoubleEle);
    run_Tree->SetBranchAddress("matchDoubleMu_1", &matchDoubleMu_1);
    run_Tree->SetBranchAddress("matchDoubleMu_2", &matchDoubleMu_2);
    run_Tree->SetBranchAddress("matchDoubleMu_3", &matchDoubleMu_3);
    run_Tree->SetBranchAddress("matchDoubleMu_4", &matchDoubleMu_4);
    run_Tree->SetBranchAddress("tauMVAisoVL_3", &tauMVAisoVL_3);
    run_Tree->SetBranchAddress("tauMVAisoVL_4", &tauMVAisoVL_4);
    run_Tree->SetBranchAddress("tauMVAisoL_3", &tauMVAisoL_3);
    run_Tree->SetBranchAddress("tauMVAisoL_4", &tauMVAisoL_4);
    run_Tree->SetBranchAddress("tauMVAisoM_3", &tauMVAisoM_3);
    run_Tree->SetBranchAddress("tauMVAisoM_4", &tauMVAisoM_4);
    run_Tree->SetBranchAddress("tauMVAisoT_3", &tauMVAisoT_3);
    run_Tree->SetBranchAddress("tauMVAisoT_4", &tauMVAisoT_4);
    run_Tree->SetBranchAddress("tauMVAisoVT_3", &tauMVAisoVT_3);
    run_Tree->SetBranchAddress("tauMVAisoVT_4", &tauMVAisoVT_4);
    run_Tree->SetBranchAddress("tauMVAisoRaw_3", &tauMVAisoRaw_3);
    run_Tree->SetBranchAddress("tauMVAisoRaw_4", &tauMVAisoRaw_4);
    run_Tree->SetBranchAddress("pt_1", &pt_1);
    run_Tree->SetBranchAddress("pt_2", &pt_2);
    run_Tree->SetBranchAddress("pt_3", &pt_3);
    run_Tree->SetBranchAddress("pt_4", &pt_4);
    run_Tree->SetBranchAddress("q_1", &q_1);
    run_Tree->SetBranchAddress("q_2", &q_2);
    run_Tree->SetBranchAddress("q_3", &q_3);
    run_Tree->SetBranchAddress("q_4", &q_4);
    run_Tree->SetBranchAddress("e_1", &e_1);
    run_Tree->SetBranchAddress("e_2", &e_2);
    run_Tree->SetBranchAddress("e_3", &e_3);
    run_Tree->SetBranchAddress("e_4", &e_4);
    run_Tree->SetBranchAddress("m_1", &m_1);
    run_Tree->SetBranchAddress("m_2", &m_2);
    run_Tree->SetBranchAddress("m_3", &m_3);
    run_Tree->SetBranchAddress("m_4", &m_4);
    run_Tree->SetBranchAddress("eta_1", &eta_1);
    run_Tree->SetBranchAddress("eta_2", &eta_2);
    run_Tree->SetBranchAddress("eta_3", &eta_3);
    run_Tree->SetBranchAddress("eta_4", &eta_4);
    run_Tree->SetBranchAddress("phi_1", &phi_1);
    run_Tree->SetBranchAddress("phi_2", &phi_2);
    run_Tree->SetBranchAddress("phi_3", &phi_3);
    run_Tree->SetBranchAddress("phi_4", &phi_4);
    run_Tree->SetBranchAddress("muiso_1", &muiso_1);
    run_Tree->SetBranchAddress("muiso_2", &muiso_2);
    run_Tree->SetBranchAddress("muiso_3", &muiso_3);
    run_Tree->SetBranchAddress("muiso_4", &muiso_4);
    run_Tree->SetBranchAddress("eiso_3", &eiso_3);
    run_Tree->SetBranchAddress("eiso_4", &eiso_4);
    run_Tree->SetBranchAddress("antimuL_3", &antimuL_3);
    run_Tree->SetBranchAddress("antimuL_4", &antimuL_4);
    run_Tree->SetBranchAddress("antimuT_3", &antimuT_3);
    run_Tree->SetBranchAddress("antimuT_4", &antimuT_4);
    run_Tree->SetBranchAddress("antieleVL_3", &antieleVL_3);
    run_Tree->SetBranchAddress("antieleVL_4", &antieleVL_4);
    run_Tree->SetBranchAddress("antieleL_3", &antieleL_3);
    run_Tree->SetBranchAddress("antieleL_4", &antieleL_4);
    run_Tree->SetBranchAddress("antieleM_3", &antieleM_3);
    run_Tree->SetBranchAddress("antieleM_4", &antieleM_4);
    run_Tree->SetBranchAddress("antieleT_3", &antieleT_3);
    run_Tree->SetBranchAddress("antieleT_4", &antieleT_4);
    run_Tree->SetBranchAddress("antieleVT_3", &antieleVT_3);
    run_Tree->SetBranchAddress("antieleVT_4", &antieleVT_4);
    run_Tree->SetBranchAddress("px_1", &px_1);
    run_Tree->SetBranchAddress("py_1", &py_1);
    run_Tree->SetBranchAddress("pz_1", &pz_1);
    run_Tree->SetBranchAddress("px_2", &px_2);
    run_Tree->SetBranchAddress("py_2", &py_2);
    run_Tree->SetBranchAddress("pz_2", &pz_2);
    run_Tree->SetBranchAddress("px_3", &px_3);
    run_Tree->SetBranchAddress("py_3", &py_3);
    run_Tree->SetBranchAddress("pz_3", &pz_3);
    run_Tree->SetBranchAddress("px_4", &px_4);
    run_Tree->SetBranchAddress("py_4", &py_4);
    run_Tree->SetBranchAddress("pz_4", &pz_4);
    run_Tree->SetBranchAddress("muidL_1", &muidL_1);
    run_Tree->SetBranchAddress("muidL_2", &muidL_2);
    run_Tree->SetBranchAddress("muidL_3", &muidL_3);
    run_Tree->SetBranchAddress("muidL_4", &muidL_4);
    run_Tree->SetBranchAddress("muidM_1", &muidM_1);
    run_Tree->SetBranchAddress("muidM_2", &muidM_2);
    run_Tree->SetBranchAddress("muidM_3", &muidM_3);
    run_Tree->SetBranchAddress("muidM_4", &muidM_4);
    run_Tree->SetBranchAddress("muidT_1", &muidT_1);
    run_Tree->SetBranchAddress("muidT_2", &muidT_2);
    run_Tree->SetBranchAddress("muidT_3", &muidT_3);
    run_Tree->SetBranchAddress("muidT_4", &muidT_4);
    run_Tree->SetBranchAddress("genmatch_1", &genmatch_1);
    run_Tree->SetBranchAddress("genmatch_2", &genmatch_2);
    run_Tree->SetBranchAddress("genmatch_3", &genmatch_3);
    run_Tree->SetBranchAddress("genmatch_4", &genmatch_4);
    run_Tree->SetBranchAddress("eid80_3", &eid80_3);
    run_Tree->SetBranchAddress("eid80_4", &eid80_4);
    run_Tree->SetBranchAddress("eid90_3", &eid90_3);
    run_Tree->SetBranchAddress("eid90_4", &eid90_4);
    run_Tree->SetBranchAddress("decayMode_3", &decayMode_3);
    run_Tree->SetBranchAddress("decayMode_4", &decayMode_4);
    run_Tree->SetBranchAddress("vetomu", &vetomu);
    run_Tree->SetBranchAddress("vetoele", &vetoele);

    run_Tree->SetBranchAddress("m_sv", &m_sv);

    //New BG_Tree
    TTree * BG_Tree = new TTree("BG_Tree", "BG_Tree");
    BG_Tree->SetDirectory(0);

    BG_Tree->Branch("channel_", &channel_, "channel_/I");
    BG_Tree->Branch("subchannel_", &subchannel_, "subchannel_/I");
    BG_Tree->Branch("var_", &var_, "var_/F");
    BG_Tree->Branch("pt_3_", &pt_3_, "pt_3_/F");
    BG_Tree->Branch("decayMode_3_", &decayMode_3_, "decayMode_3_/F");
    BG_Tree->Branch("decayMode_4_", &decayMode_4_, "decayMode_4_/F");
    BG_Tree->Branch("eta_3_", &eta_3_, "eta_3_/F");
    BG_Tree->Branch("closeJetPt_3_", &closeJetPt_3_, "closeJetPt_3_/F");
    BG_Tree->Branch("pt_4_", &pt_4_, "pt_4_/F");
    BG_Tree->Branch("eta_4_", &eta_4_, "eta_4_/F");
    BG_Tree->Branch("closeJetPt_4_", &closeJetPt_4_, "closeJetPt_4_/F");
    BG_Tree->Branch("w_", &w_, "w_/F");
    BG_Tree->Branch("isHigh_", &isHigh_, "isHigh_/O");
    BG_Tree->Branch("isSR_", &isSR_, "isSR_/O");

   //float bins0[] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400};
   //float bins1[] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400};
   //float bins0[] = {0,20,40,60,80,100,120,140};
   float bins0[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140};
   float bins1[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140};
   //float bins0[] = {0,20,40,60,80,100,120,140,160,180,200};
   //float bins1[] = {0,20,40,60,80,100,120,140,160,180,200};

   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;
   int  binnum1 = sizeof(bins1)/sizeof(Float_t) - 1;
   TH1F *h_mmee=new TH1F ("h_mmee","h_mmee",binnum0,bins0);h_mmee->Sumw2();
   TH1F *h_mmee_shape=new TH1F ("h_mmee_shape","h_mmee_shape",binnum0,bins0);h_mmee_shape->Sumw2();
   TH1F *h_mmem=new TH1F ("h_mmem","h_mmem",binnum1,bins1);h_mmem->Sumw2();
   TH1F *h_mmem_shape=new TH1F ("h_mmem_shape","h_mmem_shape",binnum1,bins1);h_mmem_shape->Sumw2();
   TH1F *h_mmmm=new TH1F ("h_mmmm","h_mmmm",binnum0,bins0);h_mmmm->Sumw2();
   TH1F *h_mmmm_shape=new TH1F ("h_mmmm_shape","h_mmmm_shape",binnum0,bins0);h_mmmm_shape->Sumw2();
   TH1F *h_mmet=new TH1F ("h_mmet","h_mmet",binnum1,bins1);h_mmet->Sumw2();
   TH1F *h_mmet_shape=new TH1F ("h_mmet_shape","h_mmet_shape",binnum1,bins1);h_mmet_shape->Sumw2();
   TH1F *h_mmmt=new TH1F ("h_mmmt","h_mmmt",binnum1,bins1);h_mmmt->Sumw2();
   TH1F *h_mmmt_shape=new TH1F ("h_mmmt_shape","h_mmmt_shape",binnum1,bins1);h_mmmt_shape->Sumw2();
   TH1F *h_mmtt=new TH1F ("h_mmtt","h_mmtt",binnum1,bins1);h_mmtt->Sumw2();
   TH1F *h_mmtt_shape=new TH1F ("h_mmtt_shape","h_mmtt_shape",binnum1,bins1);h_mmtt_shape->Sumw2();
   TH1F *h_eeee=new TH1F ("h_eeee","h_eeee",binnum0,bins0);h_eeee->Sumw2();
   TH1F *h_eeee_shape=new TH1F ("h_eeee_shape","h_eeee_shape",binnum0,bins0);h_eeee_shape->Sumw2();
   TH1F *h_eeem=new TH1F ("h_eeem","h_eeem",binnum1,bins1);h_eeem->Sumw2();
   TH1F *h_eeem_shape=new TH1F ("h_eeem_shape","h_eeem_shape",binnum1,bins1);h_eeem_shape->Sumw2();
   TH1F *h_eemm=new TH1F ("h_eemm","h_eemm",binnum0,bins0);h_eemm->Sumw2();
   TH1F *h_eemm_shape=new TH1F ("h_eemm_shape","h_eemm_shape",binnum0,bins0);h_eemm_shape->Sumw2();
   TH1F *h_eeet=new TH1F ("h_eeet","h_eeet",binnum1,bins1);h_eeet->Sumw2();
   TH1F *h_eeet_shape=new TH1F ("h_eeet_shape","h_eeet_shape",binnum1,bins1);h_eeet_shape->Sumw2();
   TH1F *h_eemt=new TH1F ("h_eemt","h_eemt",binnum1,bins1);h_eemt->Sumw2();
   TH1F *h_eemt_shape=new TH1F ("h_eemt_shape","h_eemt_shape",binnum1,bins1);h_eemt_shape->Sumw2();
   TH1F *h_eett=new TH1F ("h_eett","h_eett",binnum1,bins1);h_eett->Sumw2();
   TH1F *h_eett_shape=new TH1F ("h_eett_shape","h_eett_shape",binnum1,bins1);h_eett_shape->Sumw2();

   cout<<sample<<" "<<weight<<endl;
   ScaleFactor * myScaleFactor_idMu = new ScaleFactor();
   myScaleFactor_idMu->init_ScaleFactor("LeptonEfficiencies/Muon/Run2016BCD/Muon_IdIso0p20_eff.root");
   ScaleFactor * myScaleFactor_idEle = new ScaleFactor();
   myScaleFactor_idEle->init_ScaleFactor("LeptonEfficiencies/Electron/Run2016BtoH/Electron_IdIso_IsoLt0p15_eff.root");

    TFile *f_ID_BCDEF=new TFile("EfficienciesAndSF_BCDEF.root");
    TDirectory *dM_ID_BCDEF= (TDirectory*) f_ID_BCDEF->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_eta");
    TH2F *hM_ID_BCDEF= (TH2F*) dM_ID_BCDEF->Get("pt_abseta_ratio");
    TDirectory *dL_ID_BCDEF= (TDirectory*) f_ID_BCDEF->Get("MC_NUM_LooseID_DEN_genTracks_PAR_pt_eta");
    TH2F *hL_ID_BCDEF= (TH2F*) dL_ID_BCDEF->Get("pt_abseta_ratio");

    TFile *f_ID_GH=new TFile("EfficienciesAndSF_GH.root");
    TDirectory *dM_ID_GH= (TDirectory*) f_ID_GH->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_eta");
    TH2F *hM_ID_GH= (TH2F*) dM_ID_GH->Get("pt_abseta_ratio");
    TDirectory *dL_ID_GH= (TDirectory*) f_ID_GH->Get("MC_NUM_LooseID_DEN_genTracks_PAR_pt_eta");
    TH2F *hL_ID_GH= (TH2F*) dL_ID_GH->Get("pt_abseta_ratio");

    TFile *f_Iso_BCDEF=new TFile("EfficienciesAndSF_BCDEF-2.root");
    TDirectory *dL_Iso_BCDEF= (TDirectory*) f_Iso_BCDEF->Get("LooseISO_LooseID_pt_eta");
    TH2F *hL_Iso_BCDEF= (TH2F*) dL_Iso_BCDEF->Get("pt_abseta_ratio");
    TDirectory *dT_Iso_BCDEF= (TDirectory*) f_Iso_BCDEF->Get("TightISO_MediumID_pt_eta");
    TH2F *hT_Iso_BCDEF= (TH2F*) dT_Iso_BCDEF->Get("pt_abseta_ratio");

    TFile *f_Iso_GH=new TFile("EfficienciesAndSF_GH-2.root");
    TDirectory *dL_Iso_GH= (TDirectory*) f_Iso_GH->Get("LooseISO_LooseID_pt_eta");
    TH2F *hL_Iso_GH= (TH2F*) dL_Iso_GH->Get("pt_abseta_ratio");
    TDirectory *dT_Iso_GH= (TDirectory*) f_Iso_GH->Get("TightISO_MediumID_pt_eta");
    TH2F *hT_Iso_GH= (TH2F*) dT_Iso_GH->Get("pt_abseta_ratio");

    TFile *f_Trk=new TFile("Tracking_EfficienciesAndSF_BCDEFGH.root");
    TGraph *h_Trk=(TGraph*) f_Trk->Get("ratio_eff_eta3_dr030e030_corr");

    TFile *f_eid90 = new TFile("egammaEffi.txt_EGM2D.root");
    TH2F *sf_eid90 = (TH2F*) f_eid90->Get("EGamma_SF2D");

   TFile *f_trig_ee = new TFile("triggerSummary_ee.root");
   TH2F *h_trig_ee = (TH2F*) f_trig_ee->Get("scalefactor_eta2d_with_syst");

   TFile *f_trig_mm = new TFile("triggerSummary_mumu.root");
   TH2F *h_trig_mm = (TH2F*) f_trig_mm->Get("scalefactor_eta2d_with_syst");

   float ele_minpt=10;
   float mu_minpt=10;
   float tau_minpt=20;

   float mutrg_pt1=10;
   float mutrg_pt2=18;
   float eletrg_pt1=24;
   float eletrg_pt2=13;

   int nb_bins =150;
   int min=0;
   int max=150;

    float TightMu = 0.15;//0.25;
    float TightEle = 0.15;//0.30;

    bool lepton_isolation = true;
    bool isCat0=true;
    bool isCat1=true;
    bool isCat2=true;
    bool isCatZ=true;

    float LT_tt=0;//80;
    float LT_et=0;//60;
    float LT_em=0;//30;
    float LT_mt=0;//50;

    float tauid=0.97;

    Int_t nentries_wtn = (Int_t) run_Tree->GetEntries();
    int y = 0;
    for (Int_t i = 0; i < nentries_wtn; i++) {
        run_Tree->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        TLorentzVector l1; l1.SetPxPyPzE(px_1,py_1,pz_1,e_1);
        TLorentzVector l2; l2.SetPxPyPzE(px_2,py_2,pz_2,e_2);
        TLorentzVector l3; l3.SetPxPyPzE(px_3,py_3,pz_3,e_3);
        TLorentzVector l4; l4.SetPxPyPzE(px_4,py_4,pz_4,e_4);
        TLorentzVector mymet; mymet.SetPtEtaPhiM(met,0,metphi,0);

	// Shape uncertainties
	if (tes==1){ // tau ES 1 prong up
	    if ((channel==3 or channel==5 or channel==6 or channel==9 or channel==11 or channel==12) and genmatch_4==5 and decayMode_4==0) { l4*=1.012; mymet=mymet-(0.012/1.012)*l4; }
            if ((channel==6 or channel==12) and genmatch_3==5 and decayMode_3==0) { l3*=1.012; mymet=mymet-(0.012/1.012)*l3; }
	}
	else if (tes==-1){ // tau ES 1 prong down
            if ((channel==3 or channel==5 or channel==6 or channel==9 or channel==11 or channel==12) and genmatch_4==5 and decayMode_4==0) { l4*=0.988; mymet=mymet+(0.012/0.988)*l4; }
            if ((channel==6 or channel==12) and genmatch_3==5 and decayMode_3==0) { l3*=0.988; mymet=mymet+(0.012/0.988)*l3; }
        }
        else if (tes==2){ // tau ES 1 prong + 1pizero up
            if ((channel==3 or channel==5 or channel==6 or channel==9 or channel==11 or channel==12) and genmatch_4==5 and decayMode_4==1) { l4*=1.012; mymet=mymet-(0.012/1.012)*l4; }
            if ((channel==6 or channel==12) and genmatch_3==5 and decayMode_3==1) { l3*=1.012; mymet=mymet-(0.012/1.012)*l3; }
        }
        else if (tes==-2){ // tau ES 1 prong + 1 pizero down
            if ((channel==3 or channel==5 or channel==6 or channel==9 or channel==11 or channel==12) and genmatch_4==5 and decayMode_4==1) { l4*=0.988; mymet=mymet+(0.012/0.988)*l4; }
            if ((channel==6 or channel==12) and genmatch_3==5 and decayMode_3==1) { l3*=0.988; mymet=mymet+(0.012/0.988)*l3; }
        }
        else if (tes==3){ // tau ES 3 prong up
            if ((channel==3 or channel==5 or channel==6 or channel==9 or channel==11 or channel==12) and genmatch_4==5 and decayMode_4==10) { l4*=1.012; mymet=mymet-(0.012/1.012)*l4; }
            if ((channel==6 or channel==12) and genmatch_3==5 and decayMode_3==10) { l3*=1.012; mymet=mymet-(0.012/1.012)*l3; }
        }
        else if (tes==-3){ // tau ES 3 prong down
            if ((channel==3 or channel==5 or channel==6 or channel==9 or channel==11 or channel==12) and genmatch_4==5 and decayMode_4==10) { l4*=0.988; mymet=mymet+(0.012/0.988)*l4; }
            if ((channel==6 or channel==12) and genmatch_3==5 and decayMode_3==10) { l3*=0.988; mymet=mymet+(0.012/0.988)*l3; }
        }


	// Trigger thresholds
	if (l1.Pt()<25 and l2.Pt()<25) continue;
        if (l1.Pt()<20 or l2.Pt()<20) continue;

	if (fabs(l1.Eta())>2.4 or fabs(l2.Eta())>2.4) continue;

	// pT thresholds for the other leptons
	if ((channel==2 or channel==8) and (l3.Pt()<10 or l4.Pt()<10)) continue; // EM
        if ((channel==3 or channel==9) and (l3.Pt()<10 or l4.Pt()<20)) continue; // ET
        if ((channel==5 or channel==11) and (l3.Pt()<10 or l4.Pt()<20)) continue; // MT
        if ((channel==6 or channel==12) and (l3.Pt()<20 or l4.Pt()<20)) continue; // TT

	// Pileup weights
	float w_eff=1.0;
	float w_pu=LumiWeights_12->weight(npu);

	// Tracking, ID, iso weights
	float muidSF_1=(16.7/36.8)*hL_ID_GH->GetBinContent(hL_ID_GH->FindBin(TMath::Min(float(l1.Pt()),float(119.0)),fabs(l1.Eta())))+(20.1/36.8)*hL_ID_BCDEF->GetBinContent(hL_ID_BCDEF->FindBin(TMath::Min(float(l1.Pt()),float(119.0)),fabs(l1.Eta())));
        float muisoSF_1=(16.7/36.8)*hL_Iso_GH->GetBinContent(hL_Iso_GH->FindBin(TMath::Min(float(l1.Pt()),float(119.0)),fabs(eta_1)))+(20.1/36.8)*hL_Iso_BCDEF->GetBinContent(hL_Iso_BCDEF->FindBin(TMath::Min(float(l1.Pt()),float(119.0)),fabs(l1.Eta())));
        w->var("m_pt")->setVal(l1.Pt());
        w->var("m_eta")->setVal(l1.Eta());
        float mutrk_1=w->function("m_trk_ratio")->getVal();
        float muidSF_2=(16.7/36.8)*hL_ID_GH->GetBinContent(hL_ID_GH->FindBin(TMath::Min(float(l2.Pt()),float(119.0)),fabs(l2.Eta())))+(20.1/36.8)*hL_ID_BCDEF->GetBinContent(hL_ID_BCDEF->FindBin(TMath::Min(float(l2.Pt()),float(119.0)),fabs(l2.Eta())));
        float muisoSF_2=(16.7/36.8)*hL_Iso_GH->GetBinContent(hL_Iso_GH->FindBin(TMath::Min(float(l2.Pt()),float(119.0)),fabs(l2.Eta())))+(20.1/36.8)*hL_Iso_BCDEF->GetBinContent(hL_Iso_BCDEF->FindBin(TMath::Min(float(l2.Pt()),float(119.0)),fabs(l2.Eta())));
        w->var("m_pt")->setVal(l2.Pt());
        w->var("m_eta")->setVal(l2.Eta());
        float mutrk_2=w->function("m_trk_ratio")->getVal();
        float muidSF_3=(16.7/36.8)*hL_ID_GH->GetBinContent(hL_ID_GH->FindBin(TMath::Min(float(l3.Pt()),float(119.0)),fabs(l3.Eta())))+(20.1/36.8)*hL_ID_BCDEF->GetBinContent(hL_ID_BCDEF->FindBin(l3.Pt(),fabs(l3.Eta())));
        float muisoSF_3=(16.7/36.8)*hT_Iso_GH->GetBinContent(hT_Iso_GH->FindBin(TMath::Min(float(l3.Pt()),float(119.0)),fabs(l3.Eta())))+(20.1/36.8)*hT_Iso_BCDEF->GetBinContent(hT_Iso_BCDEF->FindBin(l3.Pt(),fabs(l3.Eta())));
	w->var("m_pt")->setVal(l3.Pt());
	w->var("m_eta")->setVal(l3.Eta());
        float mutrk_3=w->function("m_trk_ratio")->getVal();
        float muidSF_4=(16.7/36.8)*hL_ID_GH->GetBinContent(hL_ID_GH->FindBin(TMath::Min(float(l4.Pt()),float(119.0)),fabs(l4.Eta())))+(20.1/36.8)*hL_ID_BCDEF->GetBinContent(hL_ID_BCDEF->FindBin(l4.Pt(),fabs(l4.Eta())));
        float muisoSF_4=(16.7/36.8)*hT_Iso_GH->GetBinContent(hT_Iso_GH->FindBin(TMath::Min(float(l4.Pt()),float(119.0)),fabs(l4.Eta())))+(20.1/36.8)*hT_Iso_BCDEF->GetBinContent(hT_Iso_BCDEF->FindBin(l4.Pt(),fabs(l4.Eta())));
        w->var("m_pt")->setVal(l4.Pt());
        w->var("m_eta")->setVal(l4.Eta());
        float mutrk_4=w->function("m_trk_ratio")->getVal();
        float eleidSF_1=sf_eid90->GetBinContent(sf_eid90->FindBin(l1.Eta(),l1.Pt()));;
        w->var("e_pt")->setVal(l1.Pt());
        w->var("e_eta")->setVal(l1.Eta());
        float eletrk_1=w->function("e_trk_ratio")->getVal();
        float eleidSF_2=sf_eid90->GetBinContent(sf_eid90->FindBin(l2.Eta(),l2.Pt()));;
        w->var("e_pt")->setVal(l2.Pt());
        w->var("e_eta")->setVal(l2.Eta());
        float eletrk_2=w->function("e_trk_ratio")->getVal();
        float eleidSF_3=myScaleFactor_idEle->get_ScaleFactor(l3.Pt(),l3.Eta());
        w->var("e_pt")->setVal(l3.Pt());
        w->var("e_eta")->setVal(l3.Eta());
        float eletrk_3=w->function("e_trk_ratio")->getVal();
        float eleidSF_4=myScaleFactor_idEle->get_ScaleFactor(l4.Pt(),l4.Eta());
	w->var("e_pt")->setVal(l4.Pt());
	w->var("e_eta")->setVal(l4.Eta());
        float eletrk_4=w->function("e_trk_ratio")->getVal();

	float tauID_4=1.0;
	if (genmatch_4==5) tauID_4=0.97; // Medium WP
        float tauID_3=1.0;
        if (genmatch_3==5) tauID_3=0.97; // Medium WP

	if (channel<7) { // Z->MM channels
	    w_eff=w_eff*muidSF_1*muisoSF_1*mutrk_1*muidSF_2*muisoSF_2*mutrk_2*h_trig_mm->GetBinContent(h_trig_mm->FindBin(fabs(l1.Eta()),fabs(l2.Eta())));
	}
	if (channel>6){ // Z->EE channels
	    w_eff=w_eff*eleidSF_1*eletrk_1*eleidSF_2*eletrk_2*h_trig_ee->GetBinContent(h_trig_ee->FindBin(fabs(l1.Eta()),fabs(l2.Eta())));
	}
	if (channel==2 or channel==8){ // H->EM channels
	    w_eff=w_eff*muidSF_3*muisoSF_3*mutrk_3*eleidSF_4*eletrk_4;
	}
        if (channel==3 or channel==9){ // H->ET channels
            w_eff=w_eff*eleidSF_3*eletrk_3*tauID_4;
	}
        if (channel==5 or channel==11){ // H->MT channels
            w_eff=w_eff*muidSF_3*muisoSF_3*mutrk_3*tauID_4;
        }
        if (channel==6 or channel==12){ // H->TT channels
            w_eff=w_eff*tauID_3*tauID_4;
        }

	if (sample=="data_obs") w_eff=1.0;


	// Charge and isolation definitions 
        bool charge_Type = ((q_3*q_4 < 0) ? true : false); 
        bool SS = q_3*q_4 > 0;
        bool OS = q_3*q_4 < 0;
        bool tau3_IsoB = tauMVAisoM_3;
        bool tau4_IsoB = tauMVAisoM_4;
        bool tau3_Iso_ltau = tauMVAisoM_3;
        bool tau4_Iso_ltau = tauMVAisoM_4;
	bool tau3_VVL = false;
        if ( mvaOutput_normalization_DBoldDMwLT->Eval(tauMVAisoRaw_3) > DBoldDMwLTEff95->Eval(l3.Pt())) tau3_VVL = true;
        bool tau4_VVL = false;
        if ( mvaOutput_normalization_DBoldDMwLT->Eval(tauMVAisoRaw_4) > DBoldDMwLTEff95->Eval(l4.Pt())) tau4_VVL = true;

	bool l3eleIDET= eid80_3;
        bool l4eleIDEM= eid80_4;

	// Definition of signal region and anti-isolated regions
        if (channel==6 or channel==12) isCatZ=tau4_VVL && tau3_VVL && tau3_IsoB && tau4_IsoB;
	if (channel==6 or channel==12) lepton_isolation = tau4_VVL && tau3_VVL && tau3_IsoB && tau4_IsoB;
	else if (channel==3 or channel==9) lepton_isolation = tau4_VVL && tau4_Iso_ltau && (eid80_3 && (eiso_3 < TightEle));
        else if (channel==5 or channel==11) lepton_isolation = tau4_VVL && tau4_Iso_ltau && (muidL_3 && (muiso_3 < TightMu));
        else if (channel==2 or channel==8) lepton_isolation = (eid80_4 && (eiso_4 < TightEle)) && (muidL_3 && (muiso_3 < TightMu));
        else if (channel==1 or channel==7) lepton_isolation = (eid80_3 && (eiso_3 < TightEle)) && (eid80_4 && (eiso_4 < TightEle));
	else if (channel==4 or channel==10) lepton_isolation = (muidL_3 && (muiso_3 < TightMu)) && (muidL_4 && (muiso_4 < TightMu));

	// Both leptons fail
        if (channel==6 or channel==12) isCat0 = tau4_VVL && tau3_VVL && !tau3_IsoB && !tau4_IsoB;
        else if (channel==3 or channel==9) isCat0 = tau4_VVL && !tau4_Iso_ltau && (!eid80_3 or (eiso_3 > TightEle));
        else if (channel==5 or channel==11) isCat0 = tau4_VVL && !tau4_Iso_ltau && (!muidL_3 or (muiso_3 > TightMu));
        else if (channel==2 or channel==8) isCat0 = (!muidL_3 or (muiso_3 > TightMu)) && (!eid80_4 or (eiso_4 > TightEle));
        else if (channel==1 or channel==7) isCat0 = (!eid80_3 or (eiso_3 > TightEle)) && (!eid80_4 or (eiso_4 > TightEle));
        else if (channel==4 or channel==10) isCat0 = (!muidL_3 or (muiso_3 > TightMu)) && (!muidL_4 or (muiso_4 > TightMu));

	// The second lepton fails
        if (channel==6 or channel==12) isCat1 = tau4_VVL && tau3_VVL && tau3_IsoB && !tau4_IsoB;
        else if (channel==3 or channel==9) isCat1 = tau4_VVL && !tau4_Iso_ltau && (eid80_3 && (eiso_3 < TightEle));
        else if (channel==5 or channel==11) isCat1 = tau4_VVL && !tau4_Iso_ltau && (muidL_3 && (muiso_3 < TightMu));
        else if (channel==2 or channel==8) isCat1 = (muidL_3 && (muiso_3 < TightMu)) && (!eid80_4 or (eiso_4 > TightEle));
        else if (channel==1 or channel==7) isCat1 = (eid80_3 && (eiso_3 < TightEle)) && (!eid80_4 or (eiso_4 > TightEle));
        else if (channel==4 or channel==10) isCat1 = (muidL_3 && (muiso_3 < TightMu)) && (!muidL_4 or (muiso_4 > TightMu));

	// The first lepton fails
        if (channel==6 or channel==12) isCat2 = tau4_VVL && tau3_VVL && !tau3_IsoB && tau4_IsoB;
        else if (channel==3 or channel==9) isCat2 = tau4_VVL && tau4_Iso_ltau && (!eid80_3 or (eiso_3 > TightEle));
        else if (channel==5 or channel==11) isCat2 = tau4_VVL && tau4_Iso_ltau && (!muidL_3 or (muiso_3 > TightMu));
        else if (channel==2 or channel==8) isCat2 = (!muidL_3 or (muiso_3 > TightMu)) && (eid80_4 && (eiso_4 < TightEle));
        else if (channel==1 or channel==7) isCat2 = (!eid80_3 or (eiso_3 > TightEle)) && (eid80_4 && (eiso_4 < TightEle));
        else if (channel==4 or channel==10) isCat2 = (!muidL_3 or (muiso_3 > TightMu)) && (muidL_4 && (muiso_4 < TightMu));

	// Definition of observable and additional cuts
	TLorentzVector MET(met*cos(metphi),met*sin(metphi),0,0);
	TLorentzVector Zboson = l1+l2;
 	TLorentzVector Hboson_vis=l3+l4;
	if (q_1*q_2>0) continue;

        bool Cut_SR=(l1+l2).M()<120 && (l1+l2).M()>60;
        bool Cut_Shape=(l1+l2).M()<120 && (l1+l2).M()>60;
	float var=m_four;//Zboson.Mag();
	float mass=(l1+l2).M();
	var=(l3+l4).M();
	//var=l3.Pt();
 	//var=m_sv;
	float w=w_pu * w_eff * weight;
	if (sample=="data_obs") w=1.0;

        //#######################
        //######   MMTT   ####### 
        //#######################

        if (OS && (channel==12 or channel == 6) && l3.Pt()+l4.Pt()>LT_tt) {
            if (isCat0) {
                fillTreeN(BG_Tree,channel,0,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (isCat1) {
                fillTreeN(BG_Tree,channel,1,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (isCat2) {
                fillTreeN(BG_Tree,channel,2,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (lepton_isolation) {
                if (Cut_SR && channel==6) h_mmtt->Fill(var,w);
                if (Cut_SR && channel==12) h_eett->Fill(var,w);
                fillTreeN(BG_Tree,channel,3,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
        }
	//Shape
        if (Cut_Shape && SS && (channel==12 or channel == 6) && l3.Pt()+l4.Pt()>LT_tt) {
            if (tau3_VVL && tau4_VVL) {
                if (channel==6) h_mmtt_shape->Fill(var,w);
                if (channel==12) h_eett_shape->Fill(var,w);
                fillTreeN(BG_Tree,channel,4,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            } 
        }

        //######################
        //######   MMET   ######
        //######################

        if (OS && (channel==9 or channel==3) && l3.Pt()+l4.Pt()>LT_et) {
            if (isCat0) {
                fillTreeN(BG_Tree,channel,0,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (isCat1) {
                fillTreeN(BG_Tree,channel,1,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (isCat2) {
                fillTreeN(BG_Tree,channel,2,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (lepton_isolation) {
                if (Cut_SR && channel==3) h_mmet->Fill(var,w);
                if (Cut_SR && channel==9) h_eeet->Fill(var,w);
                fillTreeN(BG_Tree,channel,3,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
	}
	// Shape reducible ET 
        if (Cut_Shape && SS && (channel==9 or channel==3) && l3.Pt()+l4.Pt()>LT_et) { 
            if (eid90_3 && eiso_3<2.0 && tau4_VVL) {
                if (channel==3) h_mmet_shape->Fill(var,w);
                if (channel==9) h_eeet_shape->Fill(var,w);
                fillTreeN(BG_Tree,channel,4,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
        }

        //######################
        //######   MMMT   ######
        //######################
        if (OS && (channel==11 or channel==5) && l3.Pt()+l4.Pt()>LT_mt) {
            if (isCat0) {
                fillTreeN(BG_Tree,channel,0,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (isCat1) {
                fillTreeN(BG_Tree,channel,1,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (isCat2) {
                fillTreeN(BG_Tree,channel,2,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (lepton_isolation) {
                if (Cut_SR && channel==5) h_mmmt->Fill(var,w);
                if (Cut_SR && channel==11) h_eemt->Fill(var,w);
                fillTreeN(BG_Tree,channel,3,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
	}
        // Shape reducible MT
        if (Cut_Shape && SS && (channel==5 or channel==11) && l3.Pt()+l4.Pt()>LT_mt) {
            if (muidL_3 && muiso_3<2.0 && tau4_VVL) {
                if (channel==5) h_mmmt_shape->Fill(var,w);
                if (channel==11) h_eemt_shape->Fill(var,w);
                fillTreeN(BG_Tree,channel,4,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
        }

        //######################
        //######   MMME   ######
        //######################
        if (OS && (channel==2 or channel==8) && l3.Pt()+l4.Pt()>LT_em) {
            if (isCat0) {
                fillTreeN(BG_Tree,channel,0,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (isCat1) {
                fillTreeN(BG_Tree,channel,1,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (isCat2) {
                fillTreeN(BG_Tree,channel,2,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
            if (lepton_isolation) {
                if (channel==2 && Cut_SR) h_mmem->Fill(var,w);
                if (channel==8 && Cut_SR) h_eeem->Fill(var,w);
                fillTreeN(BG_Tree,channel,3,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
	}
        if (Cut_Shape && SS && (channel==2 or channel==8) && l3.Pt()+l4.Pt()>LT_em) {
            if (eiso_4<2.0 && muiso_3<2.0 && muidL_3 && eid90_4) {
                if (channel==2) h_mmem_shape->Fill(var,w);
                if (channel==8) h_eeem_shape->Fill(var,w);
                fillTreeN(BG_Tree,channel,4,var,pt_3,eta_3,closeJetPt_3,pt_4,eta_4,closeJetPt_4,w,Cut_SR,decayMode_3,decayMode_4);
            }
        }

        //####################################################
        // Fake Rate Measurement
        //####################################################
        bool FR_Estimation = true;
	bool isClosePt=true;
  	float varfr3=pt_3;
	float varfr4=pt_4;
        float tauvar3=pt_3;
	float tauvar4=pt_4;
	if (isClosePt && closeJetPt_3>pt_3){
 	   tauvar3=closeJetPt_3;
	}
	else tauvar3=0.5;
        if (isClosePt && closeJetPt_4>pt_4){
           tauvar4=closeJetPt_4;
     	}
	else tauvar4=0.5;

        if ((channel==6 or channel==12) && SS && l3.Pt()+l4.Pt()>50) {
	    // Inclusive in DM
            if (FR_Estimation && tau3_VVL) plotFill("FR_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_VVL && fabs(l3.Eta())<1.5) plotFill("FR_B_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_VVL && fabs(l3.Eta())>1.5) plotFill("FR_E_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL) plotFill("FR_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && fabs(l4.Eta())<1.5) plotFill("FR_B_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && fabs(l4.Eta())>1.5) plotFill("FR_E_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL) plotFill("FR_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && fabs(l3.Eta())<1.5) plotFill("FR_B_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && fabs(l3.Eta())>1.5) plotFill("FR_E_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL) plotFill("FR_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && fabs(l4.Eta())<1.5) plotFill("FR_B_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && fabs(l4.Eta())>1.5) plotFill("FR_E_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);

	    // DM == 0 (1 prong)
            if (FR_Estimation && tau3_VVL && decayMode_3==0) plotFill("FR_DM0_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_VVL && fabs(l3.Eta())<1.5 && decayMode_3==0) plotFill("FR_DM0_B_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_VVL && fabs(l3.Eta())>1.5 && decayMode_3==0) plotFill("FR_DM0_E_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && decayMode_4==0) plotFill("FR_DM0_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && fabs(l4.Eta())<1.5 && decayMode_4==0) plotFill("FR_DM0_B_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && fabs(l4.Eta())>1.5 && decayMode_4==0) plotFill("FR_DM0_E_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && decayMode_3==0) plotFill("FR_DM0_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && fabs(l3.Eta())<1.5 && decayMode_3==0) plotFill("FR_DM0_B_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && fabs(l3.Eta())>1.5 && decayMode_3==0) plotFill("FR_DM0_E_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && decayMode_4==0) plotFill("FR_DM0_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && fabs(l4.Eta())<1.5 && decayMode_4==0) plotFill("FR_DM0_B_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && fabs(l4.Eta())>1.5 && decayMode_4==0) plotFill("FR_DM0_E_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);

	    // DM == 1 (1 prong + pizero)
            if (FR_Estimation && tau3_VVL && decayMode_3==1) plotFill("FR_DM1_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_VVL && fabs(l3.Eta())<1.5 && decayMode_3==1) plotFill("FR_DM1_B_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_VVL && fabs(l3.Eta())>1.5 && decayMode_3==1) plotFill("FR_DM1_E_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && decayMode_4==1) plotFill("FR_DM1_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && fabs(l4.Eta())<1.5 && decayMode_4==1) plotFill("FR_DM1_B_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && fabs(l4.Eta())>1.5 && decayMode_4==1) plotFill("FR_DM1_E_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && decayMode_3==1) plotFill("FR_DM1_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && fabs(l3.Eta())<1.5 && decayMode_3==1) plotFill("FR_DM1_B_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && fabs(l3.Eta())>1.5 && decayMode_3==1) plotFill("FR_DM1_E_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && decayMode_4==1) plotFill("FR_DM1_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && fabs(l4.Eta())<1.5 && decayMode_4==1) plotFill("FR_DM1_B_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && fabs(l4.Eta())>1.5 && decayMode_4==1) plotFill("FR_DM1_E_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);

	    // DM == 10 (3 prongs)
            if (FR_Estimation && tau3_VVL && decayMode_3==10) plotFill("FR_DM10_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_VVL && fabs(l3.Eta())<1.5 && decayMode_3==10) plotFill("FR_DM10_B_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_VVL && fabs(l3.Eta())>1.5 && decayMode_3==10) plotFill("FR_DM10_E_tau_tt_Den", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && decayMode_4==10) plotFill("FR_DM10_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && fabs(l4.Eta())<1.5 && decayMode_4==10) plotFill("FR_DM10_B_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_VVL && fabs(l4.Eta())>1.5 && decayMode_4==10) plotFill("FR_DM10_E_tau_tt_Den", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && decayMode_3==10) plotFill("FR_DM10_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && fabs(l3.Eta())<1.5 && decayMode_3==10) plotFill("FR_DM10_B_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau3_IsoB && tau3_VVL && fabs(l3.Eta())>1.5 && decayMode_3==10) plotFill("FR_DM10_E_tau_tt_Num", tauvar3, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && decayMode_4==10) plotFill("FR_DM10_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && fabs(l4.Eta())<1.5 && decayMode_4==10) plotFill("FR_DM10_B_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);
            if (FR_Estimation && tau4_IsoB && tau4_VVL && fabs(l4.Eta())>1.5 && decayMode_4==10) plotFill("FR_DM10_E_tau_tt_Num", tauvar4, nb_bins, 0, nb_bins, w);
        }

        bool lepTauFR_denum = SS && (channel==9 or channel==3 or channel==11 or channel==5);
        if (lepTauFR_denum) {
            if (lepTauFR_denum && tau4_VVL) plotFill("FR_tau_lt_Den", varfr4, nb_bins, 0, nb_bins, w);
            if (lepTauFR_denum && tau4_Iso_ltau && tau4_VVL) plotFill("FR_tau_lt_Num", varfr4, nb_bins, 0, nb_bins, w);
            //if (lepTauFR_denum && tau4_VVL) plotFill("FR_tau_tt_Den", varfr4, nb_bins, 0, nb_bins, w);
            //if (lepTauFR_denum && tau4_Iso_ltau && tau4_VVL) plotFill("FR_tau_tt_Num", varfr4, nb_bins, 0, nb_bins, w);
        }

        bool eleFR_denum_0 = ((channel==9 or channel==3) && SS && sqrt(pow(l3.Pt()+met,2)-pow(l3.Px()+met*cos(metphi),2)-pow(l3.Py()+met*sin(metphi),2))<20);
        if (eleFR_denum_0) {
            plotFill("FR_ele_Den", varfr3, nb_bins, 0, nb_bins, w);
            if (fabs(l3.Eta())<1.5) plotFill("FR_B_ele_Den", varfr3, nb_bins, 0, nb_bins, w);
            if (fabs(l3.Eta())>1.5) plotFill("FR_E_ele_Den", varfr3, nb_bins, 0, nb_bins, w);
            if (eid80_3 && eiso_3 < TightEle) plotFill("FR_ele_loose_Num", varfr3, nb_bins, 0, nb_bins, w);
            if (eid80_3 && eiso_3 < TightEle) plotFill("FR_ele_tight_Num", varfr3, nb_bins, 0, nb_bins, w);
            if (eid80_3 && eiso_3 < TightEle && fabs(l3.Eta())<1.5) plotFill("FR_B_ele_loose_Num", varfr3, nb_bins, 0, nb_bins, w);
            if (eid80_3 && eiso_3 < TightEle && fabs(l3.Eta())<1.5) plotFill("FR_B_ele_tight_Num", varfr3, nb_bins, 0, nb_bins, w);
            if (eid80_3 && eiso_3 < TightEle && fabs(l3.Eta())>1.5) plotFill("FR_E_ele_loose_Num", varfr3, nb_bins, 0, nb_bins, w);
            if (eid80_3 && eiso_3 < TightEle && fabs(l3.Eta())>1.5) plotFill("FR_E_ele_tight_Num", varfr3, nb_bins, 0, nb_bins, w);
        }

        bool muFR_denum_0 = ((channel==11 or channel==5) && SS && sqrt(pow(l3.Pt()+met,2)-pow(l3.Px()+met*cos(metphi),2)-pow(l3.Py()+met*sin(metphi),2))<20);
        if (muFR_denum_0) {
            plotFill("FR_mu_Den", varfr3, nb_bins, 0, nb_bins, w);
            if (fabs(l3.Eta())<1.5) plotFill("FR_B_mu_Den", varfr3, nb_bins, 0, nb_bins, w);
            if (fabs(l3.Eta())>1.5) plotFill("FR_E_mu_Den", varfr3, nb_bins, 0, nb_bins, w);
            if (muidL_3 && muiso_3 < TightMu) plotFill("FR_mu_loose_Num", varfr3, nb_bins, 0, nb_bins, w);
            if (muidL_3 && muiso_3 < TightMu) plotFill("FR_mu_tight_Num", varfr3, nb_bins, 0, nb_bins, w);
            if (muidL_3 && muiso_3 < TightMu && fabs(l3.Eta())<1.5) plotFill("FR_E_mu_loose_Num", varfr3, nb_bins, 0, nb_bins, w);
            if (muidL_3 && muiso_3 < TightMu && fabs(l3.Eta())<1.5) plotFill("FR_E_mu_tight_Num", varfr3, nb_bins, 0, nb_bins, w);
            if (muidL_3 && muiso_3 < TightMu && fabs(l3.Eta())>1.5) plotFill("FR_B_mu_loose_Num", varfr3, nb_bins, 0, nb_bins, w);
            if (muidL_3 && muiso_3 < TightMu && fabs(l3.Eta())>1.5) plotFill("FR_B_mu_tight_Num", varfr3, nb_bins, 0, nb_bins, w);
        }
    }

    fout->cd();
    BG_Tree->Write();

    map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    map<string, TH1F*>::const_iterator jMap1 = myMap1->end();

    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();

    map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    map<string, TH2F*>::const_iterator jMap2 = myMap2->end();

    for (; iMap2 != jMap2; ++iMap2)
        nplot2(iMap2->first)->Write();

    TString postfix="";
    if (tes==1)
        postfix="TESUp";
    if (tes==-1)
        postfix="TESDown";
    TString shape="_shape_";

    TDirectory *dir_mmee =fout->mkdir("mmee");
    dir_mmee->cd();
    h_mmee->SetName(name.c_str()+postfix);
    h_mmee->Write();
    h_mmee_shape->SetName(name.c_str()+shape+postfix);
    h_mmee_shape->Write();
    TDirectory *dir_mmem =fout->mkdir("mmem");
    dir_mmem->cd();
    h_mmem->SetName(name.c_str()+postfix);
    h_mmem->Write();
    h_mmem_shape->SetName(name.c_str()+shape+postfix);
    h_mmem_shape->Write();
    TDirectory *dir_mmmm =fout->mkdir("mmmm");
    dir_mmmm->cd();
    h_mmmm->SetName(name.c_str()+postfix);
    h_mmmm->Write();
    h_mmmm_shape->SetName(name.c_str()+shape+postfix);
    h_mmmm_shape->Write();
    TDirectory *dir_mmet =fout->mkdir("mmet");
    dir_mmet->cd();
    h_mmet->SetName(name.c_str()+postfix);
    h_mmet->Write();
    h_mmet_shape->SetName(name.c_str()+shape+postfix);
    h_mmet_shape->Write();
    TDirectory *dir_mmmt =fout->mkdir("mmmt");
    dir_mmmt->cd();
    h_mmmt->SetName(name.c_str()+postfix);
    h_mmmt->Write();
    h_mmmt_shape->SetName(name.c_str()+shape+postfix);
    h_mmmt_shape->Write();
    TDirectory *dir_mmtt =fout->mkdir("mmtt");
    dir_mmtt->cd();
    h_mmtt->SetName(name.c_str()+postfix);
    h_mmtt->Write();
    h_mmtt_shape->SetName(name.c_str()+shape+postfix);
    h_mmtt_shape->Write();

    TDirectory *dir_eeee =fout->mkdir("eeee");
    dir_eeee->cd();
    h_eeee->SetName(name.c_str()+postfix);
    h_eeee->Write();
    h_eeee_shape->SetName(name.c_str()+shape+postfix);
    h_eeee_shape->Write();
    TDirectory *dir_eeem =fout->mkdir("eeem");
    dir_eeem->cd();
    h_eeem->SetName(name.c_str()+postfix);
    h_eeem->Write();
    h_eeem_shape->SetName(name.c_str()+shape+postfix);
    h_eeem_shape->Write();
    TDirectory *dir_eemm =fout->mkdir("eemm");
    dir_eemm->cd();
    h_eemm->SetName(name.c_str()+postfix);
    h_eemm->Write();
    h_eemm_shape->SetName(name.c_str()+shape+postfix);
    h_eemm_shape->Write();
    TDirectory *dir_eeet =fout->mkdir("eeet");
    dir_eeet->cd();
    h_eeet->SetName(name.c_str()+postfix);
    h_eeet->Write();
    h_eeet_shape->SetName(name.c_str()+shape+postfix);
    h_eeet_shape->Write();
    TDirectory *dir_eemt =fout->mkdir("eemt");
    dir_eemt->cd();
    h_eemt->SetName(name.c_str()+postfix);
    h_eemt->Write();
    h_eemt_shape->SetName(name.c_str()+shape+postfix);
    h_eemt_shape->Write();
    TDirectory *dir_eett =fout->mkdir("eett");
    dir_eett->cd();
    h_eett->SetName(name.c_str()+postfix);
    h_eett->Write();
    h_eett_shape->SetName(name.c_str()+shape+postfix);
    h_eett_shape->Write();

    fout->Close();
}

