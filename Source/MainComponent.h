#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "SetupComponent.h"
#include "SessionGUI/SessionComponent.h"
#include "ResultsComponent.h"
#include "MyLNF.h"

class MainComponent : public Component,
                      private SetupComponent::Listener,
                      private SessionComponent::Listener
{
public:
    MainComponent();
    ~MainComponent();

    void resized() override;
    void paint(Graphics& g) override;

    // Program flow callbacks
    void setupComplete (Configuration* config) override;
    void sessionComplete (Logic* logic) override;

private:
    SetupComponent setupComponent;
    std::unique_ptr<SessionComponent> sessComponent;
    std::unique_ptr<ResultsComponent> resComponent;

    DrawableButton settingsButton;

    MyLNF lnf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

#endif // MAINCOMPONENT_H_INCLUDED

