void AccessEvent(const std::string& fName) {

  TRestRun* rn = new TRestRun(fName);

  // We get the input event
  TRestEvent* tckEv = rn->GetInputEvent();

  // We get the event at entry 10
  rn->GetEntry(10);
  cout << "ID: " << tckEv->GetID() << endl;
  tckEv->PrintEvent();

  // We get the next entry (should be entry 11)
  rn->GetNextEntry();
  cout << "ID: " << tckEv->GetID() << endl;
  tckEv->PrintEvent();

  // We get the event with ID 6960
  rn->GetEventWithID(0);
  cout << "ID: " << tckEv->GetID() << endl;
  tckEv->PrintEvent();
  
  // We iterate over all the events and print the number of tracks
  const int nEntries = rn->GetEntries();
  for (int n = 0; n < nEntries; n++) {
    rn->GetEntry(n);
    tckEv->PrintEvent();
  }

  // We create a canvas
  TCanvas* c = new TCanvas();

  // We get the event at entry 100 and draw it
  rn->GetEntry(100);
  rn->GetInputEvent();
  tckEv->DrawEvent();
  
}
