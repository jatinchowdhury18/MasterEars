#include "ResultsComponent.h"

ResultsComponent::ResultsComponent (Logic* logic) :
    logic (logic)
{
    addAndMakeVisible (text);
    text.setMultiLine (true);
    text.setReadOnly (true);
    text.setText (logic->getResults());
    text.setScrollbarsShown (true);
}

void ResultsComponent::resized()
{
    text.setBounds (getLocalBounds());
}
