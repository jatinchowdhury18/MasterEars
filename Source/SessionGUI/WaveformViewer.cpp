#include "WaveformViewer.h"

enum
{
    cacheSize = 5,
    thumbSamples = 1024,
    hash = 0x2345,
};

WaveformViewer::WaveformViewer (File& file)
{
    formatManager.registerBasicFormats();

    thumbnailCache = std::make_unique<AudioThumbnailCache> (cacheSize);
    thumbnail = std::make_unique<AudioThumbnail> (thumbSamples,
        formatManager, *thumbnailCache.get());

    thumbnail->setSource (new FileInputSource (file));
}

void WaveformViewer::paint (Graphics& g)
{
    g.setColour (Colours::red);
    thumbnail->drawChannels (g, getLocalBounds(), 0, thumbnail->getTotalLength(), 1.0f);
}

