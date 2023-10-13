// Example How to run:
// RootDrawEnergyDistributions(100,1,"neutron","B")

#include "TFile.h"
#include "TTree.h"

void RootDrawDifferencialGammaFlux() {

  TF1 *fGamma = new TF1("f1","[0]*pow(x,[1])",0.01,100e3); // MeV

  fGamma->SetParameters(3,-2);

  TH1D *hGamma = new TH1D("hGamma","Atm Gamma Spectrum",100, 0.01,100e3); // MeV

  for(int i=1;i<101;++i){
    Double_t ene = hGamma->GetBinCenter(i);
    hGamma->SetBinContent(i, fGamma->Eval(ene));
  }
  
  Double_t flux = hGamma->Integral("width"); // atm gamma flux: particles / cm2 / s, should be around 0.015, probably need to use bins with variable width to take into account for the 5 orders of magnitude...

  cout << flux << endl;

  hGamma->SetTitle("Gamma flux cf Thiago");
  hGamma->GetXaxis()->SetTitle("Energy (MeV)");
  hGamma->GetYaxis()->SetTitle("Differential flux");
  
  hGamma->Draw();
  hGamma->SaveAs("Atmospheric_Gamma_differential_energy.root");
  
  return 0;
}
