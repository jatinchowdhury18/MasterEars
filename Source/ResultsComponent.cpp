#include "ResultsComponent.h"
#include "MyLNF.h"

ResultsComponent::ResultsComponent (Logic* logic) :
    logic (logic)
{
    addAndMakeVisible (text);
    text.setMultiLine (true);
    text.setFont (18.0f);
    text.setReadOnly (true);
    text.setText (logic->getResults());
    text.setScrollbarsShown (true);

    addAndMakeVisible (saveButton);
    saveButton.setColour (TextButton::buttonOnColourId, MyColours::green);
    saveButton.onClick = [=] { saveToFile(); };
}

void ResultsComponent::resized()
{
    const int h = getHeight() / 6;
    const int w = getWidth() / 5;

    text.setBounds (getLocalBounds()
        .withTrimmedBottom (2*h)
        .withTrimmedLeft (10)
        .withTrimmedRight (10));

    saveButton.setBounds ((getWidth() - w) / 2, text.getBottom() + h/2, w, h);
}

void ResultsComponent::saveToFile()
{
    FileChooser fileChooser ("Select file", File(), "*.txt", true);

    if (fileChooser.browseForFileToSave (true))
    {
        auto result = fileChooser.getResult();
        result.create();
        result.replaceWithText (logic->getResults());
    }
}
