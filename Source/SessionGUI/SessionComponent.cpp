#include "SessionComponent.h"

SessionComponent::SessionComponent (File& file) :
    waveform (file)
{
    addAndMakeVisible (waveform);
}

void SessionComponent::resized()
{
    waveform.setBounds (10, 15, getWidth() - 20, 50);
}

void SessionComponent::paint (Graphics& g)
{
    // g.fillAll (Colours::blue);
}

