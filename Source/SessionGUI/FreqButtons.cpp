#include "FreqButtons.h"
#include "../MyLNF.h"

FreqButtons::FreqButtons()
{
    for (auto fStr : freqStrings)
    {
        TextButton* button = new TextButton (fStr);
        button->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
        button->setRadioGroupId (0x2345);
        button->setClickingTogglesState (true);
        button->setColour (TextButton::buttonOnColourId, MyColours::red);
        addAndMakeVisible (button);
        buttons.add (button);
    }

    buttons.getFirst()->setConnectedEdges (Button::ConnectedOnRight);
    buttons.getLast()->setConnectedEdges (Button::ConnectedOnLeft);

    addAndMakeVisible (submitButton);
    submitButton.setColour (TextButton::buttonOnColourId, MyColours::green);
    submitButton.onClick = [=] { submitButtonPressed(); };

    addAndMakeVisible (quitButton);
    quitButton.setColour (TextButton::buttonOnColourId, MyColours::red);
    quitButton.onClick = [=] { quitButtonPressed(); };
}

StringArray FreqButtons::createFreqStrings()
{
    StringArray freqs;
    freqs.add ("60 Hz");
    freqs.add ("125 Hz");
    freqs.add ("250 Hz");
    freqs.add ("500 Hz");
    freqs.add ("1 kHz");
    freqs.add ("2 kHz");
    freqs.add ("4 kHz");
    freqs.add ("8 kHz");
    freqs.add ("16 kHz");

    return freqs;
}

int FreqButtons::getNumFreqBands()
{
    return createFreqStrings().size();
}

void FreqButtons::resized()
{
    auto bWidth = (getWidth() - 10) / buttons.size();
    auto bHeight = getHeight() / 3;

    for (int i = 0; i < buttons.size(); ++i)
        buttons[i]->setBounds (5 + i * bWidth, 0, bWidth, bHeight);

    const int w = getWidth() / 5;
    const int pad = 10;
    submitButton.setBounds (getWidth() / 2 - w - pad, 3*bHeight/2, w, bHeight);
    quitButton.setBounds (getWidth() / 2 + pad, 3*bHeight/2, w, bHeight);
}

void FreqButtons::submitButtonPressed()
{
    for (int i = 0; i < buttons.size(); ++i)
    {
        if (buttons[i]->getToggleState())
        {
            listeners.call (&Listener::freqBandSelected, i);
            buttons[i]->setToggleState (false, dontSendNotification);
            return;
        }
    }

    bubble.reset (new BubbleMessageComponent (500));
    addChildComponent (bubble.get());

    AttributedString attStr;
    attStr.append ("Must select a band!", Font (24.0f));
    attStr.setColour (MyColours::red);

    auto rect = getLocalArea (&submitButton, submitButton.getLocalBounds());

    bubble->showAt (rect, attStr, 2000, true, false);
}

void FreqButtons::quitButtonPressed()
{
    int res = AlertWindow::showYesNoCancelBox (AlertWindow::WarningIcon, "Quitting",
        "Are you sure you want to quit? All progress will be lost.");

    if (res == 1) // quitting
        listeners.call (&Listener::quit);
}
