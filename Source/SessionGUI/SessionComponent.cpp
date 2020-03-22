#include "SessionComponent.h"

SessionComponent::SessionComponent (Configuration* config) :
    player (config->file),
    numTrials (config->numTrials),
    config (config),
    logic (new Logic (config))
{
    addAndMakeVisible (player);
    addAndMakeVisible (freqButtons);
    freqButtons.addListener (this);
    
    addAndMakeVisible (trialsLabel);
    trialsLabel.setText (String (trialNum+1) + "/" + String (numTrials), dontSendNotification);

    DBG ("STARTING SESSION...");
    startTrial();
}

void SessionComponent::resized()
{
    player.setBounds (0, 0, getWidth(), 150);
    freqButtons.setBounds (10, 175, getWidth() - 20, 125);
    trialsLabel.setBounds (10, 325, 50, 30);
}

void SessionComponent::startTrial()
{
    float freq, gainDB;
    logic->getNextFilterSpec (freq, gainDB);
    DBG ("Setting filter freq: " + String (freq) + " Hz");
    DBG ("Setting filter gain: " + String (gainDB) + " dB");
    
    player.setFilterSpec (freq, gainDB);
}

void SessionComponent::freqBandSelected (int band)
{
    trialNum++;
    trialsLabel.setText (String (trialNum+1) + "/" + String (numTrials), dontSendNotification);
    logic->guessMade (band);
    
    if (trialNum < numTrials)
        startTrial();
    else
    {
        player.stopPlayer();
        DBG ("ENDING SESSION...");
        listeners.call (&Listener::sessionComplete, logic.release());
    }
}
