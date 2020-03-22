#ifndef SESSIONCOMPONENT_H_INCLUDED
#define SESSIONCOMPONENT_H_INCLUDED

#include "../Backend/Configuration.h"
#include "../Backend/Logic.h"
#include "Player.h"
#include "FreqButtons.h"

class SessionComponent : public Component,
                         private FreqButtons::Listener
{
public:
    SessionComponent (Configuration* config);

    void resized() override;
    void freqBandSelected (int band) override;

    struct Listener
    {
        ~Listener() {}
        virtual void sessionComplete (Logic* /*logic*/) {}
    };

    void addListener (Listener* l) { listeners.add (l); }
    void removeListener (Listener* l) { listeners.remove (l); }

private:
    Player player;
    FreqButtons freqButtons;

    int trialNum = 0;
    const int numTrials;
    Label trialsLabel;

    std::unique_ptr<Configuration> config;
    void startTrial();
    std::unique_ptr<Logic> logic;
    ListenerList<Listener> listeners;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SessionComponent)
};

#endif // SESSIONCOMPONENT_H_INCLUDED

