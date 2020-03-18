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
    AudioFormatManager formatManager;
    std::unique_ptr<AudioThumbnailCache> thumbnailCache;
    std::unique_ptr<AudioThumbnail> thumbnail;

    float loopStart = 0.0f;
    float loopEnd = 1.0f;
    float playhead = 0.5f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformViewer)    
};

#endif // WAVEFORMVIEWER_H_INCLUDED

