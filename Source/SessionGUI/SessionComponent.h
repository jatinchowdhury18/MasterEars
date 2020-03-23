#ifndef SESSIONCOMPONENT_H_INCLUDED
#define SESSIONCOMPONENT_H_INCLUDED

#include "../Backend/Configuration.h"
#include "../Backend/Logic.h"
#include "Player.h"
#include "FreqButtons.h"
#include "../Defs.h"

class SessionComponent : public Component,
                         private FreqButtons::Listener
{
CREATE_LISTENER (Listener, listeners, virtual void sessionComplete (Logic* /*logic*/) {})
public:
    SessionComponent (Configuration* config);

    void resized() override;
    void freqBandSelected (int band) override;

private:
    Player player;
    FreqButtons freqButtons;

    int trialNum = 0;
    const int numTrials;
    Label trialsLabel;

    std::unique_ptr<Configuration> config;
    void startTrial();
    std::unique_ptr<Logic> logic;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SessionComponent)
};

#endif // SESSIONCOMPONENT_H_INCLUDED

