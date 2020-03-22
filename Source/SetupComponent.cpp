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
            std::unique_ptr<Configuration> config = std::make_unique<Configuration> (*file.get(),
                static_cast<EQType> (eqTypeBox.getSelectedItemIndex()),
                static_cast<EQAmt> (eqAmtBox.getSelectedItemIndex()),
                numTrialsBox.getItemText (numTrialsBox.getSelectedItemIndex()).getIntValue());

            listeners.call (&Listener::setupComplete, config.release());
        }       
    };

    addAndMakeVisible (fileLabel);
    fileLabel.setText ("[No File]", dontSendNotification);
    fileLabel.setJustificationType (Justification::right);

    addAndMakeVisible (eqTypeBox);
    eqTypeBox.addItemList (Configuration::getTypeChoices(), 1);
    eqTypeBox.setSelectedItemIndex (0, dontSendNotification);

    addAndMakeVisible (eqAmtBox);
    eqAmtBox.addItemList (Configuration::getAmtChoices(), 1);
    eqAmtBox.setSelectedItemIndex (1, dontSendNotification);

    addAndMakeVisible (numTrialsLabel);
    numTrialsLabel.setText ("Number of trials:", dontSendNotification);
    numTrialsLabel.setJustificationType (Justification::right);

    addAndMakeVisible (numTrialsBox);
    numTrialsBox.addItemList (StringArray ({ "5", "10", "15", "20" }), 1);
    numTrialsBox.setSelectedItemIndex (1, dontSendNotification);
}

void SetupComponent::resized()
{
    fileButton.setBounds (100, 100, 100, 30);
    nextButton.setBounds (220, 100, 50, 30);
    fileLabel.setBounds (0, 135, 200, 30);

    eqTypeBox.setBounds (100, 200, 200, 30);
    eqAmtBox.setBounds (320, 200, 100, 30);

    numTrialsLabel.setBounds (100, 250, 200, 30);
    numTrialsBox.setBounds (320, 250, 100, 30);
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

