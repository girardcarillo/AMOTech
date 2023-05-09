void PlotEventRate(){//const std::string& fName

  ofstream AlphaFit_Threshold_vs_Rate;

  TCanvas *c1 = new TCanvas();
  
  // string fName0 = "RunArmor_neutrons_1MeV_BWater100_Threshold_vs_Rate_ID.txt";
  // string fName1 = "RunArmor_neutrons_1MeV_BWater200_Threshold_vs_Rate_ID.txt";
  // string fName2 = "RunArmor_neutrons_1MeV_BWater300_Threshold_vs_Rate_ID.txt";
  // string fName3 = "RunArmor_neutrons_1MeV_BWater400_Threshold_vs_Rate_ID.txt";
  
  string fName0 = "EventSelection/Threshold_vs_Rate_files/RunArmor_neutrons_1MeV_BWater100_Threshold_vs_Rate_and.txt";
  string fName1 = "EventSelection/Threshold_vs_Rate_files/RunArmor_neutrons_1MeV_BWater200_Threshold_vs_Rate_and.txt";
  string fName2 = "EventSelection/Threshold_vs_Rate_files/RunArmor_neutrons_1MeV_BWater300_Threshold_vs_Rate_and.txt";
  string fName3 = "EventSelection/Threshold_vs_Rate_files/RunArmor_neutrons_1MeV_BWater400_Threshold_vs_Rate_and.txt";

  TGraphErrors *gr0 = new TGraphErrors(fName0.c_str(), "%lg %lg %lg", "");//ID 100mm BWater
  TGraphErrors *gr1 = new TGraphErrors(fName1.c_str(), "%lg %lg %lg", "");//ID 200mm BWater
  TGraphErrors *gr2 = new TGraphErrors(fName2.c_str(), "%lg %lg %lg", "");//ID 300mm BWater
  TGraphErrors *gr3 = new TGraphErrors(fName3.c_str(), "%lg %lg %lg", "");//ID 400mm BWater

  // transform rate in %
  gr0->Scale(100,"y");
  gr1->Scale(100,"y");
  gr2->Scale(100,"y");
  gr3->Scale(100,"y");
  
  gr0->SetTitle("");
  gr0->GetXaxis()->SetTitle("Detection threshold (keV)");
  gr0->GetYaxis()->SetTitle("Tagging efficiency (%)");
  gr0->SetLineColor(kCyan+1);
  gr0->SetLineWidth(2);
  gr0->SetMarkerStyle(20);
  gr0->SetMarkerSize(0.5);
  gr0->SetMarkerColor(gr0->GetLineColor());
  double UpperLimitY = gr0->GetHistogram()->GetMaximum();//+gr0->GetHistogram()->GetMaximum()*0.2;
  gr0->GetYaxis()->SetRangeUser(1e-2,UpperLimitY);
  gr0->GetXaxis()->SetRangeUser(0.,550.);  
  gr0->Draw("AP");
  
  gr1->SetLineColor(gr0->GetLineColor()+1);
  gr1->SetLineWidth(gr0->GetLineWidth());
  gr1->SetMarkerStyle(gr0->GetMarkerStyle()+1);
  gr1->SetMarkerSize(gr0->GetMarkerSize());
  gr1->SetMarkerColor(gr1->GetLineColor());
  gr1->Draw("SAMEP");
  
  gr2->SetLineColor(gr0->GetLineColor()+2);
  gr2->SetLineWidth(gr0->GetLineWidth());
  gr2->SetMarkerStyle(gr0->GetMarkerStyle()+2);
  gr2->SetMarkerSize(gr0->GetMarkerSize());
  gr2->SetMarkerColor(gr2->GetLineColor());
  gr2->Draw("SAMEP");
  
  gr3->SetLineColor(gr0->GetLineColor()+3);
  gr3->SetLineWidth(gr0->GetLineWidth());
  gr3->SetMarkerStyle(gr0->GetMarkerStyle()+3);
  gr3->SetMarkerSize(gr0->GetMarkerSize());
  gr3->SetMarkerColor(gr3->GetLineColor());
  gr3->Draw("SAMEP");
  
  TF1 *f0 = new TF1("f0","pol1",-50.,550.);
  gr0->Fit("f0", "0", "", -50., 550.);
  f0->SetLineColor(gr0->GetLineColor());
  f0->Draw("SAME");

  TF1 *f1 = new TF1("f1","pol1",-50.,550.);
  gr1->Fit("f1", "0", "", 0., 500.);
  f1->SetLineColor(gr1->GetLineColor());
  f1->Draw("SAME");

  TF1 *f2 = new TF1("f2","pol1",-50.,550.);
  gr2->Fit("f2", "0", "", 0., 500.);
  f2->SetLineColor(gr2->GetLineColor());
  f2->Draw("SAME");

  TF1 *f3 = new TF1("f3","pol1",-50.,550.);
  gr3->Fit("f3", "0", "", 0., 500.);
  f3->SetLineColor(gr3->GetLineColor());
  f3->Draw("SAME");

  // TLegend *legend = new TLegend(0.121777, 0.157895, 0.409742, 0.362105); // log scale
  TLegend *legend = new TLegend(0.54298, 0.637895, 0.889685, 0.877895); // linear scale
  legend->SetHeader("Borated water layer thickness ");
  legend->AddEntry(gr0, TString::Format("100mm #rightarrow #chi^{2}/ndf = %1.3g", f0->GetChisquare()/f0->GetNDF()), "pe");
  legend->AddEntry(gr1, TString::Format("200mm #rightarrow  #chi^{2}/ndf = %1.3g", f1->GetChisquare()/f1->GetNDF()), "pe");
  legend->AddEntry(gr2, TString::Format("300mm #rightarrow  #chi^{2}/ndf = %1.3g", f2->GetChisquare()/f2->GetNDF()), "pe");
  legend->AddEntry(gr3, TString::Format("400mm #rightarrow  #chi^{2}/ndf = %1.3g", f3->GetChisquare()/f3->GetNDF()), "pe");
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->Draw();
  
  c1->SetLogy();

  // gr0->GetXaxis()->SetNdivisions(7);
  
  c1->SaveAs("SelectionRates/SelectionRates_Threshold.pdf");
  
  AlphaFit_Threshold_vs_Rate.open("AlphaFit_Threshold_vs_Rate.txt");
  if (AlphaFit_Threshold_vs_Rate.is_open()){
    AlphaFit_Threshold_vs_Rate << "100 " << f0->GetParameter(1) << " " << f0->GetParError(1) << "\n"; 
    AlphaFit_Threshold_vs_Rate << "200 " << f1->GetParameter(1) << " " << f1->GetParError(1) << "\n"; 
    AlphaFit_Threshold_vs_Rate << "300 " << f2->GetParameter(1) << " " << f2->GetParError(1) << "\n"; 
    AlphaFit_Threshold_vs_Rate << "400 " << f3->GetParameter(1) << " " << f3->GetParError(1) << "\n"; 
  }
  else {
    cout << "File Threshold_vs_Rate did not open!" << endl;
    return 6;
  }      
  AlphaFit_Threshold_vs_Rate.close();

  
  delete c1;
  return 0;

}
