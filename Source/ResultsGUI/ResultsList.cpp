#include "ResultsList.h"
#include "../MyLNF.h"

ResultsList::ResultsList (Logic* logic) :
    ListBox (String(), this),
    logic (logic)
{
}

int ResultsList::getNumRows()
{
    return logic->getNumTrials();
}

void ResultsList::paintListBoxItem (int rowNum, Graphics& g, int width, int height, bool /*rowSelected*/)
{
    g.fillAll (MyColours::black);

    g.setColour (Colours::white);
    g.setFont (Font (float (height) * 0.9f).boldened());
    g.drawFittedText (String (rowNum+1), 0, 0, width / 10, height, Justification::centred, 1);

    g.setFont (Font (float (height) * 0.9f));
    g.drawFittedText (logic->getGuess (rowNum, true), width/10, 0, 2 * width / 5, height, Justification::centred, 1);
    g.drawFittedText (logic->getGuess (rowNum, false), width/2, 0, 2 * width / 5, height, Justification::centred, 1);

    g.setColour (MyColours::red);
    g.setFont (Font (float (height) * 0.9f).boldened());
    g.drawFittedText ("+" + String (logic->getScoreForTrial (rowNum)), 9*width/10, 0, width / 10, height, Justification::centred, 1);

    g.setColour (Colours::white.withAlpha (0.25f));
    g.drawLine (0.0f, (float) height - 1.0f, (float) width, (float) height);
}
