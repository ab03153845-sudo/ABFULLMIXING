#include "PluginProcessor.h"
#include "PluginEditor.h"

AQVocalStudioAudioProcessor::AQVocalStudioAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
       apvts(*this, nullptr, "Parameters", createParameterLayout())
{
}

AQVocalStudioAudioProcessor::~AQVocalStudioAudioProcessor() {}

const juce::String AQVocalStudioAudioProcessor::getName() const { return JucePlugin_Name; }
bool AQVocalStudioAudioProcessor::acceptsMidi() const { return false; }
bool AQVocalStudioAudioProcessor::producesMidi() const { return false; }
bool AQVocalStudioAudioProcessor::isMidiEffect() const { return false; }
double AQVocalStudioAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int AQVocalStudioAudioProcessor::getNumPrograms() { return 1; }
int AQVocalStudioAudioProcessor::getCurrentProgram() { return 0; }
void AQVocalStudioAudioProcessor::setCurrentProgram (int) {}
const juce::String AQVocalStudioAudioProcessor::getProgramName (int) { return {}; }
void AQVocalStudioAudioProcessor::changeProgramName (int, const juce::String&) {}

void AQVocalStudioAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {}
void AQVocalStudioAudioProcessor::releaseResources() {}

bool AQVocalStudioAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    return true;
}

void AQVocalStudioAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float inRMS = buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    inputRMS.store(inRMS);
    inputClipping.store(buffer.getMagnitude(0, buffer.getNumSamples()) > 0.99f);

    float outRMS = buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    outputRMS.store(outRMS);
}

bool AQVocalStudioAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* AQVocalStudioAudioProcessor::createEditor()
{
    return new AQVocalStudioAudioProcessorEditor (*this);
}

void AQVocalStudioAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void AQVocalStudioAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout AQVocalStudioAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back (std::make_unique<juce::AudioParameterFloat>("inputGain", "Input Gain", -24.0f, 24.0f, 0.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("outputCeiling", "Output Ceiling", -12.0f, 0.0f, -0.1f));
    return { params.begin(), params.end() };
}
