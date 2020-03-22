#include "SessionComponent.h"
#include "../DataManager.h"

SessionComponent::SessionComponent (Configuration& config) :
    AudioAppComponent (DataManager::getInstance()->getAudioDeviceManager()),
    waveform (config.file, source),
    numTrials (config.numTrials)
{
    auto reader = DataManager::getInstance()->getAudioFormatManager().createReaderFor (config.file);
    readerSource = std::make_unique<AudioFormatReaderSource> (reader, true);
    source.setSource (readerSource.get(), 0, nullptr, reader->sampleRate);
    loopEndTime = source.getLengthInSeconds();
    setAudioChannels (0, 2);

    addAndMakeVisible (playPauseButton);
    playPauseButton.onClick = [=]
    {
        if (source.isPlaying())
        {
            source.stop();
            playPauseButton.setButtonText ("Play");
        }
        else
        {
            source.start();
            playPauseButton.setButtonText ("Pause");
        }
    };

    addAndMakeVisible (waveform);
    waveform.addPlayheadListener (this);

    addAndMakeVisible (freqButtons);
    freqButtons.addListener (this);
    
    addAndMakeVisible (trialsLabel);
    trialsLabel.setText (String (trialNum) + "/" + String (config.numTrials), dontSendNotification);
}

SessionComponent::~SessionComponent()
{
    source.stop();
    shutdownAudio();
}

void SessionComponent::prepareToPlay (int samplesPerBlock, double sampleRate)
{
    source.prepareToPlay (samplesPerBlock, sampleRate);
}

void SessionComponent::releaseResources()
{
    source.releaseResources();
}

void SessionComponent::getNextAudioBlock (const AudioSourceChannelInfo& buffer)
{
    if (readerSource.get() == nullptr)
    {
        buffer.clearActiveBufferRegion();
        return;
    }

    // looping...
    if (source.getCurrentPosition() < loopStartTime || source.getCurrentPosition() > loopEndTime)
        source.setPosition (loopStartTime);

    source.getNextAudioBlock (buffer);
}

void SessionComponent::playheadMoved (double newPosition)
{
    source.setPosition (newPosition * source.getLengthInSeconds());
}

void SessionComponent::loopStartMoved (double newPosition)
{
    loopStartTime = newPosition * source.getLengthInSeconds();
}

void SessionComponent::loopEndMoved (double newPosition)
{
    loopEndTime = newPosition * source.getLengthInSeconds();
}

void SessionComponent::resized()
{
    waveform.setBounds (10, 15, getWidth() - 20, 50);
    playPauseButton.setBounds ((getWidth() - 50) / 2, 100, 100, 30);
    freqButtons.setBounds (10, 175, getWidth() - 20, 125);
    trialsLabel.setBounds (10, 325, 50, 30);
}

void SessionComponent::freqBandSelected (int band)
{
    trialNum++;
    trialsLabel.setText (String (trialNum) + "/" + String (numTrials), dontSendNotification);
}
