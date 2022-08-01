#include "DRsimSiPMSD.hh"
#include "DRsimSiPMHit.hh"
#include "DRsimDetectorConstruction.hh"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "G4OpBoundaryProcess.hh"

using namespace std;

DRsimSiPMSD::DRsimSiPMSD(const G4String& name, const G4String& hitsCollectionName, DRsimInterface::DRsimTowerProperty towerProp)
: G4VSensitiveDetector(name), fHitCollection(0), fHCID(-1), fWavBin(60), fTimeBin(600),
fPhiUnit(2*M_PI/(G4float)DRsimDetectorConstruction::sNumZRot), fWavlenStart(900.), fWavlenEnd(300.), fTimeStart(10.), fTimeEnd(70.)
{
  collectionName.insert(hitsCollectionName);
  fWavlenStep = (fWavlenStart-fWavlenEnd)/(float)fWavBin;
  fTimeStep = (fTimeEnd-fTimeStart)/(float)fTimeBin;

  fTowerTheta = towerProp.towerTheta;
  fTowerXY = towerProp.towerXY;
  fInnerR = towerProp.innerR;
  fTowerH = towerProp.towerH;
  fDTheta = towerProp.dTheta;
}

DRsimSiPMSD::~DRsimSiPMSD() {}

void DRsimSiPMSD::Initialize(G4HCofThisEvent* hce) {
  fHitCollection = new DRsimSiPMHitsCollection(SensitiveDetectorName,collectionName[0]);
  if (fHCID<0) { fHCID = GetCollectionID(0); }
  hce->AddHitsCollection(fHCID,fHitCollection);
}

