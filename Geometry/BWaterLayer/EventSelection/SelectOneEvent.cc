// SelectOneEvent("../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/RestG4_RootOutputFiles/RunArmor_neutrons_1MeV_BWater200_restG4_SensVol_lsAMT_10-7ev.root",0)

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

void SelectOneEvent(const string& fName, int entry=0){//const string& fName
  
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

  int BWaterSensitiveTransportationMultiplicity = 0;
  
  vector<vector<int>> aSensitiveTrackHitCollection;

  // Create a map to associate trackIndex with trackID
  map<int, int> trackIDToNumberMap;

  for (int trackIndex=0; trackIndex<event->GetNumberOfTracks(); trackIndex++) 
    // for (int trackIndex=0; trackIndex<5; trackIndex++)
    {

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

      // key trackID, value trackIndex
      trackIDToNumberMap[aTrack.GetTrackID()] = trackIndex;
      
      for (int hitIndex=0; hitIndex<aTrack.GetNumberOfHits(); hitIndex++)
	{

	  TString hitVolume = geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(aHitCollection.GetHitVolume(hitIndex));

	  // Selection on existing transportation process in the track
	  if (aTrack.GetProcessName(aHitCollection.GetHitProcess(hitIndex)) == "Transportation"
	      && geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(aHitCollection.GetHitVolume(hitIndex)) == "BWater"
	      && geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(aHitCollection.GetHitVolume(hitIndex + 1)) == "Sensitive")
	    {

	      BWaterSensitiveTransportationMultiplicity++;
	      
	      // cout << "-------------------" << endl;

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

	      // cout << "      - Hit " << hitIndex
	      // 	   << " - Energy: " << ToEnergyString(aHitCollection.GetEnergy(hitIndex))
	      // 	   << " - Process: " << aTrack.GetProcessName(aHitCollection.GetHitProcess(hitIndex))
	      // 	   << " - Volume: " << hitVolume
	      // 	   << " - Position: (" << VectorToString(TVector3(aHitCollection.GetX(hitIndex),aHitCollection.GetY(hitIndex),aHitCollection.GetZ(hitIndex)))
	      // 	   << " - Time: " << ToTimeString(aHitCollection.GetTime(hitIndex))
	      // 	   << " - KE: " << ToEnergyString(aHitCollection.GetKineticEnergy(hitIndex)) << endl;

	      // cout << "-------------------" << endl;

	      // aSensitiveTrackCollection.push_back(trackIndex);
	      // aSensitiveHitCollection.push_back(hitIndex);
	      aSensitiveTrackHitCollection.push_back({trackIndex, hitIndex});
	      
	    } // end if condition on transportation BWater -> Sensitive

	}

    }

  cout << "\nMultiplicity " << BWaterSensitiveTransportationMultiplicity << endl;

  // If no hits in the Sensitive volume
  if (BWaterSensitiveTransportationMultiplicity == 0)
    cout << "No hit reached Sensitive volume" << endl;

  // If there is only one hit
  else if (BWaterSensitiveTransportationMultiplicity == 1)
    {
      cout << "There is only one hit reaching the Sensitive volume" << endl;
    }

  // If there is more than one hit
  else
    {

      // Usage:
      vector<vector<int>> trackHitVector;

      checkTrackRelation(aSensitiveTrackHitCollection, *event, trackIDToNumberMap, trackHitVector);

      BWaterSensitiveTransportationMultiplicity = trackHitVector.size();
      
      // cout << "-------------------" << endl;
      // cout << " * TrackID: " << event->GetTrack(trackNumber).GetTrackID()
      // 	   << " - Particle: " << event->GetTrack(trackNumber).GetParticleName()
      // 	   << " - ParentID: " << event->GetTrack(trackNumber).GetParentID()
      // 	   << (event->GetTrack(trackNumber).GetParentTrack() != nullptr ? TString::Format(" - Parent particle: %s", event->GetTrack(trackNumber).GetParentTrack()->GetParticleName().Data()).Data() : "")
      // 	   << " - Created by '" << event->GetTrack(trackNumber).GetCreatorProcess()
      // 	   << "' with initial KE of " << ToEnergyString(event->GetTrack(trackNumber).GetInitialKineticEnergy()) << endl;
      // cout << "   Initial position " << VectorToString(event->GetTrack(trackNumber).GetInitialPosition())
      // 	   << " at time " << ToTimeString(event->GetTrack(trackNumber).GetGlobalTime())
      // 	   << " - Time length of " << ToTimeString(event->GetTrack(trackNumber).GetTimeLength())
      // 	   << " and spatial length of " << ToLengthString(event->GetTrack(trackNumber).GetLength()) << endl;

      // cout << "      - Hit " << hitNumber
      // 	   << " - Energy: " << ToEnergyString(event->GetTrack(trackNumber).GetHits().GetEnergy(hitNumber))
      // 	   << " - Process: " << event->GetTrack(trackNumber).GetProcessName(event->GetTrack(trackNumber).GetHits().GetHitProcess(hitNumber))
      // 	   << " - Volume: " << geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(event->GetTrack(trackNumber).GetHits().GetHitVolume(hitNumber))
      // 	   << " - Position: (" << VectorToString(TVector3(event->GetTrack(trackNumber).GetHits().GetX(hitNumber),event->GetTrack(trackNumber).GetHits().GetY(hitNumber),event->GetTrack(trackNumber).GetHits().GetZ(hitNumber)))
      // 	   << " - Time: " << ToTimeString(event->GetTrack(trackNumber).GetHits().GetTime(hitNumber))
      // 	   << " - KE: " << ToEnergyString(event->GetTrack(trackNumber).GetHits().GetKineticEnergy(hitNumber)) << endl;
      // cout << "-------------------" << endl;
      
    } // end of if condition if more than one hit
  
  cout << "\nMultiplicity " << BWaterSensitiveTransportationMultiplicity << endl;
  
  event->PrintEvent();
    
  return 0;
}



      

      
// // beginning of algorithm /////////////////////////////////////////////////////////////////////

      
// unordered_map<int, vector<int>> trackHitMap;             // Map to store track IDs and their corresponding hit numbers
// vector<int> nonRepeatingTrackIDs;                        // Vector to store track IDs that do not repeat
// int smallestHitNumber = numeric_limits<int>::max();      // Initialize the smallest hit number to the maximum possible value
// vector<vector<int>> trackHitVector;                      // Stores the Track (and corresponding hit) for which we will check their affiliation

