// Cloe Girard-Carillo

// This macro can be run in a for loop, to iterate on the thickness and threshold parameters

// How to run this macro:
// 1. Erase the files Threshold_vs_Rate.txt, ...
// 2. Run the macro

// Examples without armor threshold:
// SelectEvents("ID",200)
// SelectEvents("and",200)

// Using threshold:
// SelectEvents("ID",i,j)
// iterating on i thickness (100,200,300,400)
// iterating on j threshold (50,100,150,200,250,300,350,400,450,500)

string generateOutputFileName(const char* particleType, double primaryEnergy, double bWaterThickness, double armorDetectionThreshold, const char* selectedVolumes, const char* prefix) {
  ostringstream ss;
  ss << "RootFiles_SelectedEvents/Simus_" << particleType << "_" << setprecision(0) << primaryEnergy << "MeV_BWater"
     << static_cast<int>(bWaterThickness) << "mm_Threshold" << setprecision(3) << armorDetectionThreshold << "keV_EnergyDeposited_" << prefix << "_" << selectedVolumes << ".root";
  return ss.str();
}

void SelectEvents(string SelectedVolumes, int BWaterThickness, double ArmorDetectionThreshold = 0.) {
  // SelectedVolumes                Selection on the volume where energy were deposited
  // BWaterThickness                Thickness of the borated water
  // ArmorDetectionThreshold = 0.   To apply an energy threshold, in the armor, on the event selection

  // Evaluate the running time of this code
  time_t start, end;
  time(&start);

  // Define the input file name
  const TString& fName = "../../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/RestG4_RootOutputFiles/RunArmor_neutrons_1MeV_BWater" + to_string(BWaterThickness) + "_restG4_SensVol_lsAMT.root";

  // Print some information about the current execution
  cout << "\n" << "Executing Root Macro SelectEvents(\"" << SelectedVolumes << "\", " << BWaterThickness << ", " << ArmorDetectionThreshold << ")" << "\n";
  cout << "With file " << fName << "\n\n";

  // Create an instance of TRestRun and open the input file
  TRestRun* run = new TRestRun();
  run->OpenInputFile(fName);

  // Print some information about the current run
  cout << "Run number " << run->GetRunNumber() << "\n";
  TRestGeant4Event* event = run->GetInputEvent<TRestGeant4Event>();
  const double nEvents = run->GetEntries();
  cout << "Number of events " << nEvents << "\n";

  // Read the Geant4 metadata class
  cout << "Testing reading of Geant4 metadata class" << "\n";
  TRestGeant4Metadata* geant4Metadata = (TRestGeant4Metadata*)run->GetMetadataClass("TRestGeant4Metadata");

  // If there is an issue with reading the metadata class, print an error message and return
  if (!geant4Metadata) {
    cerr << "Problem reading Geant4 metadata class!" << "\n";
    return 6;
  }

  // Print some information about the active volumes
  const vector<TString> VActiveVolumes = geant4Metadata->GetActiveVolumes();
  cout << VActiveVolumes.size() << " active volume(s):\n";

  for (const auto& volume : VActiveVolumes) {
    cout << "ID " << geant4Metadata->GetActiveVolumeID(volume) << " name " << volume << "\n";
  }

  cout << "\n";

  // For now these parameters are not used.
  // int SensitiveVolumeID = geant4Metadata->GetActiveVolumeID(geant4Metadata->GetSensitiveVolume());  
  // int ActiveVolumeID = geant4Metadata->GetActiveVolumeID("ID_lsAMT");
  
  // Get primary event information
  run->GetEntry(0);
  const double PrimaryEnergy = event->GetPrimaryEventEnergy() / 1000.;
  const TString PrimaryParticleType = event->GetPrimaryEventParticleName().Data();

  // Create histograms
  const auto h0 = make_unique<TH1F>("h0", "", 100, 0, 0);
  const auto h1 = make_unique<TH1F>("h1", "", 100, 0, 0);

  // Create output file for debugging
  ostringstream ss;
  ss << "TxtFiles_SelectedEvents/Simus_" << PrimaryParticleType.Data() << "_" << setprecision(0) << PrimaryEnergy << "MeV_BWater"
     << to_string(BWaterThickness) << "mm_Threshold" << setprecision(3) << ArmorDetectionThreshold << "keV_SelectedEvents_AMOTech_" << SelectedVolumes.c_str() << ".txt";
  const auto InfoFile = make_unique<ofstream>(ss.str().c_str());

  // Loop through events
  bool EventSelection = false;
  double SelectionRate = 0.0;
  int counter = 0;
  int counter_selected = 0;
  double Mean_TotalEnergy = 0.0;
  const int Total_number_ev_loop = 10000; // for tests
  // int Total_number_ev_loop = run->GetEntries(); // total number of events in the run

  // Create output files
  const auto Threshold_vs_Rate = make_unique<ofstream>(); 
  const auto Thickness_vs_Energy = make_unique<ofstream>();
  const auto Thickness_vs_Rate = make_unique<ofstream>();
  
  // Loop over simulated events
  for (size_t i = 0; i < Total_number_ev_loop; i++) {
    // Increment counter
    ++counter;

    // Get current event from the simulation data
    run->GetEntry(i);

    // Check if the event is selected based on the SelectedVolumes option and the ArmorDetectionThreshold
    bool checkArmorDetectionThreshold = (ArmorDetectionThreshold == 0);
    bool EventSelection = false;
    if (SelectedVolumes == "ID") {
      // Select events that deposited energy only in the Internal Detector (ID) or that deposited energy in both ID and OD, but with energy below the ArmorDetectionThreshold
      EventSelection = (isnan(event->GetFirstPositionInVolume(0).X()) && !isnan(event->GetFirstPositionInVolume(1).X())) || 
	((!isnan(event->GetFirstPositionInVolume(1).X()) && !isnan(event->GetFirstPositionInVolume(0).X())) && event->GetEnergyDepositedInVolume(1) < ArmorDetectionThreshold);
    } else if (SelectedVolumes == "OD") {
      // Select events that deposited energy only in the Outer Detector (OD)
      EventSelection = checkArmorDetectionThreshold && isnan(event->GetFirstPositionInVolume(1).X()) && !isnan(event->GetFirstPositionInVolume(0).X());
    } else if (SelectedVolumes == "or") {
      // Select events that deposited energy either in ID or in OD
      EventSelection = checkArmorDetectionThreshold && (!isnan(event->GetFirstPositionInVolume(1).X()) || !isnan(event->GetFirstPositionInVolume(0).X()));
    } else if (SelectedVolumes == "and") {
      // Select events that deposited energy both in ID and in OD, with energy above the ArmorDetectionThreshold, or select events that deposited energy only in ID with energy above the ArmorDetectionThreshold
      EventSelection = (!checkArmorDetectionThreshold && !isnan(event->GetFirstPositionInVolume(1).X()) && !isnan(event->GetFirstPositionInVolume(0).X())) || 
	(checkArmorDetectionThreshold && !isnan(event->GetFirstPositionInVolume(1).X()) && !isnan(event->GetFirstPositionInVolume(0).X()) && event->GetEnergyDepositedInVolume(1) > ArmorDetectionThreshold);
    } else if (SelectedVolumes == "none") {
      // Select events that did not deposit energy in any volume
      EventSelection = false;
    } else {
      // Invalid SelectedVolumes option, print possible options and return error code
      cout << "Wrong selected volume name! Possibilities are" << "\n";
      cout << "-\"ID\" for selecting AMOTech only events," << "\n";
      cout << "  -> for AMOTech only events with an energy detection threshold in the Armor, please set the ArmorDetectionThreshold argument different of 0 (keV)." << "\n"; 
      cout << "-\"OD\" for selecting Armor only events," << "\n";
      cout << "-\"or\" for selecting AMOTech OR Armor events," << "\n";
      cout << "-\"and\" for selecting AMOTech AND Armor events," << "\n";
      cout << "-\"none\" for selecting events not depositing energy in any volume." << "\n"; 
      return 6;
    }
  
    if (EventSelection) {
      // Increment counter_selected when EventSelection is true
      ++counter_selected;

      // Print progress and selection info every 1000 events
      if (i % 1000 == 0) {
	cout << setprecision(3) << "\nProgression... " << ((double)i/run->GetEntries())*100. << " %" << "\n";
	cout << counter_selected << " events selected so far (" << ((double)counter_selected/i)*100 << " % selection)\n" << "\n";
      }

      // Fill histograms with energy deposited in AMOTech and Armor
      h0->Fill(event->GetEnergyDepositedInVolume(0)/1000.);  // energy deposited in AMOTech
      h1->Fill(event->GetEnergyDepositedInVolume(1)/1000.);  // energy deposited in Armor

      // Calculate mean total energy and fill text file
      Mean_TotalEnergy += (event->GetEnergyDepositedInVolume(0) + event->GetEnergyDepositedInVolume(1))/1000.;
      if (InfoFile->is_open()) {
	*InfoFile << "event " << i << "\n";
	for (int j = 0; j < 2; j++) { 
	  *InfoFile << "Position (" << event->GetFirstPositionInVolume(j).X() << ", " << event->GetFirstPositionInVolume(j).Y() << ", " << event->GetFirstPositionInVolume(j).Z() << ") mm"  << "\n";
	  *InfoFile << "Energy = " << event->GetEnergyDepositedInVolume(j) << "\n";
	}
      } else {
	cerr << "File InfoFile did not open!" << "\n";
	return 6;
      }      
    }

  }

  // Close the info file
  InfoFile->close();

  // Calculate selection rate and mean total energy
  SelectionRate = ((double) counter_selected / counter);
  Mean_TotalEnergy /= counter_selected;

  const double Var_SelectionRate = sqrt(SelectionRate * (1 - SelectionRate) / counter);
  const double Var_TotalEnergy = sqrt(Mean_TotalEnergy * (1 - Mean_TotalEnergy) / counter);

  // Save selection rate vs. armor threshold to file
  Threshold_vs_Rate->open("TxtFiles_Threshold_vs_Rate/Threshold_vs_Rate.txt", ofstream::app);
  if (!Threshold_vs_Rate->is_open()) {
    cerr << "File Threshold_vs_Rate did not open!\n";
    return 6;
  }
  *Threshold_vs_Rate << ArmorDetectionThreshold << " " << SelectionRate << " " << Var_SelectionRate << "\n";
  Threshold_vs_Rate->close();

  // Save mean total energy vs. borated water layer thickness to file
  Thickness_vs_Energy->open("TxtFiles_Thickness_vs_Energy/Thickness_vs_Energy.txt", ofstream::app);
  if (!Thickness_vs_Energy->is_open()) {
    cerr << "File Thickness_vs_Energy did not open!\n";
    return 6;
  }
  *Thickness_vs_Energy << BWaterThickness << " " << Mean_TotalEnergy << " " << Var_TotalEnergy << "\n";
  Thickness_vs_Energy->close();

  // Save selection rate vs. borated water layer thickness to file
  Thickness_vs_Rate->open("TxtFiles_Thickness_vs_Rate/Thickness_vs_Rate.txt", ofstream::app);
  if (!Thickness_vs_Rate->is_open()) {
    cerr << "File Thickness_vs_Rate did not open!\n";
    return 6;
  }
  *Thickness_vs_Rate << BWaterThickness << " " << SelectionRate << " " << Var_SelectionRate << "\n";
  Thickness_vs_Rate->close();

  // Generate output file names and save histograms
  string OutputRootFileName_AMOTech = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, ArmorDetectionThreshold, SelectedVolumes.c_str(), "AMOTech");
  string OutputRootFileName_Armor = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, ArmorDetectionThreshold, SelectedVolumes.c_str(), "Armor");
  h0->SaveAs(OutputRootFileName_AMOTech.c_str());
  h1->SaveAs(OutputRootFileName_Armor.c_str());

  // Save execution time to file
  time(&end);
  double time_taken = double(end - start);
  ofstream Execution_time("Execution_time.txt", ofstream::app);
  Execution_time << time_taken << setprecision(5) << "\n";
  Execution_time.close();
    
  return 0;
}
