#ifndef TR_TREE_H
#define	TR_TREE_H

#include "TFormula.h"
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
#include <map>
#include "TH1.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility>

#include "makeHisto.h"
#include "myHelper.h"


float run,lumi,evt,gen_weight,npv,npu,NUP,passDoubleMu,njets,nbtag,m_pair1,m_pair2,m_four,vetomu,vetoele,passDoubleEle;
float eta_1,phi_1,pt_1,px_1,py_1,pz_1,e_1,m_1,q_1,muiso_1,matchDoubleMu_1,muidL_1,muidM_1,muidT_1,genmatch_1=-1;
float eta_2,phi_2,pt_2,px_2,py_2,pz_2,e_2,m_2,q_2,muiso_2,matchDoubleMu_2,muidL_2,muidM_2,muidT_2,genmatch_2=-1;
float eta_3,phi_3,pt_3,px_3,py_3,pz_3,e_3,m_3,q_3,muiso_3,eiso_3,muidL_3,muidM_3,muidT_3,antieleVL_3,antieleL_3,antieleM_3,antieleT_3,antieleVT_3,antimuL_3,antimuT_3,matchDoubleMu_3,eid80_3,eid90_3,genmatch_3,decayMode_3,tauMVAisoVL_3,tauMVAisoL_3,tauMVAisoM_3,tauMVAisoT_3,tauMVAisoVT_3,closeJetPt_3,tauMVAisoRaw_3=-1;
float eta_4,phi_4,pt_4,px_4,py_4,pz_4,e_4,m_4,q_4,muiso_4,eiso_4,muidL_4,muidM_4,muidT_4,antieleVL_4,antieleL_4,antieleM_4,antieleT_4,antieleVT_4,antimuL_4,antimuT_4,matchDoubleMu_4,eid80_4,eid90_4,genmatch_4,decayMode_4,tauMVAisoVL_4,tauMVAisoL_4,tauMVAisoM_4,tauMVAisoT_4,tauMVAisoVT_4,closeJetPt_4,tauMVAisoRaw_4=-1;
float channel,met,metphi,mvaMet,mvaMetPhi,mvametcov00,mvametcov10,mvametcov01,mvametcov11;

float m_sv, m_sv_10UP, m_sv_10DOWN, m_sv_01UP, m_sv_01DOWN, m_sv_11UP, m_sv_11DOWN;

//New BG_Tree
int channel_;
int subchannel_;
float var_;
float pt_3_;
float decayMode_3_;
float decayMode_4_;
float eta_3_;
float closeJetPt_3_;
float pt_4_;
float eta_4_;
float closeJetPt_4_;
float w_;
bool isSR_;
bool isHigh_;

void fillTreeN(TTree* BG_Tree,int Channel,int subChannel,float var,float l3Pt,float l3Eta,float l3_CloseJetPt,float l4Pt,float l4Eta,float l4_CloseJetPt,float Weight, bool SR, float dm3, float dm4) {

    channel_ = Channel;
    subchannel_ = subChannel;
    var_=var;
    pt_3_ = l3Pt;
    eta_3_ = l3Eta;
    decayMode_3_=dm3;
    decayMode_4_=dm4;
    closeJetPt_3_ = l3_CloseJetPt;
    pt_4_ = l4Pt;
    eta_4_ = l4Eta;
    closeJetPt_4_ = l4_CloseJetPt;
    w_ = Weight;
    isSR_ =SR;

    BG_Tree->Fill();
}


#endif