// // Count the occurrences and store the indices
// for (const auto& pair : aSensitiveTrackHitCollection)
// 	{
// 	  int trackNumber = pair[0];        // Get the track ID from the pair
// 	  int hitNumber = pair[1];      // Get the hit number from the pair

// 	  if (trackHitMap.count(trackNumber) == 0)
// 	    {
// 	      // If the track ID is not present in the map, add it with the hit number as the first entry
// 	      trackHitMap[trackNumber] = { hitNumber };

// 	      // Add the track ID to the non-repeating track IDs vector
// 	      nonRepeatingTrackIDs.push_back(trackNumber);     
// 	    }
// 	  else
// 	    {
// 	      // If the track ID is already present, add the hit number to its list of hit numbers
// 	      trackHitMap[trackNumber].push_back(hitNumber);
// 	    }
// 	}

// // Print the repeating track IDs and their hit numbers
// for (const auto& pair : trackHitMap)
// 	{
// 	  int trackNumber = pair.first;                    // Get the track ID
// 	  const vector<int>& hitNumbers = pair.second;     // Get the vector of hit numbers

// 	  if (hitNumbers.size() > 1)
// 	    {
// 	      // If the track ID has more than one hit number, iterate through the hit numbers
// 	      for (int hitNumber : hitNumbers)
// 		{
// 		  if (hitNumber < smallestHitNumber)
// 		    {
// 		      // Update the smallest hit number if a smaller value is found
// 		      smallestHitNumber = hitNumber;        
// 		    }
// 		}
// 	    }
// 	}

