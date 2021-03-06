/* data race detection - refactoring in progress */

#include "sage3basic.h"
#include "DataRaceDetection.h"
#include "Specialization.h"
#include "EquivalenceChecking.h"

using namespace CodeThorn;

DataRaceDetection::DataRaceDetection() {
}

DataRaceDetection::Options::Options():active(false),
                                      dataRaceFail(false),
                                      maxFloatingPointOperations(0),
                                      useConstSubstitutionRule(false),
                                      visualizeReadWriteSets(false),
                                      printUpdateInfos(false)
{
}

void DataRaceDetection::handleCommandLineOptions(Analyzer& analyzer, BoolOptions& boolOptions) {
  //cout<<"DEBUG: initializing data race detection"<<endl;
  if(boolOptions["data-race-fail"]) {
    boolOptions.setOption("data-race",true);
  }
  if(args.count("data-race-csv")) {
    options.dataRaceCsvFileName=args["data-race-csv"].as<string>();
    boolOptions.setOption("data-race",true);
  }
  if(boolOptions["data-race"]) {
    options.active=true;
    //cout<<"INFO: ignoring lhs-array accesses"<<endl;
    analyzer.setSkipArrayAccesses(true);
    options.useConstSubstitutionRule=boolOptions["rule-const-subst"];
    options.maxFloatingPointOperations=0; // not used yet
  }
  if (boolOptions["visualize-read-write-sets"]) {
    options.visualizeReadWriteSets=true;
  }
  if(boolOptions["print-update-infos"]) {
    options.printUpdateInfos=true;
  }
  options.useConstSubstitutionRule=boolOptions["rule-const-subst"];
}

void DataRaceDetection::setCsvFileName(string fileName) {
  options.dataRaceCsvFileName=fileName;
}

bool DataRaceDetection::run(Analyzer& analyzer, BoolOptions& boolOptoins) {
  if(options.active) {
    SAR_MODE sarMode=SAR_SSA;
    Specialization speci;
    ArrayUpdatesSequence arrayUpdates;
    RewriteSystem rewriteSystem;   
    int verifyUpdateSequenceRaceConditionsResult=-1;
    int verifyUpdateSequenceRaceConditionsTotalLoopNum=-1;
    int verifyUpdateSequenceRaceConditionsParLoopNum=-1;

    analyzer.setSkipSelectedFunctionCalls(true);
    analyzer.setSkipArrayAccesses(true);

    // perform data race detection
    if (options.visualizeReadWriteSets) {
      speci.setVisualizeReadWriteAccesses(true);
    }
    cout<<"STATUS: performing array analysis on STG."<<endl;
    cout<<"STATUS: identifying array-update operations in STG and transforming them."<<endl;
    
    speci.extractArrayUpdateOperations(&analyzer,
                                       arrayUpdates,
                                       rewriteSystem,
                                       options.useConstSubstitutionRule
                                       );
    speci.substituteArrayRefs(arrayUpdates, analyzer.getVariableIdMapping(), sarMode);

    SgNode* root=analyzer.startFunRoot;
    VariableId parallelIterationVar;
    LoopInfoSet loopInfoSet=EquivalenceChecking::determineLoopInfoSet(root,analyzer.getVariableIdMapping(), analyzer.getLabeler());
    cout<<"INFO: number of iteration vars: "<<loopInfoSet.size()<<endl;
    verifyUpdateSequenceRaceConditionsTotalLoopNum=loopInfoSet.size();
    verifyUpdateSequenceRaceConditionsParLoopNum=Specialization::numParLoops(loopInfoSet, analyzer.getVariableIdMapping());
    verifyUpdateSequenceRaceConditionsResult=speci.verifyUpdateSequenceRaceConditions(loopInfoSet,arrayUpdates,analyzer.getVariableIdMapping());
    if(options.printUpdateInfos) {
      speci.printUpdateInfos(arrayUpdates,analyzer.getVariableIdMapping());
    }
    speci.createSsaNumbering(arrayUpdates, analyzer.getVariableIdMapping());

    cout << "Data Race Detection:"<<endl;
    stringstream text;
    if(verifyUpdateSequenceRaceConditionsResult==-1) {
      text<<"sequential";
    } else if(verifyUpdateSequenceRaceConditionsResult==0) {
      text<<"pass";
    } else {
        text<<"fail";
    }
    text<<","<<verifyUpdateSequenceRaceConditionsResult;
    text<<","<<verifyUpdateSequenceRaceConditionsParLoopNum;
    text<<","<<verifyUpdateSequenceRaceConditionsTotalLoopNum;
    text<<endl;

    cout << text.str();
    if(options.dataRaceCsvFileName!="") {
      CodeThorn::write_file(options.dataRaceCsvFileName,text.str());
    }
    return true;
  } else {
    return false;
  }
}
