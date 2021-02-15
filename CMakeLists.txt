cmake_minimum_required(VERSION 3.12)
project(MasterEars VERSION 1.1.0)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(Modules/JUCE)

juce_add_gui_app(MasterEars
    COMPANY_NAME chowdsp
    PRODUCT_NAME "MasterEars"
    ICON_BIG Resources/MasterEarsIcon.png
)

juce_generate_juce_header(MasterEars)

target_sources(MasterEars PRIVATE
    Source/main.cpp
    Source/MainComponent.cpp
    Source/SetupComponent.cpp
    Source/DataManager.cpp
    Source/MyLNF.cpp
    Source/SessionGUI/SessionComponent.cpp
    Source/SessionGUI/WaveformViewer.cpp
    Source/SessionGUI/FreqButtons.cpp
    Source/SessionGUI/Player.cpp
    Source/ResultsGUI/ResultsComponent.cpp
    Source/ResultsGUI/ResultsList.cpp
    Source/Backend/Configuration.cpp
    Source/Backend/Logic.cpp
    Source/Backend/Filter.cpp
)

juce_add_binary_data(BinaryData SOURCES
    Resources/NunitoSans-Regular.ttf
    Resources/NunitoSans-Bold.ttf
    Resources/cog-solid.svg
    Resources/MasterEarsIcon.png
)

# Need to build BinaryData with -fPIC flag on Linux
set_target_properties(BinaryData PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE)

target_compile_definitions(MasterEars PUBLIC
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_REPORT_APP_USAGE=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(MasterEars
    PRIVATE
        BinaryData
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
