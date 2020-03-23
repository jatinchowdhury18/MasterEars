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
    const int dim = getHeight() / 6;
    player.setBounds (0, 0, getWidth(), int (3.5*dim));
    freqButtons.setBounds (10, player.getBottom(), getWidth() - 20, int (2.5*dim));
    trialsLabel.setBounds (10, freqButtons.getBottom() - dim, dim, dim);
    trialsLabel.setFont (float (dim) / 2);
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
