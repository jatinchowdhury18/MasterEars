#include "JuceHeader.h"
#include "SetupComponent.h"

class MainComponent : public Component,
                      private SetupComponent::Listener
{
public:
    MainComponent();

    void resized() override;
    void paint(Graphics& g) override;

    void setupComplete (File* file) override;

private:
    SetupComponent setupComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

