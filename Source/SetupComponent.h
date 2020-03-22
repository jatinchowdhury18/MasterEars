#ifndef SETUPCOMPONENT_H_INCLUDED
#define SETUPCOMPONENT_H_INCLUDED

#include "Backend/Configuration.h"
#include "DataManager.h"

class SetupComponent : public Component
{
public:
    SetupComponent();

    void resized() override;

    void loadFile();

    struct Listener
    {
        virtual ~Listener() {}
        virtual void setupComplete (Configuration* /*config*/) {}
    };

    void addListener (Listener* l) { listeners.add (l); }
    void removeListener (Listener* l) { listeners.remove (l); }

private:
    ListenerList<Listener> listeners;

    TextButton fileButton { "Load file" };
    TextButton nextButton { "Next" };

    Label fileLabel;
    Label numTrialsLabel;
    
    ComboBox eqTypeBox;
    ComboBox eqAmtBox;
    ComboBox numTrialsBox;

    std::unique_ptr<File> file;

    std::unique_ptr<BubbleMessageComponent> bubble;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SetupComponent)
};

#endif // SETUPCOMPONENT_H_INCLUDED

