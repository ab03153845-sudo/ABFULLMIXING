#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

class AQVocalStudioAudioProcessor : public juce::AudioProcessor
{
public:
    AQVocalStudioAudioProcessor();
    ~AQVocalStudioAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float getInputRMS() const { return inputRMS.load(); }
    float getOutputRMS() const { return outputRMS.load(); }
    bool isInputClipping() const { return inputClipping.load(); }

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts;

private:
    std::atomic<float> inputRMS { 0.0f };
    std::atomic<float> outputRMS { 0.0f };
    std::atomic<bool> inputClipping { false };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AQVocalStudioAudioProcessor)
};
