// This is mainly a reproduction of the function TRestGeant4Event::PrintEvent()
// This is for comprehension purposes on how to retrieve the different informations from the Geant4 events.

// PrintEvent("/AGWeber/girardcarillo/nameofyour.root",0)

void PrintEvent(const string& fName, int entry=0){//const std::string& fName
  
  TRestRun run(fName);

  cout << "Run number " << run.GetRunNumber() << endl;
  
  TRestGeant4Event* event = run.GetInputEvent<TRestGeant4Event>();

  double nEvents = run.GetEntries();

  cout << "Number of events " << nEvents << endl;

  cout << "Testing reading of Geant4 metadata class" << endl;
  TRestGeant4Metadata* geant4Metadata = (TRestGeant4Metadata*)run.GetMetadataClass("TRestGeant4Metadata");
  if (!geant4Metadata) {
    cout << "Problem reading Geant4 metadata class!" << endl;
    return 6;
  }
  // geant4Metadata->PrintMetadata();
  
  vector< TString > VActiveVolumes = geant4Metadata->GetActiveVolumes();
  cout << VActiveVolumes.size() << " active volume(s)" << ": " << endl;
  
  for (size_t i = 0; i < VActiveVolumes.size(); i++) {
    cout << "ID " << geant4Metadata->GetActiveVolumeID(VActiveVolumes[i]) << " name " << VActiveVolumes[i] << endl ;
  }
  cout << endl;

  int SensitiveVolumeID = geant4Metadata->GetActiveVolumeID(geant4Metadata->GetSensitiveVolume());
  int ActiveVolumeID = geant4Metadata->GetActiveVolumeID("BWater");

  run.GetEntry(entry);

  cout << "Number of tracks " << event->GetNumberOfTracks() << "\n\n";

  int trackID = 0;
  int parentID = 0;
  TString particleName;
  Double_t EnergyInSensitiveVolume = 0.;
  Double_t EnergyInBWaterVolume = 0.;
  Double_t parentEnergy = 0.;
  TString processName;
  TString initialVolume;
  TString finalVolume;
  int counter_entering_SensitiveVolume = 0;  

  // int maxNumberOfTrackToPrint = event->GetNumberOfTracks();
  int maxNumberOfTrackToPrint = 2;
  
  for (int trackIndex=0; trackIndex<maxNumberOfTrackToPrint; trackIndex++) {
    
    cout << " * TrackID: " << event->GetTrack(trackIndex).GetTrackID()
	 << " - Particle: " << event->GetTrack(trackIndex).GetParticleName()
	 << " - ParentID: " << event->GetTrack(trackIndex).GetParentID()
	 << (event->GetTrack(trackIndex).GetParentTrack() != nullptr ? TString::Format(" - Parent particle: %s", event->GetTrack(trackIndex).GetParentTrack()->GetParticleName().Data()).Data() : "")
	 << " - Created by '" << event->GetTrack(trackIndex).GetCreatorProcess()
	 << "' with initial KE of " << ToEnergyString(event->GetTrack(trackIndex).GetInitialKineticEnergy()) << endl;
    cout << "   Initial position " << VectorToString(event->GetTrack(trackIndex).GetInitialPosition())
	 << " at time " << ToTimeString(event->GetTrack(trackIndex).GetGlobalTime())
	 << " - Time length of " << ToTimeString(event->GetTrack(trackIndex).GetTimeLength())
	 << " and spatial length of " << ToLengthString(event->GetTrack(trackIndex).GetLength()) << endl;

    int maxNumberOfHitToPrint = event->GetTrack(trackIndex).GetNumberOfHits();

    for (int hitIndex=0; hitIndex<maxNumberOfHitToPrint; hitIndex++) {
      
      cout << "      - Hit " << hitIndex
	   << " - Energy: " << ToEnergyString(event->GetTrack(trackIndex).GetHits().GetEnergy(hitIndex))
	   << " - Process: " << event->GetTrack(trackIndex).GetProcessName(event->GetTrack(trackIndex).GetHits().GetHitProcess(hitIndex))
	   << " - Volume: " << geant4Metadata->GetGeant4GeometryInfo().GetVolumeFromID(event->GetTrack(trackIndex).GetHits().GetHitVolume(hitIndex))
	   << " - Position: (" << VectorToString(TVector3(event->GetTrack(trackIndex).GetHits().GetX(hitIndex),event->GetTrack(trackIndex).GetHits().GetY(hitIndex),event->GetTrack(trackIndex).GetHits().GetZ(hitIndex)))
	   << " - Time: " << ToTimeString(event->GetTrack(trackIndex).GetHits().GetTime(hitIndex))
	   << " - KE: " << ToEnergyString(event->GetTrack(trackIndex).GetHits().GetKineticEnergy(hitIndex)) << endl;

    }

  }
  
  // event->PrintEvent();
    
  return 0;
}


