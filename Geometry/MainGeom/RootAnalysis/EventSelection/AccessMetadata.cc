void AccessMetaData(const std::string& fName) {

  TRestRun* rn = new TRestRun(fName);
  rn->PrintMetadata();
  int nEntries =  rn->GetEntries();
  cout << "The number of entries is : " <<  nEntries << endl;

  // We recover the metadata object names that the user defined at the RML configuration file
  vector<string> mdNames = rn->GetMetadataNames();

  // We iterate over the list and print the name together with the object class name
  cout << "\n";
  cout << "The following metadata objects are found inside the file\n";
  cout << "--------------------------------------------------------\n";
  for (const auto& md : mdNames) {
    cout << md << " is: " << rn->GetMetadata(md)->ClassName() << endl;
  }
  cout << "\n";

  // We print the metadata information from the second element in the list
  cout << "We print the metadata information of the second element in the list:\n";
  cout << "--------------------------------------------------------------------\n";
  
  rn->GetMetadata(mdNames[1])->PrintMetadata();

  int threshold = stoi(rn->GetMetadataMember("veto::fThreshold"));
  
}
