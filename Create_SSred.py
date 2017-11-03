#!/usr/bin/env python
import ROOT
import re
from array import array

fileIn=ROOT.TFile("moyen.root","r")
fileOut=ROOT.TFile("final.root","recreate")
categories=["eeem","eeet","eemt","eett","mmem","mmet","mmmt","mmtt"]
#categories=["eeet","eemt","eett","mmem","mmet","mmmt"]

shape=ROOT.TH1F
red=ROOT.TH1F
#shape=fileOut.Get("eeee").Get("data_obs_shape").Clone()
#red=fileOut.Get("eeee").Get("Reducible")

for i in range(0,8):
#for i in range(0,6):
   fileIn.cd(categories[i]);
   mc = ROOT.gDirectory
   dirListMC = mc.GetListOfKeys()
   fileOut.cd()
   fileOut.mkdir(categories[i])
   fileOut.cd(categories[i])
   for k1 in dirListMC:
      h1 = k1.ReadObj()
      h1.Write()
      if (h1.GetName()=="Reducible"):
	 red=h1.Clone()
      if (h1.GetName()=="data_obs_shape_"):
         shape=h1.Clone()  
   shape.SetName("RedSS")
   shape.Scale(red.Integral()/shape.Integral())
   shape.Write()


