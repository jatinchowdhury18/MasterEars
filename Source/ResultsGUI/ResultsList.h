#ifndef RESULTSLIST_H_INCLUDED
#define RESULTSLIST_H_INCLUDED

#include "../Backend/Logic.h"

class ResultsList : public ListBox,
                    public ListBoxModel
{
public:
    ResultsList (Logic* logic);

    int getNumRows() override;
    void paintListBoxItem (int rowNum, Graphics& g, int width, int height, bool rowSelected) override;

private:
    Logic* logic;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResultsList)
};

#endif // RESULTSLIST_H_INCLUDED
