cmake_minimum_required(VERSION 3.4)

project("MasterEars")

# FRUT stuff
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../FRUT/cmake")
include(Reprojucer)

# if(NOT DEFINED MasterEars_jucer_FILE)
#     message(FATAL_ERROR "MasterEars_jucer_FILE must be defined")
# endif()

get_filename_component(MasterEars_jucer_FILE
    "${MasterEars_jucer_FILE}" ABSOLUTE
    BASE_DIR "${CMAKE_BINARY_DIR}"
)

jucer_project_begin(
    JUCER_VERSION "5.4.7"
    PROJECT_FILE "${MasterEars_jucer_FILE}"
    PROJECT_ID "lI5ry"
)

jucer_project_settings(
    PROJECT_NAME "MasterEars"
    PROJECT_VERSION "1.0.0"
    COMPANY_NAME "Chowdhury DSP"
    COMPANY_COPYRIGHT "Chowdhury DSP"
    REPORT_JUCE_APP_USAGE OFF
    DISPLAY_THE_JUCE_SPLASH_SCREEN OFF
    PROJECT_TYPE "GUI Application"
    BUNDLE_IDENTIFIER "com.chowdsp.MasterEars"
    CXX_LANGUAGE_STANDARD "C++17"
)

jucer_project_files("MasterEars/Source"
# Compile   Xcode     Binary    File
#           Resource  Resource
  x         .         .         "Source/main.cpp"
  .         .         .         "Source/MainComponent.h"
  x         .         .         "Source/MainComponent.cpp"
  .         .         .         "Source/SetupComponent.h"
  x         .         .         "Source/SetupComponent.cpp"
  .         .         .         "Source/DataManager.h"
  x         .         .         "Source/DataManager.cpp"
  .         .         .         "Source/ResultsComponent.h"
  x         .         .         "Source/ResultsComponent.cpp"
  .         .         .         "Source/SessionGUI/SessionComponent.h"
  x         .         .         "Source/SessionGUI/SessionComponent.cpp"
  .         .         .         "Source/SessionGUI/WaveformViewer.h"
  x         .         .         "Source/SessionGUI/WaveformViewer.cpp"
  .         .         .         "Source/SessionGUI/FreqButtons.h"
  x         .         .         "Source/SessionGUI/FreqButtons.cpp"
  .         .         .         "Source/SessionGUI/ThumbnailLoadingWindow.h"
  .         .         .         "Source/Backend/Configuration.h"
  .         .         .         "Source/Backend/Logic.h"
  .         .         .         "Source/Backend/Filter.h"
  x         .         .         "Source/Backend/Filter.cpp"
)

jucer_project_module(
    juce_audio_basics
    PATH "../JUCE/modules"
)

jucer_project_module(
    juce_audio_devices
    PATH "../JUCE/modules"
)

jucer_project_module(
    juce_audio_formats
    PATH "../JUCE/modules"
)

jucer_project_module(
    juce_audio_processors
    PATH "../JUCE/modules"
)

jucer_project_module(
    juce_audio_utils
    PATH "../JUCE/modules"
)

jucer_project_module(
    juce_core
    PATH "../JUCE/modules"
)

jucer_project_module(
    juce_data_structures
    PATH "../JUCE/modules"
)

jucer_project_module(
    juce_events
    PATH "../JUCE/modules"
)

jucer_project_module(
    juce_graphics
    PATH "../JUCE/modules"
)

jucer_project_module(
    juce_gui_basics
    PATH "../JUCE/modules"
)

jucer_project_module(
    juce_gui_extra
    PATH "../JUCE/modules"
)

jucer_export_target(
    "Xcode (MacOSX)"
)

jucer_export_target_configuration(
    "Xcode (MacOSX)"
    NAME "Debug"
    DEBUG_MODE ON
    BINARY_NAME "MasterEars"
)

jucer_export_target_configuration(
    "Xcode (MacOSX)"
    NAME "Release"
    DEBUG_MODE OFF
    BINARY_NAME "MasterEars"
)

jucer_export_target(
    "Visual Studio 2017"
)

jucer_export_target_configuration(
    "Visual Studio 2017"
    NAME "Debug"
    DEBUG_MODE ON
)

jucer_export_target_configuration(
    "Visual Studio 2017"
    NAME "Release"
    DEBUG_MODE OFF
)

jucer_export_target(
    "Linux Makefile"
)

jucer_export_target_configuration(
    "Linux Makefile"
    NAME "Debug"
    DEBUG_MODE ON
    BINARY_NAME "MasterEars"
)

jucer_export_target_configuration(
    "Linux Makefile"
    NAME "Release"
    DEBUG_MODE OFF
    BINARY_NAME "MasterEars"
)

jucer_project_end()

