void PlotEventEnergyThickness(){//const std::string& fName

  ofstream AlphaFit_Threshold_vs_Rate;

  TCanvas *c1 = new TCanvas();
  
  string fName0 = "Thickness_vs_Rate_files/RunArmor_neutrons_1MeV_Thickness_vs_Energy_or.txt";
  string fName1 = "Thickness_vs_Rate_files/RunArmor_neutrons_1MeV_Thickness_vs_Energy_and.txt";
  string fName2 = "Thickness_vs_Rate_files/RunArmor_neutrons_1MeV_Thickness_vs_Energy_ID.txt";

  // string fName1_1 = "Thickness_vs_Rate_files/RunArmor_neutrons_1MeV_Threshold200_Thickness_vs_Energy_and.txt";
  // string fName1_2 = "Thickness_vs_Rate_files/RunArmor_neutrons_1MeV_Threshold400_Thickness_vs_Energy_and.txt";
  // string fName2_1 = "Thickness_vs_Rate_files/RunArmor_neutrons_1MeV_Threshold200_Thickness_vs_Energy_ID.txt";
  // string fName2_2 = "Thickness_vs_Rate_files/RunArmor_neutrons_1MeV_Threshold400_Thickness_vs_Energy_ID.txt";

  TGraphErrors *gr0 = new TGraphErrors(fName0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *gr1 = new TGraphErrors(fName1.c_str(), "%lg %lg %lg", "");//and
  TGraphErrors *gr2 = new TGraphErrors(fName2.c_str(), "%lg %lg %lg", "");//ID

  // TGraphErrors *gr1_1 = new TGraphErrors(fName1_1.c_str(), "%lg %lg %lg", "");//and 200 eV
  // TGraphErrors *gr1_2 = new TGraphErrors(fName1_2.c_str(), "%lg %lg %lg", "");//and 400 eV
  // TGraphErrors *gr2_1 = new TGraphErrors(fName2_1.c_str(), "%lg %lg %lg", "");//ID 200 eV
  // TGraphErrors *gr2_2 = new TGraphErrors(fName2_2.c_str(), "%lg %lg %lg", "");//ID 400 eV

  // transform rate in %
  gr0->Scale(1000,"y");
  gr1->Scale(1000,"y");
  gr2->Scale(1000,"y");
  
  // gr1_1->Scale(100,"y");
  // gr1_2->Scale(100,"y");
  // gr2_1->Scale(100,"y");
  // gr2_2->Scale(100,"y");
  
  gr0->SetTitle("");
  gr0->GetXaxis()->SetTitle("Thickness (mm)");
  gr0->GetYaxis()->SetTitle("Mean deposited energy (keV)");
  gr0->SetLineColor(kGray+3);
  gr0->SetLineWidth(2);
  gr0->SetMarkerStyle(20);
  gr0->SetMarkerSize(0.5);
  gr0->SetMarkerColor(gr0->GetLineColor());
  double UpperLimitY = gr0->GetHistogram()->GetMaximum();//+gr0->GetHistogram()->GetMaximum()*0.2;
  gr0->GetYaxis()->SetRangeUser(1e2,5000);
  gr0->GetXaxis()->SetRangeUser(0.,550.);  
  gr0->Draw("ALP");
  
  gr1->SetLineColor(kMagenta+3);
  gr1->SetLineWidth(gr0->GetLineWidth());
  gr1->SetMarkerStyle(23);
  gr1->SetMarkerSize(gr0->GetMarkerSize());
  gr1->SetMarkerColor(gr1->GetLineColor());
  gr1->Draw("SAMELP");
  
  // gr1_1->SetLineColor(gr1->GetLineColor()-1);
  // gr1_1->SetLineWidth(gr0->GetLineWidth());
  // gr1_1->SetMarkerStyle(gr1->GetMarkerStyle());
  // gr1_1->SetMarkerSize(gr0->GetMarkerSize());
  // gr1_1->SetMarkerColor(gr1_1->GetLineColor());
  // gr1_1->Draw("SAMEP");
  
  // gr1_2->SetLineColor(gr1->GetLineColor()-2);
  // gr1_2->SetLineWidth(gr0->GetLineWidth());
  // gr1_2->SetMarkerStyle(gr1->GetMarkerStyle());
  // gr1_2->SetMarkerSize(gr0->GetMarkerSize());
  // gr1_2->SetMarkerColor(gr1_2->GetLineColor());
  // gr1_2->Draw("SAMEP");
  
  gr2->SetLineColor(kRed+3);
  gr2->SetLineWidth(gr0->GetLineWidth());
  gr2->SetMarkerStyle(22);
  gr2->SetMarkerSize(gr0->GetMarkerSize());
  gr2->SetMarkerColor(gr2->GetLineColor());
  gr2->Draw("SAMELP");
  
  // gr2_1->SetLineColor(gr2->GetLineColor()-1);
  // gr2_1->SetLineWidth(gr0->GetLineWidth());
  // gr2_1->SetMarkerStyle(gr2->GetMarkerStyle());
  // gr2_1->SetMarkerSize(gr0->GetMarkerSize());
  // gr2_1->SetMarkerColor(gr2_1->GetLineColor());
  // gr2_1->Draw("SAMEP");
  
  // gr2_2->SetLineColor(gr2->GetLineColor()-2);
  // gr2_2->SetLineWidth(gr0->GetLineWidth());
  // gr2_2->SetMarkerStyle(gr2->GetMarkerStyle());
  // gr2_2->SetMarkerSize(gr0->GetMarkerSize());
  // gr2_2->SetMarkerColor(gr2_2->GetLineColor());
  // gr2_2->Draw("SAMEP");
  
  TF1 *f0 = new TF1("f0","pol1",-50.,550.);
  gr0->Fit("f0", "0", "", -50., 550.);
  f0->SetLineColor(gr0->GetLineColor());
  // f0->Draw("SAME");

  TF1 *f1 = new TF1("f1","pol1",-50.,550.);
  gr1->Fit("f1", "0", "", 0., 500.);
  f1->SetLineColor(gr1->GetLineColor());
  // f1->Draw("SAME");

  TF1 *f2 = new TF1("f2","pol1",-50.,550.);
  gr2->Fit("f2", "0", "", 0., 500.);
  f2->SetLineColor(gr2->GetLineColor());
  // f2->Draw("SAME");

  TLegend *legend = new TLegend(0.540115, 0.772632, 0.872493, 0.871579); // linear scale
  legend->AddEntry(gr0, TString::Format("All events #rightarrow #chi^{2}/ndf = %1.3g", f0->GetChisquare()/f0->GetNDF()), "pe");
  legend->AddEntry(gr1, TString::Format("AMOTech + Armor events #rightarrow  #chi^{2}/ndf = %1.3g", f1->GetChisquare()/f1->GetNDF()), "pe");
  legend->AddEntry(gr2, TString::Format("AMOTech only events #rightarrow  #chi^{2}/ndf = %1.3g", f2->GetChisquare()/f2->GetNDF()), "pe");
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->Draw();
  
  c1->SetLogy();

  // gr0->GetXaxis()->SetNdivisions(7);
  
  c1->SaveAs("Thickness_Energy.pdf");
  
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
