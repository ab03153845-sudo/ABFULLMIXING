cmake_minimum_required(VERSION 3.22)

project(AQVocalStudio VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find or include JUCE
find_package(JUCE CONFIG REQUIRED)

juce_add_plugin(AQVocalStudio
    COMPANY_NAME "Abdullah Qureshi"
    PLUGIN_NAME "AQ Vocal Studio"
    PLUGIN_MANUFACTURER_CODE "AQVS"
    PLUGIN_CODE "Aqvs"
    FORMATS VST3 Standalone
    PRODUCT_NAME "AQ Vocal Studio"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
)

target_sources(AQVocalStudio PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

target_compile_definitions(AQVocalStudio PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(AQVocalStudio PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_audio_formats
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_dsp
)
