#include "ResultsComponent.h"
#include "../MyLNF.h"

ResultsComponent::ResultsComponent (Logic* logic) :
    logic (logic),
    list (logic)
{
    addAndMakeVisible (list);

    addAndMakeVisible (saveButton);
    saveButton.setColour (TextButton::buttonOnColourId, MyColours::green);
    saveButton.onClick = [=] { saveToFile(); };

    addAndMakeVisible (restartButton);
    restartButton.setColour (TextButton::buttonOnColourId, MyColours::red);
    restartButton.onClick = [=] { listeners.call (&Listener::goHome); };
}

void ResultsComponent::paint (Graphics& g)
{
    const int w = list.getWidth();
    const int h = list.getRowHeight();
    const int xOff = int (0.67f * float (getWidth() / 5));

    g.setColour (Colours::white);
    g.setFont (Font (float (h) * 0.9f).boldened());

    g.drawFittedText ("Trial",  xOff,          0, w / 10,    h, Justification::centred, 1);
    g.drawFittedText ("Actual", xOff + w / 10, 0, 2 * w / 5, h, Justification::centred, 1);
    g.drawFittedText ("Guess",  xOff + w / 2,  0, 2 * w / 5, h, Justification::centred, 1);
    g.drawFittedText ("Score",  xOff + 9*w/10, 0, w / 10,    h, Justification::centred, 1);

    Line<int> headerLine (list.getX(), list.getY(), list.getRight(), list.getY());
    g.drawLine (headerLine.toFloat(), 2.0f);

    g.setColour (MyColours::green);
    g.setFont (Font (float (h)).boldened());
    g.drawFittedText ("Total: " + String (logic->calcScore()), list.getX(),
        list.getBottom(), list.getWidth() - list.getVerticalScrollBar().getWidth() - 10, h, Justification::right, 1);

    // vertical text
    GlyphArrangement ga;
    ga.addLineOfText (Font (float (h) * 1.25f).boldened(), "Results", 0, 0);
    Path p;
    ga.createPath (p);

    auto pBounds = p.getBounds();
    p.applyTransform (AffineTransform()
        .rotated (-MathConstants<float>::halfPi,
            pBounds.getCentreX(), pBounds.getCentreY())
        .translated (0.0f, (float) getHeight() / 2));

    g.setColour (Colours::white);
    g.fillPath (p);
}

void ResultsComponent::resized()
{
    const int h = getHeight() / 6;
    const int w = getWidth() / 5;

    list.setBounds (getLocalBounds()
        .withTrimmedBottom (3 * h / 2)
        .withTrimmedLeft (int (0.67f * float (w)))
        .withTrimmedRight (int (0.33f * float (w))));
    list.setRowHeight (list.getHeight() / 6);
    list.setBounds (list.getBounds().withTrimmedTop (list.getRowHeight()));

    const int pad = 10;
    saveButton.setBounds (getWidth() / 2 - w - pad, list.getBottom() + h/2, w, h);
    restartButton.setBounds (getWidth() / 2 + pad, list.getBottom() + h/2, w, h);

    repaint();
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
