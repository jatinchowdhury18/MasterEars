#ifndef WAVEFORMVIEWER_H_INCLUDED
#define WAVEFORMVIEWER_H_INCLUDED

#include "ThumbnailLoadingWindow.h"

class WaveformViewer : public Component,
                       private Timer
{
public:
    WaveformViewer (File& file, const AudioTransportSource& source);

    void paint (Graphics& g) override;

    void mouseMove (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;
    int mouseOverMarker (const MouseEvent& e);

    struct PlayheadListener
    {
    public:
        virtual ~PlayheadListener() {}
        virtual void playheadMoved (double /*newPosition*/) {}
        virtual void loopStartMoved (double /*newPosition*/) {}
        virtual void loopEndMoved (double /*newPosition*/) {}
    };

    void addPlayheadListener (PlayheadListener* l) { playheadListeners.add (l); }
    void removePlayheadListener (PlayheadListener* l) { playheadListeners.remove (l); }

private:
    std::unique_ptr<LoadingWindow> loadingWindow;

    const AudioTransportSource& source;
    void timerCallback();

    std::unique_ptr<AudioThumbnailCache> thumbnailCache;
    std::unique_ptr<AudioThumbnail> thumbnail;

    enum MarkerType
    {
        Playhead,
        LoopStart,
        LoopEnd
    };

    float markers[3] = { 0.0f, 0.0f, 1.0f };
    bool markerDragging[3] = { false, false, false };
    ListenerList<PlayheadListener> playheadListeners;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformViewer)    
};

#endif // WAVEFORMVIEWER_H_INCLUDED

