#ifndef PLAYHER_H_INCLUDED
#define PLAYHER_H_INCLUDED

#include "../Backend/Filter.h"
#include "WaveformViewer.h"

class Player : public AudioAppComponent,
               private ChangeListener,
               private WaveformViewer::PlayheadListener
{
public:
    Player (const File& file);
    ~Player();

    void prepareToPlay (int samplesPerBlock, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const AudioSourceChannelInfo& buffer) override;

    void resized() override;
    void playPauseButtonClicked();

    void playheadMoved (double newPosition) override;
    void loopStartMoved (double newPosition) override;
    void loopEndMoved (double newPosition) override;
    void changeListenerCallback (ChangeBroadcaster* source) override;

    void stopPlayer() { source.stop(); }
    void setFilterSpec (float freq, float gainDB);

private:
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource source;
    double loopStartTime = 0.0;
    double loopEndTime = 0.0;

    WaveformViewer waveform;
    TextButton playPauseButton { "Play" };

    ToggleButton filterButton;
    Filter filter[2];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Player)
};

#endif // PLAYHER_H_INCLUDED
