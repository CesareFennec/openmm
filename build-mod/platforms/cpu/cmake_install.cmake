# Install script for directory: /home/cpd-2/rev_omm/openmm/platforms/cpu

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local/openmm")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openmm/cpu" TYPE FILE FILES
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/AlignedArray.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuBondForce.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuConstantPotentialForce.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuConstantPotentialForceFvec.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuCustomGBForce.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuCustomManyParticleForce.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuCustomNonbondedForce.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuCustomNonbondedForceFvec.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuGBSAOBCForce.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuGayBerneForce.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuKernelFactory.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuKernels.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuLCPOForce.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuLangevinMiddleDynamics.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuNeighborList.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuNonbondedForce.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuNonbondedForceFvec.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuPlatform.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuRandom.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/CpuSETTLE.h"
    "/home/cpd-2/rev_omm/openmm/platforms/cpu/include/windowsExportCpu.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/cpd-2/rev_omm/openmm/build-mod/platforms/cpu/sharedTarget/cmake_install.cmake")
endif()

