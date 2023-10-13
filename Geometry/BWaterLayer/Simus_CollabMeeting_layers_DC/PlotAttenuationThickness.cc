void PlotAttenuationThickness(string particleType, bool RealFlux = 0){

  // These numbers correspond to the number of neutrons reaching the top of the Igloo per second.
  // They have been calculated with:
  // - The Gordon et al. flux found here /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/ParticleFlux/Gordon_et_al_model_differencial_neutron_flux.root
  // - The top surface of the Igloo taken as 1120x800 cm2 (as of the Igloo design of 27/09/2023)
  // - using this macro /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/ParticleFlux/RootDrawDifferencialNeutronFlux.cc
  // division by 1e3 to convert the flux in kHz
  double NeutronFluxSec_1MeV = 932./1e3 ;
  double NeutronFluxSec_20MeV = 546./1e3 ;
  double NeutronFluxSec_100MeV = 1051./1e3 ;
  double NeutronFluxSec_Gordon = 4928./1e3 ;

  // particleType, primaires et secondaires
  string path_to_filesAttenuation = "TxtFiles_Thickness_vs_AttenuationNeutron/" + particleType + "/Attenuation" + particleType + "_" ;
  
  string fNameParticle0 = path_to_filesAttenuation+"IronTop.txt";
  string fNameParticle1 = path_to_filesAttenuation+"IronBelow.txt";
  
  TGraphErrors *grIronTop = new TGraphErrors(fNameParticle0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *grIronBelow = new TGraphErrors(fNameParticle1.c_str(), "%lg %lg %lg", "");//and

  // other particle
  string path_to_filesAttenuationGamma = "TxtFiles_Thickness_vs_AttenuationGamma/" + particleType + "/AttenuationGamma_" ;
  
  string fNameParticleGamma0 = path_to_filesAttenuationGamma+"IronTop.txt";
  string fNameParticleGamma1 = path_to_filesAttenuationGamma+"IronBelow.txt";
  
  TGraphErrors *grIronTopGamma = new TGraphErrors(fNameParticleGamma0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *grIronBelowGamma = new TGraphErrors(fNameParticleGamma1.c_str(), "%lg %lg %lg", "");//and

  // particleType primaires 
  string path_to_filesAttenuationGenerator = "TxtFiles_Thickness_vs_AttenuationGenerator/" + particleType + "/AttenuationGenerator_" ;
  
  string fNameParticleGenerator0 = path_to_filesAttenuationGenerator+"IronTop.txt";
  string fNameParticleGenerator1 = path_to_filesAttenuationGenerator+"IronBelow.txt";
  
  TGraphErrors *grIronTopGenerator = new TGraphErrors(fNameParticleGenerator0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *grIronBelowGenerator = new TGraphErrors(fNameParticleGenerator1.c_str(), "%lg %lg %lg", "");//and

  // particleType, all kind of part primaires et secondaires
  string path_to_filesAttenuationAllPart = "TxtFiles_Thickness_vs_AttenuationAllPart/" + particleType + "/AttenuationAllPart_" ;
  
  string fNameParticleAllPart0 = path_to_filesAttenuationAllPart+"IronTop.txt";
  string fNameParticleAllPart1 = path_to_filesAttenuationAllPart+"IronBelow.txt";
  
  TGraphErrors *grIronTopAllPart = new TGraphErrors(fNameParticleAllPart0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *grIronBelowAllPart = new TGraphErrors(fNameParticleAllPart1.c_str(), "%lg %lg %lg", "");//and

  // legend style
  TGraphErrors *grLegendBWater = new TGraphErrors();//ID
  TGraphErrors *grLegendWaterOnly = new TGraphErrors();//ID

  
  TCanvas *c1 = new TCanvas("c1","",2560,1368);

  for ( int i = 0; i<grIronTop->GetN(); i++) {
    grIronTopGamma->SetPointY(i,1-grIronTopGamma->GetPointY(i));
  }

  for ( int i = 0; i<grIronBelow->GetN(); i++) {
    grIronBelowGamma->SetPointY(i,1-grIronBelowGamma->GetPointY(i));
  }
    
  if (RealFlux) {

    // changing the scale to display the hour flux

    // transforming graph values in values from 0 to 1 
    
    for ( int i = 0; i<grIronTop->GetN(); i++) {
      grIronTop->SetPointY(i,1-grIronTop->GetPointY(i));
    }
  
    for ( int i = 0; i<grIronBelow->GetN(); i++) {
      grIronBelow->SetPointY(i,1-grIronBelow->GetPointY(i));
    }

    //////////////////
  
    for ( int i = 0; i<grIronTopGenerator->GetN(); i++) {
      grIronTopGenerator->SetPointY(i,1-grIronTopGenerator->GetPointY(i));
    }
  
    for ( int i = 0; i<grIronBelowGenerator->GetN(); i++) {
      grIronBelowGenerator->SetPointY(i,1-grIronBelowGenerator->GetPointY(i));
    }
  
    // Scaling with the flux in seconds
    
    grIronTop->Scale(NeutronFluxSec_Gordon,"y");
    grIronBelow->Scale(NeutronFluxSec_Gordon,"y");

    grIronTopGenerator->Scale(NeutronFluxSec_Gordon,"y");
    grIronBelowGenerator->Scale(NeutronFluxSec_Gordon,"y");
        
  }

  // transform rate in %

  else {
    
    grIronTop->Scale(100,"y");
    grIronBelow->Scale(100,"y");

    grIronTopGenerator->Scale(100,"y");
    grIronBelowGenerator->Scale(100,"y");

  }

  // graph that will contain the cumulated number of neutrons, if case RealFulx = true

  c1->Divide(2,2);
 
  TGaxis::SetMaxDigits(3);
  
  c1->cd(1);

  // ----- general settings canvas
  
  gPad->SetGrid();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  if (RealFlux)
    gPad->SetLogy();
  
  grIronTop->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grIronTop->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  grIronTop->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  grIronTop->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  grIronTop->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grIronTop->GetXaxis()->SetLabelSize(0.0);
  grIronTop->GetXaxis()->SetLabelFont(42);
  grIronTop->GetXaxis()->SetTitleOffset(1.05);
  grIronTop->GetXaxis()->CenterTitle(1);
  grIronTop->GetXaxis()->SetTickLength(0.02);
  grIronTop->GetXaxis()->SetTitleSize(0.05);
  grIronTop->GetXaxis()->SetTitleFont(42);
  grIronTop->GetXaxis()->SetNdivisions(7);
  
  grIronTop->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  grIronTop->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  grIronTop->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grIronTop->GetYaxis()->SetLabelSize(0.05);
  grIronTop->GetYaxis()->SetLabelFont(42);
  grIronTop->GetYaxis()->SetTitleOffset(0.9);
  grIronTop->GetYaxis()->CenterTitle(1);
  grIronTop->GetYaxis()->SetTickLength(0.02);
  grIronTop->GetYaxis()->SetTitleSize(0.05);
  grIronTop->GetYaxis()->SetTitleFont(42);
  grIronTop->GetYaxis()->SetNdivisions(7);

  // -----------------------------
  
  grIronTop->SetTitle("Fast neutrons attenuation - prim. + sec. neutrons");
  grIronTop->GetXaxis()->SetTitle("");

  if (RealFlux)
    grIronTop->GetYaxis()->SetTitle("# survival particles after Igloo (kHz)");
  else
    grIronTop->GetYaxis()->SetTitle("Attenuation (%)");
  
  // double LowerLimitX = 70.;
  // double UpperLimitX = 600.;
  // double LowerLimitY ;
  // double UpperLimitY ;
    
  // // limits for y axis in %
  // if (RealFlux) {
  //   LowerLimitY = 1e-6;
  //   UpperLimitY = 3;
  //   // LowerLimitY = -0.1;
  //   // UpperLimitY = 1.3;
  // }

  // // limits for y axis in 0-1 values
  // else {
  //   LowerLimitY = 70.;
  //   UpperLimitY = 105.;
  // }
  
  // grIronTop->GetYaxis()->SetRangeUser(LowerLimitY,UpperLimitY);
  // grIronTop->GetXaxis()->SetRangeUser(LowerLimitX,UpperLimitX);

  grIronTop->SetLineColor(kOrange+7);
  grIronTop->SetLineWidth(1);
  grIronTop->SetLineStyle(1);
  grIronTop->SetMarkerStyle(20);
  grIronTop->SetMarkerSize(2);
  grIronTop->SetMarkerColor(grIronTop->GetLineColor());
  grIronTop->Draw("ALP");

  // c1->RedrawAxis();
  
  grIronBelow->SetLineColor(kMagenta+3);
  grIronBelow->SetLineWidth(grIronTop->GetLineWidth());
  grIronBelow->SetLineStyle(grIronTop->GetLineStyle());
  grIronBelow->SetMarkerStyle(23);
  grIronBelow->SetMarkerSize(grIronTop->GetMarkerSize());
  grIronBelow->SetMarkerColor(grIronBelow->GetLineColor());
  grIronBelow->Draw("SAMELP");
  
  // grLegendBWater->SetLineWidth(grIronTop->GetLineWidth());
  // grLegendBWater->SetLineStyle(grIronTop->GetLineStyle());
  // grLegendBWater->SetLineColor(kBlack);
  
  // grLegendWaterOnly->SetLineWidth(grParticleWaterOnly0->GetLineWidth());
  // // grLegendWaterOnly->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
  // grLegendWaterOnly->SetLineStyle(2);
  // grLegendWaterOnly->SetLineColor(kBlack);

  TLegend *legend = new TLegend(0.745553, 0.42039, 0.889709, 0.578618); // linear scale
  // legend->SetNColumns(2);
  legend->AddEntry(grIronTop, "Iron on top", "lp");
  legend->AddEntry(grIronBelow, "Iron below", "lp");
  
  legend->SetBorderSize(1);
  legend->SetLineColor(gPad->GetFrameLineColor());
  legend->SetFillColor(0);
  legend->SetTextColor(gPad->GetFrameLineColor());
  legend->SetTextSize(0.035);
  legend->Draw();

  
  // for generator particles
  
  c1->cd(2);


  // ----- general settings canvas
  
  gPad->SetGrid();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  if (RealFlux)
    gPad->SetLogy();
  
  grIronTop->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grIronTopGenerator->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  grIronTopGenerator->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  grIronTopGenerator->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  grIronTopGenerator->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grIronTopGenerator->GetXaxis()->SetLabelSize(0.0);
  grIronTopGenerator->GetXaxis()->SetLabelFont(42);
  grIronTopGenerator->GetXaxis()->SetTitleOffset(1.05);
  grIronTopGenerator->GetXaxis()->CenterTitle(1);
  grIronTopGenerator->GetXaxis()->SetTickLength(0.02);
  grIronTopGenerator->GetXaxis()->SetTitleSize(0.05);
  grIronTopGenerator->GetXaxis()->SetTitleFont(42);
  grIronTopGenerator->GetXaxis()->SetNdivisions(7);
  
  grIronTopGenerator->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  grIronTopGenerator->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  grIronTopGenerator->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grIronTopGenerator->GetYaxis()->SetLabelSize(0.05);
  grIronTopGenerator->GetYaxis()->SetLabelFont(42);
  grIronTopGenerator->GetYaxis()->SetTitleOffset(0.9);
  grIronTopGenerator->GetYaxis()->CenterTitle(1);
  grIronTopGenerator->GetYaxis()->SetTickLength(0.02);
  grIronTopGenerator->GetYaxis()->SetTitleSize(0.05);
  grIronTopGenerator->GetYaxis()->SetTitleFont(42);
  grIronTopGenerator->GetYaxis()->SetNdivisions(7);

  // ----------------------------
  
  grIronTopGenerator->SetTitle("Fast neutrons attenuation - prim. neutrons");
  grIronTopGenerator->GetXaxis()->SetTitle(grIronTop->GetXaxis()->GetTitle());
  grIronTopGenerator->GetYaxis()->SetTitle(grIronTop->GetYaxis()->GetTitle());
  grIronTopGenerator->SetLineStyle(1);

  // grIronTopGenerator->GetYaxis()->SetRangeUser(LowerLimitY,UpperLimitY);
  // grIronTopGenerator->GetXaxis()->SetRangeUser(LowerLimitX,UpperLimitX);

  grIronTopGenerator->SetLineColor(grIronTop->GetLineColor());
  grIronTopGenerator->SetLineWidth(grIronTop->GetLineWidth());
  grIronTopGenerator->SetMarkerStyle(grIronTop->GetMarkerStyle());
  grIronTopGenerator->SetMarkerSize(grIronTop->GetMarkerSize());
  grIronTopGenerator->SetMarkerColor(grIronTop->GetLineColor());
  grIronTopGenerator->Draw("ALP");
      
  grIronBelowGenerator->SetLineColor(grIronBelow->GetLineColor());
  grIronBelowGenerator->SetLineStyle(grIronTopGenerator->GetLineStyle());
  grIronBelowGenerator->SetLineWidth(grIronTop->GetLineWidth());
  grIronBelowGenerator->SetMarkerStyle(grIronBelow->GetMarkerStyle());
  grIronBelowGenerator->SetMarkerSize(grIronTop->GetMarkerSize());
  grIronBelowGenerator->SetMarkerColor(grIronBelow->GetLineColor());
  grIronBelowGenerator->Draw("SAMELP");

    
  legend->Draw();


  // gammas
  
  c1->cd(3);

  // ----- general settings canvas
  
  gPad->SetGrid();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  // if (RealFlux)
  //   gPad->SetLogy();

  grIronTopGamma->SetTitle("Gamma production");
  
  grIronTopGamma->GetYaxis()->SetTitle("# #gamma / generated neutrons");
  
  grIronTopGamma->GetYaxis()->SetRangeUser(8e-4,0.21);
   
  grIronTopGamma->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grIronTopGamma->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  grIronTopGamma->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  grIronTopGamma->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  grIronTopGamma->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grIronTopGamma->GetXaxis()->SetLabelSize(0.0);
  grIronTopGamma->GetXaxis()->SetLabelFont(42);
  grIronTopGamma->GetXaxis()->SetTitleOffset(1.05);
  grIronTopGamma->GetXaxis()->CenterTitle(1);
  grIronTopGamma->GetXaxis()->SetTickLength(0.02);
  grIronTopGamma->GetXaxis()->SetTitleSize(0.05);
  grIronTopGamma->GetXaxis()->SetTitleFont(42);
  grIronTopGamma->GetXaxis()->SetNdivisions(7);
  
  grIronTopGamma->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  grIronTopGamma->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  grIronTopGamma->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grIronTopGamma->GetYaxis()->SetLabelSize(0.05);
  grIronTopGamma->GetYaxis()->SetLabelFont(42);
  grIronTopGamma->GetYaxis()->SetTitleOffset(0.9);
  grIronTopGamma->GetYaxis()->CenterTitle(1);
  grIronTopGamma->GetYaxis()->SetTickLength(0.02);
  grIronTopGamma->GetYaxis()->SetTitleSize(0.05);
  grIronTopGamma->GetYaxis()->SetTitleFont(42);
  grIronTopGamma->GetYaxis()->SetNdivisions(7);

  // -----------------------------

  grIronTopGamma->SetLineColor(grIronTop->GetLineColor());
  grIronTopGamma->SetLineWidth(1);
  grIronTopGamma->SetLineStyle(1);
  grIronTopGamma->SetMarkerStyle(20);
  grIronTopGamma->SetMarkerSize(2);
  grIronTopGamma->SetMarkerColor(grIronTopGamma->GetLineColor());
  grIronTopGamma->Draw("ALP");

    
  grIronBelowGamma->SetLineColor(grIronBelow->GetLineColor());
  grIronBelowGamma->SetLineWidth(grIronTop->GetLineWidth());
  grIronBelowGamma->SetLineStyle(grIronTop->GetLineStyle());
  grIronBelowGamma->SetMarkerStyle(23);
  grIronBelowGamma->SetMarkerSize(grIronTop->GetMarkerSize());
  grIronBelowGamma->SetMarkerColor(grIronBelow->GetLineColor());
  grIronBelowGamma->Draw("SAMELP");


  legend->Draw();


  // // all part
  
  // c1->cd(4);

  // // ----- general settings canvas
  
  // gPad->SetGrid();
  // gPad->SetFrameLineColor(kGray+2);
  // gPad->SetFrameLineWidth(1);

  // if (RealFlux)
  //   gPad->SetLogy();

  // grIronTopAllPart->SetTitle("AllPart production");

  // grIronTopAllPart->GetYaxis()->SetTitle("# #gamma / generated neutrons");
  
  // grIronTopGamma->GetYaxis()->SetRangeUser(8e-4,0.3);
   
  // grIronTopAllPart->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // grIronTopAllPart->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  // grIronTopAllPart->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // grIronTopAllPart->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // grIronTopAllPart->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // grIronTopAllPart->GetXaxis()->SetLabelSize(0.0);
  // grIronTopAllPart->GetXaxis()->SetLabelFont(42);
  // grIronTopAllPart->GetXaxis()->SetTitleOffset(1.05);
  // grIronTopAllPart->GetXaxis()->CenterTitle(1);
  // grIronTopAllPart->GetXaxis()->SetTickLength(0.02);
  // grIronTopAllPart->GetXaxis()->SetTitleSize(0.05);
  // grIronTopAllPart->GetXaxis()->SetTitleFont(42);
  // grIronTopAllPart->GetXaxis()->SetNdivisions(7);
  
  // grIronTopAllPart->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  // grIronTopAllPart->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  // grIronTopAllPart->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  // grIronTopAllPart->GetYaxis()->SetLabelSize(0.05);
  // grIronTopAllPart->GetYaxis()->SetLabelFont(42);
  // grIronTopAllPart->GetYaxis()->SetTitleOffset(0.9);
  // grIronTopAllPart->GetYaxis()->CenterTitle(1);
  // grIronTopAllPart->GetYaxis()->SetTickLength(0.02);
  // grIronTopAllPart->GetYaxis()->SetTitleSize(0.05);
  // grIronTopAllPart->GetYaxis()->SetTitleFont(42);
  // grIronTopAllPart->GetYaxis()->SetNdivisions(7);

  // // -----------------------------

  // grIronTopAllPart->SetLineColor(grIronTop->GetLineColor());
  // grIronTopAllPart->SetLineWidth(1);
  // grIronTopAllPart->SetLineStyle(1);
  // grIronTopAllPart->SetMarkerStyle(20);
  // grIronTopAllPart->SetMarkerSize(2);
  // grIronTopAllPart->SetMarkerColor(grIronTopAllPart->GetLineColor());
  // grIronTopAllPart->Draw("ALP");

    
  // grIronBelowAllPart->SetLineColor(grIronBelow->GetLineColor());
  // grIronBelowAllPart->SetLineWidth(grIronTop->GetLineWidth());
  // grIronBelowAllPart->SetLineStyle(grIronTop->GetLineStyle());
  // grIronBelowAllPart->SetMarkerStyle(23);
  // grIronBelowAllPart->SetMarkerSize(grIronTop->GetMarkerSize());
  // grIronBelowAllPart->SetMarkerColor(grIronBelowAllPart->GetLineColor());
  // grIronBelowAllPart->Draw("SAMELP");


  // legend->Draw();

  if (RealFlux)
    c1->SaveAs("SurvivalAfterIgloo_Thickness_RealFlux.pdf");
  else
    c1->SaveAs("SurvivalAfterIgloo_Thicknesspdf");

  // delete c1;

  return 0;

}
