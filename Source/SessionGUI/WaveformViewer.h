#ifndef WAVEFORMVIEWER_H_INCLUDED
#define WAVEFORMVIEWER_H_INCLUDED

#include "JuceHeader.h"

class WaveformViewer : public Component
{
public:
    WaveformViewer (File& file);

    void paint (Graphics& g) override;

    void mouseMove (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;
    int mouseOverMarker (const MouseEvent& e);

private:
    class LoadingWindow : public ThreadWithProgressWindow
    {
    public:
        LoadingWindow (AudioThumbnail* thumbnail) :
            ThreadWithProgressWindow ("Loading Audio...", true, false),
            thumbnail (thumbnail)
        {}

        void run() override
        {
            while (1)
            {
                if (threadShouldExit())
                    break;

                if (thumbnail->isFullyLoaded())
                {
                    // DBG ("Loaded!");
                    break;
                }
                
                setProgress (thumbnail->getProportionComplete());
                // DBG (String (thumbnail->getProportionComplete()));

                wait (10);
            }
        }

    private:
        const AudioThumbnail* thumbnail;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoadingWindow)
    };

    std::unique_ptr<LoadingWindow> loadingWindow;

    std::unique_ptr<AudioThumbnailCache> thumbnailCache;
    std::unique_ptr<AudioThumbnail> thumbnail;

    float markers[3] = { 0.0f, 1.0f, 0.5f };    // index 0 == loopStart
                                                // index 1 == loopEnd
                                                // index 2 == playhead
    bool markerDragging[3] = { false, false, false };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformViewer)    
};

#endif // WAVEFORMVIEWER_H_INCLUDED

