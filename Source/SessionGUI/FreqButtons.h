#ifndef FREQBUTTONS_H_INCLUDED
#define FREQBUTTONS_H_INCLUDED

#include "JuceHeader.h"

class FreqButtons : public Component
{
public:
    FreqButtons();

    void resized() override;

    struct Listener
    {
    public:
        virtual ~Listener() {}
        virtual void freqBandSelected (int /*band*/) {}
    };

    void addListener (Listener* l) { listeners.add (l); }
    void removeListener (Listener* l) { listeners.remove (l); }

private:
    void submitButtonPressed();

    OwnedArray<TextButton> buttons;
    TextButton submitButton { "Enter" };

    std::unique_ptr<BubbleMessageComponent> bubble;

    ListenerList<Listener> listeners;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreqButtons)
};

#endif // FREQBUTTONS_H_INCLUDED
