#include "SetupComponent.h"

SetupComponent::SetupComponent()
{
    addAndMakeVisible (fileButton);
    fileButton.onClick = [=] { loadFile(); };

    addAndMakeVisible (nextButton);
    nextButton.onClick = [=]
    {
        if (file.get() == nullptr)
        {
            bubble.reset (new BubbleMessageComponent (1000));
            addChildComponent (bubble.get());

            AttributedString attStr;
            attStr.append ("Must choose file!", Font (16.0f));
            attStr.setColour (Colours::white);            

            auto rect = getLocalArea (&nextButton, nextButton.getLocalBounds());

            bubble->showAt (rect, attStr, 1000, true, false);
        }
        else
        {
            listeners.call (&Listener::setupComplete, file.release());
        }       
    };

    addAndMakeVisible (fileLabel);
    fileLabel.setText ("[No File]", dontSendNotification);
    fileLabel.setJustificationType (Justification::centred);
}

void SetupComponent::paint (Graphics& g)
{
}

void SetupComponent::resized()
{
    fileButton.setBounds (100, 100, 100, 30);
    nextButton.setBounds (220, 100, 50, 30);
    fileLabel.setBounds (100, 150, 100, 30);
}

void SetupComponent::loadFile()
{
    FileChooser fileChooser ("Select file", File(), String ("*.wav"), true);

    if (fileChooser.browseForFileToOpen())
    {
        auto result = fileChooser.getResult();
        fileLabel.setText (result.getFileName(), dontSendNotification);
        file = std::make_unique<File> (result);
    }
}

