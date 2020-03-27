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
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/main.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/MainComponent.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/MainComponent.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SetupComponent.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SetupComponent.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/DataManager.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/DataManager.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/MyLNF.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/MyLNF.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SessionGUI/SessionComponent.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SessionGUI/SessionComponent.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SessionGUI/WaveformViewer.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SessionGUI/WaveformViewer.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SessionGUI/FreqButtons.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SessionGUI/FreqButtons.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SessionGUI/Player.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SessionGUI/Player.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/SessionGUI/ThumbnailLoadingWindow.h"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/ResultsGUI/ResultsComponent.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/ResultsGUI/ResultsComponent.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/ResultsGUI/ResultsList.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/ResultsGUI/ResultsList.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/Backend/Configuration.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/Backend/Configuration.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/Backend/Logic.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/Backend/Logic.cpp"
  .         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/Backend/Filter.h"
  x         .         .         "${CMAKE_CURRENT_LIST_DIR}/Source/Backend/Filter.cpp"
)

jucer_project_files("MasterEars/Resources"
# Compile   Xcode     Binary    File
#           Resource  Resource
  .         .         x         "${CMAKE_CURRENT_LIST_DIR}/Resources/NunitoSans-Regular.ttf"
  .         .         x         "${CMAKE_CURRENT_LIST_DIR}/Resources/NunitoSans-Bold.ttf"
  .         .         x         "${CMAKE_CURRENT_LIST_DIR}/Resources/cog-solid.svg"
  .         .         x         "${CMAKE_CURRENT_LIST_DIR}/Resources/MasterEarsIcon.png"
)

jucer_project_module(
    juce_audio_basics
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_project_module(
    juce_audio_devices
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_project_module(
    juce_audio_formats
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_project_module(
    juce_audio_processors
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_project_module(
    juce_audio_utils
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_project_module(
    juce_core
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_project_module(
    juce_data_structures
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_project_module(
    juce_events
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_project_module(
    juce_graphics
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_project_module(
    juce_gui_basics
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_project_module(
    juce_gui_extra
    PATH "${CMAKE_CURRENT_LIST_DIR}/../JUCE/modules"
)

jucer_export_target(
    "Xcode (MacOSX)"
    ICON_LARGE "${CMAKE_CURRENT_LIST_DIR}/Resources/MasterEarsIcon.png"
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
    ICON_LARGE "${CMAKE_CURRENT_LIST_DIR}/Resources/MasterEarsIcon.png"
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
    ICON_LARGE "${CMAKE_CURRENT_LIST_DIR}/Resources/MasterEarsIcon.png"
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

