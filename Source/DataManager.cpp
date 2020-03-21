#include "DataManager.h"

JUCE_IMPLEMENT_SINGLETON (DataManager)

DataManager::DataManager()
{
    formatManager.registerBasicFormats();
    audioDeviceManager.initialiseWithDefaultDevices (0, 2);
}

DataManager::~DataManager()
{
    clearSingletonInstance();
}

AudioFormatManager& DataManager::getAudioFormatManager()
{
    return formatManager;
}

AudioDeviceManager& DataManager::getAudioDeviceManager()
{
    return audioDeviceManager;
}

void DataManager::showAudioSettings()
{
    settings = std::make_unique<SettingsWindow> ("Settings", audioDeviceManager);
}
