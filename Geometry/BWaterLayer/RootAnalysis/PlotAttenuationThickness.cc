void PlotAttenuationThickness(string particleType){//const std::string& fName

  string path_to_filesAttenuation = "../EventSelection/TxtFiles_Thickness_vs_Attenuation/" ;
  
  string fNameParticle0 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_1MeV.txt";
  string fNameParticle1 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_20MeV.txt";
  string fNameParticle2 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_100MeV.txt";
  string fNameParticle3 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_thermal.txt";
  
  TGraphErrors *grParticle0 = new TGraphErrors(fNameParticle0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *grParticle1 = new TGraphErrors(fNameParticle1.c_str(), "%lg %lg %lg", "");//and
  TGraphErrors *grParticle2 = new TGraphErrors(fNameParticle2.c_str(), "%lg %lg %lg", "");//ID
  TGraphErrors *grParticle3 = new TGraphErrors(fNameParticle3.c_str(), "%lg %lg %lg", "");//ID

  string path_to_filesAttenuationGenerator = "../EventSelection/TxtFiles_Thickness_vs_AttenuationGenerator/" ;

  string fNameParticleGenerator0 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_1MeV.txt";
  string fNameParticleGenerator1 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_20MeV.txt";
  string fNameParticleGenerator2 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_100MeV.txt";
  string fNameParticleGenerator3 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_thermal.txt";
  
  TGraphErrors *grParticleGenerator0 = new TGraphErrors(fNameParticleGenerator0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *grParticleGenerator1 = new TGraphErrors(fNameParticleGenerator1.c_str(), "%lg %lg %lg", "");//and
  TGraphErrors *grParticleGenerator2 = new TGraphErrors(fNameParticleGenerator2.c_str(), "%lg %lg %lg", "");//ID
  TGraphErrors *grParticleGenerator3 = new TGraphErrors(fNameParticleGenerator3.c_str(), "%lg %lg %lg", "");//ID

  string fNameParticleWaterOnly0 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_WaterOnly_1MeV.txt";
  string fNameParticleWaterOnly1 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_WaterOnly_20MeV.txt";
  string fNameParticleWaterOnly2 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_WaterOnly_100MeV.txt";
  string fNameParticleWaterOnly3 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_WaterOnly_thermal.txt";

  TGraphErrors *grParticleWaterOnly0 = new TGraphErrors(fNameParticleWaterOnly0.c_str(), "%lg %lg %lg", "");//ID
  TGraphErrors *grParticleWaterOnly1 = new TGraphErrors(fNameParticleWaterOnly1.c_str(), "%lg %lg %lg", "");//ID
  TGraphErrors *grParticleWaterOnly2 = new TGraphErrors(fNameParticleWaterOnly2.c_str(), "%lg %lg %lg", "");//ID
  TGraphErrors *grParticleWaterOnly3 = new TGraphErrors(fNameParticleWaterOnly3.c_str(), "%lg %lg %lg", "");//ID

  string fNameParticleGeneratorWaterOnly0 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_WaterOnly_1MeV.txt";
  string fNameParticleGeneratorWaterOnly1 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_WaterOnly_20MeV.txt";
  string fNameParticleGeneratorWaterOnly2 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_WaterOnly_100MeV.txt";
  string fNameParticleGeneratorWaterOnly3 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_WaterOnly_thermal.txt";

  TGraphErrors *grParticleGeneratorWaterOnly0 = new TGraphErrors(fNameParticleGeneratorWaterOnly0.c_str(), "%lg %lg %lg", "");//ID
  TGraphErrors *grParticleGeneratorWaterOnly1 = new TGraphErrors(fNameParticleGeneratorWaterOnly1.c_str(), "%lg %lg %lg", "");//ID
  TGraphErrors *grParticleGeneratorWaterOnly2 = new TGraphErrors(fNameParticleGeneratorWaterOnly2.c_str(), "%lg %lg %lg", "");//ID
  TGraphErrors *grParticleGeneratorWaterOnly3 = new TGraphErrors(fNameParticleGeneratorWaterOnly3.c_str(), "%lg %lg %lg", "");//ID

  TGraphErrors *grLegendBWater = new TGraphErrors();//ID
  TGraphErrors *grLegendWaterOnly = new TGraphErrors();//ID
  
  TCanvas *c1 = new TCanvas("c1","",2560,1368);

  // transform rate in %
  grParticle0->Scale(100,"y");
  grParticle1->Scale(100,"y");
  grParticle2->Scale(100,"y");
  grParticle3->Scale(100,"y");

  grParticleGenerator0->Scale(100,"y");
  grParticleGenerator1->Scale(100,"y");
  grParticleGenerator2->Scale(100,"y");
  grParticleGenerator3->Scale(100,"y");

  grParticleWaterOnly0->Scale(100,"y");
  grParticleWaterOnly1->Scale(100,"y");
  grParticleWaterOnly2->Scale(100,"y");
  grParticleWaterOnly3->Scale(100,"y");

  grParticleGeneratorWaterOnly0->Scale(100,"y");
  grParticleGeneratorWaterOnly1->Scale(100,"y");
  grParticleGeneratorWaterOnly2->Scale(100,"y");
  grParticleGeneratorWaterOnly3->Scale(100,"y");
  
  c1->Divide(2,2);
 
  TGaxis::SetMaxDigits(3);
  
  c1->cd(1);
  gPad->SetGrid();

  grParticle0->GetXaxis()->SetNdivisions(7);
  grParticle0->GetYaxis()->SetNdivisions(7);

  grParticle0->SetTitle("Fast neutrons attenuation - prim. + sec. neutrons");
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
    
  grParticle2->SetLineColor(kTeal-5);
  grParticle2->SetLineWidth(grParticle0->GetLineWidth());
  grParticle2->SetLineStyle(grParticle0->GetLineStyle());
  grParticle2->SetMarkerStyle(22);
  grParticle2->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticle2->SetMarkerColor(grParticle2->GetLineColor());
  grParticle2->Draw("SAMELP");
    
  // Water only
  
  grParticleWaterOnly0->SetLineColor(grParticle0->GetLineColor());
  grParticleWaterOnly0->SetMarkerStyle(grParticle0->GetMarkerStyle());
  grParticleWaterOnly0->SetLineStyle(2);
  grParticleWaterOnly0->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleWaterOnly0->SetMarkerColor(grParticle0->GetMarkerColor());
  grParticleWaterOnly0->Draw("SAMELP");
  
  grParticleWaterOnly1->SetLineColor(grParticle1->GetLineColor());
  grParticleWaterOnly1->SetMarkerStyle(grParticle1->GetMarkerStyle());
  grParticleWaterOnly1->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
  grParticleWaterOnly1->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleWaterOnly1->SetMarkerColor(grParticle1->GetMarkerColor());
  grParticleWaterOnly1->Draw("SAMELP");
  
  grParticleWaterOnly2->SetLineColor(grParticle2->GetLineColor());
  grParticleWaterOnly2->SetMarkerStyle(grParticle2->GetMarkerStyle());
  grParticleWaterOnly2->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
  grParticleWaterOnly2->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleWaterOnly2->SetMarkerColor(grParticle2->GetMarkerColor());
  grParticleWaterOnly2->Draw("SAMELP");
    
  grLegendBWater->SetLineWidth(grParticle0->GetLineWidth());
  grLegendBWater->SetLineStyle(grParticle0->GetLineStyle());
  grLegendBWater->SetLineColor(kBlack);
  
  grLegendWaterOnly->SetLineWidth(grParticleWaterOnly0->GetLineWidth());
  grLegendWaterOnly->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
  grLegendWaterOnly->SetLineColor(kBlack);
  
  TLegend *legend = new TLegend(0.550143, 0.204211, 0.878223, 0.336842); // linear scale
  legend->SetNColumns(2);
  legend->AddEntry(grParticle0, "1 MeV", "l");
  legend->AddEntry((TObject*)0, "","");
  legend->AddEntry(grParticle1, "20 MeV", "l");
  legend->AddEntry(grLegendBWater, "w Boron (3%)", "l");
  legend->AddEntry(grParticle2, "100 MeV", "l");
  legend->AddEntry(grLegendWaterOnly, "w/o Boron", "l");
  
  legend->SetBorderSize(1);
  legend->SetLineColor(kBlack);
  legend->SetFillColor(0);
  legend->Draw();

  
  c1->cd(2);
  gPad->SetGrid();

  grParticleGenerator0->GetXaxis()->SetNdivisions(7);
  grParticleGenerator0->GetYaxis()->SetNdivisions(7);

  grParticleGenerator0->SetTitle("Fast neutrons attenuation - prim. neutrons");
  grParticleGenerator0->GetXaxis()->SetTitle(grParticle0->GetXaxis()->GetTitle());
  grParticleGenerator0->GetYaxis()->SetTitle(grParticle0->GetYaxis()->GetTitle());
  grParticleGenerator0->SetLineStyle(1);

  grParticleGenerator0->GetYaxis()->SetRangeUser(LowerLimitY,UpperLimitY);
  grParticleGenerator0->GetXaxis()->SetRangeUser(LowerLimitX,UpperLimitX);

  grParticleGenerator0->SetLineColor(grParticle0->GetLineColor());
  grParticleGenerator0->SetLineWidth(grParticle0->GetLineWidth());
  grParticleGenerator0->SetMarkerStyle(grParticle0->GetMarkerStyle());
  grParticleGenerator0->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGenerator0->SetMarkerColor(grParticle0->GetLineColor());
  grParticleGenerator0->Draw("ALP");
      
  grParticleGenerator1->SetLineColor(grParticle1->GetLineColor());
  grParticleGenerator1->SetLineStyle(grParticleGenerator0->GetLineStyle());
  grParticleGenerator1->SetLineWidth(grParticle0->GetLineWidth());
  grParticleGenerator1->SetMarkerStyle(grParticle1->GetMarkerStyle());
  grParticleGenerator1->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGenerator1->SetMarkerColor(grParticle1->GetLineColor());
  grParticleGenerator1->Draw("SAMELP");
  
  grParticleGenerator2->SetLineColor(grParticle2->GetLineColor());
  grParticleGenerator2->SetLineStyle(grParticleGenerator0->GetLineStyle());
  grParticleGenerator2->SetLineWidth(grParticle0->GetLineWidth());
  grParticleGenerator2->SetMarkerStyle(grParticle2->GetMarkerStyle());
  grParticleGenerator2->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGenerator2->SetMarkerColor(grParticle2->GetLineColor());
  grParticleGenerator2->Draw("SAMELP");

  // Water only
  
  grParticleGeneratorWaterOnly0->SetLineColor(grParticle0->GetLineColor());
  grParticleGeneratorWaterOnly0->SetMarkerStyle(grParticle0->GetMarkerStyle());
  grParticleGeneratorWaterOnly0->SetLineStyle(2);
  grParticleGeneratorWaterOnly0->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGeneratorWaterOnly0->SetMarkerColor(grParticle0->GetLineColor());
  grParticleGeneratorWaterOnly0->Draw("SAMELP");
  
  grParticleGeneratorWaterOnly1->SetLineColor(grParticle1->GetLineColor());
  grParticleGeneratorWaterOnly1->SetMarkerStyle(grParticle1->GetMarkerStyle());
  grParticleGeneratorWaterOnly1->SetLineStyle(grParticleGeneratorWaterOnly0->GetLineStyle());
  grParticleGeneratorWaterOnly1->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGeneratorWaterOnly1->SetMarkerColor(grParticle1->GetLineColor());
  grParticleGeneratorWaterOnly1->Draw("SAMELP");
  
  grParticleGeneratorWaterOnly2->SetLineColor(grParticle2->GetLineColor());
  grParticleGeneratorWaterOnly2->SetMarkerStyle(grParticle2->GetMarkerStyle());
  grParticleGeneratorWaterOnly2->SetLineStyle(grParticleGeneratorWaterOnly0->GetLineStyle());
  grParticleGeneratorWaterOnly2->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGeneratorWaterOnly2->SetMarkerColor(grParticle2->GetLineColor());
  grParticleGeneratorWaterOnly2->Draw("SAMELP");

  legend->Draw();

  // Thermal neutrons plot

  c1->cd(3);

  gPad->SetGrid();

  grParticle3->GetXaxis()->SetNdivisions(7);
  grParticle3->GetYaxis()->SetNdivisions(7);
  
  grParticle3->GetYaxis()->SetRangeUser(95.,102.);
  grParticle3->GetXaxis()->SetRangeUser(LowerLimitX,UpperLimitX);

  grParticle3->SetTitle("Thermal neutrons attenuation (0.025 eV) - prim. + sec. neutrons");
  grParticle3->GetXaxis()->SetTitle(grParticle0->GetXaxis()->GetTitle());
  grParticle3->GetYaxis()->SetTitle(grParticle0->GetYaxis()->GetTitle());

  grParticle3->SetLineColor(kPink-3);
  grParticle3->SetLineWidth(grParticle0->GetLineWidth());
  grParticle3->SetLineStyle(grParticle0->GetLineStyle());
  grParticle3->SetMarkerStyle(21);
  grParticle3->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticle3->SetMarkerColor(grParticle3->GetLineColor());
  grParticle3->Draw("ALP");
  
  grParticleWaterOnly3->SetLineColor(grParticle3->GetLineColor());
  grParticleWaterOnly3->SetMarkerStyle(grParticle3->GetMarkerStyle());
  grParticleWaterOnly3->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
  grParticleWaterOnly3->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleWaterOnly3->SetMarkerColor(grParticle3->GetLineColor());
  grParticleWaterOnly3->Draw("SAMELP");

  TLegend *legend1 = new TLegend(0.550143, 0.204211, 0.878223, 0.336842); // linear scale
  legend1->SetNColumns(2);
  // legend1->AddEntry((TObject*)0, "Neutron generator energy:","");
  legend1->AddEntry(grParticle3, "Thermal", "l");
  legend1->AddEntry(grLegendBWater, "w Boron (3%)", "l");
  legend1->AddEntry((TObject*)0, "","");
  legend1->AddEntry(grLegendWaterOnly, "w/o Boron", "l");
  
  legend1->SetBorderSize(1);
  legend1->SetLineColor(kBlack);
  legend1->SetFillColor(0);
  legend1->Draw();

  c1->cd(4);

  gPad->SetGrid();

  grParticleGenerator3->GetXaxis()->SetNdivisions(7);
  grParticleGenerator3->GetYaxis()->SetNdivisions(7);
  
  grParticleGenerator3->GetYaxis()->SetRangeUser(95.,102.);
  grParticleGenerator3->GetXaxis()->SetRangeUser(LowerLimitX,UpperLimitX);
  
  grParticleGenerator3->SetTitle("Thermal neutrons attenuation (0.025 eV) - prim. neutrons");
  grParticleGenerator3->GetXaxis()->SetTitle(grParticle0->GetXaxis()->GetTitle());
  grParticleGenerator3->GetYaxis()->SetTitle(grParticle0->GetYaxis()->GetTitle());

  grParticleGenerator3->SetLineStyle(grParticle0->GetLineStyle());
  grParticleGenerator3->SetLineColor(grParticle3->GetLineColor());
  grParticleGenerator3->SetLineWidth(grParticle0->GetLineWidth());
  grParticleGenerator3->SetMarkerStyle(grParticle3->GetMarkerStyle());
  grParticleGenerator3->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGenerator3->SetMarkerColor(grParticle3->GetLineColor());
  grParticleGenerator3->Draw("ALP");

  grParticleGeneratorWaterOnly3->SetLineColor(grParticle3->GetLineColor());
  grParticleGeneratorWaterOnly3->SetMarkerStyle(grParticle3->GetMarkerStyle());
  grParticleGeneratorWaterOnly3->SetLineStyle(grParticleGeneratorWaterOnly0->GetLineStyle());
  grParticleGeneratorWaterOnly3->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGeneratorWaterOnly3->SetMarkerColor(grParticleGeneratorWaterOnly3->GetLineColor());
  grParticleGeneratorWaterOnly3->Draw("SAMELP");

  legend1->Draw();
  

  c1->SaveAs("AttenuationvsThickness/SelectionRates_Thickness.pdf");
  
  // delete c1;
  return 0;

}
