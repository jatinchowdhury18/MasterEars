#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "SetupComponent.h"
#include "SessionGUI/SessionComponent.h"

class MainComponent : public Component,
                      private SetupComponent::Listener
{
public:
    MainComponent();
    ~MainComponent();

    void resized() override;
    void paint(Graphics& g) override;

    void setupComplete (Configuration& config) override;

private:
    SetupComponent setupComponent;
    std::unique_ptr<SessionComponent> sessComponent;

    TextButton settingsButton { "Audio Settings" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

#endif // MAINCOMPONENT_H_INCLUDED

