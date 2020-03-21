#include "WaveformViewer.h"
#include "../DataManager.h"

enum
{
    cacheSize = 5,
    thumbSamples = 1024,
    hash = 0x2345,
};

WaveformViewer::WaveformViewer (File& file)
{
    thumbnailCache = std::make_unique<AudioThumbnailCache> (cacheSize);
    thumbnail = std::make_unique<AudioThumbnail> (thumbSamples,
        DataManager::getInstance()->getAudioFormatManager(),
        *thumbnailCache.get());

    loadingWindow = std::make_unique<LoadingWindow> (thumbnail.get());

    thumbnail->setSource (new FileInputSource (file));
    loadingWindow->runThread();

    repaint();
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
    for (auto marker : markers)
        drawMarker (g, marker);

    // grey out areas excluded by loop region
    g.setColour (Colours::black);
    g.setOpacity (0.5f);
    g.fillRect (0.0f, 0.0f, markers[0] * getWidth(), (float) getHeight());
    g.fillRect (markers[1] * getWidth(), 0.0f, (1.0f - markers[1]) * getWidth(), (float) getHeight());
}

int WaveformViewer::mouseOverMarker (const MouseEvent& e)
{
    const int range = 10;
    int count = 0;
    for (auto markX : markers)
    {
        auto trueX = int (markX * getWidth());
        if (Range<int> (trueX - range, trueX + range).contains (e.x))
            return count;

        count++;
    }

    return -1; // mouse is not over any of them
}

void WaveformViewer::mouseMove (const MouseEvent& e)
{
    if (mouseOverMarker (e) >= 0)
        setMouseCursor (MouseCursor::LeftRightResizeCursor);
    else
        setMouseCursor (MouseCursor::NormalCursor);
}

void WaveformViewer::mouseDrag (const MouseEvent& e)
{
    auto setMarker = [=] (float& mark)
    { 
        mark = jlimit (0.0f, 1.0f, (float) e.x / (float) getWidth());
        repaint(); 
    };

    for (int i = 0; i < 3; ++i)
    {
        if (markerDragging[i])
        {
            setMarker (markers[i]);
            return;
        }
    }

    auto marker = mouseOverMarker (e);
    if (Range<int> (0, 3).contains (marker))
    {
        setMarker (markers[marker]);
        markerDragging[marker] = true;
    }
}

void WaveformViewer::mouseUp (const MouseEvent& e)
{
    for (int i = 0; i < 3; ++i)
        markerDragging[i] = false;
}