G4bool DRsimSiPMSD::ProcessHits(G4Step* step, G4TouchableHistory*) {

  if(step->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) return false;

  G4int SiPMnum = step->GetPostStepPoint()->GetTouchable()->GetVolume(1)->GetCopyNo();
  G4int towerPhi = step->GetPostStepPoint()->GetTouchable()->GetVolume(3)->GetCopyNo();
  G4int nofHits = fHitCollection->entries();
  G4double hitTime = step->GetPostStepPoint()->GetGlobalTime();
  G4double energy = step->GetTrack()->GetTotalEnergy();

  DRsimSiPMHit* hit = NULL;

  // -------------
  // void G4OpBoundaryProcess::BoundaryProcessVerbose() const
  // -------------
   
  // std::cout << "GetStepLength () " << step->GetStepLength ()<< std::endl; 
  
  // std::cout << "GetStepLength () " << step->GetStepLength ()<< std::endl; 
  // std::cout << "GetTotalEnergyDeposit ()" << step->GetTotalEnergyDeposit ()<< std::endl; 
  // std::cout << "GetDeltaPosition ()" << step->GetDeltaPosition ()<< std::endl; 
  // std::cout << "GetDeltaTime () " << step->GetDeltaTime () << std::endl; 
  // std::cout << "GetDeltaMomentum ()  " << step->GetDeltaMomentum () << std::endl; 
  // std::cout << "GetDeltaEnergy () " << step->GetDeltaEnergy ()<< std::endl; 
  // std::cout << "GetNumberOfSecondariesInCurrentStep () " << step->GetNumberOfSecondariesInCurrentStep () << std::endl; 
  // std::cout << "GetSecondary () " << step->GetSecondary () << std::endl; 
  // std::cout << "GetfSecondary ()" << step->GetfSecondary ()<< std::endl; 
 
  // std::cout << "GetPreStepPoint () " << step->GetPreStepPoint ()<< std::endl; 
  // std::cout << "GetPreStepPoint () GetPosition ()" << step->GetPreStepPoint () -> GetPosition () << std::endl; 
  // std::cout << "GetPreStepPoint () GetLocalTime ()" << step->GetPreStepPoint () -> GetLocalTime () << std::endl; 
  // std::cout << "GetPreStepPoint () GetGlobalTime () " << step->GetPreStepPoint () -> GetGlobalTime ()  << std::endl; 
  // std::cout << "GetPreStepPoint () GetProperTime () " << step->GetPreStepPoint () -> GetProperTime ()  << std::endl; 
  // std::cout << "GetPreStepPoint () GetMomentumDirection ()" << step->GetPreStepPoint () -> GetMomentumDirection () << std::endl; 
  // std::cout << "GetPreStepPoint () GetMomentum ()" << step->GetPreStepPoint () -> GetMomentum () << std::endl; 
  // std::cout << "GetPreStepPoint () GetTotalEnergy ()" << step->GetPreStepPoint () -> GetTotalEnergy () << std::endl; 
  // std::cout << "GetPreStepPoint () GetVelocity () " << step->GetPreStepPoint () -> GetVelocity ()  << std::endl; 
  // std::cout << "GetPreStepPoint () GetBeta ()" << step->GetPreStepPoint () -> GetBeta () << std::endl; 
  // std::cout << "GetPreStepPoint () GetGamma () " << step->GetPreStepPoint () -> GetGamma ()  << std::endl; 

  // std::cout << "GetPreStepPoint () GetMaterial () GetState () " << step->GetPreStepPoint () -> GetMaterial () -> GetState () << std::endl; 
  // std::cout << "GetPreStepPoint () GetMaterial () GetTemperature ()" << step->GetPreStepPoint () -> GetMaterial () -> GetTemperature ()<< std::endl; 
  // std::cout << "GetPreStepPoint () GetMaterial () GetPressure () " << step->GetPreStepPoint () -> GetMaterial () -> GetPressure () << std::endl; 
  // std::cout << "GetPostStepPoint () GetMaterial () GetName ()" << step->GetPostStepPoint () -> GetMaterial () -> GetName ()<< std::endl; 
  // std::cout << "GetPreStepPoint () GetMaterial () GetName ()" << step->GetPreStepPoint () -> GetMaterial () -> GetName ()<< std::endl; 
  // std::cout << "GetPostStepPoint () GetMaterial () GetChemicalFormula () " << step->GetPostStepPoint () -> GetMaterial () -> GetChemicalFormula () << std::endl; 
  // std::cout << "GetPreStepPoint () GetMaterial () GetNumberOfElements ()  " << step->GetPreStepPoint () -> GetMaterial () -> GetNumberOfElements ()  << std::endl; 
  // std::cout << "GetPreStepPoint () GetMaterial () GetMatComponents () " << step->GetPreStepPoint () -> GetMaterial () -> GetMatComponents () << std::endl; 
  // std::cout << "GetPreStepPoint () GetMaterial () GetMassOfMolecule ()" << step->GetPreStepPoint () -> GetMaterial () -> GetMassOfMolecule ()<< std::endl; 

  // std::cout << "GetPreStepPoint () GetProcessDefinedStep () " << step->GetPreStepPoint () -> GetProcessDefinedStep () << std::endl; 
  // std::cout << "GetPreStepPoint () GetProcessDefinedStep () GetPhysicsTableFileName " << step->GetPreStepPoint () -> GetProcessDefinedStep () -> GetPhysicsTableFileName ()<< std::endl; 
  // std::cout << "GetPreStepPoint () GetProcessDefinedStep () GetProcessName () " << step->GetPreStepPoint () -> GetProcessDefinedStep () -> GetProcessName () << std::endl; 
  // std::cout << "GetPreStepPoint () GetProcessDefinedStep () GetProcessType ()  " << step->GetPreStepPoint () -> GetProcessDefinedStep () -> GetProcessType ()  << std::endl; 
  // std::cout << "GetPreStepPoint () GetProcessDefinedStep () GetProcessSubType () " << step->GetPreStepPoint () -> GetProcessDefinedStep () -> GetProcessSubType () << std::endl; 
  // std::cout << "GetPreStepPoint () GetProcessDefinedStep () GetMasterProcess () " << step->GetPreStepPoint () -> GetProcessDefinedStep () -> GetMasterProcess () << std::endl; 
  // std::cout << "GetPreStepPoint () GetProcessDefinedStep () 	GetProcessTypeName (G4ProcessType) " << step->GetPreStepPoint () -> GetProcessDefinedStep () -> 	GetProcessTypeName () << std::endl; 

  std::cout << "step, G4Track * 	GetTrack () const, G4int GetTrackID () const ---------------------------------------------------------- " << std::endl; 
  std::cout << "step GetTrack() GetTrackID () " << step->GetTrack()-> GetTrackID () << std::endl; 
  std::cout << "step GetTrack() GetParentID ()   " << step->GetTrack()-> GetParentID ()  << std::endl; 
  // std::cout << "step GetTrack() GetParticleDefinition () " << step->GetTrack()-> GetParticleDefinition ()  << std::endl; 
  // std::cout << "step GetTrack() GetParticleDefinition () GetParticleName () " << step->GetTrack()-> GetParticleDefinition () -> GetParticleName ()   << std::endl; 
  // std::cout << "step GetTrack() GetParticleDefinition () GetParticleType ()  " << step->GetTrack()-> GetParticleDefinition () -> 	GetParticleType ()    << std::endl; 
  // std::cout << "step GetTrack(), const G4ParticleDefinition * 	GetParticleDefinition () const, const G4String & 	GetParticleSubType () const------------------------------------   " << std::endl; 
  // std::cout << "step GetTrack() GetParticleDefinition () GetParticleSubType ()   " << step->GetTrack()-> GetParticleDefinition () -> 	GetParticleSubType ()     << std::endl; 
  // std::cout << "step GetTrack() GetParticleDefinition () GetProcessManager ()" << step->GetTrack()-> GetParticleDefinition () -> GetProcessManager ()  << std::endl; 
  // std::cout << "step GetTrack() GetParticleDefinition () GetProcessManager () GetProcessList () entries ()  " << step->GetTrack()-> GetParticleDefinition () -> GetProcessManager () -> GetProcessList () -> entries () << std::endl; 
  // std::cout << "step GetTrack() GetParticleDefinition () GetParticleTable ()   " << step->GetTrack()-> GetParticleDefinition () -> GetParticleTable ()  << std::endl; 
  // std::cout << "step GetTrack() GetParticleDefinition () GetMasterProcessManager () GetProcessList () entries ()  " << step->GetTrack()-> GetParticleDefinition () -> GetMasterProcessManager () -> GetProcessList () -> entries () << std::endl; 
  // std::cout << "step GetTrack() GetParticleDefinition () GetParticleDefinitionID ()   " << step->GetTrack()-> GetParticleDefinition () -> GetParticleDefinitionID ()  << std::endl; 

  // std::cout << "step GetTrack() GetDefinition () GetProcessManager ()   " << step->GetTrack()-> GetDefinition () -> GetProcessManager ()  << std::endl; //no
  
  // std::cout << "step G4Track * 	GetTrack () const, G4Material * 	GetMaterial () const, const G4String & 	GetName () const, " << step->GetTrack()-> GetMaterial () -> GetName () << std::endl; // glass
  // std::cout << "GetTrack () GetMaterial () GetChemicalFormula () " << step->GetTrack () -> GetMaterial () -> GetChemicalFormula () << std::endl; 
  // std::cout << "GetTrack () GetMaterial () G4State 	GetState () const " << step->GetTrack () -> GetMaterial () -> GetState () << std::endl; 
  // std::cout << "GetTrack () GetMaterial () GetTemperature ()" << step->GetTrack () -> GetMaterial () -> GetTemperature ()<< std::endl; 
  // std::cout << "GetTrack () GetMaterial () GetPressure () " << step->GetTrack () -> GetMaterial () -> GetPressure () << std::endl; 
  // std::cout << "GetTrack () GetMaterial () GetNumberOfElements ()  " << step->GetTrack () -> GetMaterial () -> GetNumberOfElements ()  << std::endl; 
  // std::cout << "GetTrack () GetMaterial () GetMatComponents () " << step->GetTrack () -> GetMaterial () -> GetMatComponents () << std::endl; 
  // std::cout << "GetTrack () GetMaterial () GetMassOfMolecule ()" << step->GetTrack () -> GetMaterial () -> GetMassOfMolecule ()<< std::endl; 

  // std::cout << "step G4Track * 	GetTrack () const, G4Material * 	GetNextMaterial () const, const G4String & 	GetName () const, " << step->GetTrack()-> GetNextMaterial () -> GetName () << std::endl; // silicon

  // std::cout << "step G4Track * 	GetTrack () const, const G4VTouchable * 	GetTouchable () const, virtual G4VPhysicalVolume * 	GetVolume (G4int depth=0) const, G4LogicalVolume * 	GetLogicalVolume () const, const G4String & 	GetName () const, 0 " << step->GetTrack()->GetTouchable()->GetVolume(0)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
  std::cout << "step->GetTrack()->GetTouchable()->GetVolume(0)->GetLogicalVolume()->GetMaterial()->GetName() " << step->GetTrack()->GetTouchable()->GetVolume(0)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
  std::cout << "1 " << step->GetTrack()->GetTouchable()->GetVolume(1)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
  std::cout << "2 " << step->GetTrack()->GetTouchable()->GetVolume(2)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
  
  // std::cout << "step G4Track * 	GetTrack () const, const G4VTouchable * 	GetTouchable () const, virtual const G4NavigationHistory * 	GetHistory () const " << step->GetTrack()->GetTouchable()->GetHistory() << std::endl; 
  std::cout << "step->GetTrack()->GetTouchable()->GetSolid (0)->GetName() " << step->GetTrack()->GetTouchable()->GetSolid (0)->GetName() << std::endl; 
  // std::cout << "step G4Track * 	GetTrack () const, const G4VTouchable * 	GetTouchable () const, virtual G4VSolid * 	GetSolid (G4int depth=0) const, const G4String & 	GetName () const " << step->GetTrack()->GetTouchable()->GetSolid (0)->GetName() << std::endl; 
  std::cout << "virtual G4VSolid * 	GetSolid (G4int depth=1) const" << step->GetTrack()->GetTouchable()->GetSolid (1)->GetName() << std::endl; 
  std::cout << "virtual G4VSolid * 	GetSolid (G4int depth=2) const" << step->GetTrack()->GetTouchable()->GetSolid (2)->GetName() << std::endl; 
  std::cout << "virtual G4VSolid * 	GetSolid (G4int depth=3) const" << step->GetTrack()->GetTouchable()->GetSolid (3)->GetName() << std::endl; 
  
  // std::cout << "step G4Track * 	GetTrack () const, const G4VTouchable * 	GetTouchable () const, virtual G4int 	GetReplicaNumber (G4int depth=0) const, 0 " << step->GetTrack()->GetTouchable()->GetReplicaNumber(0) << std::endl; 
  // std::cout << "step G4Track * 	GetTrack () const, const G4VTouchable * 	GetTouchable () const, virtual G4int 	GetReplicaNumber (G4int depth=1) const, 0 " << step->GetTrack()->GetTouchable()->GetReplicaNumber(1) << std::endl; some value
  
  // std::cout << "step G4Track * 	GetTrack () const, const G4VTouchable * 	GetTouchable () const, virtual G4int 	GetHistoryDepth () const, 0 " << step->GetTrack()->GetTouchable()->GetHistoryDepth() << std::endl; 



  std::cout << "0 " << step->GetTrack()->GetOriginTouchable()->GetVolume(0)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
  std::cout << "1 " << step->GetTrack()->GetOriginTouchable()->GetVolume(1)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
  std::cout << "2 " << step->GetTrack()->GetOriginTouchable()->GetVolume(2)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
  // std::cout << "3 " << step->GetTrack()->GetOriginTouchable()->GetVolume(3)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
  // std::cout << "3 " << step->GetTrack()->GetOriginTouchable()->GetVolumez(4)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 

  std::cout << "GetName().compare(\"G4_AIR\") " << step->GetTrack()->GetOriginTouchable()->GetVolume(1)->GetLogicalVolume()->GetMaterial()->GetName().compare("G4_AIR") << std::endl; 
  // if (GetName().compare("G4_AIR") == 0 ){

  // }



  for (G4int i = 0; i < nofHits; i++) {
    if ( (*fHitCollection)[i]->GetSiPMnum()==SiPMnum && (*fHitCollection)[i]->GetTowerTheta()==fTowerTheta && (*fHitCollection)[i]->GetTowerPhi().first==towerPhi) {
      hit = (*fHitCollection)[i];
      break;
    }
  }

  if (hit==NULL) {
    hit = new DRsimSiPMHit(fWavBin,fTimeBin);
    hit->SetSiPMnum(SiPMnum);
    hit->SetTowerTheta(fTowerTheta);
    hit->SetTowerPhi(std::make_pair(towerPhi,(float)towerPhi*fPhiUnit));
    hit->SetTowerXY(fTowerXY);
    hit->SetTowerInnerR(fInnerR);
    hit->SetTowerH(fTowerH);
    hit->SetTowerDTheta(fDTheta);
    hit->SetSiPMXY(findSiPMXY(SiPMnum,fTowerXY));
    hit->SetSiPMpos(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetTopTransform().Inverse().TransformPoint(G4ThreeVector(0.,0.,0.)));

    fHitCollection->insert(hit);
  }

  hit->photonCount();

  DRsimInterface::hitRange wavRange = findWavRange(energy);
  hit->CountWavlenSpectrum(wavRange);

  DRsimInterface::hitRange timeRange = findTimeRange(hitTime);
  hit->CountTimeStruct(timeRange);

  return true;
}

