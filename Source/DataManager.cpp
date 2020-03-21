#include "DataManager.h"

JUCE_IMPLEMENT_SINGLETON (DataManager)

DataManager::DataManager()
{
    formatManager.registerBasicFormats();
}

DataManager::~DataManager()
{
    clearSingletonInstance();
}

AudioFormatManager& DataManager::getAudioFormatManager()
{
    return formatManager;
}
