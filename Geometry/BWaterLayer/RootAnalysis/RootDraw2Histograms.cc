// RootDraw2Histograms("../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/SelectedEvents/OutputFiles/energy_deposited_AMOTech_and.root","../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/SelectedEvents/OutputFiles/energy_deposited_Armor_and.root","energy_deposited_Armor_AMOTech_and.pdf",1)

#include "TFile.h"
#include "TTree.h"

void RootDraw2Histograms(int BWaterThickness, int PrimaryEnergy) {

  TString path = "/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/EventSelection/RootFiles_SelectedEvents/Simus_neutron_"+to_string(PrimaryEnergy)+"MeV_BWater"+to_string(BWaterThickness)+"mm_Threshold0keV_EnergyDeposited";
  
  TCanvas *c1 = new TCanvas("c1","",2560,1368);
  
  TFile *f0 = new TFile(path + "_Sensitive_or.root");//Sensitive
  TFile *f1 = new TFile(path + "_BWater_or.root");//BWater

  TH1F *hBWater = new TH1F();
  hBWater = (TH1F*)f0->Get("h0");

  TH1F *hSensitive = new TH1F();
  hSensitive = (TH1F*)f1->Get("h1");

  // hBWater->SetNameTitle("hBWater", "");
  // if (!(hBWater->GetSumw2N() > 0)) hBWater->Sumw2(kTRUE); // ensure proper error propagation
  // hBWater->Add(h1, -1.0);

  hSensitive->SetTitle("");
  hSensitive->GetXaxis()->SetTitle("Energy (MeV)");
  hSensitive->GetYaxis()->SetTitle("# Counts");
  
  hSensitive->Rebin(2);
  hSensitive->SetLineColor(kMagenta+3);
  hSensitive->SetFillStyle(3004);
  hSensitive->SetFillColor(hSensitive->GetLineColor());
  // hSensitive->SetFillColorAlpha(hSensitive->GetLineColor(),0.55);
  hSensitive->SetLineWidth(2);

  // hSensitive->GetXaxis()->SetRangeUser(0.,4.);
  hSensitive->Draw();
  
  hBWater->Rebin(2);
  hBWater->SetLineColor(kOrange+9);
  hBWater->SetFillStyle(3005);
  hBWater->SetFillColor(hBWater->GetLineColor());
  // hBWater->SetFillColorAlpha(hBWater->GetLineColor(),0.55);
  hBWater->SetLineWidth(2);

  hBWater->Draw("SAME");
  
  c1->SetLogy();
  
  auto fa1 = new TF1("fa1","1",0.001,500);
  
  // TFrame *fr = (TFrame*)hSensitive->FindObject("TFrame");
  TLine *line = new TLine(PrimaryEnergy,hSensitive->GetMinimum(),PrimaryEnergy,hSensitive->GetMaximum()+5000);
  line->SetLineColor(kRed); 
  line->SetLineWidth(2); 
  line->SetLineStyle(7); 
  line->Draw(""); 

  // TLine *line1 = new TLine(0.478,hSensitive->GetMinimum(),0.478,hSensitive->GetMaximum()+5000);
  // line1->SetLineColor(kBlack); 
  // line1->SetLineWidth(2); 
  // line1->SetLineStyle(2); 
  // line1->Draw(""); 

  // TLine *line2 = new TLine(2.22,hSensitive->GetMinimum(),2.22,hSensitive->GetMaximum()+5000);
  // line2->SetLineColor(kBlack); 
  // line2->SetLineWidth(2); 
  // line2->SetLineStyle(2); 
  // line2->Draw("");
  
  TLegend *legend = new TLegend(0.699375, 0.780343, 0.893667, 0.891288);
  legend->AddEntry(line, "Primary energy", "l");
  legend->AddEntry(hSensitive, "Detector", "f");
  legend->AddEntry(hBWater, "Borated water", "f");
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->Draw();

  gPad->Update();
  TPaveStats *st = (TPaveStats*)hSensitive->FindObject("stats");
  st->SetBorderSize(0);
  st->SetX1NDC(0.658718);
  st->SetY1NDC(0.743857);
  st->SetX2NDC(0.860438);
  st->SetY2NDC(0.77513);

  gPad->Update();
  gStyle->SetOptStat("e");

  TString fOutputName =  "Energy_distributions_Volumes" + to_string(PrimaryEnergy) + "MeV_BWater" + to_string(BWaterThickness) + "mm.pdf";
  c1->Update();  
  c1->SaveAs(fOutputName);
  
}
