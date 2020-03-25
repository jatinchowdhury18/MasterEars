#include "Configuration.h"

Configuration::Configuration (File& file, EQType type, EQAmt amt, int numTrials) :
    file (file),
    type (type),
    amt (amt),
    numTrials (numTrials)
{
    DBG ("Created new configuration!");
    DBG (getConfigString());
}

String Configuration::getConfigString() const
{
    String res;
    res += "Configuration:\n";
    res += "File: " + file.getFileName() + "\n";
    res += "EQ Type: " + getStringFor (type) + "\n";
    res += "EQ Amount: " + getStringFor (amt) + "\n";
    res += "Num Trials: " + String (numTrials) + "\n";

    return res;
}

String Configuration::getStringFor (EQType type)
{
    if (type == EQType::Boost)
        return "Boost";
        
    if (type == EQType::Cut)
        return "Cut";
        
    if (type == EQType::BoostAndCut)
        return "Boost and Cut";
    
    return "UNKNOWN!!!";
}

String Configuration::getStringFor (EQAmt amt)
{
    if (amt == EQAmt::Three)
        return "3dB";

    if (amt == EQAmt::Six)
        return "6db";

    if (amt == EQAmt::Nine)
        return "9dB";

    return "UNKNOWN!!!";
}

StringArray Configuration::getTypeChoices()
{
    return StringArray ({ "Boost", "Cut" }); // , "Boost and Cut" });
}

StringArray Configuration::getAmtChoices()
{
    return StringArray ({ "3 dB", "6 dB", "9 dB" });
}    
