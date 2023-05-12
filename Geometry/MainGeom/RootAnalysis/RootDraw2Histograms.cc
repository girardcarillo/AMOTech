// RootDraw2Histograms("../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/SelectedEvents/OutputFiles/energy_deposited_AMOTech_and.root","../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/SelectedEvents/OutputFiles/energy_deposited_Armor_and.root","energy_deposited_Armor_AMOTech_and.pdf",1)

#include "TFile.h"
#include "TTree.h"

void RootDraw2Histograms(TString fName0, TString fName1, TString fOutputName, double_t PrimaryEnergy) {

  TCanvas *c1 = new TCanvas();
  
  TFile *f0 = new TFile(fName0);//AMOTech
  TFile *f1 = new TFile(fName1);//Armor

  TH1F *h0 = new TH1F();
  h0 = (TH1F*)f0->Get("h0");

  TH1F *h1 = new TH1F();
  h1 = (TH1F*)f1->Get("h1");

  // h0->SetNameTitle("h0", "");
  // if (!(h0->GetSumw2N() > 0)) h0->Sumw2(kTRUE); // ensure proper error propagation
  // h0->Add(h1, -1.0);

  h0->Rebin(2);
  h0->SetTitle("");
  h0->GetXaxis()->SetTitle("Energy (MeV)");
  h0->GetYaxis()->SetTitle("# Counts");
  
  h0->SetLineColor(kOrange+9);
  h0->SetFillStyle(3004);
  h0->SetFillColor(h0->GetLineColor());
  // h0->SetFillColorAlpha(h0->GetLineColor(),0.55);
  h0->SetLineWidth(2);

  h0->GetXaxis()->SetRangeUser(0.,4.);
  h0->Draw();
  
  h1->Rebin(2);
  
  h1->SetLineColor(kMagenta+3);
  h1->SetFillStyle(3005);
  h1->SetFillColor(h1->GetLineColor());
  // h1->SetFillColorAlpha(h1->GetLineColor(),0.55);
  h1->SetLineWidth(2);

  h1->Draw("SAME");
  
  c1->SetLogy();
  
  auto fa1 = new TF1("fa1","1",0.001,500);
  
  // TFrame *fr = (TFrame*)h0->FindObject("TFrame");
  TLine *line = new TLine(PrimaryEnergy,h0->GetMinimum(),PrimaryEnergy,h0->GetMaximum()+5000);
  line->SetLineColor(kRed); 
  line->SetLineWidth(2); 
  line->SetLineStyle(7); 
  line->Draw(""); 

  TLine *line1 = new TLine(0.478,h0->GetMinimum(),0.478,h0->GetMaximum()+5000);
  line1->SetLineColor(kBlack); 
  line1->SetLineWidth(2); 
  line1->SetLineStyle(2); 
  line1->Draw(""); 

  TLine *line2 = new TLine(2.22,h0->GetMinimum(),2.22,h0->GetMaximum()+5000);
  line2->SetLineColor(kBlack); 
  line2->SetLineWidth(2); 
  line2->SetLineStyle(2); 
  line2->Draw(""); 

  TLegend *legend = new TLegend(0.65616, 0.728421, 0.893983, 0.890526);
  legend->AddEntry(line, "Primary energy", "l");
  legend->AddEntry(h0, "AMOTech", "f");
  legend->AddEntry(h1, "Armor", "f");
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->Draw();

  gPad->Update();
  TPaveStats *st = (TPaveStats*)h0->FindObject("stats");
  st->SetBorderSize(0);
  st->SetX1NDC(0.653295);
  st->SetY1NDC(0.671579);
  st->SetX2NDC(0.858166);
  st->SetY2NDC(0.72);

  gPad->Update();
  gStyle->SetOptStat("e");

  c1->Update();  
  c1->SaveAs(fOutputName);
  
}
