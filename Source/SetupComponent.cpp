#include "SetupComponent.h"
#include "MyLNF.h"

SetupComponent::SetupComponent()
{
    // initialize buttons
    auto setupButton = [=] (TextButton& button, Colour colour,
        std::function<void()> onClick)
    {
        addAndMakeVisible (button);
        button.setColour (TextButton::buttonOnColourId, colour);
        button.onClick = onClick;
    };

    setupButton (fileButton, MyColours::red, [=] { loadFile(); });
    setupButton (nextButton, MyColours::green, [=] { nextButtonPressed(); });

    // initialize labels
    addAndMakeVisible (fileLabel);
    fileLabel.setText ("[No File Selected]", dontSendNotification);
    fileLabel.setJustificationType (Justification::left);

    // initialize comboboxes
    auto setupComboBox = [=] (ComboBox& box, StringArray choices, int def = 0)
    {
        addAndMakeVisible (box);
        box.addItemList (choices, 1);
        box.setSelectedItemIndex (def, dontSendNotification);
        box.setJustificationType (Justification::centred);
    };

    setupComboBox (eqTypeBox, Configuration::getTypeChoices());
    setupComboBox (eqAmtBox, Configuration::getAmtChoices(), 1);
    setupComboBox (numTrialsBox, StringArray ({ "5", "10", "15", "20" }), 1);
}

void SetupComponent::resized()
{
    const int dim = getHeight() / 6;
    const int buttonWidth = (getWidth() - 6*dim) / 3;

    fileButton.setBounds (2*dim, dim, buttonWidth, dim);
    fileLabel.setBounds (fileButton.getRight() + dim, dim, 2*buttonWidth, dim);
    fileLabel.setFont (Font (float (dim) / 2));

    nextButton.setBounds ((getWidth() - buttonWidth) / 2, 5*dim, buttonWidth, dim);

    eqTypeBox.setBounds (2*dim, 3*dim, buttonWidth, dim);
    eqAmtBox.setBounds (eqTypeBox.getRight() + dim, 3*dim, buttonWidth, dim);
    numTrialsBox.setBounds (eqAmtBox.getRight() + dim, 3*dim, buttonWidth, dim);
}

void SetupComponent::paint (Graphics& g)
{
    const int dim = getHeight() / 6;
    auto drawText = [=] (Graphics& g, String text, int y)
    {
        g.drawFittedText (text, dim, y, getWidth() - 2*dim, dim,
            Justification::left, 1);
    };

    g.setColour (Colours::white);
    g.setFont (float(dim) / 2);
    drawText (g, "Step 1: Load a song to use for your test", 0);
    drawText (g, "Step 2: Choose your settings", 2*dim);
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
        bubble.reset (new BubbleMessageComponent (500));
        addChildComponent (bubble.get());

        AttributedString attStr;
        attStr.append ("Must choose file before continuing!", Font (24.0f));
        attStr.setColour (MyColours::red);

        auto rect = getLocalArea (&nextButton, nextButton.getLocalBounds());
        bubble->showAt (rect, attStr, 2000, true, false);
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

