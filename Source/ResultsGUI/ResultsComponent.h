#ifndef RESULTSCOMPONENT_H_INCLUDED
#define RESULTSCOMPONENT_H_INCLUDED

#include "ResultsList.h"

class ResultsComponent : public Component
{
public:
    ResultsComponent (Logic* logic);

    void resized() override;
    void paint (Graphics& g) override;

private:
    void saveToFile();

    std::unique_ptr<Logic> logic;
    // TextEditor text;
    ResultsList list;
    TextButton saveButton { "Save to file" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResultsComponent)
};

#endif // RESULTSCOMPONENT_H_INCLUDED
