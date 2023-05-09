// RootDrawHistograms("../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/SelectedEvents/OutputFiles/energy_deposited_AMOTech_ID.root")

#include "TFile.h"
#include "TTree.h"

void RootDrawHistograms(string fName){//const std::string& fName
  
  TCanvas *c1 = new TCanvas();

  TFile *f1 = new TFile(fName.c_str());
  
  if(f1->IsOpen()){

    TH1F *h1 = new TH1F();
    int color = 1;//kBlack
    int hatching = 0;
    
    if (fName.find("AMOTech") != string::npos) {
      h1 = (TH1F*)f1->Get("h0");//h1->GetName() // AMOTech
      // color=432+3;
      color=800+9;//kOrange+9
      hatching=3004;
    }
    else if (fName.find("Armor") != string::npos) {
      h1 = (TH1F*)f1->Get("h1");//h1->GetName() // AMOTech
      // color=800+9;
      color=616+3;//kMagenta+3
      hatching=3005;
    }
    else{
      cout << "No corresponding histogram name!" << endl;
      return 6;
    }

    // h1 = (TH1F*)f1->Get("h1");//h1->GetName() // Armor

    h1->SetFillStyle(hatching);
    h1->SetFillColor(h1->GetLineColor());

    
    h1->Rebin(2);
    h1->SetTitle("");
    h1->GetXaxis()->SetTitle("Energy (MeV)");
    h1->GetYaxis()->SetTitle("# Counts");
  
    h1->SetLineColor(color);
    h1->SetFillColorAlpha(h1->GetLineColor(),0.55);
    h1->SetLineWidth(2);

    h1->Draw();
    c1->SetLogy();
    h1->GetXaxis()->SetRangeUser(0.,4.);

    TLine *line1 = new TLine(0.477,h1->GetMinimum(),0.477,h1->GetMaximum()+300);
    line1->SetLineColor(kBlack); 
    line1->SetLineWidth(2); 
    line1->SetLineStyle(2); 
    line1->Draw(""); 

    TLine *line2 = new TLine(2.22,h1->GetMinimum(),2.22,h1->GetMaximum()+300);
    line2->SetLineColor(kBlack); 
    line2->SetLineWidth(2); 
    line2->SetLineStyle(2); 
    line2->Draw(""); 

    gPad->Update();
    TPaveStats *st = (TPaveStats*)h1->FindObject("stats");
    st->SetBorderSize(0);
    st->SetX1NDC(0.686246);
    st->SetY1NDC(0.831579);
    st->SetX2NDC(0.891117);
    st->SetY2NDC(0.873684);

    gPad->Update();
    gStyle->SetOptStat("e");
  
    c1->Update();
    c1->SaveAs("energy_deposited_AMOTech_ID.pdf");
  }
  else{
    cout << "The file did not open!" << endl;
    return 6;
  }
    
  return 0;
}
