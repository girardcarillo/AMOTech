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

void storeChildrenTracks(int trackNumber, const TRestGeant4Event& event, const map<int, int>& trackIDToNumberMap, vector<int>& childrenTracks) {
  for (const auto& childTrack : event.GetTrack(trackNumber).GetChildrenTracks())
    {
      int childTrackID = childTrack->GetTrackID();

      // Check if the child track ID exists in the track ID to number map
      auto iter = trackIDToNumberMap.find(childTrackID);
      if (iter != trackIDToNumberMap.end())
	{
	  int childTrackNumber = iter->second;

	  // Store the child track ID in the vector
	  childrenTracks.push_back(childTrackID);

	  // Recursive call to store the children tracks of the current child track
	  storeChildrenTracks(childTrackNumber, event, trackIDToNumberMap, childrenTracks);
	}
    }
}

// Function to count the occurrences of track hits and store the indices
void countTrackHits(const vector<vector<int>>& aSensitiveTrackHitCollection,
		    unordered_map<int, vector<int>>& trackHitMap,
		    vector<int>& nonRepeatingTrackIDs,
		    int& smallestHitNumber)
{
  for (const auto& pair : aSensitiveTrackHitCollection) {
    int trackNumber = pair[0];
    int hitNumber = pair[1];

    if (trackHitMap.count(trackNumber) == 0) {
      trackHitMap[trackNumber] = { hitNumber };
      nonRepeatingTrackIDs.push_back(trackNumber);
    } else {
      trackHitMap[trackNumber].push_back(hitNumber);
    }

    if (trackHitMap[trackNumber].size() > 1 && hitNumber < smallestHitNumber) {
      smallestHitNumber = hitNumber;
    }
  }
}

// Function to find the track IDs with the smallest hit number among the repeating track IDs
void findTrackIDsWithSmallestHitNumber(const unordered_map<int, vector<int>>& trackHitMap,
				       const vector<int>& nonRepeatingTrackIDs,
				       int smallestHitNumber,
				       vector<vector<int>>& trackHitVector)
{
  for (const auto& pair : trackHitMap) {
    int trackNumber = pair.first;
    const vector<int>& hitNumbers = pair.second;

    if (hitNumbers.size() > 1 && find(hitNumbers.begin(), hitNumbers.end(), smallestHitNumber) != hitNumbers.end()) {
      trackHitVector.push_back({ trackNumber, smallestHitNumber });
      break;
    }
  }

  for (int trackNumber : nonRepeatingTrackIDs) {
    const vector<int>& hitNumbers = trackHitMap.at(trackNumber);
    if (hitNumbers.size() == 1) {
      trackHitVector.push_back({ trackNumber, hitNumbers[0] });
    }
  }
}

// Function to find the smallest trackID among the trackHitVector and check their affiliation
void findAndCheckTrackAffiliation(vector<vector<int>>& trackHitVector,
				  const TRestGeant4Event& event,
				  const map<int, int>& trackIDToNumberMap)
{
  if (trackHitVector.size() <= 1) {
    return;
  }

  int smallestTrackID = numeric_limits<int>::max();
  int smallestTrackIDIndex = -1;

  for (int i = 0; i < trackHitVector.size(); ++i) {
    int trackNumber = trackHitVector[i][0];
    int trackID = event.GetTrack(trackNumber).GetTrackID();

    if (trackID < smallestTrackID) {
      smallestTrackID = trackID;
      smallestTrackIDIndex = i;
    }
  }

  // cout << "Smallest TrackID: " << smallestTrackID << ", Index: " << smallestTrackIDIndex << endl;

  vector<int> childrenTracks;
  storeChildrenTracks(trackHitVector[smallestTrackIDIndex][0], event, trackIDToNumberMap, childrenTracks);

  // // cout << "Children Tracks:\n";
  // for (const auto& trackID : childrenTracks) {
  //   cout << "TrackID: " << trackID << "\n";
  // }

  for (auto it = trackHitVector.begin(); it != trackHitVector.end(); ) {
    int trackNumber = (*it)[0];
    int trackID = event.GetTrack(trackNumber).GetTrackID();

    if (trackID != smallestTrackID) {
      bool isPresent = find(childrenTracks.begin(), childrenTracks.end(), trackID) != childrenTracks.end();

      if (isPresent) {
	// cout << "The trackID " << trackID << " is a child of trackID " << smallestTrackID << endl;
	it = trackHitVector.erase(it);
      } else {
	// cout << "The trackID " << trackID << " is NOT a child of trackID " << smallestTrackID << endl;
	++it;
      }
    } else {
      ++it;
    }
  }
}

