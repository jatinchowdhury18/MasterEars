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
    Three,
    Six,
    Nine,
};

class Configuration
{
public:
    Configuration (File& file, EQType type, EQAmt amt) :
        file (file),
        type (type),
        amt (amt)
    {
        DBG ("Created new configuration!");
        DBG ("File: " + file.getFileName());
        DBG ("EQ Type: " + getStringFor (type));
        DBG ("EQ Amount: " + getStringFor (amt));
    }

    String getStringFor (EQType type)
    {
        if (type == EQType::Boost)
            return "Boost";
        
        if (type == EQType::Cut)
            return "Cut";
        
        if (type == EQType::BoostAndCut)
            return "Boost and Cut";
    
        return "UNKNOWN!!!";
    }

    String getStringFor (EQAmt amt)
    {
        if (amt == EQAmt::Three)
            return "3dB";

        if (amt == EQAmt::Six)
            return "6db";

        if (amt == EQAmt::Nine)
            return "9dB";

        return "UNKNOWN!!!";
    }

    static StringArray getTypeChoices()
    {
        return StringArray ({ "Boost", "Cut", "Boost and Cut" });
    }

    static StringArray getAmtChoices()
    {
        return StringArray ({ "3 dB", "6 dB", "9 dB" });
    }

    const File file;
    const EQType type;
    const EQAmt amt;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Configuration)
};

#endif // CONFIGURATION_H_INCLUDED

