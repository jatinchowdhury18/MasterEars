#ifndef SETUPCOMPONENT_H_INCLUDED
#define SETUPCOMPONENT_H_INCLUDED

#include "Backend/Configuration.h"
#include "DataManager.h"
#include "Defs.h"

class SetupComponent : public Component
{
CREATE_LISTENER (Listener, listeners, virtual void setupComplete (Configuration* /*config*/) {})
public:
    SetupComponent();

    void resized() override;

    void loadFile();
    void nextButtonPressed();

private:
    TextButton fileButton { "Load file" };
    TextButton nextButton { "Next" };

    Label fileLabel;
    Label numTrialsLabel;
    TextEditor instructions;
    
    ComboBox eqTypeBox;
    ComboBox eqAmtBox;
    ComboBox numTrialsBox;

    std::unique_ptr<File> file;

    std::unique_ptr<BubbleMessageComponent> bubble;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SetupComponent)
};

#endif // SETUPCOMPONENT_H_INCLUDED