// Main algorithm to check if trackIDs are related
void checkTrackRelation(const std::vector<std::vector<int>>& aSensitiveTrackHitCollection,
                        const TRestGeant4Event& event,
                        const std::map<int, int>& trackIDToNumberMap,
                        std::vector<std::vector<int>>& trackHitVector)
{
  std::unordered_map<int, std::vector<int>> trackHitMap;
  std::vector<int> nonRepeatingTrackIDs;
  int smallestHitNumber = std::numeric_limits<int>::max();

  countTrackHits(aSensitiveTrackHitCollection, trackHitMap, nonRepeatingTrackIDs, smallestHitNumber);
  findTrackIDsWithSmallestHitNumber(trackHitMap, nonRepeatingTrackIDs, smallestHitNumber, trackHitVector);
  findAndCheckTrackAffiliation(trackHitVector, event, trackIDToNumberMap);

  
}


string generateOutputFileName(const char* particleType, double primaryEnergy, double bWaterThickness, bool WaterOnly, double armorDetectionThreshold, const char* selectedVolumes, const char* prefix)
{

  ostringstream ss;
  
  if (!WaterOnly)
    {
      
      ss << "RootFiles_SelectedEvents/tmp/Simus_" << particleType << "_" << setprecision(3) << primaryEnergy << "MeV_BWater"
	 << static_cast<int>(bWaterThickness) << "mm_Threshold" << setprecision(3) << armorDetectionThreshold << "keV_EnergyDeposited_" << prefix << "_" << selectedVolumes << ".root";
    
    }
  else if (WaterOnly)
    {
      
      ss << "RootFiles_SelectedEvents/tmp/Simus_" << particleType << "_" << setprecision(3) << primaryEnergy << "MeV_Water"
	 << static_cast<int>(bWaterThickness) << "mm_Threshold" << setprecision(3) << armorDetectionThreshold << "keV_EnergyDeposited_" << prefix << "_" << selectedVolumes << ".root";
    
    }
  
  return ss.str();
  
}

