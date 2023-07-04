void PlotAbsorbance(string fName0,string fName1, string OuputFName){//const std::string& fName

  TCanvas *c1 = new TCanvas();
  
  TGraph *gr0 = new TGraph(fName0.c_str(), "%lg %lg", "");//Pure LAB
  TGraph *gr1 = new TGraph(fName1.c_str(), "%lg %lg", "");//LAB + wax 5%

  // Here scale only if using Absorbance_curve_pureLAB.csv and Absorbance_curve_NoWash20.csv files.
  // don't scale if using the already scaled files Absorbance_curve_NoWash20_scaledClean.csv and Absorbance_curve_pureLAB_scaledClean.csv
  // gr0->Scale(4,"y");
  // gr1->Scale(4,"y");
    
  gr0->SetTitle("");
  gr0->GetXaxis()->SetTitle("Wavelength (nm)");
  gr0->GetYaxis()->SetTitle("Absorbance");
  gr0->SetLineColor(kOrange+7);
  gr0->SetLineWidth(2);
  gr0->SetMarkerStyle(20);
  gr0->SetMarkerSize(0.5);
  gr0->SetMarkerColor(gr0->GetLineColor());
  gr0->GetYaxis()->SetRangeUser(0,1.7);
  gr0->Draw("AL");

  gr1->SetLineColor(kAzure+2);
  gr1->SetLineWidth(gr0->GetLineWidth());
  gr1->SetMarkerStyle(22);
  gr1->SetMarkerSize(gr0->GetMarkerSize());
  gr1->SetMarkerColor(gr1->GetMarkerColor());
  gr1->Draw("SAME");

  // TLine *line0 = new TLine(430,0,430,gr0->GetHistogram()->GetMaximum());
  // line0->Draw("SAME");
  
  // TLine *line1 = new TLine(320,0.005,500,0.005);
  // line1->Draw("SAME");
  
  // TF1 *f0 = new TF1("f0","pol1",-50.,550.);
  // gr->Fit("f0", "0", "", -50., 550.);
  // f0->SetLineColor(gr->GetLineColor());
  // f0->Draw("SAME");

  TLegend *legend = new TLegend(0.697708, 0.776842, 0.869628, 0.858947);
  legend->AddEntry(gr0, "Pure LAB", "l");
  legend->AddEntry(gr1, "LAB + wax (5%)", "l");
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->Draw();
  
  TPad *pad = new TPad("pad","a transparent pad",0.361032, 0.56, 0.853868, 0.642105);
  pad->Draw();

  pad->cd();
  TText *text = new TText(0.0612245,0.282051,"Scaled to match 23m Abs. Length @430 nm");
  text->SetTextSize(0.410256);
  text->SetTextAlign(11);
  text->Draw();
  
  gr0->GetXaxis()->SetNdivisions(10);
  gr0->GetYaxis()->SetNdivisions(10);

  c1->SetGrid();
  c1->SaveAs(OuputFName.c_str());
  
  // delete c1;
  return 0;

}
