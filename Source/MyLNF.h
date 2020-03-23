#ifndef MYLNF_H_INCLUDED
#define MYLNF_H_INCLUDED

#include "JuceHeader.h"

namespace MyColours
{
    const Colour black { 0xff231f20 };
    const Colour red   { 0xffdf6c4f };
    const Colour green { 0xff3c948b };
    const Colour blue  { 0xffc5e2e5 };
}

class MyLNF : public LookAndFeel_V4
{
public:
    MyLNF();

    Typeface::Ptr getTypefaceForFont (const Font&) override;
    Font getTextButtonFont (TextButton&, int buttonHeight) override;
    Font getComboBoxFont (ComboBox&) override;
    Font getPopupMenuFont() override;
    Font getAlertWindowTitleFont() override;

    void drawButtonBackground (Graphics&, Button&, const Colour&, bool, bool) override;
    void drawButtonText (Graphics& g, TextButton& button, bool, bool) override;
    void drawToggleButton (Graphics& g, ToggleButton& button, bool, bool) override;

    void drawProgressBar (Graphics& g, ProgressBar& progressBar,
                                int width, int height,
                                double progress, const String& textToShow) override;

private:
    Typeface::Ptr nunitoSans;
    Typeface::Ptr nunitoSansBold;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyLNF)
};

#endif // MYLNF_H_INCLUDED
