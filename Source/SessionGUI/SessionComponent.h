#ifndef SESSIONCOMPONENT_H_INCLUDED
#define SESSIONCOMPONENT_H_INCLUDED

#include "WaveformViewer.h"

class SessionComponent : public Component
{
public:
    SessionComponent (File& file);

    void resized() override;
    void paint (Graphics& g) override;

private:
    WaveformViewer waveform;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SessionComponent)
};

#endif // SESSIONCOMPONENT_H_INCLUDED

