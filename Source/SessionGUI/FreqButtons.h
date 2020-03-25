#ifndef FREQBUTTONS_H_INCLUDED
#define FREQBUTTONS_H_INCLUDED

#include "JuceHeader.h"
#include "../Defs.h"

class FreqButtons : public Component
{
CREATE_LISTENER (Listener, listeners, virtual void freqBandSelected (int /*band*/) {}\
                                      virtual void quit() {})
public:
    FreqButtons();

    void resized() override;

    static int getNumFreqBands();
    static StringArray createFreqStrings();

private:
    void submitButtonPressed();
    void quitButtonPressed();

    OwnedArray<TextButton> buttons;
    TextButton submitButton { "Enter" };
    TextButton quitButton   { "Quit" };
    StringArray freqStrings = createFreqStrings();

    std::unique_ptr<BubbleMessageComponent> bubble;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreqButtons)
};

#endif // FREQBUTTONS_H_INCLUDED
