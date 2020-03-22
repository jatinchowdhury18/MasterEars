#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

#include "JuceHeader.h"

enum class EQType
{
    Boost,
    Cut,
    BoostAndCut
};

enum class EQAmt
{
    Three = 0,
    Six,
    Nine,
};

class Configuration
{
public:
    Configuration (File& file, EQType type, EQAmt amt, int numTrials);

    static String getStringFor (EQType type);
    static String getStringFor (EQAmt amt);

    static StringArray getTypeChoices();
    static StringArray getAmtChoices();

    const File file;
    const EQType type;
    const EQAmt amt;
    const int numTrials;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Configuration)
};

#endif // CONFIGURATION_H_INCLUDED

