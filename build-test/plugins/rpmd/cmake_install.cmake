# Install script for directory: /home/cpd-2/rev_omm/openmm/plugins/rpmd

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/cpd-2/rev_omm/openmm/build-test/plugins/rpmd/platforms/reference/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/cpd-2/rev_omm/openmm/build-test/plugins/rpmd/platforms/common/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openmm" TYPE FILE FILES
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/RPMDIntegrator.h"
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/RPMDMonteCarloAnisotropicBarostat.h"
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/RPMDMonteCarloBarostat.h"
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/RPMDMonteCarloFlexibleBarostat.h"
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/RPMDMonteCarloMembraneBarostat.h"
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/RPMDUpdater.h"
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/RpmdKernels.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openmm/internal" TYPE FILE FILES
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/internal/RPMDMonteCarloAnisotropicBarostatImpl.h"
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/internal/RPMDMonteCarloBarostatImpl.h"
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/internal/RPMDMonteCarloFlexibleBarostatImpl.h"
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/internal/RPMDMonteCarloMembraneBarostatImpl.h"
    "/home/cpd-2/rev_omm/openmm/plugins/rpmd/openmmapi/include/openmm/internal/windowsExportRpmd.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMMRPMD.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMMRPMD.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMMRPMD.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/cpd-2/rev_omm/openmm/build-test/libOpenMMRPMD.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMMRPMD.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMMRPMD.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMMRPMD.so"
         OLD_RPATH "/home/cpd-2/rev_omm/openmm/build-test:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libOpenMMRPMD.so")
    endif()
  endif()
endif()

