// SelectOneEvent("../RootOutputFiles/FastNeutrons/Test_SensVol_lsAMT/RestG4_RootOutputFiles/RunArmor_neutrons_1MeV_BWater200_restG4_SensVol_lsAMT_10-7ev.root")

void SelectOneEvent(const string& fName, int entry=0){//const std::string& fName
  
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
  geant4Metadata->PrintMetadata();
  
  vector< TString > VActiveVolumes = geant4Metadata->GetActiveVolumes();
  cout << VActiveVolumes.size() << " active volume(s)" << ": " << endl;
  
  for (size_t i = 0; i < VActiveVolumes.size(); i++) {
    cout << "ID " << geant4Metadata->GetActiveVolumeID(VActiveVolumes[i]) << " name " << VActiveVolumes[i] << endl ;
  }
  cout << endl;

  int SensitiveVolumeID = geant4Metadata->GetActiveVolumeID(geant4Metadata->GetSensitiveVolume());
  int ActiveVolumeID = geant4Metadata->GetActiveVolumeID("ID_lsAMT");

  run.GetEntry(entry);
  
  event->PrintEvent();

  return 0;
}
