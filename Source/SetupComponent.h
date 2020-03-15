#include "JuceHeader.h"

class SetupComponent : public Component
{
public:
    SetupComponent();

    void resized() override;
    void paint (Graphics& g) override;

    void loadFile();

    struct Listener
    {
        ~Listener() {}
        virtual void setupComplete (File* file) {}
    };

    void addListener (Listener* l) { listeners.add (l); }
    void removeListener (Listener* l) { listeners.remove (l); }

private:
    ListenerList<Listener> listeners;

    TextButton fileButton { "Load file" };
    TextButton nextButton { "Next" };

    Label fileLabel;

    std::unique_ptr<File> file;

    std::unique_ptr<BubbleMessageComponent> bubble;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SetupComponent)
};

