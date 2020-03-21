#ifndef DATAMANAGER_H_INCLUDED
#define DATAMANAGER_H_INCLUDED

#include "JuceHeader.h"

class DataManager
{
public:
    DataManager();
    ~DataManager();

    AudioFormatManager& getAudioFormatManager();

    JUCE_DECLARE_SINGLETON (DataManager, false)

private:
    AudioFormatManager formatManager;
};

#endif // DATAMANAGER_H_INCLUDED
