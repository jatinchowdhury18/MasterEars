#include "WaveformViewer.h"
#include "../DataManager.h"
#include "../MyLNF.h"

enum
{
    cacheSize = 5,
    thumbSamples = 1024,
    hash = 0x2345,
};

WaveformViewer::WaveformViewer (const File& file, const AudioTransportSource& source) :
    source (source)
{
    thumbnailCache = std::make_unique<AudioThumbnailCache> (cacheSize);
    thumbnail = std::make_unique<AudioThumbnail> (thumbSamples,
        DataManager::getInstance()->getAudioFormatManager(),
        *thumbnailCache.get());

    loadingWindow = std::make_unique<LoadingWindow> (thumbnail.get());

    thumbnail->setSource (new FileInputSource (file));
    loadingWindow->runThread();

    repaint();

    startTimer (20);
}

void WaveformViewer::timerCallback()
{
    if (markerDragging[Playhead] == true)
        return;

    markers[Playhead] = float (source.getCurrentPosition() / source.getLengthInSeconds());

    MessageManagerLock mml;
    repaint();
}

void WaveformViewer::paint (Graphics& g)
{
    // draw waveform
    g.setColour (MyColours::blue);
    thumbnail->drawChannels (g, getLocalBounds(), 0, thumbnail->getTotalLength(), 1.0f);

    // grey out areas excluded by loop region
    g.setColour (MyColours::black);
    g.setOpacity (0.6f);
    g.fillRect (0.0f, 0.0f, markers[LoopStart] * getWidth(), (float) getHeight());
    g.fillRect (markers[LoopEnd] * getWidth(), 0.0f, (1.0f - markers[LoopEnd]) * getWidth(), (float) getHeight());

    // draw loop markers
    auto drawMarker = [=] (Graphics& g, float xMark, Colour colour)
    {
        g.setColour (colour);
        g.drawLine (xMark * getWidth(), 0.0f,
            xMark * getWidth(), (float) getHeight(), 3.0f);
    };    
    
    drawMarker (g, markers[LoopStart], MyColours::green);
    drawMarker (g, markers[LoopEnd],   MyColours::green);
    drawMarker (g, markers[Playhead],  MyColours::red);
}

int WaveformViewer::mouseOverMarker (const MouseEvent& e)
{
    const int range = getWidth() / 30;
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
    auto setMarker = [=] (MarkerType mark)
    {
        float lowerLimit = mark == LoopStart ? 0.0f : markers[LoopStart];
        float upperLimit = mark == LoopEnd   ? 1.0f : markers[LoopEnd];

        markers[mark] = jlimit (lowerLimit, upperLimit, (float) e.x / (float) getWidth());
        repaint(); 
    };

    for (int i = 0; i < 3; ++i)
    {
        if (markerDragging[i])
        {
            setMarker ((MarkerType) i);
            return;
        }
    }

    auto marker = mouseOverMarker (e);
    if (Range<int> (0, 3).contains (marker))
    {
        setMarker ((MarkerType) marker);
        markerDragging[marker] = true;
    }
}

void WaveformViewer::mouseUp (const MouseEvent&)
{
    void (PlayheadListener::*listenerFuncs[]) (double) = { &PlayheadListener::playheadMoved,
                                                           &PlayheadListener::loopStartMoved, 
                                                           &PlayheadListener::loopEndMoved };

    for (int i = 0; i < 3; ++i)
    {
        if (markerDragging[i])
        {
            markerDragging[i] = false;
            playheadListeners.call (listenerFuncs[i], markers[i]);
        }
    }
}
