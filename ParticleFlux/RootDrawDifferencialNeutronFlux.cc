// Example How to run:
// RootDrawEnergyDistributions(100,1,"neutron","B")

#include "TFile.h"
#include "TTree.h"

void RootDrawDifferencialNeutronFlux(bool IglooFlux = 0) {

  // IglooFlux = true if we want to normalize the histogram with the Igloo top surface (1120x800 cm2) 
  
  double IglooSurface = 9e5 ; // cm2
  
  TCanvas *c1 = new TCanvas("c1","",2560,1368);

  TString path = "/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/ParticleFlux/";
  
  // test for thermal
  // TString path = "/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/EventSelection/RootFiles_SelectedEvents/Simus_neutron_2.5e-08MeV_"+bore+"Water"+to_string(BWaterThickness)+"mm_Threshold0keV_EnergyDeposited";
  
  TFile *f0 = new TFile(path + "Gordon_et_al_model_differencial_neutron_flux.root");

  TH1F *hFlux = new TH1F();
  hFlux = (TH1F*)f0->Get("Neutron_flux");
  
  double MinX = hFlux->GetXaxis()->FindBin(1);
  double MinY = gPad->GetUymin();
  
  hFlux->GetXaxis()->SetRangeUser(MinX,110);
  // hFlux->GetXaxis()->SetRangeUser(1,1e4);

  if (IglooFlux) {
    
    hFlux->Scale(IglooSurface);

  }
  hFlux->GetYaxis()->SetTitle("Normalized differential flux (/cm^{2} /s)");

  // If we want to obtain the flux in neutrons/sec
  for (int i = 0 ; i < hFlux->GetXaxis()->FindBin(1e4) ; i++) {
    hFlux->SetBinContent(i, hFlux->GetBinContent(hFlux->GetXaxis()->FindBin(hFlux->GetXaxis()->GetBinCenter(i))) * hFlux->GetXaxis()->GetBinCenter(i));
  }
  hFlux->GetYaxis()->SetTitle("Normalized differential flux (neutrons/s)");
  
  hFlux->SetLineColor(kTeal+2);
  
  hFlux->Draw("HISTE");
    
  c1->SetLogx();
  // c1->SetLogy();

  double yvalue1 = hFlux->GetBinContent(hFlux->GetXaxis()->FindBin(1));
  double yvalue20 = hFlux->GetBinContent(hFlux->GetXaxis()->FindBin(20));
  double yvalue100 = hFlux->GetBinContent(hFlux->GetXaxis()->FindBin(110));
  
  TLine *line = new TLine(1,MinY,1,yvalue1);
  line->SetLineColor(kBlack); 
  line->SetLineWidth(2); 
  line->SetLineStyle(7); 
  line->Draw(""); 

  TLine *line1 = new TLine(20,MinY,20,yvalue20);
  line1->SetLineColor(kBlack); 
  line1->SetLineWidth(2); 
  line1->SetLineStyle(7); 
  line1->Draw(""); 

  TLine *line2 = new TLine(100,MinY,100,yvalue100);
  line2->SetLineColor(kBlack); 
  line2->SetLineWidth(2); 
  line2->SetLineStyle(7); 
  line2->Draw(""); 

  TLine *line3 = new TLine(MinX,yvalue20,20,yvalue20);
  line3->SetLineColor(kBlack); 
  line3->SetLineWidth(2); 
  line3->SetLineStyle(7); 
  line3->Draw(""); 
  
  TLine *line4 = new TLine(MinX,yvalue100,100,yvalue100);
  line4->SetLineColor(kBlack); 
  line4->SetLineWidth(2); 
  line4->SetLineStyle(7); 
  line4->Draw(""); 

  cout << "\nThe total neutron flux integrated over the energy range [1,100] MeV is "
       << hFlux->Integral(1,100)
       << " neutrons/s" << endl;
  
  if (IglooFlux) {

    cout << "\nThe number of neutrons reaching the top of the Igloo per second is:" << endl;
    cout << "1 MeV neutrons: " << yvalue1 << " neutrons/s \n" 
	 << "20 MeV neutrons: " << yvalue20 << " neutrons/s \n"
	 << "100 MeV neutrons: " << yvalue100 << " neutrons/s" << endl << endl; 

  }
  // TString fOutputName =  "Energy_distributions_" + senergy + "MeV_" + bore + "Water" + to_string(BWaterThickness) + "mm.pdf";
  // // c1->Update();  
  // c1->SaveAs(fOutputName);
  
}
