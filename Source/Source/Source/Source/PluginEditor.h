#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

class AQVocalStudioAudioProcessorEditor : public juce::AudioProcessorEditor,
                                          private juce::Timer
{
public:
    AQVocalStudioAudioProcessorEditor (AQVocalStudioAudioProcessor&);
    ~AQVocalStudioAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;

    AQVocalStudioAudioProcessor& audioProcessor;

    juce::Label titleLabel;
    juce::Slider inputGainSlider;
    juce::Slider outputCeilingSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputCeilingAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AQVocalStudioAudioProcessorEditor)
};
