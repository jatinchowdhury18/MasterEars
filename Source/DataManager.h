#ifndef DATAMANAGER_H_INCLUDED
#define DATAMANAGER_H_INCLUDED

#include "JuceHeader.h"

class SettingsWindow : public DocumentWindow
{
public:
    SettingsWindow (const String& name, AudioDeviceManager& manager) :
        DocumentWindow (name, Desktop::getInstance().getDefaultLookAndFeel()
            .findColour (ResizableWindow::backgroundColourId), DocumentWindow::allButtons),
        audioDeviceSelector (manager, 0, 0, 2, 2, false, false, true, true)
    {
        audioDeviceSelector.setSize (500, 300);
        setContentOwned (&audioDeviceSelector, true);
        centreWithSize (audioDeviceSelector.getWidth(), audioDeviceSelector.getHeight());
        setUsingNativeTitleBar (true);
        setDraggable (true);
        setVisible (true);
    }

    void closeButtonPressed() override { setVisible (false); }

private:
    AudioDeviceSelectorComponent audioDeviceSelector;
};

class DataManager
{
public:
    DataManager();
    ~DataManager();

    AudioFormatManager& getAudioFormatManager();
    AudioDeviceManager& getAudioDeviceManager();
    void showAudioSettings();

    JUCE_DECLARE_SINGLETON (DataManager, false)

private:
    AudioFormatManager formatManager;
    AudioDeviceManager audioDeviceManager;

    std::unique_ptr<SettingsWindow> settings;
};

#endif // DATAMANAGER_H_INCLUDED
