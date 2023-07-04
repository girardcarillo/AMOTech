void PlotMeanEnergyThickness(){//const std::string& fName

  ofstream AlphaFit_Threshold_vs_Rate;

  TCanvas *c1 = new TCanvas();

  string path_to_files = "../EventSelection/TxtFiles_Thickness_vs_MeanSensitiveEnergy/" ;
  
  string fName0 = path_to_files+"Thickness_vs_MeanSensitiveEnergy_1MeV.txt";
  string fName1 = path_to_files+"Thickness_vs_MeanSensitiveEnergy_20MeV.txt";
  string fName2 = path_to_files+"Thickness_vs_MeanSensitiveEnergy_100MeV.txt";
  
  TGraph *gr0 = new TGraph(fName0.c_str(), "%lg %lg", "");//or 
  TGraph *gr1 = new TGraph(fName1.c_str(), "%lg %lg", "");//and
  TGraph *gr2 = new TGraph(fName2.c_str(), "%lg %lg", "");//ID

  gr0->SetTitle("");
  gr0->GetXaxis()->SetTitle("Thickness (mm)");
  gr0->GetYaxis()->SetTitle("Mean Energy deposited in sensitive volume (MeV)");
  gr0->SetLineColor(kOrange+7);
  gr0->SetLineWidth(2);
  gr0->SetMarkerStyle(20);
  gr0->SetMarkerSize(0.8);
  gr0->SetMarkerColor(gr0->GetLineColor());
  double UpperLimitY = gr0->GetHistogram()->GetMaximum();//+gr0->GetHistogram()->GetMaximum()*0.2;
  gr0->GetYaxis()->SetRangeUser(1e-1,100);
  gr0->GetXaxis()->SetRangeUser(0.,550.);
  gr0->Draw("ALP");
  
  gr1->SetLineColor(kAzure+2);
  gr1->SetLineWidth(gr0->GetLineWidth());
  gr1->SetMarkerStyle(23);
  gr1->SetMarkerSize(gr0->GetMarkerSize());
  gr1->SetMarkerColor(gr1->GetLineColor());
  gr1->Draw("SAMELP");
    
  gr2->SetLineColor(kPink+8);
  gr2->SetLineWidth(gr0->GetLineWidth());
  gr2->SetMarkerStyle(22);
  gr2->SetMarkerSize(gr0->GetMarkerSize());
  gr2->SetMarkerColor(gr2->GetLineColor());
  gr2->Draw("SAMELP");
  
  // TF1 *f0 = new TF1("f0","pol1",0.,550.);
  // gr0->Fit("f0", "0", "", 100., 500.);
  // f0->SetLineColor(gr0->GetLineColor());
  // f0->SetLineStyle(1);
  // f0->Draw("SAME");
  
  // TF1 *f1 = new TF1("f1","pol1",0.,550.);
  // gr1->Fit("f1", "0", "", 100., 500.);
  // f1->SetLineColor(gr1->GetLineColor());
  // f1->SetLineStyle(7);
  // f1->Draw("SAME");
  
  // TF1 *f2 = new TF1("f2","pol1",-0,550.);
  // gr2->Fit("f2", "0", "", 100., 500.);
  // f2->SetLineColor(gr2->GetLineColor());
  // f2->SetLineStyle(2);
  // f2->Draw("SAME");

  // cout << exp(f0->GetParameter(0)) << " " << -f0->GetParameter(1) << endl;
  // cout << exp(f1->GetParameter(0)) << " " << -f1->GetParameter(1) << endl;
  // cout << exp(f2->GetParameter(0)) << " " << -f2->GetParameter(1) << endl;

  TLegend *legend = new TLegend(0.550143, 0.204211, 0.878223, 0.336842); // linear scale
  // legend->AddEntry((TObject*)0, "All events","");
  // legend->AddEntry(gr0, TString::Format("1 MeV neutrons #rightarrow #chi^{2}/ndf = %1.3g", f0->GetChisquare()/f0->GetNDF()), "pe");
  // legend->AddEntry(gr1, TString::Format("20 MeV neutrons #rightarrow  #chi^{2}/ndf = %1.3g", f1->GetChisquare()/f1->GetNDF()), "pe");
  // legend->AddEntry(gr2, TString::Format("100 MeV neutrons #rightarrow  #chi^{2}/ndf = %1.3g", f2->GetChisquare()/f2->GetNDF()), "pe");
  legend->AddEntry(gr0, "1 MeV generated neutrons", "pe");
  legend->AddEntry(gr1, "20 MeV generated neutrons", "pe");
  legend->AddEntry(gr2, "100 MeV generated neutrons", "pe");
  legend->SetBorderSize(1);
  legend->SetLineColor(kGray);
  legend->SetFillColor(0);
  legend->Draw();

  c1->SetLogy();
  
  TGaxis::SetMaxDigits(3);
  gr0->GetXaxis()->SetNdivisions(7);
  // gr0->GetYaxis()->SetNdivisions(5);
  c1->SetGrid();  
  
  c1->SaveAs("MeanSensitiveEnergyvsThickness/MeanSensitiveEnergy_Thickness.pdf");
  
  // AlphaFit_Threshold_vs_Rate.open("AlphaFit_Threshold_vs_Rate.txt");
  // if (AlphaFit_Threshold_vs_Rate.is_open()){
  //   AlphaFit_Threshold_vs_Rate << "100 " << f0->GetParameter(1) << " " << f0->GetParError(1) << "\n"; 
  //   AlphaFit_Threshold_vs_Rate << "200 " << f1->GetParameter(1) << " " << f1->GetParError(1) << "\n"; 
  //   AlphaFit_Threshold_vs_Rate << "300 " << f2->GetParameter(1) << " " << f2->GetParError(1) << "\n"; 
  //   AlphaFit_Threshold_vs_Rate << "400 " << f3->GetParameter(1) << " " << f3->GetParError(1) << "\n"; 
  // }
  // else {
  //   cout << "File Threshold_vs_Rate did not open!" << endl;
  //   return 6;
  // }      
  // AlphaFit_Threshold_vs_Rate.close();

  // delete c1;
  return 0;

}
