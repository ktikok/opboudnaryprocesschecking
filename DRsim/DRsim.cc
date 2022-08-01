#include <iostream>
#include "DRsimDetectorConstruction.hh"
#include "DRsimActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4OpticalPhysics.hh"
#include "FTFP_BERT.hh"
#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

int main(int argc, char** argv) {
  #ifdef G4UI_USE
  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) ui = new G4UIExecutive(argc, argv);
  #endif

  G4int seed = 0;
  G4String filename;
  if (argc > 2) seed = atoi(argv[2]);
  if (argc > 3) filename = argv[3];

  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  CLHEP::HepRandom::setTheSeed(seed);

  // Construct the default run manager
  #ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  #else
  G4RunManager* runManager = new G4RunManager;
  #endif

  // Mandatory user initialization classes
  runManager->SetUserInitialization(new DRsimDetectorConstruction());

  // physics module
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();

  // std::cout << "GetStepLength () " << step->GetStepLength ()<< std::endl; 
  // opticalPhysics::ConstructProcess().fBoundaryProcess


  physicsList->RegisterPhysics(opticalPhysics);
  opticalPhysics->Configure(kCerenkov, true);
  opticalPhysics->Configure(kScintillation, true);

  // --------------------------------------------------------
  // void G4OpticalPhysics::Configure(G4OpticalProcessIndex index, G4bool isUse)
  // {
  //   // Configure the physics constructor to use/not use a selected process.
  //   // This method can only be called in PreInit> phase (before execution of
  //   // ConstructProcess). The process is not added to particle's process manager
  //   // and so it cannot be re-activated later in Idle> phase with the command
  //   // /process/activate.

  //   if ( index >= kNoProcess ) return;
  //   if ( fProcessUse[index] == isUse ) return;
  //   fProcessUse[index] = isUse;
  // }
  // --------------------------------------------------------
  G4int ver = 1;
  opticalPhysics->SetBoundaryVerbosity(ver);

  // --------------------------------------------------------
  // void G4OpticalPhysics::SetBoundaryVerbosity(G4int ver)
  // {
  //   fBoundaryVerbosity = ver;
  //   if (fBoundaryProcess) {
  //     fBoundaryProcess->SetVerboseLevel(fBoundaryVerbosity);
  //   }
  // }
  // --------------------------------------------------------


  opticalPhysics->SetTrackSecondariesFirst(kCerenkov, true);
  opticalPhysics->SetTrackSecondariesFirst(kScintillation, true);
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new DRsimActionInitialization(seed,filename));

  // Visualization manager construction
  #ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  #endif
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( argc != 1 ) {
    // execute an argument macro file if exist
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  } else {
    #ifdef G4UI_USE
    #ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    #else
    UImanager->ApplyCommand("/control/execute init.mac");
    #endif
    if (ui->IsGUI()) { UImanager->ApplyCommand("/control/execute gui.mac"); }
    // start interactive session
    ui->SessionStart();
    delete ui;
    #endif
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  #ifdef G4VIS_USE
  delete visManager;
  #endif
  delete runManager;

  return 0;
}
