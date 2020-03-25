#ifndef RESULTSCOMPONENT_H_INCLUDED
#define RESULTSCOMPONENT_H_INCLUDED

#include "ResultsList.h"
#include "../Defs.h"

class ResultsComponent : public Component
{
CREATE_LISTENER (Listener, listeners, virtual void goHome() {})
public:
    ResultsComponent (Logic* logic);

    void resized() override;
    void paint (Graphics& g) override;

private:
    void saveToFile();

    std::unique_ptr<Logic> logic;
    ResultsList list;
    TextButton saveButton { "Save to file" };
    TextButton restartButton { "Try Again" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResultsComponent)
};

#endif // RESULTSCOMPONENT_H_INCLUDED
