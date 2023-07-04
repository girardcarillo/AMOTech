// RootDraw2Histograms("../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/SelectedEvents/OutputFiles/energy_deposited_AMOTech_and.root","../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/SelectedEvents/OutputFiles/energy_deposited_Armor_and.root","energy_deposited_Armor_AMOTech_and.pdf",1)

#include "TFile.h"
#include "TTree.h"

void RootDrawInteractionDepth(int BWaterThickness, double PrimaryEnergy, string particleType, TString whichPlot, string bore = "") {

  
  stringstream stream;
  if (particleType == "gamma") stream << fixed << setprecision(1) << PrimaryEnergy;
  else if (particleType == "neutron") stream << fixed << setprecision(0) << PrimaryEnergy;
  string senergy = stream.str();

  string swhichPlot = whichPlot.Data();
  
  // tmp pour neutrons thermal
  if (PrimaryEnergy < 1. && particleType == "neutron") senergy = "2.5e-08";
  
  // TString path = "/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/EventSelection/RootFiles_SelectedEvents/" + particleType + "/Simus_" + particleType + "_" + senergy + "MeV_" + bore + "Water" + to_string(BWaterThickness) + "mm_Threshold0keV_EnergyDeposited";

  // tests tmp directory
  TString path = "/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/EventSelection/RootFiles_SelectedEvents/tmp/Simus_" + particleType + "_" + senergy + "MeV_" + bore + "Water" + to_string(BWaterThickness) + "mm_Threshold0keV_EnergyDeposited";

  // tests with SelectOneEvent
  // TString path = "/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/EventSelection/test_hits.root";

  // tmp for thermal
  // TString path = "/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/EventSelection/RootFiles_SelectedEvents/Simus_neutron_2.5e-08MeV_"+bore+"Water"+to_string(BWaterThickness)+"mm_Threshold0keV_EnergyDeposited";
  
  TFile *f0 = new TFile(path + "_" + whichPlot + "_or.root");

  // tests with SelectOneEvent
  // TFile *f0 = new TFile(path);
  
  TH2F *h2Depth = new TH2F();
  
  if (whichPlot == "Depth") {
    h2Depth = (TH2F*)f0->Get("h2_Depth");
  }
  else if (whichPlot == "DepthFirstHit") {
    h2Depth = (TH2F*)f0->Get("h2_DepthFirstHit");
  }
  else if (whichPlot == "DepthEnergyFirstHit") {
    h2Depth = (TH2F*)f0->Get("h2_DepthEnergyFirstHit");
  }
  else if (whichPlot == "DepthEnergy") {
    h2Depth = (TH2F*)f0->Get("h2_DepthEnergy");
  }

  TString title =  senergy + "MeV " + particleType + " " + to_string(BWaterThickness) + "mm " + bore + "Water " + "Interaction" + swhichPlot;
  TString fOutputName =  "Interaction" + swhichPlot + "Pdf/" + particleType + "/Interaction" + swhichPlot + "_" + particleType + "_" + senergy + "MeV_" + bore + "Water" + to_string(BWaterThickness) + "mm.pdf";

  gStyle->SetPalette(kViridis);
    
  if (whichPlot == "Depth" || whichPlot == "DepthFirstHit") {
  
    TCanvas *c1 = new TCanvas("c1", "",5,77,1244,1358);
    gStyle->SetOptStat(0);
    // gPad->SetLogz();
    c1->Range(-2819.71,-3316.51,3515.362,3811.163);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetLogz();
    c1->SetLeftMargin(0.1925329);
    c1->SetRightMargin(0.3023426);
    c1->SetFrameBorderMode(0);
    c1->SetFrameBorderMode(0);
    
    h2Depth->GetXaxis()->SetNdivisions(5);
    h2Depth->GetYaxis()->SetNdivisions(7);

    h2Depth->Draw("colz");
    h2Depth->SetTitle(title);  
    h2Depth->Rebin2D(4);
    h2Depth->GetXaxis()->SetTitle("x (mm)");
    h2Depth->GetYaxis()->SetTitle("z (mm)");

    h2Depth->GetXaxis()->SetRangeUser(-1600,1600);
    h2Depth->GetYaxis()->SetRangeUser(-2600,3100);
  
    // h2Depth->GetXaxis()->SetRangeUser(-2600,3100);

    // if (particleType == "gamma") {
    //   if (whichPlot == "Depth") {
    //     h2Depth->GetZaxis()->SetRangeUser(1,2.5e5);
    //   }
    //   else if (whichPlot == "DepthFirstHit") {
    //     h2Depth->GetZaxis()->SetRangeUser(1,1.5e2);
    //   }
    //   else if (whichPlot == "DepthEnergyFirstHit") {
    //     h2Depth->GetZaxis()->SetRangeUser(1,1.5e5);
    //   }
    //   else if (whichPlot == "DepthEnergy") {
    //     h2Depth->GetZaxis()->SetRangeUser(1,2.5e8);
    //   }
    // }
    // else {
    //   if (whichPlot == "Depth") {
    //     h2Depth = (TH2F*)f0->Get("h2_Depth");
    //   }
    //   else if (whichPlot == "DepthFirstHit") {
    //     h2Depth = (TH2F*)f0->Get("h2_DepthFirstHit");
    //   }
    //   else if (whichPlot == "DepthEnergyFirstHit") {
    //     h2Depth = (TH2F*)f0->Get("h2_DepthEnergyFirstHit");
    //   }
    //   else if (whichPlot == "DepthEnergy") {
    //     h2Depth = (TH2F*)f0->Get("h2_DepthEnergy");
    //   }
    // }
  
    // TGaxis::SetMaxDigits(3);

    TBox *Water = new TBox(-1500,2500+BWaterThickness,1500,2500);
    Water->SetFillStyle(0);
    Water->SetLineColor(1);
    Water->SetLineWidth(2);
    Water->Draw();

    TBox *Sensitive = new TBox(-1500,2500,1500,-2500);
    Sensitive->SetFillStyle(0);
    Sensitive->SetLineColor(1);
    Sensitive->SetLineWidth(2);
    Sensitive->Draw();
      
    TLine *line = new TLine(-1500,2000,1500,2000);
    line->SetLineColor(kRed); 
    line->SetLineWidth(2); 
    line->SetLineStyle(7); 
    line->Draw();
    
    c1->SaveAs(fOutputName);

  }

  else if (whichPlot == "DepthEnergy" || whichPlot == "DepthEnergyFirstHit") {

    TCanvas *c2 = new TCanvas("c2", "",10,77,1932,1358);
    gStyle->SetOptStat(0);
    c2->Range(2054.75,-0.06475,2707.25,0.58275);
    c2->SetFillColor(0);
    c2->SetBorderMode(0);
    c2->SetBorderSize(2);
    c2->SetFrameBorderMode(0);
    c2->SetFrameBorderMode(0);
    c2->SetLogz();
    
    h2Depth->GetXaxis()->SetNdivisions(7);
    h2Depth->GetYaxis()->SetNdivisions(25);

    h2Depth->Draw("colz");
    h2Depth->SetTitle(title);  
    h2Depth->Rebin2D(4);
    h2Depth->GetXaxis()->SetTitle("z (mm)");
    h2Depth->GetYaxis()->SetTitle("Deposited energy (MeV)");

    h2Depth->GetXaxis()->SetRangeUser(1000,3100);
    
    // h2Depth->GetXaxis()->SetRangeUser(-2600,3100);

    // if (particleType == "gamma") {
    //   if (whichPlot == "Depth") {
    //     h2Depth->GetZaxis()->SetRangeUser(1,2.5e5);
    //   }
    //   else if (whichPlot == "DepthFirstHit") {
    //     h2Depth->GetZaxis()->SetRangeUser(1,1.5e2);
    //   }
    //   else if (whichPlot == "DepthEnergyFirstHit") {
    //     h2Depth->GetZaxis()->SetRangeUser(1,1.5e5);
    //   }
    //   else if (whichPlot == "DepthEnergy") {
    //     h2Depth->GetZaxis()->SetRangeUser(1,2.5e8);
    //   }
    // }

    if (particleType == "neutron") {
      if (whichPlot == "DepthEnergy") {
	// h2Depth->GetZaxis()->SetRangeUser(1,4e5);
	if (PrimaryEnergy == 20) {
	  h2Depth->GetYaxis()->SetRangeUser(0,6);
	}
 	else if (PrimaryEnergy == 1) {
	  h2Depth->GetYaxis()->SetRangeUser(0,2);
	}
	else if (PrimaryEnergy == 100) {
	  h2Depth->GetYaxis()->SetRangeUser(0,8);
	}
      }
      else if (whichPlot == "DepthEnergyFirstHit") {
	// h2Depth->GetZaxis()->SetRangeUser(1,1.5e5);
	if (PrimaryEnergy == 20) {
	  h2Depth->GetYaxis()->SetRangeUser(0,6);
	}
 	else if (PrimaryEnergy == 1) {
	  h2Depth->GetYaxis()->SetRangeUser(0,0.5);
	}
	else if (PrimaryEnergy == 100) {
	  h2Depth->GetYaxis()->SetRangeUser(0,7);
	}
      }
    }

  
    // TGaxis::SetMaxDigits(3);

    TLine *line = new TLine(2000,0,2000,0.5);
    line->SetLineColor(kRed); 
    line->SetLineWidth(2); 
    line->SetLineStyle(7); 
    line->Draw();

    TLine *line2 = new TLine(2500,0,2500,0.5);
    line2->SetLineWidth(2); 
    line2->Draw();

    TLine *line3 = new TLine(2500+BWaterThickness,0,2500+BWaterThickness,0.5);
    line3->SetLineWidth(2); 
    line3->Draw();

    
    
  }


}

