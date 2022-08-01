# after git clone
source setenv-cc7-gcc8.sh
mkdir build
mkdir install
cd build
cmake ..
make -j12

ccmake ..
# change : CMAKE_INSTALL_PREFIX=../install

make -j12
make install

change analysis.cc code. you can compare with the code which is in previous working directory.
Especially, remove reco~~.

# add this in setenv-cc7-gcc8.sh
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HEPMC_DIR/lib64:$FASTJET_DIR/lib:$PYTHIA_DIR/lib:$PWD/lib
cp setenv-cc7-gcc8.sh install/

# to change materials, change below files and find "copper"
/fcc/tikim/0simulation/dual-readout/DRsim/src/DRsimDetectorConstruction.cc
/fcc/tikim/0simulation/dual-readout/DRsim/src/DRsimMaterials.cc
/fcc/tikim/0simulation/dual-readout/DRsim/include/DRsimMaterials.hh

# for brass
    const double BrassDensity = 8.44*g/cm3;
    auto CuZn37 = new G4Material(name="Brass", BrassDensity, 2);
    CuZn37->AddElement(elCu, 0.7);
    CuZn37->AddElement(elZn, 0.3);

# do : -------------------------------------------------------------------------------------
cd /fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/install ;source 0setenv-cc7-gcc8.sh 


# to apply change
cd /fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/build; make -j12 install; cd ../install

# for visualization : 
./bin/DRsim

./bin/DRsim run_ele.mac 0 ./0test

# before run simulation, you must adjust beam positon. 
# to set the points, you can use kyuyeong_example.
# and use findpoints.C

# to change angle, change /DRsim/src/DRsimPrimaryGeneratorAction.cc 

# for calib: 
./bin/calib <rootfile name> 51
# after calib, compare specific tower number hit histogram energy and totalhit histogram energy 
# to get calb constant, calculate shit/edep, chit/edep. *not total values.
# After calculate the two values, apply the two value to all towers, and run analysis.
# and then change calib value again like this. calib_value*mean/simualtion_energy.
# Check again by run analysis.


# If you want change calib.csv file, you must change a calibe
# the calib.cc file is changed 
/fcc/tikim/0simulation/dual-readout/Reco/calib.csv


# for analysis: for 20 GeV
./bin/analysis <rootfile name> 10 30

# electron같이 em particle은 S + C
# pion 과 같은 하드론은 (sE - chi * cE ) / ( 1 - chi ) 그래프

# for full simualtion, look up the 0run_all.sh file

# if you want to see materials, use the below codes in DRsimSiPMSD.cc
std::cout << "1 " << step->GetTrack()->GetOriginTouchable()->GetVolume(0)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
std::cout << "2 " << step->GetTrack()->GetOriginTouchable()->GetVolume(1)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
std::cout << "3 " << step->GetTrack()->GetOriginTouchable()->GetVolume(2)->GetLogicalVolume()->GetMaterial()->GetName() << std::endl; 
  // to see materials



phi : 1.5 angle, z axis, 0.026179939 rad
eta : 1 angle, y axis, 0.0174533 rad
tower : 2.5m
energy : 1eV
material : cupper
mac file : cm unit
visualize : red, x, green, y, blue, z

0 >> x : 3050.15 y : 0 z : 33.8885 center_distance : 3050.33


// 51>> x : 2542.6 y : 0 z : 3561.32 center_distance : 4375.83

******************************************* for barrel 51
/DRsim/action/useHepMC True
/DRsim/action/useCalib True
/DRsim/action/useGPS True

/DRsim/generator/randx 0
/DRsim/generator/randy 0
/DRsim/generator/theta -0.97694993
/DRsim/generator/phi 0.017453293
/DRsim/generator/y0 -3.170329668
/DRsim/generator/z0 -14.62319386
/gun/particle e-
/gun/energy 1 eV
/run/beamOn 1

/vis/viewer/set/viewpointVector -2542.6 0 -3561.32
******************************************* for barrel 51

-------------------------------------endcap----------------------------------------- 52
0>> x : 2496.81, y : 0, z : 3593.58 center_distance : 4375.83
/DRsim/generator/randx 0
/DRsim/generator/randy 0
/DRsim/generator/theta -0.98975053
/DRsim/generator/phi 0.017453293
/DRsim/generator/y0 -3.1132348
/DRsim/generator/z0 -14.907069
/gun/particle e-
/gun/energy 1 eV
/run/beamOn 1
-------------------------------------endcap----------------------------------------- 52

-------------------------------------0---------------------------------------- 0
0 >> x : 3050.15 y : 0 z : 33.8885 center_distance : 3050.33
/DRsim/generator/randx 0
/DRsim/generator/randy 0
/DRsim/generator/theta -0.03728991884
/DRsim/generator/phi 0.017453293
/DRsim/generator/y0 -3.1132348
/DRsim/generator/z0 -4.716005797
/gun/particle e-
/gun/energy 1 eV
/run/beamOn 1
-------------------------------------0---------------------------------------- 0

-------------------------------------0-3---------------------------------------- 0
0 >> x : 3050.15 y : 0 z : 33.8885 center_distance : 3050.33
/DRsim/generator/randx 0
/DRsim/generator/randy 0
/DRsim/generator/theta -0.06346985762
/DRsim/generator/phi 0.017453293
/DRsim/generator/y0 -3.142302266
/DRsim/generator/z0 -9.441234961
/gun/particle e-
/gun/energy 1 eV
/run/beamOn 1
/vis/viewer/set/viewpointVector 3050.15 0 33.8885
-------------------------------------0-3---------------------------------------- 0

-------------------------------------51-3----------------------------------------- 
51>> x : 2542.6 y : 0 z : 3561.32 center_distance : 4375.83
/DRsim/generator/randx 0
/DRsim/generator/randy 0
/DRsim/generator/theta -1.003129872
/DRsim/generator/phi 0.017453293
/DRsim/generator/y0 -3.170329668
/DRsim/generator/z0 -30.42650995
/gun/particle e-
/gun/energy 1 eV
/run/beamOn 1
/vis/viewer/set/viewpointVector -2542.6 0 -3561.32

-------------------------------------51-3----------------------------------------- 

useful commands---------------------
scp -r -P 50002 ./results/ tikim@165.132.25.82:/data4/tikim/simulation_result/

----------------------how to cout boundary process--------------
G4OpBoundaryProcess.hh:                                  FresnelReflection, TotalInternalReflection
  ./source/physics_lists/constructors/electromagnetic/src/G4OpticalPhysics.cc:#include "G4OpticalPhysics.hh"
    ./source/physics_lists/lists/src/G4PhysListFactoryMessenger.cc:#include "G4OpticalPhysics.hh"
      ./source/physics_lists/lists/src/G4PhysListFactory.cc:#include "G4PhysListFactoryMessenger.hh"
    ./source/physics_lists/constructors/electromagnetic/src/G4OpticalPhysicsMessenger.cc:#include "G4OpticalPhysics.hh"
    ./source/physics_lists/constructors/factory/include/G4RegisterPhysicsConstructors.icc://#include "G4OpticalPhysics.hh"
      