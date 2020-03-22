#include "MainComponent.h"
#include "DataManager.h"

MainComponent::MainComponent()
{
    setSize (500, 500);

    DataManager::getInstance();

    addAndMakeVisible (setupComponent);
    setupComponent.addListener (this);

    addAndMakeVisible (settingsButton);
    settingsButton.onClick = [=] { DataManager::getInstance()->showAudioSettings(); };
}

MainComponent::~MainComponent()
{
    sessComponent.reset (nullptr);
    DataManager::deleteInstance();
}

void MainComponent::resized()
{
    Rectangle<int> bounds (0, 30, getWidth(), 450);
    setupComponent.setBounds (bounds);
    settingsButton.setBounds (10, getHeight() - 50, 100, 30);
    
    if (sessComponent.get() != nullptr)
        sessComponent->setBounds (bounds);

    if (resComponent.get() != nullptr)
        resComponent->setBounds (bounds);

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

void MainComponent::setupComplete (Configuration* config)
{
    setupComponent.setVisible (false);
    
    sessComponent = std::make_unique<SessionComponent> (config);
    sessComponent->addListener (this);
    addAndMakeVisible (sessComponent.get());
    resized();
}

void MainComponent::sessionComplete (Logic* logic)
{
    sessComponent->setVisible (false);
    resComponent = std::make_unique<ResultsComponent> (logic);
    addAndMakeVisible (resComponent.get());
    resized();
}

