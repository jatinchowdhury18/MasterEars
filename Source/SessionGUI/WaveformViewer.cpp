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
    // draw waveform
    g.setColour (Colours::red);
    thumbnail->drawChannels (g, getLocalBounds(), 0, thumbnail->getTotalLength(), 1.0f);

    // draw loop markers
    auto drawMarker = [=] (Graphics& g, float xMark)
    {
        g.drawLine (xMark * getWidth(), 0.0f,
            xMark * getWidth(), (float) getHeight(), 2.0f);
    };    
    
    g.setColour (Colours::white);
    drawMarker (g, loopStart);
    drawMarker (g, loopEnd);
    drawMarker (g, playhead);

    // grey out areas excluded by loop region
    g.setColour (Colours::black);
    g.setOpacity (0.5f);
    g.fillRect (0.0f, 0.0f, loopStart * getWidth(), (float) getHeight());
    g.fillRect (loopEnd * getWidth(), 0.0f, (1.0f - loopEnd) * getWidth(), (float) getHeight());
}

int WaveformViewer::mouseOverMarker (const MouseEvent& e)
{
    const int range = 10;
    int count = 1;
    for (auto markX : { loopStart, loopEnd, playhead})
    {
        auto trueX = int (markX * getWidth());
        if (Range<int> (trueX - range, trueX + range).contains (e.x))
            return count;

        count++;
    }

    return 0; // mouse is not over any of them
}

void WaveformViewer::mouseMove (const MouseEvent& e)
{
    if (mouseOverMarker (e) > 0)
        setMouseCursor (MouseCursor::LeftRightResizeCursor);
    else
        setMouseCursor (MouseCursor::NormalCursor);
}

void WaveformViewer::mouseDrag (const MouseEvent& e)
{
    if (auto marker = mouseOverMarker (e))
    {
        switch (marker)
        {
        case 1:
            loopStart = (float) e.x / (float) getWidth();
            break;
        case 2:
            loopEnd = (float) e.x / (float) getWidth();
            break;
        case 3:
            playhead = (float) e.x / (float) getWidth();
            break;
        }
        
        repaint();
    }
}

void WaveformViewer::mouseUp (const MouseEvent& e)
{
}

