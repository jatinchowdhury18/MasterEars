#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize (500, 500);

    addAndMakeVisible (setupComponent);
    setupComponent.addListener (this);
}

void MainComponent::resized()
{
    setupComponent.setBounds (0, 30, getWidth(), 450);

    repaint();
}

void MainComponent::paint(Graphics& g)
{
    g.fillAll (Colours::black);

    g.setColour (Colours::red);
    g.setFont (18.0f);
    g.drawFittedText ("Master Ears", getLocalBounds().getCentreX() - 50, 0, 100, 30,
        Justification::centred, 1);
}

void MainComponent::setupComplete (File* file)
{
    setupComponent.setVisible (false);
}

