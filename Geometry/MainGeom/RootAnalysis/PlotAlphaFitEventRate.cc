void PlotAlphaFitEventRate(){//const std::string& fName

  TCanvas *c1 = new TCanvas();
  TGaxis::SetMaxDigits(3);
  
  string fName0 = "AlphaFit_Threshold_vs_Rate.txt";
    
  TGraphErrors *gr0 = new TGraphErrors(fName0.c_str(), "%lg %lg %lg", "");//ID 100mm BWater
  
  gr0->SetTitle("");
  gr0->GetXaxis()->SetTitle("Thickness (mm)");
  gr0->GetYaxis()->SetTitle("Attenuation");
  gr0->SetLineColor(kMagenta+3);
  gr0->SetLineWidth(2);
  gr0->SetMarkerStyle(20);
  gr0->SetMarkerSize(0.5);
  // gr0->SetLineStyle(7);
  gr0->SetMarkerColor(gr0->GetLineColor());
  // gr0->GetYaxis()->SetRangeUser(0,0.0015);
  // gr0->GetXaxis()->SetRangeUser(0,1000.);

  gr0->GetXaxis()->SetNdivisions(5);
  gr0->GetYaxis()->SetNdivisions(10);

  gr0->Draw("AP");
  
  // TF1 *f0 = new TF1("f0","pol1",100.,400.);
  TF1 *f0 = new TF1("f0","pol2",0.,500.);
  gr0->Fit("f0", "0", "", 100., 400.);
  f0->SetLineColor(gr0->GetLineColor()-1);
  f0->Draw("SAME");

  c1->SetGrid(2,2);
  c1->Update();

  TLegend *legend = new TLegend(0.217765, 0.692632, 0.47851, 0.837895);
  legend->AddEntry(f0, "Fit", "l");
  legend->AddEntry((TObject*)0, TString::Format("#chi^{2}/ndf = %1.3g", f0->GetChisquare()/f0->GetNDF()), "");
  // legend->AddEntry((TObject*)0, TString::Format("#alpha = %1.2e", f0->GetParameter(1)), "");
  // legend->AddEntry((TObject*)0, TString::Format("#beta = %1.2e", f0->GetParameter(2)), "");
  legend->Draw();
  
  // c1->SetLogy();
  
  c1->SaveAs("AlphaFitSelectionRate.pdf");
  
  // delete c1;
  return 0;

}
