#include "SetupComponent.h"

SetupComponent::SetupComponent()
{
    addAndMakeVisible (fileButton);
    fileButton.onClick = [=] { loadFile(); };

    addAndMakeVisible (nextButton);
    nextButton.onClick = [=] { nextButtonPressed(); };

    auto setupLabel = [=] (Label& label, String text)
    {
        addAndMakeVisible (label);
        label.setText (text, dontSendNotification);
        label.setJustificationType (Justification::right);
    };

    setupLabel (fileLabel, "[No File]");
    setupLabel (numTrialsLabel, "Number of trials: ");

    auto setupComboBox = [=] (ComboBox& box, StringArray choices, int default = 0)
    {
        addAndMakeVisible (box);
        box.addItemList (choices, 1);
        box.setSelectedItemIndex (default, dontSendNotification);
    };

    setupComboBox (eqTypeBox, Configuration::getTypeChoices());
    setupComboBox (eqAmtBox, Configuration::getAmtChoices(), 1);
    setupComboBox (numTrialsBox, StringArray ({ "5", "10", "15", "20" }), 1);

    addAndMakeVisible (instructions);
    instructions.setMultiLine (true);
    instructions.setReadOnly (true);
    instructions.setScrollbarsShown (true);
    instructions.setText (
"EQ Listening Test:\n\n\
Choose a song to use for your test, choose \
whether the EQ will boost or cut frequency bands \
and the amount by which the EQ will boost or cut.\n\n\
For each trial of the test, the EQ will create a filter \
that boosts or cuts a certain frequency band. You must \
guess which band is being effected. You may toggle the \
filter on or off, and adjust the playback of the song \
by moving the playhead or the loop markers.\n\n\
If you guess the frequency band correctly, you \
will be awarded 10 points. If you are off by one \
band, you will be awarded 9 points, 8 points for \
being two bands away, and so on. Upon completing the \
test, you may view and save your results. Enjoy!");
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

    instructions.setBounds (50, 300, getWidth() - 100, 100);
}

void SetupComponent::loadFile()
{
    FileChooser fileChooser ("Select file", File(), DataManager::getInstance()->getAudioFormatManager()
        .getWildcardForAllFormats(), true);

    if (fileChooser.browseForFileToOpen())
    {
        auto result = fileChooser.getResult();
        fileLabel.setText (result.getFileName(), dontSendNotification);
        file = std::make_unique<File> (result);
    }
}

void SetupComponent::nextButtonPressed()
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
}

