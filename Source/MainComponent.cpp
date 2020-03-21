#include "MainComponent.h"
#include "DataManager.h"

MainComponent::MainComponent()
{
    setSize (500, 500);

    DataManager::getInstance();

    addAndMakeVisible (setupComponent);
    // addChildComponent (setupComponent);
    setupComponent.addListener (this);

    // addAndMakeVisible (sessComponent);
}

MainComponent::~MainComponent()
{
    DataManager::deleteInstance();
}

void MainComponent::resized()
{
    Rectangle<int> bounds (0, 30, getWidth(), 450);
    setupComponent.setBounds (bounds);
    
    if (sessComponent.get() != nullptr)
        sessComponent->setBounds (bounds);

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
    
    sessComponent = std::make_unique<SessionComponent> (*file);
    addAndMakeVisible (sessComponent.get());
    resized();
}

