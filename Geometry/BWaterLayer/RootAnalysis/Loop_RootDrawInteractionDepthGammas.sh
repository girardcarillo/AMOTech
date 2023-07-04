#!/bin/bash

echo Executing macro for gammas

# Execute the root macro
# SelectEvents(string SelectedVolumes, int BWaterThickness, double energy, string partType, bool WaterOnly = 0, bool thermal = 0, double DetectionThreshold = 0.) {
root -l -b <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/RootAnalysis/RootDrawInteractionDepth.cc
for (int j=2;j<8;j+=5) {for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,j+0.6,"gamma","Depth");}}
for (int j=2;j<8;j+=5) {for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,j+0.6,"gamma","DepthFirstHit");}}
for (int j=2;j<8;j+=5) {for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,j+0.6,"gamma","DepthEnergy");}}
for (int j=2;j<8;j+=5) {for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,j+0.6,"gamma","DepthEnergyFirstHit");}}
.q
EOC

