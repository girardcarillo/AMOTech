void PlotAttenuationThicknessGamma(bool RealFlux = 0){//const std::string& fName

  double NeutronGammaBq_Tl = 4.25e5/1e3; // with 25 Bq/kg, normalized to have kHz
    
  string path_to_filesAttenuation = "../EventSelection/TxtFiles_Thickness_vs_AttenuationGenerator/Gamma/" ;
  
  string fNameParticle0 = path_to_filesAttenuation+"Thickness_vs_AttenuationGenerator_WaterOnly_2.6MeV.txt";
  string fNameParticle1 = path_to_filesAttenuation+"Thickness_vs_AttenuationGenerator_WaterOnly_7.6MeV.txt";
  
  TGraphErrors *grParticle0 = new TGraphErrors(fNameParticle0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *grParticle1 = new TGraphErrors(fNameParticle1.c_str(), "%lg %lg %lg", "");//and
  
  TCanvas *c1 = new TCanvas("c1","",2560,1368);

  
  TGaxis::SetMaxDigits(3);

  
  // ----- general settings canvas
  
  gPad->SetGrid();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  grParticle0->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grParticle0->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  grParticle0->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  grParticle0->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  grParticle0->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grParticle0->GetXaxis()->SetLabelSize(0.05);
  grParticle0->GetXaxis()->SetLabelFont(42);
  grParticle0->GetXaxis()->SetTitleOffset(1.05);
  grParticle0->GetXaxis()->CenterTitle(1);
  grParticle0->GetXaxis()->SetTickLength(0.02);
  grParticle0->GetXaxis()->SetTitleSize(0.05);
  grParticle0->GetXaxis()->SetTitleFont(42);
  grParticle0->GetXaxis()->SetNdivisions(7);
  
  grParticle0->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  grParticle0->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  grParticle0->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grParticle0->GetYaxis()->SetLabelSize(0.05);
  grParticle0->GetYaxis()->SetLabelFont(42);
  grParticle0->GetYaxis()->SetTitleOffset(0.9);
  grParticle0->GetYaxis()->CenterTitle(1);
  grParticle0->GetYaxis()->SetTickLength(0.02);
  grParticle0->GetYaxis()->SetTitleSize(0.05);
  grParticle0->GetYaxis()->SetTitleFont(42);
  grParticle0->GetYaxis()->SetNdivisions(7);

  // -----------------------------

  grParticle0->SetTitle("");
  grParticle0->GetXaxis()->SetTitle("Thickness (mm)");

  grParticle0->SetLineColor(kCyan+1);
  grParticle0->SetLineWidth(1);
  grParticle0->SetLineStyle(1);
  grParticle0->SetMarkerStyle(20);
  grParticle0->SetMarkerSize(2);
  grParticle0->SetMarkerColor(grParticle0->GetLineColor());

  if (RealFlux){

    // double LowerLimitX = 70.;
    // double UpperLimitX = 550.;
    // double LowerLimitY = 1.;
    // double UpperLimitY = 110.;
    // grParticle0->GetYaxis()->SetRangeUser(LowerLimitY,UpperLimitY);
    // grParticle0->GetXaxis()->SetRangeUser(LowerLimitX,UpperLimitX);
    
    for ( int i = 0; i<grParticle0->GetN(); i++) {
      grParticle0->SetPointY(i,1-grParticle0->GetPointY(i));
    }

    grParticle0->GetYaxis()->SetTitle("# survival particles (kHz)");

    grParticle0->Scale(NeutronGammaBq_Tl,"y");

    grParticle0->GetYaxis()->SetRangeUser(0,500);
    
    grParticle0->Draw("ALP");

  }

  else {
    
    // transform rate in %
    grParticle0->Scale(100,"y");
    grParticle1->Scale(100,"y");
    
    double LowerLimitX = 70.;
    double UpperLimitX = 550.;
    double LowerLimitY = 1.;
    double UpperLimitY = 110.;
    grParticle0->GetYaxis()->SetRangeUser(LowerLimitY,UpperLimitY);
    grParticle0->GetXaxis()->SetRangeUser(LowerLimitX,UpperLimitX);

    grParticle0->GetYaxis()->SetTitle("Attenuation (%)");
  
    grParticle0->Draw("ALP");
  
    grParticle1->SetLineColor(kCyan+3);
    grParticle1->SetLineWidth(grParticle0->GetLineWidth());
    grParticle1->SetLineStyle(grParticle0->GetLineStyle());
    grParticle1->SetMarkerStyle(23);
    grParticle1->SetMarkerSize(grParticle0->GetMarkerSize());
    grParticle1->SetMarkerColor(grParticle1->GetLineColor());
    grParticle1->Draw("SAMELP");

  }

  TLegend *legend = new TLegend(0.784929, 0.800447, 0.890502, 0.881608); // linear scale
  legend->AddEntry(grParticle0, "2.6 MeV", "lp");
  if(!RealFlux)
    legend->AddEntry(grParticle1, "7.6 MeV", "lp");
  
  legend->SetBorderSize(1);
  legend->SetLineColor(kBlack);
  legend->SetFillColor(0);
  legend->Draw();


  c1->SaveAs("AttenuationvsThickness/Attenuation_Thickness_Gammas.pdf");
  
  // delete c1;
  return 0;

}