// // Find the track IDs with the smallest hit number among the repeating track IDs, and store it in trackHitVector
// for (const auto& pair : trackHitMap)
// 	{
// 	  int trackNumber = pair.first;                     // Get the track ID
// 	  const vector<int>& hitNumbers = pair.second;      // Get the vector of hit numbers
	  
// 	  if (hitNumbers.size() > 1 && find(hitNumbers.begin(), hitNumbers.end(), smallestHitNumber) != hitNumbers.end())
// 	    {
// 	      // If the track ID has more than one hit number and the smallest hit number is present
// 	      trackHitVector.push_back({trackNumber, smallestHitNumber});

// 	      // Stop searching after finding the first track ID with the smallest hit number
// 	      break;                        
// 	    }
// 	}
      
// // Store the non-repeating track IDs and their hit numbers in trackHitVector
// for (int trackNumber : nonRepeatingTrackIDs)
// 	{
// 	  const vector<int>& hitNumbers = trackHitMap[trackNumber];     // Get the vector of hit numbers for the track ID

// 	  if (hitNumbers.size() == 1)
// 	    {
// 	      trackHitVector.push_back({trackNumber, hitNumbers[0]});
// 	    }
// 	}

// for (int i = 0; i < trackHitVector.size(); ++i) {
// 	int trackNumber = trackHitVector[i][0];
// 	int hitNumber = trackHitVector[i][1];
// 	int trackID = event->GetTrack(trackNumber).GetTrackID();

// 	cout << trackID << " " << hitNumber << endl;

// }
      
// // Find if the tracks are related to each other
// if (trackHitVector.size() > 1)
// 	{

// 	  // Find the smallest trackID
// 	  int smallestTrackID = numeric_limits<int>::max();
// 	  int smallestTrackIDIndex = -1;

// 	  for (int i = 0; i < trackHitVector.size(); ++i)
// 	    {
// 	      int trackNumber = trackHitVector[i][0];
// 	      int hitNumber = trackHitVector[i][1];
// 	      int trackID = event->GetTrack(trackNumber).GetTrackID();

// 	      cout << i << " " << trackID << " " << hitNumber << endl;
	      
// 	      if (trackID < smallestTrackID)
// 		{
// 		  smallestTrackID = trackID;
// 		  smallestTrackIDIndex = i;
// 		}
// 	    }

// 	  cout << "smallest trackID " << smallestTrackID << " index " << smallestTrackIDIndex << endl;

// 	  cout << "\nFinal comparison vector: " << endl;
      
// 	  int smallestTrackNumber = trackHitVector[smallestTrackIDIndex][0];

// 	  vector<int> childrenTracks;
// 	  storeChildrenTracks(smallestTrackNumber, *event, trackIDToNumberMap, childrenTracks);
	  
// 	  // Output the childrenTracks vector
// 	  cout << "Children Tracks:\n";
// 	  for (const auto& trackID : childrenTracks) {
// 	    cout << "TrackID: " << trackID << "\n";
// 	  }

	  
// 	  for (auto it = trackHitVector.begin(); it != trackHitVector.end(); ) {
// 	    int trackNumber = (*it)[0];
// 	    int trackID = event->GetTrack(trackNumber).GetTrackID();

// 	    // Skip the smallest trackID
// 	    if (trackID != smallestTrackID) {
// 	      bool isPresent = false;

// 	      for (int number : childrenTracks) {
// 		if (number == trackID) {
// 		  isPresent = true;
// 		  break;
// 		}
// 	      }

// 	      if (isPresent) {
// 		cout << "The trackID " << trackID << " is a child of trackID " << smallestTrackID << endl;
// 		// Erase the track from the trackHitVector
// 		it = trackHitVector.erase(it);
// 	      } else {
// 		cout << "The trackID " << trackID << " is NOT a child of trackID " << smallestTrackID << endl;
// 		++it;
// 	      }
// 	    } else {
// 	      ++it;
// 	    }

// 	  }
	        
// 	} // end of if condition on trackHitVector size > 1

// BWaterSensitiveTransportationMultiplicity = trackHitVector.size();

// // end of algorithm /////////////////////////////////////////////////////////////
