cmake_minimum_required(VERSION 3.5)

project(NanoSpectrum LANGUAGES CXX)

set(NanoSpectrum_VERSION_MAJOR 0)
set(NanoSpectrum_VERSION_MINOR 1)

set(CMAKE_MODULE_PATH ${NanoSpectrum_SOURCE_DIR}/cmake)

set(PROJECT_DIR "${CMAKE_BINARY_DIR}")

include(TranslationUtils)

if(UNIX)
  include(GNUInstallDirs)
else()
  if (WIN32)
    set(${CMAKE_INSTALL_LIBDIR} "lib")
    set(${CMAKE_INSTALL_DATADIR} "share")
    set(${CMAKE_INSTALL_INCLUDEDIR} "include")
    set(${CMAKE_INSTALL_BINDIR} "bin")
    message(STATUS "Setting installation destination on Windows to: ${CMAKE_INSTALL_PREFIX}")
  else()
    message(FATAL_ERROR "System not UNIX nor WIN32 - not implemented yet")
  endif()
endif()

# configure and install NanoSpectrumConfig.cmake file
configure_file(
    "${CMAKE_MODULE_PATH}/NanoSpectrumConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/NanoSpectrumConfig.cmake"
    IMMEDIATE @ONLY)

# export the NanoSpectrum package
export(PACKAGE NanoSpectrum)

option(NanoSpectrum_BUILD_TESTS "Build the NanoSpectrum tests." OFF)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
