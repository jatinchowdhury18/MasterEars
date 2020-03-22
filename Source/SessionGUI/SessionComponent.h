#ifndef SESSIONCOMPONENT_H_INCLUDED
#define SESSIONCOMPONENT_H_INCLUDED

#include "../Logic/Configuration.h"
#include "WaveformViewer.h"
#include "FreqButtons.h"

class SessionComponent : public AudioAppComponent,
                         private WaveformViewer::PlayheadListener,
                         private FreqButtons::Listener
{
public:
    SessionComponent (Configuration& config);
    ~SessionComponent();

    void prepareToPlay (int samplesPerBlock, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const AudioSourceChannelInfo& buffer) override;

    void resized() override;

    void playheadMoved (double newPosition) override;
    void loopStartMoved (double newPosition) override;
    void loopEndMoved (double newPosition) override;

    void freqBandSelected (int band) override;

private:
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource source;
    double loopStartTime = 0.0;
    double loopEndTime = 0.0;

    TextButton playPauseButton { "Play" };

    WaveformViewer waveform;
    FreqButtons freqButtons;

    int trialNum = 0;
    const int numTrials;
    Label trialsLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SessionComponent)
};

#endif // SESSIONCOMPONENT_H_INCLUDED

