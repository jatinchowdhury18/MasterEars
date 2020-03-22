#include "FreqButtons.h"

FreqButtons::FreqButtons()
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

    for (auto fStr : freqs)
    {
        TextButton* button = new TextButton (fStr);
        button->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
        button->setRadioGroupId (0x2345);
        button->setClickingTogglesState (true);
        button->setColour (TextButton::buttonOnColourId, Colours::yellow);
        button->setColour (TextButton::textColourOnId, Colours::black);
        addAndMakeVisible (button);
        buttons.add (button);
    }

    buttons.getFirst()->setConnectedEdges (Button::ConnectedOnRight);
    buttons.getLast()->setConnectedEdges (Button::ConnectedOnLeft);

    addAndMakeVisible (submitButton);
    submitButton.onClick = [=] { submitButtonPressed(); };
}

void FreqButtons::resized()
{
    auto bWidth = (getWidth() - 10) / buttons.size();

    for (int i = 0; i < buttons.size(); ++i)
        buttons[i]->setBounds (5 + i * bWidth, 0, bWidth, 50);

    submitButton.setBounds ((getWidth() - 100) / 2, 75, 100, 25);
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

    bubble.reset (new BubbleMessageComponent (1000));
    addChildComponent (bubble.get());

    AttributedString attStr;
    attStr.append ("Must select a band!", Font (16.0f));
    attStr.setColour (Colours::white);            

    auto rect = getLocalArea (&submitButton, submitButton.getLocalBounds());

    bubble->showAt (rect, attStr, 1000, true, false);
}
