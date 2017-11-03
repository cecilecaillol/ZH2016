import ROOT
import re
from array import array
import argparse

hist=["ZZ","ZH125","Reducible","data_obs"]
fs=["mmem","mmet","mmmt","mmtt","eeem","eeet","eemt","eett"]
name=["em","et","mt","tt","eeem","eeet","eemt","eett"]

nhist=4
nfs=8

myfile=ROOT.TFile("moyen.root")
for i in range (0,nhist):
   #myfile=ROOT.TFile("files_nominal/"+hist[i]+".root")
   for j in range (0,nfs):
      histo=myfile.Get(fs[j]).Get(hist[i])
      print fs[j],hist[i],histo.Integral()
   
