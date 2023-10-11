void PlotAttenuationThickness(string particleType, bool Concrete = 0, bool Iron = 0, bool RealFlux = 0){

  // These numbers correspond to the number of neutrons reaching the top of the Igloo per second.
  // They have been calculated with:
  // - The Gordon et al. flux found here /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/ParticleFlux/Gordon_et_al_model_differencial_neutron_flux.root
  // - The top surface of the Igloo taken as 1120x800 cm2 (as of the Igloo design of 27/09/2023)
  // - using this macro /uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/ParticleFlux/RootDrawDifferencialNeutronFlux.cc
  // division by 1e3 to convert the flux in kHz
  double NeutronFluxSec_1MeV = 932/1e3 ;
  double NeutronFluxSec_20MeV = 546/1e3 ;
  double NeutronFluxSec_100MeV = 1051/1e3 ;
  
  // pour tout type de particules qui interagissent dans sensitive
  
  // string path_to_filesAttenuation ;
  // if (Concrete)
  //   path_to_filesAttenuation = "../EventSelection/TxtFiles_Thickness_vs_AttenuationAllPart/Concrete/" ;
  // else
  //   path_to_filesAttenuation = "../EventSelection/TxtFiles_Thickness_vs_AttenuationAllPart/" ;
  
  // string fNameParticle0 = path_to_filesAttenuation+"Thickness_vs_AttenuationAllPart" + particleType + "_1MeV.txt";
  // string fNameParticle1 = path_to_filesAttenuation+"Thickness_vs_AttenuationAllPart" + particleType + "_20MeV.txt";
  // string fNameParticle2 = path_to_filesAttenuation+"Thickness_vs_AttenuationAllPart" + particleType + "_100MeV.txt";
  // string fNameParticle3 = path_to_filesAttenuation+"Thickness_vs_AttenuationAllPart" + particleType + "_thermal.txt";

  // juste pour les neutrons, primaires et secondaires
  string path_to_filesAttenuation = "../EventSelection/TxtFiles_Thickness_vs_AttenuationNeutron/" + particleType + "/" ;
  if (Concrete) {
    path_to_filesAttenuation += "Concrete/" ;
    if (Iron)
      path_to_filesAttenuation += "Iron/" ;
  }
  // else
  //   path_to_filesAttenuation = "../EventSelection/TxtFiles_Thickness_vs_AttenuationNeutron/" ;
  
  string fNameParticle0 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_1MeV.txt";
  string fNameParticle1 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_20MeV.txt";
  string fNameParticle2 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_100MeV.txt";
  string fNameParticle3 = path_to_filesAttenuation+"Thickness_vs_Attenuation" + particleType + "_thermal.txt";
  
  TGraphErrors *grParticle0 = new TGraphErrors(fNameParticle0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *grParticle1 = new TGraphErrors(fNameParticle1.c_str(), "%lg %lg %lg", "");//and
  TGraphErrors *grParticle2 = new TGraphErrors(fNameParticle2.c_str(), "%lg %lg %lg", "");//ID
  TGraphErrors *grParticle3 = new TGraphErrors(fNameParticle3.c_str(), "%lg %lg %lg", "");//ID

  string path_to_filesAttenuationGenerator = "../EventSelection/TxtFiles_Thickness_vs_AttenuationGenerator/" + particleType + "/" ;
if (Concrete) {
    path_to_filesAttenuationGenerator += "Concrete/" ;
    if (Iron)
      path_to_filesAttenuationGenerator += "Iron/" ;
  }
  
  string fNameParticleGenerator0 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_1MeV.txt";
  string fNameParticleGenerator1 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_20MeV.txt";
  string fNameParticleGenerator2 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_100MeV.txt";
  string fNameParticleGenerator3 = path_to_filesAttenuationGenerator+"Thickness_vs_Attenuation" + particleType + "Generator_thermal.txt";
  
  TGraphErrors *grParticleGenerator0 = new TGraphErrors(fNameParticleGenerator0.c_str(), "%lg %lg %lg", "");//or 
  TGraphErrors *grParticleGenerator1 = new TGraphErrors(fNameParticleGenerator1.c_str(), "%lg %lg %lg", "");//and
  TGraphErrors *grParticleGenerator2 = new TGraphErrors(fNameParticleGenerator2.c_str(), "%lg %lg %lg", "");//ID
  TGraphErrors *grParticleGenerator3 = new TGraphErrors(fNameParticleGenerator3.c_str(), "%lg %lg %lg", "");//ID

  // pour tout type de part
  
  // string fNameParticleWaterOnly0 = path_to_filesAttenuation+"Thickness_vs_AttenuationAllPart" + particleType + "_WaterOnly_1MeV.txt";
  // string fNameParticleWaterOnly1 = path_to_filesAttenuation+"Thickness_vs_AttenuationAllPart" + particleType + "_WaterOnly_20MeV.txt";
  // string fNameParticleWaterOnly2 = path_to_filesAttenuation+"Thickness_vs_AttenuationAllPart" + particleType + "_WaterOnly_100MeV.txt";
  // string fNameParticleWaterOnly3 = path_to_filesAttenuation+"Thickness_vs_AttenuationAllPart" + particleType + "_WaterOnly_thermal.txt";

  // pour neutrons seulement
  
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

  
  if (RealFlux) {

    // changing the scale to display the hour flux

    // transforming graph values in values from 0 to 1 
    
    for ( int i = 0; i<grParticle0->GetN(); i++) {
      grParticle0->SetPointY(i,1-grParticle0->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticle1->GetN(); i++) {
      grParticle1->SetPointY(i,1-grParticle1->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticle2->GetN(); i++) {
      grParticle2->SetPointY(i,1-grParticle2->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticle3->GetN(); i++) {
      grParticle3->SetPointY(i,1-grParticle3->GetPointY(i));
    }

    //////////////////
  
    for ( int i = 0; i<grParticleGenerator0->GetN(); i++) {
      grParticleGenerator0->SetPointY(i,1-grParticleGenerator0->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticleGenerator1->GetN(); i++) {
      grParticleGenerator1->SetPointY(i,1-grParticleGenerator1->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticleGenerator2->GetN(); i++) {
      grParticleGenerator2->SetPointY(i,1-grParticleGenerator2->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticleGenerator3->GetN(); i++) {
      grParticleGenerator3->SetPointY(i,1-grParticleGenerator3->GetPointY(i));
    }
  
    //////////////////
  
    for ( int i = 0; i<grParticleWaterOnly0->GetN(); i++) {
      grParticleWaterOnly0->SetPointY(i,1-grParticleWaterOnly0->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticleWaterOnly1->GetN(); i++) {
      grParticleWaterOnly1->SetPointY(i,1-grParticleWaterOnly1->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticleWaterOnly2->GetN(); i++) {
      grParticleWaterOnly2->SetPointY(i,1-grParticleWaterOnly2->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticleWaterOnly3->GetN(); i++) {
      grParticleWaterOnly3->SetPointY(i,1-grParticleWaterOnly3->GetPointY(i));
    }
  
    //////////////////
  
    for ( int i = 0; i<grParticleGeneratorWaterOnly0->GetN(); i++) {
      grParticleGeneratorWaterOnly0->SetPointY(i,1-grParticleGeneratorWaterOnly0->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticleGeneratorWaterOnly1->GetN(); i++) {
      grParticleGeneratorWaterOnly1->SetPointY(i,1-grParticleGeneratorWaterOnly1->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticleGeneratorWaterOnly2->GetN(); i++) {
      grParticleGeneratorWaterOnly2->SetPointY(i,1-grParticleGeneratorWaterOnly2->GetPointY(i));
    }
  
    for ( int i = 0; i<grParticleGeneratorWaterOnly3->GetN(); i++) {
      grParticleGeneratorWaterOnly3->SetPointY(i,1-grParticleGeneratorWaterOnly3->GetPointY(i));
    }

    // Scaling with the flux in seconds

    grParticle0->Scale(NeutronFluxSec_1MeV,"y");
    grParticle1->Scale(NeutronFluxSec_20MeV,"y");
    grParticle2->Scale(NeutronFluxSec_100MeV,"y");
    grParticle3->Scale(NeutronFluxSec_1MeV,"y");

    grParticleGenerator0->Scale(NeutronFluxSec_1MeV,"y");
    grParticleGenerator1->Scale(NeutronFluxSec_20MeV,"y");
    grParticleGenerator2->Scale(NeutronFluxSec_100MeV,"y");
    grParticleGenerator3->Scale(NeutronFluxSec_1MeV,"y");

    grParticleWaterOnly0->Scale(NeutronFluxSec_1MeV,"y");
    grParticleWaterOnly1->Scale(NeutronFluxSec_20MeV,"y");
    grParticleWaterOnly2->Scale(NeutronFluxSec_100MeV,"y");
    grParticleWaterOnly3->Scale(NeutronFluxSec_1MeV,"y");

    grParticleGeneratorWaterOnly0->Scale(NeutronFluxSec_1MeV,"y");
    grParticleGeneratorWaterOnly1->Scale(NeutronFluxSec_20MeV,"y");
    grParticleGeneratorWaterOnly2->Scale(NeutronFluxSec_100MeV,"y");
    grParticleGeneratorWaterOnly3->Scale(NeutronFluxSec_1MeV,"y");
        
  }

  // transform rate in %

  else {
    
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

  }

  // graph that will contain the cumulated number of neutrons, if case RealFulx = true

  // Compute the total neutron flux surviving after the Igloo, by summing on the energy contributions

  int n = grParticle0->GetN();
  double x[n], y[n], yWaterOnly[n], yGenerator[n], yGeneratorWaterOnly[n];

  for (int i = 0 ; i < n ; i++) {

    x[i] = grParticle0->GetPointX(i);
    y[i] = grParticle0->GetPointY(i) + grParticle1->GetPointY(i) + grParticle2->GetPointY(i);
    yWaterOnly[i] = grParticleWaterOnly0->GetPointY(i) + grParticleWaterOnly1->GetPointY(i) + grParticleWaterOnly2->GetPointY(i);
    yGenerator[i] = grParticleGenerator0->GetPointY(i) + grParticleGenerator1->GetPointY(i) + grParticleGenerator2->GetPointY(i);
    yGeneratorWaterOnly[i] = grParticleGeneratorWaterOnly0->GetPointY(i) + grParticleGeneratorWaterOnly1->GetPointY(i) + grParticleGeneratorWaterOnly2->GetPointY(i);

  }

  auto grTotal = new TGraph(n,x,y);
  auto grTotalWaterOnly = new TGraph(n,x,yWaterOnly);
  auto grTotalGenerator = new TGraph(n,x,yGenerator);
  auto grTotalGeneratorWaterOnly = new TGraph(n,x,yGeneratorWaterOnly);
  
  // for (int i = 0 ; i < grParticle0->GetN() ; i++) {
  //   grTotal.SetPoint(i, grParticle0->GetPointX(i), grParticle0->GetPointY(i)+grParticle1->GetPointY(i)+grParticle2->GetPointY(i));
  // }
  // for (int i = 0 ; i < grParticle0->GetN() ; i++) {
  //   cout << grParticle0->GetN() << " " << grParticle0->GetPointX(i) << " " << grParticle0->GetPointY(i) << endl;
  // }
  // for (int i = 0 ; i < grTotal.GetN() ; i++) {
  //   cout << grTotal.GetN() << " " << grTotal.GetPointX(i) << " " << grTotal.GetPointY(i) << endl;
  // }

  c1->Divide(2,2);
 
  TGaxis::SetMaxDigits(3);
  
  c1->cd(1);

  // ----- general settings canvas
  
  gPad->SetGrid();
  gPad->SetFrameLineColor(kGray+2);
  gPad->SetFrameLineWidth(1);

  if (RealFlux)
    gPad->SetLogy();
  
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
  
  grParticle0->SetTitle("Fast neutrons attenuation - prim. + sec. neutrons");
  grParticle0->GetXaxis()->SetTitle("Water layer thickness (mm)");

  if (RealFlux)
    grParticle0->GetYaxis()->SetTitle("# survival particles after Igloo (kHz)");
  else
    grParticle0->GetYaxis()->SetTitle("Attenuation (%)");
  
  double LowerLimitX = 70.;
  double UpperLimitX = 600.;
  double LowerLimitY ;
  double UpperLimitY ;
    
  // limits for y axis in %
  if (RealFlux) {
    LowerLimitY = 1e-6;
    UpperLimitY = 3;
    // LowerLimitY = -0.1;
    // UpperLimitY = 1.3;
  }

  // limits for y axis in 0-1 values
  else {
    LowerLimitY = -10.;
    UpperLimitY = 130.;
  }
  
  grParticle0->GetYaxis()->SetRangeUser(LowerLimitY,UpperLimitY);
  grParticle0->GetXaxis()->SetRangeUser(LowerLimitX,UpperLimitX);

  grParticle0->SetLineColor(kOrange-3);
  grParticle0->SetLineWidth(1);
  grParticle0->SetLineStyle(1);
  grParticle0->SetMarkerStyle(20);
  grParticle0->SetMarkerSize(2);
  grParticle0->SetMarkerColor(grParticle0->GetLineColor());
  grParticle0->Draw("ALP");

  // c1->RedrawAxis();
  
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
  grParticleWaterOnly0->SetLineWidth(grParticle0->GetLineWidth());
  grParticleWaterOnly0->SetMarkerStyle(grParticle0->GetMarkerStyle());
  grParticleWaterOnly0->SetLineStyle(7);
  grParticleWaterOnly0->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleWaterOnly0->SetMarkerColor(grParticle0->GetMarkerColor());
  grParticleWaterOnly0->Draw("SAMELP");
  
  grParticleWaterOnly1->SetLineColor(grParticle1->GetLineColor());
  grParticleWaterOnly1->SetLineWidth(grParticleWaterOnly0->GetLineWidth());
  grParticleWaterOnly1->SetMarkerStyle(grParticle1->GetMarkerStyle());
  grParticleWaterOnly1->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
  grParticleWaterOnly1->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleWaterOnly1->SetMarkerColor(grParticle1->GetMarkerColor());
  // grParticleWaterOnly1->Draw("SAMELP");
  grParticleWaterOnly1->Draw("ALP");
  
  grParticleWaterOnly2->SetLineColor(grParticle2->GetLineColor());
  grParticleWaterOnly2->SetLineWidth(grParticleWaterOnly0->GetLineWidth());
  grParticleWaterOnly2->SetMarkerStyle(grParticle2->GetMarkerStyle());
  grParticleWaterOnly2->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
  grParticleWaterOnly2->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleWaterOnly2->SetMarkerColor(grParticle2->GetMarkerColor());
  grParticleWaterOnly2->Draw("SAMELP");

  if (RealFlux) {

    grTotal->SetLineColor(kBlack);
    grTotal->SetLineWidth(1);
    grTotal->SetLineStyle(grParticle0->GetLineStyle());
    grTotal->SetMarkerStyle(5);
    grTotal->SetMarkerSize(grParticle0->GetMarkerSize());
    grTotal->SetMarkerColor(grTotal->GetLineColor());
    grTotal->Draw("SAMELP");

    grTotalWaterOnly->SetLineColor(grTotal->GetLineColor());
    grTotalWaterOnly->SetMarkerStyle(grTotal->GetMarkerStyle());
    grTotalWaterOnly->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
    grTotalWaterOnly->SetMarkerSize(grTotal->GetMarkerSize());
    grTotalWaterOnly->SetMarkerColor(grTotal->GetMarkerColor());
    grTotalWaterOnly->Draw("SAMELP");

  }  

  
  grLegendBWater->SetLineWidth(grParticle0->GetLineWidth());
  grLegendBWater->SetLineStyle(grParticle0->GetLineStyle());
  grLegendBWater->SetLineColor(kBlack);
  
  grLegendWaterOnly->SetLineWidth(grParticleWaterOnly0->GetLineWidth());
  // grLegendWaterOnly->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
  grLegendWaterOnly->SetLineStyle(2);
  grLegendWaterOnly->SetLineColor(kBlack);

  TLegend *legend = new TLegend(0.853059, 0.57097, 0.998029, 0.899836); // linear scale
  // legend->SetNColumns(2);
  legend->AddEntry(grParticle0, "1 MeV", "l");
  legend->AddEntry(grParticle1, "20 MeV", "l");
  legend->AddEntry(grParticle2, "100 MeV", "l");
  legend->AddEntry((TObject*)0, "","");
  legend->AddEntry(grLegendBWater, "w Boron (3%)", "l");
  legend->AddEntry(grLegendWaterOnly, "w/o Boron", "l");
  
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
  
  grParticle0->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grParticleGenerator0->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
  grParticleGenerator0->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
  grParticleGenerator0->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
  grParticleGenerator0->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grParticleGenerator0->GetXaxis()->SetLabelSize(0.05);
  grParticleGenerator0->GetXaxis()->SetLabelFont(42);
  grParticleGenerator0->GetXaxis()->SetTitleOffset(1.05);
  grParticleGenerator0->GetXaxis()->CenterTitle(1);
  grParticleGenerator0->GetXaxis()->SetTickLength(0.02);
  grParticleGenerator0->GetXaxis()->SetTitleSize(0.05);
  grParticleGenerator0->GetXaxis()->SetTitleFont(42);
  grParticleGenerator0->GetXaxis()->SetNdivisions(7);
  
  grParticleGenerator0->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
  grParticleGenerator0->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
  grParticleGenerator0->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  grParticleGenerator0->GetYaxis()->SetLabelSize(0.05);
  grParticleGenerator0->GetYaxis()->SetLabelFont(42);
  grParticleGenerator0->GetYaxis()->SetTitleOffset(0.9);
  grParticleGenerator0->GetYaxis()->CenterTitle(1);
  grParticleGenerator0->GetYaxis()->SetTickLength(0.02);
  grParticleGenerator0->GetYaxis()->SetTitleSize(0.05);
  grParticleGenerator0->GetYaxis()->SetTitleFont(42);
  grParticleGenerator0->GetYaxis()->SetNdivisions(7);

  // ----------------------------
  
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
  grParticleGeneratorWaterOnly0->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
  grParticleGeneratorWaterOnly0->SetLineWidth(grParticleWaterOnly0->GetLineWidth());
  grParticleGeneratorWaterOnly0->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGeneratorWaterOnly0->SetMarkerColor(grParticle0->GetLineColor());
  grParticleGeneratorWaterOnly0->Draw("SAMELP");
  
  grParticleGeneratorWaterOnly1->SetLineColor(grParticle1->GetLineColor());
  grParticleGeneratorWaterOnly1->SetMarkerStyle(grParticle1->GetMarkerStyle());
  grParticleGeneratorWaterOnly1->SetLineStyle(grParticleGeneratorWaterOnly0->GetLineStyle());
  grParticleGeneratorWaterOnly1->SetLineWidth(grParticleWaterOnly0->GetLineWidth());
  grParticleGeneratorWaterOnly1->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGeneratorWaterOnly1->SetMarkerColor(grParticle1->GetLineColor());
  grParticleGeneratorWaterOnly1->Draw("SAMELP");
  
  grParticleGeneratorWaterOnly2->SetLineColor(grParticle2->GetLineColor());
  grParticleGeneratorWaterOnly2->SetMarkerStyle(grParticle2->GetMarkerStyle());
  grParticleGeneratorWaterOnly2->SetLineWidth(grParticleWaterOnly0->GetLineWidth());
  grParticleGeneratorWaterOnly2->SetLineStyle(grParticleGeneratorWaterOnly0->GetLineStyle());
  grParticleGeneratorWaterOnly2->SetMarkerSize(grParticle0->GetMarkerSize());
  grParticleGeneratorWaterOnly2->SetMarkerColor(grParticle2->GetLineColor());
  grParticleGeneratorWaterOnly2->Draw("SAMELP");

  
  if (RealFlux) {

    grTotalGenerator->SetLineColor(grTotal->GetLineColor());
    grTotalGenerator->SetLineWidth(grTotal->GetLineWidth());
    grTotalGenerator->SetLineStyle(grTotal->GetLineStyle());
    grTotalGenerator->SetMarkerStyle(grTotal->GetMarkerStyle());
    grTotalGenerator->SetMarkerSize(grTotal->GetMarkerSize());
    grTotalGenerator->SetMarkerColor(grTotal->GetLineColor());
    grTotalGenerator->Draw("SAMELP");

    grTotalGeneratorWaterOnly->SetLineColor(grTotalGenerator->GetLineColor());
    grTotalGeneratorWaterOnly->SetMarkerStyle(grTotal->GetMarkerStyle());
    grTotalGeneratorWaterOnly->SetLineStyle(grParticleWaterOnly0->GetLineStyle());
    grTotalGeneratorWaterOnly->SetMarkerSize(grTotalGenerator->GetMarkerSize());
    grTotalGeneratorWaterOnly->SetMarkerColor(grTotalGenerator->GetMarkerColor());
    grTotalGeneratorWaterOnly->Draw("SAMELP");

  }  

  
  legend->Draw();

  // Thermal neutrons plot

  if (!Concrete && !RealFlux) {
  
    c1->cd(3);

    // ----- general settings canvas
  
    gPad->SetGrid();
    gPad->SetFrameLineColor(kGray+2);
    gPad->SetFrameLineWidth(1);
  
    grParticle3->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
    grParticle3->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
    grParticle3->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
    grParticle3->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
    grParticle3->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
    grParticle3->GetXaxis()->SetLabelSize(0.05);
    grParticle3->GetXaxis()->SetLabelFont(42);
    grParticle3->GetXaxis()->SetTitleOffset(1.05);
    grParticle3->GetXaxis()->CenterTitle(1);
    grParticle3->GetXaxis()->SetTickLength(0.02);
    grParticle3->GetXaxis()->SetTitleSize(0.05);
    grParticle3->GetXaxis()->SetTitleFont(42);
    grParticle3->GetXaxis()->SetNdivisions(7);
  
    grParticle3->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
    grParticle3->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
    grParticle3->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
    grParticle3->GetYaxis()->SetLabelSize(0.05);
    grParticle3->GetYaxis()->SetLabelFont(42);
    grParticle3->GetYaxis()->SetTitleOffset(0.9);
    grParticle3->GetYaxis()->CenterTitle(1);
    grParticle3->GetYaxis()->SetTickLength(0.02);
    grParticle3->GetYaxis()->SetTitleSize(0.05);
    grParticle3->GetYaxis()->SetTitleFont(42);
    grParticle3->GetYaxis()->SetNdivisions(7);

    // -----------------------------
  
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
    grParticleWaterOnly3->SetLineWidth(grParticleWaterOnly0->GetLineWidth());
    grParticleWaterOnly3->SetMarkerSize(grParticle0->GetMarkerSize());
    grParticleWaterOnly3->SetMarkerColor(grParticle3->GetLineColor());
    grParticleWaterOnly3->Draw("SAMELP");

    TLegend *legend1 = new TLegend(0.853873, 0.636898, 0.998029, 0.900611); // linear scale
    // legend1->SetNColumns(2);
    legend1->AddEntry(grParticle3, "Thermal", "l");
    legend1->AddEntry((TObject*)0, "","");
    legend1->AddEntry(grLegendBWater, "w Boron (3%)", "l");
    legend1->AddEntry(grLegendWaterOnly, "w/o Boron", "l");
  
    legend1->SetBorderSize(legend->GetBorderSize());
    legend1->SetLineColor(gPad->GetFrameLineColor());
    legend1->SetFillColor(legend->GetFillColor());
    legend1->SetTextColor(gPad->GetFrameLineColor());
    legend1->SetTextSize(legend->GetTextSize());
    legend1->Draw();

    c1->cd(4);

    // ----- general settings canvas
  
    gPad->SetGrid();
    gPad->SetFrameLineColor(kGray+2);
    gPad->SetFrameLineWidth(1);
  
    grParticleGenerator3->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
    grParticleGenerator3->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
  
    grParticleGenerator3->GetXaxis()->SetTitleColor(gPad->GetFrameLineColor());
    grParticleGenerator3->GetXaxis()->SetLabelColor(gPad->GetFrameLineColor());
    grParticleGenerator3->GetXaxis()->SetAxisColor(gPad->GetFrameLineColor());
    grParticleGenerator3->GetXaxis()->SetLabelSize(0.05);
    grParticleGenerator3->GetXaxis()->SetLabelFont(42);
    grParticleGenerator3->GetXaxis()->SetTitleOffset(1.05);
    grParticleGenerator3->GetXaxis()->CenterTitle(1);
    grParticleGenerator3->GetXaxis()->SetTickLength(0.02);
    grParticleGenerator3->GetXaxis()->SetTitleSize(0.05);
    grParticleGenerator3->GetXaxis()->SetTitleFont(42);
    grParticleGenerator3->GetXaxis()->SetNdivisions(7);
  
    grParticleGenerator3->GetYaxis()->SetTitleColor(gPad->GetFrameLineColor());
    grParticleGenerator3->GetYaxis()->SetLabelColor(gPad->GetFrameLineColor());
    grParticleGenerator3->GetYaxis()->SetAxisColor(gPad->GetFrameLineColor());
    grParticleGenerator3->GetYaxis()->SetLabelSize(0.05);
    grParticleGenerator3->GetYaxis()->SetLabelFont(42);
    grParticleGenerator3->GetYaxis()->SetTitleOffset(0.9);
    grParticleGenerator3->GetYaxis()->CenterTitle(1);
    grParticleGenerator3->GetYaxis()->SetTickLength(0.02);
    grParticleGenerator3->GetYaxis()->SetTitleSize(0.05);
    grParticleGenerator3->GetYaxis()->SetTitleFont(42);
    grParticleGenerator3->GetYaxis()->SetNdivisions(7);

    // -----------------------------
    
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
    grParticleGeneratorWaterOnly3->SetLineWidth(grParticleWaterOnly0->GetLineWidth());
    grParticleGeneratorWaterOnly3->SetMarkerSize(grParticle0->GetMarkerSize());
    grParticleGeneratorWaterOnly3->SetMarkerColor(grParticleGeneratorWaterOnly3->GetLineColor());
    // grParticleGeneratorWaterOnly3->SetFillColorAlpha(grParticleGeneratorWaterOnly3->GetFillColor(),0.5);
    // grParticleGeneratorWaterOnly3->SetFillStyle(1001);
    // grParticleGeneratorWaterOnly3->Draw("SAMELP3");
    grParticleGeneratorWaterOnly3->Draw("SAMELP");

    legend1->Draw();

  }

  if (Concrete)
    {
      if (RealFlux) 
	c1->SaveAs("AttenuationvsThickness/SurvivalAfterIgloo_Thickness_RealFlux_WithConcrete.pdf");
      else
	c1->SaveAs("AttenuationvsThickness/Attenuation_Thickness_WithConcrete.pdf");
    }
  else if (Iron)
    {
      if (RealFlux) 
	c1->SaveAs("AttenuationvsThickness/SurvivalAfterIgloo_Thickness_RealFlux_WithConcreteIron.pdf");
      else
	c1->SaveAs("AttenuationvsThickness/Attenuation_Thickness_WithConcreteIron.pdf");
    }
  else 
    c1->SaveAs("AttenuationvsThickness/Attenuation_Thickness.pdf");

  // delete c1;

  return 0;

}
