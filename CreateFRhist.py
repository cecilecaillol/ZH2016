import ROOT
import re
from array import array
import argparse

hist=["FR_tau_tt_Num","FR_tau_tt_Den","FR_tau_lt_Num","FR_tau_lt_Den","FR_mu_loose_Num","FR_mu_tight_Num","FR_mu_Den","FR_ele_loose_Num","FR_ele_tight_Num","FR_ele_Den"]

fileData=ROOT.TFile("files_nominal/Data.root","r")
fileZZ=ROOT.TFile("files_nominal/ZZ.root","r")
fileWZ=ROOT.TFile("files_nominal/WZ.root","r")
fileDataSub=ROOT.TFile("files_nominal/DataSub.root","recreate")

ncat=10

for i in range (0,ncat):
   Data=fileData.Get(hist[i])
   Data.Sumw2()
   #Data.Add(fileZZ.Get(hist[i]),-1)
   Data.Add(fileWZ.Get(hist[i]),-1)
   for j in range(1,Data.GetSize()-2):
      if Data.GetBinContent(j)<0:
	Data.SetBinContent(j,0)
   Data.SetName(hist[i])
   fileDataSub.cd()
   Data.Write()

