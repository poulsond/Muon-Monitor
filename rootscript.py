#!/usr/bin/python

import sys
import ROOT
from math import sqrt
from array import *

filelist = sys.argv[1:]

t1=ROOT.TCanvas()
t2=ROOT.TCanvas()
t3=ROOT.TCanvas()

max = 9000            #max number of photons created in one run
bins = max
total_photons = 0
photon_hits = 0

fWavelength_count = 0 
PMTeff = 0            #represents how many photons are missed by PMT, calculated
                      #from the effiency curve, as described below
bineff = array('f',[0.3,0.29,0.25,0.2,0.13,0.09,0.025])

#bineff[0] for 300-350nm, bineff[1] for 350-400nm
#bineff[2] for 400-450nm, bineff[3] for 450-500nm
#bineff[4] for 500-550nm, bineff[5] for 550-600nm
#bineff[6] for 600-650nm

for file in filelist:

     tempfile=ROOT.TFile.Open(file)
     fTree=tempfile.Get("fTree")

     t1.cd()
     h1=ROOT.TH1D("h1","Number of Photons Produced",bins,0,max)
     h1.GetXaxis().SetTitle("Number of Photons")
     h1.GetYaxis().SetTitle("Occurances")
     fTree.Draw("fNPhotons>>h1")
#     t1.Print('~/plot1.png')

     NumEvents = h1.Integral()  #calculate the number of events simulated
     
     t2.cd()
     h2=ROOT.TH1D("h2","Number of Photons Detected",bins,0,max)
     h2.GetXaxis().SetTitle("Number of Photons")
     h2.GetYaxis().SetTitle("Occurances")
     fTree.Draw("fNHits>>h2")
#     t2.Print('~/plot2.png')

     t3.cd()
     h3=ROOT.TH1D("h3","Wavelength",7,300,650) #wavelength of detected photons
     h3.GetXaxis().SetTitle("Wavelength")
     h3.GetYaxis().SetTitle("Occurances")
     fTree.Draw("fWavelength_nm>>h3")
#     t3.Print('~/plot3.png')

     for y in range(1,8):
          fWavelength_count += h3.GetBinContent(y)
          PMTeff += h3.GetBinContent(y)*bineff[y-1]
          
          
     for x in range(1,bins):
          total_photons += h1.GetBinContent(x)*x
          photon_hits += h2.GetBinContent(x)*x

print ''
print 'mean # photons created per decayed muon = ' + str(total_photons/NumEvents)
print 'mean # photons detected per decayed muon = ' + str(photon_hits/NumEvents)
print 'mean efficiency = ' +str(photon_hits/total_photons)
print 'w/ PMT efficiency, mean # photons detected = '+str((PMTeff)/NumEvents)
print 'and the mean effeciency = ' + str((PMTeff)/total_photons)

input = raw_input('Press any key to quit this program')
if input == '':
     print ''
