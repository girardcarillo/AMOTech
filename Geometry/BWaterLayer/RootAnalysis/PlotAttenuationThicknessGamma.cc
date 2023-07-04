void PlotAttenuationThicknessGamma(){//const std::string& fName

  string path_to_filesAttenuation = "../EventSelection/TxtFiles_Thickness_vs_Attenuation/" ;
  
  string fNameParticle0 = path_to_filesAttenuation+"Thickness_vs_AttenuationGamma_WaterOnly_2.6MeV.txt";
  string fNameParticle1 = path_to_filesAttenuation+"Thickness_vs_AttenuationGamma_WaterOnly_7.6MeV.txt";
  
  TGraphErrors *grParticle0 = new TGraphErrors(fNameParticle0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *grParticle1 = new TGraphErrors(fNameParticle1.c_str(), "%lg %lg %lg", "");//and
  
  TCanvas *c1 = new TCanvas("c1","",2560,1368);

  // transform rate in %
  grParticle0->Scale(100,"y");
  grParticle1->Scale(100,"y");
  
  TGaxis::SetMaxDigits(3);
  
  gPad->SetGrid();

  grParticle0->GetXaxis()->SetNdivisions(7);
  grParticle0->GetYaxis()->SetNdivisions(7);

  grParticle0->SetTitle("");
  grParticle0->GetXaxis()->SetTitle("Thickness (mm)");
  grParticle0->GetYaxis()->SetTitle("Attenuation (%)");
  double LowerLimitX = 70.;
  double UpperLimitX = 550.;
  double LowerLimitY = 1.;
  double UpperLimitY = 110.;
  grParticle0->GetYaxis()->SetRangeUser(LowerLimitY,UpperLimitY);
  grParticle0->GetXaxis()->SetRangeUser(LowerLimitX,UpperLimitX);

  grParticle0->SetLineColor(kOrange-3);
  grParticle0->SetLineWidth(1);
  grParticle0->SetLineStyle(1);
  grParticle0->SetMarkerStyle(20);
  grParticle0->SetMarkerSize(2);
  grParticle0->SetMarkerColor(grParticle0->GetLineColor());
  grParticle0->Draw("ALP");
  
  grParticle1->SetLineColor(kAzure+5);
  grParticle1->SetLineWidth(grParticle0->GetLineWidth());
  grParticle1->SetLineStyle(grParticle0->GetLineStyle());
  grParticle1->SetMarkerStyle(23);
  grParticle1->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticle1->SetMarkerColor(grParticle1->GetLineColor());
  grParticle1->Draw("SAMELP");

  TLegend *legend = new TLegend(0.784929, 0.800447, 0.890502, 0.881608); // linear scale
  legend->AddEntry(grParticle0, "2.6 MeV", "l");
  legend->AddEntry(grParticle1, "7.6 MeV", "l");
  
  legend->SetBorderSize(1);
  legend->SetLineColor(kBlack);
  legend->SetFillColor(0);
  legend->Draw();


  c1->SaveAs("AttenuationvsThickness/Attenuation_Thickness_Gammas.pdf");
  
  // delete c1;
  return 0;

}
