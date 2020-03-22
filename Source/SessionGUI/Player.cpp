#include "Player.h"
#include "../DataManager.h"

Player::Player (const File& file) :
    AudioAppComponent (DataManager::getInstance()->getAudioDeviceManager()),
    waveform (file, source)
{
    auto reader = DataManager::getInstance()->getAudioFormatManager().createReaderFor (file);
    readerSource = std::make_unique<AudioFormatReaderSource> (reader, true);
    source.setSource (readerSource.get(), 0, nullptr, reader->sampleRate);
    loopEndTime = source.getLengthInSeconds();
    source.setGain (Decibels::decibelsToGain (-9.0f)); // make sure filter doesn't cause clipping!
    setAudioChannels (0, 2);

    addAndMakeVisible (playPauseButton);
    playPauseButton.onClick = [=] { playPauseButtonClicked(); };

    addAndMakeVisible (waveform);
    waveform.addPlayheadListener (this);

    addAndMakeVisible (filterButton);
    filterButton.setButtonText ("Filter Enabled");
}

Player::~Player()
{
    source.stop();
    shutdownAudio();
}

void Player::prepareToPlay (int samplesPerBlock, double sampleRate)
{
    source.prepareToPlay (samplesPerBlock, sampleRate);
    for (int ch = 0; ch < 2; ++ch)
        filter[ch].reset (sampleRate, filterButton.getToggleState());
}

void Player::releaseResources()
{
    source.releaseResources();
}

void Player::getNextAudioBlock (const AudioSourceChannelInfo& buffer)
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

    // filter
    for (int ch = 0; ch < 2; ++ch)
    {
        filter[ch].setEnabled (filterButton.getToggleState());
        filter[ch].processBlock (&buffer.buffer->getWritePointer (ch)[buffer.startSample], buffer.numSamples);
    }
}

void Player::playPauseButtonClicked()
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
}

void Player::playheadMoved (double newPosition)
{
    source.setPosition (newPosition * source.getLengthInSeconds());
    DBG ("Setting playhead position: " +
        String (newPosition * source.getLengthInSeconds()) + " seconds");
}

void Player::loopStartMoved (double newPosition)
{
    loopStartTime = newPosition * source.getLengthInSeconds();
    DBG ("Setting loop start position: " + String (loopStartTime) + " seconds");
}

void Player::loopEndMoved (double newPosition)
{
    loopEndTime = newPosition * source.getLengthInSeconds();
    DBG ("Setting loop end position: " + String (loopStartTime) + " seconds");
}

void Player::setFilterSpec (float freq, float gainDB)
{
    for (int ch = 0; ch < 2; ++ch)
        filter[ch].setFilterSpec (freq, gainDB);
}

void Player::resized()
{
    waveform.setBounds (10, 15, getWidth() - 20, 50);
    playPauseButton.setBounds ((getWidth() - 50) / 2, 100, 100, 30);
    filterButton.setBounds (getWidth() - 130, 100, 120, 30);
}