void DRsimSiPMSD::EndOfEvent(G4HCofThisEvent*) {
  if ( verboseLevel>1 ) {
    G4int nofHits = fHitCollection->entries();
    G4cout
    << G4endl
    << "-------->Hits Collection: in this event they are " << nofHits
    << " hits in the tracker chambers: " << G4endl;
    for ( G4int i=0; i<nofHits; i++ ) (*fHitCollection)[i]->Print();
  }
}

DRsimInterface::hitRange DRsimSiPMSD::findWavRange(G4double en) {
  int i = 0;
  for ( ; i < fWavBin+1; i++) {
    if ( en < wavToE( (fWavlenStart - (float)i*fWavlenStep)*nm ) ) break;
  }

  if (i==0) return std::make_pair(fWavlenStart,99999.);
  else if (i==fWavBin+1) return std::make_pair(0.,fWavlenEnd);

  return std::make_pair( fWavlenStart-(float)i*fWavlenStep, fWavlenStart-(float)(i-1)*fWavlenStep );
}

DRsimInterface::hitRange DRsimSiPMSD::findTimeRange(G4double stepTime) {
  int i = 0;
  for ( ; i < fTimeBin+1; i++) {
    if ( stepTime < ( (fTimeStart + (float)i*fTimeStep)*ns ) ) break;
  }

  if (i==0) return std::make_pair(0.,fTimeStart);
  else if (i==fTimeBin+1) return std::make_pair(fTimeEnd,99999.);

  return std::make_pair( fTimeStart+(float)(i-1)*fTimeStep, fTimeStart+(float)i*fTimeStep );
}

DRsimInterface::hitXY DRsimSiPMSD::findSiPMXY(G4int SiPMnum, DRsimInterface::hitXY towerXY) {
  int x = SiPMnum/towerXY.second;
  int y = SiPMnum%towerXY.second;

  return std::make_pair(x,y);
}
