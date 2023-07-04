#!/bin/bash

echo Executing macro for $1 MeV neutrons

# Execute the root macro
# SelectEvents(string SelectedVolumes, int BWaterThickness, double energy, string partType, bool WaterOnly = 0, bool thermal = 0, double DetectionThreshold = 0.) {
   root -l -b <<EOC
.L /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/RootAnalysis/RootDrawInteractionDepth.cc
for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,$1,"neutron","Depth");}
for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,$1,"neutron","DepthFirstHit");}
for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,$1,"neutron","DepthEnergy");}
for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,$1,"neutron","DepthEnergyFirstHit");}
for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,$1,"neutron","Depth","B");}
for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,$1,"neutron","DepthFirstHit","B");}
for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,$1,"neutron","DepthEnergy","B");}
for (int i=100;i<600;i+=400){RootDrawInteractionDepth(i,$1,"neutron","DepthEnergyFirstHit","B");}
.q
EOC
