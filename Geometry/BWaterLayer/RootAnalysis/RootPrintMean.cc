#include "TFile.h"
#include "TTree.h"

void RootPrintMean(){//const std::string& fName
  
  TFile *f1 = new TFile("../EventSelection/RootFiles_SelectedEvents/Simus_20MeV/Simus_neutron_20MeV_BWater100mm_Threshold0keV_EnergyDeposited_Sensitive_or.root");
  
  if(f1->IsOpen()){

    TH1F *h1 = new TH1F();
    
    h1 = (TH1F*)f1->Get("h0");//h1->GetName()

    double average = 0.;
    
    for (int ibin=1; ibin<h1->GetNbinsX()+1; ibin++){
      average += h1->GetBinCenter(ibin)*h1->GetBinContent(ibin);
      cout << ibin << " " << h1->GetBinCenter(ibin) << " " << h1->GetBinContent(ibin) << endl;
    }

    average /= h1->GetEntries();
    
    cout << h1->GetMean() << endl;
    cout << average << endl;
    
    
  }
  else{
    cout << "The file did not open!" << endl;
    return 6;
  }
    
  return 0;
}
