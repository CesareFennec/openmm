# Install script for directory: /home/cpd-2/rev_omm/openmm/examples/cpp-examples

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/examples/cpp-examples" TYPE FILE FILES "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/HelloArgon.cpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/examples/cpp-examples" TYPE FILE FILES "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/HelloSodiumChloride.cpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/examples/cpp-examples" TYPE FILE FILES "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/HelloEthane.cpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/examples/cpp-examples" TYPE FILE FILES "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/HelloWaterBox.cpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/examples/cpp-examples" TYPE FILE FILES "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/HelloArgonInC.c")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/examples/cpp-examples" TYPE FILE FILES "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/HelloSodiumChlorideInC.c")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/examples/cpp-examples" TYPE FILE FILES "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/HelloArgonInFortran.f90")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/examples/cpp-examples" TYPE FILE FILES "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/HelloSodiumChlorideInFortran.f90")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/examples/cpp-examples/VisualStudio" TYPE FILE FILES
    "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/VisualStudio/HelloArgon.vcproj"
    "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/VisualStudio/HelloArgon.sln"
    "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/VisualStudio/HelloArgonInC.sln"
    "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/VisualStudio/HelloArgonInC.vcproj"
    "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/VisualStudio/HelloArgonInFortran.sln"
    "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/VisualStudio/HelloArgonInFortran.vfproj"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/examples/cpp-examples" TYPE FILE FILES
    "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/Makefile"
    "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/NMakefile"
    "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/Empty.cpp"
    "/home/cpd-2/rev_omm/openmm/examples/cpp-examples/README.md"
    )
endif()

