# Install script for directory: /fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "../install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/DRsim" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/DRsim")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/DRsim"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/build/DRsim/DRsim")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/DRsim" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/DRsim")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/DRsim"
         OLD_RPATH "/cvmfs/geant4.cern.ch/geant4/10.5.p01/x86_64-centos7-gcc8-opt-MT/lib64:/cvmfs/sft.cern.ch/lcg/releases/LCG_96b/hepmc3/3.1.2/x86_64-centos7-gcc8-opt/lib64:/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/build/rootIO:/cvmfs/sft.cern.ch/lcg/releases/LCG_95/qt5/5.11.1/x86_64-centos7-gcc8-opt/lib:/cvmfs/sft.cern.ch/lcg/releases/LCG_95/XercesC/3.1.3/x86_64-centos7-gcc8-opt/lib:/cvmfs/geant4.cern.ch/externals/clhep/2.4.1.0/x86_64-centos7-gcc8-opt/lib:/cvmfs/sft.cern.ch/lcg/releases/LCG_96b/fastjet/3.3.2/x86_64-centos7-gcc8-opt/lib:/cvmfs/sft.cern.ch/lcg/releases/LCG_96b/ROOT/6.18.04/x86_64-centos7-gcc8-opt/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/cvmfs/sft.cern.ch/lcg/releases/binutils/2.30-e5b21/x86_64-centos7/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/DRsim")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES
    "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim/gui.mac"
    "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim/icons.mac"
    "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim/init.mac"
    "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim/init_vis.mac"
    "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim/run_calib.mac"
    "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim/run_ele.mac"
    "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim/run_gps.mac"
    "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim/run_hepmc.mac"
    "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim/run_pi.mac"
    "/fcc/tikim/hep_fcc_dual_readout_001_2022_01_24/test/dual-readout/DRsim/vis.mac"
    )
endif()