void SelectEvents(string SelectedVolumes, int BWaterThickness, string energy, string partType, bool WaterOnly = 0, bool thermal = 0, double DetectionThreshold = 0.)
{
  
  // SelectedVolumes                Selection on the volume where energy were deposited
  // BWaterThickness                Thickness of the borated water
  // DetectionThreshold = 0.        To apply an energy threshold, in the armor, on the event selection

  // Evaluate the running time of this code
  time_t start, end;
  time(&start);

  // Define the input file name
  // const TString& fName = "/uni-mainz.de/homes/cgirardc/Workdir/nuCLOUD-REST-Simulations/Geometry/BWaterLayer/RootOutputFiles/BWaterSimus_" + to_string(BWaterThickness) + "mm_" + to_string(energy) + "MeV.root"; //_testNotKill

  string fName = "/AGWeber/girardcarillo/" + partType + "/";
  
  if (!thermal)
    {

      stringstream stream;
      int outputPrecision = 0;
    
      size_t found = energy.find(".");
      if (found != string::npos)
	{
	  
	  outputPrecision = 1;
	  cout << "Coma found at: " << found << '\n';
      
	}
    
      stream << fixed << setprecision(outputPrecision) << energy;
      string senergy = stream.str();
        	
      if (WaterOnly)	
	fName = fName + "WaterOnly/WaterSimus_" + to_string(BWaterThickness) + "mm_" + senergy + "MeV.root";
    
      else 
	fName = fName + "BWater/BWaterSimus_" + to_string(BWaterThickness) + "mm_" + senergy + "MeV.root";
    
    }
  
  else
    {

      if (WaterOnly)
	fName = fName + "WaterOnly/WaterSimus_" + to_string(BWaterThickness) + "mm_thermal.root";
    
      else
	fName = fName + "BWater/BWaterSimus_" + to_string(BWaterThickness) + "mm_thermal.root";
    
    }

  // Print some information about the current execution
  cout << "\n" << "Executing Root Macro SelectEvents(\"" << SelectedVolumes << "\", BWaterThickness=" << BWaterThickness << ", energy=" << energy << ", WaterOnly=" <<  WaterOnly << ", DetectionThreshold=" << DetectionThreshold << ")" << "\n";
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
  cout << "Testing reading of Geant4 metadata class...";
  TRestGeant4Metadata* geant4Metadata = (TRestGeant4Metadata*)run->GetMetadataClass("TRestGeant4Metadata");

  // If there is an issue with reading the metadata class, print an error message and return
  if (!geant4Metadata)
    {
      
      cerr << "Problem reading Geant4 metadata class!" << "\n";
      return 6;
    
    }
  
  else      
    cout << " ok" << endl;
    
  // Print some information about the active volumes
  const vector<TString> VActiveVolumes = geant4Metadata->GetActiveVolumes();
  cout << VActiveVolumes.size() << " active volume(s):\n";

  for (const auto& volume : VActiveVolumes)
    cout << "ID " << geant4Metadata->GetActiveVolumeID(volume) << " name " << volume << "\n";
    
  cout << "\n";
  
  // Get primary event information
  run->GetEntry(0);
  const double PrimaryEnergy = event->GetPrimaryEventEnergy() / 1000.;
  const TString PrimaryParticleType = event->GetPrimaryEventParticleName().Data();

  // Define the Sensitive and Active volume IDs  
  int SensitiveVolumeID = geant4Metadata->GetActiveVolumeID(geant4Metadata->GetSensitiveVolume());
  int ActiveVolumeID = geant4Metadata->GetActiveVolumeID("BWater");

  // Create histograms

  // Adaptative range with Primary energy
  // To remove when study with neutron spectrum
  double UpperRange = 0.;
  int nbins = 500;
  
  if (PrimaryParticleType == "neutron")
    {
      
      if (PrimaryEnergy == 1.)
	UpperRange = 4.;
      
      else if (PrimaryEnergy == 20.)
	UpperRange = 30.;
      
      else if (PrimaryEnergy == 100.)
	UpperRange = 120.;

    }
  else if (PrimaryParticleType == "gamma")
    {
      
      if (PrimaryEnergy == 2.6)
	UpperRange = 4.;
      
      else if (PrimaryEnergy == 7.6)
	UpperRange = 10.;
    
    }
  
  const auto h0 = make_unique<TH1F>("h0", "", nbins, 0, UpperRange);
  const auto h1 = make_unique<TH1F>("h1", "", nbins, 0, UpperRange);
  const auto h_generator = make_unique<TH1F>("h_generator", "", nbins, 0, UpperRange);
  const auto h_neutrons = make_unique<TH1F>("h_neutrons", "", nbins, 0, UpperRange);
  const auto h_gammas = make_unique<TH1F>("h_gammas", "", nbins, 0, UpperRange);

  double xmin = -1500.;
  double xmax = 1500.;
  double ymin = -2500.;
  double ymax = 3000.;
  
  const auto h2_DepthFirstHit = make_unique<TH2F>("h2_DepthFirstHit", "", nbins, xmin, xmax, nbins, ymin, ymax);
  const auto h2_Depth = make_unique<TH2F>("h2_Depth", "", nbins, xmin, xmax, nbins, ymin, ymax);
  const auto h2_DepthEnergyFirstHit = make_unique<TH2F>("h2_DepthEnergyFirstHit", "", nbins, ymin, ymax, nbins, 0, UpperRange);
  const auto h2_DepthEnergy = make_unique<TH2F>("h2_DepthEnergy", "", nbins, ymin, ymax, nbins, 0, UpperRange);

  const auto h_multiplicity = make_unique<TH1F>("h_multiplicity", "", nbins, 0, 10);

  // Create output file for debugging
  ostringstream ss;
  ss << "TxtFiles_SelectedEvents/Simus_" << PrimaryParticleType.Data() << "_" << setprecision(3) << PrimaryEnergy << "MeV_BWater"
     << to_string(BWaterThickness) << "mm_Threshold" << setprecision(3) << DetectionThreshold << "keV_SelectedEvents_Sensitive_" << SelectedVolumes.c_str() << ".txt";

  // Loop through events
  bool EventSelection = false; 

  double Attenuation = 0.0;
  double AttenuationNeutron = 0.0;
  double AttenuationGenerator = 0.0;
  
  int counter = 0;
  int counter_selected = 0;
  int counter_generator = 0;
  int counter_neutrons = 0;
  int counter_gammas = 0;


  // Create output files
  const auto Threshold_vs_Rate = make_unique<ofstream>(); 
  const auto Thickness_vs_AttenuationAllPart = make_unique<ofstream>();
  const auto Thickness_vs_Attenuation = make_unique<ofstream>();
  const auto Thickness_vs_AttenuationGenerator = make_unique<ofstream>();

  bool IsGenerator = false;
  bool IsNeutron = false;
  bool IsGamma = false;

  int Total_number_ev_loop = 1000; // for tests
  // int Total_number_ev_loop = run->GetEntries(); // total number of events in the run

  // Loop over simulated events
  for (size_t i = 0; i < Total_number_ev_loop; i++)
    {

      // cout << "\nevent " << i << endl;

      // Get current event from the simulation data
      run->GetEntry(i);
    
      size_t numberOfTracks = event->GetNumberOfTracks();
      Double_t aHitTime = 1.e6;
    
      IsGenerator = false;
      IsNeutron = false;
      IsGamma = false;
	
      // Check if the event is selected based on the SelectedVolumes option and the DetectionThreshold
      bool checkDetectionThreshold = (DetectionThreshold == 0);
      bool EventSelection = false;

      // Attention ici la fonction GetFirstPositionInVolume() a les volumes ID inverses!!! A voir avec les gens de REST

      // Select events that deposited energy only in the Internal Detector (ID) or that deposited energy in both ID and OD, but with energy below the DetectionThreshold
      if (SelectedVolumes == "ID")
	EventSelection = (isnan(event->GetFirstPositionInVolume(SensitiveVolumeID).X()) && !isnan(event->GetFirstPositionInVolume(ActiveVolumeID).X())) || 
	  ((!isnan(event->GetFirstPositionInVolume(ActiveVolumeID).X()) && !isnan(event->GetFirstPositionInVolume(SensitiveVolumeID).X())) && event->GetEnergyDepositedInVolume(ActiveVolumeID) < DetectionThreshold);
      
      // Select events that deposited energy only in the Outer Detector (OD)
      else if (SelectedVolumes == "OD")
	EventSelection = checkDetectionThreshold && isnan(event->GetFirstPositionInVolume(ActiveVolumeID).X()) && !isnan(event->GetFirstPositionInVolume(SensitiveVolumeID).X());
      
      // Select events that deposited energy either in ID or in OD
      else if (SelectedVolumes == "or")
	EventSelection = checkDetectionThreshold && (!isnan(event->GetFirstPositionInVolume(ActiveVolumeID).X()) || !isnan(event->GetFirstPositionInVolume(SensitiveVolumeID).X()));
      
      // Select events that deposited energy both in ID and in OD, with energy above the DetectionThreshold, or select events that deposited energy only in ID with energy above the DetectionThreshold
      else if (SelectedVolumes == "and")
	EventSelection = (!checkDetectionThreshold && !isnan(event->GetFirstPositionInVolume(ActiveVolumeID).X()) && !isnan(event->GetFirstPositionInVolume(SensitiveVolumeID).X())) || 
	  (checkDetectionThreshold && !isnan(event->GetFirstPositionInVolume(ActiveVolumeID).X()) && !isnan(event->GetFirstPositionInVolume(SensitiveVolumeID).X()) && event->GetEnergyDepositedInVolume(ActiveVolumeID) > DetectionThreshold);
      
      // Select events that did not deposit energy in any volume
      else if (SelectedVolumes == "none")
	EventSelection = false;

      else
	{
	
	  // Invalid SelectedVolumes option, print possible options and return error code
	  cout << "Wrong selected volume name! Possibilities are" << "\n";
	  cout << "-\"ID\" for selecting Sensitive only events," << "\n";
	  cout << "  -> for Sensitive only events with an energy detection threshold in the Armor, please set the DetectionThreshold argument different of 0 (keV)." << "\n"; 
	  cout << "-\"OD\" for selecting BWater only events," << "\n";
	  cout << "-\"or\" for selecting Sensitive OR BWater events," << "\n";
	  cout << "-\"and\" for selecting Sensitive AND BWater events," << "\n";
	  cout << "-\"none\" for selecting events not depositing energy in any volume." << "\n"; 
	  return 6;
      
	}

      
      // for the "or" selection, counter will be slightly different from Total_number_ev_loop 
      // for some events an interaction occurs before the first active volume, on the air molaciles (N14 I think here)
      // So for the moment I do this method, but I should pay attention to that for the more global studies
      // Also because I put the sensitive volume as the second volume and then reccord all events == true.
      // But I don't think I can do differently because I want my two volumes to be sensitive (trigger volumes), but apparently this is not possible with REST.   
      if (EventSelection) {

	// a revoir pcq mtn counter_selected depend aussi de la multiplicite
	// Print progress and selection info every 1000 events
	if (i % 1000 == 0) {
	  cout << setprecision(3) << "\nProgression... " << ((double)i/Total_number_ev_loop)*100. << " %" << " (" << ((double)i/run->GetEntries())*100. << " % of total)" << "\n";
	  cout << counter_selected << " events selected so far (" << ((double)counter_selected/i)*100 << " % selection)\n" << "\n";
	}

	int BWaterSensitiveTransportationMultiplicity = 0;
  
	vector<vector<int>> aSensitiveTrackHitCollection;

	// Create a map to associate trackIndex with trackID
	map<int, int> trackIDToNumberMap;

	for (int trackIndex=0; trackIndex<event->GetNumberOfTracks(); trackIndex++) 
	  // for (int trackIndex=0; trackIndex<5; trackIndex++)
	  {

	    const TRestGeant4Track aTrack = event->GetTrack(trackIndex);
	    const TRestGeant4Hits aHitCollection = aTrack.GetHits(); 

	    // key trackID, value trackIndex
	    trackIDToNumberMap[aTrack.GetTrackID()] = trackIndex;
      
	    for (int hitIndex=0; hitIndex<aTrack.GetNumberOfHits(); hitIndex++)
	      {

		TString hitVolume = geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(aHitCollection.GetHitVolume(hitIndex));

		h2_DepthEnergy->Fill(aHitCollection.GetZ(hitIndex), aHitCollection.GetEnergy(hitIndex) / 1.e3);
		h2_Depth->Fill(event->GetTrack(trackIndex).GetHits().GetX(hitIndex), event->GetTrack(trackIndex).GetHits().GetZ(hitIndex));
		
		// Selection on existing transportation process in the track
		if (aTrack.GetProcessName(aHitCollection.GetHitProcess(hitIndex)) == "Transportation"
		    && geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(aHitCollection.GetHitVolume(hitIndex)) == "BWater"
		    && geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(aHitCollection.GetHitVolume(hitIndex + 1)) == "Sensitive")
		  {

		    BWaterSensitiveTransportationMultiplicity++;
		    
		    aSensitiveTrackHitCollection.push_back({trackIndex, hitIndex});
	      
		  } // end if condition on transportation BWater -> Sensitive

	      }

	  }
	
	vector<vector<int>> trackHitVector;

	// If up to one hit in the Sensitive volume
	if (BWaterSensitiveTransportationMultiplicity <= 1)
	  {
	    // Fill trackHitVector with the content of aSensitiveTrackHitCollection
	    trackHitVector.assign(aSensitiveTrackHitCollection.begin(), aSensitiveTrackHitCollection.end());

 	  }
	  
	// If there is more than one hit
	else
	  {
	    
	    // check is the tracks reaching the sensitive volume are related or not
	    
	    checkTrackRelation(aSensitiveTrackHitCollection, *event, trackIDToNumberMap, trackHitVector);

	    BWaterSensitiveTransportationMultiplicity = trackHitVector.size();
	    
	  } // end of if condition if more than one hit
	
	h_multiplicity->Fill(BWaterSensitiveTransportationMultiplicity);
	
	if (BWaterSensitiveTransportationMultiplicity)
	  {
	    // a deplacer pcq le vecteur trackHitVector depend aussi de la multiplicite
	    // probablement mettre un bool dans la boucle sur les track/hit avec transportation, et quand true, counter_selected++
	    // ou alors juste ava,t cette boucle, mettre un if multiplicity > 0, counter_selected++
	    counter_selected++;
	    
	  }
	
	// cout << "Multiplicity " << BWaterSensitiveTransportationMultiplicity << endl;
	
	// cout << "event " << i << endl;

	// dans cette loop on ne va tourner que sur les ev qui ont depose de l'energie dans le Sensitive
	for (int i = 0; i < trackHitVector.size(); ++i) {
	  int trackNumber = trackHitVector[i][0];
	  int hitNumber = trackHitVector[i][1];
	  
	  // cout << "-------------------" << endl;
	  // cout << " * TrackID: " << event->GetTrack(trackNumber).GetTrackID()
	  //      << " - Particle: " << event->GetTrack(trackNumber).GetParticleName()
	  //      << " - ParentID: " << event->GetTrack(trackNumber).GetParentID()
	  //      << (event->GetTrack(trackNumber).GetParentTrack() != nullptr ? TString::Format(" - Parent particle: %s", event->GetTrack(trackNumber).GetParentTrack()->GetParticleName().Data()).Data() : "")
	  //      << " - Created by '" << event->GetTrack(trackNumber).GetCreatorProcess()
	  //      << "' with initial KE of " << ToEnergyString(event->GetTrack(trackNumber).GetInitialKineticEnergy()) << endl;
	  // cout << "   Initial position " << VectorToString(event->GetTrack(trackNumber).GetInitialPosition())
	  //      << " at time " << ToTimeString(event->GetTrack(trackNumber).GetGlobalTime())
	  //      << " - Time length of " << ToTimeString(event->GetTrack(trackNumber).GetTimeLength())
	  //      << " and spatial length of " << ToLengthString(event->GetTrack(trackNumber).GetLength()) << endl;

	  // cout << "      - Hit " << hitNumber
	  //      << " - Energy: " << ToEnergyString(event->GetTrack(trackNumber).GetHits().GetEnergy(hitNumber))
	  //      << " - Process: " << event->GetTrack(trackNumber).GetProcessName(event->GetTrack(trackNumber).GetHits().GetHitProcess(hitNumber))
	  //      << " - Volume: " << geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(event->GetTrack(trackNumber).GetHits().GetHitVolume(hitNumber))
	  //      << " - Position: (" << VectorToString(TVector3(event->GetTrack(trackNumber).GetHits().GetX(hitNumber),event->GetTrack(trackNumber).GetHits().GetY(hitNumber),event->GetTrack(trackNumber).GetHits().GetZ(hitNumber)))
	  //      << " - Time: " << ToTimeString(event->GetTrack(trackNumber).GetHits().GetTime(hitNumber))
	  //      << " - KE: " << ToEnergyString(event->GetTrack(trackNumber).GetHits().GetKineticEnergy(hitNumber)) << endl;
	  // cout << "-------------------" << endl;

	  // a deplacer, ca n'a aucun sens de mettre ca la
	  // mais a regarder: il y a probebelemnt un bug dns la selection des ev pcq dans lhisto on voit une barre verticale qui ne devrait pas etre la,
	  // tous les ev devraient etre sur linterface BWater/scintillateur
	  // h2_DepthEnergyFirstHit->Fill(event->GetTrack(trackNumber).GetHits().GetZ(hitNumber), event->GetTrack(trackNumber).GetHits().GetEnergy(hitNumber) / 1.e3);
	  // h2_DepthFirstHit->Fill(event->GetTrack(trackNumber).GetHits().GetX(hitNumber), event->GetTrack(trackNumber).GetHits().GetZ(hitNumber));
	  
	  // Fill 1D histogram to store energy deposited in Sensitive
	  h0->Fill(event->GetEnergyDepositedInVolume(SensitiveVolumeID) / 1000.);

	  // Fill 1D histogram to store energy deposited in BWater
	  h1->Fill(event->GetEnergyDepositedInVolume(ActiveVolumeID)/1000.);

	  // Selection on particle type

	  // Select events were the primary neutron deposits energy directly in the Sensitive volume:
	  if (event->GetTrack(trackNumber).GetParentID() == 0)
	    {
	      counter_generator++;
	      IsGenerator = true;
	      h_generator->Fill(event->GetEnergyDepositedInVolume(SensitiveVolumeID) / 1000.);
	      
	      // cout << "generator particle" << endl;
	    }
	  
	  else
	    {

	      // Select secondary neutrons interacting in Sensitive volume
	      if (event->GetTrack(trackNumber).GetParticleName() == "neutron")
		{
		  counter_neutrons++;
		  IsNeutron = true;
		  h_neutrons->Fill(event->GetEnergyDepositedInVolume(SensitiveVolumeID) / 1000.);
	  
		  // cout << "particle " << event->GetTrack(trackNumber).GetParticleName() << endl;
		}
		    
	      // Select secondary gammas interacting in Sensitive volume
	      else if (event->GetTrack(trackNumber).GetParticleName() == "gamma")
		{
		  counter_gammas++;
		  IsGamma = true;
		  h_gammas->Fill(event->GetEnergyDepositedInVolume(SensitiveVolumeID) / 1000.);

		  // cout << "particle " << event->GetTrack(trackNumber).GetParticleName() << endl;
		}
			    
	    } // end if condition on selection on particle type

	  
	}

	
      } // end if condition on EventSelection

      else if (isnan(event->GetFirstPositionInVolume(ActiveVolumeID).X()) && isnan(event->GetFirstPositionInVolume(SensitiveVolumeID).X())) {
	// Increment counter for events not depositing energy in any active volume 
	++counter;
      }

    } // end for loop on events

  cout << "\n\nevents interacting before the BWater volume " << counter << " on total events " << Total_number_ev_loop << endl;

  // Correcting the total number of events from events not depositing energy in any volume
  Total_number_ev_loop -= counter;
  cout << "new total events " << Total_number_ev_loop << endl;
  cout << "total selection " << ((double)counter_selected/Total_number_ev_loop)*100 << "%" << "\n\n";
  
  // Calculate selection rate and mean total energy
  Attenuation = 1-((double) counter_selected / Total_number_ev_loop);
  AttenuationNeutron = 1-((double) (counter_neutrons + counter_generator) / Total_number_ev_loop);
  AttenuationGenerator = 1-((double) (counter_generator) / Total_number_ev_loop);
	  
  const double Var_Attenuation = sqrt(Attenuation * (1 - Attenuation) / Total_number_ev_loop); 

  // Save attenuation all types of particle vs. borated water layer thickness to file
  Thickness_vs_AttenuationAllPart->open("TxtFiles_Thickness_vs_AttenuationAllPart/Thickness_vs_AttenuationAllPart.txt", ofstream::app);
  if (!Thickness_vs_AttenuationAllPart->is_open()) {
    cerr << "File Thickness_vs_AttenuationAllPart did not open!\n";
    return 6;
  }
  *Thickness_vs_AttenuationAllPart << BWaterThickness << " " << Attenuation << " " << Var_Attenuation << "\n";
  Thickness_vs_AttenuationAllPart->close();

  // Save attenuation vs. borated water layer thickness to file
  Thickness_vs_Attenuation->open("TxtFiles_Thickness_vs_Attenuation/Thickness_vs_Attenuation.txt", ofstream::app);
  if (!Thickness_vs_Attenuation->is_open()) {
    cerr << "File Thickness_vs_Attenuation did not open!\n";
    return 6;
  }
  *Thickness_vs_Attenuation << BWaterThickness << " " << AttenuationNeutron << " " << "\n";
  Thickness_vs_Attenuation->close();

  // Save neutron generator attenuation rate vs. borated water layer thickness to file
  Thickness_vs_AttenuationGenerator->open("TxtFiles_Thickness_vs_AttenuationGenerator/Thickness_vs_AttenuationGenerator.txt", ofstream::app);
  if (!Thickness_vs_AttenuationGenerator->is_open()) {
    cerr << "File Thickness_vs_AttenuationGenerator did not open!\n";
    return 6;
  }
  *Thickness_vs_AttenuationGenerator << BWaterThickness << " " << AttenuationGenerator << " " << "\n";
  Thickness_vs_AttenuationGenerator->close();

  // Generate output file names and save histograms
  string OutputRootFileName_Sensitive = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, WaterOnly, DetectionThreshold, SelectedVolumes.c_str(), "Sensitive");
  h0->SaveAs(OutputRootFileName_Sensitive.c_str());

  string OutputRootFileName_BWater = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, WaterOnly, DetectionThreshold, SelectedVolumes.c_str(), "BWater");
  h1->SaveAs(OutputRootFileName_BWater.c_str());

  string OutputRootFileName_DepthFirstHit = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, WaterOnly, DetectionThreshold, SelectedVolumes.c_str(), "DepthFirstHit");
  h2_DepthFirstHit->SaveAs(OutputRootFileName_DepthFirstHit.c_str());

  string OutputRootFileName_Depth = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, WaterOnly, DetectionThreshold, SelectedVolumes.c_str(), "Depth");
  h2_Depth->SaveAs(OutputRootFileName_Depth.c_str());

  string OutputRootFileName_DepthEnergyFirstHit = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, WaterOnly, DetectionThreshold, SelectedVolumes.c_str(), "DepthEnergyFirstHit");
  h2_DepthEnergyFirstHit->SaveAs(OutputRootFileName_DepthEnergyFirstHit.c_str());
	  
  string OutputRootFileName_DepthEnergy = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, WaterOnly, DetectionThreshold, SelectedVolumes.c_str(), "DepthEnergy");
  h2_DepthEnergy->SaveAs(OutputRootFileName_DepthEnergy.c_str());
	  
  string OutputRootFileName_generator = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, WaterOnly, DetectionThreshold, SelectedVolumes.c_str(), "generator");
  h_generator->SaveAs(OutputRootFileName_generator.c_str());

  string OutputRootFileName_neutrons = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, WaterOnly, DetectionThreshold, SelectedVolumes.c_str(), "neutrons");
  h_neutrons->SaveAs(OutputRootFileName_neutrons.c_str());

  string OutputRootFileName_gammas = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, WaterOnly, DetectionThreshold, SelectedVolumes.c_str(), "gammas");
  h_gammas->SaveAs(OutputRootFileName_gammas.c_str());

  string OutputRootFileName_multiplicity = generateOutputFileName(PrimaryParticleType.Data(), PrimaryEnergy, BWaterThickness, WaterOnly, DetectionThreshold, SelectedVolumes.c_str(), "multiplicity");
  h_multiplicity->SaveAs(OutputRootFileName_multiplicity.c_str());

  // Save execution time to file
  time(&end);
  double time_taken = double(end - start);
  ofstream Execution_time("Execution_time.txt", ofstream::app);
  Execution_time << time_taken << setprecision(5) << "\n";
  Execution_time.close();
	    
  return 0;
}
