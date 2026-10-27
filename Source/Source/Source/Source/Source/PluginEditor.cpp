#include "PluginProcessor.h"
#include "PluginEditor.h"

AQVocalStudioAudioProcessorEditor::AQVocalStudioAudioProcessorEditor (AQVocalStudioAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (900, 600);

    titleLabel.setText("AQ VOCAL STUDIO — by Abdullah Qureshi", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    inputGainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(inputGainSlider);
    inputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "inputGain", inputGainSlider);

    outputCeilingSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outputCeilingSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(outputCeilingSlider);
    outputCeilingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "outputCeiling", outputCeilingSlider);

    startTimerHz(30);
}

AQVocalStudioAudioProcessorEditor::~AQVocalStudioAudioProcessorEditor() {}

void AQVocalStudioAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour::fromRGB (18, 20, 24));
    g.setColour (juce::Colour::fromRGB (46, 204, 113));
    g.fillRect (20, 50, getWidth() - 40, 2);
}

void AQVocalStudioAudioProcessorEditor::resized()
{
    titleLabel.setBounds (20, 10, getWidth() - 40, 30);
    inputGainSlider.setBounds (50, 100, 100, 100);
    outputCeilingSlider.setBounds (180, 100, 100, 100);
}

void AQVocalStudioAudioProcessorEditor::timerCallback()
{
    repaint();
}
