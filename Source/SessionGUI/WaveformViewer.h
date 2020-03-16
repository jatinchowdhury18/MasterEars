#ifndef WAVEFORMVIEWER_H_INCLUDED
#define WAVEFORMVIEWER_H_INCLUDED

#include "JuceHeader.h"

class WaveformViewer : public Component
{
public:
    WaveformViewer (File& file);

    void paint (Graphics& g) override;

private:
    AudioFormatManager formatManager;
    std::unique_ptr<AudioThumbnailCache> thumbnailCache;
    std::unique_ptr<AudioThumbnail> thumbnail;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformViewer)    
};

#endif // WAVEFORMVIEWER_H_INCLUDED

