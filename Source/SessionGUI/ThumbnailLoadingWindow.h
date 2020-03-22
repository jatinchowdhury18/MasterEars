#ifndef THUMBNAILLOADINGWINDOW_H_INCLUDED
#define THUMBNAILLOADINGWINDOW_H_INCLUDED

#include "JuceHeader.h"

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
                break;
                
            setProgress (thumbnail->getProportionComplete());
            wait (10);
        }
    }

private:
    const AudioThumbnail* thumbnail;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoadingWindow)
};

#endif // THUMBNAILLOADINGWINDOW_H_INCLUDED
