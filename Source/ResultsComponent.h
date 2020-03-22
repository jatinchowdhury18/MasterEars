#ifndef RESULTSCOMPONENT_H_INCLUDED
#define RESULTSCOMPONENT_H_INCLUDED

#include "Backend/Logic.h"

class ResultsComponent : public Component
{
public:
    ResultsComponent (Logic* logic);

    void resized() override;

private:
    std::unique_ptr<Logic> logic;
    TextEditor text;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResultsComponent)
};

#endif // RESULTSCOMPONENT_H_INCLUDED
