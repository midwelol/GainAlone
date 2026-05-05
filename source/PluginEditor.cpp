#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 400);
    gainSlider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(-24.0f, 24.0f);
    gainSlider.setValue(0.0f);
    gainSlider.addListener(this);
    addAndMakeVisible (gainSlider);
}

PluginEditor::~PluginEditor()
{
}

void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


}

void PluginEditor::resized()
{
    // layout the positions of your child components here
    auto area = getLocalBounds();
    area.removeFromBottom(50);
    gainSlider.setBounds(getLocalBounds());
}

void PluginEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        processorRef.rawVolume = pow(10, gainSlider.getValue() / 20);
    }
}
