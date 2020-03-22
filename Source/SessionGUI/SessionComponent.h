#ifndef SESSIONCOMPONENT_H_INCLUDED
#define SESSIONCOMPONENT_H_INCLUDED

#include "../Logic/Configuration.h"
#include "../Logic/Logic.h"
#include "WaveformViewer.h"
#include "FreqButtons.h"

class SessionComponent : public AudioAppComponent,
                         private WaveformViewer::PlayheadListener,
                         private FreqButtons::Listener
{
public:
    SessionComponent (Configuration* config);
    ~SessionComponent();

    void prepareToPlay (int samplesPerBlock, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const AudioSourceChannelInfo& buffer) override;

    void resized() override;

    void playheadMoved (double newPosition) override;
    void loopStartMoved (double newPosition) override;
    void loopEndMoved (double newPosition) override;

    void freqBandSelected (int band) override;

    struct Listener
    {
        ~Listener() {}
        virtual void sessionComplete (Logic* /*logic*/) {}
    };

    void addListener (Listener* l) { listeners.add (l); }
    void removeListener (Listener* l) { listeners.remove (l); }

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

    std::unique_ptr<Configuration> config;
    void startTrial();
    std::unique_ptr<Logic> logic;
    ListenerList<Listener> listeners;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SessionComponent)
};

#endif // SESSIONCOMPONENT_H_INCLUDED

