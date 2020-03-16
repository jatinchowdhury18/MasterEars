#include "SessionComponent.h"

SessionComponent::SessionComponent (File& file) :
    waveform (file)
{
    addAndMakeVisible (waveform);
}

void SessionComponent::resized()
{
    waveform.setBounds (20, 0, getWidth() - 40, 50);
}

void SessionComponent::paint (Graphics& g)
{
    // g.fillAll (Colours::blue);
}

