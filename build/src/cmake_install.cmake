# Install script for directory: C:/Users/Administrator/Desktop/MP4decoder/mp4/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/MP4Decoder")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/Program Files (x86)/c++/bin/objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/bitStream/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/decoder/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/box/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/fileTypeBox/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/movieBox/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/trackBox/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/mediaBox/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/mediaInformationBox/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/dataInformationBox/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/sampleTableBox/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/visualSampleEntry/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/trackReferenceBox/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/audioSampleEntry/cmake_install.cmake")
  include("C:/Users/Administrator/Desktop/MP4decoder/mp4/build/src/bbbb/cmake_install.cmake")

endif()

