// SelectOneEvent("../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/RestG4_RootOutputFiles/RunArmor_neutrons_1MeV_BWater200_restG4_SensVol_lsAMT_10-7ev.root")

void SelectOneEvent(const string& fName, int entry=0){//const std::string& fName
  
  TRestRun run(fName);

  cout << "Run number " << run.GetRunNumber() << endl;
  
  TRestGeant4Event* event = run.GetInputEvent<TRestGeant4Event>();

  double nEvents = run.GetEntries();

  cout << "Number of events " << nEvents << endl;

  cout << "Testing reading of Geant4 metadata class" << endl;
  TRestGeant4Metadata* geant4Metadata = (TRestGeant4Metadata*)run.GetMetadataClass("TRestGeant4Metadata");
  if (!geant4Metadata)
    {
      
      cout << "Problem reading Geant4 metadata class!" << endl;
      return 6;

    }
  
  // geant4Metadata->PrintMetadata();
  
  vector< TString > VActiveVolumes = geant4Metadata->GetActiveVolumes();
  cout << VActiveVolumes.size() << " active volume(s)" << ": " << endl;
  
  for (size_t i = 0; i < VActiveVolumes.size(); i++)
    {
      
      cout << "ID " << geant4Metadata->GetActiveVolumeID(VActiveVolumes[i]) << " name " << VActiveVolumes[i] << endl ;

    }
  cout << endl;

  int SensitiveVolumeID = geant4Metadata->GetActiveVolumeID(geant4Metadata->GetSensitiveVolume());
  int ActiveVolumeID = geant4Metadata->GetActiveVolumeID("BWater");

  run.GetEntry(entry);

  cout << "Number of tracks " << event->GetNumberOfTracks() << "\n\n";

  bool IsFirstHitInVolumes = false;
  bool IsFirstHitInSensitiveVolume = false;


  int M_Transportation = 0;

  vector<int> aSensitiveTrackCollection;
  vector<int> aSensitiveHitCollection;

  for (int trackIndex=0; trackIndex<event->GetNumberOfTracks(); trackIndex++) 
    // for (int trackIndex=0; trackIndex<5; trackIndex++)
    {

      IsFirstHitInVolumes = false;
      IsFirstHitInSensitiveVolume = false;

      const TRestGeant4Track aTrack = event->GetTrack(trackIndex);
      const TRestGeant4Hits aHitCollection = aTrack.GetHits(); 

      // cout << " * TrackID: " << aTrack.GetTrackID()
      // 	   << " - Particle: " << aTrack.GetParticleName()
      // 	   << " - ParentID: " << aTrack.GetParentID()
      // 	   << (aTrack.GetParentTrack() != nullptr ? TString::Format(" - Parent particle: %s", aTrack.GetParentTrack()->GetParticleName().Data()).Data() : "")
      // 	   << " - Created by '" << aTrack.GetCreatorProcess()
      // 	   << "' with initial KE of " << ToEnergyString(aTrack.GetInitialKineticEnergy()) << endl;
      // cout << "   Initial position " << VectorToString(aTrack.GetInitialPosition())
      // 	   << " at time " << ToTimeString(aTrack.GetGlobalTime())
      // 	   << " - Time length of " << ToTimeString(aTrack.GetTimeLength())
      // 	   << " and spatial length of " << ToLengthString(aTrack.GetLength()) << endl;

      for (int hitIndex=0; hitIndex<aTrack.GetNumberOfHits(); hitIndex++)
	{

	  TString hitVolume = geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(aHitCollection.GetHitVolume(hitIndex));

	  // Selection on existing transportation process in the track
	  if (aTrack.GetProcessName(aHitCollection.GetHitProcess(hitIndex)) == "Transportation"
	      && geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(aHitCollection.GetHitVolume(hitIndex)) == "BWater"
	      && geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(aHitCollection.GetHitVolume(hitIndex + 1)) == "Sensitive")
	    {

	      M_Transportation++;
	      
	      cout << "-------------------" << endl;

	      cout << " * TrackID: " << aTrack.GetTrackID()
		   << " - Particle: " << aTrack.GetParticleName()
		   << " - ParentID: " << aTrack.GetParentID()
		   << (aTrack.GetParentTrack() != nullptr ? TString::Format(" - Parent particle: %s", aTrack.GetParentTrack()->GetParticleName().Data()).Data() : "")
		   << " - Created by '" << aTrack.GetCreatorProcess()
		   << "' with initial KE of " << ToEnergyString(aTrack.GetInitialKineticEnergy()) << endl;
	      cout << "   Initial position " << VectorToString(aTrack.GetInitialPosition())
		   << " at time " << ToTimeString(aTrack.GetGlobalTime())
		   << " - Time length of " << ToTimeString(aTrack.GetTimeLength())
		   << " and spatial length of " << ToLengthString(aTrack.GetLength()) << endl;

	      cout << "      - Hit " << hitIndex
		   << " - Energy: " << ToEnergyString(aHitCollection.GetEnergy(hitIndex))
		   << " - Process: " << aTrack.GetProcessName(aHitCollection.GetHitProcess(hitIndex))
		   << " - Volume: " << hitVolume
		   << " - Position: (" << VectorToString(TVector3(aHitCollection.GetX(hitIndex),aHitCollection.GetY(hitIndex),aHitCollection.GetZ(hitIndex)))
		   << " - Time: " << ToTimeString(aHitCollection.GetTime(hitIndex))
		   << " - KE: " << ToEnergyString(aHitCollection.GetKineticEnergy(hitIndex)) << endl;

	      cout << "-------------------" << endl;

	      aSensitiveTrackCollection.push_back(trackIndex);
	      aSensitiveHitCollection.push_back(hitIndex);
	      
	    } // end if condition on transportation BWater -> Sensitive

	}

    }

  cout << "Multiplicity " << M_Transportation << endl;

  if (M_Transportation == 0)
    cout << "No hit reached Sensitive volume" << endl;

  else if (M_Transportation == 1)
    {

      cout << "There is only one hit reaching the Sensitive volume" << endl;
      
    }

  else
    {

      cout << "Checking other hits..." << endl;
      
      unordered_map<int, vector<int>> indexMap;
      vector<int> nonRepeatingNumbers;
      vector<int> nonRepeatingIndices;

      int smallestHit = numeric_limits<int>::max();

      // Count the occurrences and store the indices
      for (int i = 0; i < aSensitiveTrackCollection.size(); ++i)
	{

	  indexMap[aSensitiveTrackCollection[i]].push_back(i);

	  // to handle non repeating integers
	  if (indexMap[aSensitiveTrackCollection[i]].size() == 1)
	    {
	      
	      nonRepeatingNumbers.push_back(aSensitiveTrackCollection[i]);
	      nonRepeatingIndices.push_back(i);

	    }
	  
	  else if (indexMap[aSensitiveTrackCollection[i]].size() == 2)
	    {
	      
	      auto it = find(nonRepeatingNumbers.begin(), nonRepeatingNumbers.end(), aSensitiveTrackCollection[i]);
	      
	      if (it != nonRepeatingNumbers.end())
		{
		
		  nonRepeatingNumbers.erase(it);
		  nonRepeatingIndices.erase(nonRepeatingIndices.begin() + distance(nonRepeatingNumbers.begin(), it));
	      
		}
	      
	    }

	}
      
      // Identifying repeating track IDs, and selectionning the smallestHit hit ID
      for (const auto& pair : indexMap)
	{
	  
	  if (pair.second.size() > 1)
	    {

	      cout << "-------------------" << endl;

	      cout << " * TrackID: " << event->GetTrack(pair.first).GetTrackID()
		   << " - Particle: " << event->GetTrack(pair.first).GetParticleName()
		   << " - ParentID: " << event->GetTrack(pair.first).GetParentID()
		   << (event->GetTrack(pair.first).GetParentTrack() != nullptr ? TString::Format(" - Parent particle: %s", event->GetTrack(pair.first).GetParentTrack()->GetParticleName().Data()).Data() : "")
		   << " - Created by '" << event->GetTrack(pair.first).GetCreatorProcess()
		   << "' with initial KE of " << ToEnergyString(event->GetTrack(pair.first).GetInitialKineticEnergy()) << endl;
	      cout << "   Initial position " << VectorToString(event->GetTrack(pair.first).GetInitialPosition())
		   << " at time " << ToTimeString(event->GetTrack(pair.first).GetGlobalTime())
		   << " - Time length of " << ToTimeString(event->GetTrack(pair.first).GetTimeLength())
		   << " and spatial length of " << ToLengthString(event->GetTrack(pair.first).GetLength()) << endl;

	      // cout << pair.first << " at indices: ";

	      for (int index : pair.second)
		{
		  
		  if (aSensitiveHitCollection[index] < smallestHit)
		    {

		      smallestHit = aSensitiveHitCollection[index];

		    }
		      
		}
	      
	      cout << "      - Hit " << smallestHit
		   << " - Energy: " << ToEnergyString(event->GetTrack(pair.first).GetHits().GetEnergy(smallestHit))
		   << " - Process: " << event->GetTrack(pair.first).GetProcessName(event->GetTrack(pair.first).GetHits().GetHitProcess(smallestHit))
		   << " - Volume: " << geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(event->GetTrack(pair.first).GetHits().GetHitVolume(smallestHit))
		   << " - Position: (" << VectorToString(TVector3(event->GetTrack(pair.first).GetHits().GetX(smallestHit),event->GetTrack(pair.first).GetHits().GetY(smallestHit),event->GetTrack(pair.first).GetHits().GetZ(smallestHit)))
		   << " - Time: " << ToTimeString(event->GetTrack(pair.first).GetHits().GetTime(smallestHit))
		   << " - KE: " << ToEnergyString(event->GetTrack(pair.first).GetHits().GetKineticEnergy(smallestHit)) << endl;

	      cout << "-------------------" << endl;

	    }
	
	}

      // Output non-repeating integers and their indices
      cout << "Non-repeating integers and their indices: " << endl;
      for (int i = 0; i < nonRepeatingNumbers.size(); ++i)
	{
	  
	  cout << " * TrackID: " << event->GetTrack(nonRepeatingNumbers[i]).GetTrackID();
	  cout << " hit index: " << nonRepeatingIndices[aSensitiveHitCollection[i]] << endl;
	  
	}

    }
  
  // event->PrintEvent(2);
    
  return 0;
}


