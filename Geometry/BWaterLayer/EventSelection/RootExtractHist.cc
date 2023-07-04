#include "TFile.h"
#include "TTree.h"

void RootExtractHist(const std::string& fName) {
    
  // TFile *f = new TFile(fName);
  // TTree *tr=(TTree*)f->Get("EventTree");
  // TBranch *br=(TBranch*)br->Get("TRestGeant4EventBranch");


  TRestRun* rn = new TRestRun(fName);
  rn->PrintMetadata();
  int nEntries =  rn->GetEntries();
  cout << "The number of entries is : " <<  nEntries << endl;
  
}
